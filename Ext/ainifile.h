#ifndef AIniFile_H
#define AIniFile_H

#include "astringlist.h"

#ifdef __BORLANDC__

#include <inifiles.hpp>
class AIniFile : public TMemIniFile
{
};

#else

class AIniFile
{
public:
  AIniFile();
  ~AIniFile();

  String FileName;

  AIniFile(const String &FileName);
  bool SectionExists(const String &Section);
  String ReadString(const String &Section, const String &Ident, const String &Default) = 0;
  void WriteString(const String &Section, const String &Ident, const String &Value) = 0;
  int ReadInteger(const String &Section, const String &Ident, int Default);
  void WriteInteger(const String &Section, const String &Ident, int Value);
  bool ReadBool(const String &Section, const String &Ident, bool Default);
  void WriteBool(const String &Section, const String &Ident, bool Value);
  //  int ReadBinaryStream(const String& Section, const String& Name, Classes::TStream* Value);
  //  System::TDateTime ReadDate(const String& Section, const String& Name, System::TDateTime Default);
  //  System::TDateTime ReadDateTime(const String& Section, const String& Name, System::TDateTime Default);
  double ReadFloat(const String &Section, const String &Name, double Default);
  //  System::TDateTime ReadTime(const String& Section, const String& Name, System::TDateTime Default);
  //  void WriteBinaryStream(const String& Section, const String& Name, Classes::TStream* Value);
  //  void WriteDate(const String& Section, const String& Name, System::TDateTime Value);
  //  void WriteDateTime(const String& Section, const String& Name, System::TDateTime Value);
  void WriteFloat(const String &Section, const String &Name, double Value);
  //  void WriteTime(const String& Section, const String& Name, System::TDateTime Value);
  void ReadSection(const String &Section, AStringList *Strings) = 0;
  void ReadSections(AStringList *Strings) = 0;
  void ReadSectionValues(const String &Section, AStringList *Strings) = 0;
  void EraseSection(const String &Section) = 0;
  void DeleteKey(const String &Section, const String &Ident) = 0;
  void UpdateFile(void) = 0;
  bool ValueExists(const String &Section, const String &Ident);
};

#endif

#endif
