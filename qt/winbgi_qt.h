#pragma once
#include "aheaders_h.h"

#include "bgi.h"
#include <QPainter>


struct TPoint : public POINT
{
    TPoint() {}
    TPoint(int _x, int _y) {
        x=_x;
        y=_y;
    }

    TPoint(POINT& pt){
        x = pt.x;
        y = pt.y;
    }
};




QPainter *getAntLibPainter();
QPainter *setAntLibPainter(QPainter *p);


class  QPainterDC
{
    QPainter * pOldQPainter;
public:
    QPainterDC(QPainter* pdc){pOldQPainter=setAntLibPainter(pdc);}
    ~QPainterDC(void){setAntLibPainter(pOldQPainter);}
    static void SwapDACColor();
};

QColor      BgiColor(unsigned int c);
QPainter*   BgiCanvas(void);



