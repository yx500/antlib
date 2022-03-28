#ifndef TSTRINGLIST_H
#define TSTRINGLIST_H

#include<QStringList>
#include "antlibstring.h"
class TStringList : public QStringList
{
public:
    TStringList();
    void  LoadFromFile(const AntLibString FileName);
    int Add(const AntLibString S);
};

#endif // TSTRINGLIST_H
