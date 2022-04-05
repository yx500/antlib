#pragma once


#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>




class AString : public std::string
{
public:

  AString() : std::string() {}
  AString(const char *s) : std::string(s) {}
  AString(const std::string& s) : std::string(s) {}

  int Pos(const std::string& subStr) const { return this->find_first_of(subStr); }
  bool IsEmpty() const { return this->empty(); }
  int Length() const { return size(); }
  int ToInt() const {
    try {
      return std::stoi(*this);
    } catch (const std::invalid_argument& e) {
      std::cerr<<__FUNCTION__<<e.what()<<std::endl;
    }
    return 0;
  }

  int ToIntDef(int defaultValue) const {
    try {
      return std::stoi(*this);
    } catch (...) {
    }
    return defaultValue;
  }


  AString UpperCase() const;
  AString Trim() const;
  AString SubString(int b,int n) const;
  AString Delete(int b, int n) const ;


};


inline AString  IntToStr(int Value) { return std::to_string(Value); }
extern AString  IntToHex(int Value, int Digits);

inline int StrToInt(const AString& s) { return s.ToInt(); }
inline int StrToIntDef(const AString& s, int Default) { return s.ToIntDef(Default); }
