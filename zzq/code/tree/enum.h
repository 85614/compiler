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

enum class op_e{
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
    SingalAnd = 13,     // &
    GetValue = 14,      // *
    GetArrayValue = 15, //a[3]
    GetMember = 16,     // a.b
    AssignArray = 17,   // a[1] = ?
    AssignMember = 18   // a.b = ?
};

enum class expr_e {
    Op1, // 1目运算符
    Op2, // 2目运算符
    Op3, // 3目运算符
    FuncCall, //函数调用
    Var, // 变量
    Const // 常量
};

enum id_type_e {
    Typename, //类型名
    Var, // 变量名
    Func // 函数名
};


enum class stmt_t{
    IF, // if 语句
    FuncDef, // 函数定义
    FunDec, // 函数声明
    VarDef, // 变量声明
    FOR, // for 语句
    Block, // 语句块
    Expr // 表达式语句
};


enum class type_e {
  VOIDType, //void 类型
  BasicType, // 基本类型
  PointerType, // 指针类型
  ReferenceType, // 引用类型
  FuncType // 函数类型
};