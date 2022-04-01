#ifndef STR~FUN_H
#define STR~FUN_H



#define SW 9
#define SZ 7
extern int mas__;
extern int len_4;
extern int Len;

extern int pr1[4];
extern int kr[18];
extern int sh;
extern int sh2;
extern int NomerHeight;

// extern uint8 *ras;
// extern uint8 * ras_6[];

int   S(int len);    //смещение
int   S2(int len);   //----
int   S3(int len);   // обр тн я корректировккк 
int    S4(int len);   // отр женн я ширин 
int    S5(int len);

void   L(int x, int y, int len);
void   KT(int x, int y, int len, int sw, int ll2 = 0);
void   KB(int x, int y, int len, int sw, int ll2 = 0);
void   _bar3d_(int x1, int y1, int x2, int y2, int bord, int clr);
int    linec(int x2, int y2, int x1, int y1, int h, int direct);
void   _fillpoly_(int sw_tip, int  kr[], int dr);
//void  Strelka(int is,int sw_tip,int styll1,int styll2,int clr,int nm,int x_text,int y_text,char *name, bool InvresPol,int cbord1,int cbord2,bool bShowPol);
void   KY(int y1, int y, int x);
void   krt(int x, int y, int len, int);
void   krb(int x, int y, int len, int);
void   klt(int x, int y, int len, int);
void   klb(int x, int y, int len, int);
void  Str(int X, int Y, int c, int uc, int a1, int a2, int clr, int LUDOCHKA);



#endif
