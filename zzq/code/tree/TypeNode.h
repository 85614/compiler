#pragma once
#include <vector>
#include "ASTNode.h"



struct TypeNode: public ASTNode{
    AST_e get_AST_e()override {return AST_e::Type;}
    virtual type_e get_type_e() = 0;
};

struct BasicTypeNode: public TypeNode {
    // 基础类型， 请使用静态对象
    static const BasicTypeNode VOID, INT;
    
    const char *name = nullptr;

    BasicTypeNode(const char *_Name): name(_Name){}
    virtual type_e get_type_e() override {return type_e::BasicType;};
};

const BasicTypeNode BasicTypeNode::INT{"int"};
const BasicTypeNode BasicTypeNode::VOID{"void"};

struct FuncTypeNode : public TypeNode {
    // 函数类型，函数名标识符的类型
    // 如 int fun(int);  fun的类型就是int(int)
    virtual type_e get_type_e() override {return type_e::FuncType;};
    TypeNode *re; //返回值类型
    std::vector<TypeNode *> args; // 参数类型
};

