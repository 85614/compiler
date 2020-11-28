#pragma once

#include "enum.h"

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };



struct ASTNode{
    virtual AST_e get_AST_e() = 0;
    virtual ~ASTNode(){
        printf("请实现析构函数，get_AST_e()is%d",(int)get_AST_e());
    }
    virtual void add_child(ASTNode *child) {
        fprintf(stderr, "");
        exit(1);
    }
};

