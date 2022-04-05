#include "antlibinifile.h"


AIniFile::AIniFile(const String &FileName) : QSettings(FileName.c_str(),QSettings::IniFormat)
{
    this->setIniCodec("Windows-1251");
}
