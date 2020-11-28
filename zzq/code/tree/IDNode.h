#pragma once

#include "ASTNode.h"
#include "TypeNode.h"
#include "../symbol/SymbolTable.h"



struct IDNode: public ASTNode{
    
    const char *ID;
    SymbolTable *symboltable;
};

struct VarIDNode: IDNode {
    // 变量名标识符
    TypeNode *type;
};

struct FuncIDNode: IDNode {
    TypeNode *type;
    // 函数名标识符
};

