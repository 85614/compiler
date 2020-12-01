#pragma once
#include <iostream>
#include <stdio.h>
#include "../symbol/SymbolTable.h"
#include "enum.h"
#define MY_DEBUG 1
#define USE_DEBUG { if (MY_DEBUG) cout<<__FILE__<< __LINE__ <<endl;}
using std::cout;
using std::endl;

struct TokenNode{
    const char *str;
    int tokenCount;
};

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };

struct ASTNode
{
    virtual AST_e get_AST_e() = 0;
    int tokenCount = 0; //第一个词法单元的序号
    virtual void print(int depth) { printf("请实现print，get_AST_e()is\n") ; cout << (int)this->get_AST_e(); }
    void printt(int depth) {printf("请实现print，get_AST_e()is\n") ; cout << (int)this->get_AST_e();}
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
    bool setTokenCount(const TokenNode&tn){
        this->tokenCount = tn.tokenCount;
        return true;
    
    }
    bool setTokenCount(ASTNode *n) {
      
        if(!n)
            {cout << "$1为空。"  << endl;  exit(1);return false; print(0); exit(1); }
        else if (n->tokenCount == 0) 
            {cout << "tokenCount 为0！！" << endl; /*printt(1);*/  exit(1);return false;}
        else 
            {this->tokenCount = n->tokenCount;return true;}
  
       
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