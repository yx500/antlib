
#include "aheaders_cpp.h"
#include "APch.h"

#include "Scrin.h"

extern int  MaxX, MaxY, CurrentPicture;
#define LT  0
void Super_Text2(int x1, int y1,
                 int c1, int c2,
                 char *txt)
{
    setcolor(c1);
    OutTextXY(x1 + 1, y1 + 1, txt);
    setcolor(c2);
    OutTextXY(x1, y1, txt);
}

void Super_Text(int x1, int y1,
                int c1, int c2,
                char *txt)
{
    setcolor(c2);
    OutTextXY(x1, y1, txt);
    setcolor(c1);
    OutTextXY(x1 + 1, y1 + 1, txt);
}

void Box(int x1, int y1, int x2, int y2)
{
    line(x1, y1, x2, y1);
    line(x1, y1, x1, y2);
    line(x2, y1, x2, y2);
    line(x1, y2, x2, y2);
}

void Super_Box_(int x1, int y1,
                int x2, int y2,
                int h,
                int c1, int c2, int c3, int c4,
                int cf)
{
    int t[10], b[10], l[10], r[10];
    setcolor(C_D);
    setfillstyle(1, cf);
    barx(x1 - 1, y1 - 1, x2 + 1, y2/*-1*/ + 1);

    t[0] = x1;                   t[1]        = y1;
    t[2] = x2;                   t[3]        = y1;
    t[4] = x2 - h;                 t[5]        = y1 + h;
    t[6] = x1 + h;                 t[7]        = y1 + h;
    t[8] = x1;                   t[9]        = y1;

    l[0] = x1;                   l[1]        = y1;
    l[2] = x1 + h;                 l[3]        = y1 + h;
    l[4] = x1 + h;                 l[5]        = y2 - h;
    l[6] = x1;                   l[7]        = y2;
    l[8] = x1;                   l[9]        = y1;

    b[0] = x1 + h;                 b[1]        = y2 - h;
    b[2] = x2 - h;                 b[3]        = y2 - h;
    b[4] = x2;                   b[5]        = y2;
    b[6] = x1;                   b[7]        = y2;
    b[8] = x1 + h;                 b[9] = y2 - h;

    r[0] = x2;                   r[1]        = y1;
    r[2] = x2;                   r[3]        = y2;
    r[4] = x2 - h;                 r[5]        = y2 - h;
    r[6] = x2 - h;                 r[7]        = y1 + h;
    r[8] = x2;                   r[9]        = y1;
    setcolor(c1);
    setfillstyle(1, c1);
    fillpoly(5, t);

    setcolor(c2);
    setfillstyle(1, c2);
    fillpoly(5, r);

    setcolor(c3);
    setfillstyle(1, c3);
    fillpoly(5, b);

    setcolor(c4);
    setfillstyle(1, c4);
    fillpoly(5, l);
    setcolor(LIN);

}


void Mini_Box(int x1, int y1, int x2, int y2, int c1, int c2, int cf)
{
    setcolor(c1);
    setfillstyle(1, cf);
    barx(x1, y1, x2, y2);
    setcolor(c2);
    rectangle(x1 + 1, y1 + 1, x2 + 1, y2 + 1);
}

void Super_Box(int x1, int y1, int x2, int y2, int h, int c1, int c2, int c3, int c4);

// #include"..\BMP\bmplib.h"
// tBMP Aaa;

void S_B(int rg)
{
    int sdv = 70;
//  int sdv=100;

    setcolor(TXT);

    if (rg) {
        char pattern[8] = {0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
//      char pattern[8] = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        setfillpattern(pattern, 1);
        //  setfillstyle(2,FON);
    } else
        setfillstyle(1, FON);
    /*
    char pattern[8] = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    setfillpattern(pattern, getmaxcolor());
      */
//
//
//
//     printf("MaxX = %d",MaxX);
//
//
//
//
//

    barx(0, 0, MaxX, MaxY);
//   Aaa.LoadBmp("fop.bmp");
//   Mini_Box(1,1,MaxX,122,C_D,LIN,FON );
//   Aaa.FonBmp(2,2,MaxX,120);
//   setcolor(LIN);
//   rectangle(1,1,MaxX-1,130);
//   setcolor(C_D);
//   rectangle(1+1,1+1,MaxX,130+1);
//   Aaa.FonBmp(1,MaxY-210,MaxX,MaxY-100);
//   setcolor(LIN);
//  rectangle(1,MaxY-210,MaxX-1,MaxY-80);
//   setcolor(C_D);
//   rectangle(1+1,MaxY-210+1,MaxX,MaxY-80+1);
    if (CurrentPicture == LT) {
        Super_Box(5, MaxY - sdv + 3, MaxX - 6, MaxY - 6, 0, LIN, LIN, C_D, C_D);
    }

}

void Super_Box(int x1, int y1, int x2, int y2, int h, int c1, int c2, int c3, int c4)
{
    int t[10], b[10], l[10], r[10];
    setcolor(LIN);
    setfillstyle(1, FON);
    bar(x1, y1, x2, y2 - 1);
    setfillstyle(1, LIN);

    t[0] = x1;                   t[1]        = y1;
    t[2] = x2;                   t[3]        = y1;
    t[4] = x2 - h;                 t[5]        = y1 + h;
    t[6] = x1 + h;                 t[7]        = y1 + h;
    t[8] = x1;                   t[9]        = y1;

    l[0] = x1;                   l[1]        = y1;
    l[2] = x1 + h;                 l[3]        = y1 + h;
    l[4] = x1 + h;                 l[5]        = y2 - h;
    l[6] = x1;                   l[7]        = y2;
    l[8] = x1;                   l[9]        = y1;

    b[0] = x1 + h;                 b[1]        = y2 - h;
    b[2] = x2 - h;                 b[3]        = y2 - h;
    b[4] = x2;                   b[5]        = y2;
    b[6] = x1;                   b[7]        = y2;
    b[8] = x1 + h;                 b[9] = y2 - h;

    r[0] = x2;                   r[1]        = y1;
    r[2] = x2;                   r[3]        = y2;
    r[4] = x2 - h;                 r[5]        = y2 - h;
    r[6] = x2 - h;                 r[7]        = y1 + h;
    r[8] = x2;                   r[9]        = y1;
    setcolor(c1);
    setfillstyle(1, c1);
    fillpoly(5, t);

    setcolor(c2);
    setfillstyle(1, c2);
    fillpoly(5, r);

    setcolor(c3);
    setfillstyle(1, c3);
    fillpoly(5, b);

    setcolor(c4);
    setfillstyle(1, c4);
    fillpoly(5, l);
    setcolor(LIN);
}

void barx(int x1, int y1, int x2, int y2)
{
    bar(x1, y1, x2, y2);
    rectangle(x1, y1, x2, y2);

}


