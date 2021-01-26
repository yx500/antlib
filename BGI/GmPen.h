#ifndef GmPenH
#define GmPenH
//----------------------------------------------------------------------------
//  Copyright GTSS c 2000. All Rights Reserved.
//----------------------------------------------------------------------------
#include <Graphics.hpp>

//---------------------------------------------------------------------------
class TGmPen
{
    HGDIOBJ old;
    HPEN    pen;
    TCanvas* canvas;
public:
    __fastcall TGmPen(TCanvas*);
    __fastcall ~TGmPen();
};
//---------------------------------------------------------------------------
#endif
