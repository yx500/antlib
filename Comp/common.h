#ifndef COMMON_H
#define COMMON_H

#include "ACom_V.h"

#include <string>

extern void Color_Off(void);
extern void Color_On(void);

extern void CriticalError(const char*, bool do_throw=true);
void PrintError(const char* txt);
inline void PrintError(const std::string& txt) { PrintError(txt.c_str()); }


class AComp;
const char* GetTypeName(AComp* AC);
const char* GetTypeAndName(AComp* AC);


#endif
