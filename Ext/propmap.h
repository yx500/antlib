#ifndef propmapH
#define propmapH
#include "aheaders_h.h"

#include <vector>
#include <map>


class _Props
{
public:
    struct Elem {
        String  lKey;
        String  lVal;
        void*   Obj;
    };

private:
    typedef template std::vector<Elem>     BoxType;
    typedef template std::map<String, Elem*> IndexType;

    BoxType box;
    IndexType index;

    void  reindex();

public:
    _Props(): box(), index() {
        box.reserve(32);
    }

    const Elem& get(int i) const {
        return  box[i];
    }
    int count() const {
        return  box.size();
    }
    void clear() {
        index.clear();
        box.clear();
        box.reserve(32);
    }

    void erase(const String& key);

    Elem* ElemOf(const String& key, bool create = false) {
        IndexType::const_iterator f = index.find(key);
        if (f != index.end())
            return f->second;
        else {
            if (!create)
                return  0;

            bool reidx = (box.size() == box.capacity());
            Elem e; e.lKey = key;
            box.push_back(e);
            if (!reidx)
                index[key] = &box.back();
            else
                reindex();
            return  &box.back();
        }
    }

    void setKey(int i, const String& n) {
        box[i].lKey = n;
        reindex();
    }
    void setVal(int i, const String& n) {
        box[i].lVal = n;
    }
    void setObj(int i, void* o) {
        box[i].Obj = o;
    }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class TPropMap
{
private:
    _Props  _p;

public:

    bool bNotPutDefault;

    TPropMap();
    ~TPropMap() {}
    String get(String stKey);
    String getOEM(String stKey);
    String getEx(String stKey, void ** ptr);
    void*   getPtr(String stKey);
    int geti(String stKey) {
        return StrToIntDef(get(stKey), 0);
    }

    void putEx(String stKey, String stVal, void * ptr);
    void putEx(String stKey, String stVal, void * ptr, String stValDef);
    void putOEM(String stKey, String stVal);

    void put(String stKey, String stVal) {
        putEx(stKey, stVal, 0);
    }
    void put(String stKey, String stVal, String stValDef)   {
        putEx(stKey, stVal, 0, stValDef);
    }
    void put(String stKey, int iVal)    {
        put(stKey, IntToStr(iVal));
    }
    void put(String stKey, int iVal, int iValDef) {
        put(stKey, IntToStr(iVal), IntToStr(iValDef));
    }

    void del(String stKey) {
        _p.erase(stKey);
    }

    const char* text() {
        return this->textext('=', '\n');
    }
    void text(char *szText) {
        this->textext(szText, '=', '\n');
    }

    void textext(char* szText, char rkeyval = '=', char rString = '\n', bool clr = true);
    const char* textext(char rkeyval = '=', char rString = '\n');

    bool KeyExists(String stKey) {
        return (_p.ElemOf(stKey) != 0);
    }
//---------------------------------------------------------------------------
    TStringList* createStringList();

    void addpropmap(TPropMap & pm);
    void putpropmapstr(char * sztext);
    const char * getpropmapstr(char * sztext);
    void AddToStringList(TStringList * SL);
    void putkeyvalst(String S);

    String operator [](int i) {
        return _p.get(i).lVal;
    };
    void clear() {
        _p.clear();
    }
    __property int ItemsCount  = { read = GetItemsCount };
    __property String Keys[ int i ]  = { read = GetKeys, write = SetKeys };
    __property String Val[ int i ]  = { read = GetVal, write = SetVal };
    __property String P[ String stKey]  = { read = GetP, write = SetP };
private:
    int __fastcall GetItemsCount() {
        return _p.count();
    }
    void __fastcall SetKeys(int i, String value);
    String __fastcall GetKeys(int i);
    void __fastcall SetVal(int i, String value);
    String __fastcall GetVal(int i);
    void __fastcall SetP(String stKey, String value);
    String __fastcall GetP(String stKey);
};






//---------------------------------------------------------------------------
#endif
