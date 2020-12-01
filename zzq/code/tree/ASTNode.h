#pragma once
#include <iostream>
#include <stdio.h>
#include "../symbol/SymbolTable.h"
#include "enum.h"
#define MY_DEBUG 1
#define USE_DEBUG { if (MY_DEBUG) cout<<__FILE__<< __LINE__ <<endl;}
using std::cout;
using std::endl;

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };

struct ASTNode
{
    virtual AST_e get_AST_e() = 0;
    virtual void print(int depth) { printf("请实现print，get_AST_e()is%d\n", (int)this->get_AST_e()); }
    virtual ~ASTNode() = default;
    virtual void addChild(ASTNode *child)
    {
        printf("请实现addchild，get_AST_e()is%d\n", (int)this->get_AST_e());
        exit(1);
    }
    virtual void addMsg(const char *msg)
    {
        printf("请实现addMsg，get_AST_e()is%d\n", (int)this->get_AST_e());
        exit(1);
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

static void printDepth(int depth)
{
    for (int k = 0; k < depth; k++)
        cout << "  ";
    cout << "|--";
}