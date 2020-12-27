#pragma once
#include <vector>
#include <algorithm>
#include "Identifier.h"
#include "../base.h"

struct ASTNode;
struct SymbolTable;
extern SymbolTable *global;
struct SymbolTable
{
private:
    // 暂时不会使用这个属性
    const SymbolTable *__Parent = nullptr; // 父作用域
public:
    ASTNode *belong; // 所属的节点，如果有的话
    std::vector<SymbolTable *> children;
    int off = 0;
    std::vector<Identifier *> IDList; // 作用域内可直接访问的符号，包括变量名、函数名等
    SymbolTable(ASTNode *_Belong, const SymbolTable *_Parent = nullptr)
        : __Parent(_Parent), belong(_Belong)
    {
    }
    void registe(IDNode *ID, IDType_e idType, TypeNode *extra);
    Identifier *get(const std::string &name) const
    {
        return getTableAndID(name).second;
    }
    size_t _MaxSize = -1;
    size_t maxSize()
    {
        if (_MaxSize == -1)
            calSize();
        return _MaxSize;
    }
    void calSize();
    bool individual = false;
    void setIndividual(int start = 8);
    std::pair<const SymbolTable *, Identifier *> getTableAndID(const std::string &name) const
    {
        if (name.empty())
        {
            cout << "尝试使用空指针获取标识符" << name << endl;
            ;
            exit(1);
            return std::pair<const SymbolTable *, Identifier *>(this, nullptr);
        }
        Identifier *result = nullptr;
        for (auto it = global->IDList.rbegin(); it != global->IDList.rend(); ++it)
        {
            if ((*it)->name == name)
            {
                switch ((*it)->IdType)
                {
                case IDType_e::FuncDec:
                case IDType_e::VarDec:
                case IDType_e::TypenameDec:
                    // 找到声明，尝试找定义
                    result = *it;
                    break;
                default:
                    return std::make_pair(this, *it);
                }
            }
        }
        if (result)
            return std::make_pair(this, result);
        if (parent())
            return parent()->getTableAndID(name);
        return std::pair<const SymbolTable *, Identifier *>(this, nullptr);
    }
    const SymbolTable *parent() const
    {
        if (this == global || __Parent)
            return __Parent;
        // DEBUG2(global);
        // printChild();
        // for (auto ch : children)
        //     ch->printChild();
        // my_error("parent is NULL");
        return global;
    }
    static bool isRepeat(Identifier *id, Identifier *id2);
    void printChild() const
    {
        DEBUG2(this);
        for (auto &id : IDList)
            DEBUG2(id->name);
    }
    void checkRepeat()
    {
        // for (auto id: IDList) {
        //
        // }
        for (auto it = IDList.begin(); it != IDList.end(); ++it)
        {
            for (auto it2 = it; ++it2, it2 != IDList.end();)
            {
                if (isRepeat(*it, *it2))
                {
                    cout << (*it)->name << "标识符重定义" << endl;
                    exit(1);
                }
            }
        }
    }
    void addChild(SymbolTable *child)
    {
        children.push_back(child);
        child->__Parent = this;
    }
    SymbolTable *makeChild(ASTNode *_Belong, int _TokenCount)
    {

        if (this != global)
        {
            cout << "只允许global 生成子符号表" << endl;
            exit(1);
        }
        auto begin = IDList.begin();
        for (; begin != IDList.end(); ++begin)
        {
            if ((*begin)->tokenCount >= _TokenCount)
                break;
        }
        // global = new SymbolTable{this->belong, this->parent};
        global = new SymbolTable{this->belong, nullptr};
        this->belong = _Belong;
        // this->parent = global;
        auto childIDList = std::vector<Identifier *>{begin, this->IDList.end()};
        this->IDList.erase(begin, this->IDList.end());
        global->IDList = std::move(this->IDList);
        this->IDList = std::move(childIDList);
        this->checkRepeat();
        // global->children.push_back(this);

        return this;
    }
    // 符号表
};
