#ifndef WINFONTS_H
#define WINFONTS_H
//----------------------------------------------------------------------------
//  Copyright GTSS c 2006. All Rights Reserved.
//----------------------------------------------------------------------------
#include <windows.h>
#include <systypes.h>


const int FontCount = 32;

//FONTS
extern int F_DEFAULT; //0
extern int F_LITT   ; //1
extern int F_LITT_S ; //2
extern int F_LITT_B ; //3

#define NULLFONT 0+4
#define COURE12 1+4
#define COURE18 2+4
#define COURE22 3+4
#define COURE28 4+4
#define TIMES12 5+4
#define TIMES14 6+4
#define TIMES18 7+4
#define TIMES20 8+4
#define TIMES20b 9+4
#define TIMES22 10+4
#define TIMES28 11+4
#define ARIAL12 12+4
#define ARIAL18 13+4
#define ARIAL22 14+4
#define ARIAL28 15+4
#define TIMES30b 16+4
#define TIMES28b 17+4
#define COURE28b 18+4
#define ARIAL12b 19+4
#define COURE12b 20+4
#define COURE16  21+4
#define ARIAL10b 22+4
#define WINDI10b 23+4
#define WIND210b 24+4
#define WIND310b 25+4
#define WEBDI10b 26+4
#define TERMI10b 27+4

void CreateFonts();
void DestroyFonts();











//----------------------------------------------------------------------------
#endif  //
