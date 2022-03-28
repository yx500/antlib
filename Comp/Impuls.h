//---------------------------------------------------------------------------

#ifndef ImpulsH
#define ImpulsH
//---------------------------------------------------------------------------
class AComp;
class TAImpuls
{
private:
    int FAbsNumber;
    void __fastcall SetAbsNumber(int value);
    int __fastcall GetAbsNumber();

protected:

public:
    int Chanel;
    int Number;
    bool Invers;

    int Value;
    int LastValue;
    char ImpName[24];

    AComp * Parent;

    TAImpuls();
    ~TAImpuls();
    bool UpdateState();
    void UpdateAbsNumber();

    char * ToString();
    void FromString(const char *stSrc);
#ifndef QT_ANTLIB
    __property int AbsNumber  = { read = GetAbsNumber, write = SetAbsNumber };
#endif


};

char * OldImpToNewStr(int impnumber, AComp * ac);
int  NewStrToOldImp(const char *szStr);

#endif
