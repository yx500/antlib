#pragma once


#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>




class AntLibString : public std::string
{
public:

  AntLibString():std::string() {}
  AntLibString(const char *s) : std::string(s) {}
  AntLibString(const std::string& s) : std::string(s) {}

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


  AntLibString UpperCase() const;

  AntLibString Trim() const;

  AntLibString SubString(int b,int n) const;


};
using String = AntLibString;



inline String  IntToStr(int Value) { return std::to_string(Value); }
extern String  IntToHex(int Value, int Digits);

inline int StrToInt(const String& s) { return s.ToInt(); }
inline int StrToIntDef(const String& s, int Default) { return s.ToIntDef(Default); }



