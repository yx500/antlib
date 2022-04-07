#ifndef AIniFile_H
#define AIniFile_H

#include "astring.h"
#include "astringlist.h"

#ifdef __BORLANDC__

#include <inifiles.hpp>
class AIniFile : public TMemIniFile
{
public:
  AIniFile(const String& FileName) : TMemIniFile(FileName) {}
};

#else

#include "antlibinifile.h"

#endif

#endif
