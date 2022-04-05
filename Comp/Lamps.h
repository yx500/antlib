#ifndef LampsH
#define LampsH
//---------------------------------------------------------------------------

#include "Comp.h"
#include "Elem.h"
#include "Strel.h"
#include "uFormula.h"

#pragma pack(push,1)
struct TLampData {
    uint8 TypKp;
    uint8 NKp;
    uint8 NGr;
    uint8 NOb;
    uint8 LS;
};
struct TGrpahExElem {
    uint8 Enabled;
    uint8 PictNumber;
    uint8 PictWidthStan;
    uint8 PictHeightStan;
    uint8 PictWidthYch;
    uint8 PictHeightYch;
    uint8 TextFontNStan;
    uint8 TextFontNYch;
    uint8 TextFontColor;
    uint8 TextPosStan;
    uint8 TextPosYch;
    uint8 TextRotate;
    uint8 GridAllign;
    uint8 TestExSet;
};
struct TLampMEM {
    TLampData LD;
    TGrpahExElem GE;
};

#pragma pack(pop)



class Lamp : public Element
{
public:

    int8 TypKp;
    int8 NKp;
    int8 NGr;
    int8 NOb;
    __tLStat    *LS;
    __tLStat  FirstLS;
    TGrpahExElem GrpahExData;
    Lamp();
    virtual void Set();
    virtual void Get();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
    virtual const char * GetName();
    void ShowX(int ix, int iy);
    void ShowX1(int ix, int iy);
    void ShowEX(int ix, int iy);

    TYP  GetType();
    int  GetSubType();
    UNIT GetUnit();
    virtual void UpdateState();
    virtual void  Show();
};

class Lam4 : public Strel
{
public:
    void  Show();
    void UpdateState();
    int  GetSubType();
    void ShowENG1(int x, int y);
    void ShowBML(int x, int y);
    TYP  GetType();//{return NAPR;}
    UNIT GetUnit() {
        return STAT ;
    };
};






class SuperLamp2 : public Strel
{
public:
    int TypeLamp;
    bool bAlarmLamp;
    bool bCheck;
    bool bRingInGrid;
    bool bTime;
    long timesec_begin;
    long timesec_dt;
    SuperLamp2();
    void UpdateState();
    void SetStateColors();
    void  Show();
    TYP  GetType();
    UNIT GetUnit() {
        return STAT ;
    };
    void Set();
    void Get();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
};


class CommLmp : public SuperLamp2
{

public:

    std::vector<AComp*> vComps;
    CommLmp();
    ~CommLmp();
    void CollectComps();
    virtual void UpdateState();
    void  Show();
    TYP  GetType();
    UNIT GetUnit() {
        return STAT ;
    };
    virtual void Set();
    virtual void Get();
};

class DtgLmp : public SuperLamp2
{
protected:
    int __LastByte;
    int _iclr;
public:

    String PacketName;
    int PacketType, ByteOffset, NumberBit;
    int fr;
    int Clr2;
    bool bByteChecking;
    int str_n;
    String rzd;
    int ukvag;

    DtgLmp();
    ~DtgLmp();
    virtual void UpdateState();
    void  Show();
    TYP  GetType();
    UNIT GetUnit() {
        return STAT ;
    };
    virtual void Set();
    virtual void Get();
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
};

class tLOG_LAMP : public SuperLamp2
{

public:

    TvFormulaElement vFormula[4];
    TvFormulaElement vFormulaP[4];

    tLOG_LAMP();
    virtual void UpdateState();
    TYP  GetType();
    UNIT GetUnit() {
        return STAT ;
    };
    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);
};


#endif
