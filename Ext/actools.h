//---------------------------------------------------------------------------
#ifndef AC_TOOLS_H
#define AC_TOOLS_H
//---------------------------------------------------------------------------
#include <systypes.h>
#include "ACom_T.h"





void  _ALIB_ SetYchDir(const char* dir);
void  _ALIB_ SetStaDir(const char* dir);
void  _ALIB_ SetDatDir(const char* dir);
const char* _ALIB_ FullYchFileName(const char* fn);
const char* _ALIB_ FullStaFileName(const char* fn);
const char* _ALIB_ FullDatFileName(const char* fn);
void  _ALIB_ SetRootDir(const char* dir);


extern char _ALIB_ Root_Dir[256];

extern const char* _ALIB_ CommitFile(const char* file);




//---------------------------------------------------------------------------
#endif


