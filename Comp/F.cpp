#include <vcl.h>
#pragma hdrstop
#include "APch.h"


#include "F.h"

//#undef DEBUG_X
//#define DEBUG_X

/* закоментарил - нигде не используется
bool DEBUG_X=false;
#define EDT_
int Set_Color_by_Num(int n){
    int g = n/1000;
    switch(g){
        case 0: return MAGEN;
        case 1:
        case 2:
        case 3:
        case 4: return CYAN_m;
        case 5: return BOLOT;
        case 6: return COLOR_SET;
        case 7:
        case 8:
        case 9: return TXT;
    }
    return TXT;
}
*/

//#ifdef DEBUG_X
/*void Out_MY(unsigned char dr,su_st MM,int x ,int y){
 if (!DEBUG_X) return;
 int s=15;
 int d=6;
 int s2;
 char *buf="        ";
 if(dr==ODD){ s=-8;s2=-10;}
 if(dr==EVEN) {s=8;s2=10;}
 _SetText(F_LITT,LEFT_TEXT,CENTER_TEXT);
 setcolor(BLUE_m);
 setfillstyle(1,FON);
 bar(x,y+s-4,x+4*d,y+s+4);
 OutTextXY(x,y+s+s2,"Ї§б¬");
 OutTextXY(x,y+s,itoa(MM.pere,buf,10));
 OutTextXY(x+d,y+s,itoa(MM.busi,buf,10));
 OutTextXY(x+2*d,y+s,itoa(MM.sign,buf,10));
 OutTextXY(x+3*d,y+s,itoa(MM.marh,buf,10));
} */
/*
#else
void Out_MY(DIRECT ,su_st ,int  ,int ){}
#endif

#ifdef DEBUG_X
*/
/*void Out_TB(unsigned char dr,TAB_SW *W1, TAB_SW *W2,int x ,int y){
//void Out_TB(DIRECT dr,TAB_SW *W1, TAB_SW *W2,int x ,int y){
 if (!DEBUG_X) return;

 int s=15;
 int d=8;
 char *buf="           ";
 if(dr==ODD){ s=-8;}
 if(dr==EVEN) {s=8;}
 _SetText(F_LITT,LEFT_TEXT,CENTER_TEXT);
 setcolor(BLUE_m);
 setfillstyle(1,FON);
 bar(x,y+s-4,x+4*d,y+s+4);
 int n=0;
 setcolor(TXT);
 OutTextXY(x+n*d,y+s,itoa(W1->stz,buf,10));n++;
 setcolor(BLUE_m);
  if((W1->w1!=0)&&(W1->w1<20))
  { OutTextXY(x+n*d,y+s,itoa(W1->w1,buf,10));n++;}
  if((W1->w2!=0)&&(W1->w2<20))
  { OutTextXY(x+n*d,y+s,itoa(W1->w2,buf,10));n++;}
  if((W1->w3!=0)&&(W1->w3<20))
  { OutTextXY(x+n*d,y+s,itoa(W1->w3,buf,10));n++;}
  if((W2->w1!=0)&&(W2->w1<20))
  { OutTextXY(x+n*d,y+s,itoa(W2->w1,buf,10));n++;}
  if((W2->w2!=0)&&(W2->w2<20))
  { OutTextXY(x+n*d,y+s,itoa(W2->w2,buf,10));n++;}
  if((W2->w3!=0)&&(W2->w3<20))
  { OutTextXY(x+n*d,y+s,itoa(W2->w3,buf,10));n++;}
}
/*
#else
void Out_TB(DIRECT ,TAB_SW *, TAB_SW *,int ,int ){}
#endif
*/

/*
void Box_R(int x1,int y1,int x2,int y2)// ->
{
 int k[12];
 int x3=x2;
  x2=x3-(y2-y1);
 int y3=y1+(y2-y1)/2;//+1;

   k[0] =x1;   k[1] =y1;
   k[2] =x2;   k[3] =y1;
   k[4] =x3;   k[5] =y3;
   k[6] =x2;   k[7] =y2;
   k[8] =x1;   k[9] =y2;
   k[10]=x1;   k[11]=y1;

   fillpoly(6,k);
}

void Box_L(int x1,int y1,int x2,int y2)  // <-
{
 int x3=x1;
     x1=x3+(y2-y1);
 int y3=y1+(y2-y1)/2;//+1;
 int k[12];
   k[0] =x1;   k[1] =y1;
   k[2] =x2;   k[3] =y1;
   k[4] =x2;   k[5] =y2;
   k[6] =x1;   k[7] =y2;
   k[8] =x3;   k[9] =y3;
   k[10]=x1;   k[11]=y1;
   fillpoly(6,k);
}


#ifdef EDT_
 void Z_E(int x,int y,char *nm){
  setcolor(TXT);
  int s=5;
  int len=15;
  int ss =10;
  Box_R(x,y-s+ss,x+len,y+s+ss);
 _SetText(F_LITT,LEFT_TEXT,CENTER_TEXT);
  OutTextXY(x+1,y+ss,nm);
 }
#else
 void Z_E(int ,int ,char *){}
#endif

#ifdef EDT_
 void Z_E_L(int x,int y,int x2,int y2,int ch){
  setcolor(TXT);
  int s=5;
  int len=15;
  int ss =10;
  if(ch==1)
     line(x+len+s,y+ss,x2,y2+ss);
  else
     line(x,y+ss,x2+len+s,y2+ss);
 }
#else
 void Z_E_L(int ,int ,int ,int ,int ){ }
#endif

#ifdef EDT_
 void Z_O_L(int x,int y,int x2,int y2,int ch){
  setcolor(C_D);
  int s=5;
  int len=15;
  int ss =10;
  if(ch==1)
    line(x-s,y-ss,x2+len,y2-ss);
  else
    line(x+len,y-ss,x2-s,y2-ss);
 }
#else
 void Z_O_L(int ,int ,int ,int ,int ){}
#endif

#ifdef EDT_
 void Z_O(int x,int y,char *nm){
  setcolor(C_D);
  int s=5;
  int len=15;
  int ss =10;
  Box_L(x,y-s-ss,x+len,y+s-ss);
 _SetText(F_LITT,LEFT_TEXT,CENTER_TEXT);
  OutTextXY(x+1,y-ss,nm);
 }
#else
 void Z_O(int ,int ,char *){}
#endif

//int f(int impls);
*/
int Clr_lev(int clr)
{
    if (clr == LIN)        return 1;
    if (clr == COLOR_S)    return 2;
    if (clr == COLOR_B)    return 4;
    if (clr == COLOR_SET)  return 3;
    if (clr == BIRUZOVIJ)  return 5;
    return 0;
}

int Lev_clr(int lev)
{
    switch (lev) {
    case 1:
        return LIN;
    case 2:
        return COLOR_S;
    case 3:
        return COLOR_SET;
    case 4:
        return COLOR_B;
    case 5:
        return BIRUZOVIJ;
    }
    return 0;
}

int Clr_Set(int tst)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
    if (!tst) return COLOR_F_P;
    else return COLOR_B;
}

int Clr_Set2(int tst, int tst2)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
    if (tst)  return COLOR_B;
    else  if (!tst2) return COLOR_F_P;
    else      return COLOR_SET;
}

int Clr_SetPl(int tst, int tst2)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
//  if(tst2){
    if (!tst)  return COLOR_F_P;
    else return COLOR_B;
    /*
    }else{
    if(!tst)  return COLOR_F_P;
    else return COLOR_B;
    }
    */
}


int Clr_SetC(int tst, int M, int imp1, int imp2)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
    if (!M) {
        if (tst) {
            //  !!!  вот они миг сигналы
            if (imp1)  return ZEL_MIG;
            return COLOR_SVZ;
        } else {
            //              if(imp1)  return 12;
            return FON;
        }
    } else {
        if (tst) {
            if (imp1)  return SV_MIG; else
                return TXT;
        } else {
            if (imp1)  return COLOR_PSV; else
                return FON;
        }
    }
}

int Clr_SetC(int tst, char *nam)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
    int M = 0;
    if (

        (nam != 0) && (
            (nam[0] == 'm') ||
            (nam[0] == 'м') ||
            (nam[0] == 'М') ||
            (nam[0] == 'M')
        )
    )  M = 1;

    if (!M)
        if (tst) return COLOR_SVZ;
        else return FON;
    else if (tst) {
        int f = 0;
        f++;
        return TXT;
    } else return FON;
}

int Clr_SetN(int tst)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
    if (tst) return COLOR_B;
    else return COLOR_SET;
}

int Clr_SetK(int tst)
{
    if (tst == 33) return BIRUZOVIJ;
    if (tst == 31) return FON;
//  if(tst< 0 ) return BIRUZOVIJ;
    if (!tst) return LIN;
    else return COLOR_SET;
}






