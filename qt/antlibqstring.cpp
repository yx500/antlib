#include "antlibqstring.h"

static std::string cstr;
const char *AQString::c_str() const
{
    cstr =this->toStdString();
    return cstr.c_str();
}
