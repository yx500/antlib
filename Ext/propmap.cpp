#include "propmap.h"

#include "aheaders_cpp.h"

#include <sstream>
#include <string>
using namespace std;

void PropertyMapDetails::reindex()
{
  index.clear();
  std::vector<Elem>::iterator i = box.begin();
  for (size_t i = 0; i < box.size(); ++i)
    index[box[i].lKey] = &box[i];
}

void PropertyMapDetails::erase(const String& key)
{
  std::vector<Elem>::iterator i = box.begin();
  while (i != box.end()) {
    if (key == i->lKey) {
      box.erase(i);
      break;
    }
    ++i;
  }
  reindex();
}

TPropMap::TPropMap() : props()
{
  bNotPutDefault = false;
}

String TPropMap::get(const String& stKey)
{
  PropertyMapDetails::Elem* i = props.ElemOf(stKey);
  if (i)
    return i->lVal;
  return "";
}

String TPropMap::getOEM(const String& stKey)
{
  String stVal = get(stKey);
  static char tmp[255];
  CharToOem(stVal.c_str(), tmp);
  return tmp;
}

void TPropMap::putOEM(const String& stKey, String stVal)
{
  static char tmp[255];
  OemToChar(stVal.c_str(), tmp);
  put(stKey, String(tmp));
}

String TPropMap::getEx(const String& stKey, int& ptr)
{
  PropertyMapDetails::Elem* i = props.ElemOf(stKey);
  if (i) {
    ptr = i->Obj;
    return i->lVal;
  }
  ptr = 0;
  return "";
}

int TPropMap::getPtr(const String& stKey)
{
  PropertyMapDetails::Elem* i = props.ElemOf(stKey);
  return i ? i->Obj : 0;
}

void TPropMap::putEx(const String& stKey, String stVal, int ptr)
{
  PropertyMapDetails::Elem* i = props.ElemOf(stKey, true);
  i->lKey = stKey;
  i->lVal = stVal;
  i->Obj = ptr;
}

void TPropMap::putEx(const String& stKey, String stVal, int ptr, String stValDef)
{
  if ((bNotPutDefault) && (stVal == stValDef)) {
    PropertyMapDetails::Elem* i = props.ElemOf(stKey);
    if (i)
      props.erase(stKey);
  } else {
    putEx(stKey, stVal, ptr);
  }
}

const char* TPropMap::textext(char rkeyval, char rString)
{
  int sz = props.count();
  if (sz == 0)
    return "";

  static String _stRES;
  _stRES = "";
  for (int i = 0; i < sz; i++) {
    const PropertyMapDetails::Elem& e = props.get(i);
    _stRES = _stRES + e.lKey + rkeyval + e.lVal + rString;
  }
  return _stRES.c_str();
}

void TPropMap::textext(const char* szText, char rkeyval, char rString, bool clr)
{
  if (clr)
    props.clear();
  string kvs_ = string(&rkeyval, 1);
  string ps_ = string(&rString, 1);

  istringstream buf(szText);
  while (ws(buf).good()) {
    string line;
    getline(buf, line, rString);

    if (!line.size())
      continue;

    int p = line.find_first_of(kvs_);

    string key;
    string val;
    if (p != std::string::npos) {
      key.assign(line.substr(0, p));
      val.assign(line.substr(p + 1));
      PropertyMapDetails::Elem* i = props.ElemOf(String(key.c_str()), true);
      i->lKey = key.c_str();
      i->lVal = val.c_str();
      i->lVal = i->lVal.Trim();
    }
  }
}

void TPropMap::SetKeys(int i, const String& value)
{
  props.setKey(i, value);
}

String TPropMap::GetKeys(int i)
{
  return props.get(i).lKey;
}

void TPropMap::SetVal(int i, const String& value)
{
  props.setVal(i, value);
}

String TPropMap::GetVal(int i)
{
  return props.get(i).lVal;
}

void TPropMap::SetP(const String& stKey, const String& value)
{
  put(stKey, value);
}

String TPropMap::GetP(const String& stKey)
{
  return get(stKey);
}

void TPropMap::addpropmap(TPropMap& pm)
{
  for (int i = 0; i < pm.GetItemsCount(); i++)
    put(pm.GetKeys(i), pm.GetVal(i));
}

void TPropMap::putpropmapstr(char* sztext)
{
  TPropMap pm;
  pm.text(sztext);
  addpropmap(pm);
}

const char* TPropMap::getpropmapstr(char* sztext)
{
  TPropMap pm;
  pm.text(sztext);
  pm.addpropmap(*this);
  static String _stRES;
  _stRES = pm.text();
  return _stRES.c_str();
}

void TPropMap::putkeyvalst(String S)
{
  textext(S.c_str(), '=', '\n', false);
}

AStringList* TPropMap::createStringList()
{
  AStringList* SL = new AStringList();
  this->AddToStringList(SL);
  return SL;
}

void TPropMap::AddToStringList(AStringList* SL)
{
  int sz = props.count();
  for (int i = 0; i < sz; i++) {
    const PropertyMapDetails::Elem& e = props.get(i);
    SL->Add(e.lKey + "=" + e.lVal);
  }
}

#ifdef __BORLANDC__
#include <StrUtils.hpp>
void TPropMap::AddToStringList(TStringList* SL)
{
  int sz = props.count();
  for (int i = 0; i < sz; i++) {
    const PropertyMapDetails::Elem& e = props.get(i);
    SL->Add(e.lKey + "=" + e.lVal);
  }
}
#endif
