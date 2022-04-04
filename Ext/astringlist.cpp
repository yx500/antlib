#include "astringlist.h"
#include <fstream>


void AStringList::LoadFromFile(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
}



void AStringList::SaveToFile(const std::string &filename)
{
    std::ofstream ofs(filename.c_str());

}

