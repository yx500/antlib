
#include "F.h"

#include "APch.h"
#include "aheaders_cpp.h"

int Clr_lev(int clr)
{
  if (clr == LIN)
    return 1;
  if (clr == COLOR_S)
    return 2;
  if (clr == COLOR_B)
    return 4;
  if (clr == COLOR_SET)
    return 3;
  if (clr == BIRUZOVIJ)
    return 5;
  return 0;
}

int Lev_clr(int lev)
{
  switch (lev) {
  case 1:
    return LIN;
  case 2:
    return COLOR_S;
  case 3:
    return COLOR_SET;
  case 4:
    return COLOR_B;
  case 5:
    return BIRUZOVIJ;
  }
  return 0;
}

int Clr_Set(int tst)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  if (!tst)
    return COLOR_F_P;
  else
    return COLOR_B;
}

int Clr_Set2(int tst, int tst2)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  if (tst)
    return COLOR_B;
  else if (!tst2)
    return COLOR_F_P;
  else
    return COLOR_SET;
}

int Clr_SetPl(int tst, int tst2)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  //  if(tst2){
  if (!tst)
    return COLOR_F_P;
  else
    return COLOR_B;
  /*
  }else{
  if(!tst)  return COLOR_F_P;
  else return COLOR_B;
  }
  */
}

int Clr_SetC(int tst, int M, int imp1, int imp2)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  if (!M) {
    if (tst) {
      //  !!!  вот они миг сигналы
      if (imp1)
        return ZEL_MIG;
      return COLOR_SVZ;
    } else {
      //              if(imp1)  return 12;
      return FON;
    }
  } else {
    if (tst) {
      if (imp1)
        return SV_MIG;
      else
        return TXT;
    } else {
      if (imp1)
        return COLOR_PSV;
      else
        return FON;
    }
  }
}

int Clr_SetC(int tst, char* nam)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  int M = 0;
  if (

      (nam != 0) && ((nam[0] == 'm') ||
                     (nam[0] == 'м') ||
                     (nam[0] == 'М') ||
                     (nam[0] == 'M')))
    M = 1;

  if (!M)
    if (tst)
      return COLOR_SVZ;
    else
      return FON;
  else if (tst) {
    int f = 0;
    f++;
    return TXT;
  } else
    return FON;
}

int Clr_SetN(int tst)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  if (tst)
    return COLOR_B;
  else
    return COLOR_SET;
}

int Clr_SetK(int tst)
{
  if (tst == 33)
    return BIRUZOVIJ;
  if (tst == 31)
    return FON;
  //  if(tst< 0 ) return BIRUZOVIJ;
  if (!tst)
    return LIN;
  else
    return COLOR_SET;
}
