//---------------------------------------------------------------------------

#ifndef ACom_VH
#define ACom_VH
//---------------------------------------------------------------------------

#include "ACom_T.h"

// �������� �������� ��������� ������� �������� �� ����������.
class TAntOpt
{
public:
    uint8 TW;  //  =1 ��� ����������� 0 ��� ���
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

extern  int            CommonAnimationStep; // ��� ��� ���������� ��������



extern  bool            DNC;

extern  bool            TRAINNUM_SHOW; // ��� ������ ��������
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
//   ��� ���������� ��� ��������
//   �� �� ���� � ���_��
/*-------------------*/
extern  int                    Tip_Opis_PKS;  //  �������� ������� ��� �������� ����������
extern   int               C_M;
extern   int            DNC_DC;
extern   int            MOD ;                //����� ��������/������ (ED/RD)
extern   int            CurrentStation;      // ������� �������
extern   int            DELTA_X;
extern   int            DELTA_Y;
//���������  � �������� Show
//extern int                     clr;


// �������� ���������� ����������
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
