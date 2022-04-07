#ifndef uImgContainerH
#define uImgContainerH

#include "aheaders_h.h"

bool im_drawemf(void* vhdc,
                const RECT* lpRect,
                const char* szimagename,
                int animstep = 0);

#include <string>
extern std::string imgcontainerpath;

#endif
