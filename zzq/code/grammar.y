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
//StructTable *structTable;
void yyerror(const char *str);
%}

%union{
  struct TypeNode *type;
  struct IDNode *id;
  struct ExprNode *expr;
  struct StmtNode *stmt;
  struct ASTNode *temp;
  struct TokenNode lexeme;
}
%locations
%define parse.error verbose

%right ASSIGNOP

%left <lexeme> OR
%left <lexeme>  AND
%left  <lexeme> SINGALAND
%left <lexeme>   RELOP
%left  <lexeme>  MINUS PLUS
%left  <lexeme>  STAR DIV MOD
%right  <lexeme>  POWER
%right <lexeme>  NOT
%left  <lexeme> LP RP LB RB
%nonassoc <lexeme>  LOWER_THAN_ELSE
%nonassoc  <lexeme> SEMI COMMA
%nonassoc <lexeme>  RETURN IF ELSE WHILE STRUCT GETMEMBER

%token <lexeme>  ERRID
%type <expr> INT
%type <type> TYPE
%type <id> ID
%token  <lexeme> INT1
%token  <lexeme> TYPE1
%token <lexeme>  ID1
%token  <lexeme> FOR
%token  <lexeme> LC RC

%type <type> Specifier
%type <expr> Exp 
%type <stmt> Stmt Def
%type <stmt> StructSpecifier
%type <stmt> StructDec
%type <temp> StmtList
%type <temp> ExtDefList ExtDecList
%type <stmt> ExtDef 
%type <temp> VarDec
%type <stmt> CompSt
%type <temp> StructDecList
%type <temp> Dec DecList Args ParamDec VarList FunDec 
%type <stmt> DecFor
%type <temp> Pointer
%%

/* 开始符号 */
Program: ExtDefList {
        thisFile.addChild($1);
    }
    ;

ExtDefList:
    ExtDef {
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$->addChild($1);
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
        // printf("get ExtDef\n");
        //int a, b, c;
        $$ = new VarDefStmt($1, $2);
		$$->setTokenCount($1);
        //$$ = new TempNode();
        //$$->addChild($1);
        //$$->addChild($2);
    }
    | Specifier SEMI {
    }
    | Specifier FunDec CompSt {
        //函数定义
        $$ = new FuncDefStmt($1,$2,$3);
		$$->setTokenCount($1);
    }
    | Specifier FunDec SEMI {
        //函数声明
        $$ = new FuncDecStmt($1,$2);
		$$->setTokenCount($1);
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
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$->addChild($1);
    }
    | ExtDecList COMMA VarDec {
        $1->addChild($3);
        $$ = $1;
    }
    ;

ID: ID1 {
        $$ = new IDNode($1.str);
		$$->setTokenCount($1);
    }
    ;

INT: INT1 {
        $$ = new ConstExprNode($1.str);
		$$->setTokenCount($1);
    }
    ;

TYPE: TYPE1 {
        $$ = TypeNode::getType($1.str);
        $$->setTokenCount($1);
    }
    ;

/* 数据类型 */
Specifier: TYPE {
        //类型本身：int
        $$ = $1;
    }
    | STRUCT ID {
        $$ = TypeNode::getType($2->ID);
        $$->setTokenCount($1);
    }
    ;

Pointer:
    Pointer STAR{
        $$ = $1;
        $$->addMsg("*");
    }
    |STAR {
        $$ = new TempNode();
        $$->addMsg("*");
        $$->setTokenCount($1);
    }
    ;

StructSpecifier: STRUCT ID LC StructDecList RC {
        //结构体类型定义：struct structname （ 结构体定义列表 ）
        $$ = new StructDefStmt($2, $4);
		$$->setTokenCount($1);
    }
    ;

StructDecList: StructDec {
        //结构体声明列表中只有一个声明
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$->addChild($1);
        //$$ = $1;
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
		$$->setTokenCount($1);
    }
    ;


/* 函数声明 */
FunDec: ID LP VarList RP {
        //：函数名 （ 参数列表 ）
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$->addChild($1);
        $$->addChild($3);
    }
    | ID LP RP {
        //：函数名 （ ）
        $$ = new TempNode();
		$$->setTokenCount($1);
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
		$$->setTokenCount($1);
        $$ -> addChild($1);
        $$ -> addChild($2);
    }
    | Specifier {
        //无具体意义void fun(int)
    }
    ;

/* 语句块 */
CompSt:
    LC StmtList RC {
        //：{ 语句块 }
        $$ = new BlockStmt($2);
		$$->setTokenCount($1);
    }
    | error RC {
        yyerrok;
    }
    ;

StmtList: 
	StmtList Stmt {
        //递归语句列表
        //只有一个语句
        if ($1 == NULL) 
            $1 = new TempNode();
        $1 -> addChild($2);
        $$ = $1;
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
        $$ = new ExprStmtNode($1);
		$$->setTokenCount($1);
    }
    ;

/*语句*/
Stmt: Exp SEMI {
        //表达式 ；
        $$ = new ExprStmtNode($1);
		$$->setTokenCount($1);
        
    }
    | Def SEMI {
        //定义语句 ；
            $$ = $1;
        
    }
    | STRUCT ID ID SEMI {
        //声明结构体变量：struct structname a ；
        $$ = new VarDefStmt(StructTypeNode::getStructType($2), $3);
		$$->setTokenCount($1);
    }
    | CompSt {
        //语句块
        $$ = $1;
    }
    | RETURN Exp SEMI {
        //return语句：return 表达式 ；
        $$ = new ReturnStmt($2);
		$$->setTokenCount($1);
    }
    | RETURN SEMI {
        //return语句：return ；
        $$ = new ReturnStmt(NULL);
		$$->setTokenCount($1);
    }
    | IF LP Exp RP Stmt {
        //条件语句：if （ 表达式 ）语句
        $$ = new IFStmt($3, $5, nullptr);
		$$->setTokenCount($1);
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE {
        //条件语句：if （ 表达式 ） 语句 else 语句
        $$ = new IFStmt($3, $5, $7);
		$$->setTokenCount($1);
    }
    | WHILE LP Exp RP Stmt {
        //while语句：while （ 表达式 ）语句
        $$ = new WhileStmt($3, $5);
		$$->setTokenCount($1);
    }
    | FOR LP SEMI SEMI RP Stmt {
        //无限循环的for语句：for （ ； ；）语句
        $$ = new ForStmt(NULL, NULL, NULL, $6);
		$$->setTokenCount($1);
    }
    | FOR LP DecFor SEMI SEMI RP Stmt {
        //：for（ 声明 ； ；） 语句
        $$ = new ForStmt($3, NULL, NULL, $7);
		$$->setTokenCount($1);
    }
    | FOR LP SEMI Exp SEMI RP Stmt {
        //：for （ ； 表达式 ；） 语句 
        $$ = new ForStmt(NULL, $4, NULL, $7);
		$$->setTokenCount($1);
    }
    | FOR LP SEMI SEMI Exp RP Stmt {
        //：for （ ； ； 表达式 ） 语句
        $$ = new ForStmt(NULL, NULL, $5, $7);
		$$->setTokenCount($1);
    }
    | FOR LP DecFor SEMI Exp SEMI Exp RP Stmt {
        //：for （ 声明 ； 表达式 ； 表达式 ） 语句
        $$ = new ForStmt($3, $5, $7, $9);
		$$->setTokenCount($1);
    }
    | FOR LP DecFor SEMI Exp SEMI RP Stmt {
        //：for （ 声明 ； 表达式 ； ） 语句
        $$ = new ForStmt($3, $5, NULL, $8);
		$$->setTokenCount($1);
    }
    | FOR LP DecFor SEMI SEMI Exp RP Stmt {
        //：for （ 声明 ； ； 表达式 ） 语句
        $$ = new ForStmt($3, NULL, $6, $8);
		$$->setTokenCount($1);
    }
    | FOR LP SEMI Exp SEMI Exp RP Stmt {
        //：for （ ； 表达式 ； 表达式 ） 语句
        $$ = new ForStmt(NULL, $4, $6, $8);
		$$->setTokenCount($1);
    }
    | error SEMI {
        //错误
        yyerrok;
    }
    ;

/* Local Definitions */ 
Def: Specifier DecList {
        $$ = new VarDefStmt($1, $2);
		$$->setTokenCount($1);
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
		$$->setTokenCount($1);
        $$ -> addChild($1);
        $$ -> addChild($3);
    }
    ;

Dec: VarDec {
        $$ = $1;
        // printf("get Dec\n");
    }
    | VarDec ASSIGNOP Exp {
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$ -> addChild($1);
        $$ -> addChild($3);
        $$ -> addMsg("=");
    }
    ;

/* Declarators */
/* 变量声明 */



VarDec:
    ID {
        $$ = $1;
    }
    |Pointer ID {
        $$ = $1;
		$$->setTokenCount($1);
        $$->addChild($2);
    }
    |VarDec LB INT RB {
        // $$ = $1;
        // $$->ArrMsg.push($3->toInt());
        $$ = new TempNode();
		$$->setTokenCount($1);
        $$->addChild($1);
        $$->addChild($3);
        $$->addMsg("[]");
    }
    ;


/* Expressions */
Exp:
    Exp ASSIGNOP Exp {
        $$ = new OP2ExprNode(op_e::Assignop, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp AND Exp {
        $$ = new OP2ExprNode(op_e::And, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp OR Exp {
        $$ = new OP2ExprNode(op_e::Or, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp RELOP Exp {
        $$ = new OP2ExprNode(op_e::Relop, $2.str, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp PLUS Exp {
        $$ = new OP2ExprNode(op_e::Plus, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp MINUS Exp {
        $$ = new OP2ExprNode(op_e::Minus, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp STAR Exp {
        $$ = new OP2ExprNode(op_e::Times, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp DIV Exp {
        $$ = new OP2ExprNode(op_e::Div, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp MOD Exp {
        $$ = new OP2ExprNode(op_e::Mod, $1, $3);
		$$->setTokenCount($1);
    }
    | Exp POWER Exp {
        $$ = new OP2ExprNode(op_e::Power, $1, $3);
		$$->setTokenCount($1);
    }
    | LP Exp RP {
        $$ = $2;
    }
    | MINUS Exp {
        $$ = new OP1ExprNode(op_e::Minus, $2);
		$$->setTokenCount($1);
    }
    | NOT Exp {
        $$ = new OP1ExprNode(op_e::Not, $2);
		$$->setTokenCount($1);
    }
    | SINGALAND ID {
        $$ = new OP1ExprNode(op_e::SignalAnd, new VarExprNode($2));
		$$->setTokenCount($1);
    }
    | ID LP Args RP {
        $$ = new FunCallExprNode($1, $3);
		$$->setTokenCount($1);
    }
    | ID LP RP {
        $$ = new FunCallExprNode($1, nullptr);
		$$->setTokenCount($1);
    }
    | Exp LB Exp RB {
        $$ = new OP2ExprNode(op_e::GetArrayValue, $1, $3);
		$$->setTokenCount($1);
    }
    | ID {
        $$ = new VarExprNode($1);
		$$->setTokenCount($1);
    }
    | ID LB Exp RB {
        VarExprNode *t = new VarExprNode($1);
		//$$->setTokenCount($1);
        $$ = new OP2ExprNode(op_e::GetArrayValue, t, $3);
		$$->setTokenCount($1);
    }
    | ID GETMEMBER ID {
        $$ = new OP2ExprNode(op_e::GetMember, new VarExprNode($1), new VarExprNode($3));
		$$->setTokenCount($1);
    }
    | INT {
        $$ = $1;
    }
    | STAR ID {
        $$ = new OP1ExprNode(op_e::GetValue, new VarExprNode($2));
		$$->setTokenCount($1);
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
		$$->setTokenCount($1);
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


void print_word_list();
void test_lexer()
{
    FILE* file = fopen("test.c", "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    print_word_list();
    thisFile.print(0);
}

/*
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
*/