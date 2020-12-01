

#include "symbol/SymbolTable.h"
#include "tree/IDNode.h"
#include "tree/ExprNode.h"
#include "tree/ProgramNode.h"
#include "tree/FileNode.h"
#include "tree/StmtNode.h"
#include "tree/TypeNode.h"
#include "tree/TempNode.h"


struct TokenNode{
    const char *str;
    int tokenCount;
};

void init();