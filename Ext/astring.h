#ifndef ASTRING_H
#define ASTRING_H

#ifdef __BORLANDC__
    #include <system.hpp>
#else

  #ifdef _VX_
              #include "antlibstring.h"
              typedef AntString String;
  #else
              #include "antlibqstring.h"
              typedef AQString String;
  #endif


#endif //__BORLANDC__


void cp866_to_cp1251_buff(const char* in, char* out, size_t sz);
void cp1251_to_cp866_buff(const char* in, char* out, size_t sz);



#endif // ASTRING_H
