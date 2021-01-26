//---------------------------------------------------------------------------

#ifndef YchParamsH
#define YchParamsH
//---------------------------------------------------------------------------
#include "ACom_T.h"


//extern  void _ALIB_ __fastcall AOGetANTON(TAntOpt * AO= NULL);
//extern  void _ALIB_ __fastcall AOSetANTON(TAntOpt * AO= NULL);

extern  bool _ALIB_ __fastcall AOReadFromIni(void * pFI, String Sect, TAntOpt * AO);
extern  bool _ALIB_ __fastcall AOWriteToIni(void * pFI, String Sect, TAntOpt * AO);

extern  bool _ALIB_ LoadYchParams(String FileName, TAntOpt * AO);
extern  bool _ALIB_ SaveYchParams(String FileName, TAntOpt * AO);

extern bool _ALIB_ bLoadYchParams;

#endif
