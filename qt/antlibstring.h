#pragma once


#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>


class AntLibString : public std::string
{
public:
  AntLibString():std::string() {}
  AntLibString(const char *s):std::string(s) {}

  int Pos(const std::string& subStr) const {
    return this->find_first_of(subStr);
  }

  int Length() const {
    return size();
  }

  int ToInt() const {
    try {
      return std::stoi(*this);
    } catch (const std::invalid_argument& e) {
      std::cerr<<__FUNCTION__<<e.what()<<std::endl;
    }
    return 0;
    //return std::atoi( this->c_str() );
  }

  int ToIntDef(int defaultValue) const {
    try {
      return std::stoi(*this);
    } catch (...) {
    }
    return defaultValue;
  }
  AntLibString   UpperCase() const;
  AntLibString   Trim() const;


};


extern AntLibString  IntToStr(int Value);
extern AntLibString  IntToStr(__int64 Value);
extern AntLibString  IntToHex(int Value, int Digits);
extern AntLibString  IntToHex(__int64 Value, int Digits);
extern int  StrToInt(const AntLibString S);
extern int  StrToIntDef(const AntLibString S, int Default);



