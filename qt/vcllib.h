#pragma once

#include "win/w32defs.h"
#include "antlibstring.h"


struct TPoint : public POINT
{
  TPoint() {}
  TPoint(int _x, int _y) { x=_x; y=_y; }
  TPoint(POINT& pt)
  {
    x = pt.x;
    y = pt.y;
  }
};
typedef TPoint tagPoint;


struct TRect : public RECT
{
  TRect() {}
  TRect(const TPoint& TL, const TPoint& BR) { left=TL.x; top=TL.y; right=BR.x; bottom=BR.y; }
  TRect(int l, int t, int r, int b)         { left=l;    top=t;    right=r;    bottom=b;    }
  TRect(RECT& r) {
    left    = r.left;
    top     = r.top;
    right   = r.right;
    bottom  = r.bottom;
  }

  int Width () const { return right  - left; }
  int Height() const { return bottom - top ; }

  bool operator ==(const TRect& rc) const { return left == rc.left && top==rc.top && right == rc.right && bottom==rc.bottom; }
  bool operator !=(const TRect& rc) const { return !(rc==*this); }
};



typedef tagSIZE  TSize;


//todo remove naxyi
class TFileStream {
public:

};

void ShowMessage(const String& txt);

bool FileExists(const String& fn);
String ChangeFileExt(const String& fn, const char* ext);
