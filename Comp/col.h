
#ifndef COL_H
#define COL_H

#include "ACom_T.h"

#define BL_CV 0


const     C_D       =   0      ;
const     BLUE_m    =   0      ;
const     ZEL       =   2      ; //
const     COLOR_SVZ =   2      ; //2 GREEN     ; ��������
//const     BIRUZOVIJ  =  3      ; // FON  ;     /* ���� ����� */
const     CYAN_m    =   3      ; // CYAN      ;
const     TIME_FON  =   3      ; //
const     COLOR_B   =   4      ; // RED       ;     /* ���� ����������� */
const     KRA       =   4      ; //
const     KRAYARK   =   5      ; //  ���������
const     LIN_W     =   6      ; // BROWN     ;     /* ���� ����� */
const     LIN       =   7      ; // LIN ;     /* ���� ����� */
const     COLOR_F_PRG = 7      ; // LIN ;  StnL
const     COLOR_F_P =   7      ; // LIN ;     /* ���� "��������" ��� ���� */
const     FON       =   8      ; // FON  ;     /* ���� ����� */
const     FON1      =   9      ; // FON  ;     /* ���� ����� */
const     BLUE_mmm  =   9      ; // 9         ;
const     SV_MIG    =   10     ; // WHT       ;   �/���
//const     KRA_MIG =   10     ; //  �� ���!
const     GELT      =   11     ; //   ������
const     COLOR_PSV =   12     ; // WHT       ;   ��/���
const     ZEL_MIG   =   13     ;
const     BOLOT     =   14     ; //
const     TXT       =   15     ; // TXT     ;
const     GELT_SER  =   16     ; //; 16 ������/�����
const     KRA_SER   =   17     ; //; 17 �������/�����
const     BEL_SER   =   18     ; //; 18 �����/�����
const     ZEL_SER   =   19     ; //; 19 ������/�����
const     KRA_CHERN =   20     ; //; 20 �������/������
const     KRA_BEL   =   21     ; //; 21 �������/�����
const     KRA_ZEL   =   22     ; //; 22 �������/������
const     KRA_GELT  =   23     ; //; 23 �������/������
const     ZEL_LIN   =   24     ; //; ������/�� �����
const     GELT_LIN  =   25     ; //; ������/�� �����
const     CHERN_FON =  26     ; //; ���/������
const     SER_CHERN =    27     ; //; �� �����/���

const     COLOR_IR_F =  GELT_SER ; //   ���� �� �������� ��� ���������


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

const  MaxLampType = 32;
bool _ALIB_ wc_LoadIniFile();
void _ALIB_ wc_SetColorByT_N(int T, int N);
int _ALIB_ wc_GetColor(int T, int N);
extern int KROSHBCOL[];
extern int KROSHPCOL[];


#endif




