#include "include.h"

// 程序根节点
ProgramNode ProgramNode::root;
// 文件节点
FileNode thisFile;

// 全局作用域符号表
SymbolTable global{&ProgramNode::root, nullptr};
// staic文件全局作用域 static 大概用不到吧
SymbolTable staticGlobal{&thisFile, &global};


extern FileNode thisFile;

VoidTypeNode VoidTypeNode::VOID{"void"};
IntegerTypeNode IntegerTypeNode::INT{"int", 4};
FloatTypeNode FloatTypeNode::FLOAT{"float", 4};



BasicTypeNode *BasicTypeNode::VOID = &VoidTypeNode::VOID;
BasicTypeNode *BasicTypeNode::INT = &IntegerTypeNode::INT;

BasicTypeNode *BasicTypeNode::typeList[2]{ BasicTypeNode::VOID, BasicTypeNode::INT};



void init() {

     // ProgramNode::root.belong = &global;
     global.registe(new IDNode("print_int"), IDType_e::FuncDec, 
     new FuncTypeNode(BasicTypeNode::VOID, std::vector<TypeNode*>{BasicTypeNode::INT}));
     ProgramNode::root.files.push_back(&thisFile);

     global.belong = &ProgramNode::root;
     // global.parent = nullptr;
}