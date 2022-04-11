#pragma once

#include "utils.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <cstdio>

class AString : public std::string
{
public:
  AString() : std::string() {}
  AString(const char* s) : std::string(s) {}
  AString(const std::string& s) : std::string(s) {}

  int Pos(const std::string& subStr) const { return this->find_first_of(subStr); }
  int Pos(char ch) const { return this->find_first_of(ch); }
  bool IsEmpty() const { return this->empty(); }
  int Length() const { return size(); }
  int ToInt() const
  {
    try {
      return std::stoi(*this);
    } catch (const std::invalid_argument& e) {
      std::cerr << __FUNCTION__ << e.what() << std::endl;
    }
    return 0;
  }

  int ToIntDef(int defaultValue) const
  {
    try {
      return std::stoi(*this);
    } catch (...) {
    }
    return defaultValue;
  }

  AString UpperCase() const { return alib::to_upper(*this); }
  AString Trim() const { return alib::trim(*this); }
  AString SubString(int b, int n) const;
  AString Delete(int b, int n) const;

//  void printf(const  f, float v)
//  {
//    static char _buf[64];
//    sprintf(_buf, f, v);
//    this->clear();
//    this->append(_buf);
//  }
//  void printf(const char* f, int v)
//  {
//    static char _buf[64];
//    sprintf(_buf, f, v);
//    this->clear();
//    this->append(_buf);
//  }
//  void printf(const char* f, double v)
//  {
//    static char _buf[64];
//    sprintf(_buf, f, v);
//    this->clear();
//    this->append(_buf);
//  }

  template<typename ... Args>
  void printf( const char* format, Args ... args )
  {
    size_t size = std::snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format, args ... );
    this->assign( std::string( buf.get(), buf.get() + size - 1 ) ); // We don't want the '\0' inside
  }

};

inline AString IntToStr(int Value) { return std::to_string(Value); }
extern AString IntToHex(int Value, int Digits);

inline int StrToInt(const AString& s) { return s.ToInt(); }
inline int StrToIntDef(const AString& s, int Default) { return s.ToIntDef(Default); }
