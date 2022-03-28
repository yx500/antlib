//elem.h
#ifndef ELEM_H
#define ELEM_H

#include "comp.h"
#include "uEXD.h"
#include "out_num.h"


class _ALIB_ Element: public AComp
{
public:

    int impuls_plus;
    int impuls_mnus;
    int impuls_kzm;
    int impuls_kmu;
    int impuls_mu;
    int fimpuls_plus;
    int fimpuls_mnus;
    int fimpuls_kzm;
    int fimpuls_kmu;
    int fimpuls_mu;


    unsigned char RezBuf[4];
    unsigned char RezBuf1[2];





public:


    virtual void Set();
    virtual void Get();
    //virtual void Show(void);

    virtual void Go();

    virtual void UpdateState();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

    Element();
    ~Element() {}

};

typedef Element* PElement;


class Gorl_L : public Element
{
public:
    TYP  GetType();//{return GORL_L;};
    UNIT GetUnit();//{return WAYS;};
    virtual void  Show();
};
class Gorl_R : public Element
{
public:
    TYP  GetType();//{return GORL_R;};
    UNIT GetUnit();//{return WAYS;};
    virtual void  Show();
};



// абстрактный класс с которого наследуются все элементы рц

class Ways : public Element
{
public:

    int impuls_IR;
    int fimpuls_IR;
    int impuls_predSEIR;
    int fimpuls_predSEIR;

    int impuls_svob;
    int fimpuls_svob;

    byte   MyFishk;

    bool bShowUIR;

    TTrainInfo TrainInfo;
    int                     is, _is;        // положение
    unsigned __int16 IDnext[2][2]; // сцылки на след элементы для гида

    Ways();

    //virtual char * GetCompInfo();

    virtual void UpdateState();

    virtual void ShowTrainNumber();
    virtual void HideTrainNumber();

    virtual void Set();
    virtual void Get();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

    void SetUstIR(int AIR);

    virtual bool isBusy();
    virtual bool isKzm();
    virtual bool isBusyKzmAccepted();


};




#endif
