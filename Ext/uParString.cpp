#include "aheaders_cpp.h"

#include "uParString.h"


using namespace std;

int TParString::string_split(const string & text, const string& separators, stringvector & words)
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
//---------------------------------------------------------------------------
int TParString::string_splitex(const string & text, const string& separators, stringvector & words)
{
    string::size_type n = text.size();
    string::size_type start = 0;
    string::size_type stop = n;
    while ((start >= 0) && (start <= n)) {
        stop = text.find_first_of(separators, start);
        if (stop == string::npos)
            stop = n;
        words.push_back(text.substr(start, stop - start));
        start = stop + 1;
    }
    return words.size();
}
//---------------------------------------------------------------------------
TParString::TParString(const String& ASTR, const String& achr, bool acont)
        : words()
{
    words.reserve(32);
    cont = acont;
    separators = achr.c_str();
    SetVal(ASTR);
}
//---------------------------------------------------------------------------
int TParString::GetParamsCount()
{
    return words.size();
}
//---------------------------------------------------------------------------
void TParString::SetVal(const String &ASTR)
{
    words.clear();
    if (ASTR.Length()==0) return;
    if (!cont) {
        string_splitex(ASTR.c_str(), separators, words);
    } else {
        string_split(ASTR.c_str(), separators, words);
    }
}
//---------------------------------------------------------------------------
String TParString::GetStr(int ind, const String &def)
{
    if ((ind >= words.size()) || (ind < 0))
        return def;
    String s = words.at(ind).c_str();
    if (s.IsEmpty())
        return def;
    return s;
}
//---------------------------------------------------------------------------
int TParString::GetInt(int ind, int def)
{
    if ((ind >= words.size()) || (ind < 0))
        return def;
    String s = words.at(ind).c_str();
    return s.ToIntDef(def);
}
//---------------------------------------------------------------------------
void TParString::SetStr(int ind, const String &StrVal)
{
    if (ind >= words.size()) {
        words.resize(ind + 1, "");
    }
    words[ind] = StrVal.c_str();
}
//---------------------------------------------------------------------------
String TParString::ResultStr()
{
    String STR = "";
    for (int i = 0; i < words.size(); i++) {
        STR = STR + words[i].c_str();
        if (i < words.size() - 1)STR = STR + separators[0];
    }
    return STR;
}
//---------------------------------------------------------------------------
void TParString::SetInt(int ind, signed int IntVal)
{
    SetStr(ind, IntToStr(IntVal));
}
//---------------------------------------------------------------------------
void TParString::SetHex(int ind, signed int IntVal)
{
    SetStr(ind, "0x" + IntToHex(IntVal, 2));
}
//---------------------------------------------------------------------------
int TParString::GetInd(const String &stPar)
{
    for (int i = 0; i < words.size(); i++)
        if (stPar == words[i].c_str())
            return i;
    return -1;
}
//---------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SplitString(const String &ST, TStringList * SL, const String &chBreak)
{
    String s = "";
    SL->Clear();
    for (int i = 1; i <= ST.Length(); i++) {
        if (chBreak.Pos(ST[i]) != 0) {
            s = s.TrimLeft(); s = s.TrimRight();
            SL->Add(s);
            s = "";
        } else s = s + ST[i];
    }
    s = s.TrimLeft(); s = s.TrimRight();
    if (s != "")SL->Add(s);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String  MakeSplitString(TStringList * SL, char chBreak)
{
    String s = "";
    for (int i = 0; i < SL->Count - 1; i++)
        s = s + SL->Strings[i] + chBreak;
    if (SL->Count >= 1)s = s + SL->Strings[SL->Count-1];
    return s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

