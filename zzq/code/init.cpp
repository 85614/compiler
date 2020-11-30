#include "include.h"

ProgramNode ProgramNode::root;

SymbolTable SymbolTable::global{nullptr, &ProgramNode::root};

FileNode thisFile;

extern FileNode thisFile;

VoidTypeNode VoidTypeNode::VOID{"void"};
IntegerTypeNode IntegerTypeNode::INT{"int", 4};
FloatTypeNode FloatTypeNode::FLOAT{"float", 4};

BasicTypeNode *BasicTypeNode::VOID = &VoidTypeNode::VOID;
BasicTypeNode *BasicTypeNode::INT = &IntegerTypeNode::INT;

std::vector<StructTypeNode*> StructTypeNode::structList;


SymbolTable fileGlobal{&SymbolTable::global, &thisFile};


void init() {

     ProgramNode::root.belong = &SymbolTable::global;


     ProgramNode::root.files.push_back(&thisFile);

     SymbolTable::global.belong = &ProgramNode::root;
     SymbolTable::global.parent = nullptr;
}