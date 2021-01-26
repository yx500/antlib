#ifndef WINBGI_GDP_XLAM_H
#define WINBGI_GDP_XLAM_H
//----------------------------------------------------------------------------

#include <graphics.hpp>
#include <systypes.h>
#include "winpalet.h"


TCanvas* BgiCanvas(void);


// используемые ф-ии
void    SwapDACColor();
int     Get_DAC(void);
void    PolyColor(int iBrushColor, const TPoint *Points, const int * iColors, const int Points_Count, int PenW = 1);
int    Draw_Ramka(int left, int top, int right, int bottom, UINT edge = BDR_RAISEDINNER, UINT grfFlags = BF_RECT);
void  roundrect(int nLeftRect,   // x-coord. of bounding rectangle's upper-left corner
                int nTopRect,  // y-coord. of bounding rectangle's upper-left corner
                int nRightRect,    // x-coord. of bounding rectangle's lower-right corner
                int nBottomRect,   // y-coord. of bounding rectangle's lower-right corner
                int nWidth,    // width of ellipse used to draw rounded corners
                int nHeight    // height of ellipse used to draw rounded corners
               );


//----------------------------------------------------------------------------
#endif
