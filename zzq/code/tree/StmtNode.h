#pragma once
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
    TypeNode *type = nullptr;
    std::vector<std::pair<IDNode*,ExprNode*>> ids;
    stmt_e get_stmt_e() override {return stmt_e::VarDef; };
    ~VarDefStmt()=default;
    VarDefStmt(TypeNode *_Type, TempNode*_Ids) {

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
    ForStmt(StmtNode *_Init, ExprNode *_Test, ExprNode *_Other, StmtNode *_Run){

    }
};

struct BlockStmt: public StmtNode {
    // 语句块
    std::vector<StmtNode*> stmts;
    ~BlockStmt()=default;
    BlockStmt(TempNode *_Stmts) {
        for(ASTNode*n: _Stmts->childList){
            if (n->get_AST_e()!=AST_e::Expr){
                // 报错
            }
            stmts.push_back((StmtNode*)n);
        }   
    }
    
};
 
struct FuncDecStmt: public StmtNode {
    // 函数定义语句
    TypeNode *re; //返回值类型
    IDNode *name; //函数名
    std::vector<std::pair<TypeNode*, IDNode*>> args; // 参数列表
    stmt_e get_stmt_e()override{ return stmt_e::FunDec; }
    ~FuncDecStmt()=default;
    FuncDecStmt(TypeNode *_Re, TempNode *_NameAndArgs){
    }
};

struct FuncDefStmt: public StmtNode {
    // 函数定义语句
    TypeNode *re; //返回值类型
    IDNode *name; //函数名
    std::vector<std::pair<TypeNode*, IDNode*>> args; // 参数列表
    BlockStmt *block; //函数体
    ~FuncDefStmt()=default;
    stmt_e get_stmt_e()override{ return stmt_e::FunDef; }
    FuncDefStmt(TypeNode *_Re, TempNode *_NameAndArgs, StmtNode *_Block){
        if (_NameAndArgs->childList.size() > 0 
            && _NameAndArgs->childList[0]->get_AST_e() == AST_e::ID) {
            IDNode* id = (IDNode*)_NameAndArgs->childList[0];
            // id->type = 

        }
        if(block->get_stmt_e()==stmt_e::Block) {
            
        }
    }
};


