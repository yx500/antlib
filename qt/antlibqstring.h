#pragma once

#include <QString>

class AQString : public QString
{
  mutable std::string cstr;

public:
  AQString() : QString() {}
  AQString(const QString &s);
  AQString(const char* s) ;
  AQString(const char &s) ;
  AQString(const std::string& s) : AQString( s.c_str() ) {}

  int Pos(const QString& subStr) const {return this->indexOf(subStr)+1;}
  int Pos(char ch) const {return this->indexOf(AQString(ch))+1;}
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
  AQString SubString(int b, int n)  const {return this->mid(b-1,n);}
  AQString Delete(int b, int n){return this->remove(b-1,n);}

  void printf( const char* format, int v) {
     *this=QString::asprintf(format,v);
  }
  void printf( const char* format, float v) {
     *this=QString::asprintf(format,v);
  }
  void printf( const char* format, const char* v) {
     *this=QString::asprintf(format,v);
  }
  void printf( const char* format, double v) {
     *this=QString::asprintf(format,v);
  }
  const char *c_str() const ;
  const char operator[](int i) const {return this->at(i).toLatin1();}

};

inline AQString IntToStr(int Value) { return QString::number(Value); }
inline int StrToInt(const AQString& s) { return s.toInt(); }
inline int StrToIntDef(const AQString& s, int Default) { return s.ToIntDef(Default); }
