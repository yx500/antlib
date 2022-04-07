#ifndef WINBGI_GDP_H
#define WINBGI_GDP_H

//  Copyright GTSS c 2006. All Rights Reserved.

#include "winbgi_core.h"

#include <windows.h>

//Интерфейс для использования в компонентах +++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RECT& ClearBgiCoverRect(void);
RECT& GetBgiCoverRect(void);
void __fastcall trace_bgi_coord(int x, int y);
inline void __fastcall tracecoord(int x, int y)
{
  return trace_bgi_coord(x, y);
}

inline int TextWidth(const char* str)
{
  return textwidth(str);
}
inline int TextHeight(const char* str)
{
  return textheight(str);
}
inline void SetTextStyle(unsigned int font, int direction = 0, int charsize = 0)
{
  settextstyle(font, direction, charsize);
}
// inline void OutTextXY(int x, int y, const char* str){  return outtextxy(x, y, str); }
void OutTextXY(int x, int y, char* str);

void _SetTextSize(int charsize);
void _SetText(unsigned int font, int d1, int d2);
void DrawText(int x, int y, int tw, int th, char* str);

// VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD
namespace Graphics {
class TCanvas;
};

class WinBgiDC
{
  int SaveIndex;
  void Open(Graphics::TCanvas* pdc);
  void Close();

public:
  WinBgiDC(Graphics::TCanvas* pdc, int gdp = 0);
  // WinBgiDC(HDC hdc);
  WinBgiDC(void* hdc, int gdp = 0);
  ~WinBgiDC(void);
};
// VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD

#include "winbgi_xlam.h"
#include "winfonts.h"

#endif
