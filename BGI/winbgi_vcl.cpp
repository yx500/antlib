#include <vcl.h>
#pragma hdrstop

#if (__BORLANDC__ >= 0x530)
#pragma package(smart_init)
#endif
//----------------------------------------------------------------------------

#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
//#include <algorithm>
//#include <map>

#include <SyncObjs.hpp>

//#define  BGIDBG
#include "winbgi.h"
#include "winpalet.h"
#include "Col.h"
#include "uImgContainer.h"

#include "GMPEN.H"

//#include "ALIB.h"

//static
TCanvas* dc = 0;

//int UseBGIPalette=true; vlad изменил для оптимизации и однообразия
int UseBGIPalette = false;

bool NoGmPen = false;
///*COLORREF*/

int GetGradientColor(int Color, float factor);
float GradientFactor = 1;
void SetGradientFactor(float AGradientFactor)
{
    GradientFactor = AGradientFactor;
}



TColor BgiColor(unsigned int c)
{
    //if( UseBGIPalette )
    //    return PALETTEINDEX( c );

    TColor clr = c;
    if (c < 256) clr = BgiDacColor(c);
    if ((GradientFactor != 1) && (c != FON)) clr = GetGradientColor(clr, GradientFactor);
    return clr;
}
#define BGICOLOR(c) BgiColor(c)



bool UseNativeFontSize = true;

const int FontCount = 32;
static TFont *Fonts[ FontCount ];


using namespace std;



static RECT  TraceRect;
void __fastcall tracecoord(int x, int y)
{
    if (x < TraceRect.left)    TraceRect.left = x;
    if (y < TraceRect.top)     TraceRect.top = y;
    if (x > TraceRect.right)   TraceRect.right = x;
    if (y > TraceRect.bottom)  TraceRect.bottom = y;
}
static void __fastcall tracecoord(const POINT* Points, int PointsCount)
{
    for (int i = 0; i < PointsCount; i++)  tracecoord(Points[ i ].x, Points[ i ].y);
}
static TCanvas * _SaveDC = NULL;
void * SetNullDC()
{
    _SaveDC = dc; dc = NULL; return _SaveDC;
}
void   RestoreNullDC()
{
    dc = _SaveDC; _SaveDC = NULL;
};
TCanvas * Get_SaveDC()
{
    return _SaveDC;
};

RECT& ClearBgiCoverRect(void)
{
    ::SetRect(&TraceRect, MaxInt, MaxInt, -MaxInt, -MaxInt); return TraceRect;
}
RECT& GetBgiCoverRect(void)
{
    return TraceRect;
}





static int font_height[ FontCount ]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int font_width[ FontCount ]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//static TEXTMETRIC font_tm[ FontCount ];
//static TEXTMETRIC* ptm=0;

/*
#ifdef __cplusplus
extern "C" {
#endif
*/
static linesettingstype line_settings;
static textsettingstype text_settings;
static fillsettingstype fill_settings;
static viewporttype view_port;
static int bgiColor;
static int bgiBkColor;
static int aspect_ratio_x, aspect_ratio_y;
static arccoordstype ac;

/*
static HBRUSH hBrush[USER_FILL+1];
static HBRUSH hBackgroundBrush;
*/

typedef char fillpatterntype[ 8 ];
static fillpatterntype userfillpattern = { -1, -1, -1, -1, -1, -1, -1, -1};
void SetFontParams(TFont * Font1, TFont * Font2)
{
    //return;
    if ((Font1 == NULL) || (Font2 == NULL)) return;
    Font1->Name = Font2->Name;
    Font1->Color = Font2->Color;
    Font1->Charset = Font2->Charset;
    Font1->Height = Font2->Height;

    Font1->Pitch = Font2->Pitch;
    //Font1->Size=Font2->Size;
    Font1->Style = Font2->Style;
}
/*
void SetBrushParams(TBrush* Brush1,TBrush* Brush2)
{
     return;
     Brush1->Color=Brush2->Color;
     Brush1->Style=Brush2->Style;
}
*/
static void select_font()
{
    if (text_settings.font < 0 || text_settings.font >= FontCount) {
        text_settings.font = 0;
        cerr << "Default font." << endl;
    }
    if ((dc == NULL) && (_SaveDC == NULL))  return;
    //ptm = &font_tm[ text_settings.font ];
    if (dc == NULL) {
        //SetFontParams(_SaveDC->Font,Fonts[text_settings.font]);
        _SaveDC->Font = Fonts[ text_settings.font ];
        if (text_settings.charsize != 1)
            _SaveDC->Font->Height = text_settings.charsize;
        return;
    }
    SetFontParams(dc->Font, Fonts[text_settings.font]);
    //dc->Font = Fonts[ text_settings.font ];
    if (text_settings.charsize != 1)
        dc->Font->Height = text_settings.charsize;

}

void setaspectratio(int ax, int ay)
{
    aspect_ratio_x = ax;
    aspect_ratio_y = ay;
}

void getaspectratio(int* ax, int* ay)
{
    *ax = aspect_ratio_x;
    *ay = aspect_ratio_y;
}

int getx()
{
    if (dc == NULL)  return 0;
    POINT pos;
    GetCurrentPositionEx(dc->Handle, &pos);
    return pos.x;
}
int gety()
{
    if (dc == NULL)  return 0;
    POINT pos;
    GetCurrentPositionEx(dc->Handle, &pos);
    return pos.y;
}


int getmaxx()
{
    return -1;//MaxX;
}
int getmaxy()
{
    return -1;//MaxY;
}

int getcolor(void)
{
    return bgiColor;
}

void  setbkcolor(int color)
{
    bgiBkColor = color;
}
/*
    void  setcolortn(int T,int N)
    {
        wc_SetColorByT_N(T,N);
    }

    int   getSPLC(int T,int N)
    {
        return wc_GetColor(T,N);

    }
*/
void  setcolor(int color)
{
    if (dc == NULL)  return;
    bgiColor = color;
    //::SetTextColor(dc->Handle, BGICOLOR(bgiColor) );
    dc->Pen->Color = BGICOLOR(bgiColor);

    /*dc->Pen->Width=line_settings.thickness;
    switch ( line_settings.linestyle ) {
    default : dc->Pen->Style = psSolid; break;
    case 1: dc->Pen->Style = psDash;dc->Pen->Width=1; break;
    case 2: dc->Pen->Style = psDot;dc->Pen->Width=1; break;
    case 3: dc->Pen->Style = psDashDot;dc->Pen->Width=1; break;
    case 4: dc->Pen->Style = psDashDotDot;dc->Pen->Width=1; break;
    } */

}


unsigned  getpixel(int x, int y)
{
    if (dc == NULL)  return 0;
    return dc->Pixels[ x ][ y ];
}

void  putpixel(int x, int y, int color)
{
    tracecoord(x, y);
    if (dc == NULL)  return;
    dc->Pixels[ x ][ y ]  = BGICOLOR(color);
}


void  gettextsettings(struct textsettingstype *texttypeinfo)
{
    memcpy(texttypeinfo, &::text_settings, sizeof(textsettingstype));
}

void  drawpoly(int numpoints, const int *polypoints)
{
    tracecoord((TPoint *) polypoints, numpoints);
    if (dc == NULL)  return;


    TGmPen p(dc);
    //::Polyline(dc->Handle,(TPoint *)polypoints, numpoints);
    dc->Polyline((TPoint *) polypoints, numpoints - 1);
    dc->Pen->Style = psSolid;
}
/*  На хрена ?
inline void select_fill_color()
{
 if (dc==NULL) return;
 if (bgiColor != fill_settings.color) {
//  bgiColor = fill_settings.color;
//  SetTextColor(dc->Handle, BGICOLOR(bgiColor));
 }
}
*/

void  fillpoly(int numpoints, const int *polypoints)
{
    tracecoord((TPoint *) polypoints, numpoints);
    if (dc == NULL)  return;


    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
        TGmPen p(dc);
        dc->Polygon((TPoint *) polypoints, numpoints - 1);
    } else {
        // сначала цветом
        dc->Brush->Style = bsSolid;
        dc->Brush->Color = BGICOLOR(fill_settings.color);
        {
            TGmPen p(dc);
            dc->Polygon((TPoint *) polypoints, numpoints - 1);
        }
        // потом штриховку
        dc->Brush->Style = fill_settings.pattern;
        dc->Brush->Color = BGICOLOR(BLACK);
        {
            TGmPen p(dc);
            dc->Polygon((TPoint *) polypoints, numpoints - 1);
        }
        // восстановим
        dc->Brush->Color = BGICOLOR(fill_settings.color);
    }
}

void bar(int left, int top, int right, int bottom)
{
    if (top > bottom)  swap(top, bottom);
    if (left > right)  swap(left, right);

    POINT rect[ 5 ];
    rect[ 0 ].x = left,  rect[ 0 ].y = top;
    rect[ 1 ].x = right, rect[ 1 ].y = top;
    rect[ 2 ].x = right, rect[ 2 ].y = bottom;
    rect[ 3 ].x = left,  rect[ 3 ].y = bottom;
    rect[ 4 ].x = left,  rect[ 4 ].y = top;

    tracecoord((TPoint *) rect, 4);
    if (dc == NULL)  return;
    TColor OldPenColor = dc->Pen->Color;

    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
        //dc->Brush->Style = bsSolid;
        dc->Pen->Color = BGICOLOR(fill_settings.color);
        //dc->Brush->Color = BGICOLOR(fill_settings.color);
        TGmPen p(dc);
        dc->Polygon((TPoint *) rect, 4);

    } else {
        // сначала цветом
        dc->Brush->Style = bsSolid;
        dc->Pen->Color = BGICOLOR(fill_settings.color);
        dc->Brush->Color = BGICOLOR(fill_settings.color);
        {
            TGmPen p(dc);
            dc->Polygon((TPoint *) rect, 4);
        }
        // потом штриховку
        dc->Brush->Style = fill_settings.pattern;
        //dc->Pen->Color = BGICOLOR(bgiColor);
        dc->Pen->Color = BGICOLOR(fill_settings.color);
        dc->Brush->Color = BGICOLOR(BLACK);    //clBlack //>>

        {
            TGmPen p(dc);
            dc->Polygon((TPoint *) rect, 4);
        }
        // восстановим
        dc->Brush->Color = BGICOLOR(fill_settings.color);

    }
    dc->Pen->Color = OldPenColor;
#ifdef BGIDBG
    dc->Pixels[ left ][ top ]  = 0xff00;
    dc->Pixels[ right ][ top ]  = 0xff00;
    dc->Pixels[ left ][ bottom ]  = 0xff00;
    dc->Pixels[ right ][ bottom ]  = 0xff00;
#endif

}

void floodfill(int x, int y, int border)
{
    if (dc == NULL)  return;
    //select_fill_color();
    //dc->Brush->Color = BGICOLOR(fill_settings.color);
    dc->FloodFill(x, y, BGICOLOR(border), fsSurface/*fsBorder*/);
}

void lineto(int x, int y)
{
    tracecoord(x, y);
    if (dc == NULL)  return;

    {
        TGmPen p(dc);
        dc->LineTo(x, y);
    }
}

void  line(int x0, int y0, int x1, int y1)
{
    POINT line[ 2 ];
    line[ 0 ].x = x0;
    line[ 0 ].y = y0;
    line[ 1 ].x = x1;
    line[ 1 ].y = y1;
    tracecoord(line, 2);
    if (dc == NULL)  return;

    dc->MoveTo(x0, y0); dc->LineTo(x1, y1);
    dc->Pixels[x1][y1] = dc->Pen->Color;
}

void  rectangle(int left, int top, int right, int bottom)
{
    if (top > bottom)  swap(top, bottom);
    if (left > right)  swap(left, right);

    POINT rect[ 5 ];
    rect[ 0 ].x = left, rect[ 0 ].y = top;
    rect[ 1 ].x = right, rect[ 1 ].y = top;
    rect[ 2 ].x = right, rect[ 2 ].y = bottom;
    rect[ 3 ].x = left, rect[ 3 ].y = bottom;
    rect[ 4 ].x = left, rect[ 4 ].y = top;
    tracecoord(rect, 4);
    if (dc == NULL)  return;

    drawpoly(5, (int*) &rect);
#ifdef BGIDBG
    dc->Pixels[ left ][ top ]  = 0xff;
    dc->Pixels[ right ][ top ]  = 0xff;
    dc->Pixels[ left ][ bottom ]  = 0xff;
    dc->Pixels[ right ][ bottom ]  = 0xff;
#endif

}

void  roundrect(int nLeftRect,   // x-coord. of bounding rectangle's upper-left corner
                int nTopRect,  // y-coord. of bounding rectangle's upper-left corner
                int nRightRect,    // x-coord. of bounding rectangle's lower-right corner
                int nBottomRect,   // y-coord. of bounding rectangle's lower-right corner
                int nWidth,    // width of ellipse used to draw rounded corners
                int nHeight    // height of ellipse used to draw rounded corners
               )
{
    if (nTopRect > nBottomRect)  swap(nTopRect, nBottomRect);
    if (nLeftRect > nRightRect)  swap(nLeftRect, nRightRect);

    POINT rect[ 5 ];
    rect[ 0 ].x = nLeftRect, rect[ 0 ].y = nTopRect;
    rect[ 1 ].x = nRightRect, rect[ 1 ].y = nTopRect;
    rect[ 2 ].x = nRightRect, rect[ 2 ].y = nBottomRect;
    rect[ 3 ].x = nLeftRect, rect[ 3 ].y = nBottomRect;
    rect[ 4 ].x = nLeftRect, rect[ 4 ].y = nTopRect;
    tracecoord(rect, 4);
    if (dc == NULL)  return;

    //drawpoly( 5, ( int* ) &rect );

    dc->RoundRect(nLeftRect, nTopRect, nRightRect, nBottomRect, nWidth, nHeight);
    //Rectangle(dc,nLeftRect,nTopRect,nRightRect,nBottomRect);




}



/*void bar3d( int left, int top, int right, int bottom, int depth, int topflag )
{
    int temp;
    const double tan30 = 1.0/1.73205080756887729352;
    if ( left > right )  {
        temp = left;
        left = right;
        right = temp;
    }
    if ( bottom < top )  {
        temp = bottom;
        bottom = top;
        top = temp;
    }
    bar( left+line_settings.thickness, top+line_settings.thickness,
         right-line_settings.thickness+1, bottom-line_settings.thickness+1 );
    /*
        dc->Pen->Color = BGICOLOR(bgiColor);
        int dy = int(depth*tan30);
        POINT p[11];
        p[0].x = right, p[0].y = bottom;
        p[1].x = right, p[1].y = top;
        p[2].x = left,  p[2].y = top;
        p[3].x = left,  p[3].y = bottom;
        p[4].x = right, p[4].y = bottom;
        p[5].x = right+depth, p[5].y = bottom-dy;
        p[6].x = right+depth, p[6].y = top-dy;
        p[7].x = right, p[7].y = top;

        if (topflag) {
        p[8].x = right+depth, p[8].y = top-dy;
        p[9].x = left+depth, p[9].y = top-dy;
        p[10].x = left, p[10].y = top;
        }
        dc->Polyline((TPoint *)p, topflag ? 11 : 8);
    *
}
  */
const double pi = 3.14159265358979323846;
inline void arc_coords(double angle, double rx, double ry, int& x, int& y)
{
    if (rx == 0 || ry == 0)  {
        x = y = 0;
        return;
    }
    double s = sin(angle * pi / 180.0);
    double c = cos(angle * pi / 180.0);
    if (fabs(s)  < fabs(c))  {
        double tg = s / c;
        double xr = sqrt((double) rx * rx * ry * ry / (ry * ry + rx * rx * tg * tg));
        x = int((c >= 0)  ? xr : -xr);
        y = int((s >= 0)  ? -xr * tg : xr * tg);
    } else {
        double ctg = c / s;
        double yr = sqrt((double) rx * rx * ry * ry / (rx * rx + ry * ry * ctg * ctg));
        x = int((c >= 0)  ? yr * ctg : -yr * ctg);
        y = int((s >= 0)  ? -yr : yr);
    }
}

void ellipse(int x, int y, int start_angle, int end_angle,
             int rx, int ry)
{
    ac.x = x;
    ac.y = y;
    arc_coords(start_angle, rx, ry, ac.xstart, ac.ystart);
    arc_coords(end_angle,  rx, ry, ac.xend, ac.yend);
    ac.xstart += x; ac.ystart += y;
    ac.xend += x; ac.yend += y;

    tracecoord(x - rx, y); tracecoord(x + rx, y); tracecoord(x, y - ry); tracecoord(x, y + ry);
    if (dc == NULL)  return;

    {
        TGmPen p(dc);
        dc->Arc(x - rx, y - ry, x + rx, y + ry,
                ac.xstart, ac.ystart, ac.xend, ac.yend);
    }
}

void circle(int x, int y, int radius)
{
    //    int ry = (unsigned)radius*aspect_ratio_x/aspect_ratio_y;
    int ry = radius;
    int rx = radius;
    tracecoord(x - rx, y); tracecoord(x + rx, y); tracecoord(x, y - ry); tracecoord(x, y + ry);
    if (dc == NULL)  return;

    {
        TGmPen p(dc);
        dc->Arc(x - rx, y - ry, x + rx, y + ry, x + rx, y, x + rx, y);
    }
}

void arc(int x, int y, int start_angle, int end_angle, int radius)
{
    ac.x = x;
    ac.y = y;
    ac.xstart = x + int(radius * cos(start_angle * pi / 180.0));
    ac.ystart = y - int(radius * sin(start_angle * pi / 180.0));
    ac.xend = x + int(radius * cos(end_angle * pi / 180.0));
    ac.yend = y - int(radius * sin(end_angle * pi / 180.0));
    tracecoord(ac.xstart, ac.ystart); tracecoord(ac.xend, ac.yend);
    if (dc == NULL)  return;
    dc->Arc(x - radius, y - radius, x + radius, y + radius, ac.xstart, ac.ystart, ac.xend, ac.yend);
}

void pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4)
{
    tracecoord(X1, Y1); tracecoord(X2, Y2); tracecoord(X3, Y3); tracecoord(X4, Y4);
    if (dc == NULL)  return;
    dc->Pie(X1, Y1, X2, Y2, X3, Y3, X4, Y4);
}

void  fillellipse(int x, int y, int xradius, int yradius)
{
    tracecoord(x - xradius, y); tracecoord(x + xradius, y);
    tracecoord(x, y - yradius); tracecoord(x, y + yradius);
    if (dc == NULL)  return;

    //dc->Brush->Color = BGICOLOR(fill_settings.color);

    if (fill_settings.pattern == bsClear || fill_settings.pattern == bsSolid) {
        dc->Brush->Style = bsSolid;
        TGmPen p(dc);
        dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);
    } else {
        // сначала цветом
        dc->Brush->Style = bsSolid;
        dc->Brush->Color = BGICOLOR(fill_settings.color);
        {
            TGmPen p(dc);
            dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);
        }

        // потом штриховку
        dc->Brush->Style = fill_settings.pattern;
        dc->Brush->Color = BGICOLOR(BLACK);
        {
            TGmPen p(dc);
            dc->Ellipse(x - xradius, y - yradius, x + xradius, y + yradius);
        }
        // восстановим
        dc->Brush->Color = BGICOLOR(fill_settings.color);
    }
}



void setfillstyle(int style, int col)
{
    fill_settings.color = col;
    switch (style) {
    case  EMPTY_FILL  : fill_settings.pattern = bsClear;   break;
    case  SOLID_FILL  : fill_settings.pattern = bsSolid;   break;
    case  LINE_FILL   : fill_settings.pattern = bsHorizontal; break;
    case  LTSLASH_FILL : fill_settings.pattern = bsVertical;  break;
    case  SLASH_FILL   : fill_settings.pattern = bsBDiagonal; break;
    case  BKSLASH_FILL : fill_settings.pattern = bsFDiagonal; break;
    case  LTBKSLASH_FILL:
    case  HATCH_FILL:
    case  XHATCH_FILL:
    case  INTERLEAVE_FILL : fill_settings.pattern = bsDiagCross;//bsCross;
        break;
    case  WIDE_DOT_FILL:
    case  CLOSE_DOT_FILL:
    case  USER_FILL     : fill_settings.pattern = bsDiagCross;
        break;
    default:  fill_settings.pattern = bsClear;
    }
    if (dc != NULL) {
        dc->Brush->Color = BGICOLOR(fill_settings.color);
        dc->Brush->Style = fill_settings.pattern;

    }

    //    dc->Brush->Style = fill_settings.pattern;
}

void getfillsettings(fillsettingstype* fs)
{
    *fs = fill_settings;
}

void setfillpattern(const char* upattern, int color)
{
    /*
        static HBITMAP hFillBitmap;
        static short bitmap_data[8];
        for (int i = 0; i < 8; i++) {
        bitmap_data[i] = (unsigned char)~upattern[i];
        userfillpattern[i] = upattern[i];
        }
        HBITMAP h = CreateBitmap(8, 8, 1, 1, bitmap_data);
        HBRUSH hb = CreatePatternBrush(h);
        DeleteObject(hBrush[USER_FILL]);
        if (hFillBitmap) {
        DeleteObject(hFillBitmap);
        }
        hFillBitmap = h;
        hBrush[USER_FILL] = hb;
        SelectObject(dc->Handle, hb);
    */
    fill_settings.color = color;
    fill_settings.pattern = bsSolid;
}

void getfillpattern(fillpatterntype fp)
{
    memcpy(fp, userfillpattern, sizeof(userfillpattern));
}

void  setlinestyle(int linestyle, unsigned upattern, int thickness)
{
    line_settings.linestyle = linestyle;
    line_settings.upattern  = upattern;
    line_settings.thickness  = thickness;
    if (dc != NULL) {
        switch (line_settings.linestyle) {
        default : dc->Pen->Style = psSolid; dc->Pen->Width=line_settings.thickness; break;
        case 1: dc->Pen->Style = psDash; dc->Pen->Width=1; break;
        case 2: dc->Pen->Style = psDot; dc->Pen->Width=1; break;
        case 3: dc->Pen->Style = psDashDot; dc->Pen->Width=1; break;
        case 4: dc->Pen->Style = psDashDotDot; dc->Pen->Width=1; break;
        }
    }
}

void  settextjustify(int horiz, int vert)
{
    text_settings.horiz = horiz;
    text_settings.vert  = vert;
}

void  settextstyle(int font, int direction, int charsize)
{
    text_settings.font       = (font < FontCount)  ? font : 0;
    text_settings.direction = direction;
    text_settings.charsize   = charsize;
    select_font();
}

void  setviewport(int left, int top, int right, int bottom,
                  int clip)
{
    view_port.left   = left;
    view_port.top    = top;
    view_port.right  = right;
    view_port.bottom = bottom;
    view_port.clip   = clip;
}
static TEXTMETRIC ptm;
int textheight(const char *str)
{
    if ((dc == NULL) && (_SaveDC != NULL))  {
        GetTextMetrics(
            _SaveDC->Handle,    // handle of device context
            &ptm    // address of text metrics structure
        );
        return ptm.tmHeight;
    }
    if ((dc == NULL) || (!UseNativeFontSize)) {
        int h=font_height[ text_settings.font ];
        if (h==0) return ptm.tmHeight; // хоть какую высоту выдай
        return h;
    }
    GetTextMetrics(
        dc->Handle, // handle of device context
        &ptm    // address of text metrics structure
    );
    //return dc->TextHeight(str);
    return ptm.tmAscent;
}

/*
int textwidthA(const char *str)
{
  if ((dc==NULL)&&(_SaveDC!=NULL))
     return _SaveDC->TextWidth(str);
  if ((dc==NULL)||(!UseNativeFontSize)){
     int ln = strlen(str);
     return font_width[text_settings.font]*ln;
  }
  return dc->TextWidth(str);
}
*/
int textwidth(const char *str)
{
    if (str == NULL)  return 0;
    SIZE sz;
    int l = StrLen(str);

    if ((dc == NULL) && (_SaveDC != NULL)) {
        GetTextExtentPoint32(_SaveDC->Handle, str, l, &sz);
        return sz.cx;
    }
    if ((dc == NULL) || (!UseNativeFontSize)) {
        int ln = strlen(str);
        return font_width[ text_settings.font ] *ln;
    }
    GetTextExtentPoint32(dc->Handle, str, l, &sz);
    return sz.cx;
}

void    getimage(int left, int top, int right, int bottom, void *bitmap) {}
unsigned  imagesize(int left, int top, int right, int bottom)
{
    return 0;
}
void    putimage(int left, int top, const void *bitmap, int op)  {}
void    cleardevice(void)  {}
void    clearviewport(void) {}
void    closegraph(void) {}
int     installuserfont(const char *n)
{
    return 0;
}
//void    outtextxy( int x, int y, const char *textstring ) {}
void    linerel(int dx, int dy)  {}   //{  POINT pos;  GetCurrentPositionEx(dc->Handle, &pos);  lineto(pos.x + dx, pos.y + dy);

////////////////////////////////////////////////////////////////////////////////

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

    view_port.left = 0;
    view_port.top = 0;
    view_port.right =  getmaxx();
    view_port.bottom = getmaxy();

    aspect_ratio_x = aspect_ratio_y = 10000;
}

void initgraph(int* device, int* mode, const char* p)
{
    for (int i = 0; i < FontCount; i++)  Fonts[ i ]  = NULL;
    set_defaults();
    /*
    static short SolidBrushBitmap[8] =
      {~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF, ~0xFF};
    static short LineBrushBitmap[8] =
      {~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0xFF};
    static short LtslashBrushBitmap[8] =
      {~0x01, ~0x02, ~0x04, ~0x08, ~0x10, ~0x20, ~0x40, ~0x80};
    static short SlashBrushBitmap[8] =
      {~0x81, ~0x03, ~0x06, ~0x0C, ~0x18, ~0x30, ~0x60, ~0xC0};
    static short BkslashBrushBitmap[8] =
      {~0xC0, ~0x60, ~0x30, ~0x18, ~0x0C, ~0x06, ~0x03, ~0x81};
    static short LtbkslashBrushBitmap[8] =
      {~0x80, ~0x40, ~0x20, ~0x10, ~0x08, ~0x04, ~0x02, ~0x01};
    static short HatchBrushBitmap[8] =
      {~0x01, ~0x01, ~0x01, ~0x01, ~0x01, ~0x01, ~0x01, ~0xFF};
    static short XhatchBrushBitmap[8] =
      {~0x81, ~0x42, ~0x24, ~0x18, ~0x18, ~0x24, ~0x42, ~0x81};
    static short InterleaveBrushBitmap[8] =
      {~0x55, ~0xAA, ~0x55, ~0xAA, ~0x55, ~0xAA, ~0x55, ~0xAA};
    static short WidedotBrushBitmap[8] =
      {~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0x00, ~0x01};
    static short ClosedotBrushBitmap[8] =
      {~0x44, ~0x00, ~0x11, ~0x00, ~0x44, ~0x00, ~0x11, ~0x00};

     hBackgroundBrush = CreateSolidBrush(0);
     hBrush[EMPTY_FILL] = (HBRUSH)GetStockObject(NULL_BRUSH);
     hBrush[SOLID_FILL] =
            CreatePatternBrush(CreateBitmap(8, 8, 1, 1, SolidBrushBitmap));
     hBrush[LINE_FILL] =
            CreatePatternBrush(CreateBitmap(8, 8, 1, 1, LineBrushBitmap));
     hBrush[LTSLASH_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, LtslashBrushBitmap));
     hBrush[SLASH_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, SlashBrushBitmap));
     hBrush[BKSLASH_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, BkslashBrushBitmap));
     hBrush[LTBKSLASH_FILL] =
            CreatePatternBrush(CreateBitmap(8, 8, 1, 1, LtbkslashBrushBitmap));
     hBrush[HATCH_FILL] =
            CreatePatternBrush(CreateBitmap(8, 8, 1, 1, HatchBrushBitmap));
     hBrush[XHATCH_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, XhatchBrushBitmap));
     hBrush[INTERLEAVE_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, InterleaveBrushBitmap));
     hBrush[WIDE_DOT_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, WidedotBrushBitmap));
     hBrush[CLOSE_DOT_FILL] =
        CreatePatternBrush(CreateBitmap(8, 8, 1, 1, ClosedotBrushBitmap));
     hBrush[USER_FILL] =
            CreatePatternBrush(CreateBitmap(8, 8, 1, 1, SolidBrushBitmap));
    */
}



/*
#ifdef __cplusplus
}
#endif
*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int F_DEFAULT  = 0;
int F_LITT     = 1;
int F_LITT_S   = 2;
int F_LITT_B   = 3;

void InitBgiFont(void);
void SetFont(TFont* , int n);
void InitWinBGI(void)
{
    //   static int fontheight[FontCount] = {12, 12, 14, 20, 14, 14, 14, 14, 14, 14 };
    /*   static int fontheight[FontCount] =
            {14, 12, 14, 16,
             14, 14, 14, 22, 14, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14
             14, 14, 22, 14, 12, 14, 14, 14, 14, 14, 14, 14 };
       static int fontheight[FontCount] =
            {14, 12, 14, 16,
             14, 12, 18, 22, 28, 12, 14, 18, 20, 20, 22, 28, 12, 18, 22, 28,
             30, 28, 28, 12, 12, 16, 10, 6, 6, 6, 6, 6 };
    */

    //Classes::RegisterClass(__classid(TFont));


    initgraph(NULL, NULL, "");
    InitBgiFont();
    for (int i = 0; i < FontCount; i++) {
        if (!Fonts[ i ]) {
            Fonts[ i ]  = new TFont();
            Fonts[ i ] ->Name = "Arial";
            Fonts[ i ] ->Charset = RUSSIAN_CHARSET;
            Fonts[ i ] ->Pitch = TFontPitch()  << fpFixed;
            Fonts[ i ] ->Height = 90;
            //        Fonts[i]->Height = fontheight[i];
            SetFont(Fonts[ i ] , i);
        }


        /*
              {
                SIZE ss;
                text_settings.font = i;
                select_font();
                GetTextExtentPoint32(dc->Handle, "Ш", 1, &ss);
                GetTextMetrics(dc->Handle, &font_tm[i]);
                if( !font_width[i] )
                                font_width[i] = ss.cx;
                if( !font_height[i] )
                                font_height[i] = ss.cy-font_tm[i].tmInternalLeading;
              }
        */
    }
}

void _SetTextStyle(unsigned int font)
{
    text_settings.font = (font < FontCount)  ? font : 0;
    select_font();
}

//ura
void _SetTextSize(int charsize)
{
    text_settings.charsize = charsize;
    select_font();
}
/*
void SetTextStyle( unsigned int font, int direction, int charsize )
{
    settextstyle( font, direction, charsize );
}
*/
void _SetText(unsigned int font, int d1, int d2)
{
    text_settings.font = (font < FontCount)  ? font : 0;
    select_font();
    settextjustify(d1, d2);
}

void OutTextXY(int x, int y, char* str)
{
    if (strlen(str) == 0)  return;
    int dy = 0;//ptm->tmInternalLeading;
    //int dy2 = ptm->tmExternalLeading;
    int dx = 0;

    int tw = textwidth(str);
    int th = textheight(str);

    switch (text_settings.horiz)  {
    case LEFT_TEXT:    dx = 0; break;
    case CENTER_TEXT:  {
        dx = (0.5 + 1.*tw / 2);
    }
    break;
    case RIGHT_TEXT:   dx = tw; break;
    }
    switch (text_settings.vert)  {
    case TOP_TEXT:        dy= 0; break;
    case BOTTOM_TEXT:     dy= th; break;
    case CENTER_TEXT: {
        dy = (0.5 + 1.*th / 2) /*-1*/;
    }
    break;
    }

    tracecoord(x - dx, y - dy); tracecoord(x - dx + tw, y - dy);
    tracecoord(x - dx, y - dy + th); tracecoord(x - dx + tw, y - dy + th);

    if (dc != NULL) {
        //TColor OC=dc->Pen->Color;
        TBrushStyle obs = dc->Brush->Style;
        dc->Font->Color = BGICOLOR(bgiColor);
        dc->Brush->Style = bsClear;
        dc->TextOut(x - dx, y - dy, str);
        dc->Brush->Style = obs;
        /*
          int om=::SetBkMode(dc->Handle, TRANSPARENT );
          ::SetTextColor(dc->Handle, BGICOLOR(bgiColor) );
          dc->TextOut(x-dx, y-dy, n_str);
          ::SetBkMode(dc->Handle, om );
          */

    }

#ifdef BGIDBG
    setcolor(4);
    rectangle(x - dx, y - dy, x - dx + tw, y - dy + th);
#endif
}


void DestroyFonts()
{
    for (int i = 0; i < FontCount; i++)
        if (Fonts[ i ])
            delete Fonts[ i ];
}

extern TDAC DAC[ 32 ];
extern int SwapPal;
//VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class WinBGIModule
{
public:
    TCriticalSection *CS;
    TCanvas* CashCnv;

    WinBGIModule() : CS(0), CashCnv(0) {
        //BgiPalette=0;
    }

    void Open() {
        if (!CS)  {
            CS = new TCriticalSection();
            InitWinBGI();
            Get_DAC();
            //if( UseBGIPalette && !BgiPalette )
            //    BgiPalette = new TBgiPalette();
        }
    }

    ~WinBGIModule() {
        DestroyFonts();
        if (CashCnv)  delete CashCnv;
        //if( BgiPalette )  {
        //    delete BgiPalette;
        //    BgiPalette=0;
        //}
        delete CS;
    }
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static WinBGIModule BGI;
static int CountWinBgiDC = 0;
//----------------------------------------------------------------------------
void WinBgiDC::Open(TCanvas* pdc)
{
    CountWinBgiDC++;
    BGI.Open();
    BGI.CS->Enter();

    if (CountWinBgiDC != 1) {
        //throw "CountWinBgiDC != 1 debug можно закоментарить";
    }

    SaveIndex = 0;
    dc = pdc;
    if (dc) {
        SaveIndex = ::SaveDC(dc->Handle);
        //if( BgiPalette ) {
        //    pOldPalette = ::SelectPalette( dc->Handle, BgiPalette->Handle(), TRUE );
        //    ::RealizePalette( dc->Handle );
        //}
        dc->Refresh();
    }
}
//----------------------------------------------------------------------------
void WinBgiDC::Close()
{
    if (dc) {
        //if( BgiPalette )
        //    ::SelectPalette( dc->Handle, pOldPalette, TRUE );
        ::RestoreDC(dc->Handle, SaveIndex);
        dc->Refresh();
        dc = NULL;
    }
    BGI.CS->Leave();

    CountWinBgiDC--;
}
//----------------------------------------------------------------------------
WinBgiDC::WinBgiDC(TCanvas* c)
{
    if (c == NULL)  return;
    Open(c);
}
//----------------------------------------------------------------------------
WinBgiDC::WinBgiDC(HDC hdc)
{
    if (!BGI.CashCnv)
        BGI.CashCnv = new TCanvas();
    BGI.CashCnv->Handle = hdc;
    Open(BGI.CashCnv);
}
//----------------------------------------------------------------------------
// flag - переходный период флаг для ГДИ++
WinBgiDC::WinBgiDC(TCanvas* pdc, int flag)
{
    HDC hdc = pdc->Handle;
    if (!BGI.CashCnv)
        BGI.CashCnv = new TCanvas();
    BGI.CashCnv->Handle = hdc;
    Open(BGI.CashCnv);
}
//----------------------------------------------------------------------------
WinBgiDC::~WinBgiDC(void)
{
    Close();
}

void WinBgiDC::SwapDACColor()
{
    if (dc == NULL || !SwapPal)  return;
    /*if( BgiPalette )  {
        ::SelectPalette( dc->Handle, BgiPalette->Handle(), TRUE );
        ::RealizePalette( dc->Handle );
        LPLOGPALETTE lpLogPal = BgiPalette->LogPal();
        for ( int i = 0; i<ARRAYSIZE( DAC ); i++ )   {
            if(  DAC[ i ].dt != 0 )  DAC[ i ].idx = !DAC[ i ].idx;
            lpLogPal->palPalEntry[ i ].peRed   = DAC[ i ].pe[ DAC[ i ].idx ].peRed*4.;
            lpLogPal->palPalEntry[ i ].peGreen = DAC[ i ].pe[ DAC[ i ].idx ].peGreen*4.;
            lpLogPal->palPalEntry[ i ].peBlue  = DAC[ i ].pe[ DAC[ i ].idx ].peBlue*4.;
        }
        ::AnimatePalette( BgiPalette->Handle(), 0, ARRAYSIZE( DAC ), lpLogPal->palPalEntry );
    }
    else*/ {
        SwapDACColor();
        //        for (int i = 0; i<ARRAYSIZE(DAC); i++)
        //            if( DAC[i].dt != 0 ) DAC[i].idx = !DAC[i].idx;
        //        Update_DAC();
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD
void * _GetFont(int i)
{
    if (i >= FontCount)  return NULL;
    return Fonts[ i ];
}
void _SetFont(int i, void * F)
{
    if (i >= FontCount)  return;
    Fonts[ i ] ->Assign((TFont *) F);
    if (dc != NULL)  {
        TFont * olfF;
        //SetFontParams(olfF,dc->Font);
        olfF = dc->Font;
        //SetFontParams(dc->Font,(TFont *)F);
        dc->Font = (TFont *) F;
        font_height[ i ]  = dc->TextHeight("9");
        font_width[ i ] = dc->TextWidth("9");
        //SetFontParams(dc->Font,olfF);
        dc->Font = olfF;
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static char FontFileNames[ FontCount ][ 20 ]  = {
    "FNT/axx14___.XXX",            //  00
    "FNT/axx12___.XXX",            //  01
    "FNT/axx14___.XXX",            //  02
    "FNT/axx16___.XXX",            //  03
    "FNT/axx90___.NUL",            //  04
    "FNT/cur12___.BFT",    //101   //  05
    "FNT/cur18___.BFT",    //102   //  06
    "FNT/cur22___.BFT",            //  07
    "FNT/cur28___.BFT",            //  08
    "FNT/tim12___.BFT",            //  09
    "FNT/tim14___.BFT",            //  10
    "FNT/tim18___.BFT",            //  11
    "FNT/tim20___.BFT",            //  12
    "FNT/tim20_b_.BFT",            //  13
    "FNT/tim22___.BFT",            //  14
    "FNT/tim28___.BFT",            //  15
    "FNT/ari12___.BFT",    //12    //  16
    "FNT/ari18___.BFT",    //13    //  17
    "FNT/ari22___.BFT",    //14    //  18
    "FNT/ari28___.BFT",    //15    //  19
    "FNT/tim30_b_.BFT",    //16    //  20
    "FNT/tim28_b_.BFT",    //17    //  21
    "FNT/cur28_b_.BFT",    //18    //  22
    "FNT/ari12_b_.BFT",    //17    //  23
    "FNT/cur12_b_.BFT",    //18    //  24
    "FNT/cur16___.BFT",    //19    //  25
    "FNT/ari10_b_.BFT",    //20    //  26
    "FNT/win10___.BFT",     //21   //  27
    "FNT/vW210___.BFT",     //22   //  28
    "FNT/sW310___.BFT",     //23   //  29
    "FNT/kWb10___.BFT",     //24   //  30
    "FNT/iTe10___.BFT"     //25    //  31


};

char BgiCfgFileName[ 256 ]  = "bgifnt.cfg";
void InitBgiFont(void)
{
    ifstream is(BgiCfgFileName);
    if (is.is_open())
        for (int i = 0; i < FontCount && is.good(); i++) {
            ws(is).get(FontFileNames[ i ], sizeof(FontFileNames[ i ]));
            is.ignore(80, '\n');
        }
}
void SetFont(TFont* Font, int nn)
{
    if (! strlen(FontFileNames[ nn ]))  return;
    switch (FontFileNames[ nn ][ 4 ]) {
    case 'A':
    case 'a': Font->Name = "Arial"; break;
    case 'T':
    case 't': Font->Name = "Times New Roman"; break;
    case 'C':
    case 'c': Font->Name = "Courier New"; break;
    case 'W':
    case 'w': Font->Name = "Wingdings"; break;
    case 'V':
    case 'v': Font->Name = "Wingdings 2"; break;
    case 'S':
    case 's': Font->Name = "Wingdings 3"; break;
    case 'K':
    case 'k': Font->Name = "Webdings"; break;
    case 'I':
    case 'i': Font->Name = "Terminal"; break;
    default: return;
    }
    Font->Charset = RUSSIAN_CHARSET;
    if (FontFileNames[ nn ][ 4 ] == 'w') {
        Font->Charset = DEFAULT_CHARSET;
    }
    if (FontFileNames[ nn ][ 4 ] == 's') {
        Font->Charset = DEFAULT_CHARSET;
    }
    if (FontFileNames[ nn ][ 4 ] == 'v') {
        Font->Charset = DEFAULT_CHARSET;
    }
    if (FontFileNames[ nn ][ 4 ] == 'k') {
        Font->Charset = DEFAULT_CHARSET;
    }
    if (FontFileNames[ nn ][ 4 ] == 'i') {
        Font->Charset = DEFAULT_CHARSET;
    } else
        Font->Pitch = TFontPitch()  << fpFixed;


    if (FontFileNames[ nn ][ 10 ] == 'b')
        Font->Style = TFontStyles() << fsBold;
    int sz = -atoi(&FontFileNames[ nn ][ 7 ]);
    if (sz)  Font->Size = sz;
    //  Font->Height = sz;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


TCanvas*  BgiCanvas(void)
{
    if (dc != NULL)  return dc;
    return _SaveDC;
}



TFont*   Font(int font)
{
    return font < FontCount ? Fonts[ font ]  : NULL;
}

TColor   Color(__int8 palColor)
{
    return BGICOLOR(palColor);
}





void   DrawText(int x, int y, int tw, int th, char* str)
{
    if (strlen(str) == 0)  return;
    //OemToAnsi( str,n_str );

    tracecoord(x, y); tracecoord(x + tw, y);
    tracecoord(x, y + th); tracecoord(x + tw, y + th);

    if (dc != NULL) {
        int om =::SetBkMode(dc->Handle, TRANSPARENT);
        ::SetTextColor(dc->Handle, BGICOLOR(bgiColor));
        RECT R;
        UINT uF = DT_NOCLIP   | DT_SINGLELINE | DT_EXTERNALLEADING   ;
        R.left = x; R.top = y; R.right = x + tw; R.bottom = y + th;
        if (R.left>R.right){int zz=R.left;R.left=R.right;R.right=zz;}

        switch (text_settings.horiz)  {
        case LEFT_TEXT:    uF=uF | DT_LEFT;  break;
        case CENTER_TEXT:  uF=uF | DT_CENTER; break;
        case RIGHT_TEXT:   uF=uF | DT_RIGHT; break;
        }
        switch (text_settings.vert)  {
        case TOP_TEXT:     uF=uF | DT_TOP           ; break;
        case BOTTOM_TEXT:  uF=uF | DT_BOTTOM    ; break;
        case CENTER_TEXT:  uF=uF | DT_VCENTER   ; break;
        }
        ::DrawText(dc->Handle,       // handle to device context
                   str,            // pointer to string to draw
                   strlen(str),     // string length, in characters
                   &R,    // pointer to structure with formatting dimensions
                   uF     // text-drawing flags
                  );
        ::SetBkMode(dc->Handle, om);
    }
#ifdef BGIDBG
    setcolor(4);
    rectangle(x, y, x + tw, y + th);
#endif
} /*
void   DrawTextWithPr( TRect R,char* str,int priz ) {DrawTextWithPr( R.Left,R.Top,R.Width(),R.Height(),str,priz );}
void   DrawTextWithPr( int cx,int cy,int cw,int ch,char* str,int priz )
{
    //1 2   3
    //8 9   4
    //7 6   5
    priz=priz%10;
    if ( priz==0 )  return ;
    int tw=textwidth( str );
    int th=textheight( str );
    int tsh,tsv;
    int tx,ty;
    switch ( priz ) {
    case  1:  tx=cx-tw;        ty=cy-th;
        tsh=RIGHT_TEXT;  tsv=BOTTOM_TEXT;
        break;
    case  2:  tx=cx   ;        ty=cy-th;        tw=cw;
        tsh=DT_CENTER;   tsv=BOTTOM_TEXT;
        break;
    case  3:  tx=cx+cw;        ty=cy-th;
        tsh=LEFT_TEXT;   tsv=BOTTOM_TEXT;
        break;

    case  8:  tx=cx-tw;        ty=cy   ;        th=ch;
        tsh=RIGHT_TEXT;  tsv=DT_VCENTER;
        break;
    case  9:  tx=cx   ;        ty=cy   ;        th=ch;   tw=cw;
        tsh=DT_CENTER;   tsv=DT_VCENTER;
        break;
    case  4:  tx=cx+cw;        ty=cy   ;        th=ch;
        tsh=LEFT_TEXT;   tsv=DT_VCENTER;
        break;

    case  7:  tx=cx-tw;        ty=cy+ch;
        tsh=RIGHT_TEXT;  tsv=DT_TOP;
        break;
    case  6:  tx=cx   ;        ty=cy+ch;        tw=cw;
        tsh=DT_CENTER;   tsv=DT_TOP;
        break;
    case  5:  tx=cx+cw;        ty=cy+ch;
        tsh=LEFT_TEXT;   tsv=DT_TOP;
        break;
    }
    int otsh=text_settings.horiz;
    int otsv=text_settings.vert ;
    text_settings.horiz =tsh;text_settings.vert  =tsv;
    DrawText( tx,ty,tw,th,str );
    text_settings.horiz =otsh;text_settings.vert =otsv;
}
*/

void PolyColor(int iBrushColor, const TPoint * Points, const int * iColors, const int Points_Count, int PenW)
{
    for (int i = 0; i < Points_Count; i++)
        tracecoord(Points[ i ].x, Points[ i ].y);
    TCanvas * Cnv = dc;
    if (Cnv == NULL)  return;

    TColor BrushColor = BGICOLOR(iBrushColor);

    Cnv->Pen->Color = BrushColor;
    Cnv->Brush->Color = BrushColor;
    if ((fill_settings.pattern != bsSolid) && (fill_settings.pattern != bsClear)) {
        Cnv->Brush->Style = bsSolid;
        Cnv->Polygon(Points, Points_Count - 1);
        Cnv->Brush->Color = clBlack;
    }
    bool bNormPol = true;
    int iColors0 = iColors[ 0 ];

    for (int i = 1; i < Points_Count; i++)
        if (iColors0 != iColors[ i ]) {bNormPol = false;break;}



    Cnv->Brush->Style = fill_settings.pattern;
    Cnv->Pen->Width = PenW;
    if (bNormPol) {
        Cnv->Pen->Style = psSolid;
        //Cnv->Brush->Color = BrushColor;
        Cnv->Pen->Color = BGICOLOR(iColors0);
        Cnv->Polygon(Points, Points_Count - 1);

    } else {

        //Cnv->Pen->Style = psClear;
        Cnv->Polygon(Points, Points_Count - 1);
        Cnv->Pen->Color = BrushColor;
        Cnv->Polyline(Points,Points_Count - 1);
        Cnv->Pen->Style = psSolid;

        for (int i = 1; i < Points_Count; i++) {

            if ((iBrushColor == iColors[ i-1 ]) && (iBrushColor != FON))  continue;
            Cnv->Pen->Color = BGICOLOR(iColors[ i-1 ]);

            Cnv->MoveTo(Points[ i-1 ].x, Points[ i-1 ].y);
            Cnv->LineTo(Points[ i ].x, Points[ i ].y);
            //Cnv->Polyline(&Points[i-1],1);
            Cnv->Pixels[ Points[ i ].x ][ Points[ i ].y ] = Cnv->Pen->Color;


        }
        if ((iBrushColor != iColors[ Points_Count-1 ]) || ((iBrushColor == FON) && (iColors[ Points_Count-1 ] == FON))) {
            Cnv->Pen->Color = BGICOLOR(iColors[ Points_Count-1 ]);
            Cnv->MoveTo(Points[ Points_Count-1 ].x, Points[ Points_Count-1 ].y);
            Cnv->LineTo(Points[ 0 ].x, Points[ 0 ].y);
            Cnv->Pixels[ Points[ 0 ].x ][ Points[ 0 ].y ] = Cnv->Pen->Color;

        }
    }
    /*Cnv->Pen->Width=1;
    Cnv->Pen->Color=clBlack;
    Cnv->Brush->Color=clGreen;
    for ( int i=0;i<Points_Count;i++ ) {
        Cnv->Rectangle(Points[ i ].x-2,Points[ i ].y-2,Points[ i ].x+2,Points[ i ].y+2);
        //Cnv->TextOut(Points[ i ].x+5,Points[ i ].y,IntToStr(i));
    } */
}


int Draw_Ramka(int left, int top, int right, int bottom, UINT edge, UINT grfFlags)
{
    if (top > bottom)  swap(top, bottom);
    if (left > right)  swap(left, right);

    POINT rect[ 5 ];
    rect[ 0 ].x = left, rect[ 0 ].y = top;
    rect[ 1 ].x = right, rect[ 1 ].y = top;
    rect[ 2 ].x = right, rect[ 2 ].y = bottom;
    rect[ 3 ].x = left, rect[ 3 ].y = bottom;
    rect[ 4 ].x = left, rect[ 4 ].y = top;
    tracecoord(rect, 4);

    if (dc == NULL)  return 0;
    RECT qrc;
    qrc.left = left; qrc.top = top; qrc.right = right; qrc.bottom = bottom;
    return  DrawEdge(dc->Handle, &qrc, edge, grfFlags);
}

int GetGradientColor(int Color, float factor)
{
    if (factor == 1.) return Color;
    if (Color & 0xff000000) {
        Color = ColorToRGB(Color);
        // не цвет а индекс в палитре или еще что
        // throw ("GradientColor: it is not a RGB color");
    }
    int r = GetRValue(Color);
    int g = GetGValue(Color);
    int b = GetBValue(Color);

    double FACTOR = factor; //FACTOR= -0.8;
    /*  int i = (int)(1.0/(1.0-FACTOR));
      if ( r == 0 && g == 0 && b == 0)
                    return RGB(i, i, i);
      if ( r > 0 && r < i ) r = i;
      if ( g > 0 && g < i ) g = i;
      if ( b > 0 && b < i ) b = i;*/
    return RGB(min((int)(r / FACTOR), 255),
               min((int)(g / FACTOR), 255),
               min((int)(b / FACTOR), 255));

}

// функции для работы с EMF
bool drawemf(CONST RECT *lpRect,
             const char * szimagename,
             int animstep
            )
{
    tracecoord(lpRect->left,        lpRect->top);
    tracecoord(lpRect->left,        lpRect->bottom);
    tracecoord(lpRect->right,       lpRect->top);
    tracecoord(lpRect->right,       lpRect->bottom);
    if ( lpRect->left==lpRect->right || lpRect->top==lpRect->bottom) return true;
    if (dc == NULL) return true;
    return im_drawemf(dc->Handle, lpRect, szimagename, animstep);
}



