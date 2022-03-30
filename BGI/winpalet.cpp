#include "winpalet.h"


#include <iostream>
#include <fstream>
#include <algorithm>


static RGBQUAD rgbStd256[] = {
    {   0,  0,  0, 0 }, {   0,  0, 128, 0 }, {   0, 128,  0, 0 }, {   0, 128, 128, 0 },
    { 128,  0,  0, 0 }, { 128,  0, 128, 0 }, { 128, 128,  0, 0 }, { 192, 192, 192, 0 },
    { 192, 220, 192, 0 }, { 240, 202, 166, 0 }, { 238, 238, 238, 0 }, { 221, 221, 221, 0 },
    { 204, 204, 204, 0 }, { 187, 187, 187, 0 }, { 170, 170, 170, 0 }, { 153, 153, 153, 0 },
    { 136, 136, 136, 0 }, { 119, 119, 119, 0 }, { 102, 102, 102, 0 }, {  85, 85, 85, 0 },
    {  68, 68, 68, 0 }, {  51, 51, 51, 0 }, {  34, 34, 34, 0 }, {  17, 17, 17, 0 },
    { 204, 255, 255, 0 }, { 153, 255, 255, 0 }, { 102, 255, 255, 0 }, {  51, 255, 255, 0 },
    { 255, 204, 255, 0 }, { 204, 204, 255, 0 }, { 153, 204, 255, 0 }, { 102, 204, 255, 0 },
    {  51, 204, 255, 0 }, {   0, 204, 255, 0 }, { 255, 153, 255, 0 }, { 204, 153, 255, 0 },
    { 153, 153, 255, 0 }, { 102, 153, 255, 0 }, {  51, 153, 255, 0 }, {   0, 153, 255, 0 },
    { 255, 102, 255, 0 }, { 204, 102, 255, 0 }, { 153, 102, 255, 0 }, { 102, 102, 255, 0 },
    {  51, 102, 255, 0 }, {   0, 102, 255, 0 }, { 255, 51, 255, 0 }, { 204, 51, 255, 0 },
    { 153, 51, 255, 0 }, { 102, 51, 255, 0 }, {  51, 51, 255, 0 }, {   0, 51, 255, 0 },
    { 204,  0, 255, 0 }, { 153,  0, 255, 0 }, { 102,  0, 255, 0 }, {  51,  0, 255, 0 },
    { 255, 255, 204, 0 }, { 204, 255, 204, 0 }, { 153, 255, 204, 0 }, { 102, 255, 204, 0 },
    {  51, 255, 204, 0 }, {   0, 255, 204, 0 }, { 255, 204, 204, 0 }, { 153, 204, 204, 0 },
    { 102, 204, 204, 0 }, {  51, 204, 204, 0 }, {   0, 204, 204, 0 }, { 255, 153, 204, 0 },
    { 204, 153, 204, 0 }, { 153, 153, 204, 0 }, { 102, 153, 204, 0 }, {  51, 153, 204, 0 },
    {   0, 153, 204, 0 }, { 255, 102, 204, 0 }, { 204, 102, 204, 0 }, { 153, 102, 204, 0 },
    { 102, 102, 204, 0 }, {  51, 102, 204, 0 }, {   0, 102, 204, 0 }, { 255, 51, 204, 0 },
    { 204, 51, 204, 0 }, { 153, 51, 204, 0 }, { 102, 51, 204, 0 }, {  51, 51, 204, 0 },
    {   0, 51, 204, 0 }, { 255,  0, 204, 0 }, { 204,  0, 204, 0 }, { 153,  0, 204, 0 },
    { 102,  0, 204, 0 }, {  51,  0, 204, 0 }, { 255, 255, 153, 0 }, { 204, 255, 153, 0 },
    { 153, 255, 153, 0 }, { 102, 255, 153, 0 }, {  51, 255, 153, 0 }, {   0, 255, 153, 0 },
    { 255, 204, 153, 0 }, { 204, 204, 153, 0 }, { 153, 204, 153, 0 }, { 102, 204, 153, 0 },
    {  51, 204, 153, 0 }, {   0, 204, 153, 0 }, { 255, 153, 153, 0 }, { 204, 153, 153, 0 },
    { 102, 153, 153, 0 }, {  51, 153, 153, 0 }, {   0, 153, 153, 0 }, { 255, 102, 153, 0 },
    { 204, 102, 153, 0 }, { 153, 102, 153, 0 }, { 102, 102, 153, 0 }, {  51, 102, 153, 0 },
    {   0, 102, 153, 0 }, { 255, 51, 153, 0 }, { 204, 51, 153, 0 }, { 153, 51, 153, 0 },
    { 102, 51, 153, 0 }, {  51, 51, 153, 0 }, {   0, 51, 153, 0 }, { 255,  0, 153, 0 },
    { 204,  0, 153, 0 }, { 153,  0, 153, 0 }, { 102,  0, 153, 0 }, {  51,  0, 153, 0 },
    { 255, 255, 102, 0 }, { 204, 255, 102, 0 }, { 153, 255, 102, 0 }, { 102, 255, 102, 0 },
    {  51, 255, 102, 0 }, {   0, 255, 102, 0 }, { 255, 204, 102, 0 }, { 204, 204, 102, 0 },
    { 153, 204, 102, 0 }, { 102, 204, 102, 0 }, {  51, 204, 102, 0 }, {   0, 204, 102, 0 },
    { 255, 153, 102, 0 }, { 204, 153, 102, 0 }, { 153, 153, 102, 0 }, { 102, 153, 102, 0 },
    {  51, 153, 102, 0 }, {   0, 153, 102, 0 }, { 255, 102, 102, 0 }, { 204, 102, 102, 0 },
    { 153, 102, 102, 0 }, {  51, 102, 102, 0 }, {   0, 102, 102, 0 }, { 255, 51, 102, 0 },
    { 204, 51, 102, 0 }, { 153, 51, 102, 0 }, { 102, 51, 102, 0 }, {  51, 51, 102, 0 },
    {   0, 51, 102, 0 }, { 255,  0, 102, 0 }, { 204,  0, 102, 0 }, { 153,  0, 102, 0 },
    { 102,  0, 102, 0 }, {  51,  0, 102, 0 }, { 255, 255, 51, 0 }, { 204, 255, 51, 0 },
    { 153, 255, 51, 0 }, { 102, 255, 51, 0 }, {  51, 255, 51, 0 }, {   0, 255, 51, 0 },
    { 255, 204, 51, 0 }, { 204, 204, 51, 0 }, { 153, 204, 51, 0 }, { 102, 204, 51, 0 },
    {  51, 204, 51, 0 }, {   0, 204, 51, 0 }, { 255, 153, 51, 0 }, { 204, 153, 51, 0 },
    { 153, 153, 51, 0 }, { 102, 153, 51, 0 }, {  51, 153, 51, 0 }, {   0, 153, 51, 0 },
    { 255, 102, 51, 0 }, { 204, 102, 51, 0 }, { 153, 102, 51, 0 }, { 102, 102, 51, 0 },
    {  51, 102, 51, 0 }, {   0, 102, 51, 0 }, { 255, 51, 51, 0 }, { 204, 51, 51, 0 },
    { 153, 51, 51, 0 }, { 102, 51, 51, 0 }, {   0, 51, 51, 0 }, { 255,  0, 51, 0 },
    { 204,  0, 51, 0 }, { 153,  0, 51, 0 }, { 102,  0, 51, 0 }, {  51,  0, 51, 0 },
    { 204, 255,  0, 0 }, { 153, 255,  0, 0 }, { 102, 255,  0, 0 }, {  51, 255,  0, 0 },
    { 255, 204,  0, 0 }, { 204, 204,  0, 0 }, { 153, 204,  0, 0 }, { 102, 204,  0, 0 },
    {  51, 204,  0, 0 }, { 255, 153,  0, 0 }, { 204, 153,  0, 0 }, { 153, 153,  0, 0 },
    { 102, 153,  0, 0 }, {   0,  0, 238, 0 }, {   0,  0, 221, 0 }, {   0,  0, 204, 0 },
    {   0,  0, 187, 0 }, {   0,  0, 170, 0 }, {   0,  0, 153, 0 }, {   0,  0, 136, 0 },
    {   0,  0, 119, 0 }, {   0,  0, 102, 0 }, {   0,  0, 85, 0 }, {   0,  0, 68, 0 },
    {   0,  0, 51, 0 }, {   0,  0, 34, 0 }, {   0,  0, 17, 0 }, {   0, 238,  0, 0 },
    {   0, 221,  0, 0 }, {   0, 204,  0, 0 }, {   0, 187,  0, 0 }, {   0, 170,  0, 0 },
    {   0, 153,  0, 0 }, {   0, 136,  0, 0 }, {   0, 119,  0, 0 }, {   0, 102,  0, 0 },
    {   0, 85,  0, 0 }, {   0, 68,  0, 0 }, {   0, 51,  0, 0 }, {   0, 34,  0, 0 },
    {   0, 17,  0, 0 }, { 238,  0,  0, 0 }, { 221,  0,  0, 0 }, { 204,  0,  0, 0 },
    { 187,  0,  0, 0 }, { 170,  0,  0, 0 }, { 153,  0,  0, 0 }, { 136,  0,  0, 0 },
    { 119,  0,  0, 0 }, { 102,  0,  0, 0 }, {  85,  0,  0, 0 }, {  68,  0,  0, 0 },
    {  51,  0,  0, 0 }, {  34,  0,  0, 0 }, { 240, 251, 255, 0 }, { 164, 160, 160, 0 },
    { 128, 128, 128, 0 }, {   0,  0, 255, 0 }, {   0, 255,  0, 0 }, {   0, 255, 255, 0 },
    { 255,  0,  0, 0 }, { 255,  0, 255, 0 }, { 255, 255,  0, 0 }, { 255, 255, 255, 0 }
};
//----------------------------------------------------------------------------
const int MX = 4;
/*TBgiPalette* BgiPalette=NULL;
//----------------------------------------------------------------------------
__fastcall TBgiPalette::TBgiPalette()
        :
        m_Palette(NULL),
        lpLogPal(NULL)
{
    lpLogPal = (LPLOGPALETTE) new BYTE[sizeof(LOGPALETTE) + ((255) * sizeof(PALETTEENTRY))];
    lpLogPal->palVersion = 0x0300;
    lpLogPal->palNumEntries = 256;
    for (int i = 0; i < 256; i++) {
        lpLogPal->palPalEntry[i].peRed   = rgbStd256[i].rgbRed;
        lpLogPal->palPalEntry[i].peGreen = rgbStd256[i].rgbGreen;
        lpLogPal->palPalEntry[i].peBlue  = rgbStd256[i].rgbBlue;
        lpLogPal->palPalEntry[i].peFlags = 0;
    }

    for (int i = 0; i < sizeof(DAC)/sizeof(DAC[0]); i++) {
        lpLogPal->palPalEntry[i].peRed   = DAC[i].pe[0].peBlue *MX;//����������  ������������� �������
        lpLogPal->palPalEntry[i].peGreen = DAC[i].pe[0].peGreen*MX;
        lpLogPal->palPalEntry[i].peBlue  = DAC[i].pe[0].peRed  *MX;
        lpLogPal->palPalEntry[i].peFlags = PC_RESERVED;
    }
    m_Palette = ::CreatePalette( lpLogPal );
}
//----------------------------------------------------------------------------
__fastcall TBgiPalette::~TBgiPalette()
{
    ::DeleteObject(m_Palette);
    delete [] (BYTE *)lpLogPal;
}
//----------------------------------------------------------------------------
COLORREF __fastcall TBgiPalette::Color(int i)
{
    /*
     return i<256 ? RGB(lpLogPal->palPalEntry[i].peRed,
                lpLogPal->palPalEntry[i].peGreen,
                lpLogPal->palPalEntry[i].peBlue
                ) : 0;
    *
    static PALETTEENTRY pe[256];
    ::GetPaletteEntries(m_Palette, 0, 256, (LPPALETTEENTRY)&pe);
    return i<256 ? RGB(pe[i].peRed, pe[i].peGreen, pe[i].peBlue) : 0;
}
*/
//----------------------------------------------------------------------------
const int DAC_ARRAYSIZE = 32;
TDAC DAC[DAC_ARRAYSIZE] = {
    //   r  g   b    f    r2  g2  b2   f2  idx  dt
    {    0 , 0 , 0  , 0  , 63, 63, 63 , 0,  0 ,  0 }, // 0 C_D
    {    0 , 0 , 0  , 0  , 63, 63, 63 , 0,  0 ,  0 }, // 1
    {    20, 50, 20 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 2 ZEL
    {    0 , 42, 42 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 3 BIRUZOVIJ
    {    38, 1 , 1  , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 4 KRA
    {    63, 1 , 1  , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 5 //  ���������
    {    29, 13, 0  , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 6 LIN_W BROWN     ;     /* ���� ����� */
    {    52, 52, 52 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 7 LIN ;     /* ���� ����� */
    {    32, 32, 32 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 8 FON  ;     /* ���� ����� */
    {    25, 25, 25 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 9 FON1 ;     /* ���� ����� */
    {    10, 10, 10 , 0  , 63, 63, 63 , 0,  0 ,  6 }, // 10 SV_MIG   �/���
    {    63, 53, 28 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 11   ������
    {    20, 1 , 1  , 0  , 63, 1 , 1  , 0,  0 ,  10}, // 12   COLOR_PSV ��/���
    {    20, 60, 2  , 0  , 0 , 0 , 0  , 0,  0 ,  7 }, // 13   ZEL_MIG
    {    26, 36, 24 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 14   BOLOT
    {    63, 63, 63 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 15   TXT
    {    63, 53, 28 , 0  , 30, 30, 30 , 0,  0 ,  10}, // 16  ������/�����
    {    38, 1 , 1  , 0  , 30, 30, 30 , 0,  0 ,  10}, // 17  �������/�����
    {    63, 63, 63 , 0  , 30, 30, 30 , 0,  0 ,  10}, // 18  �����/�����
    {    20, 50, 20 , 0  , 30, 30, 30 , 0,  0 ,  10}, // 19  ������/�����
    {    0 , 0 , 0  , 0  , 38, 1 , 1  , 0,  0 ,  10}, // 20  �������/������
    {    38, 1 , 1  , 0  , 63, 63, 63 , 0,  0 ,  10}, // 21  �������/�����
    {    38, 1 , 1  , 0  , 20, 50, 20 , 0,  0 ,  10}, // 22  �������/������
    {    38, 1 , 1  , 0  , 63, 53, 28 , 0,  0 ,  10}, // 23  �������/������
    {    20, 50, 20, 0  , 52, 52 , 52 , 0,  0 ,  10}, // 24  ������/�� �����
    {    63, 53, 28, 0  , 52, 52 , 52 , 0,  0 ,  10}, // 25  ������/�� �����
    {    0,  0,  0 , 0  , 32, 32, 32 , 0,  0 ,  6 }, // 26   ���/ ������
    {    52, 52 , 52, 0  , 0 , 0 , 0  , 0,  0 ,  6 }, // 27   �� �����/������
    {    20, 1 , 1  , 0  , 63, 1 , 1  , 0,  0 ,  10}, // 28
    {    20, 60, 2  , 0  , 0 , 0 , 0  , 0,  0 ,  7 }, // 29
    {    26, 36, 24 , 0  , 0 , 0 , 0  , 0,  0 ,  0 }, // 30
    {    63, 63, 63 , 0  , 0 , 0 , 0  , 0,  0 ,  0 } // 31
};
//----------------------------------------------------------------------------
static float GradientFactor = 1;
void SetGradientFactor(float AGradientFactor)
{
    GradientFactor = AGradientFactor;
}
int GetGradientColor(int Color, float factor)
{
    if (factor == 1.) return Color;
    if (Color & 0xff000000) {
        //Color = ColorToRGB(Color);  ���� �� �� ����������?
        // �� ���� � ������ � ������� ��� ��� ���
        // throw ("GradientColor: it is not a RGB color");
    }
    int r = GetRValue(Color);
    int g = GetGValue(Color);
    int b = GetBValue(Color);

    double FACTOR = factor; //FACTOR= -0.8;
    /*  int i = (int)(1.0/(1.0-FACTOR));
      if ( r == 0 && g == 0 && b == 0)
                    return RGB(i, i, i);
      if ( r > 0 && r < i ) r = i;
      if ( g > 0 && g < i ) g = i;
      if ( b > 0 && b < i ) b = i;*/
    return RGB(std::min((int)(r / FACTOR), 255),
               std::min((int)(g / FACTOR), 255),
               std::min((int)(b / FACTOR), 255));

}


COLORREF BgiDacColor(unsigned int c)
{
    COLORREF clr;
    if (c < DAC_ARRAYSIZE) {
        // �� 32 ���� �� ������� ����
        clr = DAC[c].Clr[DAC[c].idx];
    } else if (c < 255) {
        // 32-255 ���� �� �������� ������� rgbStd256
        clr = RGB(rgbStd256[c].rgbRed,
                  rgbStd256[c].rgbGreen,
                  rgbStd256[c].rgbBlue);
    } else {
        // �� ��
        clr = c;
    }
    // ��������� ����������� ������� ����
    if ((GradientFactor != 1) && (c != 8)) clr = GetGradientColor(clr, GradientFactor);
    return clr;

}


//---------------------------------------------------------------------------


//----------------------------------------------------------------------------
char DACCfgFileName[256] = "./CFG/dac.cfg";
bool wc_LoadIniFile();
//----------------------------------------------------------------------------
int Get_DAC()
{
    using namespace std;
    ifstream is(DACCfgFileName);
    for (int i = 0; i < DAC_ARRAYSIZE; i++) {
        // char  tmp[80];
        int r, g, b;
        int r2, g2, b2, dt;
        ws(is) >> r >> g >> b >> r2 >> g2 >> b2 >> dt;
        // is.get(tmp, sizeof(tmp), '\n');


        if (is.good()) {
            DAC[i].pe[0].peRed     = /*DacBgiColor[i].rgbBlue =*/ r;
            DAC[i].pe[0].peGreen   = /*DacBgiColor[i].rgbGreen =*/ g;
            DAC[i].pe[0].peBlue    = /*DacBgiColor[i].rgbRed =*/ b;
            DAC[i].pe[1].peRed     = r2;
            DAC[i].pe[1].peGreen   = g2;
            DAC[i].pe[1].peBlue    = b2;
            DAC[i].idx = false;
            DAC[i].dt = dt;
        } else break;
    }
    /* WinColors */
    wc_LoadIniFile();

    Update_DAC();

    return 1;
}
//----------------------------------------------------------------------------
extern  int            CommonAnimationStep;
void SwapDACColor()
{
    for (int i = 0; i < DAC_ARRAYSIZE; i++)
        if (DAC[i].dt != 0) DAC[i].idx = !DAC[i].idx;
    Update_DAC();
    CommonAnimationStep++;

}
//----------------------------------------------------------------------------
void  Update_DAC(void)
{
    for (int i = 0; i < DAC_ARRAYSIZE; i++) {
        for (int j = 0; j < 2; j++)
            DAC[i].Clr[j] = RGB(DAC[i].pe[j].peRed * MX,
                                DAC[i].pe[j].peGreen * MX,
                                DAC[i].pe[j].peBlue * MX);
    }
}
//----------------------------------------------------------------------------
bool  IsClrMig(int Clr)
{
    if (Clr < 0)
        return false;
    if ((Clr < DAC_ARRAYSIZE) && (DAC[Clr].dt != 0)) return true;
    return false;
}
//----------------------------------------------------------------------------


