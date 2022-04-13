#pragma once

#include "antlibstringlist.h"
#include "astring.h"

#include <QSettings>
class AIniFile : public QSettings
{
public:
  String FileName;

  AIniFile(const String& FileName);
//  ~AIniFile();

  bool SectionExists(const String& Section);
  String ReadString(const String& Section, const String& Ident, const String& Default);
  void WriteString(const String& Section, const String& Ident, const String& Value);
  int ReadInteger(const String& Section, const String& Ident, int Default);
  void WriteInteger(const String& Section, const String& Ident, int Value);
  bool ReadBool(const String& Section, const String& Ident, bool Default);
  void WriteBool(const String& Section, const String& Ident, bool Value);
  void ReadSection(const String& Section, AStringList* Strings);
  void ReadSections(AStringList* Strings);
  void ReadSectionValues(const String& Section, AStringList* Strings);
  void EraseSection(const String& Section);
  void UpdateFile(void) {;}
  //  bool ValueExists(const String &Section, const String &Ident);

};
