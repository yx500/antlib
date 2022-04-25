#include "antlibqstring.h"
#include <QTextCodec>

static QTextCodec *codec1251=nullptr;
static std::string cstr;
const char *AQString::c_str() const
{
    if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
    if (codec1251!=nullptr) {
        cstr=codec1251->fromUnicode(*this).toStdString();
    } else {
        cstr =this->toStdString();
    }
    return cstr.c_str();
}

AQString::AQString(const char* s) : QString()
{
    if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
    if (codec1251!=nullptr) {
        *this=codec1251->toUnicode(s);
    } else {
        *this=QString::fromLocal8Bit(s);
    }
}

AQString::AQString(const char &s) : QString()
{
    if (codec1251==nullptr) codec1251=QTextCodec::codecForName("Windows-1251");
    if (codec1251!=nullptr) {
        *this=codec1251->toUnicode(&s);
    } else {
        *this=QString::fromLocal8Bit(&s);
    }

}
