%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "include.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
extern int yylineno;
extern FileNode thisFile;
StructTable *structTable;
void yyerror(const char *str);
%}

%union{
  TypeNode *type;
  IDNode *id;
  ExprNode *expr;
  StmtNode *stmt;
  ASTNode *temp;
  const char *str;
}
%locations
%define parse.error verbose

%right ASSIGNOP

%left OR
%left AND
%left SINGALAND
%left <str>  RELOP
%left  MINUS PLUS
%left  STAR DIV MOD
%right  POWER
%right NOT
%left LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE STRUCT GETMEMBER

%token ERRID
%type <expr> INT
%type <type> TYPE
%type <id> ID
%token <str> INT1
%token <str> TYPE1
%token <str> ID1
%token FOR
%token LC RC

%type <type> Specifier
%type <expr> Exp 
%type <stmt> Stmt Def
%type <stmt> StructSpecifier
%type <stmt> StructDec
%type <temp> StmtList
%type <temp> ExtDefList ExtDef ExtDecList
%type <temp> VarDec
%type <temp> CompSt
%type <temp> StructDecList
%type <temp> Dec DecList Args ParamDec VarList FunDec DecFor
%%

/* 开始符号 */
Program: ExtDefList {
        thisFile.root = $1;
    }
    ;

ExtDefList:
    ExtDef {
        $$ = $1;
    }
    | ExtDefList ExtDef {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            if ($2 != NULL) {
                $1->addChild($2);
            }
            $$ = $1;
        }
    }
    ;

ExtDef: Specifier ExtDecList SEMI {
        //int a, b, c;
        $$ = new TempNode();
        $$->addChild($1);
        $$->addChild($2);
    }
    | Specifier SEMI {
    }
    | Specifier FunDec CompSt {
        //函数定义
        $$ = new FuncDefStmt($1,$2,$3);
    }
    | Specifier FunDec SEMI {
        //函数声明
        $$ = new FuncDecStmt($1,$2);
    }
    | StructSpecifier SEMI {
        //结构体定义
        $$ = $1;
    }
    | error SEMI {
        yyerrok;
        $$ = NULL;
    }
    ;

ExtDecList: VarDec {
        $$ = $1;
    }
    | ExtDecList COMMA VarDec {
        $1->addChild($3);
        $$ = $1;
    }
    ;

ID: ID1 {
        $$ = new IDNode($1);
    }
    ;

INT: INT1 {
        $$ = new ConstExprNode($1);
    }
    ;

/* 数据类型 */
Specifier: TYPE {
        //类型本身：int
        $$ = $1;
    }
    | TYPE STAR {
        //指针：int *
        $$ = new PointerTypeNode($1);
    }
    ;

StructSpecifier: STRUCT ID LC StructDecList RC {
        //结构体类型定义：struct structname （ 结构体定义列表 ）
        $$ = new StructDefStmt($2, $4);
    }
    ;

StructDecList: StructDec {
        //结构体声明列表中只有一个声明
        $$ = $1;
    }
    | StructDecList StructDec {
        //递归声明结构
        $1->addChild($2);
        $$ = $1;
    }
    ;

StructDec: Specifier ID SEMI {
        //：结构体类型 id ；
        $$ = new VarDefStmt($1, $2);
    }
    ;

/* Declarators */
/* 变量声明 */
VarDec: ID {
        //变量：varname
        $$ = $1;
    }
    | ID LB INT RB {
        //变量数组：varname [ 数字 ]
        $$ = new TempNode();
        $$->addChild($1);
        $$->addChild($3);
        $$->addMsg("[]");
    }
    ;

/* 函数声明 */
FunDec: ID LP VarList RP {
        //：函数名 （ 参数列表 ）
        $$ = new TempNode();
        $$->addChild($1);
        $$->addChild($2);
    }
    | ID LP RP {
        //：函数名 （ ）
        $$ = new TempNode();
        $$->addChild($1);
    }
    ;

VarList: VarList COMMA ParamDec {
        //递归参数列表：参数列表 ， 参数声明
        $1 -> addChild($3);
        $$ = $1;
    }
    | ParamDec {
        //参数声明比如：int 变量名
        $$ = $1;
    }
    ;

ParamDec: Specifier ID {
        $$ = new TempNode();
        $$ -> addChild($1, $2);
    }
    | Specifier {
        //无具体意义void fun(int)
    }
    ;

/* 语句块 */
CompSt:
    LC StmtList RC {
        //：{ 语句块 }
        $ = new BlockStmt($2);
    }
    | error RC {
        yyerrok;
    }
    ;

StmtList: 
	StmtList Stmt {
        //递归语句列表
        //只有一个语句
        if ($1 == NULL) {
            $$ = $2;
        } else {
            $1 -> addChild($2);
            $$ = $1;
        }
    }
    | {
        $$ = NULL;
    }
    ;

DecFor:
    Def {
        //
        $$ = $1;
    }
    | Exp {
        //
        $$ = $1;
    }
    ;

/*语句*/
Stmt: Exp SEMI {
        //表达式 ；{
            $$ = new ExprStmtNode($1);
        }
    }
    | Def SEMI {
        //定义语句 ；{
            $$ = $1;
        }
    }
    | STRUCT ID ID SEMI {
        //声明结构体变量：struct structname a ；
        StructTypeNode *t = StructTypeNode::getStructType($2);
        $$ = new VarDefStmt(t, $3);
    }
    | CompSt {
        //语句块
        $$ = $1;
    }
    | RETURN Exp SEMI {
        //return语句：return 表达式 ；
        $$ = new RetrunStmt($2);
    }
    | RETURN SEMI {
        //return语句：return ；
        $$ = new RetrunStmt(NULL);
    }
    | IF LP Exp RP Stmt {
        //条件语句：if （ 表达式 ）语句
        $$ = new IFStmt($3, $5);
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE {
        //条件语句：if （ 表达式 ） 语句 else 语句
        $$ = new IFStmt($3, $5, $7);
    }
    | WHILE LP Exp RP Stmt {
        //while语句：while （ 表达式 ）语句
        $$ = new WhileStmt($3, $5);
    }
    | FOR LP SEMI SEMI RP Stmt {
        //无限循环的for语句：for （ ； ；）语句
        $$ = new ForStmt(NULL, NULL, NULL, $6);
    }
    | FOR LP DecFor SEMI SEMI RP Stmt {
        //：for（ 声明 ； ；） 语句
        $$ = new ForStmt($3, NULL, NULL, $7);
    }
    | FOR LP SEMI Exp SEMI RP Stmt {
        //：for （ ； 表达式 ；） 语句 
        $$ = new ForStmt(NULL, $4, NULL, $7);
    }
    | FOR LP SEMI SEMI Exp RP Stmt {
        //：for （ ； ； 表达式 ） 语句
        $$ = new ForStmt(NULL, NULL, $5, $7);
    }
    | FOR LP DecFor SEMI Exp SEMI Exp RP Stmt {
        //：for （ 声明 ； 表达式 ； 表达式 ） 语句
        $$ = new ForStmt($3, $5, $7, $9);
    }
    | FOR LP DecFor SEMI Exp SEMI RP Stmt {
        //：for （ 声明 ； 表达式 ； ） 语句
        $$ = new ForStmt($3, $5, NULL, $8);
    }
    | FOR LP DecFor SEMI SEMI Exp RP Stmt {
        //：for （ 声明 ； ； 表达式 ） 语句
        $$ = new ForStmt($3, NULL, $6, $8);
    }
    | FOR LP SEMI Exp SEMI Exp RP Stmt {
        //：for （ ； 表达式 ； 表达式 ） 语句
        $$ = new ForStmt(NULL, $4, $6, $8);
    }
    | error SEMI {
        //错误
        yyerrok;
    }
    ;

/* Local Definitions */ 
Def: Specifier DecList {
        VarDefStmt* t = new VarDefStmt($1, $2);
        $$ = t;
    }
    | error SEMI {
        yyerrok;
    }
    ;

DecList: Dec {
        $$ = $1;
    }
    | Dec COMMA DecList {
        //a , 声明列表
        $$ = new TempNode();
        $$ -> addChild($1, $3);
    }
    ;

Dec: VarDec {
        $$ = $1;
    }
    | VarDec ASSIGNOP Exp {
        $$ = new TempNode();
        $$ -> addChild($1, $3);
    }
    ;

/* Expressions */
Exp:
    Exp ASSIGNOP Exp {
        $$ = new OP2ExprNode(op_e::Assignop, $1, $3);
    }
    | Exp AND Exp {
        $$ = new OP2ExprNode(op_e::And, $1, $3);
    }
    | Exp OR Exp {
        $$ = new OP2ExprNode(op_e::Or, $1, $3);
    }
    | Exp RELOP Exp {
        $$ = new OP2ExprNode(op_e::Relop, $2, $1, $3);
    }
    | Exp PLUS Exp {
        $$ = new OP2ExprNode(op_e::Plus, $1, $3);
    }
    | Exp MINUS Exp {
        $$ = new OP2ExprNode(op_e::Minus, $1, $3);
    }
    | Exp STAR Exp {
        $$ = new OP2ExprNode(op_e::Times, $1, $3);
    }
    | Exp DIV Exp {
        $$ = new OP2ExprNode(op_e::Div, $1, $3);
    }
    | Exp MOD Exp {
        $$ = new OP2ExprNode(op_e::Mod, $1, $3);
    }
    | Exp POWER Exp {
        $$ = new OP2ExprNode(op_e::Power, $1, $3);
    }
    | LP Exp RP {
        $$ = $1;
    }
    | MINUS Exp {
        $$ = new OP1ExprNode(op_e::Minus, $2);
    }
    | NOT Exp {
        $$ = new OP1ExprNode(op_e::Not, $2);
    }
    | SINGALAND ID {
        $$ = new OP1ExprNode(op_e::SignalAnd, $2);
    }
    | ID LP Args RP {
        $$ = new FunCallExprNode($1, $2);
    }
    | ID LP RP {
        $$ = new FunCallExprNode($1, NUll);
    }
    | Exp LB Exp RB {
        $$ = new OP2ExprNode(op_e::GetArrayValue, $1, $3);
    }
    | ID {
        $$ = new VarExprNode($1);
    }
    | ID LB Exp RB {
        VarExprNode *t = new VarExprNode($1);
        $$ = new OP2ExprNode(op_e::GetArrayValue, t, $3);
    }
    | ID GETMEMBER ID {
        $$ = new OP2ExprNode(op_e::GetMember, new VarExprNode($1), new VarExprNode($3));
    }
    | INT {
        $$ = $1;
    }
    | STAR ID {
        $$ = new OP1ExprNode(op_e::GetValue, $2);
    }
    | error RP {
        yyerrok;
    }
    ;
    
Args: Args COMMA Exp {
        $1 -> addChild($3);
        $$ = $1;
    }
    | Exp {
        $$ = new TempNode();
        $$ -> addChild($1);
    }
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
