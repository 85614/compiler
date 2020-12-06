#include "SymbolTable.h"
#include "../tree/IDNode.h"
#include "../tree/TypeNode.h"
 void SymbolTable::registe(IDNode *ID, IDType_e idType, TypeNode * extra)
 {

    auto item = new Identifier(ID, idType, extra);
    auto it = IDList.begin();
    for (; it!= IDList.end();++it) {
        if ((*it)->tokenCount >= ID->tokenCount){
            break;
        }
    }
    it = IDList.insert(it, item);
    // ID->realID = item; // 在Identifier的构造函数中已经有了
  }

bool SymbolTable::isRepeat(Identifier *id, Identifier *id2){
    if (id == id2) {
        cout <<" Identifier 重复" << endl;
        exit(1);
        return true;
    }
    if (id->name != id2->name)
        return false;
    switch (id->IdType)
    {
    case IDType_e::FuncDec:
        if( id2->IdType == IDType_e::FuncDec || id2->IdType == IDType_e::FuncDef) {
            return !id->extra->isSame(id2->extra);
        }
        return true;
        break;
    case IDType_e::VarDec:
        if( id2->IdType == IDType_e::VarDec || id2->IdType == IDType_e::VarDef) {
            return !id->extra->isSame(id2->extra);
        }
        return true;
        break;
    case IDType_e::TypenameDec:
        return id2->IdType != IDType_e::TypenameDec && id2->IdType != IDType_e::TypenameDef;
        break;
    case IDType_e::FuncDef:
        return id2->IdType != IDType_e::FuncDec;
        break;
    case IDType_e::VarDef:
        return id2->IdType != IDType_e::VarDec;
        break;
    case IDType_e::TypenameDef:
        return id2->IdType != IDType_e::TypenameDec;
        break;
    default:
        return true;
    }
}
