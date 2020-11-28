#pragma once
#include <vector>
#include "ASTNode.h"

struct FileNode :public ASTNode{
   static std::vector<FileNode*> FileList;
   ~FileNode()=default;
   AST_e get_AST_e()override{return AST_e::File;}
};

