#include "aheaders_cpp.h"

#include "col.h"
#include "winpalet.h"

#ifndef QT_ANTLIB
#include <inifiles.hpp>
#endif


int     COLOR_S   =   LIN      ; //   11 :-)))WHT       ;     /* ���� ����      */
int     COLOR_SET =   GELT     ; //2 GREEN     ;     /* ���� �������������� �������� */
int     COLOR_IR_Z = ZEL_LIN  ; //   ���� �� �������� ��� ���������
int     COLOR_IR_B =  KRA_ZEL  ; //   ���� �� �������� ��� �������
int     COLOR_GOR_A = 223;
int     BIRUZOVIJ  =  3      ;

int ColorBash[16] = {                 //             B     +       -       KZM
    FON ,              //        0    0 0   0   0
    GELT,              //        1    0 0   0   1
    KRA ,              //        2    0 0   1   0
    ZEL ,              //        3    0 0   1   1
    GELT,              //        4    0 1   0   0
    GELT,              //        5    0 1   0   1
    FON ,              //        6    0 1   1   0
    FON ,              //        7    0 1   1   1
    COLOR_PSV ,        //        8    1 0   0   0
    KRA ,              //        9    1 0   0   1
    KRA ,              //        10   1 0   1   0
    KRA ,              //        11   1 0   1   1
    KRA ,              //        12   1 1   0   0
    KRA ,              //        13   1 1   0   1
    KRA ,              //        14   1 1   1   0
    KRA ,              //        15   1 1   1   1
};

int ColorBash2[16] = {                 //             B     +       -       KZM
    FON ,              //        0    0 0   0   0
    GELT,              //        1    0 0   0   1
    COLOR_PSV ,        //        2    0 0   1   0
    ZEL ,              //        3    0 0   1   1
    GELT,              //        4    0 1   0   0
    GELT,              //        5    0 1   0   1
    FON ,              //        6    0 1   1   0
    FON ,              //        7    0 1   1   1
    COLOR_PSV ,        //        8    1 0   0   0
    KRA ,              //        9    1 0   0   1
    KRA ,              //        10   1 0   1   0
    KRA ,              //        11   1 0   1   1
    KRA ,              //        12   1 1   0   0
    KRA ,              //        13   1 1   0   1
    KRA ,              //        14   1 1   1   0
    KRA ,              //        15   1 1   1   1
};


/* 20/10/2003   */
int SvetStateColors000[8][2] = {
    //              ��� ������.  �C�
    //              BUSY    PLUS     MINUS
    {FON, C_D},     // 0    0   0    0          ��� / ר����
    {FON, ZEL},     // 1    0   0    1          ��� / ��˨���
    {COLOR_PSV, C_D},// 2    0   1    0          ��.��� / ר����
    {COLOR_PSV, ZEL},// 3    0   1    1              ��.��� / ��˨���
    {COLOR_SVZ, C_D},// 4    1   0    0          ��˨��� / ר����
    {COLOR_SVZ, ZEL},// 5    1   0    1          ��˨��� / ��˨���
    {ZEL_MIG, C_D},  // 6   1   1    0          ��˨���-��� / ר����
    {ZEL_MIG, ZEL},// 7  1   1    1          ��˨���-��� / ���
} ;


/* 12/02/2002   */
int SvetStateColors100[8] = {
    //              ��� �����   �������
    //              BUSY    KZM KMU
    FON,    //        0 0   0   0    ���
    KRA,    //        1 0   0   1    ���C���
    TXT,    //        2 0   1   0    �����
    SV_MIG,    //     3 1   1   0    ����� - ��������
    COLOR_SVZ,   //   4 1   0   0    ��˨���
    COLOR_SVZ,   //   5     1   0   1    ��˨���
    COLOR_SVZ,   //   6     1   1   0    ��˨���
    COLOR_SVZ,   //   7     1   1   1    ��˨���
}      ;

/* 12/02/2002   */
int SvetStateColors101[4] = {
    //              ������  �����
    //              KZM    BUSY
    FON,    //        0     0   0           ���
    TXT,    //        1     0   1           �����
    SV_MIG,    //     2     1   0           ����� - ��������
    C_D    //         3     1   1

}      ;

/* 21/10/2003   */
int SvetStateColors006[64][2] = {
//                                  mu  kmu kzm      Minus  Plus    busi
//                                ��������  ����  ������C�   ��    ������ ������    ����       �����
    { FON      ,   C_D        },   //  1   , 0        ,0       ,0    ,0 ,0  ,0  ,���         ,����
    { COLOR_SVZ,   C_D        },   //  2   , 0        ,0       ,0    ,0 ,0  ,1  ,�������     ,����
    { COLOR_PSV,   C_D        },   //  3   , 0        ,0       ,0    ,0 ,1  ,0  ,��-���      ,����
    { ZEL_MIG  ,   C_D        },   //  4   , 0        ,0       ,0    ,0 ,1  ,1  ,���-���     ,����
    { FON      ,   COLOR_SVZ  },   //  5   , 0        ,0       ,0    ,1 ,0  ,0  ,���         ,�����
    { COLOR_SVZ,   COLOR_SVZ  },   //  6   , 0        ,0       ,0    ,1 ,0  ,1  ,�������     ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  7   , 0        ,0       ,0    ,1 ,1  ,0  ,��-���      ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  8   , 0        ,0       ,0    ,1 ,1  ,1  ,���-���     ,�����
    { FON      ,   C_D        },   //  9   , 0        ,0       ,1    ,0 ,0  ,0  ,���         ,����
    { ZEL_MIG  ,   C_D        },   //  10  , 0        ,0       ,1    ,0 ,0  ,1  ,�������-��� ,����
    { COLOR_PSV,   C_D        },   //  11  , 0        ,0       ,1    ,0 ,1  ,0  ,��-���      ,����
    { ZEL_MIG  ,   C_D        },   //  12  , 0        ,0       ,1    ,0 ,1  ,1  ,���-���     ,����
    { FON      ,   COLOR_SVZ  },   //  13  , 0        ,0       ,1    ,1 ,0  ,0  ,���         ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  14  , 0        ,0       ,1    ,1 ,0  ,1  ,�������-��� ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  15  , 0        ,0       ,1    ,1 ,1  ,0  ,��-���      ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  16  , 0        ,0       ,1    ,1 ,1  ,1  ,���-���     ,�����
    { KRA      ,   C_D        },   //  17  , 0        ,1       ,0    ,0 ,0  ,0  ,�������     ,����
    { COLOR_PSV,   C_D        },   //  18  , 0        ,1       ,0    ,0 ,0  ,1  ,�����-���   ,����
    { COLOR_PSV,   C_D        },   //  19  , 0        ,1       ,0    ,0 ,1  ,0  ,�����-���   ,����
    { COLOR_PSV,   C_D        },   //  20  , 0        ,1       ,0    ,0 ,1  ,1  ,�����-���   ,����
    { KRA      ,   COLOR_SVZ  },   //  21  , 0        ,1       ,0    ,1 ,0  ,0  ,�������     ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  22  , 0        ,1       ,0    ,1 ,0  ,1  ,�����-���   ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  23  , 0        ,1       ,0    ,1 ,1  ,0  ,�����-���   ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  24  , 0        ,1       ,0    ,1 ,1  ,1  ,�����-���   ,�����
    { KRA      ,   C_D        },   //  25  , 0        ,1       ,1    ,0 ,0  ,0  ,�������     ,����
    { COLOR_PSV,   C_D        },   //  26  , 0        ,1       ,1    ,0 ,0  ,1  ,�����-���   ,����
    { COLOR_PSV,   C_D        },   //  27  , 0        ,1       ,1    ,0 ,1  ,0  ,�����-���   ,����
    { COLOR_PSV,   C_D        },   //  28  , 0        ,1       ,1    ,0 ,1  ,1  ,�����-���   ,����
    { KRA      ,   COLOR_SVZ  },   //  29  , 0        ,1       ,1    ,1 ,0  ,0  ,�������     ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  30  , 0        ,1       ,1    ,1 ,0  ,1  ,�����-���   ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  31  , 0        ,1       ,1    ,1 ,1  ,0  ,�����-���   ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  32  , 0        ,1       ,1    ,1 ,1  ,1  ,�����-���   ,�����
    { COLOR_PSV,   C_D        },   //  33  , 1        ,0       ,0    ,0 ,0  ,0  ,�����-���   ,����
    { ZEL_MIG  ,   C_D        },   //  34  , 1        ,0       ,0    ,0 ,0  ,1  ,�������-��� ,����
    { COLOR_PSV,   C_D        },   //  35  , 1        ,0       ,0    ,0 ,1  ,0  ,��-���      ,����
    { ZEL_MIG  ,   C_D        },   //  36  , 1        ,0       ,0    ,0 ,1  ,1  ,���-���     ,����
    { COLOR_PSV,   COLOR_SVZ  },   //  37  , 1        ,0       ,0    ,1 ,0  ,0  ,�����-���   ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  38  , 1        ,0       ,0    ,1 ,0  ,1  ,�������-��� ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  39  , 1        ,0       ,0    ,1 ,1  ,0  ,��-���      ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  40  , 1        ,0       ,0    ,1 ,1  ,1  ,���-���     ,�����
    { COLOR_PSV,   C_D        },   //  41  , 1        ,0       ,1    ,0 ,0  ,0  ,��-���      ,����
    { ZEL_MIG  ,   C_D        },   //  42  , 1        ,0       ,1    ,0 ,0  ,1  ,���-���     ,����
    { COLOR_PSV,   C_D        },   //  43  , 1        ,0       ,1    ,0 ,1  ,0  ,��-���      ,����
    { ZEL_MIG  ,   C_D        },   //  44  , 1        ,0       ,1    ,0 ,1  ,1  ,���-���     ,����
    { COLOR_PSV,   COLOR_SVZ  },   //  45  , 1        ,0       ,1    ,1 ,0  ,0  ,��-���      ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  46  , 1        ,0       ,1    ,1 ,0  ,1  ,���-���     ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  47  , 1        ,0       ,1    ,1 ,1  ,0  ,��-���      ,�����
    { ZEL_MIG  ,   COLOR_SVZ  },   //  48  , 1        ,0       ,1    ,1 ,1  ,1  ,���-���     ,�����
    { COLOR_PSV,   C_D        },   //  49  , 1        ,1       ,0    ,0 ,0  ,0  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  50  , 1        ,1       ,0    ,0 ,0  ,1  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  51  , 1        ,1       ,0    ,0 ,1  ,0  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  52  , 1        ,1       ,0    ,0 ,1  ,1  ,��-���      ,����
    { COLOR_PSV,   COLOR_SVZ  },   //  53  , 1        ,1       ,0    ,1 ,0  ,0  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  54  , 1        ,1       ,0    ,1 ,0  ,1  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  55  , 1        ,1       ,0    ,1 ,1  ,0  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  56  , 1        ,1       ,0    ,1 ,1  ,1  ,��-���      ,�����
    { COLOR_PSV,   C_D        },   //  57  , 1        ,1       ,1    ,0 ,0  ,0  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  58  , 1        ,1       ,1    ,0 ,0  ,1  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  59  , 1        ,1       ,1    ,0 ,1  ,0  ,��-���      ,����
    { COLOR_PSV,   C_D        },   //  60  , 1        ,1       ,1    ,0 ,1  ,1  ,��-���      ,����
    { COLOR_PSV,   COLOR_SVZ  },   //  61  , 1        ,1       ,1    ,1 ,0  ,0  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  62  , 1        ,1       ,1    ,1 ,0  ,1  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  },   //  63  , 1        ,1       ,1    ,1 ,1  ,0  ,��-���      ,�����
    { COLOR_PSV,   COLOR_SVZ  }    //  64  , 1        ,1       ,1    ,1 ,1  ,1  ,��-���      ,�����
};

/* 15/07/2002   */
int PerSvetColors[4] = {
    //              BUSY    KZM
    FON,    //        0 0   0           ���
    FON,    //        1 0   1           ���
    COLOR_SVZ,  //    2 1   0           ��˨���
    KRA  //           3    1   1               ���C���
}      ;
/* 21/06/2002   */
int UKSPSColors[16][3] = {
    //
    //                                 BUSY  +   -   KZM
    {COLOR_F_P, FON      , 0}, //     0  0   0   0   0    C�.C����       ���
    {COLOR_F_P, GELT     , 1}, //     1  0   0   0   1    C�.C����   ������
    {C_D,       FON      , 0}, //     2  0   0   1   0        ������         ���
    {C_D,       GELT     , 1}, //     3  0   0   1   1    ������         ������
    {COLOR_F_P, FON      , 0}, //     4  0   1   0   0        C�.C����       ���
    {COLOR_F_P, GELT     , 1}, //     5  0   1   0   1    C�.C����   ������
    {C_D,       FON      , 0}, //     6  0   1   1   0        ������         ���
    {C_D,       GELT     , 1}, //     7  0   1   1   1    ������         ������
    {COLOR_F_P, COLOR_PSV, 1}, //     8  1   0   0   0    C�.C����   ��.���
    {COLOR_F_P, COLOR_B  , 1}, //     9  1   0   0   1    C�.C����   ���C���
    {C_D,       COLOR_PSV, 1}, //     10 1   0   1   0    ������         ��.���
    {C_D,       COLOR_B  , 1}, //     11 1   0   1   1    ������         ���C���
    {COLOR_F_P, COLOR_PSV, 1}, //     12 1   1   0   0    C�.C����   ��.���
    {COLOR_F_P, COLOR_B  , 1}, //     13 1   1   0   1    C�.C����   ���C���
    {C_D,       COLOR_PSV, 1}, //     14 1   1   1   0    ������         ��.���
    {C_D,       COLOR_B  , 1}  //     15 1   1   1   1    ������         ���C���
}      ;

int SAUTPenColors[16] = {
    //              BUSY    +   -   KZM
    COLOR_F_P,      //        0 0   0   0   0       �����
    COLOR_F_P,      //        1 0   0   0   1       �����
    C_D,            //        2 0   0   1   0               ������
    C_D,            //        3 0   0   1   1       ������
    COLOR_F_P,      //        4 0   1   0   0               �����
    COLOR_F_P,      //        5 0   1   0   1       �����
    C_D,            //        6 0   1   1   0               ������
    C_D,            //        7 0   1   1   1       ������
    COLOR_PSV,      //        8 1   0   0   0       ��.���
    COLOR_PSV,      //        9 1   0   0   1       ��.���
    KRA,            //        10    1   0   1   0       ���C���
    KRA,            //        11    1   0   1   1       ���C���
    COLOR_PSV,      //        12    1   1   0   0       ��.���
    COLOR_PSV,      //        13    1   1   0   1       ��.���
    KRA,            //        14    1   1   1   0       ���C���
    KRA             //        15    1   1   1   1       ���C���
} ;
int KGUPenColors[16] = {
    //              BUSY    +   -   KZM
    C_D,            //        0 0   0   0   0       ������
    C_D,            //        1 0   0   0   1       ������
    C_D,            //        2 0   0   1   0               ������
    C_D,            //        3 0   0   1   1       ������
    C_D,            //        4 0   1   0   0               ������
    C_D,            //        5 0   1   0   1       ������
    C_D,            //        6 0   1   1   0               ������
    C_D,            //        7 0   1   1   1       ������
    COLOR_PSV,      //        8 1   0   0   0       ��.���
    COLOR_PSV,      //        9 1   0   0   1       ��.���
    KRA,            //        10    1   0   1   0       ���C���
    KRA,            //        11    1   0   1   1       ���C���
    COLOR_PSV,      //        12    1   1   0   0       ��.���
    COLOR_PSV,      //        13    1   1   0   1       ��.���
    KRA,            //        14    1   1   1   0       ���C���
    KRA             //        15    1   1   1   1       ���C���
} ;


int KMUSvetColors[4] = {
    //              BUSY    +
    FON,            //        0 0   0    ���
    TXT,            //        1 0   1    �����
    KRA,            //        2 1   0    ���C���
    GELT            //        3 1   1    ������
};


int DISKPenColors[16] = {
    //              BUSY    +   -   KZM
    C_D,            //        0 0   0   0   0       ������
    C_D,            //        1 0   0   0   1       ������
    C_D,            //        2 0   0   1   0               ������
    C_D,            //        3 0   0   1   1       ������
    COLOR_F_P,      //        4 0   1   0   0               �����
    COLOR_F_P,      //        5 0   1   0   1       �����
    COLOR_F_P,      //        6 0   1   1   0               �����
    COLOR_F_P,      //        7 0   1   1   1       �����
    C_D,            //        8 1   0   0   0       ������
    C_D,            //        9 1   0   0   1       ������
    C_D,            //        10    1   0   1   0       ������
    C_D,            //        11    1   0   1   1       ������
    COLOR_F_P,      //        12    1   1   0   0       �����
    COLOR_F_P,      //        13    1   1   0   1       �����
    COLOR_F_P,      //        14    1   1   1   0       �����
    COLOR_F_P       //        15    1   1   1   1       �����
} ;
int DISKFillColors[16] = {
    //              BUSY    +   -   KZM
    FON,            //        0 0   0   0   0       ���
    FON,            //        1 0   0   0   1       ���
    FON,            //        2 0   0   1   0               ���
    FON,            //        3 0   0   1   1       ���
    FON,            //        4 0   1   0   0               ���
    FON,            //        5 0   1   0   1       ���
    FON,            //        6 0   1   1   0               ���
    FON,            //        7 0   1   1   1       ���
    COLOR_PSV,      //        8 1   0   0   0       ��.���
    COLOR_PSV,      //        9 1   0   0   1       ��.���
    KRA,            //        10    1   0   1   0       ���C���
    KRA,            //        11    1   0   1   1       ���C���
    COLOR_PSV,      //        12    1   1   0   0       ��.���
    COLOR_PSV,      //        13    1   1   0   1       ��.���
    KRA,            //        14    1   1   1   0       ���C���
    KRA             //        15    1   1   1   1       ���C���
} ;


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




static int32   SPPLC[MaxLampType][16] = {
    { FON1, FON1, FON1, FON1, FON1, FON1, FON1, FON1,  KRA,  KRA,  KRA,  KRA,   KRA,  KRA, KRA,  KRA},
    { 8   , 9   , 9   , 9   , 9   , 9   , 9   , 9   ,  9  ,  9  ,  2  ,  2  ,   2  ,  2  , 2  ,  2  },
    { 8   , 9   , 9   , 9   , 9   , 9   , 9   , 9   ,  11  , 11  , 11  , 11  ,  11  , 11  , 11  , 11 },

    { 8   , 8   , 8   , 8   , 8   , 8   , 8   , 8   ,  2  ,  2  ,  2  ,  2  ,   2  ,  2  , 2  ,  2  },

    { 8   , 8   , 8   , 8   , 8   , 8   , 8   , 8   ,  2  ,  4  ,  4  ,  4  ,   4  ,  4  , 2  ,  2  }
};


int KROSHBCOL[16] = {
    0,        //        0  Black            ������
    236,      //        1  Blue             �����
    221,      //        2  Green            �������
    170,      //        3  Cyan             �������
    207,      //        4  Red              �������
    149,      //        5  Magenta          ����������
    152,      //        6  Brown            ����������
    247,      //        7  LightGray        ������-�����
    17,       //        8  DarkGray         �����-�����
    233,      //        9  LightBlue        ����-�����
    219,      //        10  LightGreen       ����-�������
    136,      //        11  LightCyan        ����-�������
    205,      //        12  LightRed         ����-�������
    155,      //        13  LightMagenta     ����-����������
    251,      //        14  Yellow           ������
    246       //        15  White            �����
};
int KROSHPCOL[16] = {
    246,      //        0  Black            ������
    246  ,      //        1  Blue             �����
    246  ,      //        2  Green            �������
    0,      //        3  Cyan             �������
    246,      //        4  Red              �������
    246,      //        5  Magenta          ����������
    246,      //        6  Brown            ����������
    0,      //        7  LightGray        ������-�����
    0,       //        8  DarkGray         �����-�����
    246,      //        9  LightBlue        ����-�����
    0,      //        10  LightGreen       ����-�������
    0,      //        11  LightCyan        ����-�������
    0,      //        12  LightRed         ����-�������
    0,      //        13  LightMagenta     ����-����������
    0,      //        14  Yellow           ������
    0       //        15  White            �����
};



void _SetCol(int T, int N, String S)
{
    if (S.Pos("x") > 0)
        SPPLC[T][N] = -S.ToIntDef(0); else
        SPPLC[T][N] = S.ToIntDef(0);
}
#ifndef QT_ANTLIB

bool wc_LoadIniFile()
{
    static bool wc_loaded=false;
    try {
        if (wc_loaded) return true;
        String FN = String(DACCfgFileName);
        FN = ChangeFileExt(FN, ".ini");
        if (!FileExists(FN)) return false;
        TMemIniFile * FI = new TMemIniFile(FN);
        String ST, S, Sect;
        char s[10];
        for (int i = 0; i < MaxLampType; i++) {
            Sect = "TYPE_" + IntToStr(i);
            if (!FI->SectionExists(Sect))continue;
            for (int j = 0; j < 16; j++) {
                itoa(j, s, 2);
                ST = String(s);
                while (ST.Length() < 4)ST = "0" + ST;
                S = FI->ReadString(Sect, ST, "0000");
                _SetCol(i, j, S);
            }
        }

        // ��������� ����� �����
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
    wc_loaded=true;
    return true;
}
#endif

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
//��� ����  ��� �����   N   Mu  Km  Kz  Mn  Pl  Bu
//                    ������� ������  �������.  ����    ������� ������
//                            ��������  ������  ������
    {FON,       C_D,        },    //0,0,0,0,0,0,0
    {COLOR_SVZ, C_D,        },    //1,0,0,0,0,0,1
    {FON,       KRA,        },    //2,0,0,0,0,1,0
    {COLOR_SVZ, KRA,        },    //3,0,0,0,0,1,1
    {FON,       COLOR_SVZ,  },    //4,0,0,0,1,0,0
    {COLOR_SVZ, COLOR_SVZ,  },    //5,0,0,0,1,0,1
    {FON,       KRA_ZEL,    },    //6,0,0,0,1,1,0
    {COLOR_SVZ, KRA_ZEL,    },    //7,0,0,0,1,1,1
    {BEL_SER,   C_D ,       },    //8,0,0,1,0,0,0
    {COLOR_SVZ, CHERN_FON,  },    //9,0,0,1,0,0,1
    {BEL_SER,   KRA_CHERN,  },    //10,0,0,1,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //11,0,0,1,0,1,1
    {BEL_SER,   CHERN_FON,  },    //12,0,0,1,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //13,0,0,1,1,0,1
    {BEL_SER,   CHERN_FON,  },    //14,0,0,1,1,1,0
    {COLOR_SVZ, CHERN_FON,  },    //15,0,0,1,1,1,1
    {KRA,       C_D,        },    //16,0,1,0,0,0,0
    {COLOR_SVZ, CHERN_FON,  },    //17,0,1,0,0,0,1
    {KRA,       KRA ,       },    //18,0,1,0,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //19,0,1,0,0,1,1
    {KRA,       COLOR_SVZ,  },    //20,0,1,0,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //21,0,1,0,1,0,1
    {KRA,       KRA_ZEL,    },    //22,0,1,0,1,1,0
    {COLOR_SVZ, CHERN_FON,  },    //23,0,1,0,1,1,1
    {BEL_SER,   KRA,        },    //24,0,1,1,0,0,0
    {COLOR_SVZ, CHERN_FON,  },    //25,0,1,1,0,0,1
    {BEL_SER,   KRA_CHERN,  },    //26,0,1,1,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //27,0,1,1,0,1,1
    {FON,       CHERN_FON,  },    //28,0,1,1,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //29,0,1,1,1,0,1
    {FON,       CHERN_FON,  },    //30,0,1,1,1,1,0
    {COLOR_SVZ, CHERN_FON,  },    //31,0,1,1,1,1,1
    {FON ,      KRA,        },    //32,1,0,0,0,0,0
    {COLOR_SVZ, KRA_CHERN,  },    //33,1,0,0,0,0,1
    {FON,       KRA,        },    //34,1,0,0,0,1,0
    {COLOR_SVZ, KRA_CHERN,  },    //35,1,0,0,0,1,1
    {FON,       KRA_ZEL,    },    //36,1,0,0,1,0,0
    {COLOR_SVZ, KRA_ZEL,    },    //37,1,0,0,1,0,1
    {FON,       KRA_ZEL,    },    //38,1,0,0,1,1,0
    {COLOR_SVZ, KRA_ZEL,    },    //39,1,0,0,1,1,1
    {BEL_SER,   KRA,        },    //40,1,0,1,0,0,0
    {COLOR_SVZ, KRA_CHERN,  },    //41,1,0,1,0,0,1
    {BEL_SER,   KRA_CHERN,  },    //42,1,0,1,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //43,1,0,1,0,1,1
    {KRA,       CHERN_FON,  },    //44,1,0,1,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //45,1,0,1,1,0,1
    {BEL_SER,   CHERN_FON,  },    //46,1,0,1,1,1,0
    {COLOR_SVZ, CHERN_FON,  },    //47,1,0,1,1,1,1
    {KRA,       KRA_CHERN,  },    //48,1,1,0,0,0,0
    {COLOR_SVZ, CHERN_FON,  },    //49,1,1,0,0,0,1
    {KRA_SER,   C_D,        },    //50,1,1,0,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //51,1,1,0,0,1,1
    {KRA,       KRA_ZEL,    },    //52,1,1,0,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //53,1,1,0,1,0,1
    {KRA,       KRA_ZEL,    },    //54,1,1,0,1,1,0
    {COLOR_SVZ, CHERN_FON,  },    //55,1,1,0,1,1,1
    {BEL_SER,   KRA,        },    //56,1,1,1,0,0,0
    {COLOR_SVZ, CHERN_FON,  },    //57,1,1,1,0,0,1
    {BEL_SER,   KRA_CHERN,  },    //58,1,1,1,0,1,0
    {COLOR_SVZ, CHERN_FON,  },    //59,1,1,1,0,1,1
    {BEL_SER,   CHERN_FON,  },    //60,1,1,1,1,0,0
    {COLOR_SVZ, CHERN_FON,  },    //61,1,1,1,1,0,1
    {BEL_SER,   CHERN_FON,  },    //62,1,1,1,1,1,0
    {COLOR_SVZ, CHERN_FON,  }     //63,1,1,1,1,1,1
};
int SvetStateColors008[64][2] = {
//���� ������   ���� �����          N   Mu  Kmu Kz  Mn  Pl  Bu
//FON   �����       ��������������                  ������� ������  ����    �����   ������
//                                              ��������        ������
    {FON,           C_D         },    //    0,  0,  0,  0,  0,  0,  0
    {COLOR_SVZ, C_D         },    //    1,  0,  0,  0,  0,  0,  1
    {BEL_SER,   C_D         },    //    2,  0,  0,  0,  0,  1,  0
    {BEL_SER,   C_D         },    //    3,  0,  0,  0,  0,  1,  1
    {FON,           COLOR_SVZ   },    //    4,  0,  0,  0,  1,  0,  0
    {COLOR_SVZ, COLOR_SVZ   },    //    5,  0,  0,  0,  1,  0,  1
    {BEL_SER,   CHERN_FON   },    //    6,  0,  0,  0,  1,  1,  0
    {BEL_SER,   CHERN_FON   },    //    7,  0,  0,  0,  1,  1,  1
    {TXT,           C_D         },    //    8,  0,  0,  1,  0,  0,  0
    {COLOR_SVZ, CHERN_FON   },    //    9,  0,  0,  1,  0,  0,  1
    {BEL_SER,   CHERN_FON   },    //    10, 0,  0,  1,  0,  1,  0
    {BEL_SER,   CHERN_FON   },    //    11, 0,  0,  1,  0,  1,  1
    {TXT,           CHERN_FON   },    //    12, 0,  0,  1,  1,  0,  0
    {COLOR_SVZ, ZEL_SER     },    //    13, 0,  0,  1,  1,  0,  1
    {BEL_SER,   CHERN_FON   },    //    14, 0,  0,  1,  1,  1,  0
    {BEL_SER,   CHERN_FON   },    //    15, 0,  0,  1,  1,  1,  1
    {FON,           KRA         },    //    16, 0,  1,  0,  0,  0,  0
    {COLOR_SVZ, KRA         },    //    17, 0,  1,  0,  0,  0,  1
    {BEL_SER,   KRA         },    //    18, 0,  1,  0,  0,  1,  0
    {BEL_SER,   KRA         },    //    19, 0,  1,  0,  0,  1,  1
    {FON,           KRA_ZEL     },    //    20, 0,  1,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL     },    //    21, 0,  1,  0,  1,  0,  1
    {BEL_SER,   KRA_SER     },    //    22, 0,  1,  0,  1,  1,  0
    {BEL_SER,   KRA_SER     },    //    23, 0,  1,  0,  1,  1,  1
    {TXT,           KRA         },    //    24, 0,  1,  1,  0,  0,  0
    {COLOR_SVZ, KRA         },    //    25, 0,  1,  1,  0,  0,  1
    {BEL_SER,   KRA         },    //    26, 0,  1,  1,  0,  1,  0
    {BEL_SER,   KRA         },    //    27, 0,  1,  1,  0,  1,  1
    {FON ,          KRA_ZEL     },    //    28, 0,  1,  1,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL     },    //    29, 0,  1,  1,  1,  0,  1
    {BEL_SER,   KRA_SER     },    //    30, 0,  1,  1,  1,  1,  0
    {BEL_SER,   KRA_SER     },    //    31, 0,  1,  1,  1,  1,  1
    {FON,           CHERN_FON   },    //    32, 1,  0,  0,  0,  0,  0
    {COLOR_SVZ, KRA_CHERN   },    //    33, 1,  0,  0,  0,  0,  1
    {BEL_SER,   KRA         },    //    34, 1,  0,  0,  0,  1,  0
    {BEL_SER,   KRA         },    //    35, 1,  0,  0,  0,  1,  1
    {FON,           KRA_ZEL     },    //    36, 1,  0,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL     },    //    37, 1,  0,  0,  1,  0,  1
    {BEL_SER,   KRA_SER     },    //    38, 1,  0,  0,  1,  1,  0
    {BEL_SER,   KRA_SER     },    //    39, 1,  0,  0,  1,  1,  1
    {TXT,           C_D         },    //    40, 1,  0,  1,  0,  0,  0
    {COLOR_SVZ, KRA_CHERN   },    //    41, 1,  0,  1,  0,  0,  1
    {BEL_SER,   KRA         },    //    42, 1,  0,  1,  0,  1,  0
    {BEL_SER,   KRA         },    //    43, 1,  0,  1,  0,  1,  1
    {TXT,           CHERN_FON   },    //    44, 1,  0,  1,  1,  0,  0
    {COLOR_SVZ, KRA_SER     },    //    45, 1,  0,  1,  1,  0,  1
    {TXT,           KRA_SER     },    //    46, 1,  0,  1,  1,  1,  0
    {BEL_SER,   KRA_SER     },    //    47, 1,  0,  1,  1,  1,  1
    {FON,           KRA         },    //    48, 1,  1,  0,  0,  0,  0
    {COLOR_SVZ, KRA         },    //    49, 1,  1,  0,  0,  0,  1
    {BEL_SER,   KRA         },    //    50, 1,  1,  0,  0,  1,  0
    {BEL_SER,   KRA         },    //    51, 1,  1,  0,  0,  1,  1
    {FON,           KRA_ZEL     },    //    52, 1,  1,  0,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL     },    //    53, 1,  1,  0,  1,  0,  1
    {BEL_SER,   KRA_ZEL     },    //    54, 1,  1,  0,  1,  1,  0
    {BEL_SER,   KRA_ZEL     },    //    55, 1,  1,  0,  1,  1,  1
    {FON,           KRA         },    //    56, 1,  1,  1,  0,  0,  0
    {COLOR_SVZ, KRA         },    //    57, 1,  1,  1,  0,  0,  1
    {BEL_SER,   KRA         },    //    58, 1,  1,  1,  0,  1,  0
    {BEL_SER,   KRA         },    //    59, 1,  1,  1,  0,  1,  1
    {FON,           KRA_ZEL     },    //    60, 1,  1,  1,  1,  0,  0
    {COLOR_SVZ, KRA_ZEL     },    //    61, 1,  1,  1,  1,  0,  1
    {BEL_SER,   KRA_SER     },    //    62, 1,  1,  1,  1,  1,  0
    {BEL_SER,   KRA_SER     }    // 63, 1,  1,  1,  1,  1,  1
};



int PerSvetStateColors[16][2] = {
//                            N    Kzm Mn  Pl  Bu  ���� ������  ���� �����
//                            �������� ��������� ������ ��������
    {FON    , C_D},         //0     0   0   0   0               ��� ר����
    {KRA    , C_D},         //1     0   0   0   1               �.�������   ר����
    {FON    , KRA},         //2     0   0   1   0               ��� �.�������
    {KRA    , KRA},         //3     0   0   1   1               �.�������   �.�������
    {KRA_SER, C_D},         //4     0   1   0   0               �.�������/���(���)  ר����
    {KRAYARK, C_D},         //5     0   1   0   1               ����-�������    ר����
    {KRA_SER, KRA},         //6     0   1   1   0               �.�������/���(���)  �.�������
    {KRAYARK, KRA},         //7     0   1   1   1               ����-�������    �.�������
    {FON    , TXT},         //8     1   0   0   0               ��� �����
    {KRA    , SER_CHERN},   //9     1   0   0   1               �.�������   ר����/�,�.���
    {FON    , KRA_BEL},     //10    1   0   1   0               ��� �.����/�����
    {KRA    , KRA_BEL},     //11    1   0   1   1               �.�������   ���/�������
    {KRA_SER, TXT},         //12    1   1   0   0               �.�������/���(���)  �����
    {KRAYARK, TXT},         //13    1   1   0   1               ����-�������    �����
    {KRA_SER, KRA_BEL},     //14    1   1   1   0               �.�������/���(���)  �.����/�����
    {KRAYARK, COLOR_PSV}    //15    1   1   1   1               ����-�������    �.��/�����(���)

};


int UTSStateColors[16][2] = {
//                       N      Kzm Mn  Pl  Bu  ���� ������  ���� �����
//                        �������� ��������� ������ ��������
    {FON    , TXT},         //0 0   0   0   0
    {GELT   , TXT},         //1 0   0   0   1
    {KRA    , C_D},         //2 0   0   1   0
    {COLOR_SVZ, C_D},       //3 0   0   1   1
    {FON, C_D},             //4 0   1   0   0
    {GELT, C_D},            //5 0   1   0   1
    {KRA, C_D},             //6 0   1   1   0
    {KRA, C_D},             //7 0   1   1   1
    {COLOR_PSV, TXT},       //8 1   0   0   0
    {COLOR_PSV, TXT},       //9 1   0   0       1
    {COLOR_PSV, C_D},       //10    1   0   1   0
    {COLOR_PSV, C_D},       //11    1   0   1   1
    {COLOR_PSV, C_D},       //12    1   1   0   0
    {COLOR_PSV, C_D},       //13    1   1   0   1
    {COLOR_PSV, C_D},       //14    1   1   1   0
    {COLOR_PSV, C_D}        //15    1   1   1   1

};


/*      ������    */
int BASH15Colors[16][2] = {
//                       N      Bu  Pl  Mn  Kzm ���� ������  ���� �����
    {FON    , FON},         //0 0   0   0   0
    {FON    , FON},         //1 0   0   0   1
    {ZEL_SER, C_D},         //2 0   0   1   0
    {ZEL_SER, C_D},         //3 0   0   1   1
    {GELT_SER, C_D},        //4 0   1   0   0
    {GELT_SER, C_D},        //5 0   1   0   1
    {GELT_SER, C_D},        //6 0   1   1   0
    {GELT_SER, C_D},        //7 0   1   1   1
    {SV_MIG, C_D},       //8    1   0   0   0
    {SV_MIG, C_D},       //9    1   0   0       1
    {SV_MIG, C_D},       //10   1   0   1   0
    {SV_MIG, C_D},       //11   1   0   1   1
    {SV_MIG, C_D},       //12   1   1   0   0
    {SV_MIG, C_D},       //13   1   1   0   1
    {SV_MIG, C_D},       //14   1   1   1   0
    {SV_MIG, C_D}        //15   1   1   1   1
};


int TonnelStateColors[8][2] = {
    //                     �������  ���  �������
    {FON1, C_D},           // 0    0    0    0
    {KRA, C_D},            // 1    0    0    1
    {FON, BEL_SER},        // 2    0    1    0
    {KRA, BEL_SER},        // 3    0    1    1
    {FON1, COLOR_PSV},     // 4    1    0    0
    {KRA_SER, COLOR_PSV},  // 5    1    0    1
    {FON, KRA_BEL},        // 6    1    1    0
    {KRA_SER, KRA_BEL},    // 7    1    1    1
} ;

int PerSvetStateColors3[8][2] = {
//�    �                     �������    ���  ��
    {FON, TXT},            // 0    0    0    0
    {KRA, TXT},            // 1    0    0    1
    {FON, FON1},           // 2    0    1    0
    {KRA, BEL_SER},        // 3    0    1    1
    {FON1, COLOR_PSV},     // 4    1    0    0
    {KRA_SER, COLOR_PSV},  // 5    1    0    1
    {FON, KRA_BEL},        // 6    1    1    0
    {KRA_SER, KRA_BEL},    // 7    1    1    1
} ;


