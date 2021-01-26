//---------------------------------------------------------------------------

#ifndef ACom_VH
#define ACom_VH
//---------------------------------------------------------------------------

#include "ACom_T.h"

// �������� �������� ��������� ������� �������� �� ����������.
class _ALIB_ TAntOpt
{
public:
    unsigned char TW;  //  =1 ��� ����������� 0 ��� ���
    int    _NAZVA_ ;
    int LUDOCHKA;  //  ����� ������� ��� ������
    int NumTch;   //  ���������� �� ����� ��������
    bool NumTchBG; //  ���������� �� ����� �������� �� �������
    int _2X2_;     // ������ �������
    int NIKOLA;              //��� ���� ���� ����������� ��������� �������
    int FLAG_POINT_NUMBER;        // ��������� ����� �� ������ ��������
    int FLAG_POINT_REVERS;        // ����������� ��������
    int MaxX;
    int MaxY;

    int Sdv_nazv;
    int SVET_LIM;

    bool DNC_ENERG;
    bool TRAINNUM;          //��� ��-�� ����� ������
    int  TN_Ver;            // 1 ���, 3 ����
    int  ENERG;             // 0 1-������ , 2 �����

    int  Ost32Yes;
    int  TypPere;
    int  TypLamp;
    int  TypName;
    int  TypRAMK;


    int DopMashtab;

    bool USE_GORL_OTCECH;

    bool TRAINNUM_INVERS;           //��� ��-�� ����� ������ � �������� �������

    char ENG_PackName[12];          // ��� ������ ��� ������� ����������

    bool bNoShowMSV;
    bool bNoShowPSV;
    bool bShowUstETTMarshruts;
    bool bShowUstETTMarshrutsOnly_1;

    bool bShowInfStat;
    bool bDopPriznak;               // �������� ���.���� ��, ����� �����
    bool bNewNeisprPer;
    bool ShowBottomPeregons;        // �������� ������ �������v
    bool bPodgonSvet;

    bool bShowInfStatAll;             //�������� ���������v� ����� ���

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

extern  int            CommonAnimationStep; // ��� ��� ���������� ��������



extern  bool            _ALIB_ DNC;

extern  bool            _ALIB_ TRAINNUM_SHOW; // ��� ������ ��������
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
//   ��� ���������� ��� ��������
//   �� �� ���� � ���_��
/*-------------------*/
extern  int                    Tip_Opis_PKS;  //  �������� ������� ��� �������� ����������
extern   int            _ALIB_    C_M;
extern   int            _ALIB_ DNC_DC;
extern   int            _ALIB_ MOD ;                //����� ��������/������ (ED/RD)
extern   int            _ALIB_ CurrentStation;      // ������� �������
extern   int            _ALIB_ DELTA_X;
extern   int            _ALIB_ DELTA_Y;
//���������  � �������� Show
//extern int                     clr;


// �������� ���������� ����������
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
