#pragma once
#include "ASTNode.h"
#include "TypeNode.h"
#include "IDNode.h"
#include "TempNode.h"

struct StmtNode : public ASTNode
{
    AST_e get_AST_e() override { return AST_e::Stmt; }
    virtual stmt_e get_stmt_e() = 0;
    void print(int depth)
    {
        switch (this->get_stmt_e())
        {
        case stmt_e::IF:
            ((IFStmt*)this)->print(depth);
            break;
        case stmt_e::FunDef:
            ((FuncDefStmt*)this)->print(depth);
            break;
        case stmt_e::FunDec:
            ((FuncDecStmt*)this)->print(depth);
            break;
        case stmt_e::VarDef:
            ((VarDef*)this)->print(depth);
            break;
        case stmt_e::StructDec:
            ((StructDecStmt*)this)->print(depth);
            break;
        case stmt_e::StructDef:
            ((StructDefStmt*)this)->print(depth);
            break;
        case stmt_e::FOR:
            ((ForStmt*)this)->print(depth);
            break;
        case stmt_e::While:
            ((WhileStmt*)this)->print(depth);
            break;
        case stmt_e::Block:
            ((BlockStmt*)this)->print(depth);
            break;
        case stmt_e::Expr:
            ((ExprStmtNode*)this)->print(depth);
            break;
        default:
            break;
        }
    }
};

struct ExprNode;

struct ExprStmtNode : public StmtNode
{
    // 表达式语句：表达式+分号
    ExprNode *expr;
    stmt_e get_stmt_e() override { return stmt_e::Expr; };
    ExprStmtNode(ExprNode *_Expr) : expr(_Expr) {}
    ~ExprStmtNode() = default;
    void print(int depth)
    {
        printDepth(depth);
        cout << "Expr Stmt. " << endl;
        this->expr->print(depth + 1);
    }
};

struct IFStmt : public StmtNode
{
    // if语句
    ExprNode *test;     //判断条件
    StmtNode *trueRun;  //为真时运行
    StmtNode *falseRun; //为假时运行
    stmt_e get_stmt_e() override { return stmt_e::IF; };
    IFStmt(ExprNode *_Test, StmtNode *_TrueRun, StmtNode *_FalseRun)
        : test(_Test), trueRun(_TrueRun), falseRun(_FalseRun)
    {
    }
    ~IFStmt() = default;
    void print(int depth)
    {
        printDepth(depth);
        cout << "IF Stmt." << endl;
        printDepth(depth + 1);
        cout << "Judge conditions." << endl;
        this->test->print(depth + 2);
        printDepth(depth + 1);
        cout << "Run if true." << endl;
        this->trueRun->print(depth + 2);
        if (!falseRun)
        {
            printDepth(depth);
            cout << "ELSE Stmt." << endl;
            printDepth(depth + 1);
            cout << "Run if false." << endl;
            this->falseRun->print(depth + 2);
        }
    }
};

struct VarDef
{
    TypeNode *type;
    IDNode *ID;
    ExprNode *init;
    void print(int depth)
    {
        printDepth(depth);
        cout << "Var def." << endl;
        this->ID->print(depth + 1);
        if (!this->init)
        {
            printDepth(depth + 1);
            cout << "Var Init." << endl;
            this->init->print(depth + 2);
        }
    }
};

struct VarDefStmt : public StmtNode
{
    // 变量定义语句
    TypeNode *basicType = nullptr;

    std::vector<VarDef> vars;
    stmt_e get_stmt_e() override { return stmt_e::VarDef; };
    ~VarDefStmt() = default;
    VarDefStmt(TypeNode *_Type, ASTNode *_Vars)
    {
        this->basicType = _Type;
        addVars(_Vars);
    }
    void addVar(ASTNode *type, ASTNode *ID, ASTNode *init)
    {
        if (type && type->get_AST_e() != AST_e::Type)
        {
            printf("变量定义语句，变量名类型不是一个类型节点\n");
            return;
        }
        if (ID && ID->get_AST_e() != AST_e::ID)
        {
            printf("变量定义语句，变量名不是一个id节点\n");
            return;
        }
        if (init && init->get_AST_e() != AST_e::Expr)
        {
            printf("变量定义语句，变量名初始化值不是一个表达式节点\n");
            return;
        }
        addVar((TypeNode *)type, (IDNode *)ID, (ExprNode *)init);
    }
    void addVar(TypeNode *type, IDNode *ID, ExprNode *init)
    {
        VarDef var;
        var.type = type;
        var.init = init;
        var.ID = ID;

        vars.push_back(var);
    }
    void addVars(ASTNode *_Vars);

    void print(int depth)
    {
        printDepth(depth);
        cout << "Var Def Stmt." << endl;
        this->basicType->print(depth + 1);
        print(depth + 1);
        cout << "Var Def List." << endl;
        for (int k = 0; k < (this->vars).size(); k++)
        {
            (this->vars[k]).print(depth + 2);
        }
    }
};

struct ForStmt : public StmtNode
{
    // for 语句
    StmtNode *init;  //初始化
    ExprNode *test;  // 判断循环调控
    ExprNode *other; // 第三个表达式
    StmtNode *run;   //执行的语句块
    stmt_e get_stmt_e() override { return stmt_e::FOR; };
    ~ForStmt() = default;
    ForStmt(StmtNode *_Init, ExprNode *_Test, ExprNode *_Other, StmtNode *_Run)
        : init(_Init), test(_Test), other(_Other), run(_Run)
    {
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "For Stmt." << endl;
        if (!this->init)
        {
            printDepth(depth + 1);
            cout << "Init Stmt." << endl;
            this->init->print(depth + 2);
        }
        if (!this->test)
        {
            printDepth(depth + 1);
            cout << "Judge Conditions." << endl;
            this->test->print(depth + 2);
        }
        if (!this->other)
        {
            printDepth(depth + 1);
            cout << "Increment" << endl;
            this->other->print(depth + 2);
        }
        printDepth(depth + 1);
        cout << "Action." << endl;
        this->run->print(depth + 2);
    }
};

struct WhileStmt : public StmtNode
{
    // for 语句
    ExprNode *test; // 判断循环调控
    StmtNode *run;  //执行的语句块
    stmt_e get_stmt_e() override { return stmt_e::While; };
    ~WhileStmt() = default;
    WhileStmt(ExprNode *_Test, StmtNode *_Run)
        : test(_Test), run(_Run)
    {
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "While Stmt. " << endl;
        print(depth + 1);
        cout << "Judge Condition." << endl;
        this->test->print(depth + 2);
        printDepth(depth + 1);
        cout << "Action." << endl;
        this->run->print(depth + 2);
    }
};

struct BlockStmt : public StmtNode
{
    // 语句块
    std::vector<StmtNode *> stmts;
    ~BlockStmt() = default;
    BlockStmt(ASTNode *_Stmts)
    {
        addStmts(_Stmts);
    }
    stmt_e get_stmt_e() override { return stmt_e::Block; }
    void addStmts(ASTNode *_Stmts)
    {
        if (!_Stmts)
            return;
        if (_Stmts->get_AST_e() == AST_e::Temp)
        {
            for (ASTNode *n : ((TempNode *)_Stmts)->childList)
                addStmts(_Stmts);
        }
        else if (_Stmts->get_AST_e() == AST_e::Stmt)
        {
            stmts.push_back((StmtNode *)_Stmts);
        }
        else
        {
            printf("语句块内不全是语句\n");
        }
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Comp Stmt. " << endl;
        for (int k = 0; k < (this->stmts).size(); k++)
        {
            (this->stmts)[k]->print(depth + 2);
        }
    }
};

struct FuncDecStmt : public StmtNode
{
    // 函数声明语句
    TypeNode *re;                                      //返回值类型
    IDNode *name = nullptr;                            //函数名
    std::vector<std::pair<TypeNode *, IDNode *>> args; // 参数列表
    stmt_e get_stmt_e() override { return stmt_e::FunDec; }
    ~FuncDecStmt() = default;
    FuncDecStmt(TypeNode *_Re, ASTNode *_NameAndArgs) : re(_Re)
    {
        addNameAndArgs(_NameAndArgs);
    }
    void addNameAndArgs(ASTNode *n)
    {
        if (!n)
        {
            if (!name)
                printf("函数声明内无函数名");
            return;
        }
        if (n->get_AST_e() == AST_e::Temp)
        {
            TempNode *temp = (TempNode *)n;
            for (ASTNode *n : temp->childList)
                addNameAndArgs(n);
        }
        else if (n->get_AST_e() == AST_e::ID)
        {
            if (name == nullptr)
            {
                name = (IDNode *)n;
            }
            else
            {
                printf("函数声明的temp节点中，第一个非temp节点不是ID节点\n");
            }
        }
        else if (n->get_AST_e() == AST_e::Type)
        {
            args.push_back(std::make_pair<TypeNode *, IDNode *>((TypeNode *)n, nullptr));
        }
        else if (n->get_AST_e() == AST_e::ID)
        {
            if (args.size() == 0)
            {
                printf("函数声明参数列表中在ID前无类型\n");
                return;
            }
            if (args.back().second != nullptr)
            {
                printf("函数声明中参数列表中一个类型类型有多个ID\n");
                return;
            }
            if (args.back().second == nullptr)
            {
                args.back().second = (IDNode *)n;
            }
        }
        else
        {
            printf("函数声明参数列表内有除type节点和id节点以外的节点\n");
            return;
        }
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Func Dec Stmt. " << endl;
        printDepth(depth + 1);
        cout << "Return Type." << endl;
        this->re->print(depth + 2);
        // printDepth(depth + 1);
        // cout << "Var Dec Stmt." << endl;
        // this->re->print(depth + 2);
        // this->name->print(depth + 2);
        printDepth(depth + 1);
        cout << "Func Name." << endl;
        this->name->print(depth + 2);
        printDepth(depth + 1);
        cout << "Para Dec Stmt." << endl;
        for (int k = 0; k < (this->args).size(); k++)
        {
            printDepth(depth + 2);
            cout << "Var Dec." << endl;
            (this->args)[k].first->print(depth + 3);
            (this->args)[k].second->print(depth + 3);
        }
    }
};

struct FuncDefStmt : public StmtNode
{
    // 函数定义语句
    FuncDecStmt funcdec; // 函数声明
    BlockStmt *block;    //函数体
    ~FuncDefStmt() = default;
    stmt_e get_stmt_e() override { return stmt_e::FunDef; }
    FuncDefStmt(TypeNode *_Re, ASTNode *_NameAndArgs, StmtNode *_Block)
        : funcdec(_Re, _NameAndArgs)
    {
        if (_Block->get_stmt_e() == stmt_e::Block)
        {
            this->block = (BlockStmt *)_Block;
        }
        else
        {
            printf("函数体不是一个块语句");
        }
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Func Def Stmt." << endl;
        this->funcdec.print(depth + 1);
        this->block->print(depth + 1);
    }
};

struct StructDecStmt : StmtNode
{
    // 结构体声明
    StructTypeNode *type;
    stmt_e get_stmt_e() override { return stmt_e::StructDec; }
    StructDecStmt(IDNode *_ID)
    {
        type = StructTypeNode::getStructType(_ID->ID);
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Struct Dec Stmt." << endl;
        this->type->print(depth + 1);
    }
};

struct StructDefStmt : StmtNode
{
    // 结构体定义
    StructTypeNode *type;
    stmt_e get_stmt_e() override { return stmt_e::StructDef; }
    StructDefStmt(IDNode *_ID, ASTNode *_Members)
    {
        type = StructTypeNode::getStructType(_ID->ID);
        type->addMembers(_Members);
    }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Struct Def Stmt. " << endl;
        this->type->print(depth + 1);
    }
};

struct ReturnStmt : StmtNode
{
    // return 语句
    ExprNode *expr;
    ReturnStmt(ExprNode *_Expr) : expr(_Expr){};
    stmt_e get_stmt_e() override { return stmt_e::Return; }

    void print(int depth)
    {
        printDepth(depth);
        cout << "Return Stmt. " << endl;
        this->expr->print(depth + 1);
    }
};
