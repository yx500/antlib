#include <vcl.h>
#pragma hdrstop

#if (__BORLANDC__ >= 0x530)
#pragma package(smart_init)
#endif

#include "winbgi_gdp.h"
#include "winpalet.h"

#include <SyncObjs.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <systypes.h>
#include <windows.h>

extern TCanvas* dc;

TCanvas* BgiCanvas(void)
{
  return dc;
}

bool NoGmPen = false;

int Draw_Ramka(int left, int top, int right, int bottom, UINT edge, UINT grfFlags)
{
  tracecoord(left, top);
  tracecoord(right, top);
  tracecoord(right, bottom);
  tracecoord(left, bottom);
  if (dc == NULL)
    return 0;
  RECT qrc;
  qrc.left = left;
  qrc.top = top;
  qrc.right = right;
  qrc.bottom = bottom;
  return DrawEdge(dc->Handle, &qrc, edge, grfFlags);
}

static void __fastcall tracecoord(const POINT* Points, int PointsCount)
{
  for (int i = 0; i < PointsCount; i++)
    tracecoord(Points[i].x, Points[i].y);
}

void roundrect(int nLeftRect,   // x-coord. of bounding rectangle's upper-left corner
               int nTopRect,    // y-coord. of bounding rectangle's upper-left corner
               int nRightRect,  // x-coord. of bounding rectangle's lower-right corner
               int nBottomRect, // y-coord. of bounding rectangle's lower-right corner
               int nWidth,      // width of ellipse used to draw rounded corners
               int nHeight      // height of ellipse used to draw rounded corners
)
{
  if (nTopRect > nBottomRect)
    std::swap(nTopRect, nBottomRect);
  if (nLeftRect > nRightRect)
    std::swap(nLeftRect, nRightRect);

  POINT rect[5];
  rect[0].x = nLeftRect, rect[0].y = nTopRect;
  rect[1].x = nRightRect, rect[1].y = nTopRect;
  rect[2].x = nRightRect, rect[2].y = nBottomRect;
  rect[3].x = nLeftRect, rect[3].y = nBottomRect;
  rect[4].x = nLeftRect, rect[4].y = nTopRect;
  tracecoord(rect, 4);
  if (dc == NULL)
    return;

  // drawpoly( 5, ( int* ) &rect );

  dc->RoundRect(nLeftRect, nTopRect, nRightRect, nBottomRect, nWidth, nHeight);
  // Rectangle(dc,nLeftRect,nTopRect,nRightRect,nBottomRect);
}
