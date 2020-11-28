#pragma once

#include "ASTNode.h"
#include "TypeNode.h"
#include "../symbol/SymbolTable.h"



struct IDNode: public ASTNode {
    // 标识符
    IDType_e id_type = IDType_e::unknow;
    TypeNode *type;
    const char *ID;
    SymbolTable *symboltable;
    ~IDNode()=default;
    IDNode(const char *_ID): ID(_ID) {}  
    IDType_e get_IDType_e() { return id_type; }
};

