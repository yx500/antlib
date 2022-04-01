//---------------------------------------------------------------------------

#ifndef Y_STRELH
#define Y_STRELH
//---------------------------------------------------------------------------

#include "Strel.h"
struct TFPoint{
       double x,y;
       void S(double ax,double ay){x=ax;y=ay;}
       void S(TPoint P){x=P.x;y=P.y;}
       TPoint ToPoint(){
            int X=(int) (x+0.5);
            if (x<0) X=(int) (x-0.5);
            int Y=(int) (y+0.5);
            if (y<0) Y=(int) (y-0.5);
            return TPoint(X,Y);
       }
};
struct tStrelYParams {
    //int XX, YY, L1, L2, L3, L3_,DH, DX;
    TPoint M[7];
    int M0X, M0Y, M3X, M3Y,M1Y;
    int sh_y;   // Ширина в сечении
    int prSTIK[3]; // стыки
    int CurrentPicture;
    int tpriz;
};
/*
void  CalcStrelY(tStrelYParams & YP,
                 //TPoint * M, // Точки полученые
                 TPoint * iT,
                 TPoint * iT_,
                 TPoint * iTd,
                 TPoint * iTd_,
                 TPoint &TP,
                 TPoint *TNPOL,
                 int &x_n,
                 int &y_n);
*/



class TY_Strel : public Strel0
{

private:
protected:
    int XX, YY, L2;


    int L3_;
    TPoint TP;
    int x_n, y_n, tpriz;

    int  _is;
    int _styll1;
    int _styll2;
    int _styll3;

    int num_font_sz;


    tStrelYParams lastYP;

    int _1x, _1y;
    void  CalcStrelY();
    virtual void ShowFON()=0;
    void ShowBLOCK();





public:
    double DX, DH;
    int M0X, M0Y, M3X, M3Y,M1Y;
    tStrelYParams YP;
    TPoint T[22];
    TPoint Td[22];
    TPoint T_[22];
    TPoint Td_[22];
    TPoint TNPOL[22];
    TPoint BL[4];
    int clBP, clBM, clPP, clPM, clS1, clS2, clS3;
    int prSTIK[3];

    bool static_enabled; // режим рисования статического вида
    int  static_clB,static_clP[2];
    int  static_shy[2];
    int  static_is;

    TY_Strel();
    void  Show();
    //void  CalcStrel();
    virtual void SetColors();
    virtual void SetYPM();
    void ShowStrelNum(int x_n, int y_n, int itextfillclr, char * outname);
    virtual void ShowNormPol();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

};




class TY_Strel_1 : public TY_Strel
{
private:
    virtual void ShowFON();
public:
    void  Show();
    TYP  GetType();
    void ShowNormPol();
};

class TY_Strel_2 : public TY_Strel
{
private:
    virtual void ShowFON();
public:
    void  Show();
    TYP  GetType();
};

class TY_Strel_3 : public TY_Strel
{
private:
    virtual void ShowFON();
public:
    void  Show();
    TYP  GetType();
};

class TY_Strel_4 : public TY_Strel
{
private:
    virtual void ShowFON();
public:
    void  Show();
    TYP  GetType();
};

class TY_Strel_5 : public TY_Strel
{
private:
    int cntP1;
    TPoint P1[10];
    int clr1[10];
    virtual void ShowFON();
public:
    TY_Strel_5();
    virtual void SetColors();
    void  Show();
    TYP  GetType();
};

class TY_Strel_6 : public TY_Strel_1
{
private:
public:
    virtual void SetYPM();
    TYP  GetType();
    virtual void ChangeMarkerXY(int iMarker,int aX,int aY);
    virtual int GetMarkerCount(){return 4;};
    virtual void GetMarkerPoint(int iMarker,int &aX,int &aY);
};



const _strel_d_x_t = 2; // размер щели по x
const _strel_d_y_t = 2; // размер щели по y




#endif
