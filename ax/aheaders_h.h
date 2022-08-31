#ifndef AHEADERS_H_H
#define AHEADERS_H_H

#ifdef __BORLANDC__
    #include <Classes.hpp>
    #include <system.hpp>
    #include <systypes.h>

#else // QT QT QT QT QT QT QT QT QT QT 

    #include <cstring>
    #include <unistd.h>
    //#define QT_ANTLIB
    #ifndef _WIN32
      #define __fastcall
    #endif
    #include "systypes.h"
    #include "win/w32defs.h"
    #include "antlibgraphics.h"
    #include "vcllib.h"

#endif  //__BORLANDC__


#include "aaa.h"
#include "utils.h"



#endif // AHEADERS_H_H
