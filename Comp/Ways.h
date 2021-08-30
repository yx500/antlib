//---------------------------------------------------------------------------

#ifndef WaysH
#define WaysH
//---------------------------------------------------------------------------
#include "comp.h"
#include "elem.h"
#include "strel.h"




class Way : public Ways
{

public:


    int LenUV;
    int                     styll1;
    int clrp;
    //byte  *YouFishk;
    Way();

    virtual void UpdateState();
    virtual void  Show();
    virtual void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    TYP  GetType();//{return  WAY;};
    UNIT GetUnit();//{return WAYS;};
    virtual void ChangeMarkerXY(int iMarker,int aX,int aY);
    virtual int GetMarkerCount(){return 2;};
    virtual void GetMarkerPoint(int iMarker,int &aX,int &aY);
    

};

class Plot : public Ways
{
public:
    int impuls_kzm0,impuls_kzm1;
    int fimpuls_kzm0,fimpuls_kzm1;
    int impuls_svob2,impuls_svob3;
    int fimpuls_svob2,fimpuls_svob3;
    int impuls_zan4,impuls_zan5,impuls_zan6;
    int fimpuls_zan4,fimpuls_zan5,fimpuls_zan6;
    int clrp;
    virtual void  Show();
    virtual void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    virtual void UpdateState();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
    Plot();
    TYP  GetType();
    UNIT GetUnit();
    int  GetSubType();
};


class Blok : public Ways
{
public:
    bool bInGrid;
    Blok();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
    virtual void  Show();
    virtual void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    TYP  GetType();
    UNIT GetUnit();
    int  GetSubType();


};

class Bl_uh : public Strel
{
public:
    virtual void  Show();
    virtual void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);
    TYP  GetType();//{return BL_UH;}
    UNIT GetUnit() {
        return STAT ;
    };
    virtual void ShowTrainNumber();
    virtual void HideTrainNumber();
};








#endif
