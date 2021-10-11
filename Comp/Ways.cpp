//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Ways.h"

#include "Str_fun.h"

#include "APch.h"

#include "Lamps.h"
#include "scrin.h"
#include "col.h"
#include "f.h"
#include "Impuls.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
void ShowPictText(int x, int y, void * AGE, char * szText, int YS);
/*  ========================= Way ==================*/

Way:: Way()
{
    LenUV = 0;
    MyFishk = 0;
    clr = LIN;
    styll1 = 1;
    clrp=C_D;
    
}

void Way::ChangeMarkerXY(int iMarker,int aX,int aY)
{
     if (iMarker==1){
       int X1=(aX-_X_)/MUL_X;
       mas+=X-X1;
       X=X1;
     }
     if (iMarker==2){
       mas=(aX-(X * MUL_X + _X_))/MUL_X-WAY_X;
     }
}
void Way::GetMarkerPoint(int iMarker,int &aX,int &aY)
{
    if (iMarker==1){aX=X * MUL_X + _X_;aY=Y * MUL_Y + _Y_;}
    if (iMarker==2){aX=X * MUL_X + _X_+(WAY_X + mas) * MUL_X;aY=Y * MUL_Y + _Y_;}
}

void Way::UpdateState()
{
    Ways::UpdateState();

    // выставляем цвет
    clr = Clr_Set2(fimpuls_busi, fimpuls_plus);
    if (clr == LIN) clrp=LIN_W; else
        clrp=C_D;
    // исскуственная разделка
    if ((impuls_IR != 0) && (fimpuls_IR == 1)) {
            if (clr == COLOR_B) clr = COLOR_IR_B; else if (clr == COLOR_SET) clr = COLOR_IR_Z; else
                clr = COLOR_IR_F;
    }
    if ((impuls_predSEIR != 0) && (fimpuls_predSEIR == 1)) {
        clrp=KRA_BEL;
    }
    if (bShowUIR) {
        clrp = SV_MIG;
    }

    // несовпадение занятости/свободности
    if ((impuls_busi!=0)&&(impuls_svob!=0)){
       if ((fimpuls_busi+fimpuls_svob==0)||(fimpuls_busi+fimpuls_svob==2))
          clrp=KRA_BEL;
    }


    // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
    if ((IsClrMig(clr))) StateChanged = true;
    if ((IsClrMig(clrp))) StateChanged = true;

}
extern int len_4;
void  Way:: Show()
{
    //      int dr;
    LenUV = masx2;
    //SetGradientFactor(1.*(masx2+10.)/10.);

    //if (!AO->bDopPriznak) masy=0;

    int xx = X * MUL_X + _X_;
    int yy1 = Y * MUL_Y + _Y_;
    int yy2 = (Y + masy) * MUL_Y + _Y_;


    int s = 1;
    int len;
    int len_t;
    len_t = strlen(name) * 4;
    len = (WAY_X + mas) * MUL_X;
    setcolor(TXT);

    if (impuls_busi == 0) clr = FON;
    
    setfillstyle(1, clr);
    setcolor(clrp);
    setfillstyle(styll1, clr);

    int Bs[10];
    if (masy != 0) {
        //int sw=1;
        //len_4=0;
        //sh_y+=2;
        //KT(xx,yy1+sh+1,len,sw,0);
        //sh_y-=2;
        //fillpoly(8,kr);

        Bs[0] = xx + 1;     Bs[1] = yy1 - sh_y / 2 - 1;
        Bs[2] = xx + len - 1; Bs[3] = yy2 - sh_y / 2 - 1;
        Bs[4] = xx + len - 1; Bs[5] = yy2 - sh_y / 2 + sh_y + 1;
        Bs[6] = xx + 1;     Bs[7] = yy1 - sh_y / 2 + sh_y + 1;
        Bs[8] = xx + 1;     Bs[9] = yy1 - sh_y / 2 - 1;
        fillpoly(4, Bs);

    } else {
        barx(xx + 1, yy1 - sh_y / 2 - 1, xx + len - 1, yy1 - sh_y / 2 + sh_y + 1);
    }




    if (CurrentPicture == BG) _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT); else
        _SetText(F_LITT_B, CENTER_TEXT, CENTER_TEXT);

    _SetTextSize(-sh_y*2 - 1);
    len_t = textwidth(name) / 2 + 1;
    if (masy == 0) {
        // подкладку подцифру выводим только без наклона
        bar(xx + len / 2 - len_t, yy1 - sh_y / 2 - 1, xx + len / 2 + len_t, yy1 - sh_y / 2 + sh_y + 1);
    }

    setcolor(C_D);
    if (masy != 0) {
        // есть желание сделать текст с наклоном
        //int grad=GradToDeg(ArcTan2(masy,(WAY_X+mas)));
        int xt = xx + len / 2 + 1;
        int yt = yy1 + (yy2 - yy1) / 2;
        OutTextXY(xt, yt, name);
    } else {
        DrawText(xx + 1, yy1 - sh_y - 1, len - 1, sh_y*2 + 2, name);
    }
    _SetTextSize(1);

    /* рисуем длину путей  */
    if ((CurrentPicture == LT) && (bShowExtInfo) && (LenUV != 0) && (masy == 0)) {
        _SetTextSize(-sh_y*2 + 6);

        setcolor(9);
        char strl[25];
        itoa(LenUV, strl, 10);
        len_t = textwidth(strl);
        OutTextXY(xx + len - len_t, yy1 + s - 1, strl);
        _SetTextSize(1);
    }

    if (MyFishk != 0) {
        TGrpahExElem GE;
        GE.Enabled = true;
        GE.PictNumber = 120 + MyFishk;
        GE.PictWidthStan = sh_y * 4; GE.PictHeightStan = sh_y * 4;
        GE.PictHeightYch = sh_y * 4; GE.PictWidthYch = sh_y * 4;
        //GE.GridAllign=0;
        GE.TextFontNStan = 0; GE.TextFontNYch = 0;
        ShowPictText(xx + len / 2, yy1, &GE, "", CurrentPicture);
    }




    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    //SetGradientFactor(1);

    //if(CurrentPicture!=BG){  OutTextXY(x+len/2+1,y+s+1-1,name);}
    // if(clr!=LIN){  // До АИПа рисовалось тока если занято
    //*   if(mas>-8) */  OUTNUM(x+len/2+(impuls_kmu*MUL_X) ,y-12+(CorNumY*MUL_Y),impuls_busi,zona);
    //  }

    /*----*/
    /*if(YouFishk!=0)*/
    /*
    {
      if(MyFishk==1){
        setfillstyle(1,KRA);
        setcolor(C_D);
        fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
        setfillstyle(1,TXT);
        bar(x+len/2-sh_y,y-sh_y/2,x+len/2+sh_y,y+sh_y/2);
      }
      //  *YouFishk=2;
      if(MyFishk==2){
        setcolor(BOLOT);
        setfillstyle(1,BOLOT);
        rectangle(x+len/2-sh_y,y-sh_y,x+len/2+sh_y,y+sh_y);
        barx(x+len/2-sh_y-1,y-sh_y-1,x+len/2+sh_y+1,y+sh_y+1);
        _SetText(COURE12,CENTER_TEXT,CENTER_TEXT);
        setcolor(C_D);
        OutTextXY(x+len/2,y,"!");
      }
      if(MyFishk==3){
        int kr[10];
        kr[0] =x+len/2-sh_y;       kr[1] =y+sh_y/2;
        kr[2] =x+len/2-sh_y;       kr[3] =y-sh_y/2;
        kr[4] =x+len/2+sh_y;       kr[5] =y+sh_y/2;
        kr[6] =x+len/2-sh_y;       kr[7] =y+sh_y/2;
        setfillstyle(1,KRA);
        setcolor(C_D);
        fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
        setfillstyle(1,TXT);
        fillpoly(4,kr);
      }
      if(MyFishk==4){
        int kr[10];
        kr[0] =x+len/2-sh_y;       kr[1] =y+sh_y/2;
        kr[2] =x+len/2+sh_y;       kr[3] =y-sh_y/2;
        kr[4] =x+len/2+sh_y;       kr[5] =y+sh_y/2;
        kr[6] =x+len/2-sh_y;       kr[7] =y+sh_y/2;
        setfillstyle(1,KRA);
        setcolor(C_D);
        fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
        setfillstyle(1,TXT);
        fillpoly(4,kr);
      }
      if(MyFishk==5){
        int kr[10];
        setfillstyle(1,KRA);
        setcolor(C_D);
        fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
        setfillstyle(1,TXT);

        kr[0] =x+len/2-sh_y;       kr[1] =y+sh_y/2;
        kr[2] =x+len/2-sh_y;       kr[3] =y-sh_y/2;
        kr[4] =x+len/2;            kr[5] =y+sh_y/2;
        kr[6] =x+len/2-sh_y;       kr[7] =y+sh_y/2;
        fillpoly(4,kr);

        kr[0] =x+len/2;       kr[1] =y+sh_y/2;
        kr[2] =x+len/2+sh_y;       kr[3] =y-sh_y/2;
        kr[4] =x+len/2+sh_y;       kr[5] =y+sh_y/2;
        kr[6] =x+len/2;       kr[7] =y+sh_y/2;
        fillpoly(4,kr);
      }
    }
    */
    //_SetText(F_DEFAULT,LEFT_TEXT,BOTTOM_TEXT);
    /*------*/

}

void Way::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int xx = this->X * MUL_X + _X_;
    int yy = this->Y * MUL_Y + _Y_;
    int len = (WAY_X + mas) * MUL_X;
    if (direct == 0) X = xx + 4; else X = xx + len - 1 - Width - 3;
    Y = yy - Height / 2;
}

TYP  Way::GetType()
{
    return  WAY;
};
UNIT Way::GetUnit()
{
    return WAYS;
};

/* =================================  Plot  ===============================*/
Plot::Plot()
{
    MyFishk = 0;
    clr = LIN;
    impuls_kzm0=impuls_kzm1=fimpuls_kzm0=fimpuls_kzm1=0;
    impuls_svob2=impuls_svob3=fimpuls_svob2=fimpuls_svob3=0;
    impuls_zan4=impuls_zan5=impuls_zan6=0;
    fimpuls_zan4=fimpuls_zan5=fimpuls_zan6=0;
}
void Plot::SetPropMap(TPropMap &m)
{
     Ways::SetPropMap(m);
     impuls_kzm0 = NewStrToOldImp(m.get("тсimpuls_kzm0").c_str());
     impuls_kzm1 = NewStrToOldImp(m.get("тсimpuls_kzm1").c_str());
     impuls_svob2 = NewStrToOldImp(m.get("тсimpuls_svob2").c_str());
     impuls_svob3 = NewStrToOldImp(m.get("тсimpuls_svob3").c_str());
     impuls_svob3 = NewStrToOldImp(m.get("тсimpuls_svob3").c_str());
     impuls_zan4 =  NewStrToOldImp(m.get("тсimpuls_zan4").c_str());
     impuls_zan5 =  NewStrToOldImp(m.get("тсimpuls_zan5").c_str());
     impuls_zan6 =  NewStrToOldImp(m.get("тсimpuls_zan6").c_str());
}

void Plot::GetPropMap(TPropMap &m)
{
    Ways::GetPropMap(m);
    m.putEx("тсimpuls_kzm0", OldImpToNewStr(impuls_kzm0, this), (void*)GetRealImp(impuls_kzm0),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_kzm1", OldImpToNewStr(impuls_kzm1, this), (void*)GetRealImp(impuls_kzm1),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_svob2", OldImpToNewStr(impuls_svob2, this), (void*)GetRealImp(impuls_svob2),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_svob3", OldImpToNewStr(impuls_svob3, this), (void*)GetRealImp(impuls_svob3),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_zan4", OldImpToNewStr(impuls_zan4, this), (void*)GetRealImp(impuls_zan4),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_zan5", OldImpToNewStr(impuls_zan5, this), (void*)GetRealImp(impuls_zan5),       OldImpToNewStr(0, this));
    m.putEx("тсimpuls_zan6", OldImpToNewStr(impuls_zan6, this), (void*)GetRealImp(impuls_zan6),       OldImpToNewStr(0, this));
}


void SetPlotNeisprClrs(int &pclr, int &bclr, bool bNewNeisprPer)
{
    if (bNewNeisprPer) {
        pclr = 249;
    } else {
        pclr = bclr; bclr = FON;
    }
    if ((pclr == bclr) && (bclr == FON)) pclr = C_D;
}

int GetABTCSost(     int masy,
                     int  fimp1, int  fimp2, int  fimp3, int  fimp4,int  fimp5
                    )
{
    int sost=0;
    if ((fimp1 == 33) || (fimp2 == 33) || (fimp3 == 33) || (fimp4 == 33) || (fimp5 == 33)) return 33;
    if (MOD == RD) {
      if (masy==11){
        //1-Рельсовая цепь свободна "С"
        //2-Рельсовая цепь ложно занята "Л3" *
        //3-Рельсовая цепь логически занята "Л”, блокирована
        //4-Рельсовая цепь правильно занята "ПЗ" *
        //5-Рельсовая цепь занята с признаком головы "П3Г" *
        if ((fimp1==1)) sost=1;
        if ((fimp2==1)) sost=2;
        if ((fimp3==1)) sost=3;
        if ((fimp4==1)) sost=4;
        if ((fimp5==1)) sost=5;
      }
      if (masy==12){
        //0: резерв
        //1: «С» свободна
        //2: «ЛЗ» ложно занята
        //3: «Л» логически занята
        //4: «ПЗ» правильно занята
        //5: «ПЗГ» правильно занята с признаком головы поезда
        sost=fimp1+fimp2*2+fimp3*4;
      }

    }
    return sost;
}


void SetABTCColors(     int sost,
                        int &clr, int &clrpen)
{
    clr = LIN;
    clrpen = BLUE_m;

    if (MOD == RD) {
      if (sost==33) {clr = BIRUZOVIJ;return;}

      clr = FON1;
      if (sost==1) {
                clrpen = BLUE_m;
                clr = LIN;
      }
      if ((sost==3)) {
                clrpen = LIN;
                clr = KRA_SER;
      }
      if ((sost==2)||(sost==4)||(sost==5)){
                clrpen = BLUE_m;
                clr = COLOR_B;
                if (sost==2) clrpen =   KRAYARK;
      }

    }


}
void Plot::UpdateState()
{
    Ways::UpdateState();
    int rimpuls_kzm0=f(impuls_kzm0);
    int rimpuls_kzm1=f(impuls_kzm1);
    int rimpuls_svob2=f(impuls_svob2);
    int rimpuls_svob3=f(impuls_svob3);
    int rimpuls_zan4=f(impuls_zan4);
    int rimpuls_zan5=f(impuls_zan5);
    int rimpuls_zan6=f(impuls_zan6);

    StateChanged = StateChanged | (rimpuls_kzm0!=fimpuls_kzm0) | (rimpuls_kzm1!=fimpuls_kzm1);
    StateChanged = StateChanged | (rimpuls_svob2!=fimpuls_svob2) | (rimpuls_svob3!=fimpuls_svob3);
    StateChanged = StateChanged | (rimpuls_zan4!=fimpuls_zan4) | (rimpuls_zan5!=fimpuls_zan5) | (rimpuls_zan6!=fimpuls_zan6);
    fimpuls_kzm0=rimpuls_kzm0;fimpuls_kzm1=rimpuls_kzm1;
    fimpuls_svob2=rimpuls_svob2;fimpuls_svob3=rimpuls_svob3;
    fimpuls_zan4=rimpuls_zan4;fimpuls_zan5=rimpuls_zan5;fimpuls_zan6=rimpuls_zan6;

    int fimp1 = fimpuls_busi;
    clrp = BLUE_m;


    clr = COLOR_F_P;
    clr = Clr_SetPl(fimp1/*fimpuls_busi*/, impuls_plus);
    // замыкание
    if ((clr ==COLOR_F_P)&&(impuls_kzm1!=0)){
       if (fimpuls_kzm1==1)
          clr=COLOR_SET;
    }
    /* 15.05.2002  busy||mu||kmu  */
    if (((masy == 2) || (masy == 3))) {
        int fimp2 = fimpuls_kmu;
        int fimp3 = fimpuls_mu;
        if ((masy == 2) && (fimp1 <= 1))fimp1 = 1 - fimp1;
        if ((masy == 2) && (fimp2 <= 1))fimp2 = 1 - fimp2;
        if ((masy == 2) && (fimp3 <= 1))fimp3 = 1 - fimp3;
        if ((masy == 2) && (fimpuls_zan4 <= 1)) fimpuls_zan4 = 1 - fimpuls_zan4;
        if ((masy == 2) && (fimpuls_zan5 <= 1)) fimpuls_zan5 = 1 - fimpuls_zan5;
        if ((masy == 2) && (fimpuls_zan6 <= 1)) fimpuls_zan6 = 1 - fimpuls_zan6;
        if ((fimp1 == 1) ||
                ((fimp2 == 1) && (impuls_kmu != 0)) ||
                ((fimp3 == 1) && (impuls_mu != 0)) ||
                ((fimpuls_zan4 == 1) && (impuls_zan4 != 0)) ||
                ((fimpuls_zan5 == 1) && (impuls_zan5 != 0)) ||
                ((fimpuls_zan6 == 1) && (impuls_zan6 != 0))
                )
            clr = COLOR_B; else clr = COLOR_F_P;
        if ((fimp1 == 33) || (fimp2 == 33) || (fimp3 == 33)) clr = BIRUZOVIJ;
    }
    /* 26.11.2013  busy||mu||kmu  */
    if (((masy == 4))) {
        int fb=fimpuls_busi+fimpuls_kmu+fimpuls_mu;
        if (fb >= 1) clr = COLOR_B;
        if (fb>=33 ) clr = BIRUZOVIJ;
        // несовпадение занятости/свободности
        if ((impuls_busi+impuls_kmu+impuls_mu!=0)&&(impuls_svob+impuls_svob2+impuls_svob3!=0)){
           if ((impuls_busi!=0)&&(impuls_svob!=0)&&((fimpuls_busi+fimpuls_svob==0)||(fimpuls_busi+fimpuls_svob==2))) clrp=KRA_BEL;
           if ((impuls_kmu!=0)&&(impuls_svob2!=0)&&((fimpuls_kmu+fimpuls_svob2==0)||(fimpuls_kmu+fimpuls_svob2==2))) clrp=KRA_BEL;
           if ((impuls_mu!=0)&&(impuls_svob3!=0)&&((fimpuls_mu+fimpuls_svob3==0)||(fimpuls_mu+fimpuls_svob3==2))) clrp=KRA_BEL;
        }
    } else {
        // несовпадение занятости/свободности
        if ((impuls_busi!=0)&&(impuls_svob!=0)){
           if ((fimpuls_busi+fimpuls_svob==0)||(fimpuls_busi+fimpuls_svob==2))
              clrp=KRA_BEL;
        }
    }

     // несовпадение замкн/незам
    if ((impuls_kzm0!=0)&&(impuls_kzm1!=0)){
       if ((fimpuls_kzm0+fimpuls_kzm1==0)||(fimpuls_kzm0+fimpuls_kzm1==2))
          clrp=ZEL_SER;
    }

    // бу не работает
    if (fimpuls_plus && (fimpuls_plus != 31) && (fimpuls_plus != 33)) {
        SetPlotNeisprClrs(clrp, clr, AO->bNewNeisprPer);
        ////setcolor(SV_MIG);
        //setcolor(clr);
        //clr = FON;
    }

    if (((masy == 11) || (masy == 12))) {
        int sost=GetABTCSost(masy,
                             fimpuls_svob, fimpuls_mu, fimpuls_zan4, fimpuls_busi ,fimpuls_zan5);
        // Сигналы АБТЦ МШ
        SetABTCColors(    sost, clr, clrp);
        if ((MOD == ED)&&(impuls_svob==0)) clr = FON;
    }
    if (masy == 13) {
        // Сигналы АБТЦ МШ  STA
        int sost=GetABTCSost(11,
                             fimpuls_busi, fimpuls_plus, fimpuls_mnus, fimpuls_kzm ,fimpuls_kmu);
        SetABTCColors(    sost, clr, clrp);

        if ((MOD == ED)&&((impuls_busi==0)||(impuls_plus==0)||(impuls_mnus==0)||(impuls_kzm==0)||(impuls_kmu==0))) clr = FON;
    }
    if (masy == 14) {
        // Сигналы АБТЦ МШ  STA
        int sost=GetABTCSost(12,
                             fimpuls_mu, fimpuls_plus, fimpuls_busi, 0 ,0);
        SetABTCColors(    sost, clr, clrp);

        if ((MOD == ED)&&((impuls_busi==0)||(impuls_plus==0)||(fimpuls_mu==0))) clr = FON;
    }




    // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
    if ((IsClrMig(clr))) StateChanged = true;

}
void  ShowPerSvet(int x, int y, int type, int iBusy, int iPlus, int iKzm, int mas, int masy, char * name,int fimpuls_block);

void  Plot::Show()
{

    int xx = X * MUL_X + _X_;
    int yy = Y * MUL_Y + _Y_;


    int len = (S_WAY_X + mas) * MUL_X;
    if (
        (MOD != ED) &&
        (
            (!strcmp("v" , name)) ||
            (!strcmp("1v", name))
        )
    ) return;


    //setcolor(TXT);


    if (MOD == ED) {
        clr = COLOR_F_P; clrp = C_D;
    }
    if (impuls_busi == 0) clr = FON;
    if ((MOD == ED) && ((masy == 2) || (masy == 3)) &&
            ((impuls_busi == 0) || (impuls_kmu == 0) || (impuls_mu == 0))) clr = FON;

    //if(CurrentPicture==LT){ di1 = 14;di2 = 18;
    //}else{di1 = 10;di2 = 11; }
    if (name[0] == '-') clr = FON;
    if (atoi(name) < 0) clr = FON;


    if ((CurrentPicture == BG)&&(abs(len)<=6)&& (clrp==C_D)&&(clr==COLOR_B)) clrp=clr;
    setcolor(clrp);
    setfillstyle(1, clr);



    int Y1 = yy - sh_y / 2;
    int Y2 = yy - sh_y / 2 + sh_y;
    int dd=1;
    //if (((masy == 11) || (masy == 12))) dd=0;
    if ((clr == LIN) || (clr == FON)) {
        setfillstyle(1, FON);
        bar(xx + 1, Y1 - 1, xx + len - 1, Y2 + 1);
        setfillstyle(1, clr);
        //          barx(x+1,y-1,x+len-1,y+1);
        barx(xx + dd, Y1, xx + len - dd, Y2);

    } else {
        barx(xx + dd, Y1 - 1, xx + len - dd, Y2 + 1);
    }
//-----------------ВЫВОД--------
    int nom;
    int s = sh_y / 2 + 6;
    int ch__cod = 0;
    int nch_cod = 1;
    int ch__len = len - 2;
    int nch_len = 2;
    int nom2 = 0;
    char *ptr = 0;
    char nx[8], nm[8], nm2[8];
    if (AO->FLAG_POINT_REVERS) {
        ch__cod = 1;
        nch_cod = 0;
    }
    nom = atoi(name);
    itoa(abs(nom), nm, 10);
    if (nom < 0) strncpy(nx, name + 1,sizeof(nx)-1); else strncpy(nx, name,sizeof(nx)-1);
    ptr = strchr(nx, '/');
    if (ptr) {
        ptr = strchr(nx, '/');
        nom2 = atoi(ptr + 1);
        itoa(nom2, nm2, 10);
    }
    setfillstyle(1, clr);
    setcolor(BLUE_m);
    int ss = 0;
    if ((AO->NumTch) &&
            ((CurrentPicture == LT) || (AO->NumTchBG)) &&
            ((nom != 0) || (nom2 != 0))) {
        if (CurrentPicture == BG) {
            _SetText(F_LITT , CENTER_TEXT, CENTER_TEXT);
            s += 2;
            ss = 1;
        } else  {
            _SetText(TIMES14, CENTER_TEXT, BOTTOM_TEXT);
            ss = 9;
            s += 5;
        }
        int xtext, ytext, xsv, ysv, tsv, masysv;
        if (nom) {
            if ((abs(nom) % 2 == nch_cod))  {
                xtext = xx + ch__len; ytext = yy - s + ss; xsv = xx + len - sh_y; ysv = yy - MUL_Y - 1; tsv = 4; masysv = 2;
            }
            if ((abs(nom) % 2 == ch__cod))  {
                xtext = xx + nch_len; ytext = yy + s + ss; xsv = xx + sh_y    ; ysv = yy - MUL_Y + 1; tsv = 3; masysv = 3;
            }
            if ((impuls_mnus != 0)) { // выводим на уч-ке только активный иначе стираем
                if ((CurrentPicture != BG) || (fimpuls_mnus == 1) || (MOD == ED))
                    ShowPerSvet(xsv, ysv, tsv, fimpuls_mnus,0, 0, 0, masysv, nm,0); else
                    ShowPerSvet(xsv, ysv, tsv, fimpuls_mnus,0, -1, 0, masysv, nm,0);
            } else OutTextXY(xtext, ytext, nm);
            if (impuls_kzm != 0) {
                // выводим на уч-ке только активный иначе стираем
                int pc, bc;
                bc = FON; pc = C_D;
                if (fimpuls_kzm == 0) bc = GELT; // инверсия заведомо
                if ((CurrentPicture == BG) && (MOD != ED)) pc = bc;
                setfillstyle(1, bc); setcolor(pc);
                int hh = sh_y;
                if (hh > MUL_X) hh = MUL_X; // шоб красиво
                if (tsv == 3) barx(xx + len / 2 - MUL_X / 2, Y1 - 2, xx + len / 2 + MUL_X / 2, Y1 - hh - 2);
                if (tsv == 4) barx(xx + len / 2 - MUL_X / 2, Y2 + 2, xx + len / 2 + MUL_X / 2, Y2 + hh + 2);
            }

        }
        if (nom2) {
            if ((abs(nom2) % 2 == nch_cod)) {
                xtext = xx + nch_len; ytext = yy - s + ss; xsv = xx + sh_y    ; ysv = yy - MUL_Y; tsv = 4; masysv = 2;
            }
            if ((abs(nom2) % 2 == ch__cod)) {
                xtext = xx + ch__len; ytext = yy + s + ss; xsv = xx + len - sh_y; ysv = yy - MUL_Y; tsv = 3; masysv = 3;
            }
            //if ((impuls_mnus!=0)) ShowPerSvet(xsv,ysv,tsv,fimpuls_mnus,0,0,masysv, nm2); else
            OutTextXY(xtext, ytext, nm2);
        }
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    }

    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);



    /*----*/
    /* if(YouFishk!=0)*/
    if (MyFishk != 0) {
        TGrpahExElem GE;
        GE.Enabled = true;
        GE.PictNumber = 120 + MyFishk;
        GE.PictWidthStan = sh_y * 4; GE.PictHeightStan = sh_y * 4;
        GE.PictHeightYch = sh_y * 4; GE.PictWidthYch = sh_y * 4;
        GE.GridAllign = 0;
        GE.TextFontNStan = 0; GE.TextFontNYch = 0;
        ShowPictText(xx + len / 2, yy, &GE, "", CurrentPicture);
    }
    /*
    {
    if(MyFishk==1){
     setfillstyle(1,KRA);
     setcolor(C_D);
     fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
     setfillstyle(1,TXT);
     bar(x+len/2-sh_y,y-sh_y/2,x+len/2+sh_y,y+sh_y/2);
    }
    if(MyFishk==8){
     setfillstyle(1,KRA);
     setcolor(C_D);
     fillellipse (x+len/2,y,sh_y*3/2,sh_y*3/2);
     setcolor(TXT);
     line(x+len/2-sh_y,y-sh_y/2,x+len/2+sh_y,y+sh_y/2);
     line(x+len/2-sh_y,y+sh_y/2,x+len/2+sh_y,y-sh_y/2);
    }
    }
    /*------*/




}

void Plot::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int len = (S_WAY_X + mas) * MUL_X;
    int xx = this->X * MUL_X + _X_;
    int yy = this->Y * MUL_Y + _Y_;
    if (CurrentPicture == BG) {
        if (direct == 0) {
            X = xx + 3; Y = yy - sh_y / 2 - Height;
        } else {
            X = xx + len - 1 - Width - 2; Y = yy + sh_y / 2 + 1;
        }
    } else {
        Y = yy - Height / 2;
        if (direct == 0) {
            X = xx + 3;
        } else {
            X = xx + len - 1 - Width - 2;
        }
    }
}


TYP   Plot::GetType()
{
    return PLOT;
};
UNIT  Plot::GetUnit()
{
    return WAYS;
};
int   Plot::GetSubType()
{
    return masy;
};


/* ============================== Blok ========================*/


void SetBl_uh4Colors(int  impuls_busi, int  impuls_plus, int  impuls_mnus, int  impuls_kzm, int  impuls_kmu, int  impuls_mu,
                     int fimpuls_busi, int fimpuls_plus, int fimpuls_mnus, int fimpuls_kzm, int fimpuls_kmu, int fimpuls_mu,
                     bool bNewNeisprPer,
                     int &clr, int &clrpen)
{
    clr = LIN;
    clrpen = BLUE_m;
    if (MOD == RD) {
        if (fimpuls_busi == 1) {
            if (fimpuls_plus == 1) clr = COLOR_B;
            if (impuls_plus == -2)   clr = FON;
            if ((impuls_kmu != 0) && (fimpuls_kmu == 1)) {
                SetPlotNeisprClrs(clrpen, clr, bNewNeisprPer);
            };
        }
        if (fimpuls_mnus == 1) {
            if (fimpuls_kzm == 1) clr = COLOR_B;
            if (impuls_kzm == -2)   clr = FON;
            if ((impuls_mu != 0) && (fimpuls_mu == 1)) {
                SetPlotNeisprClrs(clrpen, clr, bNewNeisprPer);
            };
        }
        if (fimpuls_busi == fimpuls_mnus) {
            if (
                (fimpuls_plus == 1) ||
                (fimpuls_kzm == 1)
            ) clr = COLOR_B;
            if ((fimpuls_kmu == 1) || (fimpuls_mu == 1)) {
                SetPlotNeisprClrs(clrpen, clr, bNewNeisprPer);
            };
        }
        if ((fimpuls_busi == 33) || (fimpuls_plus == 33) || (fimpuls_mnus == 33) || (fimpuls_kzm == 33))
            clr = BIRUZOVIJ;
    }

    if ((impuls_plus == 0) && (impuls_kzm == 0)) clr = FON;

}


Blok::Blok():Ways()
{
        bInGrid=false;
}

void  Blok::Show()
{
    if (!AO->ShowBottomPeregons) return;
    if (CurrentPicture == BG)return;
    int xx = X * MUL_X + _X_;
    int yy = Y * MUL_Y + _Y_;



    int clr = /*Clr_Set2*/Clr_SetPl(fimpuls_busi, fimpuls_plus);
    int clrp = BLUE_m;
    // если подцеплено больше 2 имп - работаем как бу33
    if (impuls_busi == 0) clr = FON;
    if (fimpuls_plus && (fimpuls_plus != 31) && (fimpuls_plus != 33))
        SetPlotNeisprClrs(clrp, clr, AO->bNewNeisprPer);
    if ((impuls_plus != 0) || (impuls_mnus != 0)) {
        SetBl_uh4Colors(impuls_busi, impuls_plus, impuls_mnus, impuls_kzm, impuls_kmu, impuls_mu,
                        fimpuls_busi, fimpuls_plus, fimpuls_mnus, fimpuls_kzm, fimpuls_kmu, fimpuls_mu,
                        AO->bNewNeisprPer,
                        clr, clrp);
    }


    if (((masy == 11) || (masy == 12))) {
        int sost=GetABTCSost(masy,
                              fimpuls_svob, fimpuls_mnus, fimpuls_kzm, fimpuls_busi ,fimpuls_mu);
        // Сигналы АБТЦ МШ
        SetABTCColors(    sost, clr, clrp);
        if ((MOD == ED)&&(impuls_svob==0)) clr = FON;
    }
    if (masy == 13) {
        // Сигналы АБТЦ МШ  STA
        int sost=GetABTCSost(11,
                             fimpuls_busi, fimpuls_plus, fimpuls_mnus, fimpuls_kzm ,fimpuls_kmu);
        SetABTCColors(    sost, clr, clrp);

        if ((MOD == ED)&&((impuls_busi==0)||(impuls_plus==0)||(impuls_mnus==0)||(impuls_kzm==0)||(impuls_kmu==0))) clr = FON;
    }
    if (masy == 14) {
        // Сигналы АБТЦ МШ  STA
        int sost=GetABTCSost(12,
                             fimpuls_mu, fimpuls_plus, fimpuls_busi, 0 ,0);
        SetABTCColors(    sost, clr, clrp);

        if ((MOD == ED)&&((impuls_busi==0)||(impuls_plus==0)||(fimpuls_mu==0))) clr = FON;
    }



    if (name[0] == '+') {
        clr = FON;
    }
    if (atoi(name) == 0) {
        clr = FON;
    }

    int len = mas;//!!!!!!!!!!!!!!!!!!!!!

    xx = (xx - _X_) / MUL_X;
    yy = (yy - _Y_) / MUL_Y;
    yy += DELTA_Y;
    xx += DELTA_X;

    if (bInGrid){
        xx = X * MUL_X/2 + _X_;
        yy = Y * MUL_Y/2 + _Y_;
        len=mas* MUL_X/2;
    }

    int nom;
    int s = 3;

    int ch__cod = 0;
    int nch_cod = 1;
    int ch__len = len - 2;
    int nch_len = 2;
    int nom2 = 0;
    char *ptr = 0;
    char nx[8];
    char nm[8];
    char nm2[8];
    if (AO->FLAG_POINT_REVERS) {
        ch__cod = 1;
        nch_cod = 0;
    }



    nom = atoi(name);

    if (nom == 0) clr = FON;
    if (name[0] == '+') {
        clr = FON; strncpy(nx, name + 1,sizeof(nx)-1);
    } else {
        strncpy(nx, name,sizeof(nx)-1);
    }
    ptr = strchr(nx, '/');
    if (ptr) {
        strncpy(nm, nx,sizeof(nm)-1);
        ptr = strchr(nm, '/');
        strncpy(nm2, ptr + 1,sizeof(nm2)-1);
        (*ptr) = 0;
        nom2 = atoi(nm2);
    } else {
        strncpy(nm, nx,sizeof(nm)-1);

    }
    setfillstyle(1, clr);
    setcolor(clrp);
    barx(xx + 1, yy - s, xx + len - 1, yy + s);

    if ((AO->FLAG_POINT_NUMBER) && (nom > 0)) {
        _SetText(F_LITT_S, CENTER_TEXT, BOTTOM_TEXT);
        if (nom % 2 == nch_cod) {
            OutTextXY(xx + ch__len, yy - s - 1, nm);
            OutTextXY(xx + ch__len + 1, yy - s - 1, nm);
        }
        if ((nom2 % 2 == nch_cod) && nom2) {
            OutTextXY(xx + nch_len, yy - s - 1, nm2);
            OutTextXY(xx + nch_len + 1, yy - s - 1, nm2);
        }
        _SetText(F_LITT_S, CENTER_TEXT, TOP_TEXT);
        if (nom % 2 == ch__cod) {
            OutTextXY(xx + nch_len, yy + s + 1, nm);
            OutTextXY(xx + nch_len + 1, yy + s + 1, nm);
        }
        if ((nom2 % 2 == ch__cod) && (nom2)) {
            OutTextXY(xx + ch__len, yy + s + 1, nm2);
            OutTextXY(xx + ch__len + 1, yy + s + 1, nm2);
        }
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    }

}
TYP  Blok::GetType()
{
    return BLOK;
};
UNIT Blok::GetUnit()
{
    return LINE;
};
int   Blok::GetSubType()
{
    return masy;
};

void Blok::SetPropMap(TPropMap &m)
{
     Ways::SetPropMap(m);
     bInGrid =   m.geti("лгInGrid");

}

void Blok::GetPropMap(TPropMap &m)
{
    Ways::GetPropMap(m);
    m.put("лгInGrid", bInGrid,0);
}

void Blok::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    X = 0; Y = 0;
    if (!AO->ShowBottomPeregons) return;
    if (CurrentPicture == BG)return;
    int xx = this->X * MUL_X + _X_;
    int yy = this->Y * MUL_Y + _Y_;
    xx = (xx - _X_) / MUL_X;
    yy = (yy - _Y_) / MUL_Y;
    yy += DELTA_Y;
    xx += DELTA_X;
    int len = mas;
    if (bInGrid){
        xx = X * MUL_X/2 + _X_;
        yy = Y * MUL_Y/2 + _Y_;
        len=mas* MUL_X/2;
    }

    Y = yy - Height / 2;
    if (direct == 0) {
        X = xx + 3;
    } else {
        X = xx + len - 1 - Width - 2;
    }
}


void SetPlotNeisprClrs(int &pclr, int &bclr);


void  Bl_uh::Show()
{
    Strel::Show();
    clr = LIN;
    int clrpen = BLUE_m;

    SetBl_uh4Colors(impuls_busi, impuls_plus, impuls_mnus, impuls_kzm, impuls_kmu, impuls_mu,
                    fimpuls_busi, fimpuls_plus, fimpuls_mnus, fimpuls_kzm, fimpuls_kmu, fimpuls_mu,
                    AO->bNewNeisprPer,
                    clr, clrpen);
    if (name[0] == '-') clr = FON;


    int len = (S_WAY_X + mas) * MUL_X;
    // Обрисовываем дылки
    if (masy == 1) {
        setcolor(C_D);
        line(x + 1, y, x + len - 1, y);
        len = (S_WAY_X + (mas - 2)) * MUL_X;
        x = (X + 1) * MUL_X + _X_;
    }
    setfillstyle(1, clr);
    setcolor(clrpen);
    if ((clr == LIN) || (clr == FON)) {
        setfillstyle(1, FON);
        bar(x + 1, y - sh_y / 2 - 1, x + len - 1, y - sh_y / 2 + sh_y + 1);
        setfillstyle(1, clr);
        barx(x + 1, y - 1, x + len - 1, y + 1);
        barx(x + 1, y - sh_y / 2, x + len - 1, y - sh_y / 2 + sh_y);


    } else {

        barx(x + 1, y - sh_y / 2 - 1, x + len - 1, y - sh_y / 2 + sh_y + 1);

    }

//-----------------‚›‚Ћ„--------
    int nom;
    int s = sh_y / 2 + 6;
    int ch__cod = 0;
    int nch_cod = 1;
    int ch__len = len - 2;
    int nch_len = 2;
    int nom2 = 0;
    char *ptr = 0;
    char nx[8], nm[8], nm2[8];
    if (AO->FLAG_POINT_REVERS) {
        ch__cod = 1;
        nch_cod = 0;
    }
    nom = atoi(name);
    itoa(abs(nom), nm, 10);
    if (nom < 0) strncpy(nx, name + 1,sizeof(nx)-1); else strncpy(nx, name,sizeof(nx)-1);
    ptr = strchr(nx, '/');
    if (ptr) {
        ptr = strchr(nx, '/');
        nom2 = atoi(ptr + 1);
        itoa(nom2, nm2, 10);
    }
    setfillstyle(1, clr);
    setcolor(BLUE_m);
    int ss = 0;
    if ((AO->NumTch) &&
            ((CurrentPicture == LT) || (AO->NumTchBG)) &&
            ((nom != 0) || (nom2 != 0))) {
        if (CurrentPicture == BG) {
            _SetText(F_LITT , CENTER_TEXT, CENTER_TEXT);
            s += 2;
            ss = 1;
        } else  {
            _SetText(TIMES14, CENTER_TEXT, BOTTOM_TEXT);
            ss = 9;
            s += 5;
        }
        if ((abs(nom) % 2 == nch_cod) && (nom))   OutTextXY(x + ch__len, y - s + ss, nm);
        if ((abs(nom2) % 2 == nch_cod) && nom2)   OutTextXY(x + nch_len, y - s + ss, nm2);
        if ((abs(nom) % 2 == ch__cod) && (nom))   OutTextXY(x + nch_len, y + s + ss, nm);
        if ((abs(nom2) % 2 == ch__cod) && (nom2)) OutTextXY(x + ch__len, y + s + ss, nm2);
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    }


}

void Bl_uh::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int xx = this->X * MUL_X + _X_;
    int yy = this->Y * MUL_Y + _Y_;
    int len = (S_WAY_X + mas) * MUL_X;
    if (CurrentPicture == BG) {
        if (direct == 0) {
            X = xx + 3;
            Y = yy - sh_y / 2 - Height;
        } else {
            X = xx + len - 1 - Width - 2; Y = yy + sh_y / 2 + 1;
        }
    } else {
        Y = yy - Height / 2;
        if (direct == 0) {
            X = xx + 3;
        } else {
            X = xx + len - 1 - Width - 2;
        }
    }
}


TYP   Bl_uh::GetType()
{
    return BL_UH;
};

void Bl_uh::ShowTrainNumber()
{
    EXD_ShowTrainNumber(this, fimpuls_plus | fimpuls_kzm);
}
void Bl_uh::HideTrainNumber()
{
    EXD_HideTrainNumber(this);
}



/*
void Bl_uh::Show(int x,int y)
     {
       int nap=0;
       clr=LIN;
       if(MOD==RD){
        if(f(impuls_busi)==1){
            nap=1;
            if(f(impuls_plus)==1) clr=COLOR_B;
        }
          else{
            nap=0;
            if(f(impuls_mnus)==1) clr=COLOR_B;
          }
       }
       if(!Test_strel(clr,nap,0,0,0)&&(MOD==RD))return;
       int len = (S_WAY_X+mas)*MUL_X;
       setfillstyle(1,clr);
       setcolor(BLUE_m);
       bar3d(x+1,y-sh_y/2-1,x+len-1,y-sh_y/2+sh_y+1,0,0);
     }
TYP   Bl_uh::GetType(){return BL_UH;};

*/


