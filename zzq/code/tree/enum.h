#pragma once
enum class AST_e {
    Stmt, // 语句
    ID, // 标识符
    Type, // 类型
    Expr, //表达式
    Temp, // 临时节点
    Program, //程序
    File // 文件
};

enum class op_e {
    Assignop = 1,       // =
    Relop = 2,          // < > <= >=
    Plus = 3,           // +
    Minus = 4,          // -
    Times = 5,          // *
    Div = 6,            // /
    Mod = 7,            // %
    Power = 8,          // ^
    And = 9,            // &&
    Or = 10,            // ||
    Negative = 11,      // -
    Not = 12,           // !
    SignalAnd = 13,     // &
    GetValue = 14,      // *
    GetArrayValue = 15, //a[3]
    GetMember = 16,     // a.b
    AssignArray = 17,   // a[1] = ?
    AssignMember = 18   // a.b = ?
};

const char* getInfo(op_e opE) {
    switch (opE)
    {
    case op_e::Assignop:
        return "Assignop";
    case op_e::Relop:
        return "Relop";
    case op_e::Plus:
        return "Plus";
    case op_e::Minus:
        return "Minus";
    case op_e::Times:
        return "Times";
    case op_e::Div:
        return "Div";
    case op_e::Mod:
        return "Mod";
    case op_e::Power:
        return "Power";
    case op_e::And:
        return "And";
    case op_e::Or:
        return "Or";
    case op_e::Negative:
        return "Negative";
    case op_e::Not:
        return "Not";
    case op_e::SingalAnd:
        return "SingalAnd";
    case op_e::GetValue:
        return "GetValue";
    case op_e::GetArrayValue:
        return "GetArrayValue";
    case op_e::GetMember:
        return "GetMember";
    case op_e::AssignArray:
        return "AssignArray";
    case op_e::AssignMember:
        return "AssignMember";
    default:
        return "something wrong";
    }
}

enum class expr_e {
    Op1, // 1目运算符
    Op2, // 2目运算符
    Op3, // 3目运算符
    FuncCall, //函数调用
    Var, // 变量
    Const // 常量
};


const char* getInfo(expr_e temp) {
    switch (temp)
    {
    case expr_e::Op1:
        return "Op1";
    case expr_e::Op2:
        return "Op2";
    case expr_e::Op3:
        return "Op3";
    case expr_e::FuncCall:
        return "FuncCall";
    case expr_e::Var:
        return "Var";
    case expr_e::Const:
        return "Const";
    default:
        return "";
    }
}

enum IDType_e {
    unknow, //暂时未知，之后得到
    Typename, //类型名
    Var, // 变量名
    Func // 函数名
};

const char* getInfo(IDType_e temp) {
    switch (temp)
    {
    case unknow:
        return "unknow";
    case Typename:
        return "Typename";
    case Var:
        return "Var";
    case Func:
        return "Func";
    default:
        return "Const";
    }
}

enum class type_e {
    BasicType, // 基本类型
    PointerType, // 指针类型
    ReferenceType, // 引用类型
    ArrayType, // 数组类型
    FuncType // 函数类型
};

const char* getInfo(type_e temp) {
    switch (temp)
    {
    case type_e::BasicType:
        return "BasicType";
    case type_e::PointerType:
        return "PointerType";
    case type_e::ReferenceType:
        return "ReferenceType";
    case type_e::ArrayType:
        return "ArrayType";
    case type_e::FuncType:
        return "FuncType";
    default:
        return "";
    }
}

enum class basic_type_e {
    VOID, // void 类型
    INTEGER, // 整数类型
    FLOAT, // 浮点数类型
    STRUCT // 结构体类型
};

const char* getInfo(basic_type_e temp) {
    switch (temp)
    {
    case basic_type_e::VOID:
        return "VOID";
    case basic_type_e::INTEGER:
        return "INTEGER";
    case basic_type_e::FLOAT:
        return "FLOAT";
    case basic_type_e::STRUCT:
        return "STRUCT";
    default:
        return "";
    }
}


enum class stmt_e {
    IF, // if 语句
    FunDef, // 函数定义
    FunDec, // 函数声明
    VarDef, // 变量声明
    StructDec, // 结构体声明
    StructDef, // 结构体声明
    FOR, // for 语句
    While, // while 语句
    Return, //Return语句
    Block, // 语句块
    Expr // 表达式语句
};

const char* getInfo(stmt_e temp) {
    switch (temp)
    {
    case stmt_e::IF:
        return "IF";
    case stmt_e::FunDef:
        return "FunDef";
    case stmt_e::FunDec:
        return "FunDec";
    case stmt_e::VarDef:
        return "VarDef";
    case stmt_e::StructDec:
        return "StructDec";
    case stmt_e::StructDef:
        return "StructDef";
    case stmt_e::FOR:
        return "FOR";
    case stmt_e::While:
        return "While";
    case stmt_e::Block:
        return "Block";
    case stmt_e::Expr:
        return "Expr";
    default:
        return "";
    }
}