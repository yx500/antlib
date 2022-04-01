//Strel.h
#ifndef STREL_H
#define STREL_H

#include "Comp.h"
#include "Elem.h"

extern  int Tip_Opis_PKS;  //  �������� ������� ��� �������� ����������

class Strel: public Ways
{
protected:

    int        prNomerHeight;
public:
    Strel();


    int impuls_PKS;
    int impuls_ZS;
    int impuls_ZS2;
    int impuls_kmu2;
    int impuls_mu2;



    int fimpuls_PKS;
    int fimpuls_ZS;
    int fimpuls_ZS2;
    int fimpuls_kmu2;
    int fimpuls_mu2;

    int impuls_otc;
    int fimpuls_otc;

    int impuls_SPU;
    int impuls_AV;
    int fimpuls_SPU;
    int fimpuls_AV;

    int impuls_block;
    int fimpuls_block;
    int impuls_predSA;
    int fimpuls_predSA;
    int impuls_predSAplus;
    int impuls_predSAminus;
    int fimpuls_predSAplus;
    int fimpuls_predSAminus;


    int impuls_otkl_plus;
    int impuls_otkl_minus;
    int fimpuls_otkl_plus;
    int fimpuls_otkl_minus;


    //uint8 RezBuf[4];




public:
    short int  x;
    short int  y;
    signed   char nomer;
    signed   char Prz[4];
    bool     InvertStrel;
    bool bText;
    bool bShowPol;

    /* ���������� �� � 7 �� 10 */
// char name[10]; << � element
public:


    virtual void Set();
    virtual void Get();
    virtual void Show();
    virtual void Go();

    virtual TYP  GetType() = 0;
    virtual char * GetName();

    virtual void UpdateState();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

};

typedef Strel* PStrel;


class Strel0: public Strel
{
protected :
    int sav_sh;
    int sav_sh2;
    void  Strelka(int is, int sw_tip, int styll1, int styll2, int clr, int nm, int x_text, int y_text, char *name, bool InvresPol, int cbord1, int cbord2, bool bShowPol);

public:


    bool bShowInSpyMarsh;
    // ��������� UpdateState
// bool bSetIs;                        // ��� ������ IS
// bool bSetClr;                       // ��� ������ Clr
// bool bSetStyll;                     // ��� ������ Styll
// bool bSetcbord;                     // ��� ������ cbord
    // ��������� ����������
    //clr         // ����
    
    int                     styll1, _styll1;    // ��������� +
    int                     styll2, _styll2;    // ��������� -
    int                     styll3, _styll3;    // ��������� W
    int                     cbord1;     // ���� ��������� +
    int                     cbord2;     // ���� ��������� -


    signed   char rnomer;

    Strel0();
    void Tst_Opis_PKS(void);
    int TestMu(void);
    virtual void UpdateState();
    virtual void  Show1();
    virtual void  Show2();
    void ShowStik(int xx, int yy, int prSTIK);
    UNIT GetUnit() {
        if (nomer > 0) return STRE; else return STAT ;
    };
    void SetStrelShowParams(int Aclr, int Ais, int Astyll1, int Astyll2, int Acbord1, int Acbord2);
    void SetUstPol(int pol);
    
    virtual void ShowTrainNumber();
    virtual void HideTrainNumber();

    //char * GetStrelInfo();
    virtual bool isBusy();
    virtual bool isKzm();
    virtual bool isBusyKzmAccepted();


};
typedef Strel0* PStrel0;

class SwRTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SwRBot : public Strel0
{
public:
    void  Show();
    TYP GetType();

};
class SwLBot: public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SwLTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class Line : public Strel0
{
public:
    void   Show();
    TYP  GetType();
};

class KTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class KBot : public Strel0
{
public:
    void   Show();
    TYP  GetType();
};
class SRTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SRBot : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SLBot : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SLTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SzTop : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SzBot : public Strel0
{
public:
    void  Show();
    TYP  GetType();//{return SzB ;}
};

class Info : public Strel
{
public:
    void  Show();
    void ShowX(int x, int y);
    TYP  GetType();//{return INFO;}
    UNIT GetUnit() {
        return STAT ;
    };
};
class Asn : public Strel
{
    int SS;
public:
    int OldSost;
    void  Show();
    TYP  GetType();//{return INFO;}
    UNIT GetUnit() {
        return STAT ;
    };
};

class Napr : public Strel
{
public:
    int impuls_svob2;
    int fimpuls_svob2;
    int uc;
    void  Show();
    Napr() {
        uc = 0;impuls_svob2=0;fimpuls_svob2=0;
    }
    TYP  GetType();//{return NAPR;}
    UNIT GetUnit() {
        return STAT ;
    };
    virtual void UpdateState();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
};



class APoint : public Strel
{
public:
    void  Show();
    TYP  GetType();//{return POIN;}
    UNIT GetUnit() {
        return STAT ;
    };
};



class Engl1 : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};

class Engl2 : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};

class Xbost1 : public Strel0
{
public:
    void  Show();
    TYP  GetType();
} ;

class Xbost2: public Strel0
{
public:
    void  Show();
    TYP  GetType();
}  ;

class Xbost3: public Strel0
{
public:
    void  Show();
    TYP  GetType();
}   ;

class Xbost4: public Strel0
{
public:
    void  Show();
    TYP  GetType();
}    ;

class Kus1 : public Strel0
{
public:
    void  Show();
    TYP  GetType();
}     ;

class Kus2 : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};

class  P_Sve: public Strel
{
public:
    int clrl;
    int clrt;
    int clrz;
    void  Show();
    virtual char * GetName();
    TYP  GetType() {
        return P_SVE;
    };
    UNIT GetUnit() {
        return STAT ;
    };
    int  GetSubType();
    void UpdateState();
};

class Bash : public Strel
{
public:
    int pencol, fillcol, ColorNum;
    int tip;
    Bash();
    void  Show();
    virtual void UpdateState();
    virtual char * GetName();
    TYP  GetType() {
        return BASH ;
    };
    UNIT GetUnit() {
        return STAT ;
    };
    int  GetSubType();
};




class SRTopW : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SRBotW : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SLBotW : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};
class SLTopW : public Strel0
{
public:
    void  Show();
    TYP  GetType();
};







#endif
