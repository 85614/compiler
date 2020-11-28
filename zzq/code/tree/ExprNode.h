#pragma once
#include <vector>
#include "TypeNode.h"
#include "IDNode.h"
#include "TempNode.h"

enum class op_e{
    Assignop = 1,       // =
    Relop = 2,          // < > <= >=
    Plus = 3,           // +
    Minus = 4,          // -
    Times = 5,          // *
    Div = 6,            // /
    Mod = 7,            // %
    Power = 8,          // ^
    And = 9,            // &&
    Or = 10,            // ||
    Negative = 11,      // -
    Not = 12,           // !
    SingalAnd = 13,     // &
    GetValue = 14,      // *
    GetArrayValue = 15, //a[3]
    GetMember = 16,     // a.b
    AssignArray = 17,   // a[1] = ?
    AssignMember = 18   // a.b = ?
};

enum class expr_e {
    Op1, // 1目运算符
    Op2, // 2目运算符
    Op3, // 3目运算符
    FuncCall, //函数调用
    Var, // 变量
    Const // 常量
};
    
struct ExprNode: public ASTNode{
    // 抽象表达式节点
    TypeNode *type;
    AST_e get_AST_e()override{ return AST_e::Expr; }
    virtual expr_e get_expr_e() = 0;
};

struct OP1ExprNode: public ExprNode {
    // 1目运算表达式节点
    ExprNode *first;
    op_e op;
    expr_e get_expr_e() override { return expr_e::Op1; };
    OP1ExprNode(const char *op, ExprNode *_First) {

    }
    OP1ExprNode(op_e _Op, ExprNode *_First): 
        op(_Op), first(_First)
    {
        // this->type = 
    }
};

struct OP2ExprNode: public ExprNode {
    // 2目运算表达式节点
    ExprNode *first, *second;
    op_e op;
    expr_e get_expr_e() override { return expr_e::Op2; };
    OP2ExprNode(op_e _Op, ExprNode *_First,  ExprNode *_Second): 
        op(_Op), first(_First), second(_Second) 
    { 
        // this->type = 
    }

};

struct OP3ExprNode: public ExprNode {
    // 3目运算表达式节点
    ExprNode *first, *second, *third;
    op_e op;
    expr_e get_expr_e() override { return expr_e::Op3; };
    OP3ExprNode(op_e _Op, ExprNode *_First,  ExprNode *_Second,  ExprNode *_Third): 
        op(_Op), first(_First), second(_Second), third(_Third) 
    {
        // this->type = 
    }
};

struct FuncCallExprNode: public ExprNode {
    // 函数调用表达式节点
    TypeNode *ret; //返回值类型
    IDNode *name;
    std::vector<ExprNode*> args; //参数
    expr_e get_expr_e() override { return expr_e::FuncCall; };
    FuncCallExprNode( IDNode *_Name, TempNode *_Args): name(_Name) {
        // this->ret = 
        // this->type = 
        addArgs(_Args);
        
    }
    
    void addArgs(TempNode *n) {
        if(!n)
            return;
        for (ASTNode *child: n->child_list) {
            if(child->get_AST_e()==AST_e::Temp) {
                return addArgs((TempNode *)child);
            }
            else if(child->get_AST_e()==AST_e::Expr){
               args.push_back((ExprNode*)child);
            }
            else {
              // 报错
            }

        }
    }
};

struct VarExprNode: public ExprNode {
    // 变量运算表达式节点
    IDNode *id;
    expr_e get_expr_e() override { return expr_e::Var; };
};

struct ConstExprNode: public ExprNode {
    // 1目运算表达式节点
    const char *value;
    expr_e get_expr_e() override { return expr_e::Const; };
};
