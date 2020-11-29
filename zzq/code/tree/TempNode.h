#pragma once
#include <vector>
#include "ASTNode.h"

struct TempNode : ASTNode{
    std::vector<ASTNode *> childList;
    const char *msg = nullptr;
    virtual AST_e get_AST_e() override {return AST_e::Temp;}
    void addChild(ASTNode *child)override { childList.push_back(child); }
    virtual void addMsg(const char *_Msg) {
        msg = _Msg;
    }
    ~TempNode()=default;
    void getAllLeaf(std::vector<ASTNode *> &leafs){
        for(ASTNode*n: childList) {
            if (n->get_AST_e()==AST_e::Temp)
                getAllLeaf(leafs);
            else 
                leafs.push_back(n);
        }   
    }
};

static void freeTemp(TempNode*n){
    if(n) {
        for (ASTNode*child: n->childList){
            if(child->get_AST_e()==AST_e::Temp) 
                freeTemp((TempNode*)child);
        }
        delete n;
    }
}