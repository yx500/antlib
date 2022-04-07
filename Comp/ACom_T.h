#ifndef ACom_TH
#define ACom_TH

#include "aheaders_h.h"

#define CN 6    //  ����� �����
#define Mx_Mn 1 //  ������������ ���������� ���������

#define c_DNC 2 //  ���� ���
#define c_DC 1  //  ���� ���

#define ED 1 //  ���� ���������
#define RD 2 //  ���� ������
#define BG 1 //  ���� ����� ��������
#define LT 0 //  ���� �������� �������

#define Units_Size 8 //  ������������ ���������� UNIT

/*--------------------------------------------------------------------------
              �������� �������� ������������ ����� ������
----------------------------------------------------------------------------*/

// ����
enum UNIT
{
  GORE, // ���������
  WAYS, // ���� - �������
  STRE, // �������
  CEMA, // ���������
  LINE, // �����
  STAT, // C������
  NITK, // �����
  CIFR, // �����
  XITR, // ������ �������
  TRNN  // ����� ������ Units_Size+1
};
//������ ������� � ��������� ���������
enum STATUS
{
  NET, /*�� ������������*/
  M,   /*���� */
  P,   /*�����*/
  D,   /*�� ������������ �o������� */
  H,   /*����� 2*/
  N,   /* ����������� */
  C,   /* �������*/
  W
}; /* ���� 2*/

// ���� ���������
const int CompTypeCount = 86;
enum TYP
{
  NOTHING,
  WAY,
  PLOT,
  SIG_L,
  SIG_R,
  SWRT,
  SWLT,
  SWLB,
  SWRB,
  SWL,
  SWKT,
  SWKB,
  SWrt,
  SWlt,
  SWlb,
  SWrb,
  INFO,
  BLOK,
  FISH_L,
  FISH_R,
  FISH,
  NAME,
  GORL_L,
  GORL_R,
  MESS,
  SzT,
  SzB,
  GORL,
  NAPR,
  LAMP,
  ASN,
  KRIV,
  OVER,
  POIN,
  NOMER,
  TUPIC,
  BL_UH,
  LAM4,
  STIK,
  ELEKTR,
  PLATF,
  ENGL1,
  ENGL2,
  XBOST1,
  XBOST2,
  XBOST3,
  XBOST4,
  KUS1,
  KUS2,
  P_SVE,
  BASH,
  SWrtW,
  SWltW,
  SWlbW,
  SWrbW,
  SUPERLAMP1,
  SUPERLAMP2,
  Y_STREL_1,
  Y_STREL_2,
  Y_STREL_3,
  Y_STREL_4,
  LED,
  G_STREL_Y,
  G_RC,
  G_ZAMI,
  G_ZKR,
  G_STREL_1,
  G_ZAMP,
  G_OTCLABEL,
  G_TPLABEL,
  G_KZP,
  G_OSY,
  G_STREL_2,
  COMMLMP,
  DTGLMP,
  LOG_LAMP,
  VERSION,
  TRNUM,
  LINI2,
  SUBSTATION,
  LED30,
  E_OBJ,
  G_KZP2,
  Y_STREL_5,
  Y_STREL_6,
  G_RC_2

};

/*--------------------------------------------------------------------------
              �������� �������� � ����� � � ������������� ������
----------------------------------------------------------------------------*/
#pragma pack(push, 1)

//  ��������� �������� � �����                       sizeof

typedef struct
{
  unsigned MyStat2 : 1;
  unsigned MyStat22 : 1;
  unsigned MyStat3 : 3;
  unsigned MyStat4 : 2;
  unsigned __MyStat5 : 1;
} __tLStat;
/* �������������� ��������  */
struct TExtPriz
{
  unsigned NoShowYch : 1;
  unsigned NoShowStan : 1;
  unsigned MEM2 : 1;
  unsigned UseInRevizor : 1;
  unsigned UseInCommLmp : 1;
  unsigned NoShowYchAct : 1;
  unsigned NoShowExtInfo : 1;
  unsigned Zapas : 1;
};

struct AMemory
{
  uint8 type;            //  ��� ��������           --�
  short int X_;          //  X ����������             �
  short int Y_;          //  Y ����������             �
  short int impuls_busi; //  ������ �������           �
  short int impuls_plus; //  ������ ���� �������      �
  short int impuls_mnus; //  ������ ����� �������     +- 31 ����
  short int impuls_kzm;  //  ������ ���������         �
  uint8 mas;             //  �������                  �
  signed char Nomer;     //  ����� �������            �
  char name[16];         //  ��� ��������           ---
  char name16;           // c���� ������������
                         // ========== +++++++++++++++++++++  ==============

  char DMD[37]; // ���� ������ ��� ������������ ����-��

  short int iMacro;
  // ========== +++++++++++++++++++++  ==============
  int8 GID;          //  ���                                �
  TExtPriz ExtPriz;  // �������������� �������� 04.04.2002 �� GID
  signed char masy;  //  ������� �� �               (1)     �
  signed char masx2; //  ������� � 2                (1) -----
  // ------------------------=-------------------------------------
  short int impuls_kmu; //  ����� �������� ��
  short int impuls_mu;  //  ����� �������� ��
};
#pragma pack(pop)

#endif
