#pragma once
#include <vector>
#include "ASTNode.h"

// struct StmtNode;

struct FileNode :public ASTNode{
   ASTNode *root;
   // std::vector<ASTNode*> stmts;
   ~FileNode()=default;
   // void addChild(ASTNode* child)override { stmts.push_back(child); }
   AST_e get_AST_e()override{return AST_e::File;}
   void print(int depth) override{
        
    }
};

