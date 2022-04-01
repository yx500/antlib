#include "aheaders_cpp.h"


#include "actools.h"
#include "common.h"
#include "Polig.h"
#include "Stan.h"
#include "Comp.h"

#include <string>
#include <fstream>
#include <map>

using namespace std;

char Root_Dir[256];
//---------------------------------------------------------------------------
const char* FullYchFileName(const char* fn)
{
    static string name;
    name = string(Ych_Dir) + fn + ".ych";
    return name.c_str();
}
//---------------------------------------------------------------------------
void  SetYchDir(const char* dir)
{
    if (!dir) return;
    strncpy(Ych_Dir, IncludeTrailingBackslash(dir).c_str(),sizeof(Ych_Dir)-1);
}
//---------------------------------------------------------------------------
const char* FullStaFileName(const char* fn)
{
    static string name;
    name = string(Sta_Dir) + fn + ".sta";
    return name.c_str();
}
//---------------------------------------------------------------------------
void  SetStaDir(const char* dir)
{
    if (!dir) return;
    strncpy(Sta_Dir, IncludeTrailingBackslash(dir).c_str(),sizeof(Sta_Dir)-1);
}
//---------------------------------------------------------------------------
const char* FullDatFileName(const char* fn)
{
    static string name;
    name = string(Dat_Dir) + fn;
    return name.c_str();
}
//---------------------------------------------------------------------------
void  SetDatDir(const char* dir)
{
    if (!dir) return;
    strncpy(Dat_Dir, IncludeTrailingBackslash(dir).c_str(),sizeof(Dat_Dir)-1);
}
//---------------------------------------------------------------------------
void  SetRootDir(const char* dir)
{
    if (!dir) return;
    strncpy(Root_Dir, IncludeTrailingBackslash(dir).c_str(),sizeof(Root_Dir)-1);
}

//---------------------------------------------------------------------------
const char* _AntCommitFile(const char* file);
const char* CommitFile(const char* file)
{
#if !defined (USING_ANT_EXTENSION_LIB)
    return file;
#else
    return _AntCommitFile(file);
#endif /* ! USING_ANT_EXTENSION_LIB */
}
//---------------------------------------------------------------------------

