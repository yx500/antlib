#ifndef propmapH
#define propmapH
//---------------------------------------------------------------------------
#include "aheaders_h.h"

#include <vector>
#include <map>



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class _Props
{
public:
    struct Elem {
        String  lKey;
        String  lVal;
        void*   Obj;
    };

private:
    std::vector<Elem> box;
    std::map<String, Elem*> index;
    void  reindex();

public:
    _Props(): box(), index() { }

    const Elem& get(int i) const { return  box[i]; }
    int count() const { return  box.size(); }
    void clear() {
        index.clear();
        box.clear();
    }

    void erase(const String& key);

    Elem* ElemOf(const String& key, bool create = false) {
        std::map<String, Elem*>::const_iterator f = index.find(key);
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
    String get(const String& stKey);
    String getOEM(const String& stKey);
    String getEx(const String& stKey, void ** ptr);
    void*   getPtr(const String& stKey);
    int geti(const String& stKey) {
        return StrToIntDef(get(stKey), 0);
    }

    void putEx(const String& stKey, String stVal, void * ptr);
    void putEx(const String& stKey, String stVal, void * ptr, String stValDef);
    void putOEM(const String& stKey, String stVal);

    void put(const String& stKey, String stVal) {
        putEx(stKey, stVal, 0);
    }
    void put(const String& stKey, String stVal, String stValDef)   {
        putEx(stKey, stVal, 0, stValDef);
    }
    void put(const String& stKey, int iVal)    {
        put(stKey, IntToStr(iVal));
    }
    void put(const String& stKey, int iVal, int iValDef) {
        put(stKey, IntToStr(iVal), IntToStr(iValDef));
    }

    void del(const String& stKey) {
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

    bool KeyExists(const String& stKey) {
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
    void clear() { _p.clear(); }

#ifndef QT_ANTLIB
    __property int ItemsCount  = { read = GetItemsCount };
    __property String Keys[ int i ]  = { read = GetKeys, write = SetKeys };
    __property String Val[ int i ]  = { read = GetVal, write = SetVal };
    __property String P[String stKey]  = { read = GetP, write = SetP };
#endif

private:
    int GetItemsCount() const { return _p.count(); }

    void SetKeys(int i, const String& value);
    String GetKeys(int i);

    void SetVal(int i, const String& value);
    String GetVal(int i);

    void SetP(const String& stKey, const String& value);
    String GetP(const String& stKey);
};






//---------------------------------------------------------------------------
#endif
