//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "Lamps.h"

#include "APch.h"

#include "strel.h"
#include "scrin.h"
#include "col.h"
#include "f.h"
#include "Vatempl.h"
#include "stan.h"

#include "propmap.h"
#include "Y_STREL.h"
#include "dmpacket2.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void ShowPictText(int x, int y, void * AGE, char * szText, int YS);
bool ExShowLamp(int x, int y, Lamp * AL, int YS);





Lamp::Lamp()
{
    memset(&GrpahExData, 0, sizeof(GrpahExData));
    LS = &FirstLS;
}


void  Lamp::Show()
{
    clr = Clr_Set2(fimpuls_busi, f(impuls_plus));
    int xx = X * MUL_X + _X_;
    int yy = Y * MUL_Y + _Y_;


    if (ExShowLamp(xx, yy, this, CurrentPicture)) {
        return;
    }
    if (AO->TW) {
        //ShowE(xx,yy);
    } else {

        ShowX(xx, yy);
    }
    return;
}



void Lamp::ShowX1(int x, int y)
{
//      setcolor(BLUE_mmm);
    setcolor(C_D);
    setfillstyle(1, clr);
    //if(CurrentLmp == this) setcolor(SV_MIG);
    if (name[0] == '&') {
        if (clr == KRA) {
            setcolor(C_D);
            setfillstyle(1, 16711935);
        } else {
            setcolor(BLUE_mmm);
            setfillstyle(1, FON);
        }
    }
    _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
    if (strlen(name + 1) < 3)
        barx(x - sh_y*3, y - sh_y - sh_y / 2, x + sh_y*3, y + sh_y + sh_y / 2 + 2);
    else {
        if (strlen(name + 1) < 4)
            barx(x - sh_y*4, y - sh_y - sh_y / 2, x + sh_y*4, y + sh_y + sh_y / 2 + 2);
        else
            barx(x - sh_y*5, y - sh_y - sh_y / 2, x + sh_y*5, y + sh_y + sh_y / 2 + 2);
    }

    if (CurrentPicture != LT) {
        _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
//        setcolor(C_D);
    }
    OutTextXY(x, y, name + 1);
}

void Lamp::ShowX(int x, int y)
{
    int th, tw;
    //int pr_mi;
    int prsq;
    int lclr = clr;
    char *nNam;
    if (CurrentPicture == BG)return;
    setcolor(TXT);
    _SetText(ARIAL10b, CENTER_TEXT, CENTER_TEXT);
    //  _SetText(F_DEFAULT,CENTER_TEXT,CENTER_TEXT);

    nNam = name;
    if (nNam[0] == '&') {
        prsq = 1; nNam++;/*!!!!!  y =  65;  */
    } else             prsq = 0;

    if (MUL_Y < 16)  _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
    setfillstyle(1, FON);
    setcolor(C_D);
    if (clr == LIN) lclr = FON;
    else         lclr = clr;
    if (nNam[0] == '+') {
        if (clr == LIN)  lclr = FON;
        else          lclr = ZEL;
        nNam++;
    }
    if (nNam[0] == '-') {
        if (clr == LIN)  lclr = COLOR_B;
        else          lclr = FON;
        nNam++;
    }


    tw = textwidth(nNam) + 4;
    tw = (tw / MUL_X) * MUL_X + ((tw % MUL_X) && 1) * MUL_X - 2;
    th = textheight(nNam);
    th = (th / MUL_Y) * MUL_Y + ((th % MUL_Y) && 1) * MUL_Y - 2;


    if (AO->TypLamp == 32) {
        if ((AO->TypName == 3) && (MOD == RD) && (masy != 0) && (CurrentPicture == LT)) return;
        //  ПО ОСТУ КРУЖОЧКИ НЕ РИСУЕМ !!!
        if (MUL_Y < 16)  _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
        else          _SetText(ARIAL12b, CENTER_TEXT, CENTER_TEXT);
        setcolor(clr);
        OutTextXY(x/*+tw/2*/, y, nNam);
//          OutTextXY(x+tw/2,y+th/2,nNam);
        return;
    }


    if (AO->TypLamp == 33) {
        if (MUL_Y < 16)  _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
        else          _SetText(ARIAL12, CENTER_TEXT, CENTER_TEXT);
        tw = textwidth(nNam) + 4;
        tw = (tw / MUL_X) * MUL_X + ((tw % MUL_X) && 1) * MUL_X - 2;
        th = textheight(nNam);
        th = (th / MUL_Y) * MUL_Y + ((th % MUL_Y) && 1) * MUL_Y - 2;
    }


    if (prsq) {
        if (lclr != FON) {
            Mini_Box(x, y, x + tw, y + th, LIN, C_D, lclr);
            if (lclr == ZEL)
                setcolor(C_D);
            else
                setcolor(LIN);

        } else {
            setcolor(BLUE_mmm);
            setfillstyle(1, FON);
            barx(x, y, x + tw + 1, y + th + 1);
        }
        if (MOD == ED) setcolor(C_D);
        OutTextXY(x + tw / 2, y + th / 2, nNam);
    } else {
        setcolor(C_D);
        setfillstyle(1, lclr);
        if (MUL_Y < 16)
            fillellipse(x, y + 12, 4, 4);
        else
            fillellipse(x, y + 12, 6, 6);
        setcolor(TXT);
        OutTextXY(x, y, nNam);
    }
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}

TYP  Lamp::GetType()
{
    return LAMP;
};
UNIT Lamp::GetUnit()
{
    return WAYS;
};
int  Lamp::GetSubType()
{
    if (AO->ENERG == 1) return 100;
    return 0;
};


char * Lamp::GetName()
{
    if (name[0] == '&') {
        return name + 1;
    }
    return name;
}

void Lamp:: Set()
{
    Element::Set();
    {
        TLampMEM MM;
        memcpy(&MM, &MEM.name16, sizeof(TLampMEM)); // name[16]- дурацкий сдвиг
        memcpy(&GrpahExData, &MM.GE, sizeof(GrpahExData));
        TypKp = MM.LD.TypKp;
        NKp =  MM.LD.NKp;
        NGr =  MM.LD.NGr;
        NOb =  MM.LD.NOb;
        TLampMEM* lmpdata = (TLampMEM*) & MEM.name16;
        if (LS != NULL)
            memcpy(LS,  &lmpdata->LD.LS, 1);


    }
};


static String _LampPropName[22] = {
    "цфGEEnabled"       ,   // 0
    "цфGEPictNumber"    ,   // 1
    "цфGEPictWidthStan" ,   // 2
    "цфGEPictHeightStan",   // 3
    "цфGEPictWidthYch"  ,   // 4
    "цфGEPictHeightYch" ,   // 5
    "цфGETextFontNStan" ,   // 6
    "цфGETextFontNYch"  ,   // 7
    "цфGETextFontColor" ,   // 8
    "цфGETextPosStan"   ,   // 9
    "цфGETextPosYch"    ,   //10
    "цфGETextRotate"    ,   //11
    "цфGEGridAllign"    ,   //12
    "цфGETestExSet"     ,   //13
    "цфTypKp"           ,   //14
    "цфNKp"             ,   //15
    "цфNGr"             ,   //16
    "цфNOb"             ,   //17
    "цф_S1"             ,   //18
    "цф_S2"             ,   //19
    "цф_S3"             ,   //20
    "цф_S4"                //21
};



void Lamp::SetPropMap(TPropMap &m)
{
    Element::SetPropMap(m);
    {
        GrpahExData.Enabled         = m.geti(_LampPropName[ 0]);
        GrpahExData.PictNumber      = m.geti(_LampPropName[ 1]);
        GrpahExData.PictWidthStan   = m.geti(_LampPropName[ 2]);
        GrpahExData.PictHeightStan  = m.geti(_LampPropName[ 3]);
        GrpahExData.PictWidthYch    = m.geti(_LampPropName[ 4]);
        GrpahExData.PictHeightYch   = m.geti(_LampPropName[ 5]);
        GrpahExData.TextFontNStan   = m.geti(_LampPropName[ 6]);
        GrpahExData.TextFontNYch    = m.geti(_LampPropName[ 7]);
        GrpahExData.TextFontColor   = m.geti(_LampPropName[ 8]);
        GrpahExData.TextPosStan     = m.geti(_LampPropName[ 9]);
        GrpahExData.TextPosYch      = m.geti(_LampPropName[10]);
        GrpahExData.TextRotate      = m.geti(_LampPropName[11]);
        GrpahExData.GridAllign      = m.geti(_LampPropName[12]);
        GrpahExData.TestExSet       = m.geti(_LampPropName[13]);
        TypKp                       = m.geti(_LampPropName[14]);
        NKp                         = m.geti(_LampPropName[15]);
        NGr                         = m.geti(_LampPropName[16]);
        NOb                         = m.geti(_LampPropName[17]);

        //if (LS!=NULL){
        FirstLS.MyStat2              = m.geti(_LampPropName[18]);
        //
        FirstLS.MyStat3              = m.geti(_LampPropName[19]);
        FirstLS.MyStat4              = m.geti(_LampPropName[20]);
        FirstLS.__MyStat5              = m.geti(_LampPropName[21]);
        //}
        // FirstLS=*LS;
    }

}

void Lamp::GetPropMap(TPropMap &m)
{
    Element::GetPropMap(m);
    {
        m.put(_LampPropName[ 0],          GrpahExData.Enabled, 0);
        m.put(_LampPropName[ 1],       GrpahExData.PictNumber, 0);
        m.put(_LampPropName[ 2],    GrpahExData.PictWidthStan, 0);
        m.put(_LampPropName[ 3],   GrpahExData.PictHeightStan, 0);
        m.put(_LampPropName[ 4],     GrpahExData.PictWidthYch, 0);
        m.put(_LampPropName[ 5],    GrpahExData.PictHeightYch, 0);
        m.put(_LampPropName[ 6],    GrpahExData.TextFontNStan, 0);
        m.put(_LampPropName[ 7],     GrpahExData.TextFontNYch, 0);
        m.put(_LampPropName[ 8],    GrpahExData.TextFontColor, 0);
        m.put(_LampPropName[ 9],      GrpahExData.TextPosStan, 0);
        m.put(_LampPropName[10],       GrpahExData.TextPosYch, 0);
        m.put(_LampPropName[11],       GrpahExData.TextRotate, 0);
        m.put(_LampPropName[12],       GrpahExData.GridAllign, 0);
        m.put(_LampPropName[13],        GrpahExData.TestExSet, 0);
        m.put(_LampPropName[14],              TypKp, 0);
        m.put(_LampPropName[15],                NKp, 0);
        m.put(_LampPropName[16],                NGr, 0);
        m.put(_LampPropName[17],                NOb, 0);

        //if (LS!=NULL){
        m.put(_LampPropName[18], FirstLS.MyStat2, 0);
        m.put(_LampPropName[19], FirstLS.MyStat3, 0);
        m.put(_LampPropName[20], FirstLS.MyStat4, 0);
        m.put(_LampPropName[21], FirstLS.__MyStat5, 0);
        // }

    }
}


void Lamp::Get()
{
    Element::Get();
    {
        TLampMEM MM;
        MM.LD.TypKp = TypKp;
        MM.LD.NKp = NKp;
        MM.LD.NGr = NGr;
        MM.LD.NOb = NOb;

        //if (LS!=NULL)
        memcpy(&MM.LD.LS, &FirstLS, sizeof(__tLStat));
        memcpy(&MM.GE, &GrpahExData, sizeof(GrpahExData));
        memcpy(&MEM.name16, &MM, sizeof(TLampMEM));
    }
};

void Lamp::UpdateState()
{
    Element::UpdateState();
    // энэнерги
    /*if (LS!=NULL){
       bool bLS=memcmp(LS,&LastLS,sizeof(LastLS));
       StateChanged=StateChanged || bLS;
       LastLS=*LS;
    }
    */
}




void Lam4::UpdateState()
{
    Strel::UpdateState();
    if (name[0] == '!') {
        // счетчик осей
        if (name[1] == '—') StateChanged = true;
        if (name[1] == 'S') StateChanged = true;
    }
}

int  Lam4::GetSubType()
{
    if (name[0] == '!') {
        // счетчик осей
        if (name[1] == '—') return 101;
        if (name[1] == 'S') return 102;
        if (name[1] == '‡') return 103;
    }
    return 0;
};


void Lam4::ShowENG1(int x, int y)
{
    int  diam;
    int  diam2;
    //int sos;
    int c1 = (fimpuls_busi == 1);
    int c2 = (fimpuls_plus == 1);
    //int c3 =( f(impuls_mnus)==1);
    //int c4 =( f(impuls_kzm)==1);
    //int cx  = (((set[C_M])/16 /8)/8)%8;
    //
    //if(!Test_strel(c1,c2,0,0,0)&&(MOD==RD))return;
    //
    int prD = 0;
    if (name[2] == 'А') prD = 1;
    if (name[2] == 'П') prD = 2;
    if (name[3] == 'А') prD = 1;
    if (name[3] == 'П') prD = 2;
    diam  = 15;
    diam2 = 13;
    if (MUL_Y < 16) diam  = 10;
    if (MUL_Y < 16) diam2 =  8;
    if (MUL_Y < 9)  diam  =  5;
    if (MUL_Y < 9)  diam2 =  4;
    if (prD == 0)
        setcolor(C_D);
    if (prD == 1)
        setcolor(GELT);
//  setcolor(CYAN_m);
    if (prD == 2)
        setcolor(ZEL);
    //sos = c1*2 +c2;
    if (!c1) setcolor(9);  //???
    setfillstyle(1, FON);
    fillellipse(x, y, diam, diam);


// Линия
    setlinestyle(SOLID_LINE, 0, 3);
    if (c2) {
        setcolor(KRA);
        line(x, y - diam2, x, y + diam2);
    } else {
        if (prD == 0)
            setcolor(C_D);
        if (prD == 1)
//     setcolor(CYAN_m);
            setcolor(GELT);
        if (prD == 2)
            setcolor(ZEL);
//     setcolor(KRA);
        line(x - diam2, y, x + diam2, y);
    }

    if (CurrentPicture == LT) {
        setcolor(C_D);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        OutTextXY(x, y - diam - 10, name + 1);
    }
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setlinestyle(SOLID_LINE, 0, 1);

}


void Lam4::ShowBML(int x, int y)
{
    //int typi;
    //if( !strcmp("ЉЂ" ,name))  typi = 0;
    //if( !strcmp("ђЋЌ" ,name)) typi  = 1;
    //if( !strcmp("ђЋ—" ,name)) typi  = 2;
    //if( !strcmp("‘“" ,name))  typi  = 3;
    /*
    if (f(impuls_busi)){
       ShowImg(typi,x,y);
    }else   ShowImg1(typi,x,y)1;
    */
    if (CurrentPicture == LT) {
        setcolor(C_D);
        _SetText(ARIAL10b, LEFT_TEXT, CENTER_TEXT);
        OutTextXY(x + 20, y, name);

    }
    return ;
}
void  Lam4::Show()
{
    Strel::Show();

    byte sdvig_dla_star_eng = 0;
    int cc = 0;
    int FlHid = 0;
    int kv = 0;
    int c1 = (fimpuls_busi == 1);
    int c2 = (fimpuls_plus == 1);
    int c3 = (fimpuls_mnus == 1);
    int c4 = (fimpuls_kzm == 1);
    int c5 = (fimpuls_kmu == 1);
    int cx  = 1;//(((set[C_M])/16 /8)/8)%8;
    if (name[0] == '*') {
        if (
            (!strcmp("*РА1" , name)) ||
            (!strcmp("*РП1" , name)) ||
            (!strcmp("*РАВ" , name)) ||
            (!strcmp("*РПВ" , name)) ||
            (!strcmp("*РАВ " , name)) ||
            (!strcmp("*РПВ " , name)) ||
            (!strcmp("*РАЗ " , name)) ||
            (!strcmp("*РПЗ " , name)) ||
            (!strcmp("*РАЗ" , name)) ||
            (!strcmp("*РПЗ" , name))
        )  {
            ShowENG1(x, y); return;
        }
        if (
            (!strcmp("*ФАРБ", name)) ||
            (!strcmp("*МАЗ" , name)) ||
            (!strcmp("*МАВ" , name)) ||
            (!strcmp("*МПВ" , name)) ||
            (!strcmp("*МПЗ" , name)) ||
            (!strcmp("*Ввод", name)) ||
            (!strcmp("*ДГА" , name)) ||
            (!strcmp("*ПТО" , name))
        )  sdvig_dla_star_eng = 1 ;
        kv = 1;
        c3 = 1;

    }




    _SetText(ARIAL10b, CENTER_TEXT, CENTER_TEXT);
    if (name[0] == '&') {
        kv = 1;  /*     y =  65; */
    }
    //  !!!!!!!!!!!!!!!!!!!
    // ===== для горки ===

    if (name[0] == '!') {
        //  фотоустройство
        if (name[1] == '”') {}
        // счетчик осей
        if (name[1] == '—') {
            int osi = 0 ;
            char bf[10];
            if (fimpuls_busi == 33) osi = 0; else
                osi =
                    f(impuls_busi + 0) * 1 +
                    f(impuls_busi + 1) * 2 +
                    f(impuls_busi + 2) * 4 +
                    f(impuls_busi + 3) * 8 +
                    f(impuls_busi + 4) * 16 +
                    f(impuls_busi + 5) * 32 +
                    f(impuls_busi + 6) * 64 +
                    f(impuls_busi + 7) * 128;
            if (osi <= 0) setcolor(FON1); else
                setcolor(LIN_W);
            setfillstyle(1, FON);
            _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
            int shir = textwidth("888");
            barx(x - 1, y - textheight("888") / 2 - 2, x + shir + 1, y + textheight("888") / 2 + 2);

            itoa(osi, bf, 10);
            OutTextXY(x + shir / 2, y, bf);
            _SetText(F_DEFAULT, LEFT_TEXT, CENTER_TEXT);
        }
        // счетчик осей ТТ
        if (name[1] == 'S') {
            int osi = 0 ;
            char bf[10];
            setcolor(LIN_W);
            setfillstyle(1, FON);
            _SetText(F_DEFAULT, LEFT_TEXT, CENTER_TEXT);
            barx(x - 1, y - textheight("88888") / 2 - 2, x + textwidth("88888") + 1, y + textheight("88888") / 2 + 2);
            osi =
                (1 - f(impuls_busi + 0)) * 1 +
                (1 - f(impuls_busi + 1)) * 2 +
                (1 - f(impuls_busi + 2)) * 4 +
                (1 - f(impuls_busi + 3)) * 8 +
                (1 - f(impuls_busi + 4)) * 16 +
                (1 - f(impuls_busi + 5)) * 32 +
                (1 - f(impuls_busi + 6)) * 64 +
                (1 - f(impuls_busi + 7)) * 128 +
                (1 - f(impuls_busi + 8)) * 256 +
                (1 - f(impuls_busi + 9)) * 512;

            itoa(osi, bf, 10);
            OutTextXY(x, y, bf);
        }
        // замедлитель
        if (name[1] == '‡') {
            int len = (S_WAY_X + mas) * MUL_X;
            //int swi=c2*2+c1;
            setcolor(LIN_W);
            char bf[2];
            bf[1] = 0;

            cc = 0; bf[0] = 0; setfillstyle(1, FON);
            if (c1) {
                bf[0] = '1'; cc = 1; setfillstyle(1, KRA);
            }
            if (c2) {
                cc = 0; setfillstyle(1, ZEL);
            }
            if (c3) {
                bf[0] = '2'; cc = 2; setfillstyle(1, KRA);
            }
            if (c4) {
                bf[0] = '3'; cc = 3; setfillstyle(1, KRA);
            }
            if (c5) {
                bf[0] = '4'; cc = 4; setfillstyle(1, KRA);
            }
            //         if(!(c1&c2&c3&c4&c5))setfillstyle(1,FON);
            //         if(!cc){ setfillstyle(1,FON); bar(x+len/2-5,y+sh_y-1,x+len/2+5,y+sh_y+10);}

            barx(x + 1, y - sh_y - sh_y, x + len - 1, y - sh_y - 2);
            barx(x + 1, y + sh_y + sh_y, x + len - 1, y + sh_y + 2);
            if (cc) {
                setcolor(C_D);
                _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
                setfillstyle(1, FON);
                //                 fillellipse(x+len/2,y+sh_y+5,5,5);
                //                 OutTextXY(x+len/2,y+sh_y+6+15,"1");
                OutTextXY(x + len / 2, y + sh_y + 6 + 8, bf);
            }
        }
        return;
    }

    if (name[0] != '$') {
        if ((c1 == 0) && (c2 == 0))  clr = FON;
        if ((c1 == 0) && (c2 == 1))  clr = TXT;
        if ((c1 == 1) && (c2 == 0))  clr = COLOR_B;
        if ((c1 == 1) && (c2 == 1))  clr = GELT;

        if (AO->bDopPriznak) {
            if ((nomer > 0) && ((c1 == 1) && (c2 == 0))) clr = nomer;
        }


        if (
            (fimpuls_busi == 33) ||
            (fimpuls_plus == 33) ||
            (fimpuls_mnus == 33) ||
            (fimpuls_kzm == 33)
        )   clr = BIRUZOVIJ;
        //
        //if(!Test_strel(clr,c3,c4,0,0)&&(MOD==RD))return;
        //
        if ((c3 != 1) && (c4 != 1)) {
            if ((CurrentPicture == BG) && (cx == 1)) FlHid = 1;
        }
        if (FlHid == 1) {//(( c3!=1 )&&(cx!=1)) {
            if (CurrentPicture == BG) {
                if (MOD == RD) return; else if (impuls_mnus == 0)return;
            }
        }
        if (!FlHid)  setcolor(TXT); else
            setcolor(FON);

        //прорисовка ламп по ОСТу32

        if ((AO->TypLamp == 32) || (AO->TypLamp == 33)) {
            if ((AO->TypName == 3) && (MOD == RD) && (masy != 0) && (CurrentPicture == LT)) return;

            int tw, th;
            tw = textwidth(name) + 4;
            tw = (tw / MUL_X) * MUL_X + ((tw % MUL_X) && 1) * MUL_X - 2;
            th = textheight(name);
            th = (th / MUL_Y) * MUL_Y + ((th % MUL_Y) && 1) * MUL_Y - 2;
            _SetText(ARIAL12b, CENTER_TEXT, CENTER_TEXT);
            if (MUL_Y < 16) _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
            if ((CurrentPicture == LT) || (c4) || FlHid || (MOD == ED)) {
                if (!FlHid) {
                    setcolor(clr);
                    if (clr == FON) clr = LIN;
                    //       setfillstyle(1,clr);
                } else {
                    setcolor(C_D);
                }
                setcolor(clr);
                //            setcolor(C_D);
                //int thh = th;
                //if(CurrentPicture==BG) thh = 0;
                if (name[0] == '&')
                    OutTextXY(x + tw / 2, y, name + 1);
                //               OutTextXY(x+tw/2,y+th/2,name+1);
                else
                    OutTextXY(x + tw / 2, y, name);
                //               OutTextXY(x+tw/2,y+th/2,name);
            }
            return;
        }

        if ((CurrentPicture == LT) || (c4) || FlHid) {
            if (!kv) OutTextXY(x, y - 6, name);
        }
        if (!FlHid) {
            setcolor(C_D);
            setfillstyle(1, clr);
        } else {
            setcolor(FON);
            setfillstyle(1, FON);
        }
        if (!kv) {
            if (MUL_Y < 16)
                fillellipse(x, y + 6, 4, 4);
            else
                fillellipse(x, y + 6, 6, 6);
        } else {
            int tw, th;
            tw = textwidth((name + 1)) + 4;
            tw = (tw / MUL_X) * MUL_X + ((tw % MUL_X) && 1) * MUL_X - 2;
            th = textheight((name + 1)) + 3;
            th = (th / MUL_Y) * MUL_Y + ((th % MUL_Y) && 1) * MUL_Y - 2;
            if (MUL_Y < 16) th += 4;
            if (sdvig_dla_star_eng) {
                y -= (MUL_Y / 2 + 1);
            }

            if (clr != FON) {
                Mini_Box(x, y , x + tw, y + th , LIN, C_D, clr);
                if (clr == ZEL)  setcolor(C_D); else
                    setcolor(LIN);
                if ((clr == TXT) || (clr == GELT)) setcolor(C_D);
            }  else {
                if ((FlHid) && (CurrentPicture == BG)) {
                    setcolor(FON);
                    barx(x, y, x + tw + 1, y + th + 1);
                } else {
                    setcolor(BLUE_mmm);
                    barx(x, y, x + tw + 1, y + th + 1);
                }
            }
            OutTextXY(x + tw / 2, y + th / 2, (name + 1));
        }
    } else {
        if ((c1 == 0) && (c2 == 0))  clr = FON;
        if ((c1 == 0) && (c2 == 1))  clr = TXT;
        if ((c1 == 1) && (c2 == 0))  clr = LIN;
        if ((c1 == 1) && (c2 == 1))  clr = GELT;
        //
        //if(!Test_strel(clr,c3,c4,0,0)&&(MOD==RD)){ _SetText(F_DEFAULT,CENTER_TEXT,CENTER_TEXT);return;}
        //
        // вот тееперь я точно ничего не понимаю
        //    priznak_pereris_strel_if_change_mu = 1;
        int st_st = sh_y * masy;
        int len = (WAY_X + mas) * MUL_X;
        if (!FlHid)
            setcolor(BLUE_m);
        else
            setcolor(FON);

        if (
            (fimpuls_busi == 33) ||
            (fimpuls_plus == 33) ||
            (fimpuls_mnus == 33) ||
            (fimpuls_kzm == 33)
        )   clr = BIRUZOVIJ;


        if (!FlHid)
            setfillstyle(1, clr);
        else
            setfillstyle(1, FON);
        bar(x     , y - st_st , x + len , y + st_st);

    }
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
}
TYP  Lam4::GetType()
{
    return LAM4;
}






TYP  SuperLamp2::GetType()
{
    return SUPERLAMP2;
}


SuperLamp2::SuperLamp2()
{
    TypeLamp = 0;
    bAlarmLamp = false;
    bCheck = false;
    bRingInGrid=false;
    bTime=false;
    timesec_begin=0;
    timesec_dt=0;
}
void SuperLamp2::UpdateState()
{
    Strel::UpdateState();
    SetStateColors();
    if (bTime){
        if (impuls_busi>=1000){

                long timesecD=0;
                if (GetDatagramPacket2_Func!=NULL){
                        TDatagramPacket2 *DatagramPacket2=(TDatagramPacket2 *)GetDatagramPacket2_Func(1,Stan()->ChanelNames[impuls_busi/1000]);
                        if (DatagramPacket2!=NULL) {
                                timesecD=DatagramPacket2->time;
                        }
                } else {
                        time(&timesecD);
                }
                if (fimpuls_busi==0) {
                        timesec_begin=0;
                        timesec_dt=0;
                }else {
                        if (timesec_begin==0) timesec_begin=timesecD;
                        timesec_dt=timesecD-timesec_begin;
                }
        }
    }

}
void SuperLamp2::SetStateColors()
{
    int st1 = fimpuls_busi;
    int st2 = fimpuls_plus;
    int st3 = fimpuls_mnus;
    int st4 = fimpuls_kzm;

    if (masy == 41) {
        // АВТОПИЛОТ!
        TAVStanInfo* AVStanInfo = EXD.SI_GetStan(pVisibleArray->pStation->Dat->filename);
        if (AVStanInfo == NULL) {
            clr = BIRUZOVIJ;
        } else {
            clr = FON1;
            if (AVStanInfo->AV_DU) {
                clr = ZEL;   // < >        < >
                if (AVStanInfo->z_cnt[nomer] == 1) clr = GELT;
                if (AVStanInfo->z_cnt[nomer] == 2) clr = KRA_GELT;
            }
        }
    } else if (masy < 0) {
        if (fimpuls_busi == 1) clr = -masy; else clr = FON;
    } else {
        int setc = st1 * 8 + st2 * 4 + st3 * 2 + st4;
        TypeLamp = ((masy < MaxLampType) && (masy >= 0)) ? masy : 0;

        if ((st1 == 33) || (st2 == 33) || (st3 == 33) || (st4 == 33)) clr = BIRUZOVIJ; else
            clr = wc_GetColor(TypeLamp, setc);
    }
    // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
    if (IsClrMig(clr)) StateChanged = true;
}


void  ShowKPP(int x, int y, int tw, int th, int col)
{
    setcolor(col);
    int dx = tw / 8;
    int dy = th / 4;
    rectangle(x - tw / 2 + dx, y - th / 2 + dy, x + tw / 2 - dx, y + th / 2 - dy);
    line(x - tw / 2, y, x + tw / 2, y);

}

void  ShowZEMLYA(int x, int y, int tw, int th, int col)
{
    setcolor(col);
    float dx = 1.*tw / 8;
    float dy = 1.*th / 8;
    int y0 = y - th / 2;
    line(x     , y0 + dy*3, x     , y0 + dy*5);
    line(x - dx*3, y0 + dy*5, x + dx*3, y0 + dy*5);
    line(x - dx*2, y0 + dy*6, x + dx*2, y0 + dy*6);
    line(x - dx*1, y0 + dy*7, x + dx*1, y0 + dy*7);

}
void  ShowAUM(const char *name,int x, int y,  int i1,int i1m,int i2,int i2m)
{
    if (MOD==ED){
        i1=1;
        i1m=0;
        i2=0;
        i2m=0;
    }
    if (CurrentPicture==BG){
        if ((i1==0) && (i1m==0) && (i2==0) && (i2m==0)) return;
    }
    int p=0;
    int d=0;
    int b=0;
    if (strcmp("_АУМЧ1_", name) == 0) {d = 0; p=1;} else
    if (strcmp("_АУМЧ2_", name) == 0) {d = 0; p=2;} else
    if (strcmp("_АУМЧ3_", name) == 0) {d = 0; p=3;} else
    if (strcmp("_АУМН1_", name) == 0) {d = 1; p=1;} else
    if (strcmp("_АУМН2_", name) == 0) {d = 1; p=2;} else
    if (strcmp("_АУМН3_", name) == 0) {d = 1; p=3;} else
    if (strcmp("_АУМЧ1Б_", name) == 0) {b=1;d = 0; p=1;} else
    if (strcmp("_АУМЧ2Б_", name) == 0) {b=1;d = 0; p=2;} else
    if (strcmp("_АУМЧ3Б_", name) == 0) {b=1;d = 0; p=3;} else
    if (strcmp("_АУМН1Б_", name) == 0) {b=1;d = 1; p=1;} else
    if (strcmp("_АУМН2Б_", name) == 0) {b=1;d = 1; p=2;} else
    if (strcmp("_АУМН3Б_", name) == 0) {b=1;d = 1; p=3;}
    int colp=C_D;
    int colb1=FON;
    int colb2=FON;

    if (p==1){
        colp=COLOR_SVZ;
        if (i2==1) colb1=COLOR_SVZ;
        if (i2m==1) colb1=ZEL_SER;
        if (i1==1) colb2=COLOR_SVZ;
        if (i1m==1) colb2=ZEL_SER;
    } else {
        colp=GELT;
        if (i2==1) colb1=GELT;
        if (i2m==1) colb1=GELT_SER;
        if (i1==1) colb2=GELT;
        if (i1m==1) colb2=GELT_SER;
    }
    TPoint FP1[3];
    TPoint FP2[3];
    int clr3[3] = {   colp, colp, colp};
    int tw=MUL_X*0.8;
    int th=MUL_Y-1;
    int dx=MUL_X/4;
    int dy=MUL_Y/4;

    if (b){
          if (i1==1) setfillstyle(SOLID_FILL,LIN); else setfillstyle(SOLID_FILL,FON1);
    }

    if (d==0){
        if (b){
          if (i1==1) setcolor(LIN); else setcolor(FON1);
          bar(x-tw*2-dx, y-th/2-dy, x+dx, y+th/2.+dy);
          Draw_Ramka(x-tw*2-dx, y-th/2-dy, x+dx, y+th/2.+dy,EDGE_BUMP);
        }
        FP1[0]=TPoint(x   ,  y);
        FP1[1]=TPoint(x-tw   ,  y-th/2.);
        FP1[2]=TPoint(x-tw   ,  y+th/2.);
        FP2[0]=FP1[0];FP2[0].x=FP1[0].x-tw-1;
        FP2[1]=FP1[1];FP2[1].x=FP1[1].x-tw-1;
        FP2[2]=FP1[2];FP2[2].x=FP1[2].x-tw-1;

        PolyColor(colb1, FP1, clr3, 3);
        PolyColor(colb2, FP2, clr3, 3);


    } else {
        if (b){
          if (i1==1) setcolor(LIN); else setcolor(FON1);
          bar(x+tw*2+dx, y-th/2-dy, x-dx, y+th/2.+dy);
          Draw_Ramka(x+tw*2+dx, y-th/2-dy, x-dx, y+th/2.+dy,EDGE_BUMP);
        }
        FP1[0]=TPoint(x   ,  y);
        FP1[1]=TPoint(x+tw   ,  y-th/2.);
        FP1[2]=TPoint(x+tw   ,  y+th/2.);
        FP2[0]=FP1[0];FP2[0].x=FP1[0].x+tw+1;
        FP2[1]=FP1[1];FP2[1].x=FP1[1].x+tw+1;
        FP2[2]=FP1[2];FP2[2].x=FP1[2].x+tw+1;
        PolyColor(colb1, FP1, clr3, 3);
        PolyColor(colb2, FP2, clr3, 3);

    }


}

void  ShowTime(int x, int y, long timesec)
{
    char stime[5]=" 99 ";
    int tw = textwidth(stime)+2;
    int th = textheight(stime)+3;
    if ((timesec>0)&&(timesec<=99)){
        memset(stime,0,sizeof(stime));
        sprintf(stime, " %d ",timesec);
        setcolor(C_D);
        setfillstyle(1, TXT);
        barx(x - tw /2, y  , x + tw /2, y + th);
        OutTextXY(x, y + th/2, stime);
    } else {
        setcolor(FON);
        setfillstyle(1, FON);
        barx(x - tw /2, y  , x + tw /2, y + th);
    }



}


void  SuperLamp2::Show()
{
    Strel::Show();
    if ((MOD == ED)) {
        clr = 7;
        if ((impuls_busi == 0) && (impuls_plus == 0) && (impuls_mnus == 0) && (impuls_kzm == 0)) clr = 9;
        timesec_dt=99;
    }

    // не рисуем на участке без кму
    if ((CurrentPicture == BG) && (impuls_kmu != 0) && (fimpuls_kmu == 0))
        return;

    if (masy == 42) {
        ShowAUM(name,x, y, fimpuls_busi,fimpuls_plus,fimpuls_mnus,fimpuls_kzm);
        return;
    }


    // не рисуем у ДНЦ
    if ((DNC == 1) && (Prz[2] != 0) && (CurrentPicture == LT))
        return;

    unsigned int font = Prz[1] ? Prz[1] : 10u;
    unsigned int font_size = Prz[0] ? (BYTE)(Prz[0]) : 10u;



    _SetText(font, CENTER_TEXT , CENTER_TEXT);
    _SetTextSize(font_size);
    int tw = textwidth(name);
    int th = textheight(name);

    int y1;
    if (mas >= 10) {
        // yнаходим рамку
        tw = (masx2 + 1) * MUL_X;
        y1 = y - th / 2;
    }
    int r = 7;
    if (MUL_Y < 16) r = 5;
    bool bkpp = false;
    if (strcmp("_КПП_", name) == 0) bkpp = true;
    bool bzemlya = false;
    if (strcmp("_ЗЕМЛЯ_", name) == 0) bzemlya = true;



    switch (mas) {
    default:
    case 0: {
        setcolor(clr);
        if (bkpp) ShowKPP(x, y, tw, th, clr); else if (bzemlya) ShowZEMLYA(x, y, tw, th, clr); else
            OutTextXY(x, y, name);
    }; break;

    case 1: {
        setcolor(C_D);
        setfillstyle(1, clr);
        if (clr == FON1) setcolor(FON);
        barx(x - (tw + 3) / 2, y - (th + 3) / 2, x + (tw + 3) / 2, y + (th + 3) / 2);
        OutTextXY(x, y, name);

    }; break;
    case 2: {
        setcolor(C_D);
        setfillstyle(1, clr);
        if (bRingInGrid){
          fillellipse(x, y, r, r);
          _SetText(font, CENTER_TEXT , BOTTOM_TEXT);
          OutTextXY(x, y-r-1, name);
        } else {
          fillellipse(x, y + th / 2 + r + 1, r, r);
          _SetText(font, CENTER_TEXT , CENTER_TEXT);
          OutTextXY(x, y, name);
        }
    }; break;
    case 10: {
        setcolor(clr);
        DrawText(x + 2, y1 + 1, tw - 2, th - 1, name);
    }; break;

    case 11: {
        setcolor(C_D);
        setfillstyle(1, clr);
        if (clr == FON1) setcolor(FON);
        barx(x + 1, y-th/2-1, x + tw - 1, y + th/2+1 );
        DrawText(x + 2, y-th/2 + 0, tw - 2, th, name);
        if (bTime) ShowTime(x + tw/2,y + th/2+2,timesec_dt);

    }; break;
    case 12: {
        setcolor(C_D);
        setfillstyle(1, clr);
        fillellipse(x + tw / 2, y1 + th + r + 1, r, r);
        DrawText(x + 2, y1 + 1, tw - 2, th + 2, name);
        if (bTime) ShowTime(x + tw/2,y1 + th + r + r+1,timesec_dt);
    } ; break;
    case 21: {
        setcolor(C_D);
        setfillstyle(1, clr);
        if (clr == FON1) setcolor(FON);
        roundrect(x - (tw + 3) / 2, y - (th + 3) / 2, x + (tw + 3) / 2, y + (th + 3) / 2, th / 2, th / 2);
        if (bkpp) ShowKPP(x, y, tw, th, C_D); else if (bzemlya) ShowZEMLYA(x, y, tw, th, C_D); else
            OutTextXY(x, y, name);
    } ; break;

    case 22: {
        setcolor(C_D);
        setfillstyle(1, clr);
        if (clr == FON1) setcolor(FON);
        roundrect(x + 1, y1, x + tw - 1, y1 + th + 2, th / 2, th / 2);
        if (bkpp) ShowKPP(x + (tw) / 2, y1 + th / 2, tw, th, C_D); else if (bzemlya) ShowZEMLYA(x + (tw) / 2, y1 + th / 2, tw, th, C_D); else
            DrawText(x + 2, y1 + 1, tw - 2, th, name);
    } ; break;


    }
    _SetTextSize(1);
    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
}



void SuperLamp2::Set()
{
    Strel::Set();
    Prz[2]  = MEM.name[15];

}
void SuperLamp2::Get()
{
    Strel::Get();
    MEM.name[15] = Prz[2];
}

static String _SuperLamp2PropName[] = {
    "цфPrz0",          // 0
    "цфPrz1",          // 1
    "цфPrz2",          // 2
    "цфPrz3",          // 3

    "цфNomer",         // 4
    "смname_",           //5
    "смИМЯ",            //6
    "лгПроверять",         // 7
    "лгАвария",         // 8
    "лгКругПоСетке",         // 9
    "лгВремя"         // 10


};


void SuperLamp2::SetPropMap(TPropMap &m)
{
    // перекрываю от стрелок
    Ways::SetPropMap(m);
    int _n = 0;
    Prz[0]  = m.geti(_SuperLamp2PropName[_n++]);
    Prz[1]  = m.geti(_SuperLamp2PropName[_n++]);
    Prz[2]  = m.geti(_SuperLamp2PropName[_n++]);
    Prz[3]  = m.geti(_SuperLamp2PropName[_n++]);
    nomer   = m.geti(_SuperLamp2PropName[_n++]);
    memset(name, '\x0', sizeof(name));
    strncpy(name, m.get(_SuperLamp2PropName[_n++]).c_str(), sizeof(name));
    _n++;
    bCheck   = m.geti(_SuperLamp2PropName[_n++]);
    bAlarmLamp   = m.geti(_SuperLamp2PropName[_n++]);
    bRingInGrid   = m.geti(_SuperLamp2PropName[_n++]);
    bTime   = m.geti(_SuperLamp2PropName[_n++]);
}


void SuperLamp2::GetPropMap(TPropMap &m)
{
    Ways::GetPropMap(m);
    int _n = 0;
    m.put(_SuperLamp2PropName[_n++], Prz[0], 0);
    m.put(_SuperLamp2PropName[_n++], Prz[1], 0);
    m.put(_SuperLamp2PropName[_n++], Prz[2], 0);
    m.put(_SuperLamp2PropName[_n++], Prz[3], 0);

    m.put(_SuperLamp2PropName[_n++], nomer, 0);
    m.put(_SuperLamp2PropName[_n++], name);
    m.put(_SuperLamp2PropName[_n++], name);
    m.put(_SuperLamp2PropName[_n++], bCheck, 0);
    m.put(_SuperLamp2PropName[_n++], bAlarmLamp, 0);
    m.put(_SuperLamp2PropName[_n++], bRingInGrid, 0);
    m.put(_SuperLamp2PropName[_n++], bTime, 0);

}




//==========================================
CommLmp::CommLmp()
{
    Prz[0] = 22;
    lComps = new TList();
}
CommLmp::~CommLmp()
{
    delete lComps;
}

void CommLmp::CollectComps()
{
    AComp * ac;
    lComps->Clear();
    Station *S = pVisibleArray->pStation ;
    for (int i = 1; i < Units_Size; i++) {
        for (int j = 0; j < S->POLE[i]->GetArraySize(); j++) {
            ac = S->POLE[i]->GetObjPtr(j);
            if (ac->ExtPriz.UseInCommLmp) lComps->Add(ac);
        }
    }
}

void CommLmp::UpdateState()
{
    AComp * ac;
    try {
        if (MOD == ED) {
            lComps->Clear();
        } else {
            if (lComps->Count == 0) CollectComps();
            // находим общее
            int b = 0;
            for (int i = 0; i < lComps->Count; i++) {
                ac = (AComp *)lComps->Items[i];
                ac->UpdateState(); // НЕКРАСИВО ТО КАК!
                b = ac->IsAlarmState();
                ac->StateChanged = true; // УЖАС
                if (b != 0) break;
            }
            if (b != impuls_busi) StateChanged = true;
            impuls_busi = b;
            if (impuls_busi != 0) fimpuls_busi = 1; else fimpuls_busi = 0;
            clr = FON1;
            if (fimpuls_busi == 1) {
                if (this->nomer == 0) clr = RED; else clr = nomer;
            }
            // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
            if (IsClrMig(clr)) StateChanged = true;
        }
    } catch (...) {}

}
void CommLmp::Show()
{
    SuperLamp2::Show();
}
TYP  CommLmp::GetType()
{
    return COMMLMP;
}
void CommLmp::Set()
{
    SuperLamp2::Set();
}
void CommLmp::Get()
{
    SuperLamp2::Get();
}


//==========================================
extern T_GetDatagramData_Func GetDatagramData_Func;
DtgLmp::DtgLmp()
{
    PacketName = "";
    PacketType = 0; ByteOffset = 0; NumberBit = 0;
    Prz[0] = 22;
    bByteChecking = false;
}
DtgLmp::~DtgLmp()
{
}
struct TPacketData {
    uint8 byte[490];
};
int GetPacketBit(String PacketName, int PacketType, int ByteOffset, int NumberBit)
{
    if (GetDatagramData_Func == NULL) return 33;
    TPacketData *DtgData = (TPacketData *) GetDatagramData_Func(PacketType, PacketName.c_str());
    if (DtgData == NULL) return 33;
    int r = ((DtgData->byte[ByteOffset] >> NumberBit) & 0x01) ? 1 : 0;
    return r;
}
int GetPacketByte(String PacketName, int PacketType, int ByteOffset)
{
    if (GetDatagramData_Func == NULL) return 33;
    TPacketData *DtgData = (TPacketData *) GetDatagramData_Func(PacketType, PacketName.c_str());
    if (DtgData == NULL) return 33;
    int r = DtgData->byte[ByteOffset];
    return r;
}
void DtgLmp::UpdateState()
{
    try {
        if (MOD == ED) {
            clr = TXT;
        } else {
            if (bByteChecking) {

            }
            int r = GetPacketBit(PacketName, PacketType, ByteOffset, NumberBit);
            if (r != fr) StateChanged = true;
            fr = r;
            clr = FON1;
            if (r == 1) {
                if (this->nomer == 0) clr = RED; else clr = nomer;
            }
            if (r == 33) clr = BIRUZOVIJ;
            // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
            if (IsClrMig(clr)) StateChanged = true;
        }
    } catch (...) {}

}
void DtgLmp::Show()
{
    SuperLamp2::Show();
}
TYP  DtgLmp::GetType()
{
    return DTGLMP;
}

static String _DtgLmpPropName[] = {
    "PacketName",          // 0
    "PacketType",          // 1
    "ByteOffset",          // 2
    "NumberBit",           // 3
    "лгByteChecking",      // 4
    "цфЦвет2"              // 5



};
void DtgLmp::Set()
{
    SuperLamp2::Set();

}
void DtgLmp::Get()
{
    SuperLamp2::Get();

}
void DtgLmp::SetPropMap(TPropMap &m)
{
    // перекрываю от стрелок
    SuperLamp2::SetPropMap(m);
    int _n = 0;
    PacketName = m.get(_DtgLmpPropName[_n++]);
    PacketType  = m.geti(_DtgLmpPropName[_n++]);
    ByteOffset  = m.geti(_DtgLmpPropName[_n++]);
    NumberBit  = m.geti(_DtgLmpPropName[_n++]);
    bByteChecking  = m.geti(_DtgLmpPropName[_n++]);
    Clr2  = m.geti(_DtgLmpPropName[_n++]);
}
void DtgLmp::GetPropMap(TPropMap &m)
{
    SuperLamp2::GetPropMap(m);
    int _n = 0;
    m.put(_DtgLmpPropName[_n++], PacketName);
    m.put(_DtgLmpPropName[_n++], PacketType);
    m.put(_DtgLmpPropName[_n++], ByteOffset);
    m.put(_DtgLmpPropName[_n++], NumberBit);

    m.put(_DtgLmpPropName[_n++], bByteChecking);
    m.put(_DtgLmpPropName[_n++], Clr2, 0);
}


TYP  tLOG_LAMP::GetType()
{
    return LOG_LAMP;
}


tLOG_LAMP::tLOG_LAMP()
{
    for (int i = 0; i < 4; i++) {
        vFormula[i].clear(); vFormulaP[i].clear();
    }
}
void tLOG_LAMP::UpdateState()
{
    SuperLamp2::UpdateState();
    int R[4];
    for (int i = 0; i < 4; i++) {
        fevFormulaSetR(this, vFormulaP[i]);
        R[i] = feFormulaResultP(vFormulaP[i]);
    }
    fimpuls_busi = R[0] ;
    fimpuls_plus = R[1] ;
    fimpuls_mnus = R[2] ;
    fimpuls_kzm = R[3] ;

    SuperLamp2::SetStateColors();

}
static String _tLOG_LAMPPropName[] = {
    "фсСигнал1",       // 0
    "фсСигнал2",       // 1
    "фсСигнал3",       // 2
    "фсСигнал4"        // 3


};


void tLOG_LAMP::SetPropMap(TPropMap &m)
{
    // перекрываю от стрелок
    SuperLamp2::SetPropMap(m);
    int _n = 0;
    for (int i = 0; i < 4; i++) {
        feSt2vFormula(m.get(_tLOG_LAMPPropName[_n++]).c_str(), vFormula[i]);
        fevFormulaElement2PolskaNota(vFormula[i], vFormulaP[i]);
    }

}


void tLOG_LAMP::GetPropMap(TPropMap &m)
{
    SuperLamp2::GetPropMap(m);
    int _n = 0;
    for (int i = 0; i < 4; i++) {
        m.put(_tLOG_LAMPPropName[_n++], fevFormula2St(vFormula[i]));
    }
}




//==========================================

