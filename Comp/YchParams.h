//---------------------------------------------------------------------------

#ifndef YchParamsH
#define YchParamsH
//---------------------------------------------------------------------------
#include "ACom_T.h"


//extern  void __fastcall AOGetANTON(TAntOpt * AO= NULL);
//extern  void __fastcall AOSetANTON(TAntOpt * AO= NULL);

extern  bool __fastcall AOReadFromIni(void * pFI, String Sect, TAntOpt * AO);
extern  bool __fastcall AOWriteToIni(void * pFI, String Sect, TAntOpt * AO);

extern  bool LoadYchParams(String FileName, TAntOpt * AO);
extern  bool SaveYchParams(String FileName, TAntOpt * AO);

extern bool bLoadYchParams;

#endif
