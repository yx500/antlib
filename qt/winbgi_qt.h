#pragma once
//----------------------------------------------------------------------------
//  Copyright GTSS c 2022. All Rights Reserved.
//----------------------------------------------------------------------------
#include <systypes.h>
#include <QPainter>




#if !defined(__COLORS)
#define __COLORS

typedef struct tagPOINT
{
  int  x;
  int  y;
} POINT;

typedef struct tagRECT
{
  int    left;
  int    top;
  int    right;
  int    bottom;
} RECT;


struct TPoint : public POINT
  {
    TPoint() {}
    TPoint(int _x, int _y) { x=_x; y=_y; }
    TPoint(POINT& pt)
    {
      x = pt.x;
      y = pt.y;
    }

  };


enum COLORS {
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,           /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};
#endif


enum line_styles {      /* Line styles for get/setlinestyle */
    SOLID_LINE   = 0,
    DOTTED_LINE  = 1,
    CENTER_LINE  = 2,
    DASHED_LINE  = 3,
    USERBIT_LINE = 4,   /* User defined line style */
};

enum line_widths {      /* Line widths for get/setlinestyle */
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3,
};

enum font_names {
    DEFAULT_FONT    = 0,    /* 8x8 bit mapped font */
    TRIPLEX_FONT    = 1,    /* "Stroked" fonts */
    SMALL_FONT  = 2,
    SANS_SERIF_FONT = 3,
    GOTHIC_FONT = 4,
    SCRIPT_FONT = 5,
    SIMPLEX_FONT = 6,
    TRIPLEX_SCR_FONT = 7,
    COMPLEX_FONT = 8,
    EUROPEAN_FONT = 9,
    BOLD_FONT = 10
};

#define HORIZ_DIR   0   /* left to right */
#define VERT_DIR    1   /* bottom to top */

#define USER_CHAR_SIZE  0   /* user-defined char size */

enum fill_patterns {        /* Fill patterns for get/setfillstyle */
    EMPTY_FILL,     /* fills area in background color */
    SOLID_FILL,     /* fills area in solid fill color */
    LINE_FILL,      /* --- fill */
    LTSLASH_FILL,       /* /// fill */
    SLASH_FILL,     /* /// fill with thick lines */
    BKSLASH_FILL,       /* \\\ fill with thick lines */
    LTBKSLASH_FILL,     /* \\\ fill */
    HATCH_FILL,     /* light hatch fill */
    XHATCH_FILL,        /* heavy cross hatch fill */
    INTERLEAVE_FILL,    /* interleaving line fill */
    WIDE_DOT_FILL,      /* Widely spaced dot fill */
    CLOSE_DOT_FILL,     /* Closely spaced dot fill */
    USER_FILL       /* user defined fill */
};

enum putimage_ops {     /* BitBlt operators for putimage */
    COPY_PUT,       /* MOV */
    XOR_PUT,        /* XOR */
    OR_PUT,         /* OR  */
    AND_PUT,        /* AND */
    NOT_PUT         /* NOT */
};

enum text_just {        /* Horizontal and vertical justification
                           for settextjustify */
    LEFT_TEXT   = 0x0000,
    CENTER_TEXT = 0x0001,
    RIGHT_TEXT  = 0x0002,

    BOTTOM_TEXT = 0x0000,
    TOP_TEXT    = 0x0002
};



struct linesettingstype {
    int linestyle;
    unsigned upattern;
    int thickness;
};

struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
};

struct fillsettingstype {
    int pattern;
    int color;
};

struct pointtype {
    int x, y;
};

struct viewporttype {
    int left, top, right, bottom;
    int clip;
};

struct arccoordstype {
    int x, y;
    int xstart, ystart, xend, yend;
};


void       _WINBGI_ bar(int __left, int __top, int __right, int __bottom);
void       _WINBGI_ circle(int __x, int __y, int __radius);
void       _WINBGI_ arc(int x, int y, int start_angle, int end_angle, int radius);
void       _WINBGI_ pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4);
//void       _WINBGI_ cleardevice( void );
//void       _WINBGI_ clearviewport( void );
void       _WINBGI_ drawpoly(int __numpoints, const int *__polypoints);
void       _WINBGI_ fillellipse(int __x, int __y, int __xradius, int __yradius);
void       _WINBGI_ fillpoly(int __numpoints, const int  *__polypoints);
//int        _WINBGI_ getcolor( void );
//void       _WINBGI_ getfillsettings( struct fillsettingstype  *__fillinfo );
//void       _WINBGI_ getimage( int __left, int __top, int __right, int __bottom,
//                              void  *__bitmap );
int        _WINBGI_ getmaxx(void);
int        _WINBGI_ getmaxy(void);
//unsigned   _WINBGI_ getpixel( int __x, int __y );
//void       _WINBGI_ gettextsettings( struct textsettingstype  *__texttypeinfo );
//unsigned   _WINBGI_ imagesize( int __left, int __top, int __right, int __bottom );
void       _WINBGI_ line(int __x1, int __y1, int __x2, int __y2);
//void       _WINBGI_ outtextxy(int __x, int __y, const char  *__textstring);
//void       _WINBGI_ putimage( int __left, int __top, const void  *__bitmap,int __op );
//void       _WINBGI_ putpixel( int __x, int __y, int __color );
void       _WINBGI_ rectangle(int __left, int __top, int __right, int __bottom);
void       _WINBGI_ roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight);



//void       _WINBGI_ setbkcolor( int __color );
void       _WINBGI_ setcolor(int __color);
void       _WINBGI_ setfillpattern(const char  *__upattern, int __color);
void       _WINBGI_ setfillstyle(int __pattern, int __color);
void       _WINBGI_ setlinestyle(int __linestyle, unsigned __upattern,
                                 int __thickness);
void       _WINBGI_ settextjustify(int __horiz, int __vert);
void       _WINBGI_ settextstyle(int __font, int __direction, int __charsize);
void                _SetText(unsigned int font, int d1, int d2);
void                _SetTextSize(int charsize);
//void       _WINBGI_ setviewport( int __left, int __top, int __right, int __bottom, int __clip );
int        _WINBGI_ textheight(const char  *__textstring);
int        _WINBGI_ textwidth(const char  *__textstring);
void                OutTextXY(int x, int y, char* str);
void                DrawText(int x, int y, int tw, int th, char* str);
//void       _WINBGI_ closegraph( void );
//int        _WINBGI_ installuserfont( const char  *__name );
void       _WINBGI_ initgraph(int* device, int* mode, const char* p);



/*
#ifdef __cplusplus
}
#endif
*/

/*-----------------------------------------*/
//FONTS
extern int F_DEFAULT; //0
extern int F_LITT   ; //1
extern int F_LITT_S ; //2
extern int F_LITT_B ; //3

#define NULLFONT 0+4
#define COURE12 1+4
#define COURE18 2+4
#define COURE22 3+4
#define COURE28 4+4
#define TIMES12 5+4
#define TIMES14 6+4
#define TIMES18 7+4
#define TIMES20 8+4
#define TIMES20b 9+4
#define TIMES22 10+4
#define TIMES28 11+4
#define ARIAL12 12+4
#define ARIAL18 13+4
#define ARIAL22 14+4
#define ARIAL28 15+4
#define TIMES30b 16+4
#define TIMES28b 17+4
#define COURE28b 18+4
#define ARIAL12b 19+4
#define COURE12b 20+4
#define COURE16  21+4
#define ARIAL10b 22+4
#define WINDI10b 23+4

#define WIND210b 24+4
#define WIND310b 25+4
#define WEBDI10b 26+4
#define TERMI10b 27+4



void   PolyColor(int iBrushColor, const TPoint *Points, const int * iColors, const int Points_Count, int PenW = 1);
int    Draw_Ramka(int left, int top, int right, int bottom, UINT edge = 4, UINT grfFlags = 15);


//!!!!inline  void  outtextxy(int x, int y, char* str) { OutTextXY(x, y, str); }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RECT&  ClearBgiCoverRect(void);
RECT&  GetBgiCoverRect(void);
//extern  void *  SetWinBgiDC(void * pdc);
//extern /**/ void * _GetFont( int i );
//extern /**/ void _SetFont( int i,void * F );
extern QColor  BgiColor(unsigned int c);
extern  void  SwapDACColor();
int      Get_DAC(void);
extern bool  UseNativeFontSize;
extern bool  NoGmPen;


//TCanvas* __fastcall DC( void );
//TFont*    Font( int );
//TColor    Color( int8 );



QPainter *getAntLibPainter();
QPainter *setAntLibPainter(QPainter *p);



//void     DrawTextWithPr( int cx,int cy,int cw,int ch,char* str,int priz );
//void     DrawTextWithPr( TRect R,char* str,int priz );



//VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD
extern int  UseBGIPalette; // by default=1
//----------------------------------------------------------------------------
class  QPainterDC
{
    QPainter * pOldQPainter;
public:
    QPainterDC(QPainter* pdc){pOldQPainter=setAntLibPainter(pdc);}
    ~QPainterDC(void){setAntLibPainter(pOldQPainter);}
    static void SwapDACColor();
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

//VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD VLAD


void SetGradientFactor(float AGradientFactor);

bool drawemf(CONST RECT *lpRect,
             const char * szimagename,
             int animstep = 0
            );


