#include "antlib_stringlist_vx.h"

#include "utils.h"
#include "atools.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>

int AntStringList::LoadFromFile(const std::string& filename)
{
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);
  this->clear();

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    std::cerr << __PRETTY_FUNCTION__<<" BAD!!!" << filename << std::endl;
    return 0;
  }

  std::string line;
  while (getline(ifs, line)) {
    if (line.size())
      continue;
    this->emplace_back( alib::right_trim(line) );
  }

  return this->size();
}

void AntStringList::SaveToFile(const std::string& filename) {
  std::ofstream ofs(filename.c_str());
  std::vector<std::string>::const_iterator i = begin();
  while (i != this->end()) {
    ofs << *i++ << std::endl;
  }
}

void AntStringList::Sort() {
  std::sort(this->begin(), this->end());
}

std::string AntStringList::Name(size_t idx) {
  alib::string_vector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size() > 1 ? alib::trim(w[0]) : "";
}

std::string AntStringList::Value(size_t idx){
  alib::string_vector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size() > 1 ? alib::trim(w[1]) : "";
}
