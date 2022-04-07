#ifndef BGI_H
#define BGI_H

#include "winpalet.h"

enum COLORS
{
  BLACK, /* dark colors */
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  LIGHTGRAY,
  DARKGRAY, /* light colors */
  LIGHTBLUE,
  LIGHTGREEN,
  LIGHTCYAN,
  LIGHTRED,
  LIGHTMAGENTA,
  YELLOW,
  WHITE
};

enum line_styles
{ /* Line styles for get/setlinestyle */
  SOLID_LINE = 0,
  DOTTED_LINE = 1,
  CENTER_LINE = 2,
  DASHED_LINE = 3,
  USERBIT_LINE = 4, /* User defined line style */
};

enum line_widths
{ /* Line widths for get/setlinestyle */
  NORM_WIDTH = 1,
  THICK_WIDTH = 3,
};

enum font_names
{
  DEFAULT_FONT = 0, /* 8x8 bit mapped font */
  TRIPLEX_FONT = 1, /* "Stroked" fonts */
  SMALL_FONT = 2,
  SANS_SERIF_FONT = 3,
  GOTHIC_FONT = 4,
  SCRIPT_FONT = 5,
  SIMPLEX_FONT = 6,
  TRIPLEX_SCR_FONT = 7,
  COMPLEX_FONT = 8,
  EUROPEAN_FONT = 9,
  BOLD_FONT = 10
};

enum fill_patterns
{                  /* Fill patterns for get/setfillstyle */
  EMPTY_FILL,      /* fills area in background color */
  SOLID_FILL,      /* fills area in solid fill color */
  LINE_FILL,       /* --- fill */
  LTSLASH_FILL,    /* /// fill */
  SLASH_FILL,      /* /// fill with thick lines */
  BKSLASH_FILL,    /* \\\ fill with thick lines */
  LTBKSLASH_FILL,  /* \\\ fill */
  HATCH_FILL,      /* light hatch fill */
  XHATCH_FILL,     /* heavy cross hatch fill */
  INTERLEAVE_FILL, /* interleaving line fill */
  WIDE_DOT_FILL,   /* Widely spaced dot fill */
  CLOSE_DOT_FILL,  /* Closely spaced dot fill */
  USER_FILL        /* user defined fill */
};

enum putimage_ops
{           /* BitBlt operators for putimage */
  COPY_PUT, /* MOV */
  XOR_PUT,  /* XOR */
  OR_PUT,   /* OR  */
  AND_PUT,  /* AND */
  NOT_PUT   /* NOT */
};

enum text_just
{ /* Horizontal and vertical justification
     for settextjustify */
  LEFT_TEXT = 0x0000,
  CENTER_TEXT = 0x0001,
  RIGHT_TEXT = 0x0002,

  BOTTOM_TEXT = 0x0000,
  TOP_TEXT = 0x0002
};

struct linesettingstype
{
  int linestyle;
  unsigned int upattern;
  int thickness;
};

struct textsettingstype
{
  int font;
  int direction;
  int charsize;
  int horiz;
  int vert;
};

struct fillsettingstype
{
  int pattern;
  int color;
};

struct pointtype
{
  int x, y;
};

struct viewporttype
{
  int left, top, right, bottom;
  int clip;
};

struct arccoordstype
{
  int x, y;
  int xstart, ystart, xend, yend;
};

void bar(int __left, int __top, int __right, int __bottom);
void circle(int __x, int __y, int __radius);
// void  arc(int x, int y, int start_angle, int end_angle, int radius);
void pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4);
void drawpoly(int __numpoints, const int* __polypoints);
void fillellipse(int __x, int __y, int __xradius, int __yradius);
void fillpoly(int __numpoints, const int* __polypoints);
int getmaxx(void);
int getmaxy(void);
void line(int __x1, int __y1, int __x2, int __y2);
void rectangle(int __left, int __top, int __right, int __bottom);
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight);
void setcolor(int __color);
void setfillpattern(const char* __upattern, int __color);
void setfillstyle(int __pattern, int __color);
void setlinestyle(int __linestyle, unsigned __upattern, int __thickness);
void settextjustify(int __horiz, int __vert);
void settextstyle(int __font, int __direction, int __charsize);
void _SetText(unsigned int font, int d1, int d2);
void _SetTextSize(int charsize);
int textheight(const char* __textstring);
int textwidth(const char* __textstring);
void OutTextXY(int x, int y, const char* str);
void DrawText(int x, int y, int tw, int th, const char* str);

/*-----------------------------------------*/
// FONTS
#define HORIZ_DIR 0 /* left to right */
#define VERT_DIR 1  /* bottom to top */

#define F_DEFAULT 0
#define F_LITT 1
#define F_LITT_S 2
#define F_LITT_B 3

#define NULLFONT 0 + 4
#define COURE12 1 + 4
#define COURE18 2 + 4
#define COURE22 3 + 4
#define COURE28 4 + 4
#define TIMES12 5 + 4
#define TIMES14 6 + 4
#define TIMES18 7 + 4
#define TIMES20 8 + 4
#define TIMES20b 9 + 4
#define TIMES22 10 + 4
#define TIMES28 11 + 4
#define ARIAL12 12 + 4
#define ARIAL18 13 + 4
#define ARIAL22 14 + 4
#define ARIAL28 15 + 4
#define TIMES30b 16 + 4
#define TIMES28b 17 + 4
#define COURE28b 18 + 4
#define ARIAL12b 19 + 4
#define COURE12b 20 + 4
#define COURE16 21 + 4
#define ARIAL10b 22 + 4
#define WINDI10b 23 + 4

#define WIND210b 24 + 4
#define WIND310b 25 + 4
#define WEBDI10b 26 + 4
#define TERMI10b 27 + 4

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern bool UseNativeFontSize;
extern bool NoGmPen;
extern int UseBGIPalette;

void PolyColor(int iBrushColor, const TPoint* Points, const int* iColors, const int Points_Count, int PenW = 1);
int Draw_Ramka(int left, int top, int right, int bottom, int edge = BDR_RAISEDINNER, int grfFlags = BF_RECT);

TRect ClearBgiCoverRect(void);
TRect GetBgiCoverRect(void);

void SwapDACColor();
int Get_DAC(void);

void* SetNullDC();
void RestoreNullDC();

void SetGradientFactor(float AGradientFactor);

bool drawemf(const RECT* lpRect, const char* szimagename, int animstep = 0);

#endif // BGI_H
