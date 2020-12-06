// #pragma once
#pragma once
#include <iostream>
#include <vector>
#include "TypeNode.h"
#include "IDNode.h"
#include "TempNode.h"

class TypeNode;

using std::cout;
using std::endl;

struct ExprNode : public ASTNode
{
    // 抽象表达式节点
    
    AST_e get_AST_e() override { return AST_e::Expr; }
    virtual expr_e get_expr_e() = 0;
    virtual TypeNode *getType()  { 
        if (!type) {
            cout << "表达式值的类型未确定, 表达式：" << endl;
            print(0);
            exit(1);
        } 
        return type;
    }
    virtual bool isConstExpr() {
        // 是否是字面值常量
        if (isConst == -1) {
            cout << "是否是字面值常量未确定" <<endl;
            print(0);
            exit(1);
        }
        return isConst;
    } 
    virtual bool isLeftValue() { 
        // 是否是左值（有内存，可以取地址）
        if (isLeft == -1) {
            cout << "是否是字面值常量未确定" <<endl;
            print(0);
            exit(1);
        }
        return isLeft;
    }
    void init(TypeNode* _Type, bool _IsConst, bool _IsLeft) {
        type = _Type;
        isConst = _IsConst;
        isLeft = _IsLeft;
    }
protected:
    TypeNode *type = nullptr; // 表达式的类型
    int isConst = -1;
    int isLeft = -1;
};

struct OP1ExprNode : public ExprNode
{
    // 1目运算表达式节点
    ExprNode *first;
    op_e op;
    
    ~OP1ExprNode()=default;
    expr_e get_expr_e() override { return expr_e::Op1; };
    
    
    OP1ExprNode(op_e _Op, ExprNode *_First): 
        op(_Op), first(_First)
    {
        // this->type =
        init();
    }
    void init();
    void print(int depth) override
    {
        printDepth(depth);
        cout << "Expr op:" << getInfo(this->op) << endl;
        this->first->print(depth + 1);
    }
};

struct OP2ExprNode : public ExprNode
{
    // 2目运算表达式节点
    ExprNode *first, *second;
    op_e op;
    std::string opStr; // 如果是比较运算符，区分 < > <= >=, 其他情况是null
    ~OP2ExprNode()=default;
    expr_e get_expr_e() override { return expr_e::Op2; };
    OP2ExprNode(op_e _Op, const char *_OpStr, ExprNode *_First, ExprNode *_Second )
        :op(_Op), first(_First), second(_Second), opStr(_OpStr)
    {   
        init();
    }
    OP2ExprNode(op_e _Op, ExprNode *_First, ExprNode *_Second )
        :op(_Op), first(_First), second(_Second), opStr("")
    { 
        init();
    }
    void init();
    using ExprNode::init;
    void print(int depth) override
    {
        printDepth(depth);
        cout << "Expr op:" << getInfo(this->op) << endl;
        this->first->print(depth + 1);
        this->second->print(depth + 1);
    }
};

struct MemberExprNode : public ExprNode
{
    // 取成员
    ExprNode *first;
    IDNode *second;
    op_e op;
    std::string opStr; // 如果是比较运算符，区分 < > <= >=, 其他情况是null
    ~MemberExprNode()=default;
    expr_e get_expr_e() override { return expr_e::Op2; };
    MemberExprNode(ExprNode *_First, IDNode *member)
        :first(_First), second(member)
    {
        
        init();
    }
    void init();
    using ExprNode::init;
    void print(int depth) override
    {
        printDepth(depth);
        cout << "Expr op:" << getInfo(this->op) << endl;
        this->first->print(depth + 1);
        this->second->print(depth + 1);
    }
};

struct OP3ExprNode : public ExprNode
{
    // 3目运算表达式节点
    ExprNode *first, *second, *third;
    op_e op;
    ~OP3ExprNode() = default;
    expr_e get_expr_e() override { return expr_e::Op3; };
    OP3ExprNode(op_e _Op, ExprNode *_First, ExprNode *_Second, ExprNode *_Third) : op(_Op), first(_First), second(_Second), third(_Third)
    {
        cout <<" 三目运算符未实现" <<endl;
        exit(1);
    }
    // void print(int depth) override {

    // }
};

struct FunCallExprNode: public ExprNode {
    // 函数调用表达式节点
    IDNode *name;
    ~FunCallExprNode()=default;
    std::vector<ExprNode*> args; //参数
    expr_e get_expr_e() override { return expr_e::FuncCall; };
    FunCallExprNode(IDNode *_Name, ASTNode *_Args): name(_Name) {
        _Name->checkExist(true);
        // this->ret = 
        
        if (MY_DEBUG) cout<<__FILE__<< __LINE__ <<endl;
        addArgs(_Args);
        init();
    }
    using ExprNode::init;
    void init();
    void addArgs(ASTNode *n)
    {
        if (!n)
            return;
        if (n->get_AST_e() == AST_e::Temp)
        {
            for (ASTNode *child : ((TempNode *)n)->childList)
                addArgs(child);
        }
        else if (n->get_AST_e() == AST_e::Expr)
        {
            args.push_back((ExprNode *)n);
        }
        else
        {
            printf("函数调用中的参数不是表达式\n");
            // 报错
        }
    }
    void print(int depth) override
    {
        
        printDepth(depth);
        // USE_DEBUG;
        cout << "Function Call." 
            //<< getInfo(((BasicTypeNode *)this->ret)->get_basic_type_e())
            << endl;
        //USE_DEBUG;
        this->name->print(depth + 1);
        printDepth(depth + 1);
        cout << "Para List" << endl;
        for (int k = 0; k < this->args.size(); k++)
        {
            this->args[k]->print(depth + 2);
        }
    }
};

struct VarExprNode : public ExprNode
{
    // 变量运算表达式节点
    IDNode *id;
    ~VarExprNode() = default;
    expr_e get_expr_e() override { return expr_e::Var; };
    VarExprNode(IDNode *_Id) : id(_Id)
    {
        
        _Id->checkExist(true);
        if (_Id->realID->extra && ((ASTNode*)(_Id->realID->extra))->get_AST_e()==AST_e::Type)
            this->type = (TypeNode*)_Id->realID->extra;
        else
            cout << "变量" <<id->ID <<  "类型不确定" << endl;
        init(id->getType(), false, true);
    }
    void print(int depth) override
    {
        printDepth(depth);
        cout << "Var:" << this->id->ID << endl;
    }
};

struct ConstExprNode : public ExprNode
{
    // 常量表达式
    std::string value;
    ~ConstExprNode() = default;
    ConstExprNode(const char *_Value) : value(_Value)
    {
        init();
    }
    using ExprNode::init;
    void init();
    expr_e get_expr_e() override { return expr_e::Const; };
    int toInt() {
        int num = 0, k = -1;
        while(value[++k]) 
            num = num * 10 + value[k] - '0';
        return num;
    }
    void print(int depth) override
    {
        printDepth(depth);
        cout << "Const Expr. Value:" << value << endl;
    }
};
