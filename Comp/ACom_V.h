//---------------------------------------------------------------------------

#ifndef ACom_VH
#define ACom_VH
//---------------------------------------------------------------------------

#include "ACom_T.h"

// сруктура хранящая параметры участка влияющие на прорисовку.
class TAntOpt
{
public:
    uint8 TW;  //  =1 для энергетиков 0 для ост
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

    TAntOpt();
    void SetANTON();
};



extern  bool            bNoEmbeddSubStations;
extern  bool            bShowExtInfo;
extern bool             bShowNumberPosition;
extern char             Ych_Dir[256];
extern char             Sta_Dir[256];
extern char             Dat_Dir[256];
extern char             NBDRV_Path[256];

extern  int            CommonAnimationStep; // шаг для прорисовки анимации



extern  bool            DNC;

extern  bool            TRAINNUM_SHOW; // все номера рисовать
extern  bool            bNameBlack;



extern   uint8         *sv_ras_y;
extern   uint8         *ras     ;
extern   uint8         *ras_6   ;
extern    uint8        sv_ras_y_2d[50];
extern    uint8        ras_2d     [50];
extern    uint8        ras_6_2d   [50];
extern    uint8        ras_1d     [50];
extern    uint8        ras_6_1d   [50];
extern    uint8        sv_ras_y_1d[50];
extern    uint8        _sv_ras_y_2d[50];
extern    uint8        _ras_2d     [50];
extern    uint8        _ras_6_2d   [50];
extern    uint8        _ras_1d     [50];
extern    uint8        _ras_6_1d   [50];
extern    uint8        _sv_ras_y_1d[50];
/*-------------------*/
//   Это переменные для передачи
//   ту из Сомп в инп_ту
/*-------------------*/
extern  int                    Tip_Opis_PKS;  //  пришлось сделать для описания параметров
extern   int               C_M;
extern   int            DNC_DC;
extern   int            MOD ;                //РЕЖИМ РЕДАКТОР/ЧТЕНИЕ (ED/RD)
extern   int            CurrentStation;      // ТЕКУЩЯЯ СТАНЦИЯ
extern   int            DELTA_X;
extern   int            DELTA_Y;
//параметры  в функциии Show
//extern int                     clr;


// Основные глобальные переменные
extern  int             MUL_X;
extern  int             MUL_Y;
extern  int             _X_;
extern  int             _Y_;
extern  int                    Current_Name;
extern int              FLAG_NAPRAVLENIJA_PO_MINSK; //
extern  int             CurrentPicture;
extern uint8 *         sv_ras_y;
extern uint8 *         ras     ;
extern uint8 *         ras_6   ;
extern  int             sh_y;
extern  const char *          Com_Nam[CompTypeCount+1];
extern  int             CurrentUCH;



extern  AMemory         MEM;
extern  AMemory         MEM2;


#endif
