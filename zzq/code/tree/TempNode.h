#pragma once
#include <vector>
#include "ASTNode.h"

struct TempNode{
    std::vector<ASTNode *> child_list;
    virtual AST_e get_AST_e() {return AST_e::Temp;}
};
