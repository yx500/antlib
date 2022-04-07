#include "winfonts.h"

#include "vgdp.h"
#include "winbgi_core.h"
#include "winbgi_gdp.h"

#include <Graphics.hpp>
#include <iostream>
//#include <fstream>
#include <algorithm>

#if (__BORLANDC__ >= 0x530)
#pragma package(smart_init)
#endif

using namespace std;

int F_DEFAULT = 0;
int F_LITT = 1;
int F_LITT_S = 2;
int F_LITT_B = 3;

bool UseNativeFontSize = true;
static TFont* Fonts[FontCount];

// static TEXTMETRIC font_tm[FontCount];
// static TEXTMETRIC* ptm=0;

static char FontFileNames[FontCount][8] = {
    "axx14__", //  00
    "axx12__", //  01
    "axx14__", //  02
    "axx16__", //  03
    "axx90__", //  04
    "cur12__", // 101   //  05
    "cur18__", // 102   //  06
    "cur22__", //  07
    "cur28__", //  08
    "tim12__", //  09
    "tim14__", //  10
    "tim18__", //  11
    "tim20__", //  12
    "tim20_b", //  13
    "tim22__", //  14
    "tim28__", //  15
    "ari12__", // 12    //  16
    "ari18__", // 13    //  17
    "ari22__", // 14    //  18
    "ari28__", // 15    //  19
    "tim30_b", // 16    //  20
    "tim28_b", // 17    //  21
    "cur28_b", // 18    //  22
    "ari12_b", // 17    //  23
    "cur12_b", // 18    //  24
    "cur16__", // 19    //  25
    "ari10_b", // 20    //  26
    "win10__", // 21    //  27
    "vW210__", // 22    //  28
    "sW310__", // 23    //  29
    "kWb10__", // 24    //  30
    "iTe10__"  // 25    //  31
};

void SetVCLFont(TFont* Font, int nn)
{
  Fonts[nn] = Font;
  Font->Name = "Arial";
  Font->Charset = RUSSIAN_CHARSET;
  Font->Pitch = TFontPitch() << fpFixed;
  Font->Height = 90;
  int sz = -atoi(&FontFileNames[nn][3]);
  if (sz)
    Font->Size = sz;
  if (FontFileNames[nn][6] == 'b')
    Font->Style = TFontStyles() << fsBold;

  switch (FontFileNames[nn][0]) {
  case 'a':
    Font->Name = "Arial";
    break;
  case 't':
    Font->Name = "Times New Roman";
    break;
  case 'c':
    Font->Name = "Courier New";
    break;
  case 'w':
    Font->Name = "Wingdings";
    Font->Charset = DEFAULT_CHARSET;
    break;
  case 'v':
    Font->Name = "Wingdings 2";
    Font->Charset = DEFAULT_CHARSET;
    break;
  case 's':
    Font->Name = "Wingdings 3";
    Font->Charset = DEFAULT_CHARSET;
    break;
  case 'k':
    Font->Name = "Webdings";
    Font->Charset = DEFAULT_CHARSET;
    break;
  case 'i':
    Font->Name = "Terminal";
    Font->Charset = DEFAULT_CHARSET;
    break;
  }
}

void CreateFonts()
{
  for (int i = 0; i < FontCount; i++) {
    SetVCLFont(new TFont(), i);
  }
}

void DestroyFonts()
{
  for (int i = 0; i < FontCount; i++) {
    if (Fonts[i]) {
      delete Fonts[i];
      Fonts[i] = 0;
    }
  }
}

extern textsettingstype text_settings;
extern TCanvas* dc;

void select_font()
{
  if (dc == NULL)
    return;

  if (text_settings.font < 0 || text_settings.font >= FontCount)
    text_settings.font = 0;
  dc->Font = Fonts[text_settings.font];
  if (text_settings.charsize != 1)
    dc->Font->Height = text_settings.charsize;
}

gdp::Font* _gdp_create_font()
{
  if (text_settings.font < 0 || text_settings.font >= FontCount) {
    text_settings.font = 0;
    cerr << "Default font." << endl;
  }
  int num_font = text_settings.font;
  char* fontattrib = FontFileNames[num_font];
  int font_size = atoi(&fontattrib[3]);
  bool is_bold = (fontattrib[6] == 'b');
  WCHAR* familyName = L"Arial";
  switch (fontattrib[0]) {
  case 'a':
    familyName = L"Arial";
    break;
  case 't':
    familyName = L"Times New Roman";
    break;
  case 'c':
    familyName = L"Courier New";
    break;
  case 'w':
    familyName = L"Wingdings";
    break;
  case 'v':
    familyName = L"Wingdings 2";
    break;
  case 's':
    familyName = L"Wingdings 3";
    break;
  case 'k':
    familyName = L"Webdings";
    break;
  case 'i':
    familyName = L"Terminal";
    break;
  }
  // Font->Charset = RUSSIAN_CHARSET;
  // Font->Charset = DEFAULT_CHARSET;
  if (text_settings.charsize != 1)
    font_size = text_settings.charsize;

  int PixelsPerInch = 96;
  font_size = font_size * 72 / PixelsPerInch + 1;

  gdp::Font myFont(familyName, abs(font_size),
                   is_bold ? gdp::FontStyleBold : gdp::FontStyleRegular,
                   gdp::UnitPixel
                   //                     gdp::UnitPoint
  );
  GDPCHECK(myFont.GetLastStatus());
  return myFont.Clone();
}
