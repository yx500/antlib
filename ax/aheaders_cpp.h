#ifndef AHEADERS_CPP_H
#define AHEADERS_CPP_H

#include "aheaders_h.h"

#ifdef __BORLANDC__
#include <vcl.h>
//#pragma hdrstop
#if (__BORLANDC__ >= 0x530)

#endif
#else

#ifndef _WIN32
using namespace alib;
#endif

#endif

#endif // AHEADERS_CPP_H
