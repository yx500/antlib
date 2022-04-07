// static.h
#ifndef STATIC_H
#define STATIC_H
#include "Comp.h"

class AText : public AComp
{
protected:
  short int x;
  short int y;
  bool bInGrid;

public:
  AText();
  virtual void Set();
  virtual void Get();
  // virtual void  Show()=0;
  virtual void Show();
  virtual void Go();
  virtual const char* GetName();
  virtual void UpdateState();

  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
};

class Name : public AText
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit()
  {
    return STAT;
  }
};

class Mess : public AText
{
public:
  int ux_allign, uy_allign, u_font, u_fontsize, u_color;

  Mess();
  void Show();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
  TYP GetType();
  UNIT GetUnit() { return STAT; }
};

class Stn : public AText
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit()
  {
    return STAT;
  }
};
class StnL : public AText
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit()
  {
    return STAT;
  }
};
class StnR : public AText
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit()
  {
    return STAT;
  }
};
typedef AText* PAText;

class Version : public AText
{
public:
  void Show();
  TYP GetType();
  UNIT GetUnit()
  {
    return STAT;
  }
};

#endif
