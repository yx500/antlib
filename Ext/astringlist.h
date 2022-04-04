#ifndef ASTRINGLIST_H
#define ASTRINGLIST_H



class AStringList
{
public:
    AStringList();

    void  LoadFromFile(const String& FileName);
    void  SaveToFile(const String& FileName);

    int Add(const String& S);
    int Delete(int idx);
    int Count() const;
    String& operator[]( int pos );
};





#endif // ASTRINGLIST_H
