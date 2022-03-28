#ifndef uParStringH
#define uParStringH
//---------------------------------------------------------------------------
#include <string>
#include <vector>


/*
      Класс TParString для работы со строками с разделителями
      Эффективен для чтения CSV строк
*/
class TParString
{
private:
    typedef std::vector<std::string>     stringvector;
    static int string_split(const std::string & text, const std::string& separators, stringvector & words);
    static int string_splitex(const std::string & text, const std::string& separators, stringvector & words);

    stringvector words;
    std::string  separators;       // строка разделителей.
    // Разделитель - 1 символ.При формирования резулт. строки исп. первый символ.
    bool cont;        // рассматривать несколько разд. подряд как один.

public:

    __fastcall TParString(String ASTR, String achr = ";", bool acont = false);
    ~TParString() {}

    void __fastcall SetVal(String ASTR);
    String __fastcall ResultStr();
    int __fastcall GetParamsCount();

    String __fastcall GetStr(int ind, String DefaultStr = "");
    void __fastcall SetStr(int ind, String StrVal);

    int  __fastcall GetInt(int ind, int DefaultVal = 0);
    void __fastcall SetInt(int ind, signed int IntVal);
    void __fastcall SetHex(int ind, signed int IntVal);

    int __fastcall GetInd(String stPar);

    String operator [](int i) {
        return GetStr(i);
    };
    TParString& operator = (const String& st) {
        SetVal(st); return *this;
    }
#ifndef QT_ANTLIB
    __property int ParamsCount  = { read = GetParamsCount };
#endif
};



void __fastcall SplitString(String  ST, TStringList * SL, String chBreak);
String  __fastcall MakeSplitString(TStringList * SL, char chBreak);

//---------------------------------------------------------------------------
#endif
