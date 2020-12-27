#include "TempValue.h"

ConstValue *newConstValue(std::string base, int off)
{
  return new ConstValue(base, off);
}

MemValue *newMemValue(std::ostream &os, ValPtr *addr)
{
  return new MemValue(os, addr);
}

StateValue *newStateValue(std::string trueGo, std::string flaseGo)
{
  return new StateValue(trueGo, flaseGo);
}

RegValue *newRegValue(ValPtr *v, int i)
{
  return new RegValue(v, i);
}

ValPtr *newValPtr(Value *_Ptr)
{
  return new ValPtr(_Ptr);
}