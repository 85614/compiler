#pragma once
#include <vector>
#include "Identifier.h"

struct ASTNode;

struct SymbolTable{
    static SymbolTable global;
    SymbolTable *parent; // 父作用域
    ASTNode *belong; // 所属的节点，如果有的话
    std::vector<Identifier*> IDList;// 作用域内可直接访问的符号，包括变量名、函数名等
    SymbolTable(SymbolTable *_Parent, ASTNode *_Belong)
        :parent(_Parent), belong(_Belong)
    {

    }
    // 符号表
};