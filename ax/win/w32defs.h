#ifndef W32DEFS_H
#define W32DEFS_H



#include <cstdint>

typedef struct tagPOINT
{
    long  x;
    long  y;
} POINT;

typedef struct tagRECT
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT;


typedef struct tagRGBQUAD {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} RGBQUAD;


typedef struct tagSIZE
{
  long        cx;
  long        cy;
} SIZE;




#endif // W32DEFS_H
