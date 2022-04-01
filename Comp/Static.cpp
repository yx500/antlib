
#include "aheaders_cpp.h"
#include "APch.h"

#include "static.h"


#include "Scrin.h"
#include "col.h"

#include "propmap.h"


AText::AText():AComp()
{
    x=0;
    y=0;
    bInGrid=false;
}

void AText::Set()
{
    AComp::Set();
    memset(name, 0, sizeof(name));
    OemToCharBuff(MEM.name, name, 15);
    //strncpy(name,MEM.name,15);
}
void AText::SetPropMap(TPropMap &m)
{
    AComp::SetPropMap(m);
    strncpy(name, m.get("ñìÈÌß").c_str(), sizeof(name));
    bInGrid =   m.geti("ëãInGrid");
}

void AText::Get()
{
    AComp::Get();
    MEM.impuls_busi = 0;
    MEM.impuls_plus = 0;
    MEM.impuls_mnus = 0;
    MEM.impuls_kzm = 0;
    MEM.Nomer = 0;
    memset(MEM.name, 0, sizeof(MEM.name));
    CharToOemBuff(name, MEM.name, 15);
    //strncpy(MEM.name,name,15);
}



void AText::GetPropMap(TPropMap &m)
{
    AComp::GetPropMap(m);
    m.put("ñìÈÌß", name);
    m.put("ëãInGrid", bInGrid,0);
}



char * AText::GetName()
{
    return name;
}

void AText::UpdateState()
{
    StateChanged = false;
}
//void Lini::Show(){ ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);}
void AText::Go()
{
    bool b = StateChanged;
    UpdateState();
    if (b || StateChanged) Show();
    StateChanged = false;
}
void AText::Show()
{
    x = X * MUL_X + _X_;
    y = Y * MUL_Y + _Y_;

}


int iii = 0;
void  Name::Show()
{
    AText::Show();
    if (Current_Name && (CurrentPicture == BG)) clr = 1;
    else  clr = 0;

    _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
    int a;
///  â® ¤ãà æª¨© á¤¢¨£­ §¢ ­¨ï áâ ­æ¨©
    int _DELTA_X = (1280 - 640 - 10) / 2;
    int dlt = _DELTA_X / 10;

    if (AO->Sdv_nazv) dlt = 0;

    if (CurrentPicture == LT) {
        // _SetText(TIMES30b,CENTER_TEXT,CENTER_TEXT);
        // _SetText(COURE28,CENTER_TEXT,CENTER_TEXT);
        // _SetText(COURE28b,CENTER_TEXT,CENTER_TEXT);
        _SetText(TIMES28, CENTER_TEXT, CENTER_TEXT);
        a = textwidth(name) / 2 + 10;
        if (AO->TypName == 2) {
            Super_Box_(AO->MaxX / 2 - a - 10, 30 - 15 - 2 - 2, AO->MaxX / 2 + a + 10, 30 + 15, 1, C_D, C_D, LIN, LIN, 27);
            setcolor(C_D);
//          setcolor(TXT);
            OutTextXY(AO->MaxX / 2, 30, name);
        } else {
            setcolor(TXT);
            if (mas == 1) setcolor(C_D);
            if (AO->TypName != 3) OutTextXY(x, y, name);
        }

    } else {
        _SetText(COURE16, CENTER_TEXT, CENTER_TEXT);
        if (clr) {
            setfillstyle(1, BOLOT); setcolor(C_D);
        } else    {
            setfillstyle(1, FON); setcolor(FON);
        }
        //a=textwidth(name)/2;
        //b=textheight(name)+2;
        //barx(x-a-4,y-b/2+dlt,x+a+4,y+b/2+1+dlt); // óáðàë èç-çà òàáëî
        if (bNameBlack) setcolor(C_D); else setcolor(TXT);
        OutTextXY(x, y + dlt, name);
    }
//  ‚ëå®¤
    setfillstyle(1, LIN);
    setcolor(LIN);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}
TYP  Name::GetType()
{
    return NAME;
}

Mess::Mess()
{
  ux_allign=uy_allign=u_font=u_fontsize=u_color=0;
}

static String _MessPropName[] = {
    "öôxallign",          // 0
    "öôyallign",          // 1
    "öôfont",          // 2
    "öôfontsize",          // 3
    "öôcolor"         // 4
};

void Mess::GetPropMap(TPropMap &m)
{
    AText::GetPropMap(m);
    int _n = 0;
    m.put(_MessPropName[_n++], ux_allign, 0);
    m.put(_MessPropName[_n++], uy_allign, 0);
    m.put(_MessPropName[_n++], u_font, 0);
    m.put(_MessPropName[_n++], u_fontsize, 0);
    m.put(_MessPropName[_n++], u_color, 0);
}

void Mess::SetPropMap(TPropMap &m)
{
    AText::SetPropMap(m);
    int _n = 0;
    ux_allign  = m.geti(_MessPropName[_n++]);
    uy_allign  = m.geti(_MessPropName[_n++]);
    u_font     = m.geti(_MessPropName[_n++]);
    u_fontsize = m.geti(_MessPropName[_n++]);
    u_color    = m.geti(_MessPropName[_n++]);
}

void  Mess::Show()
{
    AText::Show();
// if(MUL_Y>10){

    int x_allign=CENTER_TEXT;
    int y_allign=CENTER_TEXT;
    int clr=TXT;
    int font=F_DEFAULT;
    if (mas) {
        clr=BLUE_m;
        font=F_LITT;
    }

    switch (ux_allign){
      case 1: x_allign=LEFT_TEXT;break;
      case 2: x_allign=RIGHT_TEXT;break;
    }
    switch (uy_allign){
      case 1: y_allign=TOP_TEXT;break;
      case 2: y_allign=BOTTOM_TEXT;break;
    }
    if (u_color!=0) clr=u_color;
    if (u_font!=0) font=u_font;


    if ((MUL_Y > 2) && (CurrentPicture == LT) || (masy > 0)) {
        _SetText(font, x_allign, y_allign);
        if (u_fontsize!=0)_SetTextSize(u_fontsize);
        setcolor(clr);
        OutTextXY(x, y, name);
        _SetTextSize(1);
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    }

}
TYP  Mess::GetType()
{
    return MESS;
}

void  Stn::Show()
{
    if (CurrentPicture == BG)return;
    if (!AO->ShowBottomPeregons) return;
    AText::Show();
    if (!bInGrid){
        x = (x - _X_) / MUL_X;
        y = (y - _Y_) / MUL_Y;
        y += DELTA_Y - 5;
        x += DELTA_X;
    } else {
        x = X * MUL_X/2 + _X_;
        y = Y * MUL_Y/2 + _Y_;
    }
    int s[14];
    int l = ST_SIZE / 4;
    s[0] = x;                      s[1] = y;
    s[2] = x + l;                    s[3] = y - SH_ST_2;
    s[4] = x - l + ST_SIZE;            s[5] = y - SH_ST_2;
    s[6] = x + ST_SIZE;              s[7] = y;
    s[8] = x - l + ST_SIZE;            s[9] = y + SH_ST_2;
    s[10] = x + l;                    s[11] = y + SH_ST_2;
    s[12] = x;                      s[13] = y;
    setcolor(TXT);
    setfillstyle(1, COLOR_F_PRG);
    fillpoly(7, s);
    _SetText(F_DEFAULT, CENTER_TEXT, BOTTOM_TEXT);
    OutTextXY(x + l*2, y - SH_ST_2 - 8, name);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}
TYP Stn::GetType()
{
    return FISH;
}

void  StnL::Show()
{
    if (CurrentPicture == BG)return;
    if (!AO->ShowBottomPeregons) return;
    AText::Show();
    if (!bInGrid){
        x = (x - _X_) / MUL_X;
        y = (y - _Y_) / MUL_Y;
        y += DELTA_Y - 5;
        x += DELTA_X;
    } else {
        x = X * MUL_X/2 + _X_;
        y = Y * MUL_Y/2 + _Y_;
    }

    int s[12];
    int l = ST_SIZE / 4;
    s[0] = x;                      s[1] = y - SH_ST_2;
    s[2] = x - l + ST_SIZE / 2;          s[3] = y - SH_ST_2;
    s[4] = x + ST_SIZE / 2;            s[5] = y;
    s[6] = x - l + ST_SIZE / 2;          s[7] = y + SH_ST_2;
    s[8] = x;                      s[9] = y + SH_ST_2;
    s[10] = x;                      s[11] = y - SH_ST_2;
    setcolor(TXT);
    setfillstyle(1, COLOR_F_PRG);
    fillpoly(6, s);
    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    OutTextXY(x, y - SH_ST_2 - 8, name);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}
TYP  StnL::GetType()
{
    return FISH_L;
}

void  StnR::Show()
{
    if (CurrentPicture == BG)return;
    if (!AO->ShowBottomPeregons) return;
    AText::Show();
    if (!bInGrid){
        x = (x - _X_) / MUL_X;
        y = (y - _Y_) / MUL_Y;
        y += DELTA_Y - 5;
        x += DELTA_X;
    } else {
        x = X * MUL_X/2 + _X_;
        y = Y * MUL_Y/2 + _Y_;
    }
    int s[12];
    int l = ST_SIZE / 4;
    s[0] = x;                      s[1] = y;
    s[2] = x + l;                    s[3] = y - SH_ST_2;
    s[4] = x + ST_SIZE / 2;            s[5] = y - SH_ST_2;
    s[6] = x + ST_SIZE / 2;            s[7] = y + SH_ST_2;
    s[8] = x + l;                    s[9] = y + SH_ST_2;
    s[10] = x;                      s[11] = y;
    setcolor(TXT);
    setfillstyle(1, COLOR_F_PRG);
    fillpoly(6, s);
    _SetText(F_DEFAULT, RIGHT_TEXT, BOTTOM_TEXT);
    OutTextXY(x + l*2, y - SH_ST_2 - 8, name);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}
TYP StnR::GetType()
{
    return FISH_R;
}

typedef AText* PAText;



void  Version::Show()
{


    if (MOD == ED) {
        AText::Show();
        _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
        setcolor(LIN);
        OutTextXY(x, y, name);

        setfillstyle(1, LIN);
        _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
    }
}
TYP  Version::GetType()
{
    return VERSION;
}

