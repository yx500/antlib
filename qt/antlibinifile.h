#pragma once

#include "antlibstringlist.h"
#include "antlibqstring.h"

#include <QSettings>
class AIniFile : private QSettings
{
public:
  //AQString FileName;

  AIniFile(const AQString& path);

  bool SectionExists(const AQString& Section);
  AQString ReadString(const AQString& Section, const AQString& Ident, const AQString& Default);
  void WriteString(const AQString& Section, const AQString& Ident, const AQString& Value);
  int ReadInteger(const AQString& Section, const AQString& Ident, int Default);
  void WriteInteger(const AQString& Section, const AQString& Ident, int Value);
  bool ReadBool(const AQString& Section, const AQString& Ident, bool Default);
  void WriteBool(const AQString& Section, const AQString& Ident, bool Value);
  void ReadSection(const AQString& Section, AStringList* Strings);
  void ReadSections(AStringList* Strings);
  void ReadSectionValues(const AQString& Section, AStringList* Strings);
  void EraseSection(const AQString& Section);
  void UpdateFile(void) {;}
  //  bool ValueExists(const AQString &Section, const AQString &Ident);

};
