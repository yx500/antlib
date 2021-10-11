#include <vcl.h>
#pragma hdrstop

#include"out_num.h"

#include "APch.h"
#include "comp.h"
#include "elem.h"
#include "strel.h"
#include "stan.h"
#include "Ways.h"

#include "uEXD.h"
#include "Gor_Logic.h"
#include "tGorka.h"

#define LEFT_        1
#define _RIGHT       2
#define _CENTER_     3


void Box_R_(int x1, int y1, int x2, int y2)// ->
{
    int k[12];
    int x3 = x2 + (y2 - y1) / 2;
    int y3 = y1 + (y2 - y1) / 2;//+1;
//11.10 int c[5];
//11.10 struct  fillsettingstype i;

    k[0] = x1;   k[1] = y1;
    k[2] = x2;   k[3] = y1;
    k[4] = x3;   k[5] = y3;
    k[6] = x2;   k[7] = y2;
    k[8] = x1;   k[9] = y2;
    k[10] = x1;   k[11] = y1;

    //11.10 c[0]=getpixel(x1+1,y1+1);
    //11.10 c[1]=getpixel(x2-1,y2-1);
    //11.10 c[2]=getpixel(x1+1,y2-1);
    //11.10 c[3]=getpixel(x1+1,y2-1);
    //11.10 c[4]=getpixel(x3-1,y3);
    //11.10  getfillsettings(&i);
    /*
    if(
     (c[0]!=i.color)||
     (c[1]!=i.color)||
     (c[2]!=i.color)||
     (c[3]!=i.color)||
     (c[4]!=i.color)
    )
    */
    fillpoly(6, k);
}

void Box_L_(int x1, int y1, int x2, int y2)  // <-
{
    int x3 = x1 - (y2 - y1) / 2;
    int y3 = y1 + (y2 - y1) / 2;//+1;
    int k[12];
//11.10 int c[5];
//11.10 struct  fillsettingstype i;
    k[0] = x1;   k[1] = y1;
    k[2] = x2;   k[3] = y1;
    k[4] = x2;   k[5] = y2;
    k[6] = x1;   k[7] = y2;
    k[8] = x3;   k[9] = y3;
    k[10] = x1;   k[11] = y1;

    //11.10 c[0]=getpixel(x1+1,y1+1);
    //11.10 c[1]=getpixel(x2-1,y2-1);
    //11.10 c[2]=getpixel(x1+1,y2-1);
    //11.10 c[3]=getpixel(x1+1,y2-1);
    //11.10 c[4]=getpixel(x3+1,y3);

    //11.10  getfillsettings(&i);
    fillpoly(6, k);
}




//-------------------------------------------------------
// ”г­ЄжЁп Їа®аЁб®ўЄЁ ­®¬Ґа  б Є®­вга®¬
//-------------------------------------------------------
void Box_(int x, int y, int dr , int n, int Js)
{
//        if(n>300) return;
    int len, h1, f1 = 0;
//11.10 struct  fillsettingstype i;
//11.10 getfillsettings(&i);
// if(i.color==TXT){ f =1;/*setfillstyle(1,FON);*/}
    char *nom = "      ";
    int nm = n;
    int clr = LIN;
    itoa(nm % 1000, nom + 1, 10); nom[0] = '#';
    if (CurrentPicture == LT) {
        _SetText(TIMES12, CENTER_TEXT, CENTER_TEXT);
        len   = textwidth("8888");
        h1    = (textheight(nom) * 2) / 3 + 4;
        y     = y - (h1 + 1) / 2 + 3;

    } else {
        _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT); f1 = 2;
        len   = textwidth("8888");
        h1    = textheight(nom);
        y     = y - (h1 + 1) / 2 + 1;
    }

    switch (Js) {
    case LEFT_   :
        break;
    case _RIGHT  :
        x -= len;
        break;
    case _CENTER_:
        x -= len / 2;
        break;
    }
    if (n == -99) {
        setcolor(FON);
        setfillstyle(1, FON);
        Box_L_(x - 1,  y , x + len + 1, y + h1 + f1);
        Box_R_(x - 1,  y , x + len + 1, y + h1 + f1);
        return;
    }
    setcolor(C_D);
    setfillstyle(1, clr);
    dr = n % 2 + 1;
    if (dr == 2)  Box_L_(x - 1,  y , x + len + 1, y + h1 + f1);
    if (dr == 1)  Box_R_(x - 1,  y , x + len + 1, y + h1 + f1);
    if ((clr == KRA) || (clr == CYAN_m)) setcolor(TXT);
    OutTextXY(x + len / 2, y + h1 / 2, nom);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}






//struct TRect;

String  GetNumStr(TTrainInfo * TI)
{
    String ST;
    if (TI->TrainNumber != 0) ST = IntToStr(TI->TrainNumber); else
        ST = "???";

    if (ST.Length() == 1) ST = "  " + ST + " "; else if (ST.Length() == 2) ST = " " + ST + " "; else if (ST.Length() == 3) ST = ST + " ";

    if ((TI->TrainNumber > 9000))
        ST = " ";

    return ST;
}
TPoint _points[6];
int    _clr[6] = {C_D, C_D, C_D, C_D, C_D, C_D};
int    _clr2[6] = {C_D, C_D, C_D, C_D, C_D, C_D};
int    _clr2FON[6] = {FON, FON, FON, FON, FON, FON};
const xx = 6;

void _MakePoints(int X0, int Y0, int Width, int Height, int direct)
{
    _points[0] = Point(X0 + xx, Y0);
    _points[1] = Point(X0 + Width - xx, Y0);
    _points[2] = Point(X0 + Width - xx, Y0 + Height / 2);
    _points[3] = Point(X0 + Width - xx, Y0 + Height - 1);
    _points[4] = Point(X0 + xx, Y0 + Height - 1);
    _points[5] = Point(X0 + xx, Y0 + Height / 2);
    //_points[6] = Point(X0+xx,Y0);
    if (direct == 3) {
        _points[2] = Point(X0 + Width, Y0 + Height / 2);
        _points[5] = Point(X0, Y0 + Height / 2);
    } else if (direct == 1) {
        _points[2] = Point(X0 + Width, Y0 + Height / 2);
    } else {
        _points[5] = Point(X0, Y0 + Height / 2);
    }
}
int GetTNBrushClr(TTrainInfo * TI);
int GetTNPenClr(TTrainInfo * TI);

int  GetTNDirect(int N, bool TRAINNUM_INVERS)
{

    int d = 3;
    if (N > 0) d = 1 - N % 2;
    if (EXD.TN_Ver == 3) d = 0;
    if ((TRAINNUM_INVERS) && (d <= 1)) d = 1 - d;
    return d;
}

void CheckUslDraw(AComp *AC, bool &bs, bool &bdbl)
{
    bs = true;
    bdbl = false;
    switch (AC->GetType()) {
    case WAY:
    case PLOT:
    case BL_UH:break;
    case BLOK:if (CurrentPicture==BG)bs=false;
        break;

    case SWRT :
    case SWLT :
    case SWLB :
    case SWRB :
    case SWL  :
    case SWKT :
    case SWKB :
    case SWrt :
    case SWlt :
    case SWlb :
    case SWrb:
    case SWrtW:
    case SWltW:
    case SWlbW:
    case SWrbW:
    case Y_STREL_1 :
    case Y_STREL_2 :
    case GORL_L:
    case GORL_R:
    case Y_STREL_3:
    case Y_STREL_4:
    case G_STREL_Y:
    case G_RC:
    case G_ZAMI:
    case G_ZKR:
    case G_STREL_1:
    case G_ZAMP:
    case G_STREL_2:
    case G_KZP2:

    case GORL:   bdbl=true; break;
    default:bs=false;
    }
}

void EXD_HideTrainNumber(AComp *AC)
{
    Ways * wAC = dynamic_cast<Ways*>(AC);
    if (wAC == NULL) return;
    // Нужно ли стирать ?
    if (wAC->TrainInfo.TrainNumber == 0) return;
    int X, Y, Width, Height, direct;
    String ST;
    bool bs = true;
    bool bdbl = false;
    CheckUslDraw(wAC, bs, bdbl);
    if (!bs) return;
    if (((AC->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                                ((AC->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) return;


    TTrainInfo * TI = EXD.TN_GetTN(wAC->impuls_busi, wAC->Stan()->Dat->filename, wAC->Stan()->Name4Canal(abs(wAC->impuls_busi) / 1000), bdbl);
    if (TI != NULL) return;
    /* стираем номер*/
    direct = GetTNDirect(wAC->TrainInfo.TrainNumber, wAC->AO->TRAINNUM_INVERS);
    ST = GetNumStr(&wAC->TrainInfo);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
    Width = 2 * xx + textwidth(ST.c_str());
    Height = textheight(ST.c_str()) + 1;

    GetNumberRct(AC, X, Y, Width, Height, direct);
    _MakePoints(X, Y, Width, Height, direct);
    setfillstyle(SOLID_FILL, FON);
    PolyColor(FON, _points, _clr2FON, 6);
    memset(&wAC->TrainInfo, 0, sizeof(wAC->TrainInfo));
    //delete AC->TrainInfo;
    //AC->TrainInfo=NULL;
    wAC->StateChanged = true;
}

void EXD_UpdateTrainNumber(AComp *AC, int rimpb)
{
    bool bs = true;
    bool bdbl = false;

    Ways * wAC = dynamic_cast<Ways*>(AC);
    if (wAC == NULL)
        return;

    CheckUslDraw(wAC, bs, bdbl);
    if (!bs) return;
    if (((AC->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                                ((AC->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) return;

    int X, Y, Width, Height, direct;

    TTrainInfo * TI;
    Bl_uh * Bluh;
    if (wAC->GetType() == BL_UH) {
        Bluh = (Bl_uh *)wAC;
        TI = EXD.TN_GetTN(Bluh->impuls_plus, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(Bluh->impuls_plus) / 1000), bdbl);
        if (TI == NULL)
            TI = EXD.TN_GetTN(Bluh->impuls_kzm, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(Bluh->impuls_kzm) / 1000), bdbl);
    } else {
        TI = EXD.TN_GetTN(AC->impuls_busi, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(AC->impuls_busi) / 1000), bdbl);
    }

    String ST;
    if ( ((TI != NULL)&&(memcmp(&wAC->TrainInfo, TI, sizeof(TTrainInfo))!=0))||
         ((TI == NULL)&&(wAC->TrainInfo.TrainNumber!=0))
    ) wAC->StateChanged=true;

    if (TI != NULL) {
       memcpy(&wAC->TrainInfo, TI, sizeof(TTrainInfo));
    } else {
       memset(&wAC->TrainInfo, 0, sizeof(TTrainInfo));
    }
}


void EXD_ShowTrainNumber(AComp *AC, int rimpb)
{
    bool bs = true;
    bool bdbl = false;

    Ways * wAC = dynamic_cast<Ways*>(AC);
    if (wAC == NULL)
        return;

    CheckUslDraw(wAC, bs, bdbl);
    if (!bs) return;
    if (((AC->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                                ((AC->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) return;

    int X, Y, Width, Height, direct;
    TTrainInfo * TI;
    Bl_uh * Bluh;
    if (wAC->GetType() == BL_UH) {
        Bluh = (Bl_uh *)wAC;
        TI = EXD.TN_GetTN(Bluh->impuls_plus, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(Bluh->impuls_plus) / 1000), bdbl);
        if (TI == NULL)
            TI = EXD.TN_GetTN(Bluh->impuls_kzm, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(Bluh->impuls_kzm) / 1000), bdbl);
    } else {
        TI = EXD.TN_GetTN(AC->impuls_busi, AC->Stan()->Dat->filename, AC->Stan()->Name4Canal(abs(AC->impuls_busi) / 1000), bdbl);
    }

    String ST;
    if (TI != NULL) {
        direct = GetTNDirect(TI->TrainNumber, wAC->AO->TRAINNUM_INVERS);
        ST = GetNumStr(TI);
        _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
        Width = 2 * xx + textwidth(ST.c_str());
        Height = textheight(ST.c_str()) + 1;
    }

    if (TI != NULL) {
        //if (AC->TrainInfo==NULL)
        //   AC->TrainInfo=new TTrainInfo;
        memcpy(&wAC->TrainInfo, TI, sizeof(TTrainInfo));

        GetNumberRct(wAC, X, Y, Width, Height, direct);
        if ((TI->Reserv2[0]>0)&& (TI->Reserv2[0]<10)){
                if (direct==0) X=X+Width; else  X=X-Width;
        }
        _MakePoints(X, Y, Width, Height, direct);
        int clr = GetTNBrushClr(&wAC->TrainInfo);
        if (rimpb == 1) {
            setfillstyle(SOLID_FILL, clr);
            PolyColor(clr, _points, _clr, 6);
        } else {
            setfillstyle(EMPTY_FILL, clr);
            memset(_clr2, clr, sizeof(_clr2));
            PolyColor(clr, _points, _clr2, 6);
        }
        clr = GetTNPenClr(&wAC->TrainInfo);
        setcolor(clr);
        DrawText(X + xx, Y - 1, Width + 100, Height, ST.c_str());
    }
}
TTrainInfo * __fastcall  MakeTrainInfo(void * TNdata, int Ver);
int ShowTrainNumbers_nn;
void EXD_ShowTrainNumbers(AComp *AC, int rimpb)
{
    bool bs = true;
    bool bdbl = false;

    Ways * wAC = dynamic_cast<Ways*>(AC);
    if (wAC == NULL)
        return;

    CheckUslDraw(wAC, bs, bdbl);
    if (!bs) return;
    if (((AC->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                                ((AC->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) return;

    int X, Y, Width, Height, direct;
    int cnt=0;
    t_NewDescr*  DD=GetDescr_imp1_all(AC->impuls_busi,cnt);

    for (int i=0;i<cnt;i++){
        TTrainInfo * TI= MakeTrainInfo(&DD[i].D, 3) ;
        if (TI==NULL) break;
        String ST;
        direct = GetTNDirect(1, wAC->AO->TRAINNUM_INVERS);
        ST = GetNumStr(TI);
        _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
        Width = 2 * xx + textwidth(ST.c_str());
        Height = textheight(ST.c_str()) + 1;
        memcpy(&wAC->TrainInfo, TI, sizeof(TTrainInfo));
        ShowTrainNumbers_nn=i;
        GetNumberRct(wAC, X, Y, Width, Height, direct);
        if (Y>=10000) continue;
        //int xdv=-(cnt-i-1)*Width;
        //X=X+xdv;

        _MakePoints(X, Y, Width, Height, direct);
        int clr = GetTNBrushClr(&wAC->TrainInfo);
        if (rimpb == 1) {
            setfillstyle(SOLID_FILL, clr);
            PolyColor(clr, _points, _clr, 6);
        } else {
            setfillstyle(EMPTY_FILL, clr);
            memset(_clr2, clr, sizeof(_clr2));
            PolyColor(clr, _points, _clr2, 6);
        }
        clr = GetTNPenClr(&wAC->TrainInfo);
        setcolor(clr);
        DrawText(X + xx, Y - 1, Width + 100, Height, ST.c_str());
    }
}


bool GetNumberRct(AComp *AC, int &X, int &Y, int Width, int Height, int direct)
{
    if (AC == NULL)return false;
    bool bs = false;
    switch (AC->GetType()) {
    case WAY   :
    case PLOT  :
    case BL_UH :
        AC->GetNumberPosition(X, Y, Width, Height, direct);
        bs = true;
        break;
    case POIN  :
    case BLOK  :
        if (CurrentPicture == BG) {
            bs = false;
        } else {
            AC->GetNumberPosition(X, Y, Width, Height, direct);
            bs = true;
        }
        break;
    default : AC->GetNumberPosition(X, Y, Width, Height, direct);
        bs = true;
    }
    return bs;
}

int GetTNBrushClr(TTrainInfo * TI)
{
    int cl = 0;
    if (TI->TrainColor > 15) {
        if ((TI->TrainNumber >= 1) && (TI->TrainNumber <= 999)) cl = 207; else //красный
                if ((TI->TrainNumber >= 1000) && (TI->TrainNumber <= 4999)) cl = 236; else //синий
                        if ((TI->TrainNumber >= 5000) && (TI->TrainNumber <= 5999)) cl = 251; else //желтый
                                if ((TI->TrainNumber >= 6000) && (TI->TrainNumber <= 6999)) cl = 221; else //зеленый
                                        if ((TI->TrainNumber >= 7000) && (TI->TrainNumber <= 8999)) cl = 251; else     //желтый
                            cl = 246;
    } else {
        cl = KROSHBCOL[TI->TrainColor];
    }
    return cl;
}
int GetTNPenClr(TTrainInfo * TI)
{
    int cl = 0;
    if (TI->TrainColor > 15) {
        if ((TI->TrainNumber >= 1) && (TI->TrainNumber <= 999)) cl = 246; else if ((TI->TrainNumber >= 1000) && (TI->TrainNumber <= 4999)) cl = 246; else if ((TI->TrainNumber >= 5000) && (TI->TrainNumber <= 5999)) cl = 0; else if ((TI->TrainNumber >= 6000) && (TI->TrainNumber <= 6999)) cl = 246; else if ((TI->TrainNumber >= 7000) && (TI->TrainNumber <= 8999)) cl = 0; else
            cl = 246;
    } else {
        cl = KROSHPCOL[TI->TrainColor];
    }
    return cl;
}





/*
static int _imp0=0;
TrNum:: TrNum(){
     imp_busy=&_imp0;
     impuls_kmu=&_imp0;
     impuls_mu=&_imp0;
     pWay=NULL;
     bMustClear=false;
     bTI=false;
}

void TrNum::UpdateState()
{
     AComp::UpdateState();

     TTrainInfo * TI=EXD.TN_GetTN(impuls_busi, pWay->Stan()->Dat->filename, pWay->Stan()->Name4Canal(abs(impuls_busi)/1000),false);



     if ( (IsClrMig(clr))  ) StateChanged=true;

}

void TrNum::Show()
{
     bool bs=true;
     bool bdbl=false;

     int X, Y, Width, Height,direct;
     TTrainInfo * TI=&pWay->TrainInfo;


     String ST;
     // нет ничего - ничего не рисуем
     // информацию получаем от компоненты родителя
     if (wAC->TrainInfo.)


     if (TI!=NULL){
        direct=GetTNDirect(TI->TrainNumber,wAC->AO->TRAINNUM_INVERS);
        ST=GetNumStr(TI);
        _SetText(F_DEFAULT,LEFT_TEXT,TOP_TEXT);
        Width=2*xx+textwidth(ST.c_str());
        Height=textheight(ST.c_str())+1;
     }
     if (TI!=NULL){
        //if (AC->TrainInfo==NULL)
        //   AC->TrainInfo=new TTrainInfo;
        memcpy(&wAC->TrainInfo,TI,sizeof(TTrainInfo));

        GetNumberRct(wAC,X, Y, Width, Height,direct);
        _MakePoints(X, Y, Width, Height,direct);
        int clr=GetTNBrushClr(&wAC->TrainInfo);
        if (rimpb==1) {
            setfillstyle(SOLID_FILL,clr);
            PolyColor(clr,_points,_clr,6);
        } else {
            setfillstyle(EMPTY_FILL,clr);
            memset(&_clr2,clr,sizeof(&_clr2));
            PolyColor(clr,_points,_clr2,6);
        }
        clr=GetTNPenClr(&wAC->TrainInfo);
        setcolor(clr);
        DrawText(X+xx,Y-1,Width,Height,ST.c_str());
     }


}

*/
