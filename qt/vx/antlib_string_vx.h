#pragma once

#include "utils.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <cstdio>

#include <QString>
#include <QStaticText>


class AntString : public std::string
{
public:
  AntString() : std::string() {}
  AntString(const char* s) : std::string(s) {}
  AntString(const std::string& s) : std::string(s) {}

  int Pos(const std::string& subStr) const;
  int Pos(char ch) const;
  bool IsEmpty() const { return this->empty(); }
  int Length() const { return size(); }

  int ToIntDef(int defaultValue) const {
    try { return std::stoi(*this); } catch (...) {}
    return defaultValue;
  }
  int ToInt() const  { return ToIntDef(0); }

  AntString UpperCase() const { return alib::to_upper(*this); }
  AntString Trim() const { return alib::trim(*this); }
  AntString SubString(int b, int n) const;
  AntString Delete(int b, int n);

  template<typename ... Args>
  void printf( const char* format, Args ... args ) {
    size_t size = std::snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format, args ... );
    this->assign( std::string( buf.get(), buf.get() + size - 1 ) ); // We don't want the '\0' inside
  }

  //cache cache cache cache cache
  mutable struct {
    QString txt;
    //QStaticText stat_txt;
    int width{0};
  } cache;
  const QString& asQString() const;
  //const QStaticText& asQStaticText() const;


};

