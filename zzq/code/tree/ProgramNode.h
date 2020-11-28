#pragma once
#include "ASTNode.h"

struct ProgramNode :public ASTNode{
    static ProgramNode root;
    AST_e get_AST_e()override{return AST_e::Program;}
private:
    ProgramNode() = default;
    ~ProgramNode() = default;
};

ProgramNode ProgramNode::root;

ProgramNode &root = ProgramNode::root;