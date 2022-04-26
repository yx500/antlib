#include "antlibqstring.h"
#include <QTextCodec>
#include <QDebug>

static QTextCodec *codec1251=nullptr;

const char *AQString::c_str() const
{
  if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
  if (codec1251!=nullptr) {
    this->cstr = codec1251->fromUnicode(*this).toStdString();
  } else {
    qDebug()<<__FUNCTION__<<" BAD!!!";
    cstr = this->toStdString();
  }
  return cstr.c_str();
}

AQString::AQString(const char* s) : QString()
{
  if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
  if (codec1251!=nullptr) {
    *this=codec1251->toUnicode(s);
  } else {
    qDebug()<<__FUNCTION__<<" BAD!!!";
    *this=QString::fromLocal8Bit(s);
  }
  cstr=std::string( s );
}

AQString::AQString(const char &s) : QString()
{
  if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
  if (codec1251!=nullptr) {
    *this=codec1251->toUnicode(&s);
  } else {
    qDebug()<<__FUNCTION__<<" BAD!!!";
    *this=QString::fromLocal8Bit(&s);
  }
  cstr = std::string( 1, s );
}

AQString::AQString(const QString &s) : QString(s)
{
  if (codec1251==nullptr)
      codec1251=QTextCodec::codecForName("Windows-1251");
  if (codec1251!=nullptr) {
    this->cstr = codec1251->fromUnicode(*this).toStdString();
  } else {
    qDebug()<<__FUNCTION__<<" BAD!!!";
    cstr = this->toStdString();
  }
}
