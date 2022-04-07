// line.h
#ifndef LINE_H
#define LINE_H
#include "Comp.h"

class Lini : public AComp
{
protected:
  short int x;
  short int y;

public:
  signed char mas_y;

  virtual void Set();
  void DoZon(int a)
  {
    ;
  };
  virtual void Get();
  // virtual void  ShowXY(int ix,int iy)=0;
  virtual void Show();
  virtual void Go();
  virtual TYP GetType() = 0;
  virtual UNIT GetUnit() = 0;
  virtual const char* GetName();
  Lini()
  {
    mas_y = 0;
    clr = 7;
  };
  ~Lini(){};

  virtual void UpdateState();

  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
};

class Kriv : public Lini
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit();
};

class Tupic : public Lini
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit();
};

class Over : public Lini
{
public:
  bool bPeshehod;
  Over() { bPeshehod = false; }
  void Show();
  TYP GetType();
  UNIT GetUnit();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
};

class Nomer : public Lini
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit();
};

class Stik : public Lini
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit();
};

class Elektr : public Lini
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit();
};

class Platf : public Lini
{
public:
  bool bInGrid;
  Platf();
  void Show();
  TYP GetType();
  UNIT GetUnit();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
};

typedef Lini* PLini;

class Lini2 : public AComp
{
protected:
public:
  int EndLine[2];
  int Color;
  int PenW[2];
  int PenS;
  int SpecTip;
  int SdvigX[2][2];
  int SdvigY[2][2];
  bool bShadow;
  int clrShadow;

  virtual void Set();
  virtual void Get();
  virtual void Show();
  virtual void ShowLayer(int Layer);
  virtual void Go();
  virtual TYP GetType();
  virtual UNIT GetUnit();
  virtual const char* GetName();
  Lini2();
  ~Lini2(){};

  virtual void UpdateState();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);

  virtual void ChangeMarkerXY(int iMarker, int aX, int aY);
  virtual int GetMarkerCount() { return 2; };
  virtual void GetMarkerPoint(int iMarker, int& aX, int& aY);
};

#endif
