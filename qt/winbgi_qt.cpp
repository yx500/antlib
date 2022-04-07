#include "winbgi_qt.h"

#include "aheaders_cpp.h"

static QPainter* Painter = nullptr;

QPainter* BgiCanvas(void) { return Painter; }

QPainter* getAntLibPainter() { return Painter; }
QPainter* setAntLibPainter(QPainter* p)
{
  auto oldPainter = Painter;
  Painter = p;
  return oldPainter;
  QFont f;
}
const int FontCount = 32;
QFont Fonts[FontCount];
void initFonts()
{
  for (int i = 0; i < FontCount; i++)
    Fonts[i] = QFont("Arial", 14, QFont::Normal);
  Fonts[F_DEFAULT] = QFont("Arial", 14, QFont::Normal);
  Fonts[F_LITT] = QFont("Arial", 12, QFont::Normal);
  Fonts[F_LITT_S] = QFont("Arial", 14, QFont::Normal);
  Fonts[F_LITT_B] = QFont("Arial", 16, QFont::Normal);
  Fonts[NULLFONT] = QFont("Arial", 90, QFont::Normal);
  Fonts[COURE12] = QFont("Courier New", 12, QFont::Normal);
  Fonts[COURE18] = QFont("Courier New", 18, QFont::Normal);
  Fonts[COURE22] = QFont("Courier New", 22, QFont::Normal);
  Fonts[COURE28] = QFont("Courier New", 28, QFont::Normal);
  Fonts[TIMES12] = QFont("Times New Roman", 12, QFont::Normal);
  Fonts[TIMES14] = QFont("Times New Roman", 14, QFont::Normal);
  Fonts[TIMES18] = QFont("Times New Roman", 18, QFont::Normal);
  Fonts[TIMES20] = QFont("Times New Roman", 20, QFont::Normal);
  Fonts[TIMES20b] = QFont("Times New Roman", 20, QFont::Bold);
  Fonts[TIMES22] = QFont("Times New Roman", 22, QFont::Normal);
  Fonts[TIMES28] = QFont("Times New Roman", 28, QFont::Normal);
  Fonts[ARIAL12] = QFont("Arial", 12, QFont::Normal);
  Fonts[ARIAL18] = QFont("Arial", 18, QFont::Normal);
  Fonts[ARIAL22] = QFont("Arial", 22, QFont::Normal);
  Fonts[ARIAL28] = QFont("Arial", 28, QFont::Normal);
  Fonts[TIMES30b] = QFont("Times New Roman", 30, QFont::Bold);
  Fonts[TIMES28b] = QFont("Times New Roman", 28, QFont::Bold);
  Fonts[COURE28b] = QFont("Courier New", 28, QFont::Bold);
  Fonts[ARIAL12b] = QFont("Arial", 12, QFont::Bold);
  Fonts[COURE12b] = QFont("Courier New", 12, QFont::Bold);
  Fonts[COURE16] = QFont("Courier New", 16, QFont::Normal);
  Fonts[ARIAL10b] = QFont("Arial", 10, QFont::Bold);
  Fonts[WINDI10b] = QFont("Wingdings", 10, QFont::Bold);
  Fonts[WIND210b] = QFont("Wingdings 2", 10, QFont::Bold);
  Fonts[WIND310b] = QFont("Wingdings 3", 10, QFont::Bold);
  Fonts[WEBDI10b] = QFont("Webdings", 10, QFont::Bold);
  Fonts[TERMI10b] = QFont("Terminal", 10, QFont::Bold);
}

class initbgi
{
public:
  initbgi() { initFonts(); }
};
static initbgi _initbgi;

QRect traceRect;
TRect ClearBgiCoverRect(void)
{
  RECT traceRECT = GetBgiCoverRect();
  traceRect = QRect();
  return traceRECT;
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

static int bgi_tracking = 0;
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
