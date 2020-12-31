
# 脚本使用方法
进入`code`文件夹
```
cd code
```
如果下面的操作不能报错找不到文件
确保这四个文件`./make.sh`、`./build/make.sh`、`./lexer-grammar.sh`、`./compile-run.sh`的换行符是`LF`而不是`CRLF`，可以在vscode中打开，查看右下角


使用如下命令，赋予脚本文件执行权限
```
sudo chmod -x ./make.sh
sudo chmod -x ./lexer-grammar.sh
sudo chmod -x ./compile-run.sh
```

使用时，按如下方法输入命令即可
```
./make.sh
```
```
./lexer-grammar.sh
```
```
./compile-run.sh
```
如果未能赋予执行权限，则需要按如下方法使用
```
/bin/bash ./make.sh
```
```
/bin/bash ./lexer-grammar.sh
```
```
/bin/bash ./compile-run.sh
```

# 使用方法
使用如下命令编译生成编译器
```
./make.sh
```
生成的编译器为./build/compiler

运行编译器
```
./build/compiler
```
将编译`./test.c`，并得到词法分析，语法分析和汇编代码，分别输出到`./output/lexer.output` `./output/grammar.output`，`./output/asm.output`中，可以使用下面的命令直接查看结果。

可以使用如下命令，直接编译`./test.c`并查看`./output/lexer.output`的词法分析输出和`./output/grammar.output`的语法分析树输出
```
./lexer-grammar.sh
```

使用如下命令，编译`./test.c`，查看`./output/asm.output`中的汇编代码，得到可执行文件并执行
```
./compile-run.sh
```
可以使用链接中测试用例，复制到`.test.c`中进行测试
https://www.yuque.com/docs/share/99d1a9cf-138b-49e5-8852-62a19628c4c0?# 《测试用例》


# 设计思路
在`/tree`目录下，是相关的抽象语法树节点的实现
## 抽象语法树

抽象语法树节点，分为语句节点`StmtNode`、表达式节点`ExprNode`、标识符节点`IDNode`、类型节点`TypeNode`和临时节点`TempNode`

不同的节点，由不同类型不同数量的子节点构成。

### 临时节点`TempNode`
其中临时节点`TempNode`唯一的作用，就是存储没有明确语义的节点以及记录一定的信息，以生成其他类型的节点

### 语句节点`StmtNode`
语句节点`StmtNode`是各种语句的节点，
包括表达式语句节点`ExprStmtNode`、if语句节点`IFStmt`、变量声明节点`VarDefStmt`、for语句节点`ForStmt`、while语句节点`WhileStmt`、语句块节点`BlockStmt`、函数声明节点`FuncDecStmt`、函数定义节点`FuncDefStmt`、结构体声明节点`StructDecStmt`、结构体定义节点`StructDefStmt`、返回语句节点`ReturnStmt`

### 表达式语句`ExprNode`
表达式语句`ExprNode`是各种表达式的节点，
包括一元运算表达式`OP1ExprNode`、二元运算表达式`OP2ExprNode`、结构体取成员表达式`MemberExprNode`、函数调用表达式`FunCallExprNode`、变量表达式`VarExprNode`和常量表达式`ConstExprNode`

表达式有各种属性，类型，是否为左值（可以取址），是否为常量

### 标识符节点`IDNode`
标识符节点`IDNode`，是存储标识符的节点，可以向符号表查找或注册一个标识符。可以获取标识符的类型，如变量名，函数名，结构体名。

### 类型节点`TypeNode`
类型节点`TypeNode`，是存储类型的节点。
类型有基本类型、函数类型、数组类型和指针类型。

其中函数类型、数组类型和指针类型是复合类型。

属性：需要的存储空间，函数类型和结构体类型还有标识符节点的属性。

并分别实现如下方法，是否可以用另一个类型的变量赋值，是否与另一个类型相同，是否可以当成bool类型，是否可以进行加减运算等

## 符号表
在`/symbol`文件夹下

符号表`SymbolTable`，用于记录一个作用域内的标识符。

符号表有父符号表。

为了生成子符号表的时候知道哪些符号属于子符号表，记录了每一个节点的第一个词法单元的序号，所有在某个序号之后的标识符节点属于子作用域，其他标识符属于父作用域。

## 目标代码生成

抽象语法树都有`output`方法，用于输出目标代码

其中表达式节点`output`调用`calValue`方法，并得到`ValPtr`类型的结构，此数据结果记录了表达式的值或地址的运算数



### `ValPtr`
在`/register`文件夹下

`ValPtr`是`Value`类型指针的包装类，有一个`Value`类型指针的属性

### `Value`

`Value`是用于记录不同类型的运算数的数据结构

`Value`有不同的类型，包括寄存器`RegValue`，内存`MemValue`，常量`ConstValue`，状态`StateValue`

寄存器`RegValue`记录了一个寄存器名，如`eax`,`ebx`等

状态`StateValue`是在进行了比较之后，可以进行条件跳转的状态，记录了比较结果为真/假时的跳转指令如`jg`，`je`等

内存`MemValue`记录了内存的地址，是一个`ValPtr`类型的属性

常量`ConstValue`记录了一个字符串和一个偏移，如`ebp-0x8`，`1`

`Value` 有一些基本方法

`str` 方法

得到可以输出到目标代码的字符串如

寄存器`RegValue`输出诸如`eax`,`ebx`等字符串

常量`ConstValue`输出诸如`1`,`ebp-0x8`等字符串

状态`StateValue`无法输出

内存`MemValue`输出`[...]`其中`...`是其他运算数的`str`输出

`load`方法 

`load`方法，是将运算数加载到寄存器，转化成寄存器运算数
一般是由`ValPtr`调用，将`ValPtr`存储的运算数的指针，替换成一个寄存器`RegValue`类型的运算数指针

`store`方法

同理，`store`方法是把一个运算数存到栈中，替换成转化成一个内存运算数的指针

`GoTo` 方法

`GoTo` 方法 是`ValPtr`的方法，输出一个跳转指令。
主要是针对，状态`StateValue`，状态`StateValue`记录了一次比较之后，判断结果为真/假时的跳转指令。如进行大于判断，则状态`StateValue`记录了大于跳转`jg`和小于等于跳转`jle`

同时寄存器`RegValue`也有对应的接口。
先与`0`来比较，为真/假时对应的跳转语句分别是`jne`和`je`

### 寄存器管理

每个寄存器会记录当前被哪一个`ValPtr`所占用

当寄存器不足时，选择一个`ValPtr`进行`store`操作，暂时存到栈中

实现`holdReg`，禁止对一个`ValPtr`进行`store`操作，表示，此寄存器处于不允许暂存到栈中的状态
使用`unholdReg`解除这种状态



