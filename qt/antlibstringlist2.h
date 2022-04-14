#pragma once

// #include "antlibstring.h"

#include <string>
#include <vector>

class AStdStringList : public std::vector<std::string>
{
public:
  AStdStringList() {}

  int LoadFromFile(const std::string& FileName);
  void SaveToFile(const std::string& FileName);

  int Size() const { return this->size(); }
  void Add(const std::string& s) { this->push_back(s); }
  void Delete(size_t idx) { this->erase(this->begin() + idx); }
  void Sort();
  void Clear() { this->clear(); }
  std::string At(size_t idx) { return this->at(idx); }
  std::string Name(size_t idx);
  std::string Value(size_t idx);
  // std::string& Values(const std::string& s);
};
