#ifndef COMMON_H
#define COMMON_H

#include "ACom_V.h"

#include <string>

void Color_Off(void);
void Color_On(void);

void CriticalErr(const char*, bool do_throw=true);
inline void CriticalErr(const String& txt) { CriticalErr(txt.c_str()); }

void PrintErr(const char* txt);
//inline void PrintErr(const std::string& txt) { PrintErr(txt.c_str()); }
inline void PrintErr(const String& txt) { PrintErr(txt.c_str()); }


class AComp;
const char* GetTypeName(AComp* AC);
const char* GetTypeAndName(AComp* AC);


#endif
