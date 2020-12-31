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


std::ostream &theOs = cout;

void addGlobalChildren()
{
    for (auto &stmt : thisFile.stmts)
        if (stmt->get_AST_e() == AST_e::Stmt)
            addChildSymbolTable(global, (StmtNode *)stmt);
}

void initGlobalVar(std::ostream &os)
{
    for (auto &stmt : thisFile.stmts)
    {
        if (stmt->get_AST_e() == AST_e::Stmt && ((StmtNode *)stmt)->get_stmt_e() == stmt_e::VarDef)
            stmt->output(os);
    }
}

extern const char *grammar_output; // 语法分析输出文件
extern const char *asm_output;     // asm输出文件

void output_grammar()
{
    auto grammar_os = std::ofstream(grammar_output);
    if (!grammar_os)
        cout << "语法分析输出文件：" << grammar_output << " 打开失败" << endl;
    auto cout_rdbuf = cout.rdbuf(grammar_os.rdbuf());
    thisFile.print(0);
    cout.rdbuf(cout_rdbuf);
    grammar_os.close();
}

void output_asm()
{
    auto asm_os = std::ofstream(asm_output);
    if (!asm_os)
        cout << "asm输出文件：" << asm_output << " 打开失败" << endl;
    auto cout_rdbuf = cout.rdbuf(asm_os.rdbuf());
    cout << R"(
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
        stmt->output(cout);
    }

    cout << "section .data\n";
    for (auto id : global->IDList)
    {
        if (id->IdType == IDType_e::VarDef)
        {

            cout << "    " << id->name << " dd ";

            for (int i = 0; i < id->extra->size; i += 4)
            {
                if (i != 0)
                    cout << ", ";
                cout << "0";
            }
            cout << "\n";
        }
    }
    cout << "\n";
    cout.rdbuf(cout_rdbuf);
    asm_os.close();
}