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

#define Units_Size 9 //  ������������ ���������� UNIT

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
  XXX   // XITR, // ������ �������
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

struct __tLStat
{
  uint8 P;
  int isMyStat2(){     return (P>>0) & 0x01;}
  int isMyStat22() {   return (P>>1) & 0x01;}
  int isMyStat3() {    return (P>>2) & 0x07;}//0b00000111 ;}   // : 3;
  int isMyStat4() {    return (P>>5) & 0x03;}//0b00000011;}   //  : 2;
  int is__MyStat5() {  return (P>>7) & 0x01;}
  void setMyStat2(int v){     if (v) P|=  ( 1 << 0 ); else P&= ~( 1 << 0 );}
  void setMyStat22(int v){    if (v) P|=  ( 1 << 1 ); else P&= ~( 1 << 1 );}
  void setMyStat3(int v) {    P&= 0xE3/*0b11100011*/;    P|=  ( v << 2 ); }
  void setMyStat4(int v) {    P&= 0x9F/*0b10011111*/;    P|=  ( v << 5 ); }
  void set__MyStat5(int v) {  if (v) P|=  ( 1 << 7 ); else P&= ~( 1 << 7 );}
};
/* �������������� ��������  */
struct TExtPriz
{
  uint8 P;
  bool isNoShowYch(){     return (P>>0) & 0x01;}
  bool isNoShowStan(){    return (P>>1) & 0x01;}
  bool isMEM2(){          return (P>>2) & 0x01;}
  bool isUseInRevizor(){  return (P>>3) & 0x01;}
  bool isUseInCommLmp(){  return (P>>4) & 0x01;}
  bool isNoShowYchAct(){  return (P>>5) & 0x01;}
  bool isNoShowExtInfo(){ return (P>>6) & 0x01;}
  bool isZapas(){         return (P>>7) & 0x01;}
  void setNoShowYch(bool v){     if (v) P|=  ( 1 << 0 ); else P&= ~( 1 << 0 );}
  void setNoShowStan(bool v){    if (v) P|=  ( 1 << 1 ); else P&= ~( 1 << 1 );}
  void setMEM2(bool v){          if (v) P|=  ( 1 << 2 ); else P&= ~( 1 << 2 );}
  void setUseInRevizor(bool v){  if (v) P|=  ( 1 << 3 ); else P&= ~( 1 << 3 );}
  void setUseInCommLmp(bool v){  if (v) P|=  ( 1 << 4 ); else P&= ~( 1 << 4 );}
  void setNoShowYchAct(bool v){  if (v) P|=  ( 1 << 5 ); else P&= ~( 1 << 5 );}
  void setNoShowExtInfo(bool v){ if (v) P|=  ( 1 << 6 ); else P&= ~( 1 << 6 );}
  void setZapas(bool v){         if (v) P|=  ( 1 << 7 ); else P&= ~( 1 << 7 );}
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
