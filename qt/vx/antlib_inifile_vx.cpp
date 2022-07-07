#include "antlib_inifile_vx.h"
#include "win1251.h"
#include "atools.h"


using namespace  mINI;

AntIniFile::AntIniFile(const AntString& path)
{
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);
  mINI::INIFile file(path);
  file.read(ini);
}

bool AntIniFile::SectionExists(const AntString& c)
{
  return ini.has(c);
}

AntString AntIniFile::ReadString(const AntString& section, const AntString& key, const AntString& def)
{
  if(! ini.get(section).has(key) )
    return def;
  else
    return ini.get(section).get(key);
}

int AntIniFile::ReadInteger(const AntString& section, const AntString& key, int def)
{
  if(! ini.get(section).has(key) )
    return def;
  else
    return std::stoi( ini.get(section).get(key) );
}

bool AntIniFile::ReadBool(const AntString& section, const AntString& key, bool def)
{
  return ReadInteger(section, key, def);
}

void AntIniFile::ReadSections(AntStringList* Strings)
{
  for (auto const& it : ini)  {
    auto const& section = it.first;
    Strings->Add( section.data() );
  }
}

void AntIniFile::ReadSectionValues(const AntString& section, AntStringList* Strings)
{
  if (ini.has(section)) {
    auto const& collection = ini[section];
    for (auto const& it2 : collection)
    {
      auto const& key = it2.first;
      auto const& value = it2.second;
      AntString sv = key + "=" + value;
      Strings->Add( sv );
    }
  }
}

