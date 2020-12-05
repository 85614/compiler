#include "Identifier.h"
#include "../tree/IDNode.h"
#include "../tree/StmtNode.h"
Identifier::Identifier(IDNode *_ID, IDType_e _IdType, TypeNode * _Extra)
    :name(_ID->ID),IdType(_IdType), extra(_Extra)
{
    _ID->realID = this;
    tokenCount = _ID->tokenCount;
}