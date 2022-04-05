#include "aheaders_cpp.h"

#include "Impuls.h"
#include "Comp.h"
#include "Stan.h"
#include "common.h"
#include <string>
#include <stdio.h>

#include <cstring>

//---------------------------------------------------------------------------

extern T_GetSigName_Func _GetSigName_Func;

TAImpuls::TAImpuls()
{
    Chanel = 0;
    Number = 0;
    FAbsNumber = 0;
    Invers = false;

    Value = 0;
    LastValue = -1;
    memset(ImpName, 0, sizeof(ImpName));
    Parent = NULL;
}

TAImpuls::~TAImpuls()
{
    // TODO: Add your source code here
}
extern T_f_Func _f_;
bool TAImpuls::UpdateState()
{
    LastValue = Value;
    if (FAbsNumber == 0)
        Value = 0;
    else if (FAbsNumber == -1)
        Value = 1;
    else if (FAbsNumber == -2)
        Value = 0;
    else

        //
        if (Parent != NULL)
        {
            Value = Parent->f(Chanel * 1000 + Number);
        }
        else
        {
            if (_f_ == NULL)
                Value = 33;
            else
                Value = _f_(FAbsNumber, this);
        }
    if (Invers)
    {
        if (Value == 0)
            Value = 1;
        else if (Value == 1)
            Value = 0;
    }
    return (LastValue != Value);
}

void TAImpuls::UpdateAbsNumber()
{
    // в этой ф-ии зна€ станцию и канал в ней находим абс.номер

    if ((Number == -1) || (Number == -2))
    {
        FAbsNumber = Number;
    }
    else
    {
        FAbsNumber = 0;
        if ((Parent != NULL) && (Parent->Stan() != NULL) && (Chanel >= 0) && (Chanel < 255))
        {
            Station *S = Parent->Stan();
            FAbsNumber = S->ChanelOffset[Chanel] + Number;
        }
    }
}
char _razd = ':';
String IntToStrF(int N, int Width)
{
    if (N < 0)
    {
        return IntToStr(N);
    }
    String S = IntToStr(N);
    int l = S.Length();
    for (int i = 0; i < Width - l; i++)
        S = "0" + S;

    return S;
}
static char _buf[32];
char *_fff = "%03d:%04d:%1d:%02d:%s";
char *TAImpuls::ToString()
{
    std::string st;
    // Chanel:Number:Invers:Value
    // 001:0002:1:00:assa
    // 1234567890123
    char *szImpName;
    if (_GetSigName_Func != NULL)
    {
        szImpName = _GetSigName_Func(FAbsNumber);
        strncpy(ImpName, szImpName, sizeof(ImpName) - 1);
    }

    //     printf(_buf,"%3d%c%4d%c%1d%c %1d%c%s",Chanel,_razd,Number,_razd,Invers,_razd,Value,_razd,ImpName);
    sprintf(_buf, _fff, Chanel, Number, Invers, Value, ImpName);

    /*S=IntToStrF(Chanel,3)+_razd+
      IntToStrF(Number,4)+_razd+
      IntToStrF(Invers,1)+_razd+
        " "+

      IntToStrF(Value,1)+_razd+
      ImpName;
      */
    return _buf;
}
void TAImpuls::FromString(const char *szSrc)
{
    // int _r[5]={4,9,11,14,14};
    // Chanel:Number:Invers:Value
    // 001:0002:1:00:assa
    // 12345678901234
    memset(ImpName, 0, sizeof(ImpName));
    ;
    std::string stSrc(szSrc);
    if (stSrc == "")
    {
        Chanel = 0;
        Number = 0;
        Invers = 0;
        Value = 0;
        return;
    }
    if (stSrc == "-1")
    {
        Chanel = 0;
        Number = -1;
        Invers = 0;
        Value = 1;
        return;
    }
    if (stSrc == "-2")
    {
        Chanel = 0;
        Number = -2;
        Invers = 0;
        Value = 0;
        return;
    }
    // если просто номер - то просто и присваеваем
    if (stSrc.find(_razd) == std::string::npos)
    {
        int NN = atoi(stSrc.c_str());
        Invers = 0;
        Value = 0;
        if (NN <= -1000)
        {
            Invers = 1;
            NN = -NN;
        }
        Chanel = NN / 1000;
        Number = NN % 1000;
        return;
    }

    // if ((stSrc.length()!=_r[3])||(stSrc[_r[0]]!=_razd)||(stSrc[_r[1]]!=_razd)||(stSrc[_r[2]]!=_razd)){

    // if ((stSrc.Length()!=_r[3])||(stSrc[_r[0]]!=_razd)||(stSrc[_r[1]]!=_razd)||(stSrc[_r[2]]!=_razd)){
    //≈сли правильно форматнуть, то можно и побыстрее
    /*  int iv=0;

      String s="";
      memset(_r,0,sizeof(_r));
      _r[4]=stSrc.length();
      for (int i=1;i<=stSrc.length();i++){
           if (iv>4) break;
           if (stSrc[i]==_razd){
              _r[iv]=i;iv++;
           }
      }
    }
    scanf
    Chanel=      StrToIntDef(stSrc.substr() SubString(1,            _r[0]-1),0);
    Number=      StrToIntDef(stSrc.SubString(_r[0]+1,_r[1]-_r[0]-1),0);
    Invers=(bool)StrToIntDef(stSrc.SubString(_r[1]+1,_r[2]-_r[1]-1),0);
    Value=       StrToIntDef(stSrc.SubString(_r[2]+1,_r[3]-_r[2]-1),0);
    ImpName=                 stSrc.SubString(_r[3]+1,_r[4]-_r[3]);
    */

    // sscanf(stSrc.c_str(), "%03d:%04d:%1d:%02d",&Chanel,&Number,&Invers,&Value);
    sscanf(stSrc.c_str(), _fff, &Chanel, &Number, &Invers, &Value, ImpName);

    UpdateAbsNumber();
}

char *OldImpToNewStr(int impnumber, AComp *ac)
{
    TAImpuls IMP;
    IMP.Parent = ac;
    if ((impnumber == -1) || (impnumber == -2))
    {
        IMP.Chanel = 0;
        IMP.Number = impnumber;
        IMP.Invers = false;
    }
    else
    {
        if (impnumber < 0)
            IMP.Invers = true;
        impnumber = abs(impnumber);
        IMP.Chanel = impnumber / 1000;
        IMP.Number = impnumber % 1000;
    }
    IMP.UpdateAbsNumber();
    // IMP.UpdateState(); ??? непон€тно зачем
    return IMP.ToString();
}

int NewStrToOldImp(const char *szStr)
{
    TAImpuls IMP;
    IMP.FromString(szStr);
    int impnumber = IMP.Chanel * 1000 + IMP.Number % 1000;
    if (impnumber >= 1000)
    {
        if (IMP.Invers)
            impnumber = -impnumber;
    }
    return impnumber;
}

void __fastcall TAImpuls::SetAbsNumber(int value)
{
    if (abs(value) < 1000)
    {
        Number = value;
        FAbsNumber = value;
        return;
    }
    if ((Parent != NULL) && (Parent->Stan() != NULL))
    {
        Station *STAN = Parent->Stan();
        int chnoff = value / 1000 * 1000;
        for (int i = 1; i < 255; i++)
        {
            if (chnoff == STAN->ChanelOffset[i])
            {
                Chanel = i;
                Number = /*i*1000 + */ value % 1000;
                FAbsNumber = value;
                return;
            }
        }
        // MessageDlg(IntToStr(value)+" Ќе ¬ходит в список каналов станции", mtError  , TMsgDlgButtons() << mbOK , 0);
        Qui(" Ќе ¬ходит в список каналов станции", 1, 1);
    }
    else
    {
        FAbsNumber = value;
        Number = value;
    }
}
int __fastcall TAImpuls::GetAbsNumber()
{
    return FAbsNumber;
}
