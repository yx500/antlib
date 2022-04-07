#ifndef ASTRINGLIST_H
#define ASTRINGLIST_H

#ifdef __BORLANDC__

#include <Classes.hpp>
#include <system.hpp>

class AStringList : public TStringList
{
public:
  int Size() { return this->Count; }

  String At(size_t idx) { return this->Strings[idx]; }
  String Name(size_t idx) { return this->Names[idx]; };
  String Value(size_t idx) { return this->Values[this->Names[idx]]; }
};

#else

#include "antlibstringlist.h"

#endif

#endif // ASTRINGLIST_H
