#include "symbol/SymbolTable.h"
#include "tree/IDNode.h"
#include "tree/ExprNode.h"
#include "tree/ProgramNode.h"
#include "tree/FileNode.h"
#include "tree/StmtNode.h"
#include "tree/TypeNode.h"
#include "tree/TempNode.h"

union u{
  IDNode *id;
  ExprNode *expr;
  ProgramNode *program;
  FileNode *file;
  StmtNode *stmt;
  TypeNode *type;
  TempNode temp; // 保留父节点和左节点
};



int main(){
  printf("",
  1,2,3
  );

  return 0;
}


// 测试 enum class
// enum class e1{A};
// enum class e2{A};

// template<e1 v>
// struct test1{};


// int main(){
//     test1<e2::A>();    
// }

// 测试 enum class ~