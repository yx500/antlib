#ifndef ASTRING_H
#define ASTRING_H

#ifdef __BORLANDC__
    #include <system.hpp>
#else

  #ifdef _VX_
              #include "antlib_string_vx.h"
              typedef AntString String;
              #include "antlib_stringlist_vx.h"
              typedef AntStringList AStringList;
              #include "antlib_inifile_vx.h"
              typedef AntIniFile AIniFile;
  #else
              #include "antlibqstring.h"
              typedef AQString String;
  #endif


#endif //__BORLANDC__


#endif // ASTRING_H
