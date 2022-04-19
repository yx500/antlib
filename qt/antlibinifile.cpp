#include "antlibinifile.h"
//#include <QTextCodec>


std::string ToStdStr(const QString& qstr){
//  QTextCodec* codec1251 = QTextCodec::codecForName("Windows-1251");
//  auto ba = codec1251->fromUnicode(qstr);
  QByteArray ba;
  ba = qstr.toLatin1();
  return ba.toStdString();
}



AIniFile::AIniFile(const String& FileName) : QSettings(FileName.c_str(), QSettings::IniFormat)
{
//todo  this->setIniCodec("Windows-1251");
}

bool AIniFile::SectionExists(const String& c)
{
  if (this->childGroups().indexOf(c.c_str()) >= 0)
    return true;
  return false;
}

String AIniFile::ReadString(const String& Section, const String& Ident, const String& Default)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  QString d = Default.c_str();
  return ToStdStr(this->value(s, d).toString());
}

void AIniFile::WriteString(const String& Section, const String& Ident, const String& Value)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  QString v = Value.c_str();
  this->setValue(s, v);
}

int AIniFile::ReadInteger(const String& Section, const String& Ident, int Default)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  return this->value(s, Default).toInt();
}

void AIniFile::WriteInteger(const String& Section, const String& Ident, int Value)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  this->setValue(s, Value);
}

bool AIniFile::ReadBool(const String& Section, const String& Ident, bool Default)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  return this->value(s, Default).toBool();
}

void AIniFile::WriteBool(const String& Section, const String& Ident, bool Value)
{
  QString s = QString("%1=%2").arg(Section.c_str()).arg(Ident.c_str());
  this->setValue(s, Value);
}

void AIniFile::ReadSection(const String& Section, AStringList* Strings)
{
  this->beginGroup(Section.c_str());
  auto l = this->childKeys();
  for (auto& k: l) {
    Strings->Add( ToStdStr(k) );
  }
  this->endGroup();
}

void AIniFile::ReadSections(AStringList* Strings)
{
  auto l = this->childGroups();
  for (auto& k: l) {
    Strings->Add( ToStdStr(k) );
  }
}

void AIniFile::ReadSectionValues(const String& Section, AStringList* Strings)
{
  this->beginGroup(Section.c_str());
  auto l = this->childKeys();
  for (auto& k: l) {
    auto v = this->value(k).toString();
    auto sv = ToStdStr(k) + "=" + ToStdStr(v);
    Strings->Add( sv );
  }
  this->endGroup();
}

void AIniFile::EraseSection(const String& Section)
{
  this->remove(Section.c_str());
}
