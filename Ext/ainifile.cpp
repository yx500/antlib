#include "ainifile.h"


#ifndef __BORLANDC__
AIniFile::AIniFile(const String &FileName):QSettings(FileName.c_str(),QSettings::IniFormat)
{
    this->setIniCodec("Windows-1251");
}
#endif
