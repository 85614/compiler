#pragma once
#include <vector>
#include "ASTNode.h"
struct FileNode;
struct ProgramNode:public ASTNode {
    static ProgramNode root;
    std::vector<FileNode*> files;
    AST_e get_AST_e()override{return AST_e::Program;}
private:
    ProgramNode() = default;
    ProgramNode(const ProgramNode&) = delete;
};






