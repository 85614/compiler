#pragma once
#include "../symbol/SymbolTable.h"
#include "ASTNode.h"



// 存储变量类型否？

struct IDNode: public ASTNode {
    // 标识符
    // IDType_e id_type = IDType_e::unknow; //ID类型 类型名、变量名、函数名等
    // TypeNode *type = nullptr; // 变量或函数的类型
    // SymbolTable *symboltable = nullptr; // 所属的符号表（作用域）

    const char *name; // 标识符
    Identifier *id = nullptr;
    ~IDNode()=default;
    IDNode(const char *_ID): ID(_ID) {
        // this->id_type
        // this->type = 
        // this->symboltable = 
    }  

};

