#pragma once
#include "ASTNode.h"

enum class stmt_t{
      IF, // if 语句
      FuncDef, // 函数定义
      FunDec, // 函数声明
      VarDef, // 变量声明
      FOR, // for 语句
      Block, // 语句块
      Expr // 表达式语句
    };
struct StmtNode: public ASTNode{
    AST_e get_AST_e()override {return AST_e::Stmt; }
    virtual stmt_t get_stmt_e() = 0;
};

struct ExprNode;

struct ExprStmtNode: public StmtNode{
    ExprNode *expr;
    stmt_t get_stmt_e() override {return stmt_t::Expr; };
};

struct IFStmt: public StmtNode {
    ExprNode *test; //判断条件
    StmtNode *trueRun; //为真时运行
    StmtNode *falseRun; //为假时运行
    stmt_t get_stmt_e() override {return stmt_t::IF; };
};

struct VarDefStmt: public StmtNode {
    
    stmt_t get_stmt_e() override {return stmt_t::VarDef; };
};

struct ForStmt: public StmtNode {
    VarDefStmt *init; //初始化
    ExprNode *test; // 判断循环调控
    ExprNode *other; // 第三个表达式
    StmtNode *run; //执行的语句块
    stmt_t get_stmt_e() override {return stmt_t::FOR; };
};

struct BlockStmt: public StmtNode {
    // 语句块
    std::vector<StmtNode*> stmts;

};
 

struct FuncDefStmt: public StmtNode {
    // 函数定义语句
    TypeNode *re; //返回值类型
    IDNode *name; //函数名
    std::vector<std::pair<TypeNode*, IDNode*>> args; // 参数列表
    BlockStmt *block; //函数体
};