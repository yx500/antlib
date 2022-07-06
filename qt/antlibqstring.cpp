#include "antlibqstring.h"
#include <QDebug>
#include "win1251.h"

AQString::AQString(const QString &s)
    : QString(s)
{
  this->cstr = win1251::codec()->fromUnicode(*this).toStdString();
}

AQString::AQString(const char* s)
    : QString( win1251::codec()->toUnicode(s) )
{
  this->cstr = std::string( s );
}

AQString::AQString(const char s)
    : QString( win1251::codec()->toUnicode(&s, 1) )
{
  this->cstr = std::string( 1, s );
}


const char *AQString::c_str() const {
  this->cstr = win1251::codec()->fromUnicode(*this).toStdString();
  return cstr.c_str();
}

