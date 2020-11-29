#include "TypeNode.h"
#include "IDNode.h"

StructTypeNode * StructTypeNode::createNode(IDNode *_ID, TempNode *members) {
        StructTypeNode *result = getStructType(_ID->ID);
        if (result) {
            if (!result->defined)
                addChild(members);
            else if (members) {
                // 报错
                printf("重复定义struct %s", result->ID->ID);
            }
        } 
        else {
            result = new StructTypeNode;
            result->ID = _ID;
            result->name = ID->ID;
            result->defined = false;
            addMembers(members);
            structList.push_back(result);
        }
        return result;
}