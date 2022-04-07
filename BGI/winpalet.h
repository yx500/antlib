#ifndef WINPALET_H
#define WINPALET_H
#include "aheaders_h.h"

#ifdef QT_ANTLIB
#include <QColor>
#endif

typedef struct tagDAC_PALETTEENTRY
{
  uint8 peRed;
  uint8 peGreen;
  uint8 peBlue;
  uint8 peFlags;
} DAC_PALETTEENTRY;

struct TDAC
{
  DAC_PALETTEENTRY pe[2];
  bool idx;
  int dt;
  unsigned long Clr[2];
};

extern TDAC DAC[32];
extern char DACCfgFileName[256];

int Get_DAC(void);
void Update_DAC(void);
bool IsClrMig(int Clr);
void SwapDACColor();

#ifndef QT_ANTLIB
unsigned long BgiDacColor(unsigned int c);
#else
QColor BgiDacColor(unsigned int c);
#endif
int GetGradientColor(int Color, float factor);

#endif
