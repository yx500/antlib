#include "antlibstringlist.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>

int AStringList::LoadFromFile(const AQString &filename)
{
  this->clear();

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    std::cerr << "AStringList::LoadFromFile bad!!!" << filename.c_str() << std::endl;
    return 0;
  }

  std::string line;
  while (getline(ifs, line)) {
    if (line.size())
      continue;
    AQString s(line);
    this->push_back(  s.trimmed());
  }

  return this->size();
}

void AStringList::SaveToFile(const AQString &filename)
{
  std::ofstream ofs(filename.c_str());

  for (int i=0;i<size();i++)
  {
      QString s=this->at(i);
      ofs << s.toStdString().c_str() << std::endl;
  }

}

void AStringList::Sort() { std::sort(this->begin(), this->end()); }

AQString AStringList::Name(size_t idx)
{
  QString s=this->at(idx);
  auto l=s.split("=");
  if (l.size()>0) return l[0];
  return "";
}

AQString AStringList::Value(size_t idx)
{
    QString s=this->at(idx);
    auto l=s.split("=");
    if (l.size()>1) return l[1];
    return "";
}
