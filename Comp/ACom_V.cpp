//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ACom_V.h"
#include "col.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



__fastcall TAntOpt::TAntOpt()
{
    TW = 0;            //  =1 для энергетиков 0 для ост
    _NAZVA_ = 6 ;
    LUDOCHKA = 0;      //  Линни толстые или тонкие
    NumTch = 0;        //  Нумеровать ли точки перегона
    NumTchBG = true;   //  Нумеровать ли точки перегона на участке
    _2X2_ = 1;         // Двойно масштаб
    FLAG_POINT_NUMBER = 0;      // Нумерация точек на нижней картинке
    FLAG_POINT_REVERS = 0;      // Направление движения
    MaxX = 1280;
    MaxY = 1024;

    Sdv_nazv = 0;
    SVET_LIM = 0;

    DNC_ENERG = false;
    TRAINNUM = 0;        //для уч-ка показ номрое
    TN_Ver = 1;
    ENERG = 0;

    Ost32Yes = 0;
    TypPere = 0;
    TypLamp = 0;
    TypName = 0;
    TypRAMK = 0;


    DopMashtab = 0;

    USE_GORL_OTCECH = false;

    TRAINNUM_INVERS = false;         //для уч-ка показ номера в обратную сторону



    bNoShowMSV = false;
    bNoShowPSV = false;
    bShowUstETTMarshruts = false;
    bShowUstETTMarshrutsOnly_1 = false;
    bShowInfStat = false;
    bDopPriznak = false;             // рисовать доп.инфо пр, длина путей
    bNewNeisprPer = false;
    ShowBottomPeregons = true;      // рисовать нижние перегонv
    bPodgonSvet = false;

    bShowInfStatAll = false;           //рисовать принимаемvе фишки все

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
    /* изменяем цвета  */
    if (Ost32Yes == 0) {
        COLOR_S   =   GELT       ; //цвет установленного маршрута
        COLOR_SET =   ZEL        ; //цвет замыкания маршрута
        COLOR_IR_Z =  ZEL_LIN    ; //цвет ИР маршрута при замкнутом
        COLOR_IR_B =  KRA_ZEL    ; //цвет ИР маршрута при занятом
    } else  {
        COLOR_S   =   LIN         ;
        COLOR_SET =   GELT        ;
        COLOR_IR_Z =  GELT_LIN    ; //цвет ИР маршрута при замкнутом
        COLOR_IR_B =  KRA_GELT    ; //цвет ИР маршрута при занятом
    }

    BIRUZOVIJ = TsOffColor;
}




bool CORR = true;


int CurrentUCH = 0;

/* only Yura */

bool DNC = false;

bool            bNoEmbeddSubStations = false;
bool            bShowNumberPosition = false;
bool            TRAINNUM_SHOW = true; // все номера рисовать
bool            bNameBlack = false;

bool bShowExtInfo = false;           // рисовать доп.инфо пр, длина путей


int              DELTA_CHAN = 0;



int            CommonAnimationStep = 0; // шаг для прорисовки анимации

/*-------------------*/
//   ќв® ЇҐаҐ¬Ґ­­лҐ ¤«п ЇҐаҐ¤ зЁ
//   вг Ё§ ‘®¬Ї ў Ё­Ї_вг
/*-------------------*/

int Tip_Opis_PKS = 0;

int C_M;

int  DELTA_Y = 0;
int  DELTA_X = 0;
int  DNC_DC = 0;




int CurrentStation = 0;

int MOD = 0;
int Current_Name = 0;
// Ћб­®ў­лҐ Ј«®Ў «м­лҐ ЇҐаҐ¬Ґ­­лҐ
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
    "Путь",
    "Участк",
    "Сгн",
    "Сгн",
    "Стр",
    "Стр",
    "Стр",
    "Стр",
    "Линия",
    "Крив",
    "Крив",
    "Стр",
    "Стр",
    "Стр",
    "Стр",
    "Инф",
    "Б/У",
    "Стан",
    "Стан",
    "Стан",
    "Имя",
    "Горл",
    "Горл",
    "Текст",
    "Съез",
    "Съез",
    "Горл",
    "Напр",
    "Ламп",
    "АCН",
    "Отрез",
    "Перее",
    "Точк->",
    "Цифра",
    "Тупик",
    "Б/У >",
    "Лмп4",
    "Стык ",
    "Елект",
    "Платф",
    "Англ1",
    "Англ2",
    "Хвос1",
    "Хвос2v",
    "Хвос3v",
    "Хвос4",
    "Кусо1v",
    "Кусо2",
    "П.СВЕ",
    "БАШМА",
    "Стр",
    "Стр",
    "Стр",
    "Стр",
    "СуперЛампа",
    "МультиЛампа",
    "Y_STREL_1",
    "Y_STREL_2",
    "Y_STREL_3",
    "Y_STREL_4",
    "LED",
    "Гор.Стр_Y",
    "Гор.РЦ",
    "Гор.Зам.И",
    "Гор.ЗКР",
    "Гор.Стр_1",
    "Гор.Зам.П",
    "G_OTCLABEL",
    "G_TPLABEL",
    "G_KZP",
    "G_OSY",
    "Гор.Стр_2",
    "Общая_Неиспр.",
    "DTGLMP",
    "LOG_LAMP",
    "VERSION",
    "TRNUM",          // тшЁЄ
    "LINI2",
    "SUBSTATION",
    "LED30",
    "E_OBJ",
    "G_KZP2",
    "Y_STREL_5",
    "Y_STREL_6",
    "Гор.РЦ_2"
};

AMemory MEM;
AMemory MEM2;


char Ych_Dir[256] = "CFG\\";
char Sta_Dir[256] = "STA\\";
char Dat_Dir[256] = "DAT\\";
char NBDRV_Path[256] = ".\\..\\NB_DRV.CFG";



