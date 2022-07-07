#pragma once

#include "antlib_string_vx.h"
#include "antlib_stringlist_vx.h"

#include <QStringList>

#define MINI_CASE_SENSITIVE
#include "mini/ini.h"

class AntIniFile
{
  mINI::INIStructure ini;


public:
  AntIniFile(const AntString& path);

  bool SectionExists(const AntString& section);
  AntString ReadString(const AntString& section, const AntString& key, const AntString& def);
  int  ReadInteger(const AntString& section, const AntString& key, int def);
  bool ReadBool(const AntString& section, const AntString& key, bool def);
  void ReadSections(AntStringList* Strings);
  void ReadSectionValues(const AntString& section, AntStringList* Strings);


  void ReadSection(const AntString& section, AntStringList* Strings){}
  void WriteString(const AntString& section, const AntString& key, const AntString& val){}
  void WriteInteger(const AntString& section, const AntString& key, int val){}
  void WriteBool(const AntString& section, const AntString& key, bool val){}
  void EraseSection(const AntString& section){}
  void UpdateFile(void) {}

};
