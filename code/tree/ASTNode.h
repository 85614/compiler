#pragma once
#include <iostream>
#include <stdio.h>
#include "../symbol/SymbolTable.h"
#include "enum.h"
#include "../base.h"
#define MY_DEBUG 0
#define USE_DEBUG                                 \
    {                                             \
        if (MY_DEBUG)                             \
            cout << __FILE__ << __LINE__ << endl; \
    }
using std::cout;
using std::endl;

struct TokenNode
{
    const char *str;
    int tokenCount;
};

// 全局作用域符号表
extern SymbolTable *global;
// 文件全局作用域 static 大概用不到吧
extern SymbolTable staticGlobal;
extern int stack_esp;

struct ASTNode
{

    int tokenCount = 0; //第一个词法单元的序号
    std::string code;
    virtual void output(std::ostream &os) {  }
    virtual void print(int depth)
    {
        printf("请实现print，get_AST_e()is\n");
        cout << (int)this->get_AST_e();
        exit(1);
    }
    virtual void simplePrint(int depth) { this->print(depth); }
    virtual ~ASTNode() = default;
    virtual AST_e get_AST_e() = 0;
    virtual void addChild(ASTNode *child)
    {
        printf("请实现addchild，get_AST_e()is%d\n", (int)this->get_AST_e());
        exit(1);
    }
    virtual void addMsg(std::string &&)
    {
        printf("请实现addMsg，get_AST_e()is%d\n", (int)this->get_AST_e());
        exit(1);
    }
    void setTokenCount(const TokenNode &tn, bool make = true)
    {
        this->tokenCount = tn.tokenCount;
        if (make)
            makeSymbolTable();
    }
    void error()
    {
        print(0);
        exit(1);
    }
    virtual void makeSymbolTable() {} // 可能需要生成新的作用域
    void setTokenCount(ASTNode *n, bool make = true)
    {

        if (!n)
        {
            USE_DEBUG;
            cout << "$1为空。" << (int)this->get_AST_e() << endl;
            exit(1);
        }
        else if (n->tokenCount == 0)
        {
            USE_DEBUG;
            cout << this;
            cout << "tokenCount 为0！！";
            USE_DEBUG;
            cout << this;
            this->get_AST_e();
            USE_DEBUG;
            cout << (int)this->get_AST_e() << endl;
            USE_DEBUG;
            exit(1);
        }
        else
        {
            this->tokenCount = n->tokenCount;
            if (make)
                makeSymbolTable();
        }
    }

public:
};

static void printDepth(int depth)
{
    for (int k = 0; k < depth; k++)
        cout << "  ";
    cout << "|--";
}
