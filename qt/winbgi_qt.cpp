#include "aheaders_cpp.h"

#include "winbgi_qt.h"

static QPainter *Painter=nullptr;

QPainter*   BgiCanvas(void){return Painter;}

QPainter *getAntLibPainter(){return Painter;}
QPainter *setAntLibPainter(QPainter *p){
    auto oldPainter=Painter;
    Painter=p;
    return oldPainter;
    QFont f;
}
const int FontCount = 32;
QFont Fonts[FontCount];
void initFonts(){
    for (int i=0;i<FontCount;i++) Fonts[i]=QFont("Arial",14,QFont::Normal);
    Fonts[F_DEFAULT ]=  QFont("Arial",14,QFont::Normal);
    Fonts[F_LITT ]=     QFont("Arial",12,QFont::Normal);
    Fonts[F_LITT_S ]=   QFont("Arial",14,QFont::Normal);
    Fonts[F_LITT_B ]=   QFont("Arial",16,QFont::Normal);
    Fonts[NULLFONT]=   QFont("Arial",90,QFont::Normal);
    Fonts[COURE12 ]=   QFont("Courier New",12,QFont::Normal);
    Fonts[COURE18 ]=   QFont("Courier New",18,QFont::Normal);
    Fonts[COURE22 ]=   QFont("Courier New",22,QFont::Normal);
    Fonts[COURE28 ]=   QFont("Courier New",28,QFont::Normal);
    Fonts[TIMES12 ]=   QFont("Times New Roman",12,QFont::Normal);
    Fonts[TIMES14 ]=   QFont("Times New Roman",14,QFont::Normal);
    Fonts[TIMES18 ]=   QFont("Times New Roman",18,QFont::Normal);
    Fonts[TIMES20 ]=   QFont("Times New Roman",20,QFont::Normal);
    Fonts[TIMES20b]=   QFont("Times New Roman",20,QFont::Bold);
    Fonts[TIMES22 ]=   QFont("Times New Roman",22,QFont::Normal);
    Fonts[TIMES28 ]=   QFont("Times New Roman",28,QFont::Normal);
    Fonts[ARIAL12 ]=   QFont("Arial",12,QFont::Normal);
    Fonts[ARIAL18 ]=   QFont("Arial",18,QFont::Normal);
    Fonts[ARIAL22 ]=   QFont("Arial",22,QFont::Normal);
    Fonts[ARIAL28 ]=   QFont("Arial",28,QFont::Normal);
    Fonts[TIMES30b]=   QFont("Times New Roman",30,QFont::Bold);
    Fonts[TIMES28b]=   QFont("Times New Roman",28,QFont::Bold);
    Fonts[COURE28b]=   QFont("Courier New",28,QFont::Bold);
    Fonts[ARIAL12b]=   QFont("Arial",12,QFont::Bold);
    Fonts[COURE12b]=   QFont("Courier New",12,QFont::Bold);
    Fonts[COURE16 ]=   QFont("Courier New",16,QFont::Normal);
    Fonts[ARIAL10b]=   QFont("Arial",10,QFont::Bold);
    Fonts[WINDI10b]=   QFont("Wingdings",10,QFont::Bold);
    Fonts[WIND210b]=   QFont("Wingdings 2",10,QFont::Bold);
    Fonts[WIND310b]=   QFont("Wingdings 3",10,QFont::Bold);
    Fonts[WEBDI10b]=   QFont("Webdings",10,QFont::Bold);
    Fonts[TERMI10b]=   QFont("Terminal",10,QFont::Bold);
}

class initbgi{
public:
    initbgi(){initFonts();}
};
static initbgi _initbgi;

QRect traceRect;
TRect ClearBgiCoverRect(void)
{
    RECT traceRECT=GetBgiCoverRect();
    traceRect=QRect();
    return traceRECT;
}
TRect GetBgiCoverRect(void)
{
    TRect traceRECT;
    traceRECT.left=traceRect.left();
    traceRECT.right=traceRect.right();
    traceRECT.top=traceRect.top();
    traceRECT.bottom=traceRect.bottom();
    return traceRECT;
}

static int bgi_tracking=0;
void start_bgi_tracking(){
    if (bgi_tracking==0) ClearBgiCoverRect();
    bgi_tracking++;
}
QRect stop_bgi_tracking(){
    bgi_tracking--;
    return traceRect;

}

void tracking_add_rect(QRect r){
    r=r.normalized();
    if (r.width()==0) r.adjust(-1,0,1,0);
    if (r.height()==0) r.adjust(0,1,0,1);
    traceRect=traceRect.united(r);
}

// =============   DRAW  ==========

void  bar(int __left, int __top, int __right, int __bottom){
    QRect r(__left,__top,__right-__left,__bottom-__top);
    if (bgi_tracking) {
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawRect(r);
}
void  circle(int __x, int __y, int __radius){
    QRect r(__x-__radius,__y-__radius,__x+__radius,__y+__radius);
    if (bgi_tracking) {
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawArc(r,0,360*16);
}
void  pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4){
    QRect r(X1,Y1,X2,Y2);
    if (bgi_tracking) {
        tracking_add_rect(r); return;
    }
    if (Painter) {
        // Хер знат как пересчитать борланд отсечку в градусы
        // рисую полукружия , надо проверять
        if (Y3>Y4)
        Painter->drawPie(r,0*16,180*16); else
        Painter->drawPie(r,180*16,360*16);
    }
}
void  drawpoly(int __numpoints, const int *__polypoints)
{
    QPolygon p;
    TPoint* P=(TPoint*)__polypoints;
    for (int i=0;i<__numpoints;i++) {
        p.push_back(QPoint(P[i].x,P[i].y));
    }
    if (bgi_tracking) {
        QRect r=p.boundingRect();
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawPolyline(p);
}

void  fillellipse(int __x, int __y, int __xradius, int __yradius)
{
    QRect r(__x-__xradius,__y-__yradius,__x+__xradius,__y+__yradius);
    if (bgi_tracking) {
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawEllipse(r);
}
void  fillpoly(int __numpoints, const int  *__polypoints){
    QPolygon p;
    TPoint* P=(TPoint*)__polypoints;
    for (int i=0;i<__numpoints;i++) {
        p.push_back(QPoint(P[i].x,P[i].y));
    }

    if (bgi_tracking) {
        QRect r=p.boundingRect();
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawPolygon(p);
}

void line(int __x1, int __y1, int __x2, int __y2)
{

    if (bgi_tracking) {
        QRect r(__x1,__y1,__x2,__y2);
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawLine(__x1,__y1,__x2,__y2);
}
void rectangle(int left, int top, int right, int bottom)
{
    if (top > bottom)
        std::swap(top, bottom);
      if (left > right)
        std::swap(left, right);

      QPolygon p;
      p.push_back(QPoint(left, top));
      p.push_back(QPoint(right, top));
      p.push_back(QPoint(right, bottom));
      p.push_back(QPoint(left, bottom));
      p.push_back(QPoint(left, top));


    if (bgi_tracking) {
        tracking_add_rect(p.boundingRect()); return;
    }
    if (Painter) Painter->drawPolyline(p);
}
void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight)
{
    QRect r(nLeftRect,nTopRect,nRightRect,nBottomRect);
    if (bgi_tracking) {
        tracking_add_rect(r); return;
    }
    if (Painter) Painter->drawRoundedRect(r,nWidth,nHeight);
}






