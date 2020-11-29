#pragma once
#include <stdio.h>
#include "enum.h"

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };



struct ASTNode{
    virtual AST_e get_AST_e() = 0;
    virtual ~ASTNode(){
        printf("请实现析构函数");
    }
    virtual void addChild(ASTNode *child) {
        printf("请实现addchild，get_AST_e()is%d",(int)this->get_AST_e());
    }
    virtual void addMsg(const char *msg) {
        printf("请实现addMsg，get_AST_e()is%d",(int)this->get_AST_e());
    }
};

