#include "TypeNode.h"
#include "IDNode.h"

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
        _ID->id_type = IDType_e::Typename;
        result->defined = false;
        result->addMembers(_Members);
        structList.push_back(result);
    }
    return result;
}