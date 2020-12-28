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

void holdReg(ValPtr *vp)
{
  holdReg(vp->_Ptr);
}
void unholdReg(ValPtr *vp)
{
  unholdReg(vp->_Ptr);
}

MemValue::MemValue(std::ostream &os, ValPtr *addr) : _Addr(addr)
{
  flag = Memory;
  if (_Addr->str() == "eax")
    _Addr->store(os);
  holdReg(0);
  if (_Addr->_Ptr->type() == Memory)
    _Addr->load(os);
  unholdReg(0);
  holdReg(_Addr);
}