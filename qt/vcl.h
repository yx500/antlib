#ifndef VCL_H
#define VCL_H

#include <QString>
class String :public QString
{
public:
    int Pos(const String& subStr) const { return indexOf(subStr);}
    int Length() const {return size();}
    int ToInt() const {return toInt(); }
    int ToIntDef(int defaultValue) const {
        bool ok=false;
        int r=toInt(&ok);
        if (!ok) r=defaultValue;
        return r;
    }

};

#endif // VCL_H
