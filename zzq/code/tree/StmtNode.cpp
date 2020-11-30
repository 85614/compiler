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