
#include "Line.h"

#include "APch.h"
#include "Scrin.h"
#include "Str_fun.h"
#include "aheaders_cpp.h"
#include "propmap.h"

#include <math.h>

void Lini::Set()
{
  AComp::Set();
  mas_y = MEM.Nomer;
  // strncpy(name,MEM.name,7);
  cp866_to_cp1251_buff(MEM.name, name, 7);
}

static String _LiniPropName[2] = {
    "öôNomer", // 0
    "ñìÈÌß"    // 1
};
void Lini::SetPropMap(TPropMap& m)
{
  AComp::SetPropMap(m);
  mas_y = m.geti(_LiniPropName[0]);
  strncpy(name, m.get(_LiniPropName[1]).c_str(), sizeof(name));
}
void Lini::GetPropMap(TPropMap& m)
{
  AComp::GetPropMap(m);
  m.put(_LiniPropName[0], mas_y, 0);
  m.put(_LiniPropName[1], name);
}

void Lini::Get()
{
  AComp::Get();
  MEM.impuls_busi = 0;
  MEM.impuls_plus = 0;
  MEM.impuls_mnus = 0;
  MEM.impuls_kzm = 0;
  MEM.Nomer = mas_y;
  memset(MEM.name, 0, 16);
  cp1251_to_cp866_buff(name, MEM.name, 7);
  // strncpy(MEM.name,name,16);
}

const char* Lini::GetName()
{
  return name;
}

void Lini::UpdateState()
{

  StateChanged = false;
}
// void Lini::Show(){ ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);}
void Lini::Go()
{
  bool b = StateChanged;
  UpdateState();
  if (b || StateChanged)
    Show();
  StateChanged = false;
}
void Lini::Show()
{
  x = X * MUL_X + _X_;
  y = Y * MUL_Y + _Y_;
}

void Kriv::Show()
{
  Lini::Show();
  clr = LIN;
  int y2;
  y2 = y - _Y_;
  y2 = y2 / MUL_Y;
  int sh = 1;
  if (masy != 0)
    sh = masy;
  if (AO->LUDOCHKA == 1)
    sh = sh * 2;

  setcolor(C_D);
  setlinestyle(SOLID_LINE, 0, sh);
  if (name[0] == 'Ê') {
    setcolor(KRA);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'ß') {
    setcolor(TIME_FON);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Ý') {
    setcolor(LIN_W);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Æ') {
    setcolor(GELT);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Ç') {
    setcolor(ZEL);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Á') {
    setcolor(TXT);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Ï') {
    setcolor(ZEL);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Ä') {
    setcolor(GELT);
    // setlinestyle(SOLID_LINE,0,sh);
  }
  if (name[0] == 'Ù') {
    setcolor(C_D);
    setlinestyle(DOTTED_LINE, 0, 1);
  }
  if (name[0] != '#') {
    line(x, y, mas * MUL_X + _X_, mas_y * MUL_Y + _Y_);

    /*
    if(LUDOCHKA==0){
        if(name[0]!='™'){
            if(x==mas*MUL_X+_X_)
              line(x+1,y,mas*MUL_X+_X_+1,mas_y*MUL_Y+_Y_);
            else
              line(x,y+1,mas*MUL_X+_X_,mas_y*MUL_Y+_Y_+1);
         }
    }
    #endif */
  } else {
    if (CurrentPicture == LT)
      //         line(x,this->y+700,mas*MUL_X+_X_,mas_y+700);
      if (DNC_DC != c_DC)
        line(x, this->y + 650, mas * MUL_X + _X_, mas_y + 650);
      else
        line(x, this->y + 650 - MUL_Y * 3, mas * MUL_X + _X_, mas_y + 650 - MUL_Y * 3);
  }
  setlinestyle(SOLID_LINE, 0, 1);
}
TYP Kriv::GetType()
{
  return KRIV;
}
UNIT Kriv::GetUnit()
{
  return CIFR;
}
// UNIT Kriv::GetUnit(){return NITK;}

void Tupic::Show()
{
  Lini::Show();
  int s;
  int d;
  s = sh_y * 2 / 3 + 1;
  setcolor(C_D);
  clr = LIN;

  if (name[1] == 'Ê') {
    setcolor(KRA);
    //       setlinestyle(SOLID_LINE,0,3);
  }
  if (name[1] == 'Æ') {
    setcolor(GELT);
    //      setlinestyle(SOLID_LINE,0,3);
  }
  if (name[1] == 'Ç') {
    setcolor(ZEL);
    //      setlinestyle(SOLID_LINE,0,3);
  }
  if (name[1] == 'Á') {
    setcolor(TXT);
    //      setlinestyle(SOLID_LINE,0,3);
  }

  line(x, y, mas * MUL_X + _X_, mas_y * MUL_Y + _Y_);

  if (name[0] == 'é') {
    //      line(x,y,x+s,y);
    line(x, y - s, x + s, y);
    line(x, y + s, x + s, y);
    return;
  }
  if (name[0] == 'ö') {
    //     line(x,y,x+s,y);
    line(x, y, x + s, y + s);
    line(x, y, x + s, y - s);
    return;
  }
  if (name[0] == 'ó') {
    //      line(x,y,x,y-s);
    line(x - s, y, x, y - s);
    line(x + s, y, x, y - s);
    return;
  }
  if (name[0] == 'ê') {
    //      line(x,y,x,y-s);
    line(x - s, y - s, x, y);
    line(x, y, x + s, y - s);
    return;
  }

  if (name[0] == 'Ò') {
    //      setcolor(C_D);
    circle(x, y, sh_y + sh_y / 2);
    circle(x, y + sh_y + sh_y / 2, sh_y + sh_y / 2);
    return;
  }
  if (name[0] == 'Ä') {
    //       setcolor(C_D);
    circle(x, y, sh_y + sh_y / 2);
    circle(x + sh_y + sh_y / 2, y + sh_y / 2 + sh_y / 4, sh_y + sh_y / 2);
    circle(x, y + sh_y + sh_y / 2, sh_y + sh_y / 2);
    return;
  }
  if (x > (mas * MUL_X + _X_))
    d = sh_y / 3;
  else
    d = -sh_y / 3;
  line(x, y - s, x, y + s);
  line(x, y - s, x + d, y - s);
  line(x, y + s, x + d, y + s);
}
TYP Tupic::GetType()
{
  return TUPIC;
}
UNIT Tupic::GetUnit()
{
  return NITK;
}

void Over::GetPropMap(TPropMap& m)
{
  Lini::GetPropMap(m);
  m.put("ëãÏåøåõîäíûé", bPeshehod, 0);
}
void Over::SetPropMap(TPropMap& m)
{
  Lini::SetPropMap(m);
  bPeshehod = m.geti("ëãÏåøåõîäíûé");
}

void Over::Show()
{
  Lini::Show();
  int xx = x;

  if ((AO->TypPere == 32) || (AO->TypPere == 321))
    return;
  xx = x - MUL_X / 3;
  int x2 = x + MUL_X / 3;
  //  ‡„…‘œ ‘„…‹€› ˆ‡Œ……ˆŸ „‹Ÿ 2•2
  int y2;
  if (AO->_2X2_)
    y2 = y + (10 + mas) * MUL_Y;
  else
    y2 = y + (5 + mas) * MUL_Y;
  int s = MUL_Y / 3;
  clr = LIN;
  setcolor(C_D);
  if (bPeshehod) {
    line(xx, y, xx, y2);
    line(x2, y, x2, y2);
    int d = MUL_Y / 2;
    if (y2 < y)
      d = -MUL_Y / 2;
    for (int yy = y; yy <= y2; yy += d)
      line(xx, yy, x2, yy);
    line(xx, y, x2, y);
    line(xx, y2, x2, y2);
  } else {
    line(xx, y, xx, y2);
    line(xx - s, y2 + s, xx, y2);
    line(xx - s, y - s, xx, y);
    line(x2, y, x2, y2);
    line(x2 + s, y - s, x2, y);
    line(x2 + s, y2 + s, x2, y2);
  }
}
TYP Over::GetType()
{
  return OVER;
}
UNIT Over::GetUnit()
{
  return STAT;
}

void Nomer::Show()
{
  Lini::Show();
  int xx = x;
  int yy = y;
  clr = LIN;
  if (MUL_Y < 2)
    return;
  if ((MUL_Y < AO->_NAZVA_) && (CurrentPicture == BG))
    return;
  _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
  setcolor(BLUE_m);
  switch (mas) {
  case 1:
    _SetTextSize(-sh_y * 2 + 2);
    OutTextXY(xx, yy + MUL_Y / 2, name);
    _SetTextSize(1);
    break;
  default:
    OutTextXY(xx, yy + MUL_Y / 2, name);
  }
  //>   _SetTextStyle(F_DEFAULT);
}
TYP Nomer::GetType()
{
  return NOMER;
}
UNIT Nomer::GetUnit()
{
  return CIFR;
}

void Stik::Show()
{
  Lini::Show();
  int xx = x;
  int yy = y;
  int st_st = 2;
  int sd;
  int sd2 = 0;
  if (((ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
      ((ExtPriz.NoShowStan == 1) && (CurrentPicture == LT)))
    return;
  // if ((ExtPriz.NoShowExtInfo==1)&&(!bShowExtInfo))   return;
  setcolor(BLUE_m);
  /* äîïîëíèòåëüíûå ïðèïàðû !   */
  if (name[0] == '#') {
    if (CurrentPicture == LT) {
      xx += mas;
      yy += masy;
      st_st += sh_y / 4 + 1;
      st_st += masx2;
      if (name[1] == '+') {
        line(xx, yy - st_st, xx, yy + st_st);
        line(xx - st_st, yy, xx + st_st, yy);
      } else if (name[1] == '-') {
        line(xx - st_st, yy, xx + st_st, yy);
      } else if (name[1] == '|') {
        line(xx, yy - st_st, xx, yy + st_st);
      } else {
        circle(xx, yy, st_st);
      }
    }
    return;
  }
  st_st += sh_y / 2;

  if (name[1] == '*')
    sd2 = (sh - sh_y) / 2;
  if (CurrentPicture == LT)
    sd = 2;
  else
    sd = -1;

  if (name[0] == '-') {
    if (CurrentPicture == BG) {
      circle(xx, yy + sd2, st_st + sd + 1);
    } else {
      circle(xx, yy + sd2, st_st + sd);
    }
  }
  if (name[1] == '*')
    line(xx - st_st, yy + sd2, xx + st_st + 1, yy + sd2);
  else {
    int h = sh_y + 1; //âûñîòà áëêó÷àñòêà
    int dh1 = h / 2;
    int dh2 = h / 2;
    int f = h % 2;
    if (f == 0)
      dh1--;
    // ñàì ñòûê
    line(xx, yy - dh1 - 2, xx, yy + dh2 + 2);
    setcolor(FON);
    // çàçîðû
    line(xx - 1, yy - dh1, xx - 1, yy + dh2);
    line(xx + 1, yy - dh1, xx + 1, yy + dh2);
    if (CurrentPicture == BG) { // ó÷àñòîê
      setcolor(C_D);
      line(xx - 2, yy - dh1, xx - 2, yy + dh2); // Ñëåâà Ãðàíèöà
      line(xx + 2, yy - dh1, xx + 2, yy + dh2); // Ñïðàâà Ãðàíèöà
    } else {
      line(xx - 2, yy - dh1, xx - 2, yy + dh2); // Ñëåâ
      line(xx + 2, yy - dh1, xx + 2, yy + dh2); // Ñïðàâà çàçàîð
      setcolor(C_D);
      line(xx - 3, yy - dh1, xx - 3, yy + dh2); // Ñëåâà Ãðàíèöà
      line(xx + 3, yy - dh1, xx + 3, yy + dh2); // Ñïðàâà Ãðàíèöà
    }
  }
}
TYP Stik::GetType()
{
  return STIK;
}
UNIT Stik::GetUnit()
{
  return CIFR;
}

void Elektr::Show()
{
  Lini::Show();
  int xx = x;
  int yy = y;
  int st_st = sh_y * 2;
  int len = st_st + st_st / 2;
  setcolor(BLUE_m);
  line(xx, yy + st_st + 1, xx + len, yy - st_st);
  line(xx + len - 3, yy - st_st + 1, xx + len, yy - st_st);
  line(xx + len, yy - st_st + 4, xx + len, yy - st_st);
}
TYP Elektr::GetType()
{
  return ELEKTR;
}
UNIT Elektr::GetUnit()
{
  return CIFR;
}

Platf::Platf()
{
  bInGrid = false;
}
void Platf::SetPropMap(TPropMap& m)
{
  Lini::SetPropMap(m);
  bInGrid = m.geti("ëãInGrid");
}
void Platf::GetPropMap(TPropMap& m)
{
  Lini::GetPropMap(m);
  m.put("ëãInGrid", bInGrid, 0);
}

void Platf::Show()
{
  Lini::Show();
  if (CurrentPicture == BG)
    return;
  // if (!AO->NIKOLA) {
  int yyy = y + masx2 + (sh - sh_y) / 2;
  int st_st = (sh - sh_y * 6) / 2;
  int len = (WAY_X + mas) * MUL_X;
  st_st += masy / 2;

  int clr1 = LIN;
  int clr2 = C_D;
  if ((mas_y > 0) && (AO->bDopPriznak)) {
    clr1 = mas_y;
    clr2 = mas_y;
  }
  setcolor(BLUE_m);

  setfillstyle(1, FON);
  if (!bInGrid) {
    setcolor(clr1);
    line(x, yyy - st_st, x + len, yyy - st_st);
    line(x + len, yyy - st_st, x + len, yyy + st_st);
    setcolor(clr2);
    line(x, yyy + st_st, x + len, yyy + st_st);
    line(x, yyy - st_st, x, yyy + st_st);
  } else {
    st_st = masy * MUL_Y / 4 + masx2;
    int xx = 0;
    setcolor(clr1);
    x = X * MUL_X / 2 + _X_;
    y = Y * MUL_Y / 2 + _Y_;
    len = mas * MUL_X / 2;
    line(x + xx, y - st_st, x + len - xx, y - st_st);
    line(x + len - xx, y - st_st, x + len - xx, y + st_st);
    setcolor(clr2);
    line(x + xx, y + st_st, x + len - xx, y + st_st);
    line(x + xx, y - st_st, x + xx, y + st_st);
  }

  /*} else {
      int len;
      len = (STREL_X / 2 + mas) * MUL_X;
      setcolor(BLUE_m);
      setfillstyle(1, LIN_W);
      int d = sh_y / 2;
      int k = 2;
      y = y - sh_y / 2;
      barx(x , y - k - d   , x + len , y - k);
      barx(x , y + sh_y + k    , x + len , y + sh_y + k  + d);
  }*/
}
TYP Platf::GetType()
{
  return PLATF;
}
UNIT Platf::GetUnit()
{
  return CIFR;
}

// typedef Text* PText;

void Lini2::Set()
{
  AComp::Set();
}

void Lini2::Get()
{
  AComp::Get();
}

static String _Lini2PropName[18] = {
    "ñìÈÌß",       // 0
    "öôÑïåöÒèï",   // 1
    "öôÖâåò",      // 2
    "öôÑòèëü",     // 3
    "öôÒîëùèíàÑò", // 4
    "öôÒîëùèíàÓ÷", // 5
    "öôÎêîíå÷í1",  // 6
    "öôÎêîíå÷í2",  // 7
    "öôÑäâèã1XÑò", // 8
    "öôÑäâèã2XÑò", // 9
    "öôÑäâèã1YÑò", // 11
    "öôÑäâèã2YÑò", // 12
    "öôÑäâèã1XÓ÷", // 10
    "öôÑäâèã2XÓ÷", // 14
    "öôÑäâèã1YÓ÷", // 13
    "öôÑäâèã2YÓ÷", // 15
    "ëãÒåíü",      // 16
    "öôÒåíüÖâåò"   // 17
};
void Lini2::SetPropMap(TPropMap& m)
{
  AComp::SetPropMap(m);
  int _n = 0;
  strncpy(name, m.get(_Lini2PropName[_n++]).c_str(), sizeof(name));
  SpecTip = m.geti(_Lini2PropName[_n++]);
  Color = m.geti(_Lini2PropName[_n++]);
  PenS = m.geti(_Lini2PropName[_n++]);
  PenW[LT] = m.geti(_Lini2PropName[_n++]);
  PenW[BG] = m.geti(_Lini2PropName[_n++]);
  EndLine[0] = m.geti(_Lini2PropName[_n++]);
  EndLine[1] = m.geti(_Lini2PropName[_n++]);
  SdvigX[0][LT] = m.geti(_Lini2PropName[_n++]);
  SdvigX[1][LT] = m.geti(_Lini2PropName[_n++]);
  SdvigY[0][LT] = m.geti(_Lini2PropName[_n++]);
  SdvigY[1][LT] = m.geti(_Lini2PropName[_n++]);
  SdvigX[0][BG] = m.geti(_Lini2PropName[_n++]);
  SdvigX[1][BG] = m.geti(_Lini2PropName[_n++]);
  SdvigY[0][BG] = m.geti(_Lini2PropName[_n++]);
  SdvigY[1][BG] = m.geti(_Lini2PropName[_n++]);
  bShadow = m.geti(_Lini2PropName[_n++]);
  clrShadow = m.geti(_Lini2PropName[_n++]);
}
void Lini2::GetPropMap(TPropMap& m)
{
  AComp::GetPropMap(m);
  int _n = 0;
  m.put(_Lini2PropName[_n++], name);
  m.put(_Lini2PropName[_n++], SpecTip, 0);
  m.put(_Lini2PropName[_n++], Color, 0);
  m.put(_Lini2PropName[_n++], PenS, 0);
  m.put(_Lini2PropName[_n++], PenW[LT], 0);
  m.put(_Lini2PropName[_n++], PenW[BG], 0);
  m.put(_Lini2PropName[_n++], EndLine[0], 0);
  m.put(_Lini2PropName[_n++], EndLine[1], 0);
  m.put(_Lini2PropName[_n++], SdvigX[0][LT], 0);
  m.put(_Lini2PropName[_n++], SdvigX[1][LT], 0);
  m.put(_Lini2PropName[_n++], SdvigY[0][LT], 0);
  m.put(_Lini2PropName[_n++], SdvigY[1][LT], 0);
  m.put(_Lini2PropName[_n++], SdvigX[0][BG], 0);
  m.put(_Lini2PropName[_n++], SdvigX[1][BG], 0);
  m.put(_Lini2PropName[_n++], SdvigY[0][BG], 0);
  m.put(_Lini2PropName[_n++], SdvigY[1][BG], 0);
  m.put(_Lini2PropName[_n++], bShadow, 0);
  m.put(_Lini2PropName[_n++], clrShadow, 0);
}

const char* Lini2::GetName()
{
  return name;
}

void Lini2::UpdateState()
{
  int rimpuls_busi = f(impuls_busi);
  StateChanged = (rimpuls_busi != fimpuls_busi);
  fimpuls_busi = rimpuls_busi;
}
// void Lini::Show(){ ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);}
void Lini2::Go()
{
  bool b = StateChanged;
  UpdateState();
  if (b || StateChanged)
    Show();
  StateChanged = false;
}
TYP Lini2::GetType()
{
  return LINI2;
}
UNIT Lini2::GetUnit()
{
  return NITK;
}

Lini2::Lini2()
{
  mas = 2;
  masy = 1;
  PenW[LT] = 1;
  PenW[BG] = 1;
  PenS = 0;
  Color = 0;
  SpecTip = 0;
  memset(EndLine, 0, sizeof(EndLine));
  memset(SdvigX, 0, sizeof(SdvigX));
  memset(SdvigY, 0, sizeof(SdvigY));
  clrShadow = FON1;
  bShadow = false;
}

void __fastcall ShowArrow(int X1, int Y1, int X2, int Y2)
{
  double l = 2;
  double L = 4;
  double al;
  if ((X2 - X1) == 0) {
    if (Y1 > Y2)
      al = M_PI_2;
    else
      al = -M_PI_2;
  } else
    al = atan(1. * (Y1 - Y2) / (X2 - X1));
  if (X2 < X1)
    al += M_PI;
  double xc = X2 - L * cos(al);
  double yc = Y2 + L * sin(al);
  double x1 = xc + l * cos(al + M_PI_2);
  double y1 = yc - l * sin(al + M_PI_2);

  double x2 = xc + l * cos(al - M_PI_2);
  double y2 = yc - l * sin(al - M_PI_2);
  line(X2, Y2, x1, y1);
  line(X2, Y2, x2, y2);
}

void otstupshadow(int sd, int dd1, int dd2, int& d1, int& d2)
{
  switch (sd) {
  case 0:
    d1 = 0;
    d2 = 0;
    break;
  case 1:
    d1 = dd1;
    d2 = dd2;
    break;
  case 2:
    d1 = -dd1;
    d2 = -dd2;
    break;
  case 3:
    d1 = dd1;
    d2 = -dd2;
    break;
  case 4:
    d1 = -dd1;
    d2 = dd2;
    break;
  case 5:
    d1 = -dd2;
    d2 = -dd1;
    break;
  case 6:
    d1 = dd2;
    d2 = -dd1;
    break;
  case 7:
    d1 = -dd2;
    d2 = dd1;
    break;
  }
}
void __fastcall ShowShadow(int X1, int Y1, int X2, int Y2, int w, int clrShadow, int sd1, int sd2)
{
  int dx[2];
  int dy[2];
  int A;
  // if (X1>X2){A=X1;X1=X2;X2=A;}
  // if (Y1>Y2){A=Y1;Y1=Y2;Y2=A;}
  switch (w) {
  case 0:
  case 1:
    dx[0] = 1;
    dx[1] = 1;
    dy[0] = 1;
    dy[1] = 1;
    break;
  case 2:
    dx[0] = 1;
    dx[1] = 2;
    dy[0] = 1;
    dy[1] = 2;
    break;
  case 3:
    dx[0] = 2;
    dx[1] = 2;
    dy[0] = 2;
    dy[1] = 2;
    break;
  case 4:
    dx[0] = 2;
    dx[1] = 3;
    dy[0] = 2;
    dy[1] = 3;
    break;
  case 5:
    dx[0] = 3;
    dx[1] = 3;
    dy[0] = 3;
    dy[1] = 3;
    break;
  default:
    dx[0] = w / 2;
    dx[1] = w / 2;
    dy[0] = w / 2;
    dy[1] = w / 2;
  }

  setcolor(clrShadow);
  int d1[2];
  int d2[2];
  if (X1 == X2) {
    otstupshadow(sd1, dy[0], dy[1], d1[0], d1[1]);
    otstupshadow(sd2, dy[0], dy[1], d2[0], d2[1]);
    line(X1 + dx[0], Y1 + d1[0], X2 + dx[0], Y2 - d2[0]);
    line(X1 - dx[1], Y1 + d1[1], X2 - dx[1], Y2 - d2[1]);
  } else if (Y1 == Y2) {
    otstupshadow(sd1, dx[0], dx[1], d1[0], d1[1]);
    otstupshadow(sd2, dx[0], dx[1], d2[0], d2[1]);
    line(X1 + d1[0], Y1 + dy[0], X2 - d2[0], Y2 + dy[0]);
    line(X1 + d1[1], Y1 - dy[1], X2 - d2[1], Y2 - dy[1]);
  } else {
    if (abs(X2 - X1) > abs(Y2 - Y1)) {
      line(X1, Y1 + dy[0], X2, Y2 + dy[0]);
      line(X1, Y1 - dy[1], X2, Y2 - dy[1]);
    } else {
      line(X1 + dx[0], Y1, X2 + dx[0], Y2);
      line(X1 - dx[1], Y1, X2 - dx[1], Y2);
    }
  }
}

void __fastcall DrawA(int x, int y, int n)
{
  int s = sh_y * 2 / 3 + 1;
  if (n == 11) {
    line(x, y - s, x + s, y);
    line(x, y + s, x + s, y);
  }
  if (n == 12) {
    line(x, y, x + s, y + s);
    line(x, y, x + s, y - s);
  }
  if (n == 13) {
    line(x - s, y, x, y - s);
    line(x + s, y, x, y - s);
  }
  if (n == 14) {
    line(x - s, y - s, x, y);
    line(x, y, x + s, y - s);
  }
  if (n == 15) {
    circle(x, y, sh_y + sh_y / 2);
    circle(x, y + sh_y + sh_y / 2, sh_y + sh_y / 2);
  }
  if (n == 16) {
    circle(x, y, sh_y + sh_y / 2);
    circle(x + sh_y + sh_y / 2, y + sh_y / 2 + sh_y / 4, sh_y + sh_y / 2);
    circle(x, y + sh_y + sh_y / 2, sh_y + sh_y / 2);
  }
  if (n == 17) {
    int d = -sh_y / 3;
    line(x, y - s, x, y + s);
    line(x, y - s, x + d, y - s);
    line(x, y + s, x + d, y + s);
  }
  if (n == 18) {
    int d = +sh_y / 3;
    line(x, y - s, x, y + s);
    line(x, y - s, x + d, y - s);
    line(x, y + s, x + d, y + s);
  }
}

void Lini2::Show()
{
  int x = X * MUL_X + _X_ + SdvigX[0][CurrentPicture];
  int y = Y * MUL_Y + _Y_ + SdvigY[0][CurrentPicture];
  int w = mas * MUL_X - SdvigX[0][CurrentPicture] + SdvigX[1][CurrentPicture];
  int h = masy * MUL_Y - SdvigY[0][CurrentPicture] + SdvigY[1][CurrentPicture];

  int xx[2];
  int yy[2];
  xx[0] = x;
  xx[1] = x + w;
  yy[0] = y;
  yy[1] = y + h;
  int _Color = Color;
  if (impuls_busi != 0) {
    if (fimpuls_busi == 0)
      _Color = FON1;
  }
  if (SpecTip == 1) {
    setfillstyle(EMPTY_FILL, _Color);

    TPoint P1[4] = {TPoint(xx[0], yy[0] - PenW[CurrentPicture]), TPoint(xx[1], yy[1] - PenW[CurrentPicture]), TPoint(xx[1], yy[1] + PenW[CurrentPicture]), TPoint(xx[0], yy[0] + PenW[CurrentPicture])};
    int clr1[4] = {_Color, FON, _Color, FON};
    if (EndLine[0] == 1)
      clr1[3] = _Color;
    if (EndLine[1] == 1)
      clr1[1] = _Color;
    PolyColor(FON, P1, clr1, 4);
  } else if (SpecTip == 2) {
    int sd1 = 0;
    int sd2 = 0;
    if ((EndLine[0] >= 20) && (EndLine[0] < 30))
      sd1 = EndLine[0] - 20;
    if ((EndLine[1] >= 20) && (EndLine[1] < 30))
      sd2 = EndLine[1] - 20;
    // ShowShadow(x,y,x+w,y+h,PenW[CurrentPicture],_Color,sd1,sd2);
    setlinestyle(PenS, 0, PenW[CurrentPicture]);
    // SetGradientFactor(1.1);
    setcolor(_Color);
    line(x, y, x + w, y + h);
    // SetGradientFactor(1);
  } else {
    if (bShadow) {
      int sd1 = 0;
      int sd2 = 0;
      if ((EndLine[0] >= 20) && (EndLine[0] < 30))
        sd1 = EndLine[0] - 20;
      if ((EndLine[1] >= 20) && (EndLine[1] < 30))
        sd2 = EndLine[1] - 20;
      ShowShadow(x, y, x + w, y + h, PenW[CurrentPicture], clrShadow, sd1, sd2);
    }
    setlinestyle(PenS, 0, PenW[CurrentPicture]);
    setcolor(_Color);
    setfillstyle(SOLID_FILL, FON);
    line(x, y, x + w, y + h);
  }

  for (int i = 0; i < 2; i++) {
    switch (EndLine[i]) {
    case 2:
      if (CurrentPicture == LT) {
        setfillstyle(SOLID_FILL, _Color);
        fillellipse(xx[i], yy[i], PenW[CurrentPicture] + 2, PenW[CurrentPicture] + 2);
      }
      break;
    case 3:
      ShowArrow(xx[1 - i], yy[1 - i], xx[i], yy[i]);
      break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
      if (i == 1)
        DrawA(xx[1 - i], yy[1 - i], EndLine[i]);
      break;
    }
  }
  setlinestyle(SOLID_LINE, 0, 1);
  setlinestyle(0, 0, 1);
}

void Lini2::ShowLayer(int Layer)
{
  if (Layer > 0) {
    int x = X * MUL_X + _X_ + SdvigX[0][CurrentPicture];
    int y = Y * MUL_Y + _Y_ + SdvigY[0][CurrentPicture];
    int w = mas * MUL_X - SdvigX[0][CurrentPicture] + SdvigX[1][CurrentPicture];
    int h = masy * MUL_Y - SdvigY[0][CurrentPicture] + SdvigY[1][CurrentPicture];

    int xx[2];
    int yy[2];
    xx[0] = x;
    xx[1] = x + w;
    yy[0] = y;
    yy[1] = y + h;
    int _Color = Color;
    if (impuls_busi != 0) {
      if (fimpuls_busi == 0)
        _Color = FON1;
    }
    setcolor(_Color);
    for (int i = 0; i < 2; i++) {
      switch (EndLine[i]) {
      case 2:
        if (CurrentPicture == LT) {
          setfillstyle(SOLID_FILL, _Color);
          fillellipse(xx[i], yy[i], PenW[CurrentPicture] + 2, PenW[CurrentPicture] + 2);
        }
        break;
      }
    }
    setlinestyle(SOLID_LINE, 0, 1);
    setlinestyle(0, 0, 1);
  }
}

void Lini2::ChangeMarkerXY(int iMarker, int aX, int aY)
{
  int x = (aX - _X_) / MUL_X;
  int y = (aY - _Y_) / MUL_Y;

  if (iMarker == 1) {
    int xx = X - x;
    mas += xx;
    X = x;
    int yy = Y - y;
    masy += yy;
    Y = y;
  }
  if (iMarker == 2) {
    mas += x - (X + mas);
    masy += y - (Y + masy);
  }
}
void Lini2::GetMarkerPoint(int iMarker, int& aX, int& aY)
{

  int x = X * MUL_X + _X_ + SdvigX[0][CurrentPicture];
  int y = Y * MUL_Y + _Y_ + SdvigY[0][CurrentPicture];
  int w = mas * MUL_X - SdvigX[0][CurrentPicture] + SdvigX[1][CurrentPicture];
  int h = masy * MUL_Y - SdvigY[0][CurrentPicture] + SdvigY[1][CurrentPicture];
  if (iMarker == 1) {
    aX = x;
    aY = y;
  }
  if (iMarker == 2) {
    aX = x + w;
    aY = y + h;
  }
}
