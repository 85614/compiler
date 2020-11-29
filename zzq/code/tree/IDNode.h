#pragma once

#include "ASTNode.h"
#include "TypeNode.h"
#include "../symbol/SymbolTable.h"



struct IDNode: public ASTNode {
    // 标识符
    IDType_e id_type = IDType_e::unknow; //ID类型 类型名、变量名、函数名等
    TypeNode *type = nullptr; // 变量或函数的类型
    const char *ID; // 标识符
    SymbolTable *symboltable = nullptr; // 所属的符号表（作用域）
    ~IDNode()=default;
    IDNode(const char *_ID): ID(_ID) {
        // this->id_type
        // this->type = 
        // this->symboltable = 
    }  
    IDType_e get_IDType_e() { return id_type;  }
};

