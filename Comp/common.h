#ifndef COMMON_H
#define COMMON_H

#include "ACom_V.h"

#include <string>

extern void Color_Off(void);
extern void Color_On(void);

extern void CriticalErr(const char*, bool do_throw=true);
void PrintErr(const char* txt);
inline void PrintErr(const std::string& txt) { PrintErr(txt.c_str()); }


class AComp;
const char* GetTypeName(AComp* AC);
const char* GetTypeAndName(AComp* AC);


#endif
