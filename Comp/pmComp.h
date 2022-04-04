//---------------------------------------------------------------------------

#ifndef pmCompH
#define pmCompH
//---------------------------------------------------------------------------

#include "ACom_T.h"
#include "propmap.h"

// абстрактный класс для использования пм

class  pmComp
{

private:

public:

    void  SetProp(const char * PropName, const char *value);
    const char *  GetProp(const char *PropName);
    void  SetPropInt(const char *PropName, int value);
    int  GetPropInt(const char * PropName);

    virtual void GetPropMap(TPropMap &m) = 0;
    virtual void SetPropMap(TPropMap &m) = 0;

    const char *GetPropEx(const char * PropName, int& ptr);
    const char * GetPropMapStr(int ver = 1);
    void SetPropMapStr(char * szSrc);
#ifndef QT_ANTLIB
    __property const char * Prop[const char * PropName]  = { read = GetProp, write = SetProp };
    __property int PropInt[const char * PropName]  = { read = GetPropInt, write = SetPropInt };
#endif
};


#endif
