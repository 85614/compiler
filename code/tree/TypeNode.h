#pragma once
#include <vector>
#include <string.h>
#include "IDNode.h"
#include "ASTNode.h"
#include "TempNode.h"
#include "ExprNode.h"

struct ExprNode;

struct TypeNode : public ASTNode
{

    size_t size = -1;
    AST_e get_AST_e() override { return AST_e::Type; }
    virtual type_e get_type_e() = 0;
    static TypeNode *getType(const std::string &_Name) ;
    virtual bool assignable(TypeNode *type) const { return isSame(type); }
    virtual bool isSame(TypeNode *type) const = 0;
    virtual bool decAble()const = 0;
    static void checkNull(TypeNode *type, const char *tip){
        if (!type){
            cout << tip << endl;
            exit(1);
        }
    }
};

struct BasicTypeNode : public TypeNode
{
    // 基础类型， 请使用静态对象
    static BasicTypeNode *VOID, *INT;
    static BasicTypeNode *typeList[2];
    std::string name;
    static TypeNode *getType(const std::string &_Name){
        for (auto type: typeList)
            if (type->name == _Name)
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

    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: VOID" << endl;
    }
    bool assignable(TypeNode *type) const override{
        return false;
    }
    virtual bool decAble()const override { return false; }
    bool isSame(TypeNode *type) const override {
        checkNull(type, "in isSame type is NULL");
        return type == &VOID;
    }
private:
    VoidTypeNode(const char *_Name)
    {
        this->name = _Name;
    }
};


struct IntegerTypeNode : public BasicTypeNode
{
    // 整数类型
    static IntegerTypeNode INT;
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::INTEGER; };
    
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: INTEGER" << endl;
    }
    virtual bool decAble()const override { return true; }
    bool assignable(TypeNode *type) const override{
        return isSame(type);
    }
    
    bool isSame(TypeNode *type) const override {
        checkNull(type, "in isSame type is NULL");
        return type == &INT;
    }
private:
    IntegerTypeNode(const char *_Name, size_t _Size)
    {
        this->name = _Name;
        this->size = size;
    }
};

struct FloatTypeNode : public BasicTypeNode
{
    // 浮点数
    static FloatTypeNode FLOAT;
    virtual basic_type_e get_basic_type_e() override { return basic_type_e::FLOAT; };
    virtual bool decAble()const override { return true; }
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: FLOAT" << endl;
    }
    bool assignable(TypeNode *type) const override{
        return isSame(type);
    }
    bool isSame(TypeNode *type) const override {
        checkNull(type, "in isSame type is NULL");
        return type == &FLOAT;
    }
private:
    FloatTypeNode(const char *_Name, size_t _Size)
    {
        this->name = _Name;
        this->size = size;
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
        return getStructType(_ID->ID.c_str());
    }
    virtual bool decAble()const override { return defined; }
    bool isSame(TypeNode *type) const override {
        checkNull(type, "in isSame type is NULL");
        if (type->get_type_e() == type_e::BasicType) {
            auto basicT = (BasicTypeNode*) type;
            if (basicT->get_basic_type_e() == basic_type_e::STRUCT){
                auto structT = (StructTypeNode*) type;
                if (structT->ID->isSame(this->ID))
                    return true;
            }
        }
        return false;
    }
    static TypeNode *getStructType(const std::string &name, SymbolTable*symbolTable){
        if (!symbolTable) {
            cout << "符号表为NULL" << endl;
            exit(1);
        }
        Identifier *n = symbolTable->get(name);
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
        
        return nullptr;
    }
    static TypeNode *getStructType(const std::string &name)
    {
        // find from structList
        return getStructType(name, global);
    }
    void addMembers(ASTNode *members);
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
    void simplePrint(int depth) override {
        printDepth(depth);
        cout << "Type Specifier: Sturct " << this->ID->ID << endl;
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
    virtual bool decAble()const override { return false; }
    bool assignable(TypeNode *type) const override{
        return false;
    }
    bool isSame(TypeNode *type) const override {
        checkNull(type, "in isSame type is NULL");
        if (type->get_type_e() != type_e::FuncType) 
            return false;
        auto funcT = (FuncTypeNode*)type;
        if (!re->isSame(funcT->re))
            return false;
        auto &rightArgs = funcT->args;
        if (rightArgs.size() != args.size())
            return false;
        for (int i = 0; i < args.size(); ++i) {
            if (!args[i]->isSame(rightArgs[i]))
                return false;
        }
        return true;
    }
};

struct ArrayTypeNode : public TypeNode
{
    // 数组类型
    TypeNode *basicType;
    virtual type_e get_type_e() override { return type_e::ArrayType; };
    size_t len;
    ArrayTypeNode(TypeNode *_Basic, ExprNode *_Size);
    ArrayTypeNode(TypeNode *_Basic, std::vector<ASTNode*>& leafs){
        cout << "ArrayNode 构造函数已过时" << endl;
        exit(1);
    }
    virtual bool decAble()const override { return true; }
    bool assignable(TypeNode *type) const override {
        return false;
    }
    bool isSame(TypeNode *type) const override{
        checkNull(type, "in assignable type is NULL");
        if (type->get_type_e() != type_e::ArrayType) 
            return false;
        auto arrayT = (ArrayTypeNode*) type;
        return basicType->isSame(arrayT->basicType);
    }
    void print(int depth) {
        printDepth(depth);
        cout << "Type Specifier: Array" << endl;
        printDepth(depth + 1);
        cout << "Size: " << this->len << endl;
        this->basicType->print(depth + 1);
    }
};




struct PointerTypeNode : public TypeNode 
{
    // 指针类型
    TypeNode *basicType;
    int dimension = 0;
    virtual type_e get_type_e() override { return type_e::PointerType; };
    PointerTypeNode(TypeNode *_Basic, int d = 1) : basicType(_Basic), dimension(d) {
        if (d != 1 ) {
            cout << "指针有好多个* "<< endl;
            exit(1);
        }
    };
    virtual bool decAble()const override { return true; }
    bool isSame(TypeNode *type) const override{
        checkNull(type, "in assignable type is NULL");
        if (type->get_type_e() != type_e::PointerType) 
            return false;
        auto pointT = (PointerTypeNode*) type;
        return basicType->isSame(pointT->basicType);
    }
    bool assignable(TypeNode *type) const override {
        if (isSame(type))
            return true;
        if (type->get_type_e() == type_e::ArrayType &&((ArrayTypeNode*)type)->basicType == this->basicType)
            return true;
        return false;
    }
    void print(int depth)
    {
        printDepth(depth);
        cout << "Type Specifier: POINTER" << endl;
        this->basicType->print(depth + 1);
    }
};
