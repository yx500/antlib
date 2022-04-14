#include "antlibstring.h"

int AString::Pos(const std::string &subStr) const
{
  auto f = this->find(subStr);
  return f==npos ? 0 : f+1;
}

int AString::Pos(char ch) const
{
  auto f = this->find_first_of(ch);
  return f==npos ? 0 : f+1;
}

AString AString::SubString(int b, int n) const
{
  return this->substr(b-1, n);
}

AString AString::Delete(int b, int n)
{
  return this->erase(b-1, n);
}
