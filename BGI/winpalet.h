#ifndef WINPALET_H
#define WINPALET_H
//----------------------------------------------------------------------------
//  Copyright GTSS c 2000. All Rights Reserved.
//----------------------------------------------------------------------------
#ifndef QT_ANTLIB
#include <windows.h>
#endif
#include <systypes.h>

/*
class TBgiPalette
{
    LPLOGPALETTE lpLogPal;
    HPALETTE     m_Palette;

public:

    __fastcall TBgiPalette();
    __fastcall ~TBgiPalette();

    HPALETTE      __fastcall Handle() {return m_Palette;}
    LPLOGPALETTE  __fastcall LogPal(void)  {return lpLogPal;}
    COLORREF      __fastcall Color(int indx);
};

extern TBgiPalette*  BgiPalette;
*/
struct  TDAC {
    PALETTEENTRY pe[2];
    bool         idx;
    int          dt;
    COLORREF     Clr[2];
};

extern TDAC  DAC[32];
extern char  DACCfgFileName[256];

int     Get_DAC(void);
void    Update_DAC(void);
bool    IsClrMig(int Clr);
void    SwapDACColor();
COLORREF  BgiDacColor(unsigned int c);

//----------------------------------------------------------------------------
#endif
