#pragma once
#include <tuple>
#include "ASTNode.h"
#include "TypeNode.h"
#include "IDNode.h"
#include "TempNode.h"

struct StmtNode: public ASTNode{
    AST_e get_AST_e()override {return AST_e::Stmt; }
    virtual stmt_e get_stmt_e() = 0;
};

struct ExprNode;

struct ExprStmtNode: public StmtNode{
    // 表达式语句：表达式+分号
    ExprNode *expr;
    stmt_e get_stmt_e() override {return stmt_e::Expr; };
    ExprStmtNode(ExprNode *_Expr):expr(_Expr){}
    ~ExprStmtNode()=default;
};

struct IFStmt: public StmtNode {
    // if语句
    ExprNode *test; //判断条件
    StmtNode *trueRun; //为真时运行
    StmtNode *falseRun; //为假时运行
    stmt_e get_stmt_e() override {return stmt_e::IF; };
    IFStmt(ExprNode *_Test,ExprNode *_TrueRun,ExprNode *_FalseRun);
    ~IFStmt()=default;
};

struct VarDefStmt: public StmtNode {
    // 变量定义语句
    TypeNode *basicType = nullptr;
    std::vector<std::tuple<TypeNode*, IDNode*, ExprNode*>> ids;
    stmt_e get_stmt_e() override {return stmt_e::VarDef; };
    ~VarDefStmt()=default;
    VarDefStmt(TypeNode *_Type, ASTNode*_Ids) {
        this->basicType = _Type;
        // this->ids = 
    }
};

struct ForStmt: public StmtNode {
    // for 语句
    StmtNode *init; //初始化
    ExprNode *test; // 判断循环调控
    ExprNode *other; // 第三个表达式
    StmtNode *run; //执行的语句块
    stmt_e get_stmt_e() override {return stmt_e::FOR; };
    ~ForStmt()=default;
    ForStmt(StmtNode *_Init, ExprNode *_Test, ExprNode *_Other, StmtNode *_Run)
        :init(_Init), test(_Test), other(_Other), run(_Run)
    {

    }
};

struct BlockStmt: public StmtNode {
    // 语句块
    std::vector<StmtNode*> stmts;
    ~BlockStmt()=default;
    BlockStmt(ASTNode *_Stmts) {
        addStmts(_Stmts);
    }

    void addStmts(ASTNode* _Stmts) {
        if (!_Stmts)
            return;
        if (_Stmts->get_AST_e()==AST_e::Temp) {
            for(ASTNode*n: ((TempNode*)_Stmts)->childList)
                addStmts(_Stmts);
        }
        else if (_Stmts->get_AST_e()==AST_e::Stmt){
            stmts.push_back((StmtNode*)_Stmts);
        }
        else {
            printf("语句块内不全是语句\n");
        }            
        
    }
    
};
 
struct FuncDecStmt: public StmtNode {
    // 函数声明语句
    TypeNode *re; //返回值类型
    IDNode *name = nullptr; //函数名
    std::vector<std::pair<TypeNode*, IDNode*>> args; // 参数列表
    stmt_e get_stmt_e()override{ return stmt_e::FunDec; }
    ~FuncDecStmt()=default;
    FuncDecStmt(TypeNode *_Re, ASTNode *_NameAndArgs):re(_Re){
        addNameAndArgs(_NameAndArgs);
    }
    void addNameAndArgs(ASTNode *n){
        if (!n){
            if (!name)
                printf("函数声明内无函数名");
            return;
        }
        if (n->get_AST_e()==AST_e::Temp) {
            TempNode* temp = (TempNode*)n;
            for (ASTNode *n:temp->childList) 
                addNameAndArgs(n);
        }
        else if (n->get_AST_e()==AST_e::ID){
            if (name == nullptr) {
                name = (IDNode*)n;
            }
            else {
                printf("函数声明的temp节点中，第一个非temp节点不是ID节点\n");
            }
        }else if (n->get_AST_e()==AST_e::Type) {
            args.push_back(std::make_pair<TypeNode*, IDNode*>((TypeNode*)n,nullptr));
        }else if (n->get_AST_e()==AST_e::ID) {
            if (args.size()==0) {
                printf("函数声明参数列表中在ID前无类型\n");
                return;
            }
            if (args.back().second != nullptr) {
                printf("函数声明中参数列表中一个类型类型有多个ID\n");
                return;
            }
            if (args.back().second == nullptr){
                args.back().second = (IDNode*)n;
            }
        }
        else {
            printf("函数声明参数列表内有除type节点和id节点以外的节点\n");
            return ;
        }
        
    }
};

struct FuncDefStmt: public StmtNode {
    // 函数定义语句
    FuncDecStmt funcdec; // 函数声明
    BlockStmt *block; //函数体
    ~FuncDefStmt()=default;
    stmt_e get_stmt_e()override{ return stmt_e::FunDef; }
    FuncDefStmt(TypeNode *_Re, ASTNode *_NameAndArgs, StmtNode *_Block) 
        :funcdec(_Re, _NameAndArgs) 
    {
        if(_Block->get_stmt_e()==stmt_e::Block){
            this->block = (BlockStmt*)_Block;
        }
        else {
            printf("函数体不是一个块语句");
        }
    }
};



struct StructDecStmt: StmtNode {
    // 结构体声明
    StructTypeNode *type;
    stmt_e get_stmt_e()override{ return stmt_e::StructDec; }
    StructDecStmt(IDNode*_ID){
        type = StructTypeNode::getStructType(_ID->ID);
    }
};


struct StructDefStmt: StmtNode {
    // 结构体定义
    StructTypeNode *type;
    stmt_e get_stmt_e()override{ return stmt_e::StructDef; }
    StructDefStmt(IDNode *_ID, ASTNode *_Members){
        type = StructTypeNode::getStructType(_ID->ID);
        type->addMembers(_Members);
    }
};

