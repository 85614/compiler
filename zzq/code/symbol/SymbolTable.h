#pragma once
#include <vector>


struct IDNode;
struct ASTNode;

struct SymbolTable{
    static SymbolTable global;
    SymbolTable *parent; // 父作用域
    ASTNode *belong; // 所属的节点，如果有的话
    std::vector<IDNode*> IDList;// 作用域内可直接访问的符号，包括变量名、函数名等
    // 符号表
};