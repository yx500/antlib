#include "antlibstringlist2.h"

#include "utils.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>

int AStdStringList::LoadFromFile(const std::string& filename)
{
  this->clear();

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    std::cerr << "AStdStringList::LoadFromFile bad!!!" << filename << std::endl;
    return 0;
  }

  std::string line;
  while (getline(ifs, line)) {
    if (line.size())
      continue;
    this->push_back(alib::right_trim(line));
  }

  return this->size();
}

void AStdStringList::SaveToFile(const std::string& filename)
{
  std::ofstream ofs(filename.c_str());
  std::vector<std::string>::const_iterator i = begin();
  while (i != this->end()) {
    ofs << *i++ << std::endl;
  }
}

void AStdStringList::Sort() { std::sort(this->begin(), this->end()); }

std::string AStdStringList::Name(size_t idx)
{
  alib::string_vector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size() > 1 ? alib::trim(w[0]) : "";
}

std::string AStdStringList::Value(size_t idx)
{
  alib::string_vector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size() > 1 ? alib::trim(w[1]) : "";
}
