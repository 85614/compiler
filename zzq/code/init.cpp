#include "include.h"

ProgramNode ProgramNode::root;

SymbolTable SymbolTable::global;

FileNode thisFile;


void init() {
     ProgramNode::root.files.push_back(&thisFile);
     SymbolTable::global.belong = &ProgramNode::root;
     SymbolTable::global.parent = nullptr;
}