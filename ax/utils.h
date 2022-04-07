#ifndef utils_H
#define utils_H

#include <stddef.h>
#include <string>
#include <vector>

#ifndef __BORLANDC__
// winuser.h
void OemToAnsi(const char* in, char* out);
void OemToCharBuff(const char* in, char* out, size_t s);
void CharToOemBuff(const char* in, char* out, size_t s);
#endif

namespace alib {

// todo !!must deprecated
char* itoa(int num, char* buffer, int base);

// strings
typedef std::vector<std::string> stringvector;
int string_split(const std::string& text, const std::string& separators, stringvector& words);
int string_splitex(const std::string& text, const std::string& separators, stringvector& words);
void string_replace(std::string& o, const char* s, const char* d);
void string_replace_all(std::string& o, const char* s, const char* d);
std::string to_upper(const std::string& s);
std::string to_lower(const std::string& s);
std::string left_trim(const std::string& s);
std::string right_trim(const std::string& s);
inline std::string trim(const std::string& s) { return left_trim(right_trim(s)); }
std::string& strings_merge(const stringvector& words, const std::string& separator, std::string& text);
int to_int(const std::string& s);

} // namespace alib

#endif
