#include "astringlist.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>
#include <cctype>
#include <functional>


static std::string right_crlf_trim(const std::string& s)
{
  std::string result(s);
  result.erase(find_if(result.rbegin(), result.rend(), not1(std::ptr_fun(std::isspace))).base(), result.end());
//  result.erase(
//      std::find_if(result.rbegin(), result.rend(),
//                   not1( std::bind2nd(std::ptr_fun(&std::isspace<char>), std::locale("")) )
//              ).base(),
//      result.end());
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

std::string& AStringList::Names(size_t idx)
{

}

std::string& AStringList::Values(const std::string &s)
{

}

