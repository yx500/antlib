#include "uParString.h"

#include "aheaders_cpp.h"

using namespace std;

TParString::TParString(const String& ASTR, const String& achr, bool acont)
    : words()
{
  words.reserve(32);
  cont = acont;
  separators = achr.c_str();
  SetVal(ASTR);
}

int TParString::GetParamsCount()
{
  return words.size();
}

void TParString::SetVal(const String& ASTR)
{
  words.clear();
  if (ASTR.Length() == 0)
    return;
  if (!cont) {
    alib::string_splitex(ASTR.c_str(), separators, words);
  } else {
    alib::string_split(ASTR.c_str(), separators, words);
  }
}

String TParString::GetStr(size_t ind, const String& def)
{
  if ((ind >= words.size()) || (ind < 0))
    return def;
  String s = words.at(ind).c_str();
  if (s.IsEmpty())
    return def;
  return s;
}

int TParString::GetInt(size_t ind, int def)
{
  if ((ind >= words.size()) || (ind < 0))
    return def;
  String s = words.at(ind).c_str();
  return s.ToIntDef(def);
}

void TParString::SetStr(size_t ind, const String& StrVal)
{
  if (ind >= words.size()) {
    words.resize(ind + 1, "");
  }
  words[ind] = StrVal.c_str();
}

String TParString::ResultStr()
{
  String STR = "";
  for (size_t i = 0; i < words.size(); i++) {
    STR = STR + words[i].c_str();
    if (i < words.size() - 1)
      STR = STR + separators[0];
  }
  return STR;
}

void TParString::SetInt(size_t ind, signed int IntVal)
{
  SetStr(ind, IntToStr(IntVal));
}

// void TParString::SetHex(size_t ind, signed int IntVal)
// {
//   SetStr(ind, "0x" + IntToHex(IntVal, 2));
// }

int TParString::GetInd(const String& stPar)
{
  for (int i = 0; i < words.size(); i++)
    if (stPar == words[i].c_str())
      return i;
  return -1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SplitString(const String& ST, AStringList* SL, const String& chBreak)
{
  String s = "";
  SL->Clear();
  for (int i = 1; i <= ST.Length(); i++) {
    if (chBreak.Pos(String(ST[i])) != 0) {
      s = s.Trim();
      SL->Add(s);
      s = "";
    } else
      s = s + ST[i];
  }
  s = s.Trim();
  if (s != "")
    SL->Add(s);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String MakeSplitString(AStringList* SL, char chBreak)
{
  String s = "";
  for (int i = 0; i < SL->Size() - 1; i++)
    s = s + SL->At(i) + chBreak;
  if (SL->Size() >= 1)
    s = s + SL->At(SL->Size() - 1);
  return s;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef __BORLANDC__
void SplitString(const String& ST, TStringList* SL, const String& chBreak)
{
  String s = "";
  SL->Clear();
  for (int i = 1; i <= ST.Length(); i++) {
    if (chBreak.Pos(ST[i]) != 0) {
      s = s.TrimLeft();
      s = s.TrimRight();
      SL->Add(s);
      s = "";
    } else
      s = s + ST[i];
  }
  s = s.Trim();
  if (s != "")
    SL->Add(s);
}

String MakeSplitString(TStringList* SL, char chBreak)
{
  String s = "";
  for (int i = 0; i < SL->Count - 1; i++)
    s = s + SL->Strings[i] + chBreak;
  if (SL->Count >= 1)
    s = s + SL->Strings[SL->Count - 1];
  return s;
}
#endif
