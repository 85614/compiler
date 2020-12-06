#pragma once
#include <vector>
#include <algorithm>
#include "Identifier.h"
#define DEBUG2(x)  { cout<<__FILE__ << " " << __LINE__ << "  " <<#x <<" is "<<x <<endl;}
// #define DEBUG2(x) {}

struct ASTNode;
struct SymbolTable;
extern SymbolTable *global;
struct SymbolTable{
private:
    // 暂时不会使用这个属性
    const SymbolTable *parent = nullptr; // 父作用域
public:
    ASTNode *belong; // 所属的节点，如果有的话
    std::vector<Identifier*> IDList;// 作用域内可直接访问的符号，包括变量名、函数名等
    SymbolTable(ASTNode *_Belong,const SymbolTable *_Parent = nullptr)
        :parent(_Parent), belong(_Belong)
    {
    }
    void registe(IDNode *ID, IDType_e idType, TypeNode * extra);
    Identifier *get(const std::string &name) const{
        return getTableAndID(name).second;
    }
    std::pair<const SymbolTable*, Identifier*> getTableAndID(const std::string &name)const {
         if (name.empty()) {
            cout << "尝试使用空指针获取标识符"<< name << endl;;
            exit(1);
            return std::pair<const SymbolTable*, Identifier*>(this, nullptr);
        }
        for (auto it = global->IDList.rbegin(); it != global->IDList.rend(); ++it) {
            if ((*it)->name == name) 
                return std::make_pair(this, *it);
        }
        if (parent) 
            return parent->getTableAndID(name);
        return std::pair<const SymbolTable*, Identifier*>(this, nullptr);
    }

    static bool isRepeat(Identifier *id, Identifier *id2);

    void checkRepeat(){
        auto child = this;
        for (auto it = IDList.begin(); it != IDList.end(); ++it) {
            for (auto it2 = it; ++it2, it2 != IDList.end();) {
                if (isRepeat(*it, *it2)){
                    cout << (*it)->name << "标识符重定义" << endl;
                    exit(1);
                }

            }
        }
    }
    SymbolTable *makeChild(ASTNode*_Belong, int _TokenCount)
    {
        if (this != global) {
            cout << "只允许global 生成子符号表" <<endl;
            exit(1);
        }
        auto begin = IDList.begin();
        for ( ;begin!= IDList.end(); ++begin) {
            if ((*begin)->tokenCount >= _TokenCount)
                break;
        }
        global = new SymbolTable{this->belong, this->parent};
        this->belong = _Belong;
        this->parent = global;
        auto childIDList = std::vector<Identifier*>{begin, this->IDList.end()};
        this->IDList.erase(begin, this->IDList.end());
        global->IDList = std::move(this->IDList);
        this->IDList = std::move(childIDList);
        this->checkRepeat();
        return this;
    }
    // 符号表
};

