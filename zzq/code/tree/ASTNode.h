#pragma once

#include "enum.h"

// template<AST_e e> struct __AST_getter{ static_assert(false, "未实现的类型"); };



struct ASTNode{
    virtual AST_e get_AST_e() = 0;
    virtual void add_child(ASTNode *child) {
        fprintf(stderr, "");
        exit(1);
    }
};

