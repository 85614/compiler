#pragma once
#include <vector>
#include "ASTNode.h"
#include "TempNode.h"
// struct StmtNode;
extern SymbolTable staticGlobal;
struct FileNode :public ASTNode {
   SymbolTable *belong = nullptr;
   std::vector<ASTNode*> stmts;
   ~FileNode()=default;
   // void addChild(ASTNode* child)override { stmts.push_back(child); }
   AST_e get_AST_e()override{return AST_e::File;}
   void print(int depth) override{
        for(ASTNode *n: stmts)
            n->print(0);
   }
   void addChild(ASTNode *children)override {
      if (!children)
         return;
      if (children->get_AST_e() == AST_e::Stmt) {
         stmts.push_back(children);
      } else if (children->get_AST_e() == AST_e::Temp) {
         for (ASTNode*n: ((TempNode*)children)->childList)
            addChild(n);
      } else {
         printf("将非语句节点 %d 加入到 file 节点 \n", (int)children->get_AST_e());
      }
   }
   FileNode(){
      this->belong = &staticGlobal;
   }
};

