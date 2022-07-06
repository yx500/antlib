#ifndef AHEADERS_H_H
#define AHEADERS_H_H

#ifdef __BORLANDC__
#include <Classes.hpp>
#include <system.hpp>
#include <systypes.h>

#else // QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT QT

#include <cstring>
#include <unistd.h>
//#define QT_ANTLIB
#define __fastcall
#include "systypes.h"
#include "win/w32defs.h"
#include "antlibgraphics.h"
#include "vcllib.h"

#endif  //__BORLANDC__



#include "astring.h"
#include "astringlist.h"
#include "utils.h"



#endif // AHEADERS_H_H
