#pragma once
#include <vector>
#include "ASTNode.h"

// struct StmtNode;
extern SymbolTable fileGlobal;
struct FileNode :public ScopeNode{
   ASTNode *root;
   // std::vector<ASTNode*> stmts;
   ~FileNode()=default;
   // void addChild(ASTNode* child)override { stmts.push_back(child); }
   AST_e get_AST_e()override{return AST_e::File;}
   void print(int depth) override{
         cout << "|--FILE :" << endl;
         root->print(1);
   }
   FileNode(){
      this->belong = &fileGlobal;
   }
   void print_tree() {
       
   }
};

