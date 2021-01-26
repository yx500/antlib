//---------------------------------------------------------------------------


#pragma hdrstop

#include "pmComp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static TPropMap _m;
static String S;

const char * pmComp::GetPropMapStr(int ver)
{
    _m.clear();
    //_m.ver=ver;
    GetPropMap(_m);
    S = _m.text();
    return S.c_str();
}

void pmComp::SetPropMapStr(char * szSrc)
{
    _m.text(szSrc);
    SetPropMap(_m);
}
void __fastcall pmComp::SetProp(char * PropName, char * value)
{
    _m.clear();
    GetPropMap(_m);
    _m.put(PropName, value);
    SetPropMap(_m);
}
char * __fastcall pmComp::GetProp(char * PropName)
{
    _m.clear();
    GetPropMap(_m);
    S = _m.get(PropName);
    return S.c_str();
}

char * __fastcall pmComp::GetPropEx(char * PropName, void ** ptr)
{
    _m.clear();
    GetPropMap(_m);
    S = _m.getEx(PropName, ptr);
    return S.c_str();
}

void __fastcall pmComp::SetPropInt(char * PropName, int value)
{
    SetProp(PropName, IntToStr(value).c_str());
}
int __fastcall pmComp::GetPropInt(char * PropName)
{
    return StrToIntDef(GetProp(PropName), 0);
}
