#pragma once
#include "../symbol/SymbolTable.h"
#include "ASTNode.h"


struct StmtNode;

struct IDNode: public ASTNode {
    // 标识符
    // IDType_e id_type = IDType_e::unknow; //ID类型 类型名、变量名、函数名等
    // TypeNode *type = nullptr; // 变量或函数的类型
    // SymbolTable *symboltable = nullptr; // 所属的符号表（作用域）

    std::string ID;
    Identifier *realID = nullptr;
    SymbolTable *symbolTable;
    ~IDNode() = default;

    AST_e get_AST_e()override{ return AST_e::ID; }
    IDNode(const char *_ID): ID(_ID) {
        if (!_ID)
            printf("标识符是空指针字符串\n");
        this->realID = global->get(_ID);
        symbolTable = global;
        if (!this->realID)
            this->realID = staticGlobal.get(_ID);
        // if (!this->realID)
        //     printf("未声明的标识符%s\n", _ID);
        // 只有非声明语句需要报错
    }  
    void setType(IDType_e IDType, TypeNode *type) {
        if (checkExist()){
            realID->IdType = IDType;
            realID->extra = type;
        }
            
    }
    TypeNode *getType() const {
        if (realID->extra) {
            return realID->extra;
        }
        else {
            if (realID->IdType == IDType_e::TypenameDec)
                cout << "不允许使用不完整的类型" << ID << endl;
            else 
                cout << "ID "<< ID << "类型不确定" << endl;
        }
        return nullptr;
    }
    bool isSame(IDNode *_Right) const{
        if (ID != _Right->ID)
            return false;
        if (symbolTable == _Right->symbolTable)
            return true;
        return symbolTable->getTableAndID(ID).first == _Right->symbolTable->getTableAndID(ID).first;
            
    }
    bool checkExist(bool _Existed = true)const {
        if (existed()!=_Existed) {
            cout << "ID "<< ID << "未声明" << endl;
            exit(1);
            return false;
        }
        return true;
    }
    bool existed() const {return realID;}
    void print(int depth) {
        printDepth(depth);
        cout << "ID Declaration: " << this->ID << endl;
    }
};



