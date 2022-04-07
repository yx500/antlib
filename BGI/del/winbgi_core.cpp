#include "winbgi_core.h"

#include <systypes.h>
#include <windows.h>

#if (__BORLANDC__ >= 0x530)
#pragma package(smart_init)
#endif

//*****для определения координант рисуемого компонента
static RECT TraceRect;
void __fastcall trace_bgi_coord(int x, int y)
{
  if (x < TraceRect.left)
    TraceRect.left = x;
  if (y < TraceRect.top)
    TraceRect.top = y;
  if (x > TraceRect.right)
    TraceRect.right = x;
  if (y > TraceRect.bottom)
    TraceRect.bottom = y;
}
void __fastcall trace_bgi_coord(const POINT* Points, int PointsCount)
{
  for (int i = 0; i < PointsCount; i++)
    trace_bgi_coord(Points[i].x, Points[i].y);
}
RECT& ClearBgiCoverRect(void)
{
  ::SetRect(&TraceRect, 2147483647, 2147483647, -2147483647, -2147483647);
  return TraceRect;
}
RECT& GetBgiCoverRect(void)
{
  return TraceRect;
}
//******************************************************

#define FunBgi_NotUsing() throw "Bgi Function is not allowed."

void setbkcolor(int color) //> not using
{
  FunBgi_NotUsing();
}

unsigned getpixel(int x, int y) //> not using
{
  FunBgi_NotUsing();
}

void putpixel(int x, int y, int color) //> not using
{
  FunBgi_NotUsing();
}

void gettextsettings(struct textsettingstype* texttypeinfo) //> not using
{
  FunBgi_NotUsing();
}

void floodfill(int x, int y, int border) //> not using
{
  FunBgi_NotUsing();
}

void lineto(int x, int y) //> not using
{
  FunBgi_NotUsing();
}

void ellipse(int x, int y, int start_angle, int end_angle, int rx, int ry) //> not using
{
  FunBgi_NotUsing();
}

void getfillsettings(fillsettingstype* fs)
{
  FunBgi_NotUsing();
}

void setfillpattern(const char* upattern, int color) //> not using
{
  FunBgi_NotUsing();
}

void setaspectratio(int ax, int ay) //> not using
{
  FunBgi_NotUsing();
}

void getaspectratio(int* ax, int* ay) //> not using
{
  FunBgi_NotUsing();
}

int getx() //> not using
{
  FunBgi_NotUsing();
}

int gety() //> not using
{
  FunBgi_NotUsing();
}

void initgraph(int* device, int* mode, const char* p) //> not using
{
  FunBgi_NotUsing();
}

void getimage(int left, int top, int right, int bottom, void* bitmap)
{
  FunBgi_NotUsing();
}

unsigned imagesize(int left, int top, int right, int bottom)
{
  FunBgi_NotUsing();
}

void putimage(int left, int top, const void* bitmap, int op)
{
  FunBgi_NotUsing();
}

void cleardevice(void)
{
  FunBgi_NotUsing();
}

void clearviewport(void)
{
  FunBgi_NotUsing();
}

void closegraph(void)
{
  FunBgi_NotUsing();
}

int installuserfont(const char* n)
{
  FunBgi_NotUsing();
}

void linerel(int dx, int dy)
{
  FunBgi_NotUsing();
}

// функции для работы с EMF
// загружает emf в нечто
// для vcl это HENHMETAFILE
void __fastcall tracecoord(int x, int y);
extern HDC _gdp_hdc;
void* EMF_Load(char* lpszMetaFile)
{
  return GetEnhMetaFile(lpszMetaFile);
}
void EMF_Delete(void* emf)
{
  DeleteEnhMetaFile((HENHMETAFILE)emf);
}
bool EMF_Show(
    void* emf,
    const RECT* lpRect // pointer to bounding rectangle
)
{
  tracecoord(lpRect->left, lpRect->top);
  tracecoord(lpRect->left, lpRect->bottom);
  tracecoord(lpRect->right, lpRect->top);
  tracecoord(lpRect->right, lpRect->bottom);

  if (_gdp_hdc == NULL)
    return true;
  HENHMETAFILE hemf = (HENHMETAFILE)emf; // handle to an enhanced metafile
  return PlayEnhMetaFile(
      _gdp_hdc, // handle to a device context
      hemf,     // handle to an enhanced metafile
      lpRect    // pointer to bounding rectangle
  );
}
