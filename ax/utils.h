#ifndef utils_H
#define utils_H

#include <stddef.h>
#include <string>
#include <vector>
#include <list>

//#ifndef __BORLANDC__
//#endif

namespace alib {

// todo !!must deprecated
char* itoa(int num, char* buffer, int base);

// strings
typedef std::list<std::string> string_list;
typedef std::vector<std::string> string_vector;

int string_split(const std::string& text, const std::string& separators, string_vector& words);
int string_splitex(const std::string& text, const std::string& separators, string_vector& words);
void string_replace(std::string& o, const char* s, const char* d);
void string_replace_all(std::string& o, const char* s, const char* d);
std::string to_upper(const std::string& s);
std::string to_lower(const std::string& s);
std::string left_trim(const std::string& s);
std::string right_trim(const std::string& s);
inline std::string trim(const std::string& s) { return left_trim(right_trim(s)); }
std::string& strings_merge(const string_vector& words, const std::string& separator, std::string& text);
int to_int(const std::string& s);




class CaseInsensitiveFilePath : std::string
{
public:
    typedef std::string (*CaseTrasformFunc)(const char* );
    static CaseTrasformFunc path_transform_function;

    explicit CaseInsensitiveFilePath(const char* filepath )
        : std::string( path_transform_function(filepath) ) {
    }

    const char* path() { return this->c_str(); }
};




} // namespace alib


void cp866_to_cp1251_buff(const char* in, char* out, size_t sz);
void cp1251_to_cp866_buff(const char* in, char* out, size_t sz);



#endif
