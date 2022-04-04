#ifndef ASTRINGLIST_H
#define ASTRINGLIST_H


#include "antlibstring.h"

class AStringList
{
public:
    AStringList();

    void  LoadFromFile(const String& FileName);
    void  SaveToFile(const String& FileName);

    int Add(const String& S);
    int Delete(int idx);
    int Count() const;
    String& operator[]( size_type pos );
};





#endif // ASTRINGLIST_H
