
#ifndef COL_H
#define COL_H

#include "ACom_T.h"

#define BL_CV 0


const int     C_D       =   0      ;
const int     BLUE_m    =   0      ;
const int     ZEL       =   2      ; //
const int     COLOR_SVZ =   2      ; //2 GREEN     ; светофор
//const int     BIRUZOVIJ  =  3      ; // FON  ;     /* цвет фнона */
const int     CYAN_m    =   3      ; // CYAN      ;
const int     TIME_FON  =   3      ; //
const int     COLOR_B   =   4      ; // RED       ;     /* цвет занятятости */
const int     KRA       =   4      ; //
const int     KRAYARK   =   5      ; //  Яркокрасн
const int     LIN_W     =   6      ; // BROWN     ;     /* цвет линии */
const int     LIN       =   7      ; // LIN ;     /* цвет линии */
const int     COLOR_F_PRG = 7      ; // LIN ;  StnL
const int     COLOR_F_P =   7      ; // LIN ;     /* цвет "свободен" для пути */
const int     FON       =   8      ; // FON  ;     /* цвет фнона */
const int     FON1      =   9      ; // FON  ;     /* цвет фнона */
const int     BLUE_mmm  =   9      ; // 9         ;
const int     SV_MIG    =   10     ; // WHT       ;   Ч/Бел
//const int     KRA_MIG =   10     ; //  не исп!
const int     GELT      =   11     ; //   ЖЕЛТЫЙ
const int     COLOR_PSV =   12     ; // WHT       ;   КР/Бел
const int     ZEL_MIG   =   13     ;
const int     BOLOT     =   14     ; //
const int     TXT       =   15     ; // TXT     ;
const int     GELT_SER  =   16     ; //; 16 желтый/серый
const int     KRA_SER   =   17     ; //; 17 красный/серый
const int     BEL_SER   =   18     ; //; 18 белый/серый
const int     ZEL_SER   =   19     ; //; 19 зелёный/серый
const int     KRA_CHERN =   20     ; //; 20 красный/черный
const int     KRA_BEL   =   21     ; //; 21 красный/белый
const int     KRA_ZEL   =   22     ; //; 22 красный/зелёный
const int     KRA_GELT  =   23     ; //; 23 красный/желтый
const int     ZEL_LIN   =   24     ; //; зелёный/св серый
const int     GELT_LIN  =   25     ; //; желтый/св серый
const int     CHERN_FON =  26     ; //; ФОН/черный
const int     SER_CHERN =    27     ; //; св серый/ФОН

const int     COLOR_IR_F =  GELT_SER ; //   цвет ИР маршрута при свободном


extern int   COLOR_SET ; //   // цвет замыкания маршрута
extern int   COLOR_S   ; //   цвет установленного маршрута
extern int   COLOR_IR_B; //   цвет ИР маршрута при занятом
extern int   COLOR_IR_Z; //   цвет ИР маршрута при замкнутом

extern int   COLOR_GOR_A; //   цвет для горки в автомате

extern int   BIRUZOVIJ;

extern int ColorBash[16];
extern int ColorBash2[16];
extern int SvetStateColors100[8];
extern int SvetStateColors101[4];
extern int PerSvetColors[4];
extern int UKSPSColors[16][3];
extern int KMUSvetColors[4];
extern int DISKPenColors[16];
extern int DISKFillColors[16];
extern int SAUTPenColors[16];
extern int KGUPenColors[16];
extern int SvetStateColors000[8][2];
extern int SvetStateColors006[64][2];
extern int SvetStateColors007[64][2];
extern int SvetStateColors008[64][2];
extern int PerSvetStateColors[16][2];
extern int UTSStateColors[16][2];
extern int BASH15Colors[16][2];
extern int PerSvetStateColors3[8][2];
extern int TonnelStateColors[8][2];

void _ALIB_ SwapDACForPrinter();
void _ALIB_ RestoreDAC();

const  int MaxLampType = 32;
bool _ALIB_ wc_LoadIniFile();
void _ALIB_ wc_SetColorByT_N(int T, int N);
int _ALIB_ wc_GetColor(int T, int N);
extern int KROSHBCOL[];
extern int KROSHPCOL[];


#endif




