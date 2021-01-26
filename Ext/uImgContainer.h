//---------------------------------------------------------------------------

#ifndef uImgContainerH
#define uImgContainerH
//---------------------------------------------------------------------------
bool im_drawemf(void *vhdc,
                CONST RECT *lpRect,
                const char * szimagename,
                int animstep = 0
               );
#include <string>
extern std::string imgcontainerpath;


#endif
