#pragma once


#include "antlibstring.h"
#include<QStringList>


class TStringList : public QStringList
{
public:
  TStringList();
  void  LoadFromFile(const String& FileName);
  int Add(const String& S);
};



