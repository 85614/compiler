#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
using std::cout;
using std::endl;

#define DEBUG2(x)                                                             \
  {                                                                           \
    cout << __FILE__ << " " << __LINE__ << "  " << #x << " is " << x << endl; \
  }

extern std::ostream &theOs;

std::string toHex(int _Value);

void notImplement(const char *name);

void my_error(const char *err);

inline std::string toSignedHex(int off)
{
  if (off > 0)
    return "+" + toHex(off);
  else if (off < 0)
    return "-" + toHex(-off);
  return "";
}