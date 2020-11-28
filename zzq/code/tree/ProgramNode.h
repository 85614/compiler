#pragma once

#include "ASTNode.h"

struct ProgramNode{
    static ProgramNode root;
private:
    ProgramNode() = default;
    ~ProgramNode() = default;
};

ProgramNode ProgramNode::root;

ProgramNode &root = ProgramNode::root;