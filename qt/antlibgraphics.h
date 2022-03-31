#ifndef ANTLIBGRAPHICS_H
#define ANTLIBGRAPHICS_H


/* 3D border styles */
#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER       (BDR_RAISEDOUTER | BDR_SUNKENOUTER)
#define BDR_INNER       (BDR_RAISEDINNER | BDR_SUNKENINNER)
#define BDR_RAISED      (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define BDR_SUNKEN      (BDR_SUNKENOUTER | BDR_SUNKENINNER)


#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)

/* Border flags */
#define BF_LEFT         0x0001
#define BF_TOP          0x0002
#define BF_RIGHT        0x0004
#define BF_BOTTOM       0x0008

#define BF_TOPLEFT      (BF_TOP | BF_LEFT)
#define BF_TOPRIGHT     (BF_TOP | BF_RIGHT)
#define BF_BOTTOMLEFT   (BF_BOTTOM | BF_LEFT)
#define BF_BOTTOMRIGHT  (BF_BOTTOM | BF_RIGHT)
#define BF_RECT         (BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM)

struct TPoint
{
    int x,y;
    TPoint() {}
    TPoint(int _x, int _y) {
        x=_x;
        y=_y;
    }

    TPoint(TPoint& pt){
        x = pt.x;
        y = pt.y;
    }
};

struct TRect
{
    long    left;
    long    top;
    long    right;
    long    bottom;
    TRect() {}
    TRect(const TPoint& TL, const TPoint& BR) { left=TL.x; top=TL.y; right=BR.x; bottom=BR.y; }
    TRect(int l, int t, int r, int b)         { left=l;    top=t;    right=r;    bottom=b;    }
    TRect(TRect& r)
    {
        left    = r.left;
        top     = r.top;
        right   = r.right;
        bottom  = r.bottom;
    }
    int Width () const { return right  - left; }
    int Height() const { return bottom - top ; }
    bool operator ==(const TRect& rc) const
    {
        return left ==  rc.left  && top==rc.top &&
                right == rc.right && bottom==rc.bottom;
    }
    bool operator !=(const TRect& rc) const
    {  return !(rc==*this); }
};


#endif // ANTLIBGRAPHICS_H
