#pragma once
#include <stdio.h>
#include "enum.h"

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };

struct ASTNode
{
    virtual AST_e get_AST_e() = 0;
    virtual void print(int depth) { printf("请实现print\n"); }
    virtual ~ASTNode()
    {
        printf("请实现析构函数");
    }
    virtual void addChild(ASTNode *child)
    {
        printf("请实现addchild，get_AST_e()is%d", (int)this->get_AST_e());
    }
    virtual void addMsg(const char *msg)
    {
        printf("请实现addMsg，get_AST_e()is%d", (int)this->get_AST_e());
    }
};

struct ScopeNode: ASTNode {
    SymbolTable *belong = nullptr;
    void setSymbolTable(SymbolTable *_Parent) {
        if (belong)
            belong->parent = belong;
        else 
            belong = _Parent;
    }
};

void printDepth(int depth)
{
    for (int k = 0; k < depth; k++)
        cout << " ";
    cout << "|--";
}