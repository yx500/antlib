#pragma once

#include <string>
#include <vector>
#include <QStringList>


class AntStringList : public std::vector<std::string>
{
public:
  AntStringList() {}

  int LoadFromFile(const std::string& FileName);
  void SaveToFile(const std::string& FileName);

  void Add(const std::string& s) { this->push_back(s); }
  void Delete(size_t idx) { this->erase(this->begin() + idx); }
  void Sort();
  void Clear() { this->clear(); }
  int  Size() const { return this->size(); }
  const std::string& At(size_t idx) const { return this->at(idx); }
  std::string Name(size_t idx);
  std::string Value(size_t idx);

  QStringList asQStringList();
};
