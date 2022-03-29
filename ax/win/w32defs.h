#ifndef W32DEFS_H
#define W32DEFS_H



typedef struct tagPOINT
{
    int  x;
    int  y;
} POINT;

typedef struct tagRECT
{
    int    left;
    int    top;
    int    right;
    int    bottom;
} RECT;


typedef struct tagRGBQUAD {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} RGBQUAD;





#endif // W32DEFS_H
