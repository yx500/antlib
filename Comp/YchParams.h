#ifndef YchParamsH
#define YchParamsH

#include "aheaders_h.h"
#include "ACom_T.h"
#include "ACom_V.h"

extern bool AOReadFromIni(void* pFI, String Sect, TAntOpt* AO);
extern bool AOWriteToIni(void* pFI, String Sect, TAntOpt* AO);
extern bool LoadYchParams(String FileName, TAntOpt* AO);
extern bool SaveYchParams(String FileName, TAntOpt* AO);
extern bool bLoadYchParams;


#endif
