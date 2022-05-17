#ifndef POLIGON_H
#define POLIGON_H

#include "ACom_V.h"
#include "Stan.h"
#include "YchParams.h"

class Poligon
{
public:
  String FullFileName;
  String name;
  int Col_ST;
  Station* ST[30];
  Station* STB[30];

  TAntOpt AO;
  void SetSelfAntOpt();

  int8* ENG_Pack;
  int CABufCount;

  Poligon();
  ~Poligon() { Close(); }

  int Open(const char* fn);
  int LoadYCH(const char* filename);
  int LoadYCE(const char* filename);
  int Close();

  String Name() { return name; }
  const char* FileName() { return FullFileName.c_str(); }

  int Count() { return Col_ST; }
  Station* Item(int i) { return STB[i]; }

  void Save();
  void SaveYCH();
  void SaveYCE();
  void Go();
  void ShowActives();
  void Clear();
  void Show();
  void Del(int Nomer);
  int TstXY(int, int);
  int GetNumStanFor(int x, int y);

  void* SetCommBuf(int8 A);
  int UpdateState();
  void for_each_chanel(TGetPacketOffset f);
  void reassignChanelOffset();
};


#endif
