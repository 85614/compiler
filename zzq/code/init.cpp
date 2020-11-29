#include "include.h"

ProgramNode ProgramNode::root;

SymbolTable SymbolTable::global;

FileNode thisFile;

extern FileNode thisFile;

VoidTypeNode VoidTypeNode::VOID{"void"};
IntegerTypeNode IntegerTypeNode::INT{"int", 4};
FloatTypeNode FloatTypeNode::FLOAT{"float", 4};

BasicTypeNode *BasicTypeNode::VOID = &VoidTypeNode::VOID;
BasicTypeNode *BasicTypeNode::INT = &IntegerTypeNode::INT;

std::vector<StructTypeNode*> StructTypeNode::structList;

void init() {
     ProgramNode::root.files.push_back(&thisFile);

     
     SymbolTable::global.belong = &ProgramNode::root;
     SymbolTable::global.parent = nullptr;
}