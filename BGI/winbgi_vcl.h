#ifndef WINBGI_VCL_H
#define WINBGI_VCL_H

#include "aheaders_h.h"
#include "bgi.h"
#include "winpalet.h"

#include <graphics.hpp>

class WinBgiDC
{
  HPALETTE pOldPalette;
  void Open(TCanvas* pdc);
  void Close();

public:
  int SaveIndex;
  WinBgiDC(TCanvas* pdc);
  WinBgiDC(HDC hdc);
  WinBgiDC(TCanvas* pdc, int flag);

  ~WinBgiDC(void);
  void SwapDACColor();
};

TColor BgiColor(unsigned int c);
TCanvas* BgiCanvas(void);

#endif // WINBGI_VCL_H
