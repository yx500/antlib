#include "astring.h"

#include <cstring>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#endif


void cp866_to_cp1251_buff(const char *in, char *out, size_t sz)
{
#ifdef _WIN32
  ::OemToCharBuffA(in, out, sz);
#else
  //todo implement
  std::cerr<< __FUNCTION__ << " is NOT IMPLEMENTED."<<std::endl;
  strncpy(out, in, sz);
#endif
}

void cp1251_to_cp866_buff(const char *in, char *out, size_t sz)
{
#ifdef _WIN32
  ::CharToOemBuffA(in, out, sz);
#else
  //todo implement
  std::cerr<< __FUNCTION__ << " is NOT IMPLEMENTED."<<std::endl;
  strncpy(out, in, sz);

#endif
}
