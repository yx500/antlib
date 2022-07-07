#ifndef AAA_H
#define AAA_H

#ifdef __BORLANDC__
  #include <system.hpp>
  #include <Classes.hpp>
  #include <inifiles.hpp>

  class AIniFile : public TMemIniFile
  {
  public:
    AIniFile(const String& FileName) : TMemIniFile(FileName) {}
  };

  class AStringList : public TStringList
  {
  public:
    int Size() { return this->Count; }

    String At(size_t idx) { return this->Strings[idx]; }
    String Name(size_t idx) { return this->Names[idx]; };
    String Value(size_t idx) { return this->Values[this->Names[idx]]; }
  };

#else
  #ifndef _VX_
              #include "antlibqstring.h"
              #include "antlibstringlist.h"
              #include "antlibinifile.h"
              typedef AQString String;
  #else
              #include "vx/antlib_string_vx.h"
              #include "vx/antlib_stringlist_vx.h"
              #include "vx/antlib_inifile_vx.h"
              typedef AntString String;
              typedef AntStringList AStringList;
              typedef AntIniFile AIniFile;
  #endif //_VX_
#endif //__BORLANDC__


#endif // AAA_H
