//---------------------------------------------------------------------------
#ifndef AC_TOOLS_H
#define AC_TOOLS_H
//---------------------------------------------------------------------------
#include <systypes.h>
#include "ACom_T.h"





void  SetYchDir(const char* dir);
void  SetStaDir(const char* dir);
void  SetDatDir(const char* dir);
const char* FullYchFileName(const char* fn);
const char* FullStaFileName(const char* fn);
const char* FullDatFileName(const char* fn);
void  SetRootDir(const char* dir);


extern char Root_Dir[256];

extern const char* CommitFile(const char* file);




//---------------------------------------------------------------------------
#endif


