
#include "aheaders_cpp.h"
#include "APch.h"

#include "Str_fun.h"
//#include<math.h>
#include<fastmath.h>
#include "Strel.h"


#define SW 9
#define SZ 7


int mas__;
int len_4;
int Len;

int pr1[4];
int kr[18];
int sh;
int sh2;

int NomerHeight = 0;


#define As1  120
#define As2  100




int  S(int len);    //смещение
int  S2(int len);   //----
int  S3(int len);   // обратная корректировккка
int  S4(int len);   // отраженная ширина
int  S5(int len);

int  S(int len)
{

//     return sh_y/3;
    return S2(len) / 2;

}

int  S5(int len)
{
    return S2(len);
//     return sh_y*2/3;
//     return S2(len)/2;

}

int  S4(int len)
{
    return S2(len);
    // БЛИН ЧТО-Ж  Я СДЕЛАЛ-ТО
    /*
    int A= len/2;
    int B= sh2-sh_y;
    int a ;
    int b=sh_y ;
    a = (A*b)/B;
     return a/2+sh_y  ;
    */
//    return S(len);
}


int  S2(int len)
{
//     return sh_y/3;
    unsigned long   A = len - len_4 * 2;     // len -2*len_4   похоже на правду
    unsigned long   B = sh2 - 2 * sh_y;
    int a ;
    a = sh_y * As1 * sqrt(1 + (A * A) / (B * B)) / As2;
    return a;
}

int  S3(int len)
{
//  return 0;
    unsigned long   A = len - 2 * len_4;     // len -2*len_4   похоже на правду
    unsigned long   B = sh2 - 2 * sh_y;
    int a ;
    a = (sh_y * As1 * A) / (B * As2);
    return a;
}

void   L(int x, int y, int len)
{
    int sl = len;
    len += mas__;

    if (len < 0) {
        x += len;
        len = sl - len;
    }
    y = y - sh_y / 2;
    pr1[0] = x;        pr1[1] = y;
    pr1[2] = x + len;    pr1[3] = y + sh_y;
}

void   KT(int x, int y, int len, int sw, int ll2)
{
//   int sl =len;
    int len2 = len + mas__;
    int x3 = x;

    switch (sw) {
    case 1:
        if (mas__ < 0) {
            x3 = x;
            len2 = len;

        } else {
            x3 = x;
//           len2=len;
        }
        x3 -= ll2;
        break;
    case 0:
        if (len2 < 0) {
            x3 = x + len2;
            len2 = len;
        } else {
            x3 = x;
            len2 = len;
        }
        len2 += ll2;
        break;
    }

    int y1, x1;
    y1 = y;
    y = y - sh;
    x1 = x + len;
    y1 = y1 - sh_y / 2;
    y = y - sh_y / 2;
    len_4 = len_4 + S3(len) / 2;

    kr[0] = x3;               kr[1] = y1;
    kr[2] = x3;               kr[3] = y1 - sh_y;
    kr[4] = x + len_4 - S(len);  kr[5] = y1 - sh_y;
    kr[6] = x1 - len_4 - S(len) + S3(len);  kr[7] = y;
    kr[8] = x + len2;          kr[9] = y;
    kr[10] = x + len2;          kr[11] = y + sh_y;
    kr[12] = x1 - len_4 + S(len);  kr[13] = y + sh_y;
    kr[14] = x + len_4 + S(len) - S3(len);  kr[15] = y1;
    kr[16] = x3;               kr[17] = y1;
}

void   KB(int x, int y, int len, int sw, int ll2)
{

    // int sl =len;
    int len2 = len + mas__;
    int x3 = x;

    switch (sw) {
    case 1:
        if (mas__ < 0) {
            x3 = x;
            len2 = len;
        } else {
            x3 = x;
        }
        x3 -= ll2;
        break;
    case 0:
        if (len2 < 0) {
            x3 = x + len2;
            len2 = len;
        } else {
            x3 = x;
            len2 = len;
        }
        len2 += ll2;
        break;
    }
    int y1, x1;
    y1 = y;
    y = y + sh;
    x1 = x + len;
    y1 = y1 - sh_y / 2;
    y = y - sh_y / 2;

    len_4 = len_4 + S3(len) / 2;

    kr[0] = x3;               kr[1] = y1;
    kr[2] = x3;               kr[3] = y1 + sh_y;
    kr[4] = x + len_4 - S(len);  kr[5] = y1 + sh_y;
    kr[6] = x1 - len_4 - S(len) + S3(len);  kr[7] = y;
    kr[8] = x + len2;          kr[9] = y;
    kr[10] = x + len2;          kr[11] = y - sh_y;
    kr[12] = x1 - len_4 + S(len);  kr[13] = y - sh_y;
    kr[14] = x + len_4 + S(len) - S3(len);  kr[15] = y1;
    kr[16] = x3;               kr[17] = y1;
}

void  _bar3d_(int x1, int y1, int x2, int y2, int bord, int clr)
{
    bord = bord;
    clr = clr;
    bar(x1, y1 + 1, x2, y2 - 1);
    line(x1, y1, x2, y1);
    line(x1, y2, x2, y2);
}

int  linec(int x2, int y2, int x1, int y1, int h, int direct)
{
    int xx1, yy1, xx2, yy2;
    int xxx;
    if (!direct) {
        xxx = x1; x1 = x2; x2 = xxx;
        xxx = y1; y1 = y2; y2 = xxx;
    }
    xx1 = x1; yy1 = y1;
    if (y2 < y1) {
        yy2 = yy1 - sh_y;
    } else {
        yy2 = yy1 + sh_y;
    }
    int absy2_y1 = abs(y2 - y1);
    if (absy2_y1 == 0) absy2_y1 = 1;
    if (x2 < x1) {
        xx2 = x1 - abs(x2 - x1) * h / absy2_y1;// * h;
    } else {
        xx2 = x1 + abs(x2 - x1) * h / absy2_y1;// * h;
    }
    line(xx1, yy1, xx2, yy2);
    return 1;
}

int  linec2(int x2, int y2, int x1, int y1, int h, int direct, int h1, int dx, int dy)
{
    int yy1, xx2, yy2, xx3, yy3;
    int xxx;
    if (!direct) {
        xxx = x1; x1 = x2; x2 = xxx;
        xxx = y1; y1 = y2; y2 = xxx;
    }
    //xx1=x1;
    yy1 = y1;
    if (y2 < y1) {
        yy2 = yy1 - h;
        yy3 = yy1 - h1;

    } else {
        yy2 = yy1 + h;
        yy3 = yy1 + h1;
    }
    if (y2 == y1) y2 = y1 + 1; // деление на 0!
    if (x2 < x1) {
        xx2 = x1 - abs(x2 - x1) * h / abs(y2 - y1);// * h;
        xx3 = x1 - abs(x2 - x1) * h1 / abs(y2 - y1);// * h;
    } else {
        xx2 = x1 + abs(x2 - x1) * h / abs(y2 - y1);// * h;
        xx3 = x1 + abs(x2 - x1) * h1 / abs(y2 - y1);// * h;
    }
    line(xx2, yy2, xx3, yy3);
    return 1;
}



void   _fillpoly_(int sw_tip, int far kr[], int dr, bool bShowIsNormalMnus, int  clr, int  clrfill)
{

    int t1 = 0, t2;
    int c = 1;
    int s = 1;
    //struct  fillsettingstype i;
    t2 = t1 + 8;
//    int tx=8;
    int h;
//11.10    clr=getcolor();
//11.10    getfillsettings(&i);
    fillpoly(sw_tip, kr);
    setcolor(clrfill/*i.color*/);
    if (kr[t1+1] > kr[t1+3]) c = -1;
    else c =  1;
    line(kr[t1], kr[t1+1] + c, kr[t1+2], kr[t1+3] - c);
    int n = 1;

    if (sw_tip == SW) {
        if (kr[t2+1] > kr[t2+3])c = -1;
        else c =  1;
        line(kr[t2], kr[t2+1] + c, kr[t2+2], kr[t2+3] - c);
        if ((kr[1] != dr) && (kr[1] != (dr + sh_y))) {
            n = -1;  h = 4; s = 1;
        } else {
            n = 1;   h = 12; s = 1;
        }
    }

    if (sw_tip == SZ) {
        if (kr[1] < kr[7]) {
            h = 4; s = 0;
        } else           {
            h = 8; s = 1;
        }
        if (kr[0] < kr[6]) {
            n = 1;
        } else            {
            n = -1;
        }

    }

    // это зазор в минусе
    setcolor(FON);
    linec(kr[h] + 1*n, kr[h+1], kr[h+2] + 1*n, kr[h+3], sh_y, s);
    linec(kr[h] + 2*n, kr[h+1], kr[h+2] + 2*n, kr[h+3], sh_y, s);
    // это подрисовка дырки в минусе
    setcolor(clr);
    linec(kr[h] + 3*n, kr[h+1], kr[h+2] + 3*n, kr[h+3], sh_y, s);

    if (bShowIsNormalMnus) {
        // рисуется чёрная чёрточка
        setcolor(C_D);
        linec2(kr[h] + 1*n, kr[h+1], kr[h+2] + 1*n, kr[h+3], sh_y + 3, s, sh_y*2.5 + 3, 0, 0);
        linec2(kr[h] + 2*n, kr[h+1], kr[h+2] + 2*n, kr[h+3], sh_y + 3, s, sh_y*2.5 + 3, 0, 0);
        linec2(kr[h] + 3*n, kr[h+1], kr[h+2] + 3*n, kr[h+3], sh_y + 3, s, sh_y*2.5 + 3, 0, 0);
        linec2(kr[h] + 4*n, kr[h+1], kr[h+2] + 4*n, kr[h+3], sh_y + 3, s, sh_y*2.5 + 3, 0, 0);
    }


    setcolor(clr);

}
// ограничение масштаба после которого появляются номера стрелок
// #define Lim _NAZVA_
const sdv_nazv = 0;
//    sdv_nazv =  -11;
void  Strel0::Strelka(int is, int sw_tip, int styll1, int styll2, int clr, int nm, int x_text, int y_text, char *name, bool InvresPol, int cbord1, int cbord2, bool bShowPol)
{
//   int is = _is;
    // это инверсия стрели
    bool bShowIsNormalPlus = true;
    bool bShowIsNormalMnus = false;
    if (InvresPol) {
        if (is == 1) is = 2;
        else    if (is == 2) is = 1;
        int st = styll1;
        styll1 = styll2;
        styll2 = st;
        bShowIsNormalPlus = false;
        bShowIsNormalMnus = true;
    }
    if ((!bShowPol) || (CurrentPicture == BG)) {
        bShowIsNormalPlus = false;
        bShowIsNormalMnus = false;
    }

    char *nom_sw = "      ";
    int cvet = LIN;
    if (clr == FON) cvet = FON;
    int bord_act = BLUE_m;
    itoa(nm, nom_sw, 10);
    setcolor(BLUE_m);
    // для николя
    //     if((CurrentPicture==LT)&&(MUL_Y>_NAZVA_+2)/*(MaxX>801)*/)

    if ((CurrentPicture == LT) && (AO->MaxX > 801)) {
        _SetText(ARIAL12, CENTER_TEXT, TOP_TEXT);
//            _SetText(F_DEFAULT,CENTER_TEXT,TOP_TEXT);
    } else {
        _SetText(F_LITT, CENTER_TEXT, TOP_TEXT);
    }

    if (NomerHeight == 1) {
        _SetTextSize(-sh_y*2 + 2);
    }

    if ((name[0] == '$') && ((MUL_Y > AO->_NAZVA_)||(CurrentPicture == LT))) {
        OutTextXY(x_text, y_text + sdv_nazv, name + 1);
    } else if ((nm > 0) && ((MUL_Y > AO->_NAZVA_)||(CurrentPicture == LT))) {
        OutTextXY(x_text, y_text + sdv_nazv, nom_sw);
    }
    // это выключение масштабирования текста
    if (NomerHeight != 0) {
        _SetTextSize(1);
    }


    if (sh_y <= 2) {
        bord_act = BLUE_mmm;
        if (clr != LIN) bord_act = clr; else
            clr = BLUE_mmm;
        cvet = BLUE_mmm;
        setcolor(BLUE_mmm);
    }
//    _SetText(F_DEFAULT,CENTER_TEXT,TOP_TEXT);
    _SetText(ARIAL12, CENTER_TEXT, TOP_TEXT);
    int z[4];
    z[0] = kr  [0];
    z[1] = kr  [12];
    z[2] = pr1 [0];
    z[3] = pr1 [2];
    int sd  =  0;
    int sdy = -1;




    // вычисляется какаято херомантия
    int t1;
    if (!((kr[1] != pr1[1]) &&
            (kr[1] != (pr1[1] + sh_y)))) {
        t1 = 2;
    } else {
        if (sw_tip == SW)t1 = 6; else t1 = 5;
    }
    int shi;
    shi = S2(Len) + 1;

    if (sw_tip == SW) {
        if (t1 == 6)   sd  = 0;
        if (t1 == 2)   sd  = 1;
        if (
            ((t1 == 2) && (kr[1] < kr[3])) ||
            ((t1 == 6) && (kr[1] > kr[3]))
        )              sdy = 1;
        else           sdy = -1;
    } else {
        if (sw_tip == SZ) {
            if (kr[1] < kr[7])  {
                t1 += 3; sdy = 1;
            } else              {
                sdy = -1;
            }
            if (kr[0] < kr[6])  {
                sd = 1;
            } else              {
                sd = 0;
            }
        }
    }

    switch (is) {
    case 2:
        // установка цвета заполнения для минуса
        setfillstyle(styll2, cvet);
        setcolor(cbord2);
        if (sh_y <= 0) drawpoly(sw_tip - 1, kr); else
            _fillpoly_(sw_tip, kr, pr1[1], bShowIsNormalMnus, cbord2, cvet);
        setfillstyle(styll1, clr);
        if (sh_y <= 0) {

            line(pr1[0], pr1[1], pr1[2], pr1[3]);
        } else {
            //setcolor(bord_act);
            setcolor(cbord1);
            _bar3d_(pr1[0], pr1[1], pr1[2], pr1[3], 0, 0);
            setcolor(C_D);


            setcolor(FON);
            line(kr[t1*2] - shi*(1 - sd), kr[t1*2+1] + sdy, kr[t1*2] + shi*sd, kr[t1*2+1] + sdy);
            setcolor(bord_act);
            line(kr[t1*2] - shi*(1 - sd) + 1*sd, kr[t1*2+1] + sdy*2,
                 kr[t1*2] + shi*sd - 1*(1 - sd), kr[t1*2+1] + sdy*2);


        }
        break;
    case 1:

        setfillstyle(styll1, cvet);
        setcolor(cbord1);
        _bar3d_(pr1[0], pr1[1], pr1[2], pr1[3], 0, 0);
        setfillstyle(styll2, clr);
        //setcolor(bord_act);
        setcolor(cbord2);
        _fillpoly_(sw_tip, kr, pr1[1], bShowIsNormalMnus, cbord2, clr);

        break;
    case 3:

//  здесь идет дублирование того что
// сделано по росечке
// вообще-то надо переделать рисование стрелки вообще
        setfillstyle(styll1, clr);
        setcolor(cbord1);
        if (sh_y <= 0) {
            drawpoly(sw_tip - 1, kr);
            line(pr1[0], pr1[1], pr1[2], pr1[3]);
        } else {

            //setcolor(bord_act);
            setcolor(cbord1);
//           setcolor(COLOR_B); // ПКС  БЛИН БЛИН БЛИН

            setfillstyle(styll1, clr);
            _bar3d_(pr1[0], pr1[1], pr1[2], pr1[3], 0, 0);
            setfillstyle(styll2, clr);
            _fillpoly_(sw_tip, kr, pr1[1], bShowIsNormalMnus, cbord1, clr);
            setfillstyle(styll1, clr);
            bar(pr1[0] + 1, pr1[1] + 1, pr1[2] - 1, pr1[3] - 1);
            setcolor(FON);
            setfillstyle(1, FON);

            int t1;
            if (!((kr[1] != pr1[1]) &&
                    (kr[1] != (pr1[1] + sh_y)))) {
                t1 = 2;
            } else {
                if (sw_tip == SW)t1 = 6; else t1 = 5;
            }
            int shi;
            shi = S2(Len) + 1;
            setcolor(FON);
            if (sw_tip == SW) {
                if (t1 == 6)   sd  = 0;
                if (t1 == 2)   sd  = 1;
                if (
                    ((t1 == 2) && (kr[1] < kr[3])) ||
                    ((t1 == 6) && (kr[1] > kr[3]))
                )              sdy = 1;
                else           sdy = -1;
            } else {
                if (sw_tip == SZ) {
                    if (kr[1] < kr[7])  {
                        t1 += 3; sdy = 1;
                    } else              {
                        sdy = -1;
                    }
                    if (kr[0] < kr[6])  {
                        sd = 1;
                    } else              {
                        sd = 0;
                    }
                }
            }
            if (Tip_Opis_PKS == 1) {
                bar(kr[t1*2] - shi*(1 - sd), pr1[1] - 1   , kr[t1*2] + shi*sd, pr1[3] + 1);
                setcolor(bord_act);
                line(kr[t1*2] - shi*(1 - sd) + 1*sd, kr[t1*2+1] + sdy*2, kr[t1*2] + shi*sd - 1*(1 - sd), kr[t1*2+1] + sdy*2);
                line(kr[t1*2] - shi*(1 - sd)     , pr1[1] , kr[t1*2] - shi*(1 - sd), pr1[3]);
                line(kr[t1*2] + shi*sd         , pr1[1] , kr[t1*2] + shi*sd    , pr1[3]);
            }
        }

        break;
    case 0:
//    default:

        setcolor(COLOR_B);
        setfillstyle(1, cvet);
        _bar3d_(pr1[0], pr1[1], pr1[2], pr1[3], 0, 0);
        _fillpoly_(sw_tip, kr, pr1[1], bShowIsNormalMnus, COLOR_B, cvet);

        break;
    }
/// -------------------------  ОТОБРАЖАЕМ минус СТРЕЛКИ---------------------
    setcolor(C_D);

    if (bShowIsNormalPlus) {
        int x1, x2;
        if (sd == 0) {
            x1 = kr[t1*2] - (shi * 2) * (1 - sd) + 1 * sd; x2 = kr[t1*2] - (shi * 3) * (1 - sd) + 1 * sd;
        } else {
            x1 = kr[t1*2] + (shi * 2) * sd - 1 * (1 - sd); x2 = kr[t1*2] + (shi * 3) * sd - 1 * (1 - sd);
        }

        line(x1, kr[t1*2+1] + sdy*2, x2, kr[t1*2+1] + sdy*2);
        line(x1, kr[t1*2+1] + sdy*2 + 1, x2, kr[t1*2+1] + sdy*2 + 1);
        line(x1, kr[t1*2+1] + sdy*2 - 1, x2, kr[t1*2+1] + sdy*2 - 1);
        /*
        int t1,t2;
        if(!((kr[1]!=pr1[1])&&
        (kr[1]!=(pr1[1]+sh_y)))){
        t1=2;
        }else{
        if(sw_tip==SW)t1=6;else t1=5;
        }
        int shi;
        shi=S2(Len)+1;
        if(sw_tip==SW){
          if(
            ((t1==2)&& (kr[1]<kr[3]))||
            ((t1==6)&&(kr[1]>kr[3]))
                  )              sdy = 1;
                  else           sdy =-1;
        }else{
              if(sw_tip==SZ){
                 if(kr[1]< kr[7])  { t1+=3;sdy=1;}
                 else              { sdy=-1;}
              }
        }
          setcolor(C_D);
          setfillstyle(1,LIN);
          fillellipse( kr[t1*2] , pr1[2-sdy]-sdy*sh_y/2,sh_y/2,sh_y/2);
          */
    }
/// -------------------------  ОТОБРАЖАЕМ ПЛЮС СТРЕЛКИ-  end-----------------




}

void  KY(int y1, int y, int x)
{
    y1 = y1 - sh_y / 2;
    y = y - sh_y / 2;
    kr[0]  = x;
    kr[2]  = x;
    kr[12] = x;
    kr[1] = y1;
    kr[3] = y1 - sh_y;
    kr[5] = y1 - sh_y;
    kr[7] = y + (y1 - y) / 2;
    kr[9] = y + (y1 - y) / 2;
    kr[11] = y1;
    kr[13] = y1;
}

void  krt(int x, int y, int len, int)/*-------*/
{

//   int sl =len;
//   int len2 = len + mas__;
//   int x3=x;
    int y1, x1;

    y = y - sh2 + sh_y;
    y1 = y + sh2;
    x1 = x;
    x = x + len;
    len_4 = len_4 + S3(len) / 2;

    kr[4] = x - len_4 + S5(len) / 2;
    kr[6] = x1 + len / 2 + S4(len) / 2;
    kr[8] = x1 + len / 2 - S4(len) / 2;
    kr[10] = x - len_4 - S5(len) / 2 + S3(len);
    KY(y1, y, x);
    if (mas__ > 0) {
        kr[0] += mas__;
        kr[2] += mas__;
    }
}

void  krb(int x, int y, int len, int)
{
    int y1, x1;
    y1 = y + sh_y;
    y = y + sh2 - sh_y;
    x1 = x;
    x = x + len;
    len_4 = len_4 + S3(len) / 2;

    kr[4] = x - len_4 - S5(len) / 2 + S3(len);
    kr[6] = x1 + len / 2 - S4(len) / 2;
    kr[8] = x1 + len / 2 + S4(len) / 2;
    kr[10] = x - len_4 + S5(len) / 2;
    KY(y1, y, x);
    if (mas__ > 0) {
        kr[0] += mas__;
        kr[2] += mas__;
    }

}
void  klt(int x, int y, int len, int)/*----------*/
{
    int y1;
    y = y - sh2 + sh_y;
    y1 = y + sh2;

    len_4 = len_4 + S3(len) / 2;

    kr[4] = x + len_4 - S5(len) / 2;
    kr[6] = x + len / 2 - S4(len) / 2;
    kr[8] = x + len / 2 + S4(len) / 2;
    kr[10] = x + len_4 + S5(len) / 2 - S3(len);
    KY(y1, y, x);
    //*******************
    if ((mas__ + len) < 0) {
        kr[0] += (mas__ + len);
        kr[2] += (mas__ + len);
    }

}
void  klb(int x, int y, int len, int)
{
    int y1;
    y1 = y + sh_y;
    y = y + sh2 - sh_y;

    len_4 = len_4 + S3(len) / 2;
    kr[4] = x + len_4 + S5(len) / 2 - S3(len);
    kr[6] = x + len / 2 + S4(len) / 2;
    kr[8] = x + len / 2 - S4(len) / 2;
    kr[10] = x + len_4 - S5(len) / 2;
    KY(y1, y, x);
    //*************
    if ((mas__ + len) < 0) {
        kr[0] += (mas__ + len);
        kr[2] += (mas__ + len);
    }

}

#define DD_  11
#define S_    2
#define Z_    2


int napr[22];



void  Str(int X, int Y, int c, int uc, int a1, int a2, int clr, int LUDOCHKA)
{
    int DD; // ПОЛУДЛИННА
    int S ; // ПОЛУТОЛЩИНА
    int Z ; // ВЫСОТА ЗУБЦА
    /*
    S= sh_y/2+1+1;
    Z= sh_y/2+1+1;
    */
//  20/03/2000 возвращяю на витебском ширину стрелок
// напрвления
// Интересно ? а зачем я их тоньше делал ?
//  Блин какой же толщины они были ?
    if (LUDOCHKA == 1) {
        S = sh_y / 2 + 1 - 1;
        Z = sh_y / 2 + 1 - 1;
    } else {
        S = sh_y / 2 + 1;
        Z = sh_y / 2 + 1;
    }
    DD = S * 3;
    int napr1[22] = {       X - DD,             Y - S,
                            X + DD,             Y - S,
                            X + DD,             Y - S - Z,
                            X + DD + DD,          Y,
                            X + DD,             Y + S + Z,
                            X + DD,             Y + S,
                            X - DD,             Y + S,
                            X - DD,             Y + S + Z,
                            X - DD - DD,          Y,
                            X - DD,             Y - S - Z,
                            X - DD,             Y - S
                    };
    int napr2[16] = {       X - DD,             Y - S,
                            X + DD,             Y - S,
                            X + DD,             Y - S - Z,
                            X + DD + DD,          Y,
                            X + DD,             Y + S + Z,
                            X + DD,             Y + S,
                            X - DD,             Y + S,
                            X - DD,             Y - S
                    };
    int napr3[16] = {       X + DD,             Y - S,
                            X - DD,             Y - S,
                            X - DD,             Y - S - Z,
                            X - DD - DD,          Y,
                            X - DD,             Y + S + Z,
                            X - DD,             Y + S,
                            X + DD,             Y + S,
                            X + DD,             Y - S
                    };
    /*int A1[10]={          X-1 ,             Y-S+1,
                          X-DD+1,           Y-S+1,
                          X-DD+1,           Y+S-1,
                          X-1 ,             Y+S-1,
                          X-1,              Y+S-1
    };*/
    int A1[10] = {          X + DD - 1 ,          Y - S + 1,
                            X - DD + 1,           Y - S + 1,
                            X - DD + 1,           Y + S - 1,
                            X + DD - 1 ,          Y + S - 1,
                            X + DD - 1,           Y + S - 1
                 };
    /*int A2[10]={          X   ,             Y-S+1  ,
                          X+DD-1  ,           Y-S+1  ,
                          X+DD-1  ,           Y+S-1  ,
                          X   ,             Y+S-1  ,
                          X  ,              Y+S-1
    };*/
    // реакция асн
    int afclr;
    if (clr == COLOR_B) afclr = KRA_SER; else if (clr == ZEL)     afclr = ZEL_SER; else
        afclr = KRA_BEL;
    if (a2 == 1) {
        setfillstyle(1, afclr);
    }

    // собственнно стрелка
    switch (c) {
    case 1: fillpoly(11, napr1); break;
    case 2: fillpoly(8, napr2); break;
    case 3: fillpoly(8, napr3); break;
    }

    if ((a2 == 1) && (a1 == 0)) {
        afclr = clr;
        setcolor(afclr); setfillstyle(1, afclr);
        fillpoly(5, A1);
    } else if (a1 == 1) {
        setcolor(afclr); setfillstyle(1, afclr);
        fillpoly(5, A1);
    }
    //if (a2==1){
    //   setcolor(afclr);setfillstyle(1,afclr);
    //   fillpoly(5,A2);
    //}
    // направление контура
    if (uc != 0) {
        setcolor(GELT);
        switch (uc) {
        case 3: drawpoly(11, napr1); break;
        case 2: drawpoly(7, napr2); break;
        case 1: drawpoly(7, napr3); break;
        }
        setcolor(C_D);
    }

}



