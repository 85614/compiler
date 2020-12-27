#pragma once
#include "ASTNode.h"
#include "TypeNode.h"
#include "IDNode.h"
#include "TempNode.h"
#include "ExprNode.h"

struct StmtNode : public ASTNode
{

    AST_e get_AST_e() override { return AST_e::Stmt; }
    virtual stmt_e get_stmt_e() = 0;
    virtual bool isScope() { return false; }
};

struct ScopeStmtNode : public StmtNode
{
    // 会产生新作用域ScopeStmtNode的语句
    SymbolTable *belong = nullptr;
    void setSymbolTable(SymbolTable *_Parent)
    {
        belong = _Parent;
    }
    virtual bool isScope() override { return true; }
    void makeSymbolTable() override
    {
        // 会产生新作用域
        setSymbolTable(global->makeChild(this, this->tokenCount));
        addChild();
    }
    virtual void addChild(){};
};

inline ScopeStmtNode *toScope(StmtNode *stmt)
{
    if (stmt->isScope())
        return (ScopeStmtNode *)stmt;
    my_error("scope cat error");
    return nullptr;
}

struct ExprStmtNode : public StmtNode
{
    // 表达式语句：表达式+分号
    ExprNode *expr;
    stmt_e get_stmt_e() override { return stmt_e::Expr; };
    ExprStmtNode(ExprNode *_Expr) : expr(_Expr)
    {
        if (!_Expr)
            cout << "表达式语句的表达式为NULL\n"
                 << endl;
    }
    std::string dasdhasjhdgs;

    void output(std::ostream &os) override
    {
        expr->output(os);
    }
    ~ExprStmtNode() = default;
    void print(int depth) override;
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
    void output(std::ostream &os)
    {
        auto v = test->calValue(os);
        int label = nextlable();
        v->GoTo(os, label, false);
        delete v;
        trueRun->output(os);
        if (falseRun)
            os << "    jmp if_over_" << label << "\n";
        os << "goto" << label << ":\n";
        if (falseRun)
        {
            falseRun->output(os);
            os << "if_over_" << label << ":\n";
        }
    }
    ~IFStmt() = default;
    void print(int depth) override;
};

struct VarDef
{
    TypeNode *type;
    IDNode *ID;
    ExprNode *init;
    void print(int depth);
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
        for (auto &var : vars)
        {
            auto type = var.type;
            if (!type->decAble())
            {
                cout << "不允许声明此类型的变量，ID：" << var.ID->ID << "，类型：" << endl;
                type->print(0);
                exit(1);
            }
        }
    }
    void addVar(ASTNode *type, ASTNode *ID, ASTNode *init)
    {
        if (type && type->get_AST_e() != AST_e::Type)
        {
            cout << "变量定义语句，变量名类型不是一个类型节点\n"
                 << endl;
            return;
        }
        if (ID && ID->get_AST_e() != AST_e::ID)
        {
            cout << "变量定义语句，变量名不是一个id节点\n"
                 << endl;
            return;
        }
        if (init && init->get_AST_e() != AST_e::Expr)
        {
            cout << "变量定义语句，变量名初始化值不是一个表达式节点\n"
                 << endl;
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
        global->registe(ID, IDType_e::VarDef, type);
        vars.push_back(var);
    }
    void addVars(ASTNode *_Vars);

    void output(std::ostream &os)
    {
        for (auto &var : vars)
        {
            if (!var.init)
                continue;
            auto v = var.init->calValue(os);
            v->load(os);
            os << "    mov ";
            auto _Off = var.ID->realID->off;
            if (_Off)
                os << "[ebp" << toSignedHex(_Off);
            else
                os << var.ID->realID->name;
            os << "], " << v->str() << "\n";
            delete v;
        }
    }

    void print(int depth) override;
};

inline void addChildSymbolTable(SymbolTable *father, StmtNode *child)
{
    if (child->isScope())
        father->addChild(toScope(child)->belong);
}

struct ForStmt : public ScopeStmtNode
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
    virtual void addChild() override
    {
        // 添加子作用域
        addChildSymbolTable(belong, run);
    }

    void output(std::ostream &os) override
    {
        int label = nextlable();
        init->output(os);
        os << "for_go_on_" << label << ":\n";
        auto testv = test->calValue(os);
        testv->GoTo(os, label, false);
        delete testv;
        run->output(os);
        other->output(os);
        os << "    jmp for_go_on_" << label << "\n";
        os << "goto" << label << ":\n";
    }
    void print(int depth) override;
    // 经测试，for语句的初始化语句和执行语句不是同一个作用域
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
    void output(std::ostream &os) override
    {
        int label = nextlable();
        os << "while_go_on_" << label << ":\n";
        auto v = test->calValue(os);
        v->GoTo(os, label, false);
        delete v;
        run->output(os);
        os << "    jmp while_go_on_" << label << "\n";
        os << "goto" << label << ":\n";
    }

    void print(int depth) override;
};

struct BlockStmt : public ScopeStmtNode
{
    // 语句块
    std::vector<StmtNode *> stmts;
    ~BlockStmt() = default;
    BlockStmt(ASTNode *_Stmts)
    {
        addStmts(_Stmts);
    }
    stmt_e get_stmt_e() override { return stmt_e::Block; }
    void addChild(ASTNode *_Stmt) override
    {
        if (!_Stmt)
            return;
        if (_Stmt->get_AST_e() != AST_e::Stmt)
            cout << "添加非语句节点到语句块中" << endl;
        stmts.push_back((StmtNode *)_Stmt);
    }
    virtual void addChild() override
    {
        // 添加子作用域
        for (auto stmt : stmts)
            addChildSymbolTable(belong, stmt);
    }
    void addStmts(ASTNode *_Stmts)
    {
        if (!_Stmts)
            return;
        if (_Stmts->get_AST_e() == AST_e::Temp)
        {
            for (ASTNode *n : ((TempNode *)_Stmts)->childList)
                addStmts(n);
        }
        else if (_Stmts->get_AST_e() == AST_e::Stmt)
        {
            stmts.push_back((StmtNode *)_Stmts);
        }
        else
        {
            cout << "语句块内不全是语句\n"
                 << endl;
        }
    }
    void output(std::ostream &os) override
    {
        for (auto stmt : stmts)
            stmt->output(os);
    }
    void print(int depth) override;
};

struct FuncDecStmt : public ScopeStmtNode
{
    // 函数声明语句
    TypeNode *re;                                      //返回值类型
    IDNode *name = nullptr;                            //函数名
    std::vector<std::pair<TypeNode *, IDNode *>> args; // 参数列表
    FuncTypeNode *funType = nullptr;
    stmt_e get_stmt_e() override { return stmt_e::FunDec; }
    ~FuncDecStmt() = default;
    FuncDecStmt(TypeNode *_Re, ASTNode *_NameAndArgs) : re(_Re)
    {
        addNameAndArgs(_NameAndArgs);
        std::vector<TypeNode *> argTypes;
        for (auto &arg : args)
        {
            argTypes.push_back(arg.first);
        }
        funType = new FuncTypeNode(re, std::move(argTypes));
        name->setType(IDType_e::FuncDec, funType);
        memberTokenCount = _NameAndArgs->tokenCount + 1;
    }
    virtual void addChild() override
    {
        // 添加子作用域
    }
    void addNameAndArgs(ASTNode *n)
    {
        if (!n)
        {
            if (!name)
                cout << "函数声明内无函数名" << endl;
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
                global->registe(name, IDType_e::FuncDec, nullptr);
            }
            else
            {
                if (args.size() == 0)
                {
                    cout << "函数声明参数列表中在ID前无类型\n"
                         << endl;
                    return;
                }
                if (args.back().second != nullptr)
                {
                    cout << "函数声明中参数列表中一个类型类型有多个ID\n"
                         << endl;
                    return;
                }
                if (args.back().second == nullptr)
                {
                    auto id = (IDNode *)n;
                    args.back().second = id;
                    global->registe(id, IDType_e::VarDef, args.back().first);
                }
            }
        }
        else if (n->get_AST_e() == AST_e::Type)
        {
            args.push_back(std::make_pair<TypeNode *, IDNode *>((TypeNode *)n, nullptr));
        }
        else if (n->get_AST_e() == AST_e::Stmt)
        {
            auto stmt = (StmtNode *)n;
            if (stmt->get_stmt_e() == stmt_e::VarDef)
            {
                auto varDef = (VarDefStmt *)stmt;
                for (auto var : varDef->vars)
                {
                    args.push_back(std::make_pair(var.type, var.ID));
                }
            }
        }
        else
        {
            cout << "函数声明参数列表内有除type节点和id节点以外的节点\n"
                 << endl;
            return;
        }
    }
    int memberTokenCount = 0;
    void makeSymbolTable() override
    {
        setSymbolTable(global->makeChild(this, memberTokenCount));
    }
    void print(int depth) override;
};

struct FuncDefStmt : public StmtNode
{
    // 函数定义语句
    FuncDecStmt &funcdec; // 函数声明
    BlockStmt *block;     //函数体
    ~FuncDefStmt() = default;
    stmt_e get_stmt_e() override { return stmt_e::FunDef; }
    FuncDefStmt(StmtNode *_Dec, StmtNode *_Block)
        : funcdec(*(FuncDecStmt *)_Dec)
    {
        if (!_Block)
            cout << "函数体为NULL\n"
                 << endl;
        if (_Block && _Block->get_stmt_e() == stmt_e::Block)
        {
            this->block = (BlockStmt *)_Block;
        }
        else
        {
            cout << "函数体不是一个块语句" << endl;
        }

        funcdec.name->setType(IDType_e::FuncDef, funcdec.funType);
        memberTokenCount = _Block->tokenCount;
        //this->belong;//
    }

    void output(std::ostream &os) override;
    void makeSymbolTable() override
    {
        funcdec.makeSymbolTable();
        for (Identifier *id : funcdec.belong->IDList)
        {
            for (Identifier *id2 : block->belong->IDList)
            {
                if (id->name == id2->name)
                {
                    cout << id->name << " 重定义" << endl;
                    exit(1);
                }
            }
        }
        addChildSymbolTable(funcdec.belong, block);
        funcdec.belong->setIndividual();
    }
    // 经测试，函数定义的参数列表和函数体同一个作用域，不允许重复定义
    int memberTokenCount = 0;

    void print(int depth) override;
};

struct StructDecStmt : StmtNode
{
    // 结构体声明
    StructTypeNode *type;
    stmt_e get_stmt_e() override { return stmt_e::StructDec; }
    StructDecStmt(IDNode *_ID)
    {
        type = StructTypeNode::createNode(_ID, nullptr);
        global->registe(_ID, IDType_e::TypenameDec, type);
    }

    void print(int depth) override;
};

struct StructDefStmt : ScopeStmtNode
{
    // 结构体定义

    stmt_e get_stmt_e() override { return stmt_e::StructDef; }
    IDNode *defID;
    StructTypeNode *type;
    StructDecStmt *dec;
    StructDefStmt(StmtNode *_Dec, ASTNode *_Members, bool empty = false)
        : dec((StructDecStmt *)_Dec)
    {
        if (_Dec->get_stmt_e() != stmt_e::StructDec)
        {
            cout << "结构体定义中，第一个参数不是结构体声明语句" << endl;
            exit(1);
        }
        defID = new IDNode(dec->type->ID->ID.c_str());
        type = StructTypeNode::createNode(defID, _Members);
        if (empty)
            type->setDefined();
        global->registe(defID, IDType_e::TypenameDef, type);
        memberTokenCount = _Members->tokenCount;
    }
    virtual void addChild() override
    {
        // 添加子作用域
    }
    int memberTokenCount = 0;
    void makeSymbolTable() override
    {
        setSymbolTable(global->makeChild(this, memberTokenCount));
        this->belong->setIndividual(0);
        // auto structT = type;
        // for (auto &&member : structT->members)
        // {
        //     // if (member.second->ID == second->ID)
        //
        //
        // }
    }

    void print(int depth) override;
};

struct ReturnStmt : StmtNode
{
    // return 语句
    ExprNode *expr;
    ReturnStmt(ExprNode *_Expr) : expr(_Expr){};
    stmt_e get_stmt_e() override { return stmt_e::Return; }
    void output(std::ostream &os) override;
    void print(int depth) override;
};
