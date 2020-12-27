#include <iostream>
#include "TempValue.h"
using namespace std;
struct RegValue;

extern std::ostream &theOs;

constexpr int regSize = 4;

const char *registers[regSize]{"eax", "ebx", "ecx", "edx"};

ValPtr *owners[regSize]{nullptr, nullptr, nullptr, nullptr};

bool held[regSize]{false, false, false, false};

void checkIndex(int i)
{
  if (i < 0 || i > regSize - 1)
  {
    cout << "使用错误的寄存器编号";
    exit(1);
  }
}

bool hasOwner(int i)
{
  return owners[i] && owners[i]->isRegister();
}
void freeReg(int i)
{
  owners[i] = nullptr;
}
void storeReg(int i)
{
  checkIndex(i);
  if (held[i])
    my_error("store held");
  if (hasOwner(i))
  {
    owners[i]->store(theOs);
    owners[i] = nullptr;
  }
}

void holdReg(int i)
{
  held[i] = true;
}
void unholdReg(int i)
{
  held[i] = false;
}

void getReg(int i, ValPtr *_Who)
{
  checkIndex(i);
  storeReg(i);
  owners[i] = _Who;
}

int getReg(ValPtr *_Who)
{
  for (int i = 0; i < regSize; ++i)
  {
    if (!hasOwner(i) && !held[i])
    {
      getReg(i, _Who);
      return i;
    }
  }
  for (int i = regSize - 1; i >= 0; --i)
    if (!held[i])
    {
      getReg(i, _Who);
      return i;
    }
  my_error("all held");
  return 1;
}

int nextlable()
{
  static int i = 0;
  return i++;
}