#pragma once
#include <vector>
#include "ASTNode.h"

struct TempNode{
    std::vector<ASTNode *> childList;
    virtual AST_e get_AST_e() {return AST_e::Temp;}
    void addChild(ASTNode *child) { childList.push_back(child); }
    ~TempNode()=default;
};

void freeTemp(TempNode*n){
    if(n) {
        for (ASTNode*child: n->childList){
            if(child->get_AST_e()==AST_e::Temp) 
                freeTemp((TempNode*)child);
        }
        delete n;
    }

}