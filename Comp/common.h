#ifndef COMMON_H
#define COMMON_H

#include "ACom_V.h"

#include <string>

class AComp;

//-------------------------------------------------------------------
//                 œ–Œ“Œ“»œ€ ‘”Õ ÷»…
//-------------------------------------------------------------------

extern void Color_Off(void);
extern void Color_On(void);

extern void Qui(const char*, int, int);
void WriteToLog(const std::string& Str);
void WriteToErr(const std::string& Str);

/*
struct TImpPropNamesInfo {
    char   CompType[64];
    char   CompName[64];

    int    ImpCount;
    char   ImpName[6][64];
    int RealOffset[6];
};
void  _GetImpPropNamesInfo(AComp * ac , TImpPropNamesInfo &I);
*/
const char* GetTypeName(AComp* AC);
const char* GetTypeAndName(AComp* AC);

#endif
