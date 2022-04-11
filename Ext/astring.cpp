#include "astring.h"

#include <iostream>


void cp866_to_cp1251_buff(const char *in, char *out, size_t sz)
{
#ifdef _WIN32
  OemToCharBuff(in, out, sz);
#else
  //todo implement
  std::cerr<< __FUNCTION__ << " is NOT IMPLEMENTED."<<std::endl;
#endif
}

void cp1251_to_cp866_buff(const char *in, char *out, size_t sz)
{
#ifdef _WIN32
  CharToOemBuff(in, out, sz);
#else
  //todo implement
  std::cerr<< __FUNCTION__ << " is NOT IMPLEMENTED."<<std::endl;
#endif
}
