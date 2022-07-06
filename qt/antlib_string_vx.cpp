#include "antlib_string_vx.h"
#include "win1251.h"

int AntString::Pos(const std::string &subStr) const
{
  auto f = this->find(subStr);
  return f==npos ? 0 : f+1;
}

int AntString::Pos(char ch) const
{
  auto f = this->find_first_of(ch);
  return f==npos ? 0 : f+1;
}

AntString AntString::SubString(int b, int n) const
{
  return this->substr(b-1, n);
}

AntString AntString::Delete(int b, int n)
{
  return this->erase(b-1, n);
}

const QString &AntString::asQString() const
{
  if( qstr.isEmpty() )
    qstr = win1251::codec()->toUnicode( this->c_str() );
  return qstr;
}
