//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ACom_V.h"
#include "col.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



__fastcall TAntOpt::TAntOpt()
{
    TW = 0;            //  =1 ��� ����������� 0 ��� ���
    _NAZVA_ = 6 ;
    LUDOCHKA = 0;      //  ����� ������� ��� ������
    NumTch = 0;        //  ���������� �� ����� ��������
    NumTchBG = true;   //  ���������� �� ����� �������� �� �������
    _2X2_ = 1;         // ������ �������
    FLAG_POINT_NUMBER = 0;      // ��������� ����� �� ������ ��������
    FLAG_POINT_REVERS = 0;      // ����������� ��������
    MaxX = 1280;
    MaxY = 1024;

    Sdv_nazv = 0;
    SVET_LIM = 0;

    DNC_ENERG = false;
    TRAINNUM = 0;        //��� ��-�� ����� ������
    TN_Ver = 1;
    ENERG = 0;

    Ost32Yes = 0;
    TypPere = 0;
    TypLamp = 0;
    TypName = 0;
    TypRAMK = 0;


    DopMashtab = 0;

    USE_GORL_OTCECH = false;

    TRAINNUM_INVERS = false;         //��� ��-�� ����� ������ � �������� �������



    bNoShowMSV = false;
    bNoShowPSV = false;
    bShowUstETTMarshruts = false;
    bShowUstETTMarshrutsOnly_1 = false;
    bShowInfStat = false;
    bDopPriznak = false;             // �������� ���.���� ��, ����� �����
    bNewNeisprPer = false;
    ShowBottomPeregons = true;      // �������� ������ �������v
    bPodgonSvet = false;

    bShowInfStatAll = false;           //�������� ���������v� ����� ���

    TsOffColor = BIRUZOVIJ;
    bNumStrelColor = false;

    bEmbeddedSubStation = true;
    _E_def_WK[0] = 32; _E_def_WK[1] = 20;
    _E_def_FontsSz[0] = 18; _E_def_FontsSz[1] = 14;

    memset(ENG_PackName, 0, sizeof(ENG_PackName));
    memset(Name, 0, sizeof(Name));
    memset(EttReciveName, 0, sizeof(EttReciveName));
}


void __fastcall TAntOpt::SetANTON()
{
    for (int i = 0; i < 50; i++) {
        ras_1d[i] = _ras_1d[i] + DopMashtab;
        //sv_ras_y_1d[i]=_sv_ras_y_1d[i]+DopMashtab;
    }
    /* �������� �����  */
    if (Ost32Yes == 0) {
        COLOR_S   =   GELT       ; //���� �������������� ��������
        COLOR_SET =   ZEL        ; //���� ��������� ��������
        COLOR_IR_Z =  ZEL_LIN    ; //���� �� �������� ��� ���������
        COLOR_IR_B =  KRA_ZEL    ; //���� �� �������� ��� �������
    } else  {
        COLOR_S   =   LIN         ;
        COLOR_SET =   GELT        ;
        COLOR_IR_Z =  GELT_LIN    ; //���� �� �������� ��� ���������
        COLOR_IR_B =  KRA_GELT    ; //���� �� �������� ��� �������
    }

    BIRUZOVIJ = TsOffColor;
}




bool CORR = true;


int CurrentUCH = 0;

/* only Yura */

bool DNC = false;

bool            bNoEmbeddSubStations = false;
bool            bShowNumberPosition = false;
bool            TRAINNUM_SHOW = true; // ��� ������ ��������
bool            bNameBlack = false;

bool bShowExtInfo = false;           // �������� ���.���� ��, ����� �����


int              DELTA_CHAN = 0;



int            CommonAnimationStep = 0; // ��� ��� ���������� ��������

/*-------------------*/
//   �� ��६���� ��� ��।��
//   �� �� ���� � ���_��
/*-------------------*/

int Tip_Opis_PKS = 0;

int C_M;

int  DELTA_Y = 0;
int  DELTA_X = 0;
int  DNC_DC = 0;




int CurrentStation = 0;

int MOD = 0;
int Current_Name = 0;
// �᭮��� �������� ��६����
int FLAG_NAPRAVLENIJA_PO_MINSK = 0;
int MUL_X = 10;
int MUL_Y = 10;
int _X_;
int _Y_;
int CurrentPicture = 1;

unsigned char  *sv_ras_y;
unsigned char  *ras     ;
unsigned char  *ras_6   ;

unsigned char  sv_ras_y_2d[50] = { 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16,};
unsigned char  ras_2d     [50] = { 3, 4, 4, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16,};
unsigned char  ras_6_2d   [50] = { 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 14, 13, 13, 13, 14, 14, 14,};
// 0   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
unsigned char  ras_1d     [50] = {11, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14};
unsigned char  ras_6_1d   [50] = { 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,  7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11};
unsigned char  sv_ras_y_1d[50] = { 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 7,  7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11};



unsigned char  _sv_ras_y_2d[50] = { 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16,};
unsigned char  _ras_2d     [50] = { 3, 4, 4, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16,};
unsigned char  _ras_6_2d   [50] = { 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 14, 13, 13, 13, 14, 14, 14,};
// 0   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
unsigned char  _ras_1d     [50] = {11, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14};
unsigned char  _ras_6_1d   [50] = { 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,  7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11};
unsigned char  _sv_ras_y_1d[50] = { 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 7,  7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11};


int sh_y;
char *Com_Nam[CompTypeCount+1] = {
    "       ",
    "����",
    "������",
    "���",
    "���",
    "���",
    "���",
    "���",
    "���",
    "�����",
    "����",
    "����",
    "���",
    "���",
    "���",
    "���",
    "���",
    "�/�",
    "����",
    "����",
    "����",
    "���",
    "����",
    "����",
    "�����",
    "����",
    "����",
    "����",
    "����",
    "����",
    "�C�",
    "�����",
    "�����",
    "����->",
    "�����",
    "�����",
    "�/� >",
    "���4",
    "���� ",
    "�����",
    "�����",
    "����1",
    "����2",
    "����1",
    "����2v",
    "����3v",
    "����4",
    "����1v",
    "����2",
    "�.���",
    "�����",
    "���",
    "���",
    "���",
    "���",
    "����������",
    "�����������",
    "Y_STREL_1",
    "Y_STREL_2",
    "Y_STREL_3",
    "Y_STREL_4",
    "LED",
    "���.���_Y",
    "���.��",
    "���.���.�",
    "���.���",
    "���.���_1",
    "���.���.�",
    "G_OTCLABEL",
    "G_TPLABEL",
    "G_KZP",
    "G_OSY",
    "���.���_2",
    "�����_������.",
    "DTGLMP",
    "LOG_LAMP",
    "VERSION",
    "TRNUM",          // ����
    "LINI2",
    "SUBSTATION",
    "LED30",
    "E_OBJ",
    "G_KZP2",
    "Y_STREL_5",
    "Y_STREL_6",
    "���.��_2"
};

AMemory MEM;
AMemory MEM2;


char Ych_Dir[256] = "CFG\\";
char Sta_Dir[256] = "STA\\";
char Dat_Dir[256] = "DAT\\";
char NBDRV_Path[256] = ".\\..\\NB_DRV.CFG";



