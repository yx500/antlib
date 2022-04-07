#ifndef WINBGI_CORE_H
#define WINBGI_CORE_H

//  Copyright GTSS c 2006. All Rights Reserved.

#if !defined(__COLORS)
#define __COLORS
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
#endif

/* Line styles for get/setlinestyle */
enum line_styles
{
  SOLID_LINE = 0,
  DOTTED_LINE = 1,
  CENTER_LINE = 2,
  DASHED_LINE = 3,
  USERBIT_LINE = 4, /* User defined line style */
};

/* Line widths for get/setlinestyle */
enum line_widths
{
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

#define HORIZ_DIR 0 /* left to right */
#define VERT_DIR 1  /* bottom to top */

#define USER_CHAR_SIZE 0 /* user-defined char size */

/* Fill patterns for get/setfillstyle */
enum fill_patterns
{
  EMPTY_FILL,      /* 0 fills area in background color */
  SOLID_FILL,      /* 1 fills area in solid fill color */
  LINE_FILL,       /* 2 --- fill */
  LTSLASH_FILL,    /* 3 /// fill */
  SLASH_FILL,      /* 4 /// fill with thick lines */
  BKSLASH_FILL,    /* 5 \\\ fill with thick lines */
  LTBKSLASH_FILL,  /* 6 \\\ fill */
  HATCH_FILL,      /* 7 light hatch fill */
  XHATCH_FILL,     /* heavy cross hatch fill */
  INTERLEAVE_FILL, /* interleaving line fill */
  WIDE_DOT_FILL,   /* Widely spaced dot fill */
  CLOSE_DOT_FILL,  /* Closely spaced dot fill */
  USER_FILL        /* user defined fill */
};

/* Horizontal and vertical justification for settextjustify */
enum text_just
{
  LEFT_TEXT = 0x0000,
  CENTER_TEXT = 0x0001,
  RIGHT_TEXT = 0x0002,
  BOTTOM_TEXT = 0x0000,
  TOP_TEXT = 0x0002
};

struct linesettingstype
{
  int linestyle;
  unsigned upattern;
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
void arc(int x, int y, int start_angle, int end_angle, int radius);
void pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4);
void drawpoly(int __numpoints, const int* __polypoints);
void fillellipse(int __x, int __y, int __xradius, int __yradius);
void fillpoly(int __numpoints, const int* __polypoints);
int getcolor(void);
void getfillsettings(struct fillsettingstype* __fillinfo);
void getimage(int __left, int __top, int __right, int __bottom,
              void* __bitmap);
int getmaxx(void);
int getmaxy(void);
void gettextsettings(struct textsettingstype* __texttypeinfo);
void line(int __x1, int __y1, int __x2, int __y2);
void outtextxy(int __x, int __y, const char* __textstring);
void rectangle(int __left, int __top, int __right, int __bottom);
void setcolor(int __color);
void setfillstyle(int __pattern, int __color);
void setlinestyle(int __linestyle, unsigned __upattern,
                  int __thickness);
void settextjustify(int __horiz, int __vert);
void settextstyle(int __font, int __direction, int __charsize);
int textheight(const char* __textstring);
int textwidth(const char* __textstring);

void setbkcolor(int __color);
void setfillpattern(const char* __upattern, int __color);
void setviewport(int __left, int __top, int __right, int __bottom,
                 int __clip);
unsigned imagesize(int __left, int __top, int __right, int __bottom);
void putimage(int __left, int __top, const void* __bitmap,
              int __op);
unsigned getpixel(int __x, int __y);
void putpixel(int __x, int __y, int __color);
void cleardevice(void);
void clearviewport(void);
void closegraph(void);
int installuserfont(const char* __name);
void initgraph(int* device, int* mode, const char* p);

#endif
