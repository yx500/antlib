//---------------------------------------------------------------------------

#ifndef pmCompH
#define pmCompH
//---------------------------------------------------------------------------

#include "ACom_T.h"
#include "propmap.h"

// абстрактный класс для использования пм

class  _ALIB_ pmComp
{

private:

public:

    void __fastcall SetProp(char * PropName, char * value);
    char * __fastcall GetProp(char * PropName);
    void __fastcall SetPropInt(char * PropName, int value);
    int __fastcall GetPropInt(char * PropName);

    virtual void GetPropMap(TPropMap &m) = 0;
    virtual void SetPropMap(TPropMap &m) = 0;

    char * __fastcall GetPropEx(char * PropName, void ** ptr);
    const char * GetPropMapStr(int ver = 1);
    void SetPropMapStr(char * szSrc);
#ifndef QT_ANTLIB
    __property char * Prop[char * PropName]  = { read = GetProp, write = SetProp };
    __property int PropInt[char * PropName]  = { read = GetPropInt, write = SetPropInt };
#endif
};


#endif
