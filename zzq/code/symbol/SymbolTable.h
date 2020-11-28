#pragma once
#include <vector>


struct IDNode;
struct StmtNode;

class SymbolTable{
    SymbolTable *parent; // 父作用域
    StmtNode *belong; // 所属的语句，如果有的话
    std::vector<IDNode*> IDList;// 作用域内可直接访问的符号，包括变量名、函数名等
    // 符号表

};