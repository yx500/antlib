#pragma once

#include "antlibqstring.h"
#include <QStringList>

class AStringList : public QStringList
{
public:
  AStringList() {}

  int LoadFromFile(const AQString& FileName);
  void SaveToFile(const AQString& FileName);

  int Size() const { return this->size(); }
  void Add(const AQString& s) { this->push_back(s); }
  void Delete(size_t idx) { this->erase(this->begin() + idx); }
  void Sort();
  void Clear() { this->clear(); }
  AQString At(size_t idx) { return this->at(idx); }
  AQString Name(size_t idx);
  AQString Value(size_t idx);
  // std::string& Values(const std::string& s);
};
