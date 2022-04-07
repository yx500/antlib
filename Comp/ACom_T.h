#ifndef ACom_TH
#define ACom_TH

#include "aheaders_h.h"

#define CN 6    //  ДЛИНА ИМЕНИ
#define Mx_Mn 1 //  МАКСИМАЛЬНОЕ КОЛИЧЕСТВО МОНИТОРОВ

#define c_DNC 2 //  ФЛАГ ДНЦ
#define c_DC 1  //  ФЛАГ ШЧД

#define ED 1 //  ФЛАГ РЕДАКТОРА
#define RD 2 //  ФЛАГ РИДЕРА
#define BG 1 //  ФЛАГ ОБШЕЙ КАРТИНКИ
#define LT 0 //  ФЛАГ КАРТИНКИ СТАНЦИИ

#define Units_Size 8 //  МАКСИМАЛЬНОЕ КОЛИЧЕСТВО UNIT

/*--------------------------------------------------------------------------
              ОПИСАНИЕ ОСНОВНЫХ ПЕРЕЧИСЛИМЫХ ТИПОВ ДАННЫХ
----------------------------------------------------------------------------*/

// ТИПЫ
enum UNIT
{
  GORE, // Горловины
  WAYS, // Пути - участки
  STRE, // Стрелки
  CEMA, // Светофоры
  LINE, // Блоки
  STAT, // Cтатика
  NITK, // Нитки
  CIFR, // Цифры
  XITR, // ХИТРЫЕ СТРЕЛКИ
  TRNN  // НОМЕР ПОЕЗДА Units_Size+1
};
//статус СТРЕЛКИ В ОПИСАТЕЛЕ МАРШРУТОВ
enum STATUS
{
  NET, /*не используется*/
  M,   /*мимо */
  P,   /*Прямо*/
  D,   /*не определенное пoложение */
  H,   /*прямо 2*/
  N,   /* отсутствует */
  C,   /* статика*/
  W
}; /* Мимо 2*/

// ТИПЫ КОМПОНЕНТ
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
              ОПИСАНИЕ СТРУКТУР В ФАЙЛЕ И В ОПЕРАТИИИВНОЙ ПАМЯТИ
----------------------------------------------------------------------------*/
#pragma pack(push, 1)

//  Структура элемента в файле                       sizeof

typedef struct
{
  unsigned MyStat2 : 1;
  unsigned MyStat22 : 1;
  unsigned MyStat3 : 3;
  unsigned MyStat4 : 2;
  unsigned __MyStat5 : 1;
} __tLStat;
/* Дополнительные признаки  */
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
  uint8 type;            //  тип элемента           --¬
  short int X_;          //  X координата             ¦
  short int Y_;          //  Y координата             ¦
  short int impuls_busi; //  сигнал занятия           ¦
  short int impuls_plus; //  сигнал плюс стрелки      ¦
  short int impuls_mnus; //  сигнал минус стрелки     +- 31 байт
  short int impuls_kzm;  //  сигнал замыкания         ¦
  uint8 mas;             //  масштаб                  ¦
  signed char Nomer;     //  номер стрелки            ¦
  char name[16];         //  имя элемента           ---
  char name16;           // cдвиг исторический
                         // ========== +++++++++++++++++++++  ==============

  char DMD[37]; // блок байтов для использвония комп-ми

  short int iMacro;
  // ========== +++++++++++++++++++++  ==============
  int8 GID;          //  ГИД                                ¦
  TExtPriz ExtPriz;  // Дополнительные признаки 04.04.2002 из GID
  signed char masy;  //  масштаб по у               (1)     ¦
  signed char masx2; //  масштаб х 2                (1) -----
  // ------------------------=-------------------------------------
  short int impuls_kmu; //  номер лампочки му
  short int impuls_mu;  //  номер лампочки му
};
#pragma pack(pop)

#endif
