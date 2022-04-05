#ifndef ASTRINGLIST_H
#define ASTRINGLIST_H


#include <string>
#include <vector>

class AStringList : public std::vector<std::string>
{
public:
    AStringList(){}

    int   LoadFromFile(const std::string& FileName);
    void  SaveToFile(const std::string& FileName);

    int Count() const { return this->size(); }
    void Add(const std::string& s) { this->push_back(s); }
    void Delete(size_t idx) { this->erase( this->begin() + idx);  }

    std::string& Strings(size_t idx) { return this->at(idx); }

    void Sort();
    std::string& Names(size_t idx);
    std::string& Values(size_t idx);
    //std::string& Values(const std::string& s);
};





#endif // ASTRINGLIST_H
