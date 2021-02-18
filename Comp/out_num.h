
#ifndef OUT_NUM_CPP
#define OUT_NUM_CPP

#include "Comp.h"

class AComp;
class Ways;
void OutNum(int x, int y, int impuls);
void EXD_ShowTrainNumber(AComp *AC, int rimpb);
void EXD_HideTrainNumber(AComp *AC);
void EXD_UpdateTrainNumber(AComp *AC, int rimpb);
bool GetNumberRct(AComp *AC, int &X, int &Y, int Width, int Height, int direct);
void EXD_ShowTrainNumbers(AComp *AC, int rimpb);


/*class _ALIB_ TrNum:public AComp
{
public:

   int &imp_busy;
   int &impuls_kmu;
   int &impuls_mu;

   Ways * pWay;
   bool bTI;
   bool bMustClear;
   int X,Y,Width,Height,direct;

   virtual void UpdateState();
   virtual void  Show();
   TYP  GetType(){return  TRNUM;};
   UNIT GetUnit(){return TRNN;};

   virtual void Go();

   TrNum();
    ~TrNum(){}

};


*/

#endif
