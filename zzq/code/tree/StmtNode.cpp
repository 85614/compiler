#include <math.h>
#include "StmtNode.h"
#include "TypeNode.h"
#include "ExprNode.h"

void VarDefStmt::addVars(ASTNode*_Vars) {
    if(!_Vars)
        return;
    if(_Vars->get_AST_e()==AST_e::Temp){
        TempNode* temp = (TempNode*)_Vars;
        if(!temp->msg) {
            // 没有消息，此temp节点是一个变量列表
            for(ASTNode *n: temp->childList)
                addVars(n);
        } else if (strcmp(temp->msg, "=") == 0) {
            // 带初始化
            std::vector<ASTNode*> leafs;
            temp->getAllLeaf(leafs);
            if(leafs.size()!=2){
                printf("带初始化的变量声明，变量名+初始化值数量不为2");
                return;
            }
            addVar(this->basicType, leafs[0],leafs[1]);
        } else if (strcmp(temp->msg, "[]") == 0) {
            // 声明数组
            std::vector<ASTNode*> leafs;
            temp->getAllLeaf(leafs);
            if(leafs.size()!=2){
                printf("数组声明，变量名+数组长度不为2");
                return;
            }
            if (leafs[1]->get_AST_e() != AST_e::Expr)
                ;
            auto expr = (ExprNode*)(leafs[1]);
            if (expr->get_expr_e() != expr_e::Const)
                ;
            auto _const = (ConstExprNode*)expr;
            int len =  atoi(_const->value);
            addVar(new ArrayTypeNode(basicType),leafs[0], nullptr);

        } else if (strcmp(temp->msg, "*") == 0) {            
            // 声明指针
            printf("变量定义: unexcepted *");
            return;
            // std::vector<ASTNode*> leafs;
            // temp->getAllLeaf(leafs);
        } else {
            printf("变量定义是出现不期望的节点类型\n");
        }
    }
}


void ExprStmtNode::print(int depth)
{
    printDepth(depth);
    cout << "Expr Stmt. " << endl;
    this->expr->print(depth + 1);
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
    if (!falseRun)
    {
        printDepth(depth);
        cout << "ELSE Stmt." << endl;
        printDepth(depth + 1);
        cout << "Run if false." << endl;
        this->falseRun->print(depth + 2);
    }
}


void VarDef::print(int depth)
{
    printDepth(depth);
    cout << "Var def." << endl;
    this->ID->print(depth + 1);
    if (!this->init)
    {
        printDepth(depth + 1);
        cout << "Var Init." << endl;
        this->init->print(depth + 2);
    }
}

void VarDefStmt::print(int depth)
{
    printDepth(depth);
    cout << "Var Def Stmt." << endl;
    this->basicType->print(depth + 1);
    print(depth + 1);
    cout << "Var Def List." << endl;
    for (int k = 0; k < (this->vars).size(); k++)
    {
        (this->vars[k]).print(depth + 2);
    }
}

void ForStmt::print(int depth)
{
    printDepth(depth);
    cout << "For Stmt." << endl;
    if (!this->init)
    {
        printDepth(depth + 1);
        cout << "Init Stmt." << endl;
        this->init->print(depth + 2);
    }
    if (!this->test)
    {
        printDepth(depth + 1);
        cout << "Judge Conditions." << endl;
        this->test->print(depth + 2);
    }
    if (!this->other)
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
    print(depth + 1);
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
        (this->stmts)[k]->print(depth + 2);
    }
}

void FuncDecStmt::print(int depth)
    {
        printDepth(depth);
        cout << "Func Dec Stmt. " << endl;
        printDepth(depth + 1);
        cout << "Return Type." << endl;
        this->re->print(depth + 2);
        // printDepth(depth + 1);
        // cout << "Var Dec Stmt." << endl;
        // this->re->print(depth + 2);
        // this->name->print(depth + 2);
        printDepth(depth + 1);
        cout << "Func Name." << endl;
        this->name->print(depth + 2);
        printDepth(depth + 1);
        cout << "Para Dec Stmt." << endl;
        for (int k = 0; k < (this->args).size(); k++)
        {
            printDepth(depth + 2);
            cout << "Var Dec." << endl;
            (this->args)[k].first->print(depth + 3);
            (this->args)[k].second->print(depth + 3);
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