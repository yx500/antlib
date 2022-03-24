#ifndef WINBGI_H
#define WINBGI_H
//----------------------------------------------------------------------------
//  Copyright GTSS c 2006. All Rights Reserved.
//----------------------------------------------------------------------------

#ifdef QT_ANTLIB
#include "winbgi_qt.h"
#else
#ifdef _USE_WINGDIPLUS
# include "winbgi_gdp.h"
#else
# include "winbgi_vcl.h"
#endif
#endif

//----------------------------------------------------------------------------
#endif
