#include "antlibinifile.h"
#include "win1251.h"


auto ToStdStr(const QString& qstr){
  QByteArray ba;
  ba = qstr.toLatin1();
  return ba.toStdString();
}

AIniFile::AIniFile(const AQString& path)
    : QSettings(path.c_str(), QSettings::IniFormat)
    //, FileName(path)
{
}

bool AIniFile::SectionExists(const AQString& c)
{
  if (this->childGroups().indexOf(c.c_str()) >= 0)
    return true;
  return false;
}

AQString AIniFile::ReadString(const AQString& Section, const AQString& Ident, const AQString& Default)
{
  QString s = QString("%1/%2").arg(Section).arg(Ident);
  QString ss = QString().fromLatin1( win1251::codec()->fromUnicode(s) );
  QString v=this->value(ss, Default).toString();
  v=win1251::codec()->toUnicode(v.toLatin1().data());
  return v;
}

void AIniFile::WriteString(const AQString& Section, const AQString& Ident, const AQString& Value)
{
  QString s = QString("%1/%2").arg(Section.c_str()).arg(Ident.c_str());
  QString ss = QString().fromLatin1(win1251::codec()->fromUnicode(s));
  QString v = Value;
  this->setValue(ss, v);
}

int AIniFile::ReadInteger(const AQString& Section, const AQString& Ident, int Default)
{
  QString s = QString("%1/%2").arg(Section.c_str()).arg(Ident.c_str());
  QString ss = QString().fromLatin1(win1251::codec()->fromUnicode(s));
  return this->value(ss, Default).toInt();
}

void AIniFile::WriteInteger(const AQString& Section, const AQString& Ident, int Value)
{
  QString s = QString("%1/%2").arg(Section.c_str()).arg(Ident.c_str());
  QString ss = QString().fromLatin1(win1251::codec()->fromUnicode(s));
  this->setValue(ss, Value);
}

bool AIniFile::ReadBool(const AQString& Section, const AQString& Ident, bool Default)
{
  QString s = QString("%1/%2").arg(Section.c_str()).arg(Ident.c_str());
  QString ss = QString().fromLatin1(win1251::codec()->fromUnicode(s));
  return this->value(ss, Default).toBool();
}

void AIniFile::WriteBool(const AQString& Section, const AQString& Ident, bool Value)
{
  QString s = QString("%1/%2").arg(Section.c_str()).arg(Ident.c_str());
  QString ss = QString().fromLatin1(win1251::codec()->fromUnicode(s));
  this->setValue(ss, Value);
}

void AIniFile::ReadSection(const AQString& Section, AStringList* Strings)
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

void AIniFile::ReadSectionValues(const AQString& Section, AStringList* Strings)
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

void AIniFile::EraseSection(const AQString& Section)
{
  this->remove(Section.c_str());
}
