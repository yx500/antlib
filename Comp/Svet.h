//---------------------------------------------------------------------------

#ifndef SvetH
#define SvetH
//---------------------------------------------------------------------------
#include "comp.h"
#include "elem.h"


class Svet_0 : public Element
{
protected:
    int xx;
    int yy;
    int M;
    int M1;
    int ZagradSv;
    int len, sh;
    int clrP, _clrP;
    int clrP2, clrB2;

    int Razmer[2];
    int Stek;
    int impuls_yach;
    int fimpuls_yach;
    int impuls_block;
    int fimpuls_block;
    bool bZAKRKRA;
    int yach_sdvig;
    int impuls_jelt;
    int fimpuls_jelt;
    int impuls_jeltzel;
    int fimpuls_jeltzel;
    int impuls_neispr2;
    int fimpuls_neispr2;
    int impuls_aum_a;
    int impuls_aum_ust;
    int fimpuls_aum_a;
    int fimpuls_aum_ust;
    bool bNiz;
    bool bNoShowSV;

public:
    bool bGorl;

    Svet_0();
    virtual void UpdateState();
    int  GetSubType();
    bool  Show1();
    virtual int IsAlarmState();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

};

class Svet_R : public Svet_0
{
public:
    TYP  GetType();
    UNIT GetUnit();
    //int TstXY(int x,int y);
    virtual void  Show();
};
class Svet_L : public Svet_0
{
public:
    TYP  GetType();
    UNIT GetUnit();
    //int TstXY(int x,int y);
    virtual void  Show();
};







#endif
