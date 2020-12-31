#include "include.h"

void run_yyparse();
void output_asm();
void output_lexer();
void output_grammar();

const char *lexer_output = "./output/lexer.output";     // 词法分析输出文件
const char *grammar_output = "./output/grammar.output"; // 语法分析输出文件
const char *asm_output = "./output/asm.output";         // asm输出文件
const char *input_file = "./test.c";

int main(int argc, char *argv[])
{
   init();
   run_yyparse();
   output_lexer();
   output_grammar();
   output_asm();
}
