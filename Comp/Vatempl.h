#ifndef Vatempl_H
#define Vatempl_H

#include "Comp.h"
#include "aheaders_h.h"

#include <stdio.h>
#include <vector>

class Station;
class VisibleArray
{

public:
  typedef std::vector<AComp*> data_type;
  data_type data;

  Station* pStation;
  int RTGorlCnt;

  VisibleArray(int ArraySize, Station* pAStation);
  ~VisibleArray();

  AComp* New(TYP type);
  int Add(AComp* ptr);
  int Insert(AComp* ptr, int p);
  int Remove(int p);
  void RemoveAll();
  void Show(AComp* ac);
  AComp* GetObjPtr(int p);
  AComp* SetObjPtr(int p, AComp* ac);
  void ShowAll();
  void ShowLayer(int Layer);
  void GoAll();
  void ConnectAll();
  int GetArraySize();
  int LoadAll(int NALL, std::istream& file, int ut);
  int SaveAll(std::ostream& file, int ut);
  int TstXY(int x, int y); //!!!
  void ClearAll(void);
  int IndexOf(AComp* ac);
};

typedef void* (*TSetCommBufFunc)(int8);
void SetSetCommBufFunc(TSetCommBufFunc ASetCommBuf);

typedef void (*TEachAComp)(AComp*);
extern TEachAComp EachACompPreFun;
extern TEachAComp EachACompPostFun;
extern TEachAComp EachACompStanPreFun;
extern TEachAComp EachACompStanPostFun;
extern TEachAComp MakeNewComp;

#endif
