#include <math.h>
#include <string>
#include "StmtNode.h"
#include "TypeNode.h"
#include "ExprNode.h"

void VarDefStmt::addVars(ASTNode *_Vars)
{

    if (!_Vars)
        return;
    if (_Vars->get_AST_e() == AST_e::ID)
    {
        this->addVar(this->basicType, (IDNode *)_Vars, nullptr);
        if (MY_DEBUG)
            cout << __FILE__ << __LINE__ << endl;
    }
    else if (_Vars->get_AST_e() == AST_e::Temp)
    {

        TempNode *temp = (TempNode *)_Vars;

        // DEBUG2(temp);
        // DEBUG2(temp->msg);
        // for (auto child : temp->childList)
        //     if (child->get_AST_e() == AST_e::Temp)
        //     {
        //         DEBUG2(child);
        //         DEBUG2(((TempNode *)child)->msg);
        //     }

        if (temp->msg.empty())
        {
            // 没有消息，此temp节点是一个变量列表
            for (ASTNode *n : temp->childList)
                addVars(n);
        }
        else if (temp->msg == "=")
        {
            // temp = left + init
            // 带初始化

            if (temp->childList.size() != 2)
            {
                printf("带初始化的变量声明，变量名+初始化值数量不为2");
                exit(1);
            }
            addVars(temp->childList[0]);
            if (temp->childList[1]->get_AST_e() == AST_e::Expr)
                vars.back().init = (ExprNode *)(temp->childList[1]);
            else
                cout << "初始化值不是表达式" << endl;
        }
        else
        {
            if (temp->childList.empty())
            {
                cout << "变量声明语句中有空temp结点" << endl;
                exit(1);
            }
            // for(auto child: temp->childList)
            //     child->print(0);
            // if (temp->childList.size() != 1)
            //     my_error("预期外的多个节点");
            addVars(temp->childList[0]);
            
            if (vars.back().init)
            {
                cout << "变量声明类型声明好前已经有初始化值" << endl;
                exit(1);
            }

            if (vars.empty())
            {
                cout << "变量声明没有id" << endl;
                exit(1);
            }
            auto oldType = vars.back().type;
            if (temp->msg == "[]")
            {
                // temp =  (ID + []) + [] .....
                //
                // 声明数组

                if (temp->childList.size() != 2)
                {
                    cout << "[] temp 结点子节点不是两个 " << endl;
                    exit(1);
                }
                if (temp->childList[1]->get_AST_e() != AST_e::Expr)
                {
                    cout << "数组[]中的不是表达式" << endl;
                    exit(1);
                }
                vars.back().type = new ArrayTypeNode(oldType, (ExprNode *)temp->childList[1]);
                vars.back().ID->setType(IDType_e::VarDef, vars.back().type);
            }
            else if ((temp->msg)[0] == '*')
            {

                // temp = ***... + ID
                // 声明指针
                if (temp->childList.size()!=1)
                    my_error("*temp节点的子节点不是1个");
                auto type = oldType;
                for (int i = 0; i < temp->msg.size(); ++i)
                {
                    type = new PointerTypeNode(type, 1);
                }
                vars.back().type = type;
                vars.back().ID->setType(IDType_e::VarDef, vars.back().type);
            }
            else
            {
                printf("变量定义出现未识别的结点类型\n");
            }
        }
    }
    else
    {
        cout << "变量声明语句中出现不应出现的结点类型" << endl;
    }
}

void ExprStmtNode::print(int depth)
{
    printDepth(depth);
    cout << "Expr Stmt. " << endl;
    if (expr)
        this->expr->print(depth + 1);
    else
        printf("打印时表达式语句的表达式为NULL\n");
}

void IFStmt::print(int depth)
{
    printDepth(depth);
    cout << "IF Stmt." << endl;
    printDepth(depth + 1);
    cout << "Judge conditions." << endl;
    this->test->print(depth + 2);
    printDepth(depth + 1);
    cout << "Run if true." << endl;
    this->trueRun->print(depth + 2);
    if (falseRun)
    {
        // printDepth(depth);
        // cout << "ELSE Stmt." << endl;
        printDepth(depth + 1);
        cout << "Run if false." << endl;
        this->falseRun->print(depth + 2);
    }
}

void VarDef::print(int depth)
{
    if (this->init)
    {
        printDepth(depth);
        cout << "Var def." << endl;
        this->type->simplePrint(depth + 1);
        this->ID->print(depth + 1);
        printDepth(depth + 1);
        cout << "Var Init." << endl;
        this->init->print(depth + 2);
    }
    else
    {
        printDepth(depth);
        cout << "Var Dec." << endl;
        this->type->simplePrint(depth + 1);
        this->ID->print(depth + 1);
    }
    if (MY_DEBUG)
        cout << __FILE__ << __LINE__ << endl;

    // if (!this->init) // 为什么你又搞出这样的来了！！
}

void VarDefStmt::print(int depth)
{
    bool flag = 0; // 有def就是1
    for (int k = 0; k < (this->vars).size(); k++)
    {
        if (MY_DEBUG)
            cout << __FILE__ << __LINE__ << endl;
        if ((this->vars[k]).init)
            flag = 1;
    }
    printDepth(depth);
    if (!flag)
        cout << "Var Dec Stmt." << endl;
    else
        cout << "Var Def Stmt." << endl;
    //this->basicType->print(depth + 1);

    if ((this->vars).size() > 1)
    {
        printDepth(depth + 1);
        if (!flag)
            cout << "Var Dec List." << endl;
        else
            cout << "Var Def List." << endl;
        for (int k = 0; k < (this->vars).size(); k++)
        {
            if (MY_DEBUG)
                cout << __FILE__ << __LINE__ << endl;
            (this->vars[k]).print(depth + 2);
        }
    }
    else if ((this->vars).size() == 1)
    {
        (this->vars[0]).print(depth + 1);
    }
}

void ForStmt::print(int depth)
{
    printDepth(depth);
    cout << "For Stmt." << endl;
    if (this->init)
    {
        printDepth(depth + 1);
        cout << "Init Stmt." << endl;
        this->init->print(depth + 2);
    }
    if (this->test)
    {
        printDepth(depth + 1);
        cout << "Judge Conditions." << endl;
        this->test->print(depth + 2);
    }
    if (this->other)
    {
        printDepth(depth + 1);
        cout << "Increment" << endl;
        this->other->print(depth + 2);
    }
    printDepth(depth + 1);
    cout << "Action." << endl;
    this->run->print(depth + 2);
}

void WhileStmt::print(int depth)
{
    printDepth(depth);
    cout << "While Stmt. " << endl;
    printDepth(depth + 1);
    cout << "Judge Condition." << endl;
    this->test->print(depth + 2);
    printDepth(depth + 1);
    cout << "Action." << endl;
    this->run->print(depth + 2);
}

void BlockStmt::print(int depth)
{
    printDepth(depth);
    cout << "Comp Stmt. " << endl;
    for (int k = 0; k < (this->stmts).size(); k++)
    {
        (this->stmts)[k]->print(depth + 1);
    }
}

void FuncDecStmt::print(int depth)
{
    printDepth(depth);
    cout << "Func Dec Stmt. " << endl;
    printDepth(depth + 1);
    cout << "Return Type." << endl;
    this->re->print(depth + 2);
    printDepth(depth + 1);
    cout << "Func Name." << endl;
    this->name->print(depth + 2);
    printDepth(depth + 1);
    cout << "Para Dec Stmt." << endl;
    for (int k = 0; k < (this->args).size(); k++)
    {
        printDepth(depth + 2);
        cout << "Var Dec." << endl;
        (this->args)[k].second->print(depth + 3);
        (this->args)[k].first->print(depth + 3);
    }
}

void FuncDefStmt::print(int depth)
{
    printDepth(depth);
    cout << "Func Def Stmt." << endl;
    this->funcdec.print(depth + 1);
    this->block->print(depth + 1);
}

void StructDecStmt::print(int depth)
{
    printDepth(depth);
    cout << "Struct Dec Stmt." << endl;
    this->type->print(depth + 1);
}

void StructDefStmt::print(int depth)
{
    printDepth(depth);
    cout << "Struct Def Stmt. " << endl;
    this->type->print(depth + 1);
}

void ReturnStmt::print(int depth)
{
    printDepth(depth);
    cout << "Return Stmt. " << endl;
    this->expr->print(depth + 1);
}
void initGlobalVar(std::ostream &os);
int curReturnLabel = 0;
void FuncDefStmt::output(std::ostream &os)
{
    int returnLable = ++curReturnLabel;
    os << funcdec.name->ID;
    os << ":\n    push ebp\n    mov ebp, esp\n";

    size_t _Size = block->belong->maxSize();
    stack_esp = -_Size;
    if (_Size)
        os << "    sub esp, " << toHex(_Size) << "\n";
    if (funcdec.name->ID == "main")
        initGlobalVar(os);
    for (auto &stmt : block->stmts)
    {
        stmt->output(os);
    }
    if (returnLable != curReturnLabel)
        my_error("return label error");
    os << "return_" << returnLable << ":\n    mov esp, ebp\n    pop ebp\n    ret\n\n";
}
void ReturnStmt::output(std::ostream &os)
{
    auto v = expr->calValue(os);
    if (v->str() != "eax")
    {
        os << "    mov eax, " << v->str() << "\n";
    }

    os << "    jmp return_" << curReturnLabel << "\n";
    delete v;
}