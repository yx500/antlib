#ifndef AIniFile_H
#define AIniFile_H

#include "astringlist.h"
#include "astring.h"

#ifdef __BORLANDC__

#include <inifiles.hpp>
class AIniFile : public TMemIniFile
{
public:
         AIniFile(const String &FileName): TMemIniFile(FileName) {}
};

#else
#include <QSettings>
class AIniFile : public QSettings
{
public:
  ~AIniFile();

  String FileName;

  AIniFile(const String &FileName);
  bool SectionExists(const String &Section);
  String ReadString(const String &Section, const String &Ident, const String &Default);
  void WriteString(const String &Section, const String &Ident, const String &Value);
  int ReadInteger(const String &Section, const String &Ident, int Default);
  void WriteInteger(const String &Section, const String &Ident, int Value);
  bool ReadBool(const String &Section, const String &Ident, bool Default);
  void WriteBool(const String &Section, const String &Ident, bool Value);
  //  int ReadBinaryStream(const String& Section, const String& Name, Classes::TStream* Value);
  //  System::TDateTime ReadDate(const String& Section, const String& Name, System::TDateTime Default);
  //  System::TDateTime ReadDateTime(const String& Section, const String& Name, System::TDateTime Default);
//  double ReadFloat(const String &Section, const String &Name, double Default);
  //  System::TDateTime ReadTime(const String& Section, const String& Name, System::TDateTime Default);
  //  void WriteBinaryStream(const String& Section, const String& Name, Classes::TStream* Value);
  //  void WriteDate(const String& Section, const String& Name, System::TDateTime Value);
  //  void WriteDateTime(const String& Section, const String& Name, System::TDateTime Value);
//  void WriteFloat(const String &Section, const String &Name, double Value);
  //  void WriteTime(const String& Section, const String& Name, System::TDateTime Value);
  void ReadSection(const String &Section, AStringList *Strings) ;
  void ReadSections(AStringList *Strings);
  void ReadSectionValues(const String &Section, AStringList *Strings);
//  void EraseSection(const String &Section);
//  void DeleteKey(const String &Section, const String &Ident);
  void UpdateFile(void);
//  bool ValueExists(const String &Section, const String &Ident);
};

#endif

#endif
