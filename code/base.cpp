#include "base.h"

std::string toHex(int _Value)
{
  char buf[12];
  if (_Value < 0)
    cout << "toHex _Value is nagetive\n";
  sprintf(buf, "0x%x", _Value);
  return buf;
}

void notImplement(const char *name)
{
  std::cout << "not implement: " << name << endl;
  exit(1);
}

void my_error(const char *err)
{
  cout << err << endl;
  exit(1);
}
