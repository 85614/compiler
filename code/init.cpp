#include "include.h"
#include <fstream>
// 程序根节点
ProgramNode ProgramNode::root;
// 文件节点
FileNode thisFile;

// 全局作用域符号表
SymbolTable *global = new SymbolTable{&ProgramNode::root, nullptr};
// staic文件全局作用域 static 大概用不到吧
SymbolTable staticGlobal{&thisFile, global};

extern FileNode thisFile;

VoidTypeNode VoidTypeNode::VOID{"void"};
IntegerTypeNode IntegerTypeNode::INT{"int", 4};

BasicTypeNode *BasicTypeNode::VOID = &VoidTypeNode::VOID;
BasicTypeNode *BasicTypeNode::INT = &IntegerTypeNode::INT;

BasicTypeNode *BasicTypeNode::typeList[2]{BasicTypeNode::VOID, BasicTypeNode::INT};

int stack_esp = 0;

void init()
{

    // ProgramNode::root.belong = &global;
    global->registe(new IDNode("print_int"), IDType_e::FuncDec,
                    new FuncTypeNode(BasicTypeNode::VOID, std::vector<TypeNode *>{BasicTypeNode::INT}));
    ProgramNode::root.files.push_back(&thisFile);

    global->belong = &ProgramNode::root;
    // global->parent = nullptr;
}

std::ofstream os("code.asm");
std::ostream &theOs = os;

void initGlobalVar(std::ostream &os)
{
    for (auto &stmt : thisFile.stmts)
    {
        if (stmt->get_AST_e() == AST_e::Stmt && ((StmtNode *)stmt)->get_stmt_e() == stmt_e::VarDef)
            stmt->output(os);
    }
}

void output()
{

    os << R"(
extern printf
global main

print_int:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 0x8]
    push 0x0a6425
    mov ebx, esp
    push eax
    push ebx
    call printf 
    mov esp, ebp
    pop ebp
    ret

)";
    for (auto &stmt : thisFile.stmts)
    {
        

        if (stmt->get_AST_e() == AST_e::Stmt && ((StmtNode *)stmt)->get_stmt_e() == stmt_e::VarDef)
            continue;
        stmt->output(os);
    }

    os << "section .data\n";
    for (auto id : global->IDList)
    {
        if (id->IdType == IDType_e::VarDef)
        {
            
            os << "    "<<id->name << " dd ";
            
            for (int i = 0; i < id->extra->size; i += 4)
            {
                if (i != 0)
                    os << ", ";
                os << "0";
            }
            os << "\n";
        }
    }
    os << "\n";
}