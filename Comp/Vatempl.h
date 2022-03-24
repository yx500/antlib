//---------------------------------------------------------------------------
#ifndef VatemplxH
#define VatemplxH
//---------------------------------------------------------------------------
#ifndef QT_ANTLIB
#include <Classes.hpp>
#else
#include <vcl.h>
#endif
#include <stdio.h>
#include <vector>

#include "Comp.h"



const int AllocError = -1;
const int Ok = 0;



class Station;
class  _ALIB_ VisibleArray
{

public:
    typedef std::vector<PAComp> TvObjPtr;
    TvObjPtr vObjPtr;

    Station * pStation;
    int RTGorlCnt;

    VisibleArray(int ArraySize, Station * pAStation);
    _fastcall ~VisibleArray();

    PAComp New(TYP type);
    int  Add(PAComp ptr);
    int  Insert(PAComp ptr, int p);
    int  Remove(int p);
    void RemoveAll();
    void Show(PAComp ac);
    PAComp GetObjPtr(int p);
    PAComp SetObjPtr(int p, PAComp ac);
    void Move(PAComp ac, int DeltaX, int DeltaY);
    void ShowAll();
    void ShowLayer(int Layer);
    void GoAll();
    void HideAll();
    void ConnectAll();
    void MoveAll(int DeltaX, int DeltaY);
    int  GetArraySize();
    int  LoadAll(int NALL, FILE *file, int ut);
    int  SaveAll(FILE *file, int ut);
    int  TstXY(int x, int y); //!!!
    void ClearAll(void);
    int IndexOf(PAComp ac);

};


typedef VisibleArray* PVisibleArray;

typedef void *(*TSetCommBufFunc)(__int8);
void _ALIB_ SetSetCommBufFunc(TSetCommBufFunc ASetCommBuf);

typedef void(*TEachAComp)(PAComp);
extern TEachAComp _ALIB_ EachACompPreFun;
extern TEachAComp _ALIB_ EachACompPostFun;
extern TEachAComp _ALIB_ EachACompStanPreFun;
extern TEachAComp _ALIB_ EachACompStanPostFun;
extern TEachAComp _ALIB_ MakeNewComp;



extern FILE*      _ALIB_ CurStanFile;



#endif
