//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "APch.h"

#include "Y_STREL.h"
#include "str_fun.h"
#include "gorl.h"
#include "scrin.h"
#include "elem.h"
#include "f.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int PA(TPoint *P, ...);
int IA(int *P, ...);





void TY_Strel::ShowStrelNum(int x_n, int y_n, int itextfillclr, char * outname)
{

    int clr = itextfillclr;
    if (AO->bNumStrelColor) {
        int Pol = _is;
        if (InvertStrel) {
            if (_is == P) Pol = M;
            if (_is == M) Pol = P;
        }
        if (Pol == P) clr = COLOR_SVZ; else if (Pol == M) clr = GELT; else
            clr = COLOR_B;
    }

    setcolor(clr);


    if ((CurrentPicture == LT) && (AO->MaxX > 801)) _SetText(ARIAL12, x_n, y_n); else
        _SetText(F_LITT, x_n, y_n);
    if (NomerHeight == 1) {
        if (num_font_sz!=0) _SetTextSize(num_font_sz); else
                            _SetTextSize(-sh_y*2 + 2);
    }
    if  (((MUL_Y > AO->_NAZVA_) || (CurrentPicture == LT))) {
        if (outname == NULL) OutTextXY(TP.x, TP.y, GetName()); else
            OutTextXY(TP.x, TP.y, outname);
    }
    if (NomerHeight != 0) {
        _SetTextSize(1);
    }

}


TY_Strel::TY_Strel()
        : Strel0()
{
    memset(&YP, 0, sizeof(YP));
    memset(&T, 0, sizeof(T));
    memset(&Td, 0, sizeof(Td));
    memset(&prSTIK, 0, sizeof(prSTIK));
    XX = YY = DH = DX = 0;
    Prz[0] = 2;
    Prz[1] = 0;
    Prz[2] = 0;
    masx2 = 2;
    Prz[3] = 3;
    masy = 3;
    mas = 3;
    M0X = M0Y = M3X = M3Y = M1Y = 0;
    static_enabled=false;
    static_clB=TXT;static_clP[0]=C_D;static_clP[1]=C_D;
    static_shy[0]=8;static_shy[1]=8;
    static_is=W;
    num_font_sz=0;


}
static String _Y_Strel_PropName[] = {
    "цфCтык1",     // 11
    "цфCтык2",     // 12
    "цфCтык3",     // 13
    "M0X",      // 0
    "M0Y",     // 1
    "M3X",      // 2
    "M3Y",      // 3
    "M1Y",      // 3
    "static_enabled",
    "static_clB",
    "static_clP",
    "static_clPY",
    "static_shyS",
    "static_shyY",
    "static_is",
    "num_font_sz"
};
void TY_Strel::GetPropMap(TPropMap &m)
{
    Strel0::GetPropMap(m);
    int i = 0;
    m.put(_Y_Strel_PropName[i++], prSTIK[0], 0);
    m.put(_Y_Strel_PropName[i++], prSTIK[1], 0);
    m.put(_Y_Strel_PropName[i++], prSTIK[2], 0);
    m.put(_Y_Strel_PropName[i++], M0X);
    m.put(_Y_Strel_PropName[i++], M0Y);
    m.put(_Y_Strel_PropName[i++], M3X);
    m.put(_Y_Strel_PropName[i++], M3Y);
    m.put(_Y_Strel_PropName[i++], M1Y);

    m.put(_Y_Strel_PropName[i++], static_enabled,0);
    m.put(_Y_Strel_PropName[i++], static_clB);
    m.put(_Y_Strel_PropName[i++], static_clP[0]);
    m.put(_Y_Strel_PropName[i++], static_clP[1]);
    m.put(_Y_Strel_PropName[i++], static_shy[0]);
    m.put(_Y_Strel_PropName[i++], static_shy[1]);
    m.put(_Y_Strel_PropName[i++], static_is,0);
    m.put(_Y_Strel_PropName[i++], num_font_sz,0);
}
void TY_Strel::SetPropMap(TPropMap &m)
{
    Strel0::SetPropMap(m);
    int i = 0;
    prSTIK[0] = m.geti(_Y_Strel_PropName[i++]);
    prSTIK[1] = m.geti(_Y_Strel_PropName[i++]);
    prSTIK[2] = m.geti(_Y_Strel_PropName[i++]);
    M0X =    m.geti(_Y_Strel_PropName[i++]);
    M0Y =    m.geti(_Y_Strel_PropName[i++]);
    M3X =    m.geti(_Y_Strel_PropName[i++]);
    M3Y =    m.geti(_Y_Strel_PropName[i++]);
    M1Y =    m.geti(_Y_Strel_PropName[i++]);

    static_enabled=    m.geti(_Y_Strel_PropName[i++]);
    static_clB    =    m.geti(_Y_Strel_PropName[i++]);
    static_clP[0] =    m.geti(_Y_Strel_PropName[i++]);
    static_clP[1] =    m.geti(_Y_Strel_PropName[i++]);
    static_shy[0] =    m.geti(_Y_Strel_PropName[i++]);
    static_shy[1] =    m.geti(_Y_Strel_PropName[i++]);
    static_is     =    m.geti(_Y_Strel_PropName[i++]);
    num_font_sz     =  m.geti(_Y_Strel_PropName[i++]);
}



TPoint rPoint(double x, double y)
{
    TPoint P;
    P.x = x + 0.5;
    P.y = y + 0.5;
    return P;
}

// функция находит точку на векторе по смещению y
TFPoint Ph(TFPoint P1,TFPoint P2,double dh){
     TFPoint P;
     double ky=1;
     if (P2.y<P1.y) ky=-1;
     P.y=P1.y+dh*ky;
     if (P2.y==P1.y) {
        P.x=P1.x;
     }else{
        double kx=dh/fabs(P1.y-P2.y);
        P.x=P1.x+kx*(P2.x-P1.x);
     }
     return P;
}
void FlipPy(TPoint *P,int cnt,int Y,int dy=0)
{
     for (int i=0;i<cnt;i++){
         P[i].y=Y-(P[i].y-Y)+dy;
     }
}
void FlipPx(TPoint *P,int cnt,int X,int DX=0)
{
     for (int i=0;i<cnt;i++){
         P[i].x=X-(P[i].x-X)+DX;
     }
}

void  TY_Strel::CalcStrelY(/*,
                 //TPoint * M, // Точки полученые
                 TPoint * iT,
                 TPoint * iT_,
                 TPoint * iTd,
                 TPoint * iTd_,
                 TPoint &TP,
                 TPoint *TNPOL,
                 int &x_n,
                 int &y_n*/)
{

    int DX = abs(YP.M[3].x - YP.M[0].x);
    int DH = abs(YP.M[0].y - YP.M[3].y);
    int DH1 = abs(YP.M[0].y - YP.M[1].y);
    int L1=abs(YP.M[0].x - YP.M[1].x);
    int L2=abs(YP.M[0].x - YP.M[2].x);
    int L3=abs(YP.M[3].x - YP.M[4].x);
    int L3_=abs(YP.M[5].x - YP.M[6].x);
    TPoint M[7] ;
    // приводим к нормальному виду
    M[0]=YP.M[0];
    M[1]=Point(M[0].x-L1,M[0].y+DH1);
    M[2]=Point(M[0].x+L2,M[0].y);
    M[3]=Point(M[0].x+DX,M[0].y-DH);
    M[4]=Point(M[3].x+L3,M[3].y);
    M[5]=Point(M[0].x+DX,M[0].y+DH);
    M[6]=Point(M[3].x+L3_,M[5].y);


    int SH = YP.sh_y;
    double SH2=SH/ 2.;  // ширина пополам абс;
    int d_x = SH / 4+1;//*4/5; // щель
    int d_y = SH / 4+1;//*4/5; // щель
    int d_x_t = _strel_d_x_t;
    int d_y_t = _strel_d_y_t;//4;
    double B = DH;//+YP.M3Y;
    double A = DX;//+YP.M3X;
    double B1 = DH1;//+YP.M3Y;
    double A1 = M[1].x - M[0].x;//+YP.M3X;
    double SH_,  SH__1;
    double dx_stik[3];
    double dy_stik[3];
    double SH_2,SH_2_1;
    // подгоняем под стыки
    for (int i = 0; i < 3; i++) {
        dx_stik[i] = 3;
        dy_stik[i] = 3;
        if (YP.prSTIK[i] == 31) {
            dx_stik[i] = 1;
            dy_stik[i] = 1;
        }
    }

    // подгоняем под стыки
    if (CurrentPicture == BG) {
        for (int i = 0; i < 3; i++) dx_stik[i] = 0;
        for (int i = 0; i < 3; i++) dy_stik[i] = 0;
        //Td[5] = T[18]; Td[6] = T[19];
        //Td_[5] = T_[18]; Td_[6] = T_[19];
        //Td[8] = T[1]; Td[7] = T[8];
    }

    double dys = dy_stik[0];

    if (B == 0) {
        SH_2 = SH / 2;
    } else {
        double sinal = B / sqrt(A * A + B * B);
        SH_ = fabs(SH2*2 / sinal); // ширина наклонной по x
        SH_2 = SH_ / 2.;
    }
    if (B1 == 0) {
        SH_2_1 = SH / 2;
    } else {
        double sinal1 = B1 / sqrt(A1 * A1 + B1 * B1);
        SH__1 = fabs(SH2*2 / sinal1); // ширина наклонной по x
        SH_2_1 = SH__1 / 2.;
    }

    TFPoint fT[22];
    TFPoint fTd[22];
    TFPoint fT_[22];
    TFPoint fTd_[22];

    if (M[0].y!=M[1].y){
      fT[0]  .S(M[1].x - SH_2_1, M[1].y);
      fT[13] .S(M[1].x + SH_2_1, M[1].y);
    } else {
      fT[0]  .S(M[1].x, M[1].y - SH2);
      fT[13] .S(M[1].x, M[1].y + SH2);
    }

    fT[16] .S(M[0].x - SH_2, M[0].y);
    fT[17] .S(M[0].x + SH_2, M[0].y);
    fT[18] .S(M[3].x - SH_2, M[3].y);
    fT[19] .S(M[3].x + SH_2, M[3].y);

    fT[1] =Ph(fT[16],fT[18],+SH2);
    fT[8] =Ph(fT[17],fT[19],+SH2);
    fT[12]=Ph(fT[16],fT[18],-SH2);
    fT[11]=Ph(fT[17],fT[19],-SH2);

    fT[2] =Ph(fT[16],fT[18],+DH-SH2);
    fT[3] =Ph(fT[16],fT[18],+DH+SH2);
    fT[7] =Ph(fT[17],fT[19],+DH-SH2);
    fT[4] =Ph(fT[17],fT[19],+DH+SH2);

    fT[5] .S(M[4].x,    M[3].y - SH2);
    fT[6] .S(M[4].x,    M[3].y + SH2);

    fT[9] .S(M[2].x, M[0].y - SH2);
    fT[10].S(M[2].x, M[0].y + SH2);

    // 14 и 15 для съезда
    fT[14] .S((fT[1].x + fT[2].x) / 2, (fT[1].y + fT[2].y) / 2);
    fT[15] .S((fT[7].x + fT[8].x) / 2, (fT[7].y + fT[8].y) / 2);

    fTd[1] =Ph(fT[16],fT[18],+SH2 + d_y   );
    fTd[2] =Ph(fT[17],fT[19],+SH2 + d_y   );

    fTd[3] .S(fT[8].x + d_x, fT[8].y);
    fTd[4] .S(fT[11].x + d_x, fT[11].y);

    fTd[5] =Ph(fT[18],fT[16],dy_stik[2] );
    fTd[6] =Ph(fT[19],fT[17],dy_stik[2] );

    fTd[8] =Ph(fT[16],fT[18],+ dys   );
    fTd[7] =Ph(fT[17],fT[19],+ dys   );

    fT_[16].S(fT[16].x,fT[16].y);
    fT_[17].S(fT[17].x,fT[17].y);

    fT_[18] .S(M[5].x - SH_2, M[5].y);
    fT_[19] .S(M[5].x + SH_2, M[5].y);
    fT_[1] =Ph(fT[16],fT_[18],+SH2);
    fT_[8] =Ph(fT[17],fT_[19],+SH2);
    fT_[12]=Ph(fT[16],fT_[18],-SH2);
    fT_[11]=Ph(fT[17],fT_[19],-SH2);
    fT_[2] =Ph(fT[16],fT_[18],+DH-SH2);
    fT_[3] =Ph(fT[16],fT_[18],+DH+SH2);
    fT_[7] =Ph(fT[17],fT_[19],+DH-SH2);
    fT_[4] =Ph(fT[17],fT_[19],+DH+SH2);

    fT_[5] .S(M[6].x, M[6].y + SH2);
    fT_[6] .S(M[6].x, M[6].y - SH2);

    fTd_[1] =Ph(fT[16],fT_[18],+SH2 + d_y   );
    fTd_[2] =Ph(fT[17],fT_[19],+SH2 + d_y   );

    fTd_[3] .S(fT_[8].x  + d_x, fT_[8].y);
    fTd_[4] .S(fT_[11].x + d_x, fT_[11].y);

    fTd_[5] =Ph(fT_[18],fT[16],dy_stik[1] );
    fTd_[6] =Ph(fT_[19],fT[17],dy_stik[1] );

    fTd_[8] =Ph(fT[16],fT_[18],- dys   );
    fTd_[7] =Ph(fT[17],fT_[19],- dys   );


    TFPoint FTNPOL[12];

    FTNPOL[0].S(fTd[3].x   , fTd[3].y-1  );
    FTNPOL[1].S(fTd[3].x   , fTd[3].y-2);
    FTNPOL[2].S(fTd[3].x+SH, fTd[3].y-2);
    FTNPOL[3].S(fTd[3].x+SH, fTd[3].y-1  );

    int PolLen=SH;
    if (M[3].y>fTd[2].y-PolLen) PolLen=fTd[2].y-M[3].y;
    FTNPOL[4+0].S(fTd[2].x   , fTd[2].y  );
    FTNPOL[4+1]=Ph(fTd[2],fT[19],+PolLen);
    FTNPOL[4+2].S(FTNPOL[4+1].x+3,FTNPOL[4+1].y);
    FTNPOL[4+3].S(FTNPOL[4+0].x+3,FTNPOL[4+0].y);
    PolLen=SH;
    if (M[5].y<fTd_[2].y+PolLen) PolLen=M[5].y-fTd_[2].y;
    FTNPOL[8+0].S(fTd_[2].x   , fTd_[2].y  );
    FTNPOL[8+1]=Ph(fTd_[2],fT_[19],+PolLen);
    FTNPOL[8+2].S(FTNPOL[8+1].x+3,FTNPOL[8+1].y);
    FTNPOL[8+3].S(FTNPOL[8+0].x+3,FTNPOL[8+0].y);



    if (YP.prSTIK[0] >= 10) {
        if (M[0].y==M[1].y){
           fT[0].x += dx_stik[0];
           fT[13].x += dx_stik[0];
        } else{
           fT[0] =Ph(fT[0],fT[12],dy_stik[2]);
           fT[13] =Ph(fT[13],fT[11],dy_stik[2]);
        }
        if (M[1].x == M[0].x) {
            fT[16] = fTd[8]; fT[17] = fTd[7];
        }
    }
    if (YP.prSTIK[1] >= 10) {
        fT[9].x -= dx_stik[1];
        fT[10].x -= dx_stik[1];
        fT_[5].x -= dx_stik[1];
        fT_[6].x -= dx_stik[1];
        if (M[6].x == M[5].x) {
            fT_[18] = fTd_[5]; fT_[19] = fTd_[6];
        }
    }
    if (YP.prSTIK[2] >= 10) {
        fT[5].x -= dx_stik[2];
        fT[6].x -= dx_stik[2];
        fT[14].y -= dy_stik[2];
        fT[15].y -= dy_stik[2];
        if (M[3].x == M[4].x) {
            fT[18] = fTd[5]; fT[19] = fTd[6];
        }
    }

    // доп усекновения  L2
    if (M[2].x - M[0].x <= 0){
        fT[9] = fT[8]; fT[10] = fT[11];
    }

    if (M[4].x == M[3].x) { //L3==0
        fT[2] = fT[18]; fT[3] = fT[18] ; fT[4] = fT[18]; fT[5] = fT[18]; fT[6] = fT[19]; fT[7] = fT[19];
    }
    if (M[6].x == M[5].x) { //M2X==0
        fT_[3] = fT_[18]; fT_[4] = fT_[18]; fT_[5] = fT_[18]; fT_[6] = fT_[19];
    }
    if (M[1].x == M[0].x) {
        fT[0] = fT[16] ; fT[11] = fT[17] ; fT[12] = fT[17]; fT[13] = fT[17];
    }

    if ((CurrentPicture == LT) ) _SetText(ARIAL12, x_n, y_n); else
        _SetText(F_LITT, x_n, y_n);
    if (NomerHeight == 1) {
        if (num_font_sz!=0) _SetTextSize(num_font_sz); else
                            _SetTextSize(-sh_y*2 + 2);
    }
    int texth=textheight("88");
    if (NomerHeight != 0) _SetTextSize(1);

    TFPoint FPT;

    switch (YP.tpriz) {
    case  1: FPT=Ph(fT[8],fT[7],+texth + d_y_t   );FPT.x+=2;
        if (YP.M[3].x > YP.M[0].x )x_n = LEFT_TEXT; else x_n = RIGHT_TEXT;
        if (YP.M[3].y > YP.M[0].y )y_n = BOTTOM_TEXT; else y_n = TOP_TEXT;
        break;
    case  2:  FPT.x=fTd[4].x; FPT.y=fTd[4].y+d_y_t;
        if (YP.M[3].x > YP.M[0].x )x_n = LEFT_TEXT; else x_n = RIGHT_TEXT;
        if (YP.M[3].y < YP.M[0].y )y_n = TOP_TEXT; else y_n = BOTTOM_TEXT;
        break;
    case  3:  FPT.x=fT[12].x-d_x_t; FPT.y=fT[12].y+d_y_t;
        if (YP.M[3].x > YP.M[0].x )x_n = RIGHT_TEXT; else x_n = LEFT_TEXT;
        if (YP.M[3].y < YP.M[0].y )y_n = TOP_TEXT; else y_n = BOTTOM_TEXT;
        break;
    default: FPT.x=fT[1].x-d_x_t; FPT.y=fT[1].y-d_y_t;
        if (YP.M[3].x > YP.M[0].x )x_n = RIGHT_TEXT; else x_n = LEFT_TEXT;
        if (YP.M[3].y < YP.M[0].y )y_n = BOTTOM_TEXT; else y_n = TOP_TEXT;
        break;
    }
    TP.x=FPT.x;TP.y=FPT.y;

    // блокировка прямоугольник
    BL[0]=TPoint(M[0].x-SH*1.5,M[0].y-SH*1.5);
    BL[1]=TPoint(M[0].x+SH*1.5,M[0].y-SH*1.5);
    BL[2]=TPoint(M[0].x+SH*1.5,M[0].y+SH*1.5);
    BL[3]=TPoint(M[0].x-SH*1.5,M[0].y+SH*1.5);

    // заполняем массивы
    for (int i=0;i<22;i++){
        T[i]=fT[i].ToPoint();
        Td[i]=fTd[i].ToPoint();
        T_[i]=fT_[i].ToPoint();
        Td_[i]=fTd_[i].ToPoint();
    }
    for (int i=0;i<12;i++)
        TNPOL[i]=FTNPOL[i].ToPoint();
    // вертим
    if (YP.M[3].x < YP.M[0].x){
        FlipPx(T,22,          YP.M[0].x);
        FlipPx(Td,22,         YP.M[0].x);
        FlipPx(T_,22,         YP.M[0].x);
        FlipPx(Td_,22,        YP.M[0].x);
        FlipPx(&TP,1,          YP.M[0].x);
        FlipPx(TNPOL,12,       YP.M[0].x);
    }

    if (YP.M[3].y > YP.M[0].y) {
        int dy=0;
        if (SH2!=(int)SH2) dy=1;
        FlipPy(T,22,          YP.M[0].y,dy);
        FlipPy(Td,22,         YP.M[0].y,dy);
        FlipPy(T_,22,         YP.M[0].y,dy);
        FlipPy(Td_,22,        YP.M[0].y,dy);
        FlipPy(&TP,1,          YP.M[0].y,dy);
        FlipPy(TNPOL,12,       YP.M[0].y,dy);
    }

}


void TY_Strel::SetColors()
{
    // раставляем заполнение в зависимости от положения
    // всё сосчитанго до нас
    int fillclr = clr;
    clPP = cbord1; clPM = cbord2;
    clS1 = clS2 = clS3 = fillclr;
    switch (_is) {
    default: clBP=fillclr; clBM=fillclr; clS1 = (prSTIK[0] == 0) ? clBP : clPP;break;
    case  M: clBP=LIN; clBM=fillclr; clS1 = (prSTIK[0] == 0) ? clBM : clPP;break;
    case  P: clBM=LIN; clBP=fillclr; clS1 = (prSTIK[0] == 0) ? clBP : clPP;break;
    };
    if (fillclr == FON) {
        clBM = FON;
        clBP = FON;
    }
    clS2 = (prSTIK[1] == 0) ? clBP : clPP;
    clS3 = (prSTIK[2] == 0) ? clBM : clPM;

}

void TY_Strel::SetYPM()
{
       /* Приходится бороться с округлением int  */
    //if (sh_y / 2 + sh_y / 2 != sh_y) y++;

    XX = x;
    YY = y;
    int L1 = Prz[0] * MUL_X;
    L2 = masx2 * MUL_X;
    int L3 = Prz[3] * MUL_X;
    DH = masy * MUL_Y;
    DX = mas * MUL_X;
    tpriz = Prz[1];

    // подготавливаем данные для расчета стрелки
    // инициализируем вторые понятные для меня переменные



    YP.M[0] = Point(XX + M0X, YY);
    YP.M[1] = Point(YP.M[0].x - L1, YP.M[0].y+M1Y*MUL_Y);
    if (DH<0) YP.M[1] = Point(YP.M[0].x - L1, YP.M[0].y-M1Y*MUL_Y);
    YP.M[2] = Point(XX + L2,       YP.M[0].y);
    YP.M[3] = Point(XX + DX + M3X,       YY - DH);
    YP.M[4] = Point(YP.M[3].x + L3, YP.M[3].y);
    YP.M[5] = Point(XX + DX,       YY + DH);
    YP.M[6] = Point(YP.M[5].x + L2, YP.M[5].y);
    //YP.M0X=M0X*MUL_X;YP.M0Y=M0Y*MUL_Y;
    //YP.M3X=M3X*MUL_X;YP.M3Y=M3Y*MUL_Y;
    if (DX < 0) {
        YP.M[1] = Point(YP.M[0].x + L1, YP.M[0].y+M1Y*MUL_Y);
        if (DH<0) YP.M[1] = Point(YP.M[0].x + L1, YP.M[0].y-M1Y*MUL_Y);
        YP.M[2] = Point(XX - L2,       YP.M[0].y);
        YP.M[4] = Point(YP.M[3].x - L3, YP.M[3].y);
        YP.M[6] = Point(YP.M[5].x - L2, YP.M[5].y);
        //YP.M0X=-M0X*MUL_X;YP.M3X=-M3X*MUL_X;
    }
    YP.tpriz = tpriz;

    //YP.XX=XX;YP.YY=YY;YP.L1=L1;YP.L2=L2;YP.L3=L3;YP.L3_=L3_;YP.DH=DH;YP.DX=DX;

    YP.prSTIK[0] = prSTIK[0]; YP.prSTIK[1] = prSTIK[1]; YP.prSTIK[2] = prSTIK[2];

}



void  TY_Strel::Show()
{
     YP.CurrentPicture = CurrentPicture;
     YP.sh_y = sh_y; // Ширина в сечении

     SetYPM();
     if (static_enabled){
        YP.sh_y=static_shy[CurrentPicture];
        _is=static_is;
     }

     _1x = 1; _1y = 1;
    if (DH < 0) _1y = -1;
    if (DX < 0) _1x = -1;

    // Проверяем надо ли персчитывать точки
    if (memcmp(&lastYP, &YP, sizeof(YP)) != 0)
        CalcStrelY();
/*        ,
                   //M, // Точки полученые
                   T,
                   T_,
                   Td,
                   Td_,
                   TP,
                   TNPOL,
                   x_n,
                   y_n);*/

    memcpy(&lastYP, &YP, sizeof(YP));

    _is = is;
    _styll1 = styll1;
    _styll2 = styll2;
    _styll3 = styll3;

    if (InvertStrel) {

        if (_is == 1) _is = 2;
        else    if (_is == 2) _is = 1;
        int st = _styll1;
        _styll1 = _styll2;
        _styll2 = st;
    }



    // раставляем заполнение в зависимости от положения

    SetColors();
    if (static_enabled){
       _is=W;
       clr=static_clB;cbord1=static_clP[CurrentPicture];cbord2=static_clP[CurrentPicture];
       SetColors();
       _is=static_is;
     }
    // переделываем кму
    if (_styll2 == 7) {
        //textfillclr=COLOR_SVZ;   ???
        _styll1 = SOLID_FILL; _styll2 = SOLID_FILL;
    }

    /* затирем фоном на случай изм. положения */
    ShowFON();

    if (MOD == ED) {
        if ((M0Y != 0)) {
            setcolor(ZEL);
            fillellipse(YP.M[0].x + YP.M0X, YP.M[0].y - YP.M0Y, 2, 2);
        }
        if ((M3Y != 0)) {
            setcolor(ZEL);
            fillellipse(YP.M[3].x + YP.M3X, YP.M[3].y - YP.M3Y, 2, 2);
        }
    }
    ShowBLOCK();



}
void TY_Strel::ShowNormPol()
{
    setcolor(C_D);
    int clr1[4] = {   C_D, C_D, C_D, C_D};
    if (!InvertStrel){
       TPoint P1[4] = {TNPOL[8+0], TNPOL[8+1], TNPOL[8+2], TNPOL[8+3]};
       PolyColor(C_D, P1, clr1, 4);
    } else {
       TPoint P1[4] = {TNPOL[4+0], TNPOL[4+1], TNPOL[4+2], TNPOL[4+3]};
       PolyColor(C_D, P1, clr1, 4);
    }
}

void TY_Strel::ShowBLOCK()
{
     int clr1[4] = {   C_D, C_D, C_D, C_D};
     TPoint P1[4] = {BL[0], BL[1],BL[2], BL[3] };

     if (MOD==ED){
        if (impuls_block==1) PolyColor(FON, P1, clr1, 4);
     } else {
        if ((fimpuls_block==1)&&(CurrentPicture == LT)) PolyColor(KRA, P1, clr1, 4);
        if ((fimpuls_otkl_plus==1)||(fimpuls_otkl_minus==1)) PolyColor(BIRUZOVIJ, P1, clr1, 4);
     }
}

//   =======================================================================================

void TY_Strel_1::ShowFON()
{
    TPoint P3W[11] = {T[0], T[1], T[3], T[5], T[6], T[7], T[8], T[9], T[10],T[11], T[13]};
    if (L2 <= 0) {
        P3W[7] = T[8]; P3W[8] = T[11];
    }
    /* затирем фоном на случай изм. положения */
    {
        int clB = FON;
        int clr3[11] = {   clB, clB, clB, clB, clB, clB, clB, clB,  clB, clB,clB};
        if (L2 <= 0) clr3[7] = clPP;
        PolyColor(clB, P3W, clr3, 11);
    }
}

void  TY_Strel_1::Show()
{

    Strel0::Show1();
    TY_Strel::Show();


    TPoint P3W[11] = {T[0], T[1], T[3], T[5], T[6], T[7], T[8], T[9], T[10],T[11], T[13]};
    if (L2 <= 0) {
        P3W[7] = T[8]; P3W[8] = T[11];
    }

    /*  НЕТ СИГН */
    if (_is == D) {
        setfillstyle(_styll3, clBP);
        if (_styll1>1)setfillstyle(_styll1, clBP);
        if (_styll2>1)setfillstyle(_styll2, clBP);
        int clr1[4] = {clPP, clPP, clPP, clS1};
        if (YP.M[1].y==YP.M[0].y){
           TPoint P1[4] = {T[0], T[1], T[12], T[13]};
           PolyColor(clBP, P1, clr1, 4);
        }else {
           TPoint P1[4] = {T[0], T[12], T[11], T[13]};
           PolyColor(clBP, P1, clr1, 4);
        }

        TPoint P3[6] = {T[1], T[3], T[5], T[6], T[7], T[8]};
        int clr3[6] = {   clPP, clPP, clS3, clPP, clPP, clPP};
        TPoint P2[4] = {T[8], T[9], T[10], T[11]};
        int clr2[4] = {   clPP, clS2, clPP, clPP};

        setfillstyle(_styll3, clBP);if (_styll2>1) setfillstyle(_styll2, clBP);
        PolyColor(clBP, P3, clr3, 6);
        if (L2 > 0) {
          //if (styll1>1)    {
            setfillstyle(_styll3, clBP);if (_styll1>1) setfillstyle(_styll1, clBP);
            PolyColor(clBP, P2, clr2, 4);
          //}
        }

    }

    /*  неопр */
    if (_is == W) {
        int clr3[11] = {   clPP, clPP, clPP, clS3, clPP, clPP, clPP, clS2,  clPP, clPP, clS1};
        if (L2 <= 0)clr3[7] = clPP;
        setfillstyle(_styll3, clBP); PolyColor(clBP, P3W, clr3, 11);
    }
    /*  + */
    if (_is == P) {
        //TPoint PM[6] = {Td[1], T[3], T[5], T[6], T[7], Td[2]};
        //int clrM[6] = {    clPM, clPM, clS3, clPM, clPM, clPM};
        TPoint PM[7] = {Td[1], T[2],T[3], T[5], T[6], T[7], Td[2]};
        int clrM[7] = {    clPM, clPM,clPM, clS3, clPM, clPM, clPM};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, clrM, 7);

        TPoint PP[6] = {T[0], T[1], T[9], T[10], T[11], T[13]};
        int clrP[6] = {    clPP, clPP, clS2, clPP, clPP, clS1};
        if (L2 <= 0) {
            PP[1] = T[8]; PP[2] = T[11];
            clrP[1] = clPP;
        }
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, clrP, 6);
    }
    /*  - */
    if (_is == M) {
        TPoint PM[8] = {T[0], T[1], T[3], T[5], T[6], T[7], T[11], T[13]};
        int clrM[8] = {   clPM, clPM, clPM, clS3, clPM, clPM,  clPM, clS1};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, clrM, 8);

        if (L2 > 0) {
            TPoint PP[4] = {Td[3], T[9], T[10], Td[4]};
            int clrP[4] = {    clPP, clS2, clPP, clPP};
            setfillstyle(_styll1, clBP); PolyColor(clBP, PP, clrP, 4);
        }
    }

    /* Вывод номера  */
    ShowStrelNum(x_n, y_n, BLUE_m, NULL);

    ShowStik(YP.M[1].x, YP.M[1].y, prSTIK[0]);
    ShowStik(YP.M[4].x, YP.M[4].y, prSTIK[2]);
    ShowStik(YP.M[2].x, YP.M[2].y, prSTIK[1]);

    if ((bShowPol)&&(CurrentPicture == LT))  ShowNormPol();

    Strel0::Show2();
}

void TY_Strel_1::ShowNormPol()
{
    setcolor(C_D);
    int clr1[4] = {   C_D, C_D, C_D, C_D};
    if (!InvertStrel){
       TPoint P1[4] = {TNPOL[0+0], TNPOL[0+1], TNPOL[0+2], TNPOL[0+3]};
       PolyColor(C_D, P1, clr1, 4);
    } else {
       TPoint P1[4] = {TNPOL[4+0], TNPOL[4+1], TNPOL[4+2], TNPOL[4+3]};
       PolyColor(C_D, P1, clr1, 4);
    }
}

TYP  TY_Strel_1::GetType()
{
    return Y_STREL_1;
}

/*   ==============   Y_STREL_2      =========================*/

void TY_Strel_2::ShowFON()
{
     TPoint P3W[17] = {T[0], T[1], Td[1], T[3], T[5], T[6], T[7], Td[2], T[17], Td_[2], T_[7], T_[6], T_[5], T_[3], Td_[1], T_[1], T[13]};
    /* затирем фоном на случай изм. положения */
    {
        int clB = FON;
        int clr3[17] = {   clB, clB, clB, clB, clB, clB, clB, clB, clB, clB, clB,   clB,  clB,  clB , clB,  clB, clB};
        PolyColor(clB, P3W, clr3, 17);
    }
}


void  TY_Strel_2::Show()
{
    Strel0::Show1();
    TY_Strel::Show();


    TPoint P3W[17] = {T[0], T[1], Td[1], T[3], T[5], T[6], T[7], Td[2], T[17], Td_[2], T_[7], T_[6], T_[5], T_[3], Td_[1], T_[1], T[13]};

    int PW = 1;
    int textfillclr = BLUE_m;
    /* переделываем кму  */
    if (_styll2 == 7) {
        textfillclr = COLOR_SVZ;
        _styll2 = SOLID_FILL;
        _styll1 = SOLID_FILL;
    }

    /*  НЕТ СИГН */
    if (_is == D) {
        setfillstyle(_styll3, clBP);
        TPoint P1[5] = {T[0], T[1], T[16], T_[1], T[13]};
        int fillclr1[5] = {clPP, clPP, clPP, clPP, clS1};

        TPoint P3[6] = {T[1], T[3], T[5], T[6], T[7], T[8]};
        int fillclr3M[6] = {   clPP, clPP, clS3, clPP, clPP, clPP};
        int fillclr3P[6] = {   clPP, clPP, clS2, clPP, clPP, clPP};

        TPoint P3_[6] = {T_[1], T_[3], T_[5], T_[6], T_[7], T_[8]};

        PolyColor(clBP, P1, fillclr1, 5, PW);
        PolyColor(clBP, P3, fillclr3M, 6, PW);
        PolyColor(clBP, P3_, fillclr3P, 6, PW);
    }

    /*  неопр */
    if (_is == W) {
        setfillstyle(_styll3, clBP);
        int fillclr3[13] = {   clPP, clPP, clPP, clS3, clPP, clPP, clPP,   clPP,  clS2,  clPP , clPP,  clPP, clS1};

        PolyColor(clBP, P3W, fillclr3, 13, PW);
    }
    /*  + */
    if (_is == P) {
        TPoint PM[6] = {Td[1], T[3], T[5], T[6], T[7], Td[2]};
        int fillclrM[6] = {    clPM, clPM, clS3, clPM, clPM, clPM};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, fillclrM, 6, PW);

        TPoint PP[10] = {T[0], T_[11], Td_[2], T_[7], T_[6], T_[5], T_[3], Td_[1], T_[1], T[13]};
        int fillclrP[10] = {   clPP,   clPP,   clPP,  clPP,  clS2,  clPP,  clPP,   clPP,  clPP,  clS1};
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, fillclrP, 10, PW);
    }
    /*  - */
    if (_is == M) {
        TPoint PM[10] = {T[0], T[1], Td[1], T[3], T[5], T[6], T[7], Td[2], T[11], T[13]};
        int fillclrM[10] = {   clPM, clPM,  clPM, clPM, clS3, clPM, clPM,  clPM,  clPM, clS1};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, fillclrM, 10, PW);

        TPoint PP[6] = {Td_[1], T_[3], T_[5], T_[6], T_[7], Td_[2]};
        int fillclrP[6] = {    clPP, clPP, clS2, clPP, clPP, clPP};
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, fillclrP, 6, PW);



    }

    /* Вывод номера  */
    ShowStrelNum(x_n, y_n, textfillclr, NULL);



    Strel0::Show2();
}


TYP  TY_Strel_2::GetType()
{
    return Y_STREL_2;
}


void TY_Strel_3::ShowFON()
{
    TPoint P3W[8] = {T[0], T[1], Td[1], Td[2], T[8], T[9], T[10], T[13]};
    if (L2 <= 0) {
        P3W[5] = T[8]; P3W[6] = T[11];
    }
    /* затирем фоном на случай изм. положения */
    {
        int clB = FON;
        int clr3[8] = {   clB, clB, clB, clB, clB, clB, clB, clB};
        if (L2 <= 0) {
            P3W[5] = T[8]; P3W[6] = T[11];
            clr3[5] = clPP;
        }
        PolyColor(clB, P3W, clr3, 8);
    }
}

void TY_Strel_3::Show()   // СЪЕЗД обрезанный
{
    Strel0::Show1();
    TY_Strel::Show();


    TPoint P3W[8] = {T[0], T[1], Td[1], Td[2], T[8], T[9], T[10], T[13]};
    if (L2 <= 0) {
        P3W[5] = T[8]; P3W[6] = T[11];
    }

    /*  НЕТ СИГН */
    if (_is == D) {

        TPoint P1[4] = {T[0], T[1], T[12], T[13]};
        int clr1[4] = {clPP, clPP, clPP, clS1};
        TPoint P3[4] = {T[1], Td[1], Td[2], T[8]};
        int clr3[4] = {   clPP, clS3, clPP, clPP};
        TPoint P2[4] = {T[8], T[9], T[10], T[11]};
        int clr2[4] = {   clPP, clS2, clPP, clPP};
        setfillstyle(_styll3, clBP);
        PolyColor(clBP, P1, clr1, 4);
        PolyColor(clBP, P3, clr3, 4);
        if (L2 > 0)
            PolyColor(clBP, P2, clr2, 4);
    }

    /*  неопр */
    if (_is == W) {
        int clr3[8] = {   clPP, clPP, clS3, clPP, clPP, clS2, clPP, clS1};
        if (L2 <= 0) {
            P3W[5] = T[8]; P3W[6] = T[11];
            clr3[5] = clPP;
        }
        setfillstyle(_styll3, clBP); PolyColor(clBP, P3W, clr3, 8);
    }
    /*  + */
    if (_is == P) {
        // нету минуса то !
        //TPoint PM[2]={Td[1],Td[1]};
        //int clrM[2]={    clBP, clBP};
        //setfillstyle(_styll2,clBP);PolyColor(clBP,PM,clrM,2);

        TPoint PP[4] = {T[0], T[9], T[10], T[13]};
        int clrP[4] = {    clPP, clS2, clPP, clS1};
        if (L2 <= 0) {
            PP[1] = T[8]; PP[2] = T[11];
            clrP[1] = clPP;
        }
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, clrP, 4);
    }
    /*  - */
    if (_is == M) {
        TPoint PM[6] = {T[0], T[1], Td[1], Td[2], T[11], T[13]};
        int clrM[6] = {   clPM, clPM, clS3, clPM, clPM, clS1};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, clrM, 6);

        if (L2 > 0) {
            TPoint PP[4] = {Td[3], T[9], T[10], Td[4]};
            int clrP[4] = {    clPP, clS2, clPP, clPP};
            setfillstyle(_styll1, clBP); PolyColor(clBP, PP, clrP, 4);
        }
    }

    /* Вывод номера  */
    ShowStrelNum(x_n, y_n, BLUE_m, NULL);

    Strel0::Show2();

}

TYP  TY_Strel_3::GetType()
{
    return Y_STREL_3;
}

void TY_Strel_4::ShowFON(){}
void TY_Strel_4::Show() // огрызок к обрезанной
{
    Strel0::Show1();
    TY_Strel::Show();

    setfillstyle(_styll2, clBM);

    clS1 = clBM;
    clS2 = clBM;

    if ((Prz[0] == 1) || (Prz[0] == 3)) clS1 = clPP;
    if ((Prz[0] == 2) || (Prz[0] == 3)) clS2 = clPP;
    TPoint PM[4] = {Td[1], Td[2], Td[6], Td[5]};
    int clrM[4] = {   clS1, clPP, clS2 , clPP };
    //int clrM[4]={   clP, clP, clP, clP};
    PolyColor(clBM, PM, clrM, 4);

    Strel0::Show2();
}

TYP  TY_Strel_4::GetType()
{
    return Y_STREL_4;
}

// =======================================================
TY_Strel_5::TY_Strel_5()
        : TY_Strel()
{
    Prz[0] = 1;
    Prz[1] = 0;
    Prz[2] = 0;
    masx2 = 1;
    Prz[3] = 0;
}

void TY_Strel_5::SetColors()
{
    // глупо взял минусовое положение за основу
    int fillclr = clr;
    clPP = cbord1; clPM = cbord2;
    clS1 = clS2 = clS3 = fillclr;
    clBM=LIN; clBP=fillclr; clS1 = (prSTIK[0] == 0) ? clBP : clPP;
    if (fillclr == FON) {clBM = FON;clBP = FON;}
    clS3 = (prSTIK[2] == 0) ? clBP : clPP;

}

void  TY_Strel_5::ShowFON(){}
void  TY_Strel_5::Show() // Кривая
{
    Strel0::Show1();
    TY_Strel::Show();

    if (MOD == ED) {
        clPP = C_D;
        //if ((clr != COLOR_SET) && (bShowInSpyMarsh)) clr = COLOR_S;   else  clr = LIN;
        if (impuls_busi == 0)clr = FON;
        if (static_enabled){
           clr=static_clB;cbord1=static_clP[CurrentPicture];cbord2=static_clP[CurrentPicture];
        }

    }

    setfillstyle(_styll1, clr);
  /*  if (YP.M[3].y == YP.M[0].y) {
        TPoint P1[4] = {T[0], T[5], T[6], T[13]};
        int clr1[4] = {clPP, clS2, clPP, clS1};
        PolyColor(clr, P1, clr1, 4);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x == YP.M[3].x)) { //  /
        TPoint P1[4] = {T[16], T[18], T[19], T[17]};
        int clr1[4] = {     clPP,  clS3, clPP, clS1};
        PolyColor(clr, P1, clr1, 4);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { //  /-
        TPoint P1[6] = {T[16], T[3], T[5], T[6], T[7], T[17]};
        int clr1[6] = {     clPP, clPP, clS3, clPP, clPP, clS1};
        PolyColor(clr, P1, clr1, 6);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { // _/
        TPoint P1[6] = {T[0], T[1], T[18], T[19], T[11], T[13]};
        int clr1[6] = {    clPP, clPP,  clS3, clPP,  clPP, clS1};
        PolyColor(clr, P1, clr1, 6);
    } else {
        TPoint P1[10] = {T[0], T[1], T[2], T[3], T[5], T[6], T[7], T[8], T[11], T[13]};
        int clr1[10] = {   clPP, clPP, clPP, clPP, clS3, clPP, clPP, clPP, clPP, clS1};
        PolyColor(clr, P1, clr1, 10);
    }
*/

    if (YP.M[3].y == YP.M[0].y) {
        cntP1=PA(P1,&T[0], &T[5], &T[6], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clS3, &clPP, &clS1,NULL);

    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x == YP.M[3].x)) { //  /
        cntP1=PA(P1,&T[16], &T[18], &T[19], &T[17],NULL);
        cntP1=IA(clr1,&clPP,  &clS3, &clPP, &clS1,NULL);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { //  /-
        cntP1=PA(P1,&T[16], &T[3], &T[5], &T[6], &T[7], &T[17],NULL);
        cntP1=IA(clr1,&clPP, &clPP, &clS3, &clPP, &clPP, &clS1,NULL);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { // _/
        cntP1=PA(P1,&T[0], &T[1], &T[18], &T[19], &T[11], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clPP,  &clS3, &clPP,  &clPP, &clS1,NULL);
    } else {
        cntP1=PA(P1,&T[0], &T[1], &T[2], &T[3], &T[5], &T[6], &T[7], &T[8], &T[11], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clPP, &clPP, &clPP, &clS3, &clPP, &clPP, &clPP, &clPP, &clS1,NULL);
    }
    PolyColor(clr, P1, clr1, cntP1);


    ShowStik(YP.M[1].x, YP.M[1].y, prSTIK[0]);
    ShowStik(YP.M[4].x, YP.M[4].y, prSTIK[2]);

    Strel0::Show2();
}


TYP  TY_Strel_5::GetType(){return Y_STREL_5;}
TYP  TY_Strel_6::GetType(){return Y_STREL_6;}

void TY_Strel_6::SetYPM()
{
    TY_Strel_1::SetYPM();
    int L1 = Prz[0] * MUL_X/2;
    L2 = masx2 * MUL_X/2;
    int L3 = Prz[3] * MUL_X/2;
    DH = masy * MUL_Y/2;
    DX = mas * MUL_X/2;
    // подготавливаем данные для расчета стрелки
    // инициализируем вторые понятные для меня переменные
    YP.M[0] = Point(XX + M0X, YY);
    YP.M[1] = Point(YP.M[0].x - L1, YP.M[0].y+M1Y*MUL_Y/2);
    if (DH<0) YP.M[1] = Point(YP.M[0].x - L1, YP.M[0].y-M1Y*MUL_Y/2);
    YP.M[2] = Point(XX + L2,       YP.M[0].y);
    YP.M[3] = Point(XX + DX + M3X,       YY - DH);
    YP.M[4] = Point(YP.M[3].x + L3, YP.M[3].y);
    YP.M[5] = Point(XX + DX,       YY + DH);
    YP.M[6] = Point(YP.M[5].x + L2, YP.M[5].y);
    //YP.M0X=M0X*MUL_X;YP.M0Y=M0Y*MUL_Y;
    //YP.M3X=M3X*MUL_X;YP.M3Y=M3Y*MUL_Y;
    if (DX < 0) {
        YP.M[1] = Point(YP.M[0].x + L1, YP.M[0].y+M1Y*MUL_Y/2);
        if (DH<0) YP.M[1] = Point(YP.M[0].x + L1, YP.M[0].y-M1Y*MUL_Y/2);
        YP.M[2] = Point(XX - L2,       YP.M[0].y);
        YP.M[4] = Point(YP.M[3].x - L3, YP.M[3].y);
        YP.M[6] = Point(YP.M[5].x - L2, YP.M[5].y);
    }
}

void TY_Strel_6::ChangeMarkerXY(int iMarker,int aX,int aY)
{
     if (iMarker==1){
       Prz[0]=abs(YP.M[0].x-aX)/(MUL_X/2);
       M1Y=   (aY-YP.M[0].y)/(MUL_Y/2);
     }
     if (iMarker==2){
       masx2=abs(YP.M[0].x-aX)/(MUL_X/2);
     }
     if (iMarker==3){
       mas=(aX-YP.M[0].x)/(MUL_X/2);
       masy=   (YP.M[0].y-aY)/(MUL_Y/2);
     }
     if (iMarker==4){
       Prz[3]=abs(YP.M[3].x-aX)/(MUL_X/2);
     }

}
void TY_Strel_6::GetMarkerPoint(int iMarker,int &aX,int &aY)
{
    aX=YP.M[iMarker].x;aY=YP.M[iMarker].y;
}
