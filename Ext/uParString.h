#ifndef uParStringH
#define uParStringH
//---------------------------------------------------------------------------
#include "aheaders_h.h"

#include <string>
#include <vector>

/*
      Класс TParString для работы со строками с разделителями
      Эффективен для чтения CSV строк
*/
class TParString
{
private:
    typedef std::vector<std::string> stringvector;
    stringvector words;
    std::string separators; // строка разделителей.
    // Разделитель - 1 символ.При формирования резулт. строки исп. первый символ.
    bool cont; // рассматривать несколько разд. подряд как один.

public:
    TParString(const String &ASTR, const String &achr = ";", bool acont = false);
    ~TParString() {}

    void SetVal(const String &ASTR);
    String ResultStr();
    int GetParamsCount();

    String GetStr(int ind, const String &DefaultStr = "");
    void SetStr(int ind, const String &StrVal);

    int GetInt(int ind, int DefaultVal = 0);
    void SetInt(int ind, signed int IntVal);
    void SetHex(int ind, signed int IntVal);

    int GetInd(const String &stPar);

    String operator[](int i) { return GetStr(i); }
    TParString &operator=(const String &st)
    {
        SetVal(st);
        return *this;
    }

#ifdef __BORLANDC__
    __property int ParamsCount = {read = GetParamsCount};
#endif
};

void SplitString(const String &ST, AStringList *SL, const String &chBreak);
String MakeSplitString(AStringList *SL, char chBreak);

#ifdef __BORLANDC__
void SplitString(const String &ST, TStringList *SL, const String &chBreak);
String MakeSplitString(TStringList *SL, char chBreak);
#endif

#endif
