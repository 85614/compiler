#pragma once
#include <vector>
#include "ASTNode.h"



struct TypeNode: public ASTNode{
    AST_e get_AST_e()override {return AST_e::Type;}
    virtual type_e get_type_e() = 0;
};

struct VoidTyoeNode: public TypeNode {
    virtual type_e get_type_e() override {return type_e::VOIDType;};
};

struct BasicTypeNode: public TypeNode {
    const char *name = nullptr;
    static const BasicTypeNode INT;
    BasicTypeNode(const char *_Name): name(_Name){}
    virtual type_e get_type_e() override {return type_e::BasicType;};
};

const BasicTypeNode BasicTypeNode::INT{"int"};

struct FuncTypeNode : public TypeNode {
    virtual type_e get_type_e() override {return type_e::FuncType;};
    TypeNode *re; //返回值类型
    std::vector<TypeNode *> args; // 参数类型
};
