#pragma once
#include <vector>
#include <string.h>
#include "IDNode.h"
#include "ASTNode.h"
#include "TempNode.h"



struct TypeNode: public ASTNode{

    size_t size = -1;
    AST_e get_AST_e()override {return AST_e::Type;}
    virtual type_e get_type_e() = 0;
};

struct BasicTypeNode: public TypeNode {
    // 基础类型， 请使用静态对象
    static BasicTypeNode *VOID, *INT;
    const char *name = nullptr;
    virtual type_e get_type_e() override {return type_e::BasicType;};
    virtual basic_type_e get_basic_type_e() = 0;
};

struct VoidTypeNode: public BasicTypeNode {
    // void 类型
    static VoidTypeNode VOID;
    virtual basic_type_e get_basic_type_e()override { return basic_type_e::VOID; };
    VoidTypeNode(const char *_Name) {
        this->name = _Name;
    }
};

struct IntegerTypeNode: public BasicTypeNode {
    // 整数类型
    static IntegerTypeNode INT;
    virtual basic_type_e get_basic_type_e()override { return basic_type_e::INTEGER; };
    IntegerTypeNode(const char *_Name, size_t _Size) {
        this->name = _Name;
        this->size = size;
    }
};

struct FloatTypeNode: public BasicTypeNode {
    // 浮点数
    static FloatTypeNode FLOAT;
    virtual basic_type_e get_basic_type_e()override { return basic_type_e::FLOAT; };
    FloatTypeNode(const char *_Name, size_t _Size) {
        this->name = _Name;
        this->size = size;
    }
};

struct StructTypeNode: public BasicTypeNode {
    // 结构体
    bool defined = false;
    IDNode *ID; // 结构体名
    static std::vector<StructTypeNode*> structList;
    std::vector<std::pair<TypeNode*,IDNode*>> members; //成员变量
    virtual basic_type_e get_basic_type_e()override { return basic_type_e::STRUCT; };
    static StructTypeNode *getStructType(IDNode *_ID) {
        return getStructType(_ID->ID);
    }
    static StructTypeNode *getStructType(const char *name) {
        // find from structList
        for(StructTypeNode *node: structList) {
            if(strcmp(node->name,name)==0)
                return node;
        }
        return nullptr;
    }
    void addMembers(ASTNode *members) {
        if (!members) 
            return;
        if (members->get_AST_e()==AST_e::Temp){
            for (ASTNode*child: ((TempNode*)members)->childList)
                addMembers(child);   
        }
        this->defined = true;
    }
    static StructTypeNode *createNode(IDNode *_ID, ASTNode *members);
private:
    StructTypeNode()=default;
};



struct FuncTypeNode : public TypeNode {
    // 函数类型，函数名标识符的类型
    // 如 int fun(int);  fun的类型就是int(int)
    virtual type_e get_type_e() override {return type_e::FuncType;};
    TypeNode *re; //返回值类型
    std::vector<TypeNode *> args; // 参数类型
};

struct ArrayTypeNode : public TypeNode {
    // 数组类型
    TypeNode *basicType;
    size_t len;
    virtual type_e get_type_e() override {return type_e::ArrayType;};
    ArrayTypeNode(TypeNode *_Basic):basicType(_Basic) {

    }
};


struct PointerTypeNode: public TypeNode {
    // 指针类型
    TypeNode *basicType;
    virtual type_e get_type_e() override {return type_e::PointerType;};
    PointerTypeNode(TypeNode *_Basic):basicType(_Basic) {

    }
};