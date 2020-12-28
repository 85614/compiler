#include "TypeNode.h"
#include "IDNode.h"
#include "ExprNode.h"
#include "StmtNode.h"

StructTypeNode *StructTypeNode::createNode(IDNode *_ID, ASTNode *_Members)
{
    StructTypeNode *result;
    result = new StructTypeNode;
    result->ID = _ID;
    result->name = _ID->ID;
    result->defined = _Members;
    result->addMembers(_Members);
    if (result->defined)
    {
        result->size = 0;
        for (auto &member : result->members)
            result->size += member.first->size;
    }
    return result;
}

TypeNode *TypeNode::getType(const std::string &_Name)
{
    auto ans = BasicTypeNode::getType(_Name);
    if (!ans)
        ans = StructTypeNode::getStructType(_Name);
    if (!ans)
        cout << "类型 " << _Name << "未找到" << endl;
    return ans;
}

// ArrayTypeNode::ArrayTypeNode(TypeNode *_Basic, std::vector<ASTNode *> &leafs) : basicType(_Basic)
// {
//     for (int k = 1; k < leafs.size(); k++)
//     {
//         if (leafs[k]->get_AST_e() != AST_e::Expr)
//             ;
//         auto expr = (ExprNode *)(leafs[k]);
//         if (expr->get_expr_e() != expr_e::Const)
//             ;
//         auto _const = (ConstExprNode *)expr;
//         len.push_back((size_t)atoi(_const->value));
//     }
// }

ArrayTypeNode::ArrayTypeNode(TypeNode *_Basic, ExprNode *_Size)
    : basicType(_Basic)
{
    if (_Size->get_expr_e() != expr_e::Const)
    {
        cout << "数组内[]的不是数字" << endl;
        exit(1);
    }
    len = atoi(((ConstExprNode *)_Size)->value.c_str());
    this->size = len * _Basic->size;
}

void StructTypeNode::addMembers(ASTNode *_Members)
{
    if (!_Members)
        return;
    if (_Members->get_AST_e() == AST_e::Temp)
    {
        for (ASTNode *child : ((TempNode *)_Members)->childList)
            addMembers(child);
    }
    else if (_Members->get_AST_e() == AST_e::Stmt)
    {
        StmtNode *stmt = (StmtNode *)_Members;
        if (stmt->get_stmt_e() == stmt_e::VarDef)
        {
            VarDefStmt *varDef = (VarDefStmt *)stmt;
            for (auto &var : varDef->vars)
            {
                auto member = std::make_pair(var.type, var.ID);
                members.push_back(member);
            }
        }
        else
        {
            cout << "结构体内部的语句不是声明语句，stmt_e:" << getInfo(stmt->get_stmt_e()) << endl;
        }
    }
    else
    {
        cout << "结构体内部的语句不是语句，AST_e:" << int(_Members->get_AST_e()) << endl;
    }
    this->defined = true;
}

ArrayTypeNode *ArrayTypeNode::newArrayTypeNode(TypeNode *_Basic, ExprNode *_Size)
{
    // 生成数组，但是大小要反过来，慎用
    if (_Size->get_expr_e() != expr_e::Const)
    {
        cout << "数组内[]的不是数字" << endl;
        exit(1);
    }
    auto len = atoi(((ConstExprNode *)_Size)->value.c_str());

    if (_Basic->get_type_e() == type_e::ArrayType)
    {
        auto arrayT = (ArrayTypeNode *)_Basic;
        auto temp = arrayT->len;
        arrayT->len = len;
        arrayT->size = arrayT->len * arrayT->basicType->size;
        auto ans = new ArrayTypeNode(_Basic, _Size);
        ans->len = temp;
        ans->size = temp * _Basic->size;
        return ans;
    }
    return new ArrayTypeNode(_Basic, _Size);
}