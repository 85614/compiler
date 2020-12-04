#pragma once
#include <vector>
#include <algorithm>
#include "Identifier.h"
// #define DEBUG2(x)  { cout<<__FILE__ << " " << __LINE__ << "  " <<#x <<" is "<<x <<endl;}
#define DEBUG2(x) {}

struct ASTNode;
struct SymbolTable;
extern SymbolTable global;
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
    Identifier *get(const char *name) {
        cout << "try get ID"<<endl;
        DEBUG2(name);
        if (!name) {
            printf("尝试使用空指针获取标识符%s", name);
            return nullptr;
        }
        for (auto it = global.IDList.rbegin(); it != global.IDList.rend(); ++it) {
            if ((*it)->name == name) 
                return *it;
        }
        return nullptr;
    }

    void checkRepeat(){
        auto child = this;
        // DEBUG2(_TokenCount);
        cout << "children"<<endl;
        // DEBUG2(_TokenCount);
        for (Identifier *id: child->IDList) {
            // DEBUG2(id->tokenCount);
            DEBUG2(id->name);
            DEBUG2(id->tokenCount);
        }
        for (Identifier *id: child->IDList) {
            for (Identifier *id2: child->IDList) {
                if (id != id2 && id->name == id2->name) {
                    // DEBUG2(id);
                    // DEBUG2(id->name);
                    // DEBUG2(id2);
                    // DEBUG2(id2->name);
                    if (id->IdType == IDType_e::FuncDec ||
                        id->IdType == IDType_e::VarDec ||
                        id->IdType == IDType_e::TypenameDec ||
                        id2->IdType == IDType_e::FuncDec ||
                        id2->IdType == IDType_e::VarDec ||
                        id2->IdType == IDType_e::TypenameDec)
                        {DEBUG2(id2);}
                    else {
                        cout << id->name << "标识符重定义" << endl;
                        exit(1);
                    }
                    DEBUG2(id2);
                }
                
            }
        }       
    }
    SymbolTable *makeChild(ASTNode*_Belong, int _TokenCount)
    {
        // DEBUG2(_TokenCount);
        auto begin = IDList.begin();
        DEBUG2(_TokenCount);
        for ( ;begin!= IDList.end(); ++begin) {
            if ((*begin)->tokenCount >= _TokenCount)
                break;
        }
        // DEBUG2((*begin)->tokenCount);
        // DEBUG2((*begin)->name);
        auto child = new SymbolTable(_Belong, this);
        child->IDList.insert(child->IDList.end(), begin, this->IDList.end());
        this->IDList.erase(begin, this->IDList.end());
        child->checkRepeat();
        return child;
        
    }
    // 符号表
};

