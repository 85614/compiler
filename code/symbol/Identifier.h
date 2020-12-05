
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
    int tokenCount = 0;
    Identifier(IDNode *_ID, IDType_e _IdType, TypeNode * _Extra);

};