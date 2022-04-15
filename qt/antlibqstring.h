#pragma once

#include <QString>

class AQString : public QString
{
public:
  AQString() : QString() {}
  AQString(const QString &s) : QString(s) {}
  AQString(const char* s) : QString(s) {}
  AQString(const std::string& s) : QString(s.c_str()) {}
  AQString(const char &s) : QString(s) {}

  int Pos(const QString& subStr) const {return this->indexOf(subStr);}
  //int Pos(char ch) const;
  bool IsEmpty() const { return this->isEmpty(); }
  int Length() const { return size(); }
  int ToInt() const  {return this->toInt();}

  int ToIntDef(int defaultValue) const {
    bool ok;
    int n=this->toInt(&ok);
    if (!ok) return defaultValue;
    return n;
  }

  AQString UpperCase() const { return this->toUpper(); }
  AQString Trim() const { return this->trimmed(); }
  AQString SubString(int b, int n)  const {return this->mid(b,n);}
  AQString Delete(int b, int n){return this->remove(b,n);}

  void printf( const char* format, int v) {
     *this=QString::asprintf(format,v);
  }
  const char *c_str() const ;
  const char operator[](int i) const {return this->at(i).toLatin1();}

};

inline AQString IntToStr(int Value) { return QString::number(Value); }
inline int StrToInt(const AQString& s) { return s.toInt(); }
inline int StrToIntDef(const AQString& s, int Default) { return s.ToIntDef(Default); }
