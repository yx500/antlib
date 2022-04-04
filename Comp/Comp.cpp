//---------------------------------------------------------------------------

#include "aheaders_cpp.h"

#include "common.h"
#include "Comp.h"
#include "Vatempl.h"
#include "Stan.h"
#include "Polig.h"
#include "bgi.h"
#include "Impuls.h"
#include"out_num.h"
#include "uParString.h"
#include "col.h"

T_f_Func _f_ = NULL;
T_f2_Func _f2_ = NULL;
T_GetSigName_Func _GetSigName_Func = NULL;
T_GetDatagramData_Func GetDatagramData_Func = NULL;
T_GetDatagramPacket2_Func GetDatagramPacket2_Func = NULL;
bool ALIB_ShowMarkers=false;

void Set_f_Func(T_f_Func A_f_)
{
    _f_ = A_f_;
}
void Set_f2_Func(T_f2_Func A_f2_)
{
    _f2_ = A_f2_;
}
void Set_T_GetSigName_Func(T_GetSigName_Func AGetSigName_Func)
{
    _GetSigName_Func = AGetSigName_Func;
};
void Set_GetDatagramData_Func(T_GetDatagramData_Func AGetDatagramData_Func)
{
    GetDatagramData_Func = AGetDatagramData_Func;
};

void Set_GetDatagramPacket2_Func(T_GetDatagramPacket2_Func AGetDatagramPacket2_Func)
{
    GetDatagramPacket2_Func = AGetDatagramPacket2_Func;
};


void AComp::Hide(void)
{
    Color_Off(); Show(); Color_On();
}
void AComp::Move(int DeltaX, int DeltaY)
{
    Hide();
    X += DeltaX;
    Y += DeltaY;
    Show();
}

void AComp::Clear()
{
    StateChanged = true;
}


AComp::AComp()
{
    AO = NULL;
    ID = 0;
    X = 0;
    Y = 0;
    mas = 0;
    masy = 0;
    masx2 = 0;
    pr = 0;
    impuls_busi = 0;
    fimpuls_busi = 0;
    Data = NULL;
    Tag = 0;
    memset(&ExtPriz, 0, sizeof(ExtPriz));

    iMacro = 0;

    ExtFocus = 0;
    memset(pNext, 0, sizeof(pNext));
    pmRepl = NULL;
    memset(name, 0, sizeof(name));
    memset(Pad,0,sizeof(Pad));

    clr=0;
    _clr=0;
    pVisibleArray=NULL;
    Tagstr.clear();
    StateChanged=false;
    ExtFocus=0;
}

unsigned int  AComp::GetID()
{
    return ID;
}
void AComp::SetID(unsigned int AID)
{
    ID = AID;
}

AComp::~AComp()
{
    if (pmRepl != NULL) delete pmRepl;
}

const char* AComp::GetIDObj()
{
    Station* s = AComp::Stan();
    if (this->GetID() != 0
            && s != 0
            && s->FileName()
       ) {
        static char tmp[256];
        String S(s->FileName());
        S = S.Trim().UpperCase();
        sprintf(tmp, "%s:%d", S.c_str(), this->GetID());
        return tmp;
    }
    return 0;
}

Station* AComp::Stan()
{
    if (pVisibleArray == NULL) return NULL;
    return pVisibleArray->pStation;
}

Poligon* AComp::Polig()
{
    if (Stan() == NULL) return NULL;
    return Stan()->pPoligon;
}



int  AComp::f(int impls)
{
    if (impls == 0)  return 0;
    if (impls == -1) return 1;
    if (impls == -2) return 0;
    if ((_f_ == NULL) && (_f2_ == NULL)) {
        //return 33;
        throw "_f_ not defined!";
    }

    unsigned  imp;
    int r = 33;
    if ((impls <= -1000)) {
        imp = abs(impls);
    } else {
        imp = impls;
    }
    if (imp < 1000) return 0;
    if (imp / 1000 >= 255) return 33;

    if (_f2_) {  // ôóíêöèÿ ïî íàçâàíèþ êàíàëà è íîìåðó èìïóëüñà
        Station* STAN = Stan();
        r = _f2_(imp, STAN->ChanelNames[imp/1000]);
    } else {      // ñòàðûé âàðèàíò
        Station* STAN = Stan();
        if ((STAN != NULL)) {
            if (STAN->ChanelOffset[imp/1000] > 0)
                r = _f_(STAN->ChanelOffset[imp/1000] + imp % 1000, this); else
                r = 33;
        }
    }


    if ((impls <= -1000)) {
        if (r == 0) r = 1; else if (r == 1) r = 0;
    }
    return r;

}

int  AComp::GetRealImp(int impls)
{
    signed int imp;
    if ((impls < 0)) {
        imp = abs(impls);
    } else {
        imp = impls;
    }
    if (imp < 1000) return impls;
    if (imp / 1000 >= 255) return impls;
    int ii = imp;
    Station* STAN = Stan();
    if ((STAN != NULL)) {
        if (STAN->ChanelOffset[imp/1000] > 0) {
            ii = STAN->ChanelOffset[imp/1000] + imp % 1000;
        }
    }
    if ((impls < 0)) {
        ii = -ii;
    }
    return ii;
}

bool   AComp::SetNativeImp(int RealImpls, short int &NativeImp)
{
    if (abs(RealImpls) < 1000) {
        NativeImp = RealImpls;
        return true;
    }
    unsigned int imp;
    signed int NatImp = -1;
    if ((RealImpls < 0)) {
        imp = abs(RealImpls);
    } else {
        imp = RealImpls;
    }

    Station* STAN = Stan();
    {
        int chnoff = imp / 1000 * 1000;
        for (int i = 1; i < 255; i++) {
            if (chnoff == STAN->ChanelOffset[i]) {
                NatImp = i * 1000 + imp % 1000/*-STAN->ALL_CHANELS_OFFSET*/;
                break;
            }
        }
    }
    if (NatImp < 0) return  false;


    if ((RealImpls < 0))
        NatImp = -NatImp;

    NativeImp = NatImp;
    return true;
}
int   AComp::GetNativeImp(int RealImpls)
{

    if (abs(RealImpls) < 1000) {
        return RealImpls;
    }

    unsigned int imp;

    if ((RealImpls < 0)) {
        imp = abs(RealImpls);
    } else {
        imp = RealImpls;
    }
    signed int NatImp = imp;

    Station* STAN = Stan();
    int chnoff = imp / 1000 * 1000;
    for (int i = 1; i < 255; i++) {
        if (chnoff == STAN->ChanelOffset[i]) {
            NatImp = i * 1000 + RealImpls % 1000;
            break;
        }
    }
    if ((RealImpls < 0))
        NatImp = -NatImp;

    return RealImpls;
}

int AComp::TstXY(int, int)
{
    return 0;
}

void AComp::Go()
{
    UpdateState();
    Show();
}

void AComp::UpdateRCT()
{
    ClearBgiCoverRect();
    Show();
    RCT = GetBgiCoverRect();
}


void AComp::Set()
{
    X = MEM.X_;
    Y = MEM.Y_;
    mas = MEM.mas;
    masy = MEM.masy;
    masx2 = MEM.masx2;
    impuls_busi = MEM.impuls_busi;
    //if (GetType()!=LAMP)
    ExtPriz = MEM.ExtPriz;
    iMacro = MEM.iMacro;
}
void AComp::Get()
{
    MEM.type = GetType();
    MEM.X_ = X;
    MEM.Y_ = Y;
    MEM.mas = mas;
    MEM.impuls_busi = impuls_busi;

    MEM.masy = masy;
    MEM.masx2 = masx2;
    //if (GetType()!=LAMP)
    MEM.ExtPriz = ExtPriz;
    MEM.iMacro = iMacro;
}


static char _ACompPropName[25][20] = {
    "öôID"   ,          // 0
    "öôtype" ,          // 1
    "öôX_"   ,          // 2
    "öôY_"   ,          // 3
    "öômas"  ,          // 4
    "öômasy" ,          // 5
    "öômasx2",          // 6
    "òñimpuls_busi",    // 7
    "ëãNoShowYch",      // 8
    "ëãNoShowStan",     // 9
    "ëãMEM2",           // 10
    "ëãUseInRevizor",   // 11
    "ëãUseInCommLmp",   // 12
    "öôiMacro",         // 13
    "ëãNoShowYchAct",   // 14
    "ëãNoShowExtInfo",  // 15
    "ñìPad1xy",         // 16
    "ñìPad1cmd",        // 17
    "ñìPad1param",      // 18
    "ñìPad2xy",         // 19
    "ñìPad2cmd",        // 20
    "ñìPad2param",      // 21
    "ñìPad3xy",         // 22
    "ñìPad3cmd",        // 23
    "ñìPad3param"       // 24

};
void AComp::GetPropMap(TPropMap &m)
{

    m.put(_ACompPropName[0], GetID());
    m.put(_ACompPropName[1], GetType());
    m.put(_ACompPropName[2], X);
    m.put(_ACompPropName[3], Y);
    m.put(_ACompPropName[4], mas,       0);
    m.put(_ACompPropName[5], masy,      0);
    m.put(_ACompPropName[6], masx2,     0);
    m.putEx(_ACompPropName[7], OldImpToNewStr(impuls_busi, this), GetRealImp(impuls_busi), OldImpToNewStr(0, this));
    m.put(_ACompPropName[8], ExtPriz.NoShowYch,       0);
    m.put(_ACompPropName[9], ExtPriz.NoShowStan,      0);
    m.put(_ACompPropName[10], ExtPriz.MEM2,           0);
    m.put(_ACompPropName[11], ExtPriz.UseInRevizor,   0);
    m.put(_ACompPropName[12], ExtPriz.UseInCommLmp,   0);
    m.put(_ACompPropName[13], iMacro,                 0);
    m.put(_ACompPropName[14], ExtPriz.NoShowYchAct,   0);
    m.put(_ACompPropName[15], ExtPriz.NoShowExtInfo,  0);
    for (int i=0;i<3;i++){
        int xy=0;
        for (int j=0;j<8;j++) xy+=abs(Pad[i].xy[j]);
        String stxy="";
        if (xy>0){
           stxy=IntToStr(Pad[i].xy[0]);
           for (int j=1;j<8;j++) stxy=stxy+";"+IntToStr(Pad[i].xy[j]);
        }
        m.put("ñìPad"+IntToStr(i+1)+"xy",    stxy , "");
        m.put("ñìPad"+IntToStr(i+1)+"cmd",   Pad[i].cmd,    "" );
        m.put("ñìPad"+IntToStr(i+1)+"param", Pad[i].param,  "" );
    }

    if (pmRepl != NULL) {
        for (int i = 0; i < pmRepl->GetItemsCount(); i++) {
            m.put(pmRepl->Keys[i], pmRepl->Val[i]);
        }
    }

}
void AComp::SetPropMap(TPropMap &m)
{

    SetID(m.geti(_ACompPropName[0]));

    X =    m.geti(_ACompPropName[2]);
    Y =    m.geti(_ACompPropName[3]);
    mas =  m.geti(_ACompPropName[4]);
    masy = m.geti(_ACompPropName[5]);
    masx2 = m.geti(_ACompPropName[6]);

    impuls_busi = NewStrToOldImp(m.get(_ACompPropName[7]).c_str());
    ExtPriz.NoShowYch = m.geti(_ACompPropName[8]);
    ExtPriz.NoShowStan = m.geti(_ACompPropName[9]);
    ExtPriz.MEM2 = m.geti(_ACompPropName[10]);
    ExtPriz.UseInRevizor  = m.geti(_ACompPropName[11]);
    ExtPriz.UseInCommLmp  = m.geti(_ACompPropName[12]);
    iMacro = m.geti(_ACompPropName[13]);
    ExtPriz.NoShowYchAct = m.geti(_ACompPropName[14]);
    ExtPriz.NoShowExtInfo = m.geti(_ACompPropName[15]);

    for (int i=0;i<3;i++){
        String stxy=m.get("ñìPad"+IntToStr(i+1)+"xy");
        if (stxy!=""){
                TParString ps("",";");
                ps.SetVal(stxy);
                for (int j=0;j<8;j++) Pad[i].xy[j]=ps.GetInt(j,0);
        }
        strncpy(Pad[i].cmd,  m.get("ñìPad"+IntToStr(i+1)+"cmd").c_str(),sizeof(Pad[i].cmd));
        strncpy(Pad[i].param,m.get("ñìPad"+IntToStr(i+1)+"param").c_str(),sizeof(Pad[i].param));
    }



    for (int i = 0; i < m.GetItemsCount(); i++) {
        String stKeys = m.Keys[i];
        if ((stKeys.Length() >= 1) && (m.Keys[i][1] == '$')) {
            if (pmRepl == NULL) pmRepl = new TPropMap();
            pmRepl->put(m.Keys[i], m.Val[i]);
        }
    }
}




const char * AComp::GetImpulsName(char * PropName)
{
    static String _S;
    if (_GetSigName_Func == NULL) return "";
    int imp;
    _S = GetPropEx(PropName, imp);
    if (_S == "") return "";

    _S = _GetSigName_Func(imp);
    return _S.c_str();
}

/*
void _PST(String &ST,String Key, char * Val){
     ST=ST+"\n"+Key+"="+String(Val);
}
void _PST(String &ST,String Key, int Val){
     ST=ST+"\n"+Key+"="+IntToStr(Val);
}
*/

void AComp::UpdateState()
{};

/*static TImpPropNamesInfo _IPNI;

int AComp::GetUsedImpulsCount()
{
    _GetImpPropNamesInfo(this, _IPNI);
    return _IPNI.ImpCount;
}
char * AComp::GetUsedImpulsInfo(int NumImpProp, int &RealOffset)
{
    _GetImpPropNamesInfo(this, _IPNI);
    if (NumImpProp < _IPNI.ImpCount) {
        RealOffset = _IPNI.RealOffset[NumImpProp];
        return _IPNI.ImpName[NumImpProp];
    }
    return _IPNI.ImpName[0];
}

int  AComp::GetImpulsInfo(int aimp, const char* &CnlName, int &RealOffset)
{
    Station* STAN = this->Stan();
    if (STAN != NULL) {
        int  ch = abs(aimp / 1000); //íîìåð êàíàëà
        int  im = aimp % 1000; //íîìåð èìï
        if (STAN->ChanelNames[ch][0] != 0) {
            CnlName = STAN->ChanelNames[ch];
            RealOffset = STAN->ChanelOffset[ch] + im;
            return 1;
        } else {
            CnlName = "NONE";
            RealOffset = aimp;
            return 0;
        }
    }
    return 0;
}

char * AComp::GetImpulsInfo2(char * PropName, int &RealOffset)
{
    static String _S;
    static TAImpuls _IMP;
    if (_GetSigName_Func == NULL) return "";
    _S = GetProp(PropName);
    if (_S == "") return "";
    _IMP.Parent = this;
    _IMP.FromString(_S.c_str());
    _S = _GetSigName_Func(_IMP.AbsNumber);

    return _S.c_str();
}

char * AComp::GetImpulsInfo3(char * PropName, const char* &CnlName, int &RealOffset)
{
    static String _S;
    static TAImpuls _IMP;
    Station* STAN = this->Stan();
    if (_GetSigName_Func == NULL) return "";
    _S = GetProp(PropName);
    if (_S == "") return "";
    _IMP.Parent = this;
    _IMP.FromString(_S.c_str());
    RealOffset = _IMP.AbsNumber;
    CnlName = STAN->ChanelNames[_IMP.Chanel];
    if (_IMP.Invers) RealOffset = -RealOffset;
    _S = _GetSigName_Func(_IMP.AbsNumber);
    return _S.c_str();
}
*/

void AComp::ShowTrainNumber() {};
void AComp::HideTrainNumber() {};

int AComp::IsAlarmState()
{
    if (fimpuls_busi == 1) return impuls_busi;
    return false;
}

void AComp::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    X = this->X * MUL_X + _X_;
    Y = this->Y * MUL_Y + _Y_;
}

/*
static String _SS_GetCompInfo;
char * AComp::GetCompInfo()
{
    _SS_GetCompInfo = "";
    //name;ObjID;packet_name;busy;plus;minus;kzm
    String packet_name = "";
    String ss;
    int imp;
    String impname;
    imp = impuls_busi;

    char* CnlName;
    int RealOffset;
    impname = "";
    GetImpulsInfo(imp, CnlName, RealOffset);
    ss = String(CnlName);
    if ((ss != "NONE")) packet_name = ss;
    if (_GetSigName_Func != NULL) {
        impname = _GetSigName_Func(RealOffset);
    }
    _SS_GetCompInfo = String(GetName()) + ";" +
                      IntToStr(GetID()) + ";" +
                      packet_name + ";" +
                      IntToStr(imp) + ";" + impname + ";0;0;0";

    return _SS_GetCompInfo.c_str();
}
*/
char* AComp::GetText(char *txt)
{
    strcpy(txt, Com_Nam[GetType()]);
    strncat(txt, GetName(), CN);
    return txt;
}

char * AComp::GetName()
{
    return name;
}


int AComp::GetMarkerAtXY(int X, int Y)
{
    if (!ALIB_ShowMarkers) return 0;
    int aX,aY;
    for (int i=0;i<GetMarkerCount();i++){
        GetMarkerPoint(i+1,aX,aY);
        if ((X>=aX-4) && (Y<=aY+4) && (X<=aX+4) && (Y>=aY-4)) return i+1;
    }
    return 0;
}

void AComp::ShowPads()
{
     for (int p=0;p<3;p++){
                       int s=0;
                       int xy[8];
                       for (int pj=0;pj<8;pj++) s+=abs(Pad[p].xy[pj]);
                       if (s>0){
                          for (int pj=0;pj<4;pj++) {
                              xy[pj*2]=  (X+Pad[p].xy[pj*2])*MUL_X+_X_;
                              xy[pj*2+1]=(Y+Pad[p].xy[pj*2+1])*MUL_Y+_Y_;
                          }
                          setcolor(GELT);
                          setfillstyle(EMPTY_FILL, GELT);
                          fillpoly(4, xy);
                       }
     }
}

