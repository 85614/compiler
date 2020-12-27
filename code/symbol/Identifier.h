
#pragma once
#include <string>
#include <iostream>
#include "../tree/enum.h"
using std::cout;
using std::endl;
struct IDNode;
struct TypeNode;
struct Identifier {
    std::string name;
    IDType_e IdType = IDType_e::unknow;
    TypeNode * extra = nullptr;
    int off = 0;
    int tokenCount = 0;
    std::string getCode() {
        char buf [32];
        if (off ) {
            if (off > 0)
                snprintf(buf, 31, "[ebp+%#x]", off);
            else 
                snprintf(buf, 31, "[ebp-%#x]", -off);
            return buf;
        }
        return name;
        
    }
    Identifier(IDNode *_ID, IDType_e _IdType, TypeNode * _Extra);

};