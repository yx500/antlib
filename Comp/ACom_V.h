//---------------------------------------------------------------------------

#ifndef ACom_VH
#define ACom_VH
//---------------------------------------------------------------------------

#include "ACom_T.h"

// сруктура хранящая параметры участка влияющие на прорисовку.
class _ALIB_ TAntOpt
{
public:
    unsigned char TW;  //  =1 для энергетиков 0 для ост
    int    _NAZVA_ ;
    int LUDOCHKA;  //  Линни толстые или тонкие
    int NumTch;   //  Нумеровать ли точки перегона
    bool NumTchBG; //  Нумеровать ли точки перегона на участке
    int _2X2_;     // Двойно масштаб
    int NIKOLA;              //еше один ФЛАГ СПЕЦИАЛЬНОЙ ОБРАБОТКИ СТРЕЛОК
    int FLAG_POINT_NUMBER;        // Нумерация точек на нижней картинке
    int FLAG_POINT_REVERS;        // Направление движения
    int MaxX;
    int MaxY;

    int Sdv_nazv;
    int SVET_LIM;

    bool DNC_ENERG;
    bool TRAINNUM;          //для уч-ка показ номрое
    int  TN_Ver;            // 1 гид, 3 гора
    int  ENERG;             // 0 1-старый , 2 новый

    int  Ost32Yes;
    int  TypPere;
    int  TypLamp;
    int  TypName;
    int  TypRAMK;


    int DopMashtab;

    bool USE_GORL_OTCECH;

    bool TRAINNUM_INVERS;           //для уч-ка показ номера в обратную сторону

    char ENG_PackName[12];          // имя пакета для участка енергетика

    bool bNoShowMSV;
    bool bNoShowPSV;
    bool bShowUstETTMarshruts;
    bool bShowUstETTMarshrutsOnly_1;

    bool bShowInfStat;
    bool bDopPriznak;               // рисовать доп.инфо пр, длина путей
    bool bNewNeisprPer;
    bool ShowBottomPeregons;        // рисовать нижние перегонv
    bool bPodgonSvet;

    bool bShowInfStatAll;             //рисовать принимаемvе фишки все

    int TsOffColor;
    bool bNumStrelColor;


    char  Name[255];

    bool bEmbeddedSubStation;
    int   _E_def_WK[2];
    int   _E_def_FontsSz[2];

    char  EttReciveName[64];

    __fastcall TAntOpt();

    void __fastcall SetANTON();


};





extern  bool            _ALIB_ bNoEmbeddSubStations;
extern  bool            _ALIB_ bShowExtInfo;
extern bool             _ALIB_ bShowNumberPosition;
extern char             _ALIB_ Ych_Dir[256];
extern char             _ALIB_ Sta_Dir[256];
extern char             _ALIB_ Dat_Dir[256];
extern char             _ALIB_ NBDRV_Path[256];

extern  int            CommonAnimationStep; // шаг для прорисовки анимации



extern  bool            _ALIB_ DNC;

extern  bool            _ALIB_ TRAINNUM_SHOW; // все номера рисовать
extern  bool            bNameBlack;



extern   unsigned char         *sv_ras_y;
extern   unsigned char         *ras     ;
extern   unsigned char         *ras_6   ;
extern    unsigned char        sv_ras_y_2d[50];
extern    unsigned char        ras_2d     [50];
extern    unsigned char        ras_6_2d   [50];
extern    unsigned char        ras_1d     [50];
extern    unsigned char        ras_6_1d   [50];
extern    unsigned char        sv_ras_y_1d[50];
extern    unsigned char        _sv_ras_y_2d[50];
extern    unsigned char        _ras_2d     [50];
extern    unsigned char        _ras_6_2d   [50];
extern    unsigned char        _ras_1d     [50];
extern    unsigned char        _ras_6_1d   [50];
extern    unsigned char        _sv_ras_y_1d[50];
/*-------------------*/
//   Это переменные для передачи
//   ту из Сомп в инп_ту
/*-------------------*/
extern  int                    Tip_Opis_PKS;  //  пришлось сделать для описания параметров
extern   int            _ALIB_    C_M;
extern   int            _ALIB_ DNC_DC;
extern   int            _ALIB_ MOD ;                //РЕЖИМ РЕДАКТОР/ЧТЕНИЕ (ED/RD)
extern   int            _ALIB_ CurrentStation;      // ТЕКУЩЯЯ СТАНЦИЯ
extern   int            _ALIB_ DELTA_X;
extern   int            _ALIB_ DELTA_Y;
//параметры  в функциии Show
//extern int                     clr;


// Основные глобальные переменные
extern  int             _ALIB_ MUL_X;
extern  int             _ALIB_ MUL_Y;
extern  int             _ALIB_ _X_;
extern  int             _ALIB_ _Y_;
extern  int                    Current_Name;
extern int              _ALIB_ FLAG_NAPRAVLENIJA_PO_MINSK; //
extern  int             _ALIB_ CurrentPicture;
extern unsigned char *         sv_ras_y;
extern unsigned char *         ras     ;
extern unsigned char *         ras_6   ;
extern  int             _ALIB_ sh_y;
extern  char *          _ALIB_ Com_Nam[CompTypeCount+1];
extern  int             _ALIB_ CurrentUCH;



extern  AMemory         _ALIB_ MEM;
extern  AMemory         _ALIB_ MEM2;


#endif
