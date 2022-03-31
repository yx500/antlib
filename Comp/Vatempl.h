//---------------------------------------------------------------------------
#ifndef VatemplxH
#define VatemplxH
//---------------------------------------------------------------------------
#ifndef QT_ANTLIB
#include <Classes.hpp>
#else
#include "aheaders_h.h"
#endif
#include <stdio.h>
#include <vector>

#include "Comp.h"



const int AllocError = -1;
const int Ok = 0;



class Station;
class  VisibleArray
{

public:
    typedef std::vector<PAComp> TvObjPtr;
    TvObjPtr vObjPtr;

    Station * pStation;
    int RTGorlCnt;

    VisibleArray(int ArraySize, Station * pAStation);
    ~VisibleArray();

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

typedef void *(*TSetCommBufFunc)(int8);
void SetSetCommBufFunc(TSetCommBufFunc ASetCommBuf);

typedef void(*TEachAComp)(PAComp);
extern TEachAComp EachACompPreFun;
extern TEachAComp EachACompPostFun;
extern TEachAComp EachACompStanPreFun;
extern TEachAComp EachACompStanPostFun;
extern TEachAComp MakeNewComp;



extern FILE*      CurStanFile;



#endif
