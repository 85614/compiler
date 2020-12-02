#include "TypeNode.h"
#include "IDNode.h"
#include "ExprNode.h"

StructTypeNode * StructTypeNode::createNode(IDNode *_ID, ASTNode *_Members) {
    StructTypeNode *result = getStructType(_ID->ID);
    if (result) {
        if (!result->defined)
            result->addChild(_Members);
        else if (_Members) {
            // 报错
            printf("重复定义struct %s", result->ID->ID);
        }
    } 
    else {
        result = new StructTypeNode;
        result->ID = _ID;
        result->name = _ID->ID;
        result->defined = false;
        result->addMembers(_Members);
        structList.push_back(result);
    }
    return result;
}


TypeNode *TypeNode::getType(const char *_Name) {
        return BasicTypeNode::INT;
}

ArrayTypeNode::ArrayTypeNode(TypeNode *_Basic, std::vector<ASTNode *> &leafs) : basicType(_Basic)
{
    for (int k = 1; k < leafs.size(); k++)
    {
        if (leafs[k]->get_AST_e() != AST_e::Expr)
            ;
        auto expr = (ExprNode *)(leafs[k]);
        if (expr->get_expr_e() != expr_e::Const)
            ;
        auto _const = (ConstExprNode *)expr;
        len.push_back((size_t)atoi(_const->value));
    }
}
