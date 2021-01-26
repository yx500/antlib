#ifndef _SCRIN_H
#define _SCRIN_H

void Mini_Box(int x1, int y1, int x2, int y2, int c1, int c2, int cf);
void Super_Text(int x1, int y1, int c1, int c2, char *txt);
void Box(int x1, int y1, int x2, int y2);
void Super_Box_(int x1, int y1,
                int x2, int y2,
                int h,
                int c1, int c2, int c3, int c4,
                int cf);
void Super_Box(int x1, int y1,
               int x2, int y2,
               int h,
               int c1, int c2, int c3, int c4);
void S_B(int rg);
void barx(int , int , int , int);

#endif
