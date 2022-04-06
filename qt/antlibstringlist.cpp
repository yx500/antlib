#include "antlibstringlist.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>
#include <cctype>
#include <functional>
#include "utils.h"

int is_crlf( int ch ){
  return ch=='\r' || ch=='\n';
}

static std::string right_crlf_trim(const std::string& s)
{
  std::string result(s);
  result.erase( std::find_if( result.rbegin(), result.rend(), not1(std::ptr_fun(is_crlf))).base(), result.end() );
  return result;
}

int AStringList::LoadFromFile(const std::string &filename)
{
  this->clear();

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()){
    std::cerr<<"AStringList::LoadFromFile bad!!!" << filename << std::endl;
    return 0;
  }

  std::string line;
  while( getline(ifs,line) ) {
    if(line.size())
      continue;
    this->push_back( right_crlf_trim(line) );
  }

  return this->size();
}



void AStringList::SaveToFile(const std::string &filename)
{
  std::ofstream ofs(filename.c_str());
  std::vector<std::string>::const_iterator i = begin();
  while( i != this->end() ){
    ofs << *i++ << std::endl;
  }
}

void AStringList::Sort()
{
  std::sort(this->begin(), this->end());
}

std::string AStringList::Name(size_t idx)
{
  alib::stringvector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size()>1 ? alib::trim(w[0]) : "";
}

std::string AStringList::Value(size_t idx)
{
  alib::stringvector w;
  alib::string_split(this->at(idx), "=", w);
  return w.size()>1 ? alib::trim(w[1]) : "";
}


