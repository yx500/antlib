#ifndef ASTRING_H
#define ASTRING_H

#ifdef __BORLANDC__

#include <system.hpp>
// class RTL_DELPHIRETURN AString : public AnsiString{};
// typedef AnsiString  String;

#else

#include "antlibstring.h"
typedef AString String;

#endif //__BORLANDC__


void cp866_to_cp1251_buff(const char* in, char* out, size_t sz);
void cp1251_to_cp866_buff(const char* in, char* out, size_t sz);



#endif // ASTRING_H
