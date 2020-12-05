#pragma once
#include <vector>
#include <string>
#include "ASTNode.h"

struct TempNode : ASTNode{
    std::vector<ASTNode *> childList;
    std::string msg = "";
    virtual AST_e get_AST_e() override {return AST_e::Temp;}
    void addChild(ASTNode *child)override { if(child) childList.push_back(child); }
    virtual void addMsg(std::string &&_Msg) {
        msg += _Msg;
        
    }
    ~TempNode()=default;
    void getAllLeaf(std::vector<ASTNode *> &leafs){
        for(ASTNode*n: childList) {
            if (n->get_AST_e()==AST_e::Temp)
                ((TempNode*)n)->getAllLeaf(leafs);
            else 
                leafs.push_back(n);
        }   
    }
    void print(int depth)override{
        for (ASTNode *n: childList)
            n->print(depth);
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