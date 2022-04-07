#pragma hdrstop

#if (__BORLANDC__ >= 0x530)
#pragma package(smart_init)
#endif

#include <SyncObjs.hpp>
#include <graphics.hpp>
#include <iostream>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <systypes.h>
#include <windows.h>
#include <wstring.h>

//#include "..\..\vpacks\gdiplusvcl.h"

#include "auto_array_ptr.h"
#include "uImgContainer.h"
#include "vgdp.h"
#include "winbgi_gdp.h"
#include "winfonts.h"
#include "winpalet.h"

using namespace std;
using namespace Vx;
//#define  BGIDBG

extern int MaxX;
extern int MaxY;

TCanvas* dc = 0;

gdp::Graphics* graphics = 0;
int _gdp_count = 1;
HDC _gdp_hdc = 0;

class _GdpGraphics_
{
public:
  _GdpGraphics_()
  {
    enter();
  }
  ~_GdpGraphics_()
  {
    leave();
  }

  int ok()
  {
    return graphics != 0;
  }
  gdp::Graphics* gdp()
  {
    return graphics;
  }

  void enter()
  {
    if (graphics) {
      if (_gdp_count == 1) {
        graphics->ReleaseHDC(_gdp_hdc);
        _gdp_count--;
      }
    }
  }
  void leave()
  {
    if (graphics) {
      if (_gdp_count == 0) {
        _gdp_hdc = graphics->GetHDC();
        _gdp_count++;
      }
    }
  }
};

void __fastcall trace_bgi_coord(int x, int y);
void __fastcall trace_bgi_coord(const POINT* Points, int PointsCount);

void select_font();
gdp::Font* _gdp_create_font();

linesettingstype line_settings;
textsettingstype text_settings;
fillsettingstype fill_settings;
static int bgiColor;

int getmaxx()
{
  return MaxX;
}

int getmaxy()
{
  return MaxY;
}

int getcolor(void)
{
  return bgiColor;
}

void setcolor(int color)
{
  bgiColor = color;
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
  } else {
    dc->Pen->Width = line_settings.thickness;
    dc->Pen->Color = BgiDacColor(bgiColor);
    switch (line_settings.linestyle) {
    default:
      dc->Pen->Style = psSolid;
      break;
    case 1:
      dc->Pen->Style = psDash;
      dc->Pen->Width = 1;
      break;
    case 2:
      dc->Pen->Style = psDot;
      dc->Pen->Width = 1;
      break;
    case 3:
      dc->Pen->Style = psDashDot;
      dc->Pen->Width = 1;
      break;
    case 4:
      dc->Pen->Style = psDashDotDot;
      dc->Pen->Width = 1;
      break;
    }
  }
}

void setlinestyle(int linestyle, unsigned upattern, int thickness)
{
  line_settings.linestyle = linestyle;
  line_settings.upattern = upattern;
  line_settings.thickness = thickness;
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    //% в крейтепен
  } else {
    switch (line_settings.linestyle) {
    default:
      dc->Pen->Style = psSolid;
      break;
    case 1:
      dc->Pen->Style = psDash;
      dc->Pen->Width = 1;
      break;
    case 2:
      dc->Pen->Style = psDot;
      dc->Pen->Width = 1;
      break;
    case 3:
      dc->Pen->Style = psDashDot;
      dc->Pen->Width = 1;
      break;
    case 4:
      dc->Pen->Style = psDashDotDot;
      dc->Pen->Width = 1;
      break;
    }
  }
}

gdp::Color _gdp_color(int c)
{
  int color = BgiDacColor(c);
  return gdp::Color(255, GetRValue(color), GetGValue(color), GetBValue(color));
}

gdp::Pen* _gdp_create_pen()
{
  gdp::Color color = _gdp_color(bgiColor);
  gdp::Pen myPen(color);

  switch (line_settings.linestyle) {
  default:
    myPen.SetDashStyle(gdp::DashStyleSolid);
    break;
  case 1:
    myPen.SetDashStyle(gdp::DashStyleDash);
    break;
  case 2:
    myPen.SetDashStyle(gdp::DashStyleDot);
    break;
  case 3:
    myPen.SetDashStyle(gdp::DashStyleDashDot);
    break;
  case 4:
    myPen.SetDashStyle(gdp::DashStyleDashDotDot);
    break;
  }

  myPen.SetAlignment(gdp::PenAlignmentCenter);
  int PenWidth = line_settings.thickness;
  myPen.SetWidth(PenWidth);
  GDPCHECK(myPen.GetLastStatus());
  return myPen.Clone();
}

void setfillstyle(int style, int col)
{
  fill_settings.color = col;
  fill_settings.pattern = style;

  _GdpGraphics_ g;
  if (g.ok()) {
    //% в крейтебраш
  } else {
    //%
    switch (style) {
    case EMPTY_FILL:
      fill_settings.pattern = bsClear;
      break;
    case SOLID_FILL:
      fill_settings.pattern = bsSolid;
      break;
    case LINE_FILL:
      fill_settings.pattern = bsHorizontal;
      break;
    case LTSLASH_FILL:
      fill_settings.pattern = bsVertical;
      break;
    case SLASH_FILL:
      fill_settings.pattern = bsBDiagonal;
      break;
    case BKSLASH_FILL:
      fill_settings.pattern = bsFDiagonal;
      break;
    case LTBKSLASH_FILL:
    case HATCH_FILL:
    case XHATCH_FILL:
    case INTERLEAVE_FILL:
      fill_settings.pattern = bsDiagCross; // bsCross;
      break;
    case WIDE_DOT_FILL:
    case CLOSE_DOT_FILL:
    case USER_FILL:
      fill_settings.pattern = bsDiagCross;
      break;
    default:
      fill_settings.pattern = bsClear;
    }
    if (dc != NULL) {
      dc->Brush->Color = BgiDacColor(fill_settings.color);
      dc->Brush->Style = fill_settings.pattern;
    }
  }
}

void getfillsettings(fillsettingstype* fs)
{
  *fs = fill_settings;
}

gdp::Brush* _gdp_create_brush(int brsh_cl1 = -1, int brsh_cl2 = -1)
{
  gdp::Color color = _gdp_color(fill_settings.color);
  gdp::Color color2 = _gdp_color(bgiColor);

  if (brsh_cl1 != -1)
    color = _gdp_color(brsh_cl1);
  if (brsh_cl2 != -1)
    color2 = _gdp_color(brsh_cl2);

  gdp::HatchStyle pattern = gdp::HatchStyleTotal + 6;
  switch (fill_settings.pattern) {
  default:
    break;
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    pattern = gdp::HatchStyleTotal;
    break;

  case LINE_FILL:
    pattern = gdp::HatchStyleLightHorizontal;
    break;
  case LTSLASH_FILL:
    pattern = gdp::HatchStyleLightVertical;
    break;
  case SLASH_FILL:
    pattern = gdp::HatchStyleForwardDiagonal;
    break;
  case BKSLASH_FILL:
    pattern = gdp::HatchStyleBackwardDiagonal;
    break;
  case LTBKSLASH_FILL:
  case HATCH_FILL:
  case XHATCH_FILL:
  case INTERLEAVE_FILL:
  case WIDE_DOT_FILL:
  case CLOSE_DOT_FILL:
  case USER_FILL:
    pattern = gdp::HatchStyleSmallCheckerBoard;
    break;
  }

  if (pattern == gdp::HatchStyleTotal) {
    gdp::SolidBrush mySBrush(color);
    GDPCHECK(mySBrush.GetLastStatus());
    return mySBrush.Clone();
  }
  if (pattern < gdp::HatchStyleTotal) {
    gdp::HatchBrush myHBrush(pattern, color2, color);
    GDPCHECK(myHBrush.GetLastStatus());
    return myHBrush.Clone();
  }
  return 0;
}

// просто линия вторая точка рисуется включительно
void line(int x0, int y0, int x1, int y1)
{
  trace_bgi_coord(x0, y0);
  trace_bgi_coord(x1, y1);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawLine(pen.get(), x0, y0, x1, y1);
  } else {
    dc->MoveTo(x0, y0);
    dc->LineTo(x1, y1);
    dc->Pixels[x1][y1] = dc->Pen->Color;
  }
}

// прямоугольник без заполнения
void rectangle(int left, int top, int right, int bottom)
{
  if (top > bottom)
    swap(top, bottom);
  if (left > right)
    swap(left, right);
  trace_bgi_coord(left, top);
  trace_bgi_coord(right, bottom);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawRectangle(pen.get(), left, top, right - left, bottom - top);
  } else {
    POINT rect[5];
    rect[0].x = left, rect[0].y = top;
    rect[1].x = right, rect[1].y = top;
    rect[2].x = right, rect[2].y = bottom;
    rect[3].x = left, rect[3].y = bottom;
    rect[4].x = left, rect[4].y = top;
    drawpoly(5, (int*)&rect);
  }
}

// окружность без заполнения
void circle(int x, int y, int radius)
{
  trace_bgi_coord(x - radius, y - radius);
  trace_bgi_coord(x + radius, y + radius);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawEllipse(pen.get(), x - radius, y - radius, radius * 2, radius * 2);
  } else {
    dc->Arc(x - radius, y - radius, x + radius, y + radius, x + radius, y, x + radius, y);
  }
}

// заполянет и обрамляет элипс
void fillellipse(int x, int y, int xradius, int yradius)
{
  trace_bgi_coord(x - xradius, y - yradius);
  trace_bgi_coord(x + xradius, y + yradius);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Brush> brush(_gdp_create_brush());
    if (brush.get())
      g.gdp()->FillEllipse(brush.get(), x - xradius, y - yradius, xradius * 2, yradius * 2);

    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawEllipse(pen.get(), x - xradius, y - yradius, xradius * 2, yradius * 2);
  } else {
    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
      dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);
    } else {
      // сначала цветом
      dc->Brush->Style = bsSolid;
      dc->Brush->Color = BgiDacColor(fill_settings.color);
      dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);

      // потом штриховку
      dc->Brush->Style = fill_settings.pattern;
      dc->Brush->Color = BgiDacColor(BLACK);
      dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);
      // восстановим
      dc->Brush->Color = BgiDacColor(fill_settings.color);
    }
  }
}

// только окантовка
void drawpoly(int num, const int* points)
{
  trace_bgi_coord((POINT*)points, num);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    POINT* pp = (POINT*)points;
    auto_array_ptr<gdp::Point> ps(new gdp::Point[num]);
    for (int i = 0; i < num; ++i) {
      ps[i].X = pp[i].x;
      ps[i].Y = pp[i].y;
    }
    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawPolygon(pen.get(), ps.get(), num);
  } else {
    dc->Polyline((TPoint*)points, num - 1);
    dc->Pen->Style = psSolid;
  }
}

// окантовка с заполнением
void fillpoly(int num, const int* points)
{
  trace_bgi_coord((POINT*)points, num);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    POINT* pp = (POINT*)points;
    auto_array_ptr<gdp::Point> ps(new gdp::Point[num]);
    for (int i = 0; i < num; ++i) {
      ps[i].X = pp[i].x;
      ps[i].Y = pp[i].y;
    }
    auto_ptr<gdp::Brush> brush(_gdp_create_brush());
    if (brush.get())
      g.gdp()->FillPolygon(brush.get(), ps.get(), num);
    auto_ptr<gdp::Pen> pen(_gdp_create_pen());
    g.gdp()->DrawPolygon(pen.get(), ps.get(), num);
  } else {
    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
      dc->Polygon((TPoint*)points, num - 1);
    } else {
      // сначала цветом
      dc->Brush->Style = bsSolid;
      dc->Brush->Color = BgiDacColor(fill_settings.color);
      dc->Polygon((TPoint*)points, num - 1);
      // потом штриховку
      dc->Brush->Style = fill_settings.pattern;
      dc->Brush->Color = BgiDacColor(BLACK);
      dc->Polygon((TPoint*)points, num - 1);
      // восстановим
      dc->Brush->Color = BgiDacColor(fill_settings.color);
    }
  }
}

// только заполняет прямоугольник без обрамления
void bar(int left, int top, int right, int bottom)
{
  if (top > bottom)
    swap(top, bottom);
  if (left > right)
    swap(left, right);
  trace_bgi_coord(left, top);
  trace_bgi_coord(right, bottom);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Brush> brush(_gdp_create_brush());
    if (brush.get())
      g.gdp()->FillRectangle(brush.get(), left, top, right - left + 1, bottom - top + 1);
  } else {
    POINT rect[5];
    rect[0].x = left, rect[0].y = top;
    rect[1].x = right, rect[1].y = top;
    rect[2].x = right, rect[2].y = bottom;
    rect[3].x = left, rect[3].y = bottom;
    rect[4].x = left, rect[4].y = top;
    TColor OldPenColor = dc->Pen->Color;
    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
      dc->Pen->Color = BgiDacColor(fill_settings.color);
      dc->Polygon((TPoint*)rect, 4);

    } else {
      // сначала цветом
      dc->Brush->Style = bsSolid;
      dc->Pen->Color = BgiDacColor(fill_settings.color);
      dc->Brush->Color = BgiDacColor(fill_settings.color);
      dc->Polygon((TPoint*)rect, 4);
      // потом штриховку
      dc->Brush->Style = fill_settings.pattern;
      // dc->Pen->Color = BgiDacColor(bgiColor);
      dc->Pen->Color = BgiDacColor(fill_settings.color);
      dc->Brush->Color = BgiDacColor(BLACK); // clBlack //>>
      dc->Polygon((TPoint*)rect, 4);
      // восстановим
      dc->Brush->Color = BgiDacColor(fill_settings.color);
    }
    dc->Pen->Color = OldPenColor;
  }
}

void pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4)
{
  trace_bgi_coord(X1, Y1);
  trace_bgi_coord(X2, Y2);
  trace_bgi_coord(X3, Y3);
  trace_bgi_coord(X4, Y4);
  if (dc == NULL)
    return;

  dc->Pie(X1, Y1, X2, Y2, X3, Y3, X4, Y4);
}

void settextjustify(int horiz, int vert)
{
  text_settings.horiz = horiz;
  text_settings.vert = vert;
}

void settextstyle(int font, int direction, int charsize)
{
  text_settings.font = (font < FontCount) ? font : 0;
  text_settings.direction = direction;
  text_settings.charsize = charsize;
  select_font();
}

wchar_t* oem2wchar(const char* oemstr)
{
  static WCHAR w_str[1024];
  static char str[512];
  ::OemToAnsi(oemstr, str);
  memset(w_str, 0, sizeof(w_str));
  int wlen = ::MultiByteToWideChar(CP_ACP, 0, str, -1, 0, 0);
  if (wlen >= (sizeof(w_str) / sizeof(w_str[0])))
    throw "not implemented.";
  int r = ::MultiByteToWideChar(CP_ACP, 0, str, -1, w_str, wlen);
  return w_str;
}

char* oem2char(const char* oemstr)
{
  static char str[512];
  ::OemToAnsi(oemstr, str);
  return str;
}

int textheight(const char* str)
{
  if (dc == NULL)
    return 0;
  int h = 0;
  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Font> font(_gdp_create_font());
    h = font->GetSize();
  } else {
    TEXTMETRIC ptm;
    ::GetTextMetrics(dc->Handle, &ptm);
    h = ptm.tmAscent;
  }
  return h;
}

int textwidth(const char* oemstr)
{
  if (dc == NULL)
    return 0;
  int w = 0;
  _GdpGraphics_ g;
  if (g.ok()) {
    auto_ptr<gdp::Font> font(_gdp_create_font());
    gdp::PointF origin(0.0f, 0.0f);
    gdp::RectF boundRect;
    WCHAR* wstr = oem2wchar(oemstr);
    g.gdp()->MeasureString(wstr, -1, font.get(), origin, &boundRect);
    w = boundRect.Width;
  } else {
    SIZE sz;
    char* str = oem2char(oemstr);
    ::GetTextExtentPoint32(dc->Handle, str, strlen(str), &sz);
    w = sz.cx;
  }
  return w;
}

void OutTextXY(int x, int y, char* str)
{
  int th = textheight(str);
  int tw = textwidth(str);

  int dx = 0;
  int dy = 0;
  switch (text_settings.horiz) {
  case LEFT_TEXT:
    dx = 0;
    break;
  case RIGHT_TEXT:
    dx = tw;
    break;
  case CENTER_TEXT:
    dx = (0.5 + 1. * tw / 2);
    break;
  }
  switch (text_settings.vert) {
  case TOP_TEXT:
    dy = 0;
    break;
  case BOTTOM_TEXT:
    dy = th;
    break;
  case CENTER_TEXT:
    dy = (0.5 + 1. * th / 2);
    break;
  }
  trace_bgi_coord(x - dx, y - dy);
  trace_bgi_coord(x - dx + tw, y - dy);
  trace_bgi_coord(x - dx, y - dy + th);
  trace_bgi_coord(x - dx + tw, y - dy + th);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    gdp::PointF origin(x - dx, y - dy);
    gdp::SolidBrush brush(_gdp_color(bgiColor));
    auto_ptr<gdp::Font> font(_gdp_create_font());
    g.gdp()->DrawString(oem2wchar(str), -1, font.get(), origin, &brush);
  } else {
    TBrushStyle obs = dc->Brush->Style;
    dc->Font->Color = BgiDacColor(bgiColor);
    dc->Brush->Style = bsClear;
    dc->TextOut(x - dx, y - dy, oem2char(str));
    dc->Brush->Style = obs;
  }

#ifdef BGIDBG
  setcolor(5);
  rectangle(x - dx, y - dy, x - dx + tw, y - dy + th);
#endif
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void DrawText(int x, int y, int tw, int th, char* str)
{
  trace_bgi_coord(x, y);
  trace_bgi_coord(x + tw, y + th);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    gdp::RectF rect(x, y, tw, th);
    //> сделать выравнивание строки
    gdp::StringFormat format;
    format.SetAlignment(gdp::StringAlignmentCenter);
    format.SetLineAlignment(gdp::StringAlignmentCenter);
    gdp::SolidBrush brush(_gdp_color(bgiColor));
    auto_ptr<gdp::Font> font(_gdp_create_font());
    g.gdp()->DrawString(oem2wchar(str), -1, font.get(), rect, &format, &brush);
  } else {
    UINT uF = DT_NOCLIP | DT_SINGLELINE | DT_EXTERNALLEADING;
    switch (text_settings.horiz) {
    case LEFT_TEXT:
      uF = uF | DT_LEFT;
      break;
    case CENTER_TEXT:
      uF = uF | DT_CENTER;
      break;
    case RIGHT_TEXT:
      uF = uF | DT_RIGHT;
      break;
    }
    switch (text_settings.vert) {
    case TOP_TEXT:
      uF = uF | DT_TOP;
      break;
    case BOTTOM_TEXT:
      uF = uF | DT_BOTTOM;
      break;
    case CENTER_TEXT:
      uF = uF | DT_VCENTER;
      break;
    }
    RECT R;
    R.left = x;
    R.top = y;
    R.right = x + tw;
    R.bottom = y + th;
    int om = ::SetBkMode(dc->Handle, TRANSPARENT);
    ::SetTextColor(dc->Handle, BgiDacColor(bgiColor));
    ::DrawText(dc->Handle, oem2char(str), -1, &R, uF);
    ::SetBkMode(dc->Handle, om);
  }

#ifdef BGIDBG
  setcolor(4);
  rectangle(x, y, x + tw, y + th);
#endif
}

void _SetTextSize(int charsize)
{
  text_settings.charsize = charsize;
  select_font();
}

void _SetText(unsigned int font, int d1, int d2)
{
  text_settings.font = (font < FontCount) ? font : 0;
  settextjustify(d1, d2);
  select_font();
}

static void set_defaults()
{
  line_settings.thickness = 1;
  line_settings.linestyle = SOLID_LINE;
  line_settings.upattern = ~0;
  fill_settings.pattern = SOLID_FILL;
  fill_settings.color = WHITE;
  text_settings.direction = HORIZ_DIR;
  text_settings.font = DEFAULT_FONT;
  text_settings.charsize = 1;
  //    text_settings.horiz = TA_LEFT;
  //    text_settings.vert = TA_TOP;
}

// VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class WinBGIModule
{
public:
  TCriticalSection* CS;
  TCanvas* CashCnv;

  WinBGIModule() : CS(0), CashCnv(0)
  {
  }

  void Open()
  {
    if (!CS) {
      CS = new TCriticalSection();
      CreateFonts();
      Get_DAC();
      set_defaults();
    }
  }

  ~WinBGIModule()
  {
    DestroyFonts();
    if (CashCnv)
      delete CashCnv;
    delete CS;
  }
};
static WinBGIModule BGI;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

WinBgiDC::WinBgiDC(TCanvas* c, int _gdp)
{
  dc = 0;
  if (c == NULL)
    return;

  if (_gdp) {
    HDC hdc = c->Handle;
    graphics = gdp::Graphics::FromHDC(hdc);
    if (graphics != NULL) {
      graphics->SetSmoothingMode(gdp::SmoothingModeHighQuality);
      graphics->SetTextRenderingHint(gdp::TextRenderingHintAntiAlias);
      //        graphics->SetTextRenderingHint(gdp::TextRenderingHintSingleBitPerPixel);

      GDPCHECK(graphics->GetLastStatus());
      _gdp_hdc = graphics->GetHDC();
    }
    if (!BGI.CashCnv)
      BGI.CashCnv = new TCanvas();
    BGI.CashCnv->Handle = _gdp_hdc;
  }
  Open(c);
}

WinBgiDC::WinBgiDC(void* _hdc, int _gdp)
{
  HDC hdc = (HDC)_hdc;
  dc = 0;
  graphics = 0;
  if (_gdp) {
    graphics = gdp::Graphics::FromHDC(hdc);
    graphics->SetSmoothingMode(gdp::SmoothingModeHighQuality);
    graphics->SetTextRenderingHint(gdp::TextRenderingHintAntiAlias);
    //        graphics->SetTextRenderingHint(gdp::TextRenderingHintSingleBitPerPixel);

    GDPCHECK(graphics->GetLastStatus());
    _gdp_hdc = graphics->GetHDC();
    if (!BGI.CashCnv)
      BGI.CashCnv = new TCanvas();
    BGI.CashCnv->Handle = _gdp_hdc;
  }
  // if(!BGI.CashCnv)
  //     BGI.CashCnv = new TCanvas();
  // BGI.CashCnv->Handle = hdc;
  Open(BGI.CashCnv);
}

/*
WinBgiDC::WinBgiDC(HDC hdc)
{
    dc = 0;
    graphics  = 0;
    if(!BGI.CashCnv)
        BGI.CashCnv = new TCanvas();
    BGI.CashCnv->Handle = hdc;
    Open( BGI.CashCnv );
}
*/

WinBgiDC::~WinBgiDC(void)
{
  Close();
  if (graphics) {
    graphics->ReleaseHDC(_gdp_hdc);
    delete graphics;
    graphics = 0;
  }
}

static int CountWinBgiDC = 0;
void WinBgiDC::Open(TCanvas* pdc)
{
  CountWinBgiDC++;
  //   if( CountWinBgiDC != 1 )
  //       throw "CountWinBgiDC != 1 debug можно закоментарить";

  BGI.Open();
  BGI.CS->Enter();

  SaveIndex = 0;
  dc = pdc;
  if (dc) {
    SaveIndex = ::SaveDC(dc->Handle);
    dc->Refresh();
  }
}

void WinBgiDC::Close()
{
  if (dc) {
    ::RestoreDC(dc->Handle, SaveIndex);
    dc->Refresh();
    dc = NULL;
  }
  BGI.CS->Leave();
  CountWinBgiDC--;
}

//для тестовых случаев
void draw_xpoint(int x, int y)
{
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    gdp::Pen myPen(gdp::Color(255, 0, 0, 255));
    g.gdp()->DrawLine(&myPen, gdp::Point(x - 2, y), gdp::Point(x + 2, y));
    g.gdp()->DrawLine(&myPen, gdp::Point(x, y - 2), gdp::Point(x, y + 2));
    gdp::Pen myPen2(gdp::Color(255, 255, 0, 0));
    g.gdp()->DrawEllipse(&myPen2, x - 1, y - 1, 2, 2);
  } else {
    dc->Pixels[x][y] = 0xff0000;
    dc->Pixels[x + 1][y] = 0xff00;
    dc->Pixels[x - 1][y] = 0xff00;
    dc->Pixels[x][y + 1] = 0xff00;
    dc->Pixels[x][y - 1] = 0xff00;
  }
}

// только для Yстрелок
void PolyColor(int iBrushColor, const TPoint* Points, const int* iColors, const int Points_Count, int PenW)
{
  for (int i = 0; i < Points_Count; i++)
    trace_bgi_coord(Points[i].x, Points[i].y);
  if (dc == NULL)
    return;

  _GdpGraphics_ g;
  if (g.ok()) {
    POINT* pp = (POINT*)Points;
    auto_array_ptr<gdp::Point> ps(new gdp::Point[Points_Count]);
    for (int i = 0; i < Points_Count; ++i) {
      ps[i].X = pp[i].x;
      ps[i].Y = pp[i].y;
    }
    auto_ptr<gdp::Brush> brush(_gdp_create_brush(iBrushColor));
    if (brush.get()) {
      g.gdp()->FillPolygon(brush.get(), ps.get(), Points_Count);
    }

    for (int i = 1; i < Points_Count; i++) {
      if (iBrushColor == iColors[i - 1])
        continue;
      gdp::Color color = _gdp_color(iColors[i - 1]);
      gdp::Pen myPen(color);
      g.gdp()->DrawLine(&myPen, ps[i - 1].X, ps[i - 1].Y, ps[i].X, ps[i].Y);
    }
    if (iBrushColor != iColors[Points_Count - 1]) {
      gdp::Color color = _gdp_color(iColors[Points_Count - 1]);
      gdp::Pen myPen(color);
      g.gdp()->DrawLine(&myPen, ps[Points_Count - 1].X, ps[Points_Count - 1].Y, ps[0].X, ps[0].Y);
    }
  } else {
    //%%
    TColor BrushColor = BgiDacColor(iBrushColor);
    dc->Pen->Color = BrushColor;
    dc->Brush->Color = BrushColor;
    if ((fill_settings.pattern != bsSolid) && (fill_settings.pattern != bsClear)) {
      dc->Brush->Style = bsSolid;
      dc->Polygon(Points, Points_Count - 1);
      dc->Brush->Color = clBlack;
    }
    dc->Brush->Style = fill_settings.pattern;
    dc->Pen->Style = psClear;
    dc->Polygon(Points, Points_Count - 1);
    dc->Pen->Style = psSolid;
    dc->Pen->Width = PenW;
    for (int i = 1; i < Points_Count; i++) {
      if (iBrushColor == iColors[i - 1])
        continue;
      dc->Pen->Color = BgiDacColor(iColors[i - 1]);
      dc->MoveTo(Points[i - 1].x, Points[i - 1].y);
      dc->LineTo(Points[i].x, Points[i].y);
      dc->Pixels[Points[i].x][Points[i].y] = dc->Pen->Color;
    }
    if (iBrushColor != iColors[Points_Count - 1]) {
      dc->Pen->Color = BgiDacColor(iColors[Points_Count - 1]);
      dc->MoveTo(Points[Points_Count - 1].x, Points[Points_Count - 1].y);
      dc->LineTo(Points[0].x, Points[0].y);
      dc->Pixels[Points[0].x][Points[0].y] = dc->Pen->Color;
    }
    dc->Pen->Width = 1;
  }
}

// функции для работы с EMF
bool drawemf(const RECT* lpRect,
             const char* szimagename,
             int animstep)
{
  tracecoord(lpRect->left, lpRect->top);
  tracecoord(lpRect->left, lpRect->bottom);
  tracecoord(lpRect->right, lpRect->top);
  tracecoord(lpRect->right, lpRect->bottom);
  if (lpRect->left == lpRect->right || lpRect->top == lpRect->bottom)
    return true;
  if (dc == NULL)
    return true;
  return im_drawemf(dc->Handle, lpRect, szimagename, animstep);
}
static TCanvas* _SaveDC = NULL;
void* SetNullDC()
{
  _SaveDC = dc;
  dc = NULL;
  return _SaveDC;
}
void RestoreNullDC()
{
  dc = _SaveDC;
  _SaveDC = NULL;
};
