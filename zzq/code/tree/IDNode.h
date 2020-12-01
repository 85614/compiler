#pragma once
#include "../symbol/SymbolTable.h"
#include "ASTNode.h"


struct StmtNode;

struct IDNode: public ASTNode {
    // 标识符
    // IDType_e id_type = IDType_e::unknow; //ID类型 类型名、变量名、函数名等
    // TypeNode *type = nullptr; // 变量或函数的类型
    // SymbolTable *symboltable = nullptr; // 所属的符号表（作用域）

    const char *ID; // 标识符
    StmtNode* belong = nullptr;
    ~IDNode()=default;

    AST_e get_AST_e()override{ return AST_e::ID; }
    IDNode(const char *_ID): ID(_ID) {
        // this->id_type
        // this->type = 
        // this->symboltable = 
    }  

};

