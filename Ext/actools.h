
#ifndef AC_TOOLS_H
#define AC_TOOLS_H

#include "aheaders_h.h"

inline const char* CommitFile(const char* file) { return file; }
inline const char* CommitFile(const String& file) { return file.c_str(); }

#endif
