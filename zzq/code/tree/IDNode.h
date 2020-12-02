#pragma once
#include "../symbol/SymbolTable.h"
#include "ASTNode.h"


struct StmtNode;

struct IDNode: public ASTNode {
    // 标识符
    // IDType_e id_type = IDType_e::unknow; //ID类型 类型名、变量名、函数名等
    // TypeNode *type = nullptr; // 变量或函数的类型
    // SymbolTable *symboltable = nullptr; // 所属的符号表（作用域）

    const char *ID; // 标识符
    Identifier *realID = nullptr;
    ~IDNode()=default;

    AST_e get_AST_e()override{ return AST_e::ID; }
    IDNode(const char *_ID): ID(_ID) {
        if (!_ID)
            printf("标识符是空指针字符串\n");
        this->realID = global.get(_ID);
        if (!this->realID)
            this->realID = staticGlobal.get(_ID);
        // if (!this->realID)
        //     printf("未声明的标识符%s\n", _ID);
        // 只有非声明语句需要报错
    }  
    void setType(IDType_e IDType, TypeNode *type) {
        if (!realID){
            printf("ID %s 未声明", ID);
            return;
        }
        else {
            realID->IdType = IDType;
            realID->extra = type;
        }
            
    }
    void checkExist(bool _Existed)const {
        if (existed()!=_Existed) {
            printf("未声明的标识符%s\n", ID);
            exit(1);
        }
    }
    bool existed() const {return realID;}
    void print(int depth) {
        printDepth(depth);
        cout << "ID Declaration: " << this->ID << endl;
    }
};

