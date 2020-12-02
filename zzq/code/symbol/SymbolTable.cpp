#include "SymbolTable.h"
#include "../tree/IDNode.h"
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
      cout << endl << "registe   " << (*it)->name << " tokenCount: "<<
          (*it)->tokenCount << endl;
  }