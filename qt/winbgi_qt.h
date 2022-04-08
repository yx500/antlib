#pragma once

// #include "aheaders_h.h"
#include "bgi.h"

#include <QPainter>

QPainter* getAntLibPainter();
QPainter* setAntLibPainter(QPainter* p);
QPainter* BgiCanvas(void);
QColor BgiColor(unsigned int c);

class QPainterDC
{
  QPainter* pOldQPainter;

public:
  QPainterDC(QPainter* pdc) { pOldQPainter = setAntLibPainter(pdc); }
  ~QPainterDC(void) { setAntLibPainter(pOldQPainter); }
  static void SwapDACColor();
};
