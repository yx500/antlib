#include <vcl.h>
#pragma hdrstop
#include <StrUtils.hpp>

#include "propmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
static String _stNULL = "";
static String _stRES = "";
static char ans[255];


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  _Props::reindex()
{
    index.clear();
    BoxType::iterator i = box.begin();
    while (i != box.end()) {
        index[ i->lKey ] = i;
        ++i;
    }
}
void  _Props::erase(const String& key)
{
    BoxType::iterator i = box.begin();
    while (i != box.end()) {
        if (key == i->lKey) {
            box.erase(i);
            break;
        }
        ++i;
    }
    reindex();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//---------------------------------------------------------------------------
TPropMap::TPropMap(): _p()
{
    bNotPutDefault = false;
}
//---------------------------------------------------------------------------
String TPropMap::get(String stKey)
{
    _Props::Elem* i = _p.ElemOf(stKey);
    if (i) return i->lVal;
    return _stNULL;
}
//---------------------------------------------------------------------------
String TPropMap::getOEM(String stKey)
{
    String stVal = get(stKey);
    CharToOem(stVal.c_str(), ans);
    return String(ans);
}
//---------------------------------------------------------------------------
void TPropMap::putOEM(String stKey, String stVal)
{
    OemToChar(stVal.c_str(), ans);
    stVal = String(ans);
    put(stKey, stVal);
}
//---------------------------------------------------------------------------
String TPropMap::getEx(String stKey, void ** ptr)
{
    _Props::Elem* i = _p.ElemOf(stKey);
    if (i) {
        *ptr = i->Obj;
        return i->lVal;
    }
    ptr = NULL;
    return _stNULL;
}
//---------------------------------------------------------------------------
void*  TPropMap::getPtr(String stKey)
{
    _Props::Elem* i = _p.ElemOf(stKey);
    return i ? i->Obj : NULL;
}
//---------------------------------------------------------------------------
void TPropMap::putEx(String stKey, String stVal, void *ptr)
{
    _Props::Elem* i = _p.ElemOf(stKey, true);
    i->lKey = stKey;
    i->lVal = stVal;
    i->Obj = ptr;
}
//---------------------------------------------------------------------------
void TPropMap::putEx(String stKey, String stVal, void * ptr, String stValDef)
{
    if ((bNotPutDefault) && (stVal == stValDef)) {
        _Props::Elem* i = _p.ElemOf(stKey);
        if (i)
            _p.erase(stKey);
    } else {
        putEx(stKey, stVal, ptr);
    }
}
//---------------------------------------------------------------------------
const char * TPropMap::textext(char rkeyval, char rString)
{
    int sz = _p.count();
    if (sz == 0)
        return _stNULL.c_str();

    _stRES = "";
    for (int i = 0; i < sz; i++) {
        const _Props::Elem& e = _p.get(i);
        _stRES = _stRES + e.lKey + rkeyval + e.lVal + rString;
    }
    return _stRES.c_str();
}
//---------------------------------------------------------------------------
#include <string>
#include <sstream>
using namespace std;
void TPropMap::textext(char * szText, char rkeyval, char rString, bool clr)
{
    if (clr)
        _p.clear();
    string kvs_ = string(&rkeyval, 1);
    string ps_ =  string(&rString, 1);

    istringstream buf(szText);
    while (ws(buf).good()) {
        string line;
        getline(buf, line, rString);

        if (!line.size()) continue;

        int p = line.find_first_of(kvs_);

        string key;
        string val;
        if (p != std::string::npos) {
            key.assign(line.substr(0, p));
            val.assign(line.substr(p + 1));
            _Props::Elem* i = _p.ElemOf(String(key.c_str()), true);
            i->lKey = key.c_str();
            i->lVal = val.c_str();
            i->lVal = i->lVal.TrimRight();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TPropMap::SetKeys(int i, String value)
{
    _p.setKey(i, value);
}
//---------------------------------------------------------------------------
String __fastcall TPropMap::GetKeys(int i)
{
    return _p.get(i).lKey;
}
//---------------------------------------------------------------------------
void __fastcall TPropMap::SetVal(int i, String value)
{
    _p.setVal(i, value);
}
//---------------------------------------------------------------------------
String __fastcall TPropMap::GetVal(int i)
{
    return _p.get(i).lVal;
}
//---------------------------------------------------------------------------
void __fastcall TPropMap::SetP(String stKey, String value)
{
    put(stKey, value);
}
//---------------------------------------------------------------------------
String __fastcall TPropMap::GetP(String stKey)
{
    return get(stKey);
}
//---------------------------------------------------------------------------
void TPropMap::addpropmap(TPropMap & pm)
{
    for (int i = 0; i < pm.ItemsCount; i++)
        put(pm.Keys[i], pm.Val[i]);
}
//---------------------------------------------------------------------------
void TPropMap::putpropmapstr(char * sztext)
{
    TPropMap pm;
    pm.text(sztext);
    addpropmap(pm);
}
//---------------------------------------------------------------------------
const char * TPropMap::getpropmapstr(char * sztext)
{
    TPropMap pm;
    pm.text(sztext);
    pm.addpropmap(*this);
    _stRES = pm.text();
    return _stRES.c_str();
}
//---------------------------------------------------------------------------
void TPropMap::AddToStringList(TStringList * SL)
{
    int sz = _p.count();
    for (int i = 0; i < sz; i++) {
        const _Props::Elem& e = _p.get(i);
        SL->Add(e.lKey + "=" + e.lVal);
    }
}
//---------------------------------------------------------------------------
void TPropMap::putkeyvalst(String S)
{
    textext(S.c_str(), '=', '\n', false);
}
//---------------------------------------------------------------------------
TStringList* TPropMap::createStringList()
{
    TStringList *SL = new TStringList();
    this->AddToStringList(SL);
    return SL;
}
//---------------------------------------------------------------------------

