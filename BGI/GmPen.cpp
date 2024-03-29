#include "GmPen.h"

#include "aheaders_cpp.h"

#include <limits.h>
#include <windows.h>
#include <wingdi.h>

/* TODO : !!! Cashing pens */
extern bool NoGmPen;
__fastcall TGmPen::TGmPen(TCanvas* cnv)
    : canvas(cnv)
{
  if (NoGmPen)
    return;
  LOGPEN logpen;
  int err = GetObject(canvas->Pen->Handle, sizeof(logpen), &logpen);

  static LOGBRUSH lplb;
  lplb.lbStyle = BS_SOLID;
  lplb.lbColor = logpen.lopnColor;
  lplb.lbHatch = HS_BDIAGONAL;

  pen = ::ExtCreatePen(
      // DWORD dwPenStyle, // pen style
      PS_GEOMETRIC | logpen.lopnStyle, //|PS_ENDCAP_FLAT|PS_JOIN_BEVEL,
      // DWORD dwWidth,    // pen width
      1, // logpen.lopnWidth,
      // const LOGBRUSH *lplb, // pointer to structure for brush attributes
      &lplb,
      // DWORD dwStyleCount,   // length of array containing custom style bits
      0,
      // const DWORD *lpStyle  // optional array of custom style bits
      NULL);

  old = ::SelectObject(
      canvas->Handle, //  HDC hdc,           // handle of device context
      pen             //  HGDIOBJ hgdiobj   // handle of object
  );

#ifdef _DEBUG
  /*
  ::OutputDebugString(
      IntToStr((int)canvas->Pen->Handle).c_str()
  );
  */
#endif
}

__fastcall TGmPen::~TGmPen()
{
  if (NoGmPen)
    return;
  ::SelectObject(canvas->Handle, old);
  ::DeleteObject(pen);
}
