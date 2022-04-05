//---------------------------------------------------------------------------

#ifndef Gor_ElemH
#define Gor_ElemH
//---------------------------------------------------------------------------
#include "Comp.h"
#include "Y_STREL.h"
#include "uFormula.h"
#include "tGorka.h"
#include "Lamps.h"
enum tGorElemType
{
    gorRC = 1,
    gorZKR = 2,
    gorSTRY = 3,
    gorZAMI = 4,
    gorZAMP = 5,
    gorSTR1 = 6,
    gorSTR2 = 7,
    gorRC2 = 8,
    gotOTCLABEL = 9,
    gotTPLABEL = 10,
    gotKZP = 11
};

class tGRC0 : public TY_Strel
{
private:
    virtual void ShowFON(){};

public:
    char StrelName[15];
    String stNext[2][2];
    int _tag;
    void *_tagptr;
    bool bUseGAC;
    bool bNegabarit;

    int MinWay, MaxWay, Len, PutPark;
    int MinWay1, MaxWay1; // при минусе лягушки
    int Reserv[3];

    int impuls_sv[2];
    int fimpuls_sv[2];
    void UpdateState();

    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    virtual tGorElemType GetGorElemType() = 0;

    virtual int getospolyline(TPoint *PK, int Psz) { return 0; };

    tGRC0();
};

enum tG_Strel_Y_Imp_Pr
{
    i_prp = 0,
    i_prm = 1,
    i_sk = 2,
    i_m = 3,
    i_ipd = 4,
    i_ped1 = 5,
    i_ped2 = 6,
    i_uvk_block = 7
};

class tG_Strel_Y : public tGRC0
{
private:
    virtual void ShowFON();

protected:
    TPoint Tr[7];
    TPoint Pr[4];
    TPoint Mr[3];
    TPoint NP[2];
    int rr;
    int clrp[8];
    int clrb[8];

    void CalcPRRTDS();
    void ShowPR();
    void ShowRTDS_IPD();
    bool CheckNegabarit();

public:
    int impuls_pr[8];
    int TU_pr[2];

    int fimpuls_pr[8];
    int StrelPrizak[2];

    TvFormulaElement frm_blok;
    TvFormulaElement frm_blokP;
    int ffrm_blok;

    int impuls_uvk_gac;
    int impuls_uvk_str;

    tG_Strel_Y();
    TYP GetType()
    {
        return G_STREL_Y;
    };
    UNIT GetUnit()
    {
        return TY_Strel::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorSTRY;
    };
    void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    virtual int getospolyline(TPoint *PK, int Psz);
};

class tG_Strel_1 : public tGRC0
{
private:
protected:
    int clrp[4];
    int clrb[4];
    TPoint NP[2];
    int tsMarshrut;

public:
    tG_Strel_1();
    TYP GetType()
    {
        return G_STREL_1;
    };
    UNIT GetUnit()
    {
        return TY_Strel::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorSTR1;
    };
    void ShowNormPol();
    void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    virtual int getospolyline(TPoint *PK, int Psz);
};

class tG_Strel_2 : public tG_Strel_1
{
private:
protected:
public:
    int impuls_busy_m[2];
    int fimpuls_busy_m[2];

    tG_Strel_2();
    TYP GetType()
    {
        return G_STREL_2;
    };
    UNIT GetUnit()
    {
        return TY_Strel::GetUnit();
    };
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorSTR2;
    };
};

class tG_RC : public tGRC0
{
private:
protected:
    TPoint NP;
    TPoint P1[10];
    int clr1[10];
    int cntP1;

public:
    tG_RC();
    TYP GetType()
    {
        return G_RC;
    };
    UNIT GetUnit()
    {
        return TY_Strel::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    virtual void Show();
    virtual void UpdateState();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorRC;
    };
    void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    virtual int getospolyline(TPoint *PK, int Psz);
};
class tG_RC_2 : public tG_RC
{
private:
protected:
public:
    int imp_dso[2];
    int imp_osy_cnt;
    int imp_dso_cnt[2];
    tG_RC_2();
    TYP GetType()
    {
        return G_RC_2;
    };
    UNIT GetUnit()
    {
        return tG_RC::GetUnit();
    };
    tGorElemType GetGorElemType()
    {
        return gorRC2;
    };
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
};

class tG_ZAMI;
class tG_OTCLABEL : public AComp
{
public:
    t_Descr Descr;

    int Height, Width;
    int imp_descr_start[5];
    int imp_descr_end[5];
    String Name;
    int NTP;
    int addr1, addr2, AddrLK1Slot, AddrLK2Slot;

    int num;    // Номер отцепа 1-255 Живет в течении роспуска одного
    int mar_f;  // Фактический маршрут(==Заданному либо 0 либо реализов)
    int ves;    // Вес отцепа в тоннах
    int len;    // Длинна ( в вагонах)
    int Stupen; // Ступень торможения
    int V_Zad;
    int V_out;
    int p_rzp;

    tG_OTCLABEL();
    TYP GetType()
    {
        return G_OTCLABEL;
    };
    UNIT GetUnit()
    {
        return STRE;
    };
    virtual const char *GetName()
    {
        return Name.c_str();
    };
    virtual void Show();
    virtual void UpdateState();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
};
class tG_TPLABEL : public tG_OTCLABEL
{
public:
    int V1, V2;
    int Voleg1, Voleg2, RC1, RC2;
    int VesBukv;
    int imp_krasn, imp_krasn_mig;
    int fimp_krasn, fimp_krasn_mig;
    int ZKR_N;
    String ADAM;
    String FADAV_val;
    String ADK3;
    String FADK3_val;
    bool bShowVnadv;
    int fves_osi;
    bool NoShowVout;
    int provV;
    int rc_busy;

    tG_ZAMI *G_ZAMI;

    tG_TPLABEL();
    TYP GetType()
    {
        return G_TPLABEL;
    };
    void Show();
    void UpdateState();

    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);

    void SetParamsFromZam(tG_ZAMI *G_ZAMI);
};

enum tG_ZAMI_Imp_Pr
{
    _impT1 = 0,
    _impT2 = 1,
    _impT3 = 2,
    _impT4 = 3,
    _impR = 4,
    _impA = 5,
    _impKZ = 6,
    _impMAN = 7,
    _impOG = 8,
    _impRRC = 9,
    _impROSPUSK = 10
};
class tG_ZAMI : public tG_RC
{
private:
protected:
    int kolTR;  // кол-во рисуемых треугольников
    int clrpTR; // цвет окантовки треугольников
    int clrbTR; // цвет заполнения треугольников
    int clrpK;  // цвет окантовки прямоугольника
    int clrbK;  // цвет заполнения прямоугольника
    int clrpPP; // цвет окантовки подлжки
    int clrbPP; // цвет заполнения подлжки
    void SetZamColors(int T1, int T2, int T3, int T4, int R, int A, int mkRRC, int mkErrCS, int tsRRC);
    void ShowZAM(float stupen);
    tG_TPLABEL G_TPLABEL;

public:
    String NZAM;
    int NTP, TipZM, AddrLK, AddrLKSlot;
    int TipStupen;
    int DopMashtab;
    int DX_LABEL, DY_LABEL;

    int impuls_zam[11];
    int fimpuls_zam[11];

    int RRC;
    int ErrCS;
    bool bNomkErrCS;

    tG_ZAMI();
    TYP GetType()
    {
        return G_ZAMI;
    };
    UNIT GetUnit()
    {
        return tG_RC::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorZAMI;
    };
};

class tG_ZAMP : public tG_ZAMI
{
private:
protected:
public:
    int AddrKZP;
    tG_ZAMP(){};
    TYP GetType()
    {
        return G_ZAMP;
    };
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorZAMP;
    };
};

const int _zkr_max_imp = 21;

enum tG_ZKR_Imp_Pr
{
    i_rtds1 = 0,
    i_rtds2 = 1,
    i_svetk = 2,
    i_svetj = 3,
    i_svetz = 4,
    i_svetb = 5,
    i_avt = 6,
    i_razcep = 7,
    i_D1 = 8,
    i_DN1 = 11,
    i_D11 = 14,
    i_rosp = 20
};

enum tG_ZKR_Pr
{
    _zkr_regim = 4,
    _zkr_vagon = 5,
    _zkr_putnadv = 6,
    _zkr_AddrLK = 7,
    _zkr_AddrLKSlot = 8,
    _zkr_tip_vivod_dso = 9,
    _zkr_rtds_y = 10,
    _zkr_rtds_h = 11,
    _zkr_rtds_hide = 12
};

class tG_ZKR : public tG_RC
{
private:
protected:
    int Bs[3][2][8];
    int Bs2[6][2][8];
    int xt, x0, dx, dx2;
    void makebs(int dn);

public:
    int impuls_zkr[_zkr_max_imp];
    int fimpuls_zkr[_zkr_max_imp];
    int params_zkr[13];

    tG_ZKR();
    TYP GetType()
    {
        return G_ZKR;
    };
    UNIT GetUnit()
    {
        return tG_RC::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorZKR;
    };
};

class tG_KZP : public AComp
{
public:
    int Height, Width;
    int HeightT, WidthT;
    int MaxD;
    String Name;
    int addr;
    int Direct, inUV;
    uint16 Emask;

    int D, _D, D1; // Значение
    int E, _E;     // Ошибка

    tG_KZP();
    TYP GetType()
    {
        return G_KZP;
    };
    UNIT GetUnit()
    {
        return STRE;
    };
    virtual char *GetName()
    {
        return Name.c_str();
    };
    virtual void Show();
    virtual void UpdateState();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
};

class tG_OSY : public Element
{
public:
    int AddrLK;
    int V, E;
    int imp_osy;
    int tip;
    bool bShowOs;
    int outParam;
    String PacketName_21;
    String stNext[2];
    t_OsyCell_21 OsyCell_21;

    tG_OSY();
    TYP GetType()
    {
        return G_OSY;
    };
    UNIT GetUnit()
    {
        return STRE;
    };
    int GetSubType();
    void Show();
    void UpdateState();

    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
};

class tG_KZP2 : public tG_RC
{
private:
protected:
    TSize szAll; // размер всего без текста свободности
    TSize szNSV; // размер текста свободности
    TSize szNP;  // размер текста номера пути
    int xxNP;    // смещение текста номера пути
    TSize szV;   // размер ячейки скорости
    TSize szNZ;  // размер текста текста занятости
    int xxNZ;    // смещение текста текста занятости
    int yyNZ;    // смещение текста текста занятости

    int mashtab;

    TPoint T[4];
    TPoint TS[4];
    TPoint TZ[4];
    TPoint TV[4];
    TPoint TNP[4];
    TPoint TNS[4];
    TPoint TNZ[4];
    TPoint TUS[4];

    TPoint _TV[4];

    t_KvKzp KvKzp;
    t_KzpInf KzpInf;
    uint16 Emask;
    int kolvo_otc;

    int clr_podl; // цвет подложки
    int clr_Z;    // цвет занятости
    int clr_S;    // цвет свободности
    int clr_US;   // цвет усл свободности
    SuperLamp2 Lmp;
    bool bOtcMig;

public:
    uint8 mar;   // маршрут   c 1
    int AddrKZP; // пипец! он оказывается не равен mar!!!!
    int Direct, inUV;
    int outV;  // 0 не выводить скорость,1 по владу, 2 сам считаю
    int outD;  // 0 по новому,1 старье
    int outZZ; // 0 не выводить занятость
    int dxV;

    tG_KZP2();
    TYP GetType()
    {
        return G_KZP2;
    };
    UNIT GetUnit()
    {
        return tG_RC::GetUnit();
    };
    char *GetName()
    {
        return TY_Strel::GetName();
    }
    void Show();
    void UpdateState();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
    tGorElemType GetGorElemType()
    {
        return gorZAMI;
    };
    virtual int getospolyline(TPoint *PK, int Psz);
    void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    void ShowTrainNumber();
};

#endif
