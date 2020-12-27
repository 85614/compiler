#pragma once
#include <iostream>
#include <iomanip>
#include <string>

#include "register.h"
#include "../base.h"
using std::cout;
using std::endl;

extern int stack_esp;

struct Value;
struct MemValue;
struct ConstValue;
struct StateValue;
struct RegValue;
struct ValPtr;
ValPtr *newValPtr(Value *_Ptr);
ConstValue *newConstValue(std::string base, int off);

MemValue *newMemValue(std::ostream &os, ValPtr *addr);

StateValue *newStateValue(std::string trueGo, std::string flaseGo);
RegValue *newRegValue(ValPtr *ptr, int i);
struct Value
{

  enum
  {
    Memory = 0,
    Const = 1,
    Register = 2,
    State = 3,
    TypeMask = 3,

  };

  int flag = 0;

  int type() { return flag & 0b11; }

  virtual std::string str(int off = 0)
  {
    notImplement("str");
    return "";
  }
  // 暂存
  virtual Value *store(std::ostream &os, ValPtr *owner)
  {
    notImplement("store");
    return 0;
  }
  // 存入寄存器
  virtual Value *load(std::ostream &os, ValPtr *owner, int index = -1)
  {
    if (index == -1)
      index = getReg(owner);
    else
      getReg(index, owner);
    const char *reg = registers[index];
    os << "    mov " << reg << ", " << str() << "\n";
    return (Value *)newRegValue(owner, index);
  }
  // 判断，以供跳转
  virtual Value *judge(std::ostream &os, ValPtr *owner)
  {
    os << "    cmp " << str() << ", 0\n";
    return (Value *)newStateValue("je", "jne");
  }
  // true 跳转
  virtual void trueGoTo(std::ostream &os, int label)
  {
    notImplement("store");
  }
  // false 跳转
  virtual void falseGoTo(std::ostream &os, int label)
  {
    notImplement("store");
  }

  virtual ~Value() {}
};

struct RegValue : public Value
{
  // 存寄存器编号
  int index;
  RegValue(ValPtr *ptr, int i) : index(i)
  {
    if (i == -1)
      index = getReg(ptr);
    else
      getReg(i, ptr);
    flag = Register;
  }
  ~RegValue() { freeReg(index); }
  // 暂存
  // 存入寄存器 什么也不做
  // 判断
  // true 跳转
  // false 跳转
  virtual std::string str(int off = 0) override { return registers[index] + toSignedHex(off); }
  // 暂存
  virtual Value *store(std::ostream &os, ValPtr *owner) override
  {

    os << "    push " << registers[index] << "\n";
    stack_esp -= 4;
    Value *addr = (Value *)newConstValue("ebp", stack_esp);
    auto addrPtr = newValPtr(addr);
    freeReg(index);
    return (Value *)newMemValue(os, addrPtr);
  }
  // 存入寄存器
  virtual Value *load(std::ostream &os, ValPtr *owner, int _Index) override
  {

    if (_Index == this->index || _Index == -1)
      return this;
    my_error("should call ValPtr::load not this");
    return nullptr;
  }
  // 判断，以供跳转
  virtual Value *judge(std::ostream &os, ValPtr *owner) override
  {
    os << "    cmp " << str() << ", 0\n";
    return (Value *)newStateValue("je", "jne");
  }
  // true 跳转
  virtual void trueGoTo(std::ostream &os, int label) override
  {
    os << "    cmp " << registers[index] << ", 0\n";
    os << "    jne goto" << label << '\n';
  }
  // false 跳转
  virtual void falseGoTo(std::ostream &os, int label) override
  {
    os << "    cmp " << registers[index] << ", 0\n";
    os << "    je goto" << label << '\n';
  }
};
struct ConstValue : public Value
{
  std::string base;
  int off;

  // 暂存 什么也不做
  // 存入寄存器
  // 判断
  // true 跳转
  // false 跳转
  ConstValue(std::string _Base, int _Off) : base(_Base), off(_Off)
  {
    flag = Const;
  }
  virtual std::string str(int _Off = 0) override
  {
    if (off == 0)
      return base;
    return base + toSignedHex(this->off + _Off);
  }

  // 暂存
  // virtual Value *store(std::ostream &os, ValPtr *owner) override {}
  // 存入寄存器

  virtual Value *load(std::ostream &os, ValPtr *owner, int _Index) override
  {
    
    int oldoff = off;
    off = 0;
    auto ans = Value::load(os, owner, _Index);
    if (oldoff)
    {
      if (oldoff > 0)
        os << "    add " << ans->str() << ", " << toHex(oldoff) << "\n";
      else
        os << "    sub " << ans->str() << ", " << toHex(-oldoff) << "\n";
    }
    
    return ans;
  }
};
// 判断，以供跳转
// virtual Value *judge(std::ostream &os, ValPtr *owner) override {}
// true 跳转
// virtual void trueGoTo(std::ostream &os, int label) override {}
// false 跳转
// virtual void falseGoTo(std::ostream &os, int label) override {}

struct StateValue : public Value
{

  // 记录 true 跳转的方式和false跳转的方式
  std::string trueGo;
  std::string falseGo;

  // 暂存
  // 存入寄存器
  // 判断
  // true 跳转
  // false 跳转
  // 暂存
  // virtual Value *store(ValPtr *owner) override {}
  // 存入寄存器
  StateValue(std::string _True, std::string _False) : trueGo(_True), falseGo(_False)
  {
    flag = State;
  }

  virtual Value *load(std::ostream &os, ValPtr *owner, int index) override
  {
    if (index = -1)
      index = getReg(owner);
    const char *reg = registers[index];
    int label = nextlable();
    os << "    mov " << reg << ", 0\n";
    this->falseGoTo(os, label);
    os << "    mov " << reg << ", 1\n";
    os << "goto" << label << ":\n";
    return new RegValue(owner, index);
  }
  // 判断，以供跳转
  virtual Value *judge(std::ostream &os, ValPtr *owner) override
  {
    return this;
  }
  // true 跳转
  virtual void trueGoTo(std::ostream &os, int label) override
  {
    os << "    " << trueGo << " goto" << label << "\n";
  }
  // false 跳转
  virtual void falseGoTo(std::ostream &os, int label) override
  {
    os << "    " << falseGo << " goto" << label << "\n";
  }
};

/*
 * 存在寄存器上
 * 存在内存上
 * 是常量
 * 
 */

struct ValPtr
{
  Value *_Ptr = nullptr;
  bool _IsRef;
  ValPtr(Value *ptr, bool isRef = false) : _Ptr(ptr), _IsRef(isRef) {}

  std::string str(int off = 0)
  {
    if (_Ptr->type() == Value::State)
      load(theOs);
    if (_Ptr)
      return _Ptr->str(off);
    return "";
  }
  ValPtr &newRegValue(int i = -1)
  {
    if (!_Ptr)
    {
      _Ptr = (Value *)::newRegValue(this, i);
    }
    else
    {
      my_error("已经有_Ptr");
    }
    return *this;
  }
  bool isConst(){
    return _Ptr->type() == Value::Const;
  }
  bool isMemory()
  {
    return _Ptr->type() == Value::Memory;
  }
  bool isRegister()
  {
    return _Ptr->type() == Value::Register;
  }
  bool isState()
  {
    return _Ptr->type() == Value::State;
  }
  bool swapTrueFalse = false;

  void GoTo(std::ostream &os, int label, bool test)
  {
    if (_Ptr->type() == Value::Memory || _Ptr->type() == Value::Const)
      load(os);
    if (test == swapTrueFalse) // false false / true true
      _Ptr->falseGoTo(os, label);
    else
      _Ptr->trueGoTo(os, label);
  }

  void swapTF()
  {
    swapTrueFalse = !swapTrueFalse;
  }

  void judge(std::ostream &os)
  {
    if (_Ptr)
    {
      _Ptr->judge(os, this);
    }
  }
  void store(std::ostream &os)
  {
    if (_Ptr)
    {
      auto old = _Ptr;
      _Ptr = _Ptr->store(os, this);
      if (old != _Ptr)
        delete old;
    }
  }

  void load(std::ostream &os, int index = -1)
  {
    if (_Ptr)
    {
      auto old = _Ptr;
      if (index == -1)
        _Ptr = _Ptr->load(os, this);
      else
      {
        if (isRegister() && ((RegValue *)_Ptr)->index != index)
        {
          auto newPtr = ::newRegValue(this, index);
          os << "    mov " << newPtr->str() << ", " << _Ptr->str();
          _Ptr = newPtr;
        }
        else
          _Ptr = _Ptr->load(os, this);
      }
      if (old != _Ptr)
        delete old;
    }
  }
  bool hasOff()
  {
    return _Ptr->type() == Value::Const && ((ConstValue *)_Ptr)->off;
  }
  ~ValPtr()
  {
    delete _Ptr;
  }
};

struct MemValue : public Value
{
  ValPtr *_Addr;
  // 地址用一个父类指针存

  // 暂存 什么也不做
  // 存入寄存器
  // 判断
  // true 跳转
  // false 跳转
  MemValue(std::ostream &os, ValPtr *addr) : _Addr(addr)
  {
    flag = Memory;
    if (_Addr->_Ptr->type() == Memory)
      _Addr->load(os);
  }
  ~MemValue()
  {
    delete _Addr;
  }

  virtual std::string str(int off = 0) override
  {
    if (off)
      my_error("Memory Value str off is not 0");
    return '[' + _Addr->str() + ']';
  }
  // 暂存
  virtual Value *store(std::ostream &os, ValPtr *owner) override { return this; }
  // 存入寄存器
  virtual Value *load(std::ostream &os, ValPtr *owner)
  {
    int index = getReg(owner);
    const char *reg = registers[index];
    os << "    mov " << reg << ", [" << _Addr->str() << "]\n";
    return new RegValue(owner, index);
  }
  // 判断，以供跳转
  // virtual Value *judge(std::ostream &os, ValPtr *owner) { notImplement("judge"); }
  // true 跳转
  // virtual void trueGoTo(std::ostream &os, int label) { notImplement("trueGoTo"); }
  // false 跳转
  // virtual void falseGoTo(std::ostream &os, int label) { notImplement("falseGoto"); }
};

inline ValPtr *newRegValPtr(int index = -1)
{
  return &(new ValPtr(0))->newRegValue(index);
}

inline int getRegIndex(Value *v)
{
  if (v->type() == Value::Register)
    return ((RegValue *)v)->index;
  return -1;
}

inline void holdReg(Value *v)
{
  int index = getRegIndex(v);
  if (index != -1)
    holdReg(index);
}
inline void holdReg(ValPtr *vp)
{
  holdReg(vp->_Ptr);
}

inline void unholdReg(Value *v)
{
  int index = getRegIndex(v);
  if (index != -1)
    unholdReg(index);
}
inline void unholdReg(ValPtr *vp)
{
  unholdReg(vp->_Ptr);
}

inline bool ismem2(ValPtr *ptr)
{
  // 指向地址的地址
  return ptr->isMemory() && ((MemValue *)ptr->_Ptr)->_Addr->isMemory();
}

static ValPtr *toAddr(ValPtr *vp)
{
  if (vp->isMemory())
  {
    auto memVp = (MemValue *)vp->_Ptr;
    auto ans = memVp->_Addr;
    memVp->_Addr = nullptr;
    return ans;
  }
  return vp;
}

inline void addrAble(ValPtr *p, std::ostream &os)
{
  if (p->isMemory() || p->isState())
    p->load(os);
}