#include "col.h"

#include "aheaders_cpp.h"
#include "ainifile.h"
#include "winpalet.h"

int COLOR_S = LIN;        //   11 :-)))WHT       ;     /* цвет сбоя      */
int COLOR_SET = GELT;     // 2 GREEN     ;     /* цвет установленного маршрута */
int COLOR_IR_Z = ZEL_LIN; //   цвет ИР маршрута при замкнутом
int COLOR_IR_B = KRA_ZEL; //   цвет ИР маршрута при занятом
int COLOR_GOR_A = 223;
int BIRUZOVIJ = 3;

int ColorBash[16] = {
    //             B     +       -       KZM
    FON,       //        0    0 0   0   0
    GELT,      //        1    0 0   0   1
    KRA,       //        2    0 0   1   0
    ZEL,       //        3    0 0   1   1
    GELT,      //        4    0 1   0   0
    GELT,      //        5    0 1   0   1
    FON,       //        6    0 1   1   0
    FON,       //        7    0 1   1   1
    COLOR_PSV, //        8    1 0   0   0
    KRA,       //        9    1 0   0   1
    KRA,       //        10   1 0   1   0
    KRA,       //        11   1 0   1   1
    KRA,       //        12   1 1   0   0
    KRA,       //        13   1 1   0   1
    KRA,       //        14   1 1   1   0
    KRA,       //        15   1 1   1   1
};

int ColorBash2[16] = {
    //             B     +       -       KZM
    FON,       //        0    0 0   0   0
    GELT,      //        1    0 0   0   1
    COLOR_PSV, //        2    0 0   1   0
    ZEL,       //        3    0 0   1   1
    GELT,      //        4    0 1   0   0
    GELT,      //        5    0 1   0   1
    FON,       //        6    0 1   1   0
    FON,       //        7    0 1   1   1
    COLOR_PSV, //        8    1 0   0   0
    KRA,       //        9    1 0   0   1
    KRA,       //        10   1 0   1   0
    KRA,       //        11   1 0   1   1
    KRA,       //        12   1 1   0   0
    KRA,       //        13   1 1   0   1
    KRA,       //        14   1 1   1   0
    KRA,       //        15   1 1   1   1
};

/* 20/10/2003   */
int SvetStateColors000[8][2] = {
    //              зел неиспр.  АCН
    //              BUSY    PLUS     MINUS
    {FON, C_D},       // 0    0   0    0          ФОН / ЧЁРНЫЙ
    {FON, ZEL},       // 1    0   0    1          ФОН / ЗЕЛЁНЫЙ
    {COLOR_PSV, C_D}, // 2    0   1    0          КР.МИГ / ЧЁРНЫЙ
    {COLOR_PSV, ZEL}, // 3    0   1    1              КР.МИГ / ЗЕЛЁНЫЙ
    {COLOR_SVZ, C_D}, // 4    1   0    0          ЗЕЛЁНЫЙ / ЧЁРНЫЙ
    {COLOR_SVZ, ZEL}, // 5    1   0    1          ЗЕЛЁНЫЙ / ЗЕЛЁНЫЙ
    {ZEL_MIG, C_D},   // 6   1   1    0          ЗЕЛЁНЫЙ-МИГ / ЧЁРНЫЙ
    {ZEL_MIG, ZEL},   // 7  1   1    1          ЗЕЛЁНЫЙ-МИГ / ЗЕЛ
};

/* 12/02/2002   */
int SvetStateColors100[8] = {
    //              зел белый   красныё
    //              BUSY    KZM KMU
    FON,       //        0 0   0   0    ФОН
    KRA,       //        1 0   0   1    КРАCНЫЙ
    TXT,       //        2 0   1   0    БЕЛЫЙ
    SV_MIG,    //     3 1   1   0    БЕЛЫЙ - МИГАЮЩИЙ
    COLOR_SVZ, //   4 1   0   0    ЗЕЛЁНЫЙ
    COLOR_SVZ, //   5     1   0   1    ЗЕЛЁНЫЙ
    COLOR_SVZ, //   6     1   1   0    ЗЕЛЁНЫЙ
    COLOR_SVZ, //   7     1   1   1    ЗЕЛЁНЫЙ
};

/* 12/02/2002   */
int SvetStateColors101[4] = {
    //              белыйМ  белый
    //              KZM    BUSY
    FON,    //        0     0   0           ФОН
    TXT,    //        1     0   1           БЕЛЫЙ
    SV_MIG, //     2     1   0           БЕЛЫЙ - МИГАЮЩИЙ
    C_D     //         3     1   1

};

/* 21/10/2003   */
int SvetStateColors006[64][2] = {
    //                                  mu  kmu kzm      Minus  Plus    busi
    //                                НеиспрКО  Закр  НеиспрCО   АД    Неиспр Открыт    Цвет       Рамка
    {FON, C_D},             //  1   , 0        ,0       ,0    ,0 ,0  ,0  ,фон         ,черн
    {COLOR_SVZ, C_D},       //  2   , 0        ,0       ,0    ,0 ,0  ,1  ,зеленый     ,черн
    {COLOR_PSV, C_D},       //  3   , 0        ,0       ,0    ,0 ,1  ,0  ,кр-миг      ,черн
    {ZEL_MIG, C_D},         //  4   , 0        ,0       ,0    ,0 ,1  ,1  ,зел-миг     ,черн
    {FON, COLOR_SVZ},       //  5   , 0        ,0       ,0    ,1 ,0  ,0  ,фон         ,зелен
    {COLOR_SVZ, COLOR_SVZ}, //  6   , 0        ,0       ,0    ,1 ,0  ,1  ,зеленый     ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  7   , 0        ,0       ,0    ,1 ,1  ,0  ,кр-миг      ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  8   , 0        ,0       ,0    ,1 ,1  ,1  ,зел-миг     ,зелен
    {FON, C_D},             //  9   , 0        ,0       ,1    ,0 ,0  ,0  ,фон         ,черн
    {ZEL_MIG, C_D},         //  10  , 0        ,0       ,1    ,0 ,0  ,1  ,зеленый-миг ,черн
    {COLOR_PSV, C_D},       //  11  , 0        ,0       ,1    ,0 ,1  ,0  ,кр-миг      ,черн
    {ZEL_MIG, C_D},         //  12  , 0        ,0       ,1    ,0 ,1  ,1  ,зел-миг     ,черн
    {FON, COLOR_SVZ},       //  13  , 0        ,0       ,1    ,1 ,0  ,0  ,фон         ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  14  , 0        ,0       ,1    ,1 ,0  ,1  ,зеленый-миг ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  15  , 0        ,0       ,1    ,1 ,1  ,0  ,кр-миг      ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  16  , 0        ,0       ,1    ,1 ,1  ,1  ,зел-миг     ,зелен
    {KRA, C_D},             //  17  , 0        ,1       ,0    ,0 ,0  ,0  ,красный     ,черн
    {COLOR_PSV, C_D},       //  18  , 0        ,1       ,0    ,0 ,0  ,1  ,красн-миг   ,черн
    {COLOR_PSV, C_D},       //  19  , 0        ,1       ,0    ,0 ,1  ,0  ,красн-миг   ,черн
    {COLOR_PSV, C_D},       //  20  , 0        ,1       ,0    ,0 ,1  ,1  ,красн-миг   ,черн
    {KRA, COLOR_SVZ},       //  21  , 0        ,1       ,0    ,1 ,0  ,0  ,красный     ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  22  , 0        ,1       ,0    ,1 ,0  ,1  ,красн-миг   ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  23  , 0        ,1       ,0    ,1 ,1  ,0  ,красн-миг   ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  24  , 0        ,1       ,0    ,1 ,1  ,1  ,красн-миг   ,зелен
    {KRA, C_D},             //  25  , 0        ,1       ,1    ,0 ,0  ,0  ,красный     ,черн
    {COLOR_PSV, C_D},       //  26  , 0        ,1       ,1    ,0 ,0  ,1  ,красн-миг   ,черн
    {COLOR_PSV, C_D},       //  27  , 0        ,1       ,1    ,0 ,1  ,0  ,красн-миг   ,черн
    {COLOR_PSV, C_D},       //  28  , 0        ,1       ,1    ,0 ,1  ,1  ,красн-миг   ,черн
    {KRA, COLOR_SVZ},       //  29  , 0        ,1       ,1    ,1 ,0  ,0  ,красный     ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  30  , 0        ,1       ,1    ,1 ,0  ,1  ,красн-миг   ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  31  , 0        ,1       ,1    ,1 ,1  ,0  ,красн-миг   ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  32  , 0        ,1       ,1    ,1 ,1  ,1  ,красн-миг   ,зелен
    {COLOR_PSV, C_D},       //  33  , 1        ,0       ,0    ,0 ,0  ,0  ,красн-миг   ,черн
    {ZEL_MIG, C_D},         //  34  , 1        ,0       ,0    ,0 ,0  ,1  ,зеленый-миг ,черн
    {COLOR_PSV, C_D},       //  35  , 1        ,0       ,0    ,0 ,1  ,0  ,кр-миг      ,черн
    {ZEL_MIG, C_D},         //  36  , 1        ,0       ,0    ,0 ,1  ,1  ,зел-миг     ,черн
    {COLOR_PSV, COLOR_SVZ}, //  37  , 1        ,0       ,0    ,1 ,0  ,0  ,красн-миг   ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  38  , 1        ,0       ,0    ,1 ,0  ,1  ,зеленый-миг ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  39  , 1        ,0       ,0    ,1 ,1  ,0  ,кр-миг      ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  40  , 1        ,0       ,0    ,1 ,1  ,1  ,зел-миг     ,зелен
    {COLOR_PSV, C_D},       //  41  , 1        ,0       ,1    ,0 ,0  ,0  ,кр-миг      ,черн
    {ZEL_MIG, C_D},         //  42  , 1        ,0       ,1    ,0 ,0  ,1  ,зел-миг     ,черн
    {COLOR_PSV, C_D},       //  43  , 1        ,0       ,1    ,0 ,1  ,0  ,кр-миг      ,черн
    {ZEL_MIG, C_D},         //  44  , 1        ,0       ,1    ,0 ,1  ,1  ,зел-миг     ,черн
    {COLOR_PSV, COLOR_SVZ}, //  45  , 1        ,0       ,1    ,1 ,0  ,0  ,кр-миг      ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  46  , 1        ,0       ,1    ,1 ,0  ,1  ,зел-миг     ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  47  , 1        ,0       ,1    ,1 ,1  ,0  ,кр-миг      ,зелен
    {ZEL_MIG, COLOR_SVZ},   //  48  , 1        ,0       ,1    ,1 ,1  ,1  ,зел-миг     ,зелен
    {COLOR_PSV, C_D},       //  49  , 1        ,1       ,0    ,0 ,0  ,0  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  50  , 1        ,1       ,0    ,0 ,0  ,1  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  51  , 1        ,1       ,0    ,0 ,1  ,0  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  52  , 1        ,1       ,0    ,0 ,1  ,1  ,кр-миг      ,черн
    {COLOR_PSV, COLOR_SVZ}, //  53  , 1        ,1       ,0    ,1 ,0  ,0  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  54  , 1        ,1       ,0    ,1 ,0  ,1  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  55  , 1        ,1       ,0    ,1 ,1  ,0  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  56  , 1        ,1       ,0    ,1 ,1  ,1  ,кр-миг      ,зелен
    {COLOR_PSV, C_D},       //  57  , 1        ,1       ,1    ,0 ,0  ,0  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  58  , 1        ,1       ,1    ,0 ,0  ,1  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  59  , 1        ,1       ,1    ,0 ,1  ,0  ,кр-миг      ,черн
    {COLOR_PSV, C_D},       //  60  , 1        ,1       ,1    ,0 ,1  ,1  ,кр-миг      ,черн
    {COLOR_PSV, COLOR_SVZ}, //  61  , 1        ,1       ,1    ,1 ,0  ,0  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  62  , 1        ,1       ,1    ,1 ,0  ,1  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}, //  63  , 1        ,1       ,1    ,1 ,1  ,0  ,кр-миг      ,зелен
    {COLOR_PSV, COLOR_SVZ}  //  64  , 1        ,1       ,1    ,1 ,1  ,1  ,кр-миг      ,зелен
};

/* 15/07/2002   */
int PerSvetColors[4] = {
    //              BUSY    KZM
    FON,       //        0 0   0           ФОН
    FON,       //        1 0   1           ФОН
    COLOR_SVZ, //    2 1   0           ЗЕЛЁНЫЙ
    KRA        //           3    1   1               КРАCНЫЙ
};
/* 21/06/2002   */
int UKSPSColors[16][3] = {
    //
    //                                 BUSY  +   -   KZM
    {COLOR_F_P, FON, 0},       //     0  0   0   0   0    CВ.CЕРЫЙ       ФОН
    {COLOR_F_P, GELT, 1},      //     1  0   0   0   1    CВ.CЕРЫЙ   ЖЕЛТЫЙ
    {C_D, FON, 0},             //     2  0   0   1   0        ЧЕРНЫЙ         ФОН
    {C_D, GELT, 1},            //     3  0   0   1   1    ЧЕРНЫЙ         ЖЕЛТЫЙ
    {COLOR_F_P, FON, 0},       //     4  0   1   0   0        CВ.CЕРЫЙ       ФОН
    {COLOR_F_P, GELT, 1},      //     5  0   1   0   1    CВ.CЕРЫЙ   ЖЕЛТЫЙ
    {C_D, FON, 0},             //     6  0   1   1   0        ЧЕРНЫЙ         ФОН
    {C_D, GELT, 1},            //     7  0   1   1   1    ЧЕРНЫЙ         ЖЕЛТЫЙ
    {COLOR_F_P, COLOR_PSV, 1}, //     8  1   0   0   0    CВ.CЕРЫЙ   КР.МИГ
    {COLOR_F_P, COLOR_B, 1},   //     9  1   0   0   1    CВ.CЕРЫЙ   КРАCНЫЙ
    {C_D, COLOR_PSV, 1},       //     10 1   0   1   0    ЧЕРНЫЙ         КР.МИГ
    {C_D, COLOR_B, 1},         //     11 1   0   1   1    ЧЕРНЫЙ         КРАCНЫЙ
    {COLOR_F_P, COLOR_PSV, 1}, //     12 1   1   0   0    CВ.CЕРЫЙ   КР.МИГ
    {COLOR_F_P, COLOR_B, 1},   //     13 1   1   0   1    CВ.CЕРЫЙ   КРАCНЫЙ
    {C_D, COLOR_PSV, 1},       //     14 1   1   1   0    ЧЕРНЫЙ         КР.МИГ
    {C_D, COLOR_B, 1}          //     15 1   1   1   1    ЧЕРНЫЙ         КРАCНЫЙ
};

int SAUTPenColors[16] = {
    //              BUSY    +   -   KZM
    COLOR_F_P, //        0 0   0   0   0       БЕЛЫЙ
    COLOR_F_P, //        1 0   0   0   1       БЕЛЫЙ
    C_D,       //        2 0   0   1   0               ЧЕРНЫЙ
    C_D,       //        3 0   0   1   1       ЧЕРНЫЙ
    COLOR_F_P, //        4 0   1   0   0               БЕЛЫЙ
    COLOR_F_P, //        5 0   1   0   1       БЕЛЫЙ
    C_D,       //        6 0   1   1   0               ЧЕРНЫЙ
    C_D,       //        7 0   1   1   1       ЧЕРНЫЙ
    COLOR_PSV, //        8 1   0   0   0       КР.МИГ
    COLOR_PSV, //        9 1   0   0   1       КР.МИГ
    KRA,       //        10    1   0   1   0       КРАCНЫЙ
    KRA,       //        11    1   0   1   1       КРАCНЫЙ
    COLOR_PSV, //        12    1   1   0   0       КР.МИГ
    COLOR_PSV, //        13    1   1   0   1       КР.МИГ
    KRA,       //        14    1   1   1   0       КРАCНЫЙ
    KRA        //        15    1   1   1   1       КРАCНЫЙ
};
int KGUPenColors[16] = {
    //              BUSY    +   -   KZM
    C_D,       //        0 0   0   0   0       ЧЕРНЫЙ
    C_D,       //        1 0   0   0   1       ЧЕРНЫЙ
    C_D,       //        2 0   0   1   0               ЧЕРНЫЙ
    C_D,       //        3 0   0   1   1       ЧЕРНЫЙ
    C_D,       //        4 0   1   0   0               ЧЕРНЫЙ
    C_D,       //        5 0   1   0   1       ЧЕРНЫЙ
    C_D,       //        6 0   1   1   0               ЧЕРНЫЙ
    C_D,       //        7 0   1   1   1       ЧЕРНЫЙ
    COLOR_PSV, //        8 1   0   0   0       КР.МИГ
    COLOR_PSV, //        9 1   0   0   1       КР.МИГ
    KRA,       //        10    1   0   1   0       КРАCНЫЙ
    KRA,       //        11    1   0   1   1       КРАCНЫЙ
    COLOR_PSV, //        12    1   1   0   0       КР.МИГ
    COLOR_PSV, //        13    1   1   0   1       КР.МИГ
    KRA,       //        14    1   1   1   0       КРАCНЫЙ
    KRA        //        15    1   1   1   1       КРАCНЫЙ
};

int KMUSvetColors[4] = {
    //              BUSY    +
    FON, //        0 0   0    ФОН
    TXT, //        1 0   1    БЫЛЫЙ
    KRA, //        2 1   0    КРАCНЫЙ
    GELT //        3 1   1    ЖЕЛТЫЙ
};

int DISKPenColors[16] = {
    //              BUSY    +   -   KZM
    C_D,       //        0 0   0   0   0       ЧЕРНЫЙ
    C_D,       //        1 0   0   0   1       ЧЕРНЫЙ
    C_D,       //        2 0   0   1   0               ЧЕРНЫЙ
    C_D,       //        3 0   0   1   1       ЧЕРНЫЙ
    COLOR_F_P, //        4 0   1   0   0               БЕЛЫЙ
    COLOR_F_P, //        5 0   1   0   1       БЕЛЫЙ
    COLOR_F_P, //        6 0   1   1   0               БЕЛЫЙ
    COLOR_F_P, //        7 0   1   1   1       БЕЛЫЙ
    C_D,       //        8 1   0   0   0       ЧЕРНЫЙ
    C_D,       //        9 1   0   0   1       ЧЕРНЫЙ
    C_D,       //        10    1   0   1   0       ЧЕРНЫЙ
    C_D,       //        11    1   0   1   1       ЧЕРНЫЙ
    COLOR_F_P, //        12    1   1   0   0       БЕЛЫЙ
    COLOR_F_P, //        13    1   1   0   1       БЕЛЫЙ
    COLOR_F_P, //        14    1   1   1   0       БЕЛЫЙ
    COLOR_F_P  //        15    1   1   1   1       БЕЛЫЙ
};
int DISKFillColors[16] = {
    //              BUSY    +   -   KZM
    FON,       //        0 0   0   0   0       ФОН
    FON,       //        1 0   0   0   1       ФОН
    FON,       //        2 0   0   1   0               ФОН
    FON,       //        3 0   0   1   1       ФОН
    FON,       //        4 0   1   0   0               ФОН
    FON,       //        5 0   1   0   1       ФОН
    FON,       //        6 0   1   1   0               ФОН
    FON,       //        7 0   1   1   1       ФОН
    COLOR_PSV, //        8 1   0   0   0       КР.МИГ
    COLOR_PSV, //        9 1   0   0   1       КР.МИГ
    KRA,       //        10    1   0   1   0       КРАCНЫЙ
    KRA,       //        11    1   0   1   1       КРАCНЫЙ
    COLOR_PSV, //        12    1   1   0   0       КР.МИГ
    COLOR_PSV, //        13    1   1   0   1       КР.МИГ
    KRA,       //        14    1   1   1   0       КРАCНЫЙ
    KRA        //        15    1   1   1   1       КРАCНЫЙ
};

TDAC O15;
TDAC O8;
void SwapDACForPrinter()
{
  O15 = DAC[15];
  DAC[15].pe[0].peRed = 0;
  DAC[15].pe[0].peGreen = 0;
  DAC[15].pe[0].peBlue = 0;
  O8 = DAC[8];
  DAC[8].pe[0].peRed = 63;
  DAC[8].pe[0].peGreen = 63;
  DAC[8].pe[0].peBlue = 63;
  Update_DAC();
}

void RestoreDAC()
{
  DAC[15] = O15;
  DAC[8] = O8;
  Update_DAC();
}

static int32 SPPLC[MaxLampType][16] = {
    {FON1, FON1, FON1, FON1, FON1, FON1, FON1, FON1, KRA, KRA, KRA, KRA, KRA, KRA, KRA, KRA},
    {8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2},
    {8, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11},

    {8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2},

    {8, 8, 8, 8, 8, 8, 8, 8, 2, 4, 4, 4, 4, 4, 2, 2}};

int KROSHBCOL[16] = {
    0,   //        0  Black            черный
    236, //        1  Blue             синий
    221, //        2  Green            зеленый
    170, //        3  Cyan             голубой
    207, //        4  Red              красный
    149, //        5  Magenta          фиолетовый
    152, //        6  Brown            коричневый
    247, //        7  LightGray        светло-серый
    17,  //        8  DarkGray         темно-серый
    233, //        9  LightBlue        ярко-синий
    219, //        10  LightGreen       ярко-зеленый
    136, //        11  LightCyan        ярко-голубой
    205, //        12  LightRed         ярко-красный
    155, //        13  LightMagenta     ярко-фиолетовый
    251, //        14  Yellow           желтый
    246  //        15  White            белый
};
int KROSHPCOL[16] = {
    246, //        0  Black            черный
    246, //        1  Blue             синий
    246, //        2  Green            зеленый
    0,   //        3  Cyan             голубой
    246, //        4  Red              красный
    246, //        5  Magenta          фиолетовый
    246, //        6  Brown            коричневый
    0,   //        7  LightGray        светло-серый
    0,   //        8  DarkGray         темно-серый
    246, //        9  LightBlue        ярко-синий
    0,   //        10  LightGreen       ярко-зеленый
    0,   //        11  LightCyan        ярко-голубой
    0,   //        12  LightRed         ярко-красный
    0,   //        13  LightMagenta     ярко-фиолетовый
    0,   //        14  Yellow           желтый
    0    //        15  White            белый
};

void _SetCol(int T, int N, String S)
{
  if (S.Pos("x") > 0)
    SPPLC[T][N] = -S.ToIntDef(0);
  else
    SPPLC[T][N] = S.ToIntDef(0);
}

bool wc_LoadIniFile()
{
  static bool wc_loaded = false;
  try {
    if (wc_loaded)
      return true;
    String FN = String(DACCfgFileName);
    FN = ChangeFileExt(FN, ".ini");
    if (!FileExists(FN))
      return false;
    AIniFile* FI = new AIniFile(FN);
    String ST, S, Sect;
    char s[10];
    for (int i = 0; i < MaxLampType; i++) {
      Sect = "TYPE_" + IntToStr(i);
      if (!FI->SectionExists(Sect))
        continue;
      for (int j = 0; j < 16; j++) {
        itoa(j, s, 2);
        ST = String(s);
        while (ST.Length() < 4)
          ST = "0" + ST;
        S = FI->ReadString(Sect, ST, "0000");
        _SetCol(i, j, S);
      }
    }

    // загружаем цвета Кроша
    if (FI->SectionExists("KROSH_COLOR")) {
      for (int i = 0; i < 15; i++) {
        KROSHBCOL[i] = FI->ReadInteger("KROSH_COLOR", "B" + IntToStr(i), KROSHBCOL[i]);
        KROSHPCOL[i] = FI->ReadInteger("KROSH_COLOR", "T" + IntToStr(i), KROSHPCOL[i]);
      }
    }

    delete FI;
  } catch (...) {
    return false;
  }
  wc_loaded = true;
  return true;
}

void wc_SetColorByT_N(int T, int N)
{
  /*   TCanvas* dc=BgiCanvas();
     if (dc==NULL) return;

     if (SPPLC[T][N]>0)
          setcolor(SPPLC[T][N]);
     else {
          TColor clr=(TColor)(-SPPLC[T][N]);
          ::SetTextColor(dc->Handle, clr );
          dc->Pen->Color = clr;
     }
    */
}

int wc_GetColor(int T, int N)
{
  return SPPLC[T][N];
}

/* 20/04/2007   */
int SvetStateColors007[64][2] = {
    //Цвт зплн  Цвт рамки   N   Mu  Km  Kz  Mn  Pl  Bu
    //                    признак закрыт  Приглас.  Авто    Неиспра Сигнал
    //                            действие  вность  открыт
    {
        FON,
        C_D,
    }, // 0,0,0,0,0,0,0
    {
        COLOR_SVZ,
        C_D,
    }, // 1,0,0,0,0,0,1
    {
        FON,
        KRA,
    }, // 2,0,0,0,0,1,0
    {
        COLOR_SVZ,
        KRA,
    }, // 3,0,0,0,0,1,1
    {
        FON,
        COLOR_SVZ,
    }, // 4,0,0,0,1,0,0
    {
        COLOR_SVZ,
        COLOR_SVZ,
    }, // 5,0,0,0,1,0,1
    {
        FON,
        KRA_ZEL,
    }, // 6,0,0,0,1,1,0
    {
        COLOR_SVZ,
        KRA_ZEL,
    }, // 7,0,0,0,1,1,1
    {
        BEL_SER,
        C_D,
    }, // 8,0,0,1,0,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 9,0,0,1,0,0,1
    {
        BEL_SER,
        KRA_CHERN,
    }, // 10,0,0,1,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 11,0,0,1,0,1,1
    {
        BEL_SER,
        CHERN_FON,
    }, // 12,0,0,1,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 13,0,0,1,1,0,1
    {
        BEL_SER,
        CHERN_FON,
    }, // 14,0,0,1,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 15,0,0,1,1,1,1
    {
        KRA,
        C_D,
    }, // 16,0,1,0,0,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 17,0,1,0,0,0,1
    {
        KRA,
        KRA,
    }, // 18,0,1,0,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 19,0,1,0,0,1,1
    {
        KRA,
        COLOR_SVZ,
    }, // 20,0,1,0,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 21,0,1,0,1,0,1
    {
        KRA,
        KRA_ZEL,
    }, // 22,0,1,0,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 23,0,1,0,1,1,1
    {
        BEL_SER,
        KRA,
    }, // 24,0,1,1,0,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 25,0,1,1,0,0,1
    {
        BEL_SER,
        KRA_CHERN,
    }, // 26,0,1,1,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 27,0,1,1,0,1,1
    {
        FON,
        CHERN_FON,
    }, // 28,0,1,1,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 29,0,1,1,1,0,1
    {
        FON,
        CHERN_FON,
    }, // 30,0,1,1,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 31,0,1,1,1,1,1
    {
        FON,
        KRA,
    }, // 32,1,0,0,0,0,0
    {
        COLOR_SVZ,
        KRA_CHERN,
    }, // 33,1,0,0,0,0,1
    {
        FON,
        KRA,
    }, // 34,1,0,0,0,1,0
    {
        COLOR_SVZ,
        KRA_CHERN,
    }, // 35,1,0,0,0,1,1
    {
        FON,
        KRA_ZEL,
    }, // 36,1,0,0,1,0,0
    {
        COLOR_SVZ,
        KRA_ZEL,
    }, // 37,1,0,0,1,0,1
    {
        FON,
        KRA_ZEL,
    }, // 38,1,0,0,1,1,0
    {
        COLOR_SVZ,
        KRA_ZEL,
    }, // 39,1,0,0,1,1,1
    {
        BEL_SER,
        KRA,
    }, // 40,1,0,1,0,0,0
    {
        COLOR_SVZ,
        KRA_CHERN,
    }, // 41,1,0,1,0,0,1
    {
        BEL_SER,
        KRA_CHERN,
    }, // 42,1,0,1,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 43,1,0,1,0,1,1
    {
        KRA,
        CHERN_FON,
    }, // 44,1,0,1,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 45,1,0,1,1,0,1
    {
        BEL_SER,
        CHERN_FON,
    }, // 46,1,0,1,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 47,1,0,1,1,1,1
    {
        KRA,
        KRA_CHERN,
    }, // 48,1,1,0,0,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 49,1,1,0,0,0,1
    {
        KRA_SER,
        C_D,
    }, // 50,1,1,0,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 51,1,1,0,0,1,1
    {
        KRA,
        KRA_ZEL,
    }, // 52,1,1,0,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 53,1,1,0,1,0,1
    {
        KRA,
        KRA_ZEL,
    }, // 54,1,1,0,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 55,1,1,0,1,1,1
    {
        BEL_SER,
        KRA,
    }, // 56,1,1,1,0,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 57,1,1,1,0,0,1
    {
        BEL_SER,
        KRA_CHERN,
    }, // 58,1,1,1,0,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 59,1,1,1,0,1,1
    {
        BEL_SER,
        CHERN_FON,
    }, // 60,1,1,1,1,0,0
    {
        COLOR_SVZ,
        CHERN_FON,
    }, // 61,1,1,1,1,0,1
    {
        BEL_SER,
        CHERN_FON,
    }, // 62,1,1,1,1,1,0
    {
        COLOR_SVZ,
        CHERN_FON,
    } // 63,1,1,1,1,1,1
};
int SvetStateColors008[64][2] = {
    //Цвет заполн   Цвет рамки          N   Mu  Kmu Kz  Mn  Pl  Bu
    // FON   серый       Несоответствие                  признак маневр  Авто    Пригл   Сигнал
    //                                              действие        открыт
    {FON, C_D},             //    0,  0,  0,  0,  0,  0,  0
    {COLOR_SVZ, C_D},       //    1,  0,  0,  0,  0,  0,  1
    {BEL_SER, C_D},         //    2,  0,  0,  0,  0,  1,  0
    {BEL_SER, C_D},         //    3,  0,  0,  0,  0,  1,  1
    {FON, COLOR_SVZ},       //    4,  0,  0,  0,  1,  0,  0
    {COLOR_SVZ, COLOR_SVZ}, //    5,  0,  0,  0,  1,  0,  1
    {BEL_SER, CHERN_FON},   //    6,  0,  0,  0,  1,  1,  0
    {BEL_SER, CHERN_FON},   //    7,  0,  0,  0,  1,  1,  1
    {TXT, C_D},             //    8,  0,  0,  1,  0,  0,  0
    {COLOR_SVZ, CHERN_FON}, //    9,  0,  0,  1,  0,  0,  1
    {BEL_SER, CHERN_FON},   //    10, 0,  0,  1,  0,  1,  0
    {BEL_SER, CHERN_FON},   //    11, 0,  0,  1,  0,  1,  1
    {TXT, CHERN_FON},       //    12, 0,  0,  1,  1,  0,  0
    {COLOR_SVZ, ZEL_SER},   //    13, 0,  0,  1,  1,  0,  1
    {BEL_SER, CHERN_FON},   //    14, 0,  0,  1,  1,  1,  0
    {BEL_SER, CHERN_FON},   //    15, 0,  0,  1,  1,  1,  1
    {FON, KRA},             //    16, 0,  1,  0,  0,  0,  0
    {COLOR_SVZ, KRA},       //    17, 0,  1,  0,  0,  0,  1
    {BEL_SER, KRA},         //    18, 0,  1,  0,  0,  1,  0
    {BEL_SER, KRA},         //    19, 0,  1,  0,  0,  1,  1
    {FON, KRA_ZEL},         //    20, 0,  1,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL},   //    21, 0,  1,  0,  1,  0,  1
    {BEL_SER, KRA_SER},     //    22, 0,  1,  0,  1,  1,  0
    {BEL_SER, KRA_SER},     //    23, 0,  1,  0,  1,  1,  1
    {TXT, KRA},             //    24, 0,  1,  1,  0,  0,  0
    {COLOR_SVZ, KRA},       //    25, 0,  1,  1,  0,  0,  1
    {BEL_SER, KRA},         //    26, 0,  1,  1,  0,  1,  0
    {BEL_SER, KRA},         //    27, 0,  1,  1,  0,  1,  1
    {FON, KRA_ZEL},         //    28, 0,  1,  1,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL},   //    29, 0,  1,  1,  1,  0,  1
    {BEL_SER, KRA_SER},     //    30, 0,  1,  1,  1,  1,  0
    {BEL_SER, KRA_SER},     //    31, 0,  1,  1,  1,  1,  1
    {FON, CHERN_FON},       //    32, 1,  0,  0,  0,  0,  0
    {COLOR_SVZ, KRA_CHERN}, //    33, 1,  0,  0,  0,  0,  1
    {BEL_SER, KRA},         //    34, 1,  0,  0,  0,  1,  0
    {BEL_SER, KRA},         //    35, 1,  0,  0,  0,  1,  1
    {FON, KRA_ZEL},         //    36, 1,  0,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL},   //    37, 1,  0,  0,  1,  0,  1
    {BEL_SER, KRA_SER},     //    38, 1,  0,  0,  1,  1,  0
    {BEL_SER, KRA_SER},     //    39, 1,  0,  0,  1,  1,  1
    {TXT, C_D},             //    40, 1,  0,  1,  0,  0,  0
    {COLOR_SVZ, KRA_CHERN}, //    41, 1,  0,  1,  0,  0,  1
    {BEL_SER, KRA},         //    42, 1,  0,  1,  0,  1,  0
    {BEL_SER, KRA},         //    43, 1,  0,  1,  0,  1,  1
    {TXT, CHERN_FON},       //    44, 1,  0,  1,  1,  0,  0
    {COLOR_SVZ, KRA_SER},   //    45, 1,  0,  1,  1,  0,  1
    {TXT, KRA_SER},         //    46, 1,  0,  1,  1,  1,  0
    {BEL_SER, KRA_SER},     //    47, 1,  0,  1,  1,  1,  1
    {FON, KRA},             //    48, 1,  1,  0,  0,  0,  0
    {COLOR_SVZ, KRA},       //    49, 1,  1,  0,  0,  0,  1
    {BEL_SER, KRA},         //    50, 1,  1,  0,  0,  1,  0
    {BEL_SER, KRA},         //    51, 1,  1,  0,  0,  1,  1
    {FON, KRA_ZEL},         //    52, 1,  1,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL},   //    53, 1,  1,  0,  1,  0,  1
    {BEL_SER, KRA_ZEL},     //    54, 1,  1,  0,  1,  1,  0
    {BEL_SER, KRA_ZEL},     //    55, 1,  1,  0,  1,  1,  1
    {FON, KRA},             //    56, 1,  1,  1,  0,  0,  0
    {COLOR_SVZ, KRA},       //    57, 1,  1,  1,  0,  0,  1
    {BEL_SER, KRA},         //    58, 1,  1,  1,  0,  1,  0
    {BEL_SER, KRA},         //    59, 1,  1,  1,  0,  1,  1
    {FON, KRA_ZEL},         //    60, 1,  1,  1,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL},   //    61, 1,  1,  1,  1,  0,  1
    {BEL_SER, KRA_SER},     //    62, 1,  1,  1,  1,  1,  0
    {BEL_SER, KRA_SER}      // 63, 1,  1,  1,  1,  1,  1
};

int PerSvetStateColors[16][2] = {
    //                            N    Kzm Mn  Pl  Bu  Цвет заполн  Цвет рамки
    //                            открытое извещение неиспр Закрытое
    {FON, C_D},          // 0     0   0   0   0               ФОН ЧЁРНЫЙ
    {KRA, C_D},          // 1     0   0   0   1               Т.красный   ЧЁРНЫЙ
    {FON, KRA},          // 2     0   0   1   0               ФОН Т.красный
    {KRA, KRA},          // 3     0   0   1   1               Т.красный   Т.красный
    {KRA_SER, C_D},      // 4     0   1   0   0               Т.красный/фон(миг)  ЧЁРНЫЙ
    {KRAYARK, C_D},      // 5     0   1   0   1               Ярко-красный    ЧЁРНЫЙ
    {KRA_SER, KRA},      // 6     0   1   1   0               Т.красный/фон(миг)  Т.красный
    {KRAYARK, KRA},      // 7     0   1   1   1               Ярко-красный    Т.красный
    {FON, TXT},          // 8     1   0   0   0               ФОН БЕЛЫЙ
    {KRA, SER_CHERN},    // 9     1   0   0   1               Т.красный   ЧЁРНЫЙ/т,т.сер
    {FON, KRA_BEL},      // 10    1   0   1   0               ФОН Т.крас/белый
    {KRA, KRA_BEL},      // 11    1   0   1   1               Т.красный   бел/красный
    {KRA_SER, TXT},      // 12    1   1   0   0               Т.красный/фон(миг)  БЕЛЫЙ
    {KRAYARK, TXT},      // 13    1   1   0   1               Ярко-красный    БЕЛЫЙ
    {KRA_SER, KRA_BEL},  // 14    1   1   1   0               Т.красный/фон(миг)  Т.крас/белый
    {KRAYARK, COLOR_PSV} // 15    1   1   1   1               Ярко-красный    Т.кр/красн(миг)

};

int UTSStateColors[16][2] = {
    //                       N      Kzm Mn  Pl  Bu  Цвет заполн  Цвет рамки
    //                        открытое извещение неиспр Закрытое
    {FON, TXT},       // 0 0   0   0   0
    {GELT, TXT},      // 1 0   0   0   1
    {KRA, C_D},       // 2 0   0   1   0
    {COLOR_SVZ, C_D}, // 3 0   0   1   1
    {FON, C_D},       // 4 0   1   0   0
    {GELT, C_D},      // 5 0   1   0   1
    {KRA, C_D},       // 6 0   1   1   0
    {KRA, C_D},       // 7 0   1   1   1
    {COLOR_PSV, TXT}, // 8 1   0   0   0
    {COLOR_PSV, TXT}, // 9 1   0   0       1
    {COLOR_PSV, C_D}, // 10    1   0   1   0
    {COLOR_PSV, C_D}, // 11    1   0   1   1
    {COLOR_PSV, C_D}, // 12    1   1   0   0
    {COLOR_PSV, C_D}, // 13    1   1   0   1
    {COLOR_PSV, C_D}, // 14    1   1   1   0
    {COLOR_PSV, C_D}  // 15    1   1   1   1

};

/*      ЯЧЕЙКА    */
int BASH15Colors[16][2] = {
    //                       N      Bu  Pl  Mn  Kzm Цвет заполн  Цвет рамки
    {FON, FON},      // 0 0   0   0   0
    {FON, FON},      // 1 0   0   0   1
    {ZEL_SER, C_D},  // 2 0   0   1   0
    {ZEL_SER, C_D},  // 3 0   0   1   1
    {GELT_SER, C_D}, // 4 0   1   0   0
    {GELT_SER, C_D}, // 5 0   1   0   1
    {GELT_SER, C_D}, // 6 0   1   1   0
    {GELT_SER, C_D}, // 7 0   1   1   1
    {SV_MIG, C_D},   // 8    1   0   0   0
    {SV_MIG, C_D},   // 9    1   0   0       1
    {SV_MIG, C_D},   // 10   1   0   1   0
    {SV_MIG, C_D},   // 11   1   0   1   1
    {SV_MIG, C_D},   // 12   1   1   0   0
    {SV_MIG, C_D},   // 13   1   1   0   1
    {SV_MIG, C_D},   // 14   1   1   1   0
    {SV_MIG, C_D}    // 15   1   1   1   1
};

int TonnelStateColors[8][2] = {
    //                     нПитФид  нАП  ЗакрДСП
    {FON1, C_D},          // 0    0    0    0
    {KRA, C_D},           // 1    0    0    1
    {FON, BEL_SER},       // 2    0    1    0
    {KRA, BEL_SER},       // 3    0    1    1
    {FON1, COLOR_PSV},    // 4    1    0    0
    {KRA_SER, COLOR_PSV}, // 5    1    0    1
    {FON, KRA_BEL},       // 6    1    1    0
    {KRA_SER, KRA_BEL},   // 7    1    1    1
};

int PerSvetStateColors3[8][2] = {
    //Ф    Л                     нПитФид    нАП  зП
    {FON, TXT},           // 0    0    0    0
    {KRA, TXT},           // 1    0    0    1
    {FON, FON1},          // 2    0    1    0
    {KRA, BEL_SER},       // 3    0    1    1
    {FON1, COLOR_PSV},    // 4    1    0    0
    {KRA_SER, COLOR_PSV}, // 5    1    0    1
    {FON, KRA_BEL},       // 6    1    1    0
    {KRA_SER, KRA_BEL},   // 7    1    1    1
};
