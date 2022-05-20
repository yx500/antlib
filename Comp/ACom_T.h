#ifndef ACom_TH
#define ACom_TH

#include "aheaders_h.h"

#define CN 6    //  ÄËÈÍÀ ÈÌÅÍÈ
#define Mx_Mn 1 //  ÌÀÊÑÈÌÀËÜÍÎÅ ÊÎËÈ×ÅÑÒÂÎ ÌÎÍÈÒÎÐÎÂ

#define c_DNC 2 //  ÔËÀÃ ÄÍÖ
#define c_DC 1  //  ÔËÀÃ Ø×Ä

#define ED 1 //  ÔËÀÃ ÐÅÄÀÊÒÎÐÀ
#define RD 2 //  ÔËÀÃ ÐÈÄÅÐÀ
#define BG 1 //  ÔËÀÃ ÎÁØÅÉ ÊÀÐÒÈÍÊÈ
#define LT 0 //  ÔËÀÃ ÊÀÐÒÈÍÊÈ ÑÒÀÍÖÈÈ

#define Units_Size 9 //  ÌÀÊÑÈÌÀËÜÍÎÅ ÊÎËÈ×ÅÑÒÂÎ UNIT

/*--------------------------------------------------------------------------
              ÎÏÈÑÀÍÈÅ ÎÑÍÎÂÍÛÕ ÏÅÐÅ×ÈÑËÈÌÛÕ ÒÈÏÎÂ ÄÀÍÍÛÕ
----------------------------------------------------------------------------*/

// ÒÈÏÛ
enum UNIT
{
  GORE, // Ãîðëîâèíû
  WAYS, // Ïóòè - ó÷àñòêè
  STRE, // Ñòðåëêè
  CEMA, // Ñâåòîôîðû
  LINE, // Áëîêè
  STAT, // Còàòèêà
  NITK, // Íèòêè
  CIFR, // Öèôðû
  XXX   // XITR, // ÕÈÒÐÛÅ ÑÒÐÅËÊÈ
};
//ñòàòóñ ÑÒÐÅËÊÈ Â ÎÏÈÑÀÒÅËÅ ÌÀÐØÐÓÒÎÂ
enum STATUS
{
  NET, /*íå èñïîëüçóåòñÿ*/
  M,   /*ìèìî */
  P,   /*Ïðÿìî*/
  D,   /*íå îïðåäåëåííîå ïoëîæåíèå */
  H,   /*ïðÿìî 2*/
  N,   /* îòñóòñòâóåò */
  C,   /* ñòàòèêà*/
  W
}; /* Ìèìî 2*/

// ÒÈÏÛ ÊÎÌÏÎÍÅÍÒ
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
              ÎÏÈÑÀÍÈÅ ÑÒÐÓÊÒÓÐ Â ÔÀÉËÅ È Â ÎÏÅÐÀÒÈÈÈÂÍÎÉ ÏÀÌßÒÈ
----------------------------------------------------------------------------*/
#pragma pack(push, 1)

//  Ñòðóêòóðà ýëåìåíòà â ôàéëå                       sizeof

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
/* Äîïîëíèòåëüíûå ïðèçíàêè  */
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
  uint8 type;            //  òèï ýëåìåíòà           --¬
  short int X_;          //  X êîîðäèíàòà             ¦
  short int Y_;          //  Y êîîðäèíàòà             ¦
  short int impuls_busi; //  ñèãíàë çàíÿòèÿ           ¦
  short int impuls_plus; //  ñèãíàë ïëþñ ñòðåëêè      ¦
  short int impuls_mnus; //  ñèãíàë ìèíóñ ñòðåëêè     +- 31 áàéò
  short int impuls_kzm;  //  ñèãíàë çàìûêàíèÿ         ¦
  uint8 mas;             //  ìàñøòàá                  ¦
  signed char Nomer;     //  íîìåð ñòðåëêè            ¦
  char name[16];         //  èìÿ ýëåìåíòà           ---
  char name16;           // cäâèã èñòîðè÷åñêèé
                         // ========== +++++++++++++++++++++  ==============

  char DMD[37]; // áëîê áàéòîâ äëÿ èñïîëüçâîíèÿ êîìï-ìè

  short int iMacro;
  // ========== +++++++++++++++++++++  ==============
  int8 GID;          //  ÃÈÄ                                ¦
  TExtPriz ExtPriz;  // Äîïîëíèòåëüíûå ïðèçíàêè 04.04.2002 èç GID
  signed char masy;  //  ìàñøòàá ïî ó               (1)     ¦
  signed char masx2; //  ìàñøòàá õ 2                (1) -----
  // ------------------------=-------------------------------------
  short int impuls_kmu; //  íîìåð ëàìïî÷êè ìó
  short int impuls_mu;  //  íîìåð ëàìïî÷êè ìó
};
#pragma pack(pop)

#endif
