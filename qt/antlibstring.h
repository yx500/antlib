#pragma once


#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>


class AntLibString : public std::string
{
public:
  AntLibString():std::string() {}

  int Pos(const std::string& subStr) const {
    return this->find_first_of(subStr);
  }

  int Length() const {
    return size();
  }

  int ToInt() const {
    try {
      return std::stoi(*this);
    } catch (const std::invalid_argument& e) {
      std::cerr<<__FUNCTION__<<e.what()<<std::endl;
    }
    return 0;
    //return std::atoi( this->c_str() );
  }

  int ToIntDef(int defaultValue) const {
    try {
      return std::stoi(*this);
    } catch (...) {
    }
    return defaultValue;
  }


};




