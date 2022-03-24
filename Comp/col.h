
#ifndef COL_H
#define COL_H

#include "ACom_T.h"

#define BL_CV 0


const int     C_D       =   0      ;
const int     BLUE_m    =   0      ;
const int     ZEL       =   2      ; //
const int     COLOR_SVZ =   2      ; //2 GREEN     ; ��������
//const int     BIRUZOVIJ  =  3      ; // FON  ;     /* ���� ����� */
const int     CYAN_m    =   3      ; // CYAN      ;
const int     TIME_FON  =   3      ; //
const int     COLOR_B   =   4      ; // RED       ;     /* ���� ����������� */
const int     KRA       =   4      ; //
const int     KRAYARK   =   5      ; //  ���������
const int     LIN_W     =   6      ; // BROWN     ;     /* ���� ����� */
const int     LIN       =   7      ; // LIN ;     /* ���� ����� */
const int     COLOR_F_PRG = 7      ; // LIN ;  StnL
const int     COLOR_F_P =   7      ; // LIN ;     /* ���� "��������" ��� ���� */
const int     FON       =   8      ; // FON  ;     /* ���� ����� */
const int     FON1      =   9      ; // FON  ;     /* ���� ����� */
const int     BLUE_mmm  =   9      ; // 9         ;
const int     SV_MIG    =   10     ; // WHT       ;   �/���
//const int     KRA_MIG =   10     ; //  �� ���!
const int     GELT      =   11     ; //   ������
const int     COLOR_PSV =   12     ; // WHT       ;   ��/���
const int     ZEL_MIG   =   13     ;
const int     BOLOT     =   14     ; //
const int     TXT       =   15     ; // TXT     ;
const int     GELT_SER  =   16     ; //; 16 ������/�����
const int     KRA_SER   =   17     ; //; 17 �������/�����
const int     BEL_SER   =   18     ; //; 18 �����/�����
const int     ZEL_SER   =   19     ; //; 19 ������/�����
const int     KRA_CHERN =   20     ; //; 20 �������/������
const int     KRA_BEL   =   21     ; //; 21 �������/�����
const int     KRA_ZEL   =   22     ; //; 22 �������/������
const int     KRA_GELT  =   23     ; //; 23 �������/������
const int     ZEL_LIN   =   24     ; //; ������/�� �����
const int     GELT_LIN  =   25     ; //; ������/�� �����
const int     CHERN_FON =  26     ; //; ���/������
const int     SER_CHERN =    27     ; //; �� �����/���

const int     COLOR_IR_F =  GELT_SER ; //   ���� �� �������� ��� ���������


extern int   COLOR_SET ; //   // ���� ��������� ��������
extern int   COLOR_S   ; //   ���� �������������� ��������
extern int   COLOR_IR_B; //   ���� �� �������� ��� �������
extern int   COLOR_IR_Z; //   ���� �� �������� ��� ���������

extern int   COLOR_GOR_A; //   ���� ��� ����� � ��������

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




