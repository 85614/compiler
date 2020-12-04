#pragma once
#include <vector>
#include <string.h>
#include "IDNode.h"
#include "ASTNode.h"
#include "TempNode.h"
#include "ExprNode.h"

struct TypeNode : public ASTNode
{

    size_t size = -1;
    AST_e get_AST_e() override { return AST_e::Type; }
    virtual type_e get_type_e() = 0;
    static TypeNode *getType(const char *_Name) ;
    
};

struct BasicTypeNode : public TypeNode
{
    // 基础类型， 请使用静态对象
    static BasicTypeNode *VOID, *INT;
    static BasicTypeNode *typeList[2];
    const char *name = nullptr;
    static TypeNode *getType(const char *_Name){
        for (auto type: typeList)
            if (strcmp( type->name,_Name) == 0 )
                return type;
        return nullptr;
    }
    virtual type_e get_type_e() override { return type_e::BasicType; };
    virtual basic_type_e get_basic_type_e() = 0;
    
};

struct VoidTypeNode : public BasicTypeNode
{
    // void 类型
    static VoidTypeNode VOID;
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::VOID; };
    VoidTypeNode(const char *_Name)
    {
        this->name = _Name;
    }
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: VOID" << endl;
    }
};

struct IntegerTypeNode : public BasicTypeNode
{
    // 整数类型
    static IntegerTypeNode INT;
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::INTEGER; };
    IntegerTypeNode(const char *_Name, size_t _Size)
    {
        this->name = _Name;
        this->size = size;
    }
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: INTEGER" << endl;
    }

    void print_(int depth) {
        printDepth(depth);
        cout << "Type Specifier: INTEGER";
    }
};

struct FloatTypeNode : public BasicTypeNode
{
    // 浮点数
    static FloatTypeNode FLOAT;
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::FLOAT; };
    FloatTypeNode(const char *_Name, size_t _Size)
    {
        this->name = _Name;
        this->size = size;
    }
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: FLOAT" << endl;
    }
};

struct StructTypeNode : public BasicTypeNode
{
    // 结构体
    bool defined = false;
    IDNode *ID; // 结构体名
    std::vector<std::pair<TypeNode *, IDNode *>> members; //成员变量
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::STRUCT; };
    static TypeNode *getStructType(IDNode *_ID)
    {
        return getStructType(_ID->ID);
    }
    static TypeNode *getStructType(const char *name)
    {
        // find from structList
        Identifier *n = global.get(name);
        if (!n) {
            cout << "类型 "<<name << "未定义"<<endl;
            exit(1);
        }
        if (n && (n->IdType == IDType_e::TypenameDec||n->IdType == IDType_e::TypenameDef))
        {
            if (n->extra)
                return n->extra;
            else 
                cout <<"类型 " << n->name<< "获取的类型为NULL";

        }
        
        DEBUG2(n);
        // DEBUG2(n->extra);
        return nullptr;
    }
    void addMembers(ASTNode *members)
    {
        if (!members)
            return;
        if (members->get_AST_e() == AST_e::Temp)
        {
            for (ASTNode *child : ((TempNode *)members)->childList)
                addMembers(child);
        }
        this->defined = true;
    }
    static StructTypeNode *createNode(IDNode *_ID, ASTNode *members);
    void print(int depth)
    {
        printDepth(depth);
        cout << "Sturct Name." << endl;
        this->ID->print(depth + 1);
        if (defined)
        {
            printDepth(depth);
            cout << "Member Attribute List." << endl;
            for (int k = 0; k < this->members.size(); k++)
            {
                printDepth(depth + 1);
                cout << "Var Dec." << endl;
                (this->members)[k].first->print(depth + 2);
                (this->members)[k].second->print(depth + 2);
            }
        }
    }

private:
    StructTypeNode() = default;
};

struct FuncTypeNode : public TypeNode
{
    // 函数类型，函数名标识符的类型
    // 如 int fun(int);  fun的类型就是int(int)
    virtual type_e get_type_e() override { return type_e::FuncType; };
    TypeNode *re;                 //返回值类型
    std::vector<TypeNode *> args; // 参数类型
    FuncTypeNode(TypeNode *_Re, std::vector<TypeNode *> &&_Args)
        :re(_Re), args(_Args)
    {
    }
};

struct PointerTypeNode : public TypeNode 
{
    // 指针类型
    TypeNode *basicType;
    int dimension = 0;
    virtual type_e get_type_e() override { return type_e::PointerType; };
    PointerTypeNode(TypeNode *_Basic, int d) : basicType(_Basic), dimension(d) {};

    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: " << getInfo(((BasicTypeNode *)this->basicType)->get_basic_type_e());
        for(int k = 0; k < dimension; k++) cout << '*';
        cout << endl;
    }

    void print_(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: " << getInfo(((BasicTypeNode *)this->basicType)->get_basic_type_e());
        for(int k = 0; k < dimension; k++) cout << '*';
    }
};

struct ArrayTypeNode : public TypeNode
{
    // 数组类型
    TypeNode *basicType;
    virtual type_e get_type_e() override { return type_e::ArrayType; };
    //size_t len;
    // ArrayTypeNode(TypeNode *_Basic, int l) : basicType(_Basic)
    // {
    //     len = l;
    // }
    std::vector<size_t> len;
    ArrayTypeNode(TypeNode *_Basic, std::vector<ASTNode*>& leafs) ;
    void print(int depth)
    {
        if((this->basicType)->get_type_e() != type_e::PointerType) {
            printDepth(depth);
            cout << "Type Specifier: " << getInfo(((BasicTypeNode *)this->basicType)->get_basic_type_e())
              << " ";
        }
        else ((PointerTypeNode*)(this->basicType))->print_(depth);
        
        for(int k = 0; k < len.size(); k++) cout<<"[" << len[k] <<"]";
        cout<<endl;
    }
};

