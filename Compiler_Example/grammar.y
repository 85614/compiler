%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "../common/trees.h"
#include "../common/util/InterMediate.h"
#include "../common/util/AsmGenerator.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
extern int yylineno;
AbstractASTNode* root;
StructTable *structTable;
void yyerror(const char *str);
%}

%union {
	AbstractASTNode* ast;
    char* str;
}
%locations
%define parse.error verbose

%right ASSIGNOP

%left <ast> OR
%left <ast> AND
%left <ast> SINGALAND
%left <str> RELOP
%left <ast> MINUS PLUS
%left <ast> STAR DIV MOD
%left <ast> POWER
%right <ast> NOT
%left LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%token ERRID
%token <str> INT
%token <str> TYPE
%token <str> ID
%token FOR
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE STRUCT GETMEMBER
%token LC RC
%type <ast> VarDec 
%type <str> Specifier
%type <ast> ExtDefList ExtDef ExtDecList
%type <ast> Exp CompSt
%type <ast> StmtList Stmt Dec DecList Def
%type <ast> Args ParamDec VarList FunDec DecFor
%type <ast> StructSpecifier StructDecList StructDec
%%

/* 开始符号 */
Program: ExtDefList 
    ;

/*
ExtDefList:
    ExtDef 
    | ExtDefList ExtDef 
    ;

ExtDef: Specifier ExtDecList SEMI 
    | Specifier SEMI 
    | Specifier FunDec CompSt {
        //函数定义

    }
    | Specifier FunDec SEMI 
    | StructSpecifier SEMI 
    | error SEMI 
    ;

ExtDecList: VarDec 
    | ExtDecList COMMA VarDec
    ;

/* 数据类型 */
Specifier: TYPE {
        //类型本身：int
    }
    | TYPE STAR {
        //指针：int *
    }
    ;

StructSpecifier: STRUCT ID LC StructDecList RC {
        //结构体类型定义：struct structname （ 结构体声明列表 ）
    }
    ;

StructDecList: StructDec {
        //结构声明
    }
    | StructDecList StructDec {
        //递归声明结构
    }
    ;

StructDec: Specifier ID SEMI {
        //：int id ；
    }
    ;

/* Declarators */
/* 变量声明 */
VarDec: ID {
        //变量：varname
    }
    | ID LB INT RB {
        //变量数组：varname [ 数字 ]
    }
    ;

/* 函数声明 */
FunDec: ID LP VarList RP {
        //：函数名 （ 参数列表 ）
    }
    | ID LP RP {
        //：函数名 （ ）
    }
    ;

VarList: VarList COMMA ParamDec {
        //递归参数列表：参数列表 ， 参数声明
    }
    | ParamDec {
        //参数声明比如：int 变量名
    }
    ;

ParamDec: Specifier ID 
    | Specifier 
    ;

/* 语句块 */
CompSt:
    LC StmtList RC {
        //：{ 语句列表 }
    }
    | error RC 
    ;

StmtList: 
	StmtList Stmt {
        //递归语句列表
    }
    | 
    ;

DecFor:
    Def {
        //
    }
    | Exp {
        //
    }
    ;

/*语句*/
Stmt: Exp SEMI {
        //表达式 ；
    }
    | Def SEMI {
        //定义 ；
    }
    | STRUCT ID ID SEMI {
        //声明结构体变量：struct structname a ；
    }
    | CompSt {
        //
    }
    | RETURN Exp SEMI {
        //return语句：return 表达式 ；
    }
    | RETURN SEMI {
        //return语句：return ；
    }
    | IF LP Exp RP Stmt {
        //条件语句：if （ 表达式 ）语句
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE {
        //条件语句：if （ 表达式 ） 语句 else 语句
    }
    | WHILE LP Exp RP Stmt {
        //while语句：while （ 表达式 ）语句
    }
    | FOR LP SEMI SEMI RP Stmt {
        //无限循环的for语句：for （ ； ；）语句
    }
    | FOR LP DecFor SEMI SEMI RP Stmt {
        //：for（ 声明 ； ；） 语句
    }
    | FOR LP SEMI Exp SEMI RP Stmt {
        //：for （ ； 表达式 ；） 语句 
    }
    | FOR LP SEMI SEMI Exp RP Stmt {
        //：for （ ； ； 表达式 ） 语句
    }
    | FOR LP DecFor SEMI Exp SEMI Exp RP Stmt {
        //：for （ 声明 ； 表达式 ； 表达式 ） 语句
    }
    | FOR LP DecFor SEMI Exp SEMI RP Stmt {
        //：for （ 声明 ； 表达式 ； ） 语句
    }
    | FOR LP DecFor SEMI SEMI Exp RP Stmt {
        //：for （ 声明 ； ； 表达式 ） 语句
    }
    | FOR LP SEMI Exp SEMI Exp RP Stmt {
        //：for （ ； 表达式 ； 表达式 ） 语句
    }
    | error SEMI {
        //错误
    }
    ;

/* Local Definitions */
/*  *//
Def: Specifier DecList 
    | error SEMI 
    ;

DecList: Dec 
    | Dec COMMA DecList 
    ;

Dec: VarDec 
    | VarDec ASSIGNOP Exp 
    ;

/* Expressions */
Exp:
    Exp ASSIGNOP Exp {
        $$ = new OP2ExprNode("=", $1, $3);
    }
    | Exp AND Exp 
    | Exp OR Exp 
    | Exp RELOP Exp 
    | Exp PLUS Exp 
    | Exp MINUS Exp 
    | Exp STAR Exp 
    | Exp DIV Exp 
    | Exp MOD Exp 
    | Exp POWER Exp 
    | LP Exp RP 
    | MINUS Exp 
    | NOT Exp 
    | SINGALAND ID 
    | ID LP Args RP 
    | ID LP RP 
    | Exp LB Exp RB 
    | ID 
    | ID LB Exp RB 
    | ID GETMEMBER ID 
    | INT 
    | STAR ID 
    | error RP 
    ;
    
Args: Args COMMA Exp 
    | Exp 
    ;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: At line %d. %s\n", yylineno, s);
	exit(1);
}

std::string replaceExtName(char* fileName) {
    int dotIndex = 0;
    int nameLength = strlen(fileName);
    for (int i = nameLength - 1; i >= 0; i--) {
        if (fileName[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    char* buf = new char[dotIndex];
    strncpy(buf, fileName, dotIndex);
    std::string rev(buf);
    rev += ".asm";
    return rev;
}

int main(int argc,char* argv[])
{
    InterMediate* im;
    bool flag_print_ast = false;
    bool flag_print_ir = false;
    bool flag_print_asm = false;
    char* filename = NULL;
    if (argc == 1) {
        printf("Error! Please input file name!\n");
        printf("Usage: parser [-t] [-i] [-a] [-d]\n");
        printf("  -t  print the abstract syntax tree (AST)\n");
        printf("  -i  print IR code\n");
        printf("  -a  print asm code\n");
        printf("  -d  debug mode print all\n");
        return -1;
    } else if (argc >= 2) {
        for (int i=1; i<argc; i++) {
            if (*argv[i] != '-') {
                if (filename == NULL) filename = argv[i];
            }
            else if (strcmp(argv[i], "-t") == 0) flag_print_ast = true;
            else if (strcmp(argv[i], "-i") == 0) flag_print_ir = true;
            else if (strcmp(argv[i], "-a") == 0) flag_print_asm = true;
            else if (strcmp(argv[i], "-d") == 0) {
                flag_print_ast = true;
                flag_print_ir = true;
                flag_print_asm = true;
            }
            else printf("Invalid parameter \"%s\"\n", argv[i]);
        }
    }
    FILE* file = fopen(filename, "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    if (flag_print_ast) {
        root->printTree();
    }
    im = new InterMediate((RootASTNode *)root, structTable);
    im->Generate(im->getRoot(), im->getTable());
    if (flag_print_ir) {
        im->printQuads();
    }
    AsmGenerator* asmgenerator = new AsmGenerator(im->getQuads(), im->getTempVars(), im->getTable(), im->getFuncTable());
    asmgenerator->generate();
    if (flag_print_asm) {
        std::cout << asmgenerator->getAsmCode();
    }

    std::string outFileName = replaceExtName(filename);
    std::ofstream outasm(outFileName);
    outasm << asmgenerator->getAsmCode();
    return 0;
}
