#include "winbgi_qt.h"

#include "aheaders_cpp.h"
#include "col.h"

static QPainter* Painter = nullptr;
static textsettingstype text_settings;
static linesettingstype line_settings;
static fillsettingstype fill_settings;
const int FontCount = 32;
static QFont Fonts[FontCount];
static QFont font;
static QBrush brush;
static QPen pen;
static QRect traceRect;
static int bgi_tracking = 0;

QPainter* BgiCanvas(void) { return Painter; }

QPainter* getAntLibPainter() { return BgiCanvas(); }

QPainter* setAntLibPainter(QPainter* p)
{
    auto oldPainter = Painter;
    Painter = p;
    return oldPainter;
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
}

void initFonts()
{
    for (int i = 0; i < FontCount; i++){ 
        Fonts[i] = QFont("Arial", 14, QFont::Normal);               
        Fonts[i].setPixelSize(14);
    }
    Fonts[F_LITT] = QFont("Arial", 12, QFont::Normal);              Fonts[F_LITT].setPixelSize(12);
    Fonts[F_DEFAULT] = QFont("Arial", 14, QFont::Normal);           Fonts[F_DEFAULT].setPixelSize(14);
    Fonts[F_LITT_S] = QFont("Arial", 14, QFont::Normal);            Fonts[F_LITT_S].setPixelSize(14);
    Fonts[F_LITT_B] = QFont("Arial", 16, QFont::Normal);            Fonts[F_LITT_B].setPixelSize(16);
    Fonts[NULLFONT] = QFont("Arial", 90, QFont::Normal);            Fonts[NULLFONT].setPixelSize(90);
    Fonts[COURE12] = QFont("Courier New", 12, QFont::Normal);       Fonts[COURE12].setPixelSize(12);
    Fonts[COURE18] = QFont("Courier New", 18, QFont::Normal);       Fonts[COURE18].setPixelSize(18);
    Fonts[COURE22] = QFont("Courier New", 22, QFont::Normal);       Fonts[COURE22].setPixelSize(22);
    Fonts[COURE28] = QFont("Courier New", 28, QFont::Normal);       Fonts[COURE28].setPixelSize(28);
    Fonts[TIMES12] = QFont("Times New Roman", 12, QFont::Normal);   Fonts[TIMES12].setPixelSize(12);
    Fonts[TIMES14] = QFont("Times New Roman", 14, QFont::Normal);   Fonts[TIMES14].setPixelSize(14);
    Fonts[TIMES18] = QFont("Times New Roman", 18, QFont::Normal);   Fonts[TIMES18].setPixelSize(18);
    Fonts[TIMES20] = QFont("Times New Roman", 20, QFont::Normal);   Fonts[TIMES20].setPixelSize(20);
    Fonts[TIMES20b] = QFont("Times New Roman", 20, QFont::Bold);    Fonts[TIMES20b].setPixelSize(20);
    Fonts[TIMES22] = QFont("Times New Roman", 22, QFont::Normal);   Fonts[TIMES22].setPixelSize(22);
    Fonts[TIMES28] = QFont("Times New Roman", 28, QFont::Normal);   Fonts[TIMES28].setPixelSize(28);
    Fonts[ARIAL12] = QFont("Arial", 12, QFont::Normal);             Fonts[ARIAL12].setPixelSize(12);
    Fonts[ARIAL18] = QFont("Arial", 18, QFont::Normal);             Fonts[ARIAL18].setPixelSize(18);
    Fonts[ARIAL22] = QFont("Arial", 22, QFont::Normal);             Fonts[ARIAL22].setPixelSize(22);
    Fonts[ARIAL28] = QFont("Arial", 28, QFont::Normal);             Fonts[ARIAL28].setPixelSize(28);
    Fonts[TIMES30b] = QFont("Times New Roman", 30, QFont::Bold);    Fonts[TIMES30b].setPixelSize(30);
    Fonts[TIMES28b] = QFont("Times New Roman", 28, QFont::Bold);    Fonts[TIMES28b].setPixelSize(28);
    Fonts[COURE28b] = QFont("Courier New", 28, QFont::Bold);        Fonts[COURE28b].setPixelSize(28);
    Fonts[ARIAL12b] = QFont("Arial", 12, QFont::Bold);              Fonts[ARIAL12b].setPixelSize(12);
    Fonts[COURE12b] = QFont("Courier New", 12, QFont::Bold);        Fonts[COURE12b].setPixelSize(12);
    Fonts[COURE16] = QFont("Courier New", 16, QFont::Normal);       Fonts[COURE16].setPixelSize(16);
    Fonts[ARIAL10b] = QFont("Arial", 10, QFont::Bold);              Fonts[ARIAL10b].setPixelSize(10);
    Fonts[WINDI10b] = QFont("Wingdings", 10, QFont::Bold);          Fonts[WINDI10b].setPixelSize(10);
    Fonts[WIND210b] = QFont("Wingdings 2", 10, QFont::Bold);        Fonts[WIND210b].setPixelSize(10);
    Fonts[WIND310b] = QFont("Wingdings 3", 10, QFont::Bold);        Fonts[WIND310b].setPixelSize(10);
    Fonts[WEBDI10b] = QFont("Webdings", 10, QFont::Bold);           Fonts[WEBDI10b].setPixelSize(10);
    Fonts[TERMI10b] = QFont("Terminal", 10, QFont::Bold);           Fonts[TERMI10b].setPixelSize(10);
}

TRect ClearBgiCoverRect(void)
{
    RECT _traceRECT = GetBgiCoverRect();
    traceRect = QRect();
    return _traceRECT;
}

TRect GetBgiCoverRect(void)
{
    TRect traceRECT;
    traceRECT.left = traceRect.left();
    traceRECT.right = traceRect.right();
    traceRECT.top = traceRect.top();
    traceRECT.bottom = traceRect.bottom();
    return traceRECT;
}

void start_bgi_tracking()
{
    if (bgi_tracking == 0)
        ClearBgiCoverRect();
    bgi_tracking++;
}

QRect stop_bgi_tracking()
{
    bgi_tracking--;
    return traceRect;
}

void tracking_add_rect(QRect r)
{
    r = r.normalized();
    if (r.width() == 0)
        r.adjust(-1, 0, 1, 0);
    if (r.height() == 0)
        r.adjust(0, 1, 0, 1);
    traceRect = traceRect.united(r);
}
void tracecoord(int x, int y){
    QRect r1(x,y,1,1);
    traceRect = traceRect.united(r1);
}

// =============   SETTING  ==========

QColor BgiColor(unsigned int c){
    return BgiDacColor(c);
}

void setcolor(int __color)
{
    pen.setColor(BgiColor(__color));
    if ((Painter) &&(!bgi_tracking))
        Painter->setPen(pen);
}
void setfillstyle(int __pattern, int __color)
{
    fill_settings.color = __color;
    fill_settings.pattern = __pattern;
    brush.setColor(BgiColor(__color));
    switch (__pattern) {
    case EMPTY_FILL:
        brush.setStyle(Qt::NoBrush);
        break;
    case SOLID_FILL:
        brush.setStyle(Qt::SolidPattern);
        break;
    case LINE_FILL:
        brush.setStyle(Qt::HorPattern);
        break;
    case LTSLASH_FILL:
        brush.setStyle(Qt::HorPattern);
        break;
    case SLASH_FILL:
        brush.setStyle(Qt::BDiagPattern);
        break;
    case BKSLASH_FILL:
        brush.setStyle(Qt::FDiagPattern);
        break;
    case LTBKSLASH_FILL:
    case HATCH_FILL:
    case XHATCH_FILL:
    case INTERLEAVE_FILL:
        brush.setStyle(Qt::DiagCrossPattern);
        break;
    case WIDE_DOT_FILL:
    case CLOSE_DOT_FILL:
    case USER_FILL:
        brush.setStyle(Qt::DiagCrossPattern);
        break;
    default:
        brush.setStyle(Qt::NoBrush);
    }
    if ((Painter)&&(!bgi_tracking))
        Painter->setBrush(brush);
}

void setlinestyle(int __linestyle, unsigned __upattern, int __thickness)
{
    line_settings.linestyle = __linestyle;
    line_settings.upattern = __upattern;
    line_settings.thickness = __thickness;
    switch (line_settings.linestyle) {
    default:
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(line_settings.thickness);
        break;
    case 1:
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        break;
    case 2:
        pen.setStyle(Qt::DotLine);
        pen.setWidth(1);
        break;
    case 3:
        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(1);
        break;
    case 4:
        pen.setStyle(Qt::DashDotDotLine);
        pen.setWidth(1);
        break;
    }
    if (Painter)
        Painter->setPen(pen);
}

void settextjustify(int __horiz, int __vert)
{
    text_settings.horiz = __horiz;
    text_settings.vert = __vert;
}

static void select_font()
{
    if (text_settings.font < 0 || text_settings.font >= FontCount) {
        text_settings.font = 0;
        //        std::cerr << "Default font." << std::endl;
    }

    if (Painter){
        font = Fonts[text_settings.font];
        if (text_settings.charsize != 1){
            if (text_settings.charsize<0)
                font.setPixelSize(-text_settings.charsize);else
                font.setPixelSize(text_settings.charsize);
        }
        Painter->setFont(font);
    }
}

void settextstyle(int __font, int __direction, int __charsize)
{
    text_settings.font = (__font < FontCount) ? __font : 0;
    text_settings.direction = __direction;
    text_settings.charsize = __charsize;
    select_font();
}

void _SetText(unsigned int __font, int d1, int d2)
{
    text_settings.font = (__font < FontCount) ? __font : 0;
    text_settings.charsize = Fonts[__font].pixelSize();
    select_font();
    settextjustify(d1, d2);
}

void _SetTextSize(int charsize)
{
    text_settings.charsize = charsize;
    select_font();
}

int textheight(const String & __textstring)
{
    QFontMetrics fm(font);
    return fm.height();
}

int textwidth(const String &__textstring)
{
    QFontMetrics fm(font);
    return fm.horizontalAdvance(__textstring);
//    return fm.width(__textstring);
}

// =============   DRAW  ==========

void bar(int __left, int __top, int __right, int __bottom)
{
    QRect r(QPoint(__left, __top),QPoint(__right-1 , __bottom-1));
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter){
        auto old_pen_color=pen.color();
        pen.setColor(brush.color());
        Painter->setPen(pen);
        Painter->drawRect(r);
        pen.setColor(old_pen_color);
        Painter->setPen(pen);
    }
}

void circle(int __x, int __y, int __radius)
{
    QRect r(__x - __radius, __y - __radius,  __radius*2,  __radius*2);
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawArc(r, 0, 360 * 16);
}

void pie(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4)
{
    QRect r(QPoint(X1, Y1), QPoint(X2, Y2));
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter) {
        if (Y3 > Y4)
            Painter->drawPie(r, 0 * 16, 180 * 16);
        else
            Painter->drawPie(r, 180 * 16, 360 * 16);
    }
}

void drawpoly(int __numpoints, const int* __polypoints)
{
    QPolygon p;
    TPoint* P = (TPoint*)__polypoints;
    for (int i = 0; i < __numpoints; i++) {
        p.push_back(QPoint(P[i].x, P[i].y));
    }
    if (bgi_tracking) {
        QRect r = p.boundingRect();
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawPolyline(p);
}

void fillellipse(int __x, int __y, int __xradius, int __yradius)
{
    QRect r( __x - __xradius, __y - __yradius, __xradius*2, __yradius*2);
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawEllipse(r);
}

void fillpoly(int __numpoints, const int* __polypoints)
{
    QPolygon p;
    TPoint* P = (TPoint*)__polypoints;
    for (int i = 0; i < __numpoints; i++) {
        p.push_back(QPoint(P[i].x, P[i].y));
    }

    if (bgi_tracking) {
        QRect r = p.boundingRect();
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawPolygon(p);
}

void line(int __x1, int __y1, int __x2, int __y2)
{

    if (bgi_tracking) {
        QRect r(QPoint(__x1, __y1),QPoint(__x2, __y2));
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawLine(__x1, __y1, __x2, __y2);
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
        tracking_add_rect(p.boundingRect());
        return;
    }
    if (Painter)
        Painter->drawPolyline(p);
}

void roundrect(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight)
{
    QRect r(QPoint(nLeftRect, nTopRect), QPoint(nRightRect, nBottomRect));
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter)
        Painter->drawRoundedRect(r, nWidth, nHeight);
}

void OutTextXY(int x, int y, const String &str)
{
    if (str.Length()==0)
        return;
    int tw = textwidth(str);
    int th = textheight(str);
    QRect r(x , y, tw,   th);
    int dy = 0; // ptm->tmInternalLeading;
    int dx = 0;
    switch (text_settings.horiz) {
    case LEFT_TEXT:
        dx = 0;
        break;
    case CENTER_TEXT: {
        dx = -tw/2;//(0.5 + 1. * tw / 2);
    } break;
    case RIGHT_TEXT:
        dx = -tw;
        break;
    }
    switch (text_settings.vert) {
    case TOP_TEXT:
        dy =0;// -th;
        break;
    case BOTTOM_TEXT:
        dy = -th;
        break;
    case CENTER_TEXT: {
        dy = -th/2;//(0.5 + 1. * th / 2) /*-1*/;
    } break;
    }
    r.translate(dx,dy);
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    if (Painter){
        int uF = Qt::AlignLeft;
        Painter->drawText(r,uF, str);
        //        QRect r(x - dx, y - dy, tw,   th);
        //        Painter->drawRect(r);
    }
}

void DrawText(int x, int y, int tw, int th, const String &str)
{
    //    if (strlen(str) == 0)
    if (str.Length()==0)
        return;
    QRect r( x, y, tw, th);
    if (bgi_tracking) {
        tracking_add_rect(r);
        return;
    }
    int uF = 0;
    switch (text_settings.horiz) {
    case LEFT_TEXT:
        uF = uF | Qt::AlignLeft;
        break;
    case CENTER_TEXT:
        uF = uF | Qt::AlignHCenter;
        break;
    case RIGHT_TEXT:
        uF = uF | Qt::AlignRight;
        break;
    }
    switch (text_settings.vert) {
    case TOP_TEXT:
        uF = uF | Qt::AlignTop;
        break;
    case BOTTOM_TEXT:
        uF = uF | Qt::AlignBottom;
        break;
    case CENTER_TEXT:
        uF = uF | Qt::AlignVCenter;
        break;
    }

    if (Painter)
        Painter->drawText(r, uF, str);
}

void PolyColor(int iBrushColor, const TPoint* Points, const int* iColors, const int Points_Count, int PenW )
{

    QPolygon p;
    TPoint* P = (TPoint*)Points;
    for (int i = 0; i < Points_Count; i++) {
        p.push_back(QPoint(P[i].x, P[i].y));
    }

    if (bgi_tracking) {
        QRect r = p.boundingRect();
        tracking_add_rect(r);
        return;
    }


    QColor BrushColor = BgiColor(iBrushColor);
    pen.setColor(BrushColor);
    brush.setColor(BrushColor);

    //      if ((fill_settings.pattern != SOLID_FILL) && (fill_settings.pattern != EMPTY_FILL)) {

    //          Cnv->Brush->Style = bsSolid;
    //        Cnv->Polygon(Points, Points_Count - 1);
    //        Cnv->Brush->Color = clBlack;
    //      }
    bool bNormPol = true;
    int iColors0 = iColors[0];

    for (int i = 1; i < Points_Count; i++)
        if (iColors0 != iColors[i]) {
            bNormPol = false;
            break;
        }

    setfillstyle(fill_settings.pattern,iBrushColor);
    pen.setWidth(PenW);
    if (Painter){
        Painter->setPen(pen);
        Painter->setBrush(brush);
        if (bNormPol) {
            setlinestyle(SOLID_LINE,0,PenW);
            setcolor(iColors0);
            Painter->drawPolygon(p);

        } else {

            Painter->drawPolygon(p);
            pen.setColor(BrushColor);Painter->setPen(pen);
            Painter->drawPolyline(p);
            pen.setStyle(Qt::SolidLine);Painter->setPen(pen);

            for (int i = 1; i < Points_Count; i++) {

                if ((iBrushColor == iColors[i - 1]) && (iBrushColor != FON))
                    continue;
                pen.setColor(BgiColor(iColors[i - 1]));Painter->setPen(pen);
                Painter->drawLine(Points[i - 1].x, Points[i - 1].y,Points[i].x, Points[i].y);
                //                Cnv->Pixels[Points[i].x][Points[i].y] = Cnv->Pen->Color;
            }
            if ((iBrushColor != iColors[Points_Count - 1]) || ((iBrushColor == FON) && (iColors[Points_Count - 1] == FON))) {
                pen.setColor(BgiColor(iColors[Points_Count - 1]));Painter->setPen(pen);
                Painter->drawLine(Points[Points_Count - 1].x, Points[Points_Count - 1].y,Points[0].x, Points[0].y);
                //                Cnv->Pixels[Points[0].x][Points[0].y] = Cnv->Pen->Color;
            }
        }
    }
}


int Draw_Ramka(int left, int top, int right, int bottom, int edge , int grfFlags )
{
    rectangle(left,  top,  right,  bottom);
    return 0;
}

bool drawemf(const RECT* lpRect, const char* szimagename, int animstep )
{
    rectangle(lpRect->left,  lpRect->top,  lpRect->right,  lpRect->bottom);
    return true;
}



class initbgi
{
public:
    initbgi() {
        initFonts();
        Get_DAC();
    }
};
static initbgi _initbgi;
