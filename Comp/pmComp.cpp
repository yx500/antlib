//---------------------------------------------------------------------------


#include "aheaders_cpp.h"

#include "pmComp.h"

//---------------------------------------------------------------------------



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
void pmComp::SetProp(const char *PropName, const char * value)
{
    _m.clear();
    GetPropMap(_m);
    _m.put(PropName, value);
    SetPropMap(_m);
}
const char *pmComp::GetProp(const char * PropName)
{
    _m.clear();
    GetPropMap(_m);
    S = _m.get(PropName);
    return S.c_str();
}

const char * pmComp::GetPropEx(const char *PropName, int& ptr)
{
    _m.clear();
    GetPropMap(_m);
    int _ptr;
    S = _m.getEx(PropName, _ptr);
    ptr=_ptr;
    return S.c_str();
}

void pmComp::SetPropInt(const char * PropName, int value)
{
    SetProp(PropName, IntToStr(value).c_str());
}
int pmComp::GetPropInt(const char *PropName)
{
    return StrToIntDef(GetProp(PropName), 0);
}
