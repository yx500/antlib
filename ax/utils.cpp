#include "utils.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace alib {

char* itoa(int num, char* buffer, int base)
{
  int curr = 0;

  if (num == 0) {
    // Base case
    buffer[curr++] = '0';
    buffer[curr] = '\0';
    return buffer;
  }

  int num_digits = 0;

  if (num < 0) {
    if (base == 10) {
      num_digits++;
      buffer[curr] = '-';
      curr++;
      // Make it positive and finally add the minus sign
      num *= -1;
    } else
      // Unsupported base. Return NULL
      return NULL;
  }

  num_digits += (int)floor(log(num) / log(base)) + 1;

  // Go through the digits one by one
  // from left to right
  while (curr < num_digits) {
    // Get the base value. For example, 10^2 = 1000, for the third digit
    int base_val = (int)pow(base, num_digits - 1 - curr);

    // Get the numerical value
    int num_val = num / base_val;

    char value = num_val + '0';
    buffer[curr] = value;

    curr++;
    num -= base_val * num_val;
  }
  buffer[curr] = '\0';
  return buffer;
}

int string_split(const string& text, const string& separators, string_vector& words)
{
  string::size_type n = text.size();
  string::size_type start, stop;
  start = text.find_first_not_of(separators);
  while (start != string::npos) {
    stop = text.find_first_of(separators, start);
    if (stop == string::npos)
      stop = n;
    words.push_back(text.substr(start, stop - start));
    start = text.find_first_not_of(separators, stop + 1);
  }
  return words.size();
}

int string_splitex(const string& text, const string& separators, string_vector& words)
{
  string::size_type n = text.size();
  string::size_type start = 0;
  string::size_type stop = n;
  while ((start >= 0) && (start < n)) {
    stop = text.find_first_of(separators, start);
    if (stop == string::npos)
      stop = n;
    words.push_back(text.substr(start, stop - start));
    start = stop + 1;
  }
  return words.size();
}

// void string_replace(std::string& o, std::string& s, std::string& d)
void string_replace(string& o, const char* ss, const char* d)
{
  std::string s(ss);
  string::size_type f = o.find(s, 0);
  if (f != string::npos)
    o.replace(f, s.length(), d);
}

// void string_replace_all(std::string& o, std::string& s, std::string& d)
void string_replace_all(string& o, const char* ss, const char* d)
{
  string s(ss);
  string::size_type f = string::npos;
  while (f) {
    f = o.rfind(s, f);
    if (f != string::npos)
      o.replace(f, s.length(), d);
    else
      break;
  }
}

string& strings_merge(const string_vector& words, const string& separator, string& text)
{
  string_vector::const_iterator i = words.begin();
  while (i != words.end()) {
    text = text + (*i++) + separator;
  }
  return text;
}

int to_int(const std::string& s) { return atoi(s.c_str()); }

string left_trim(const string& s)
{
  string result(s);
#ifdef __BORLANDC__
  result.erase(result.begin(), find_if(result.begin(), result.end(), not1(ptr_fun(std::isspace))));
#else
//  result.erase(result.begin(), std::find_if(result.begin(), result.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
                                              return !std::isspace(ch);
          }));
#endif
  return result;
}

string right_trim(const string& s)
{
  string result(s);
#ifdef __BORLANDC__
  result.erase(find_if(result.rbegin(), result.rend(), not1(ptr_fun(std::isspace))).base(), result.end());
#else
  result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
          }).base(), result.end());
#endif
  return result;
}

string to_lower(const string& s)
{
  string result(s.length(), '\0');
#ifdef __BORLANDC__
  transform(s.begin(), s.end(), result.begin(), std::tolower);
#else
  transform(s.begin(), s.end(), result.begin(), [](unsigned char ch) { return std::tolower(ch); } );
#endif
  return result;
}

string to_upper(const string& s)
{
  string result(s.length(), '\0');
#ifdef __BORLANDC__
  transform(s.begin(), s.end(), result.begin(), ptr_fun(std::toupper));
#else
  transform(s.begin(), s.end(), result.begin(), [](unsigned char ch) { return std::toupper(ch); } );
#endif
  return result;
}



std::string WindowsCaseTrasformFunc(const char* path){
  return path;
}

CaseInsensitiveFilePath::CaseTrasformFunc CaseInsensitiveFilePath::path_transform_function = WindowsCaseTrasformFunc;


} // namespace alib
