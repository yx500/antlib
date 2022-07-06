#pragma once

#include <QTextCodec>
#include <QTextDecoder>

class win1251
{
public:

  static QTextCodec* codec(){
    static auto codec = QTextCodec::codecForName("Windows-1251");
    return codec;
  }

  static QTextDecoder* decoder(){
    static QTextDecoder decoder{ codec() };
    return &decoder;
  }

};

