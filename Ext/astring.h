#ifndef ASTRING_H
#define ASTRING_H


#ifdef __BORLANDC__

  #include <system.hpp>
  //class RTL_DELPHIRETURN AString : public AnsiString{
  //};
  //typedef AnsiString  String;


#else

  #include "antlibstring.h"
  typedef AString  String;


#endif //__BORLANDC__





#endif  //ASTRING_H
