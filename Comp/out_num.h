#ifndef OUT_NUM_CPP
#define OUT_NUM_CPP

#include "Comp.h"

void OutNum(int x, int y, int impuls);
void EXD_ShowTrainNumber(AComp* AC, int rimpb);
void EXD_HideTrainNumber(AComp* AC);
void EXD_UpdateTrainNumber(AComp* AC, int rimpb);
bool GetNumberRct(AComp* AC, int& X, int& Y, int Width, int Height, int direct);
void EXD_ShowTrainNumbers(AComp* AC, int rimpb);

#endif
