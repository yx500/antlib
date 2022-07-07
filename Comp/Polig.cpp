#include "Polig.h"

#include "APch.h"
#include "Stan.h"
#include "aheaders_cpp.h"

#include <map>
#include <math.h>

extern int MaxY, DELTA_X, DELTA_Y;
//---------------------------------

extern int DELTA_CHAN;
extern int CurrentUCH;

Poligon::Poligon()
{
  name="";
  FullFileName="";
  Col_ST = 0;
  ENG_Pack = NULL;
  CABufCount = 0;
  ST.resize(30, NULL);
  STB.resize(30, NULL);
}

int Poligon::Close()
{
  name="";
  FullFileName="";
  Col_ST = 0;
  for (int i = 0; i < 30; i++) {
    if (ST[i] == STB[i])
      STB[i] = NULL;

    if (ST[i])
      delete ST[i];
    if (STB[i])
      delete STB[i];
    ST[i] = STB[i] = NULL;
  }
  return 1;
}

int Poligon::LoadYCH(const char* filename)
{
  alib::CaseInsensitiveFilePath  filepath(filename);
  FullFileName = filepath.path();

  if (!LoadYchParams(ChangeFileExt(String(filename), ".ini"), &AO))
    AO = AntOpt0;
  name=AO.Name;

  std::ifstream file( FullFileName.c_str(), std::ios::binary);

  if (!file.is_open()) {
    String t = String("Can't open file: ") + filename;
    CriticalErr(t.c_str());
    return -1;
  }
  file.read( (char*)&Col_ST, sizeof(short int));
  for (CurrentStation = 0; CurrentStation < Col_ST; CurrentStation++) {
    if (ST[CurrentStation] == NULL) {
      ST[CurrentStation] = new Station("");
      ST[CurrentStation]->pPoligon = this;
      ST[CurrentStation]->AO = &AO;
    }

    file.read( (char*)ST[CurrentStation]->Dat, sizeof(St_Dat));
    //> !!!  ïðàâèòü îáÿçàòåëüíî êîãäà
    String fns = ExtractFileDir(filename)+"\\..\\sta\\"+ST[CurrentStation]->Dat->filename+".sta";
    ST[CurrentStation]->filename=fns;
    if (ST[CurrentStation]->Open(fns.c_str()) == -1) {
      return -1;
    }
    STB[CurrentStation] = new Station("");

    memcpy(STB[CurrentStation]->Dat, ST[CurrentStation]->Dat, sizeof(St_Dat));
    STB[CurrentStation]->Dat->filename[0] = '!';
    String fnm = STB[CurrentStation]->FullFN();
    if (!FileExists(fnm)) {
      delete STB[CurrentStation];
      STB[CurrentStation] = ST[CurrentStation];
    } else
      STB[CurrentStation]->Open(fnm.c_str());
  }
  
  CurrentStation = 0;
  return 1;
}

int Poligon::LoadYCE(const char* filename)
{
  alib::CaseInsensitiveFilePath  filepath(filename);
  FullFileName = filepath.path();

  AIniFile* FI = new AIniFile( FullFileName.c_str() );

  if (!AOReadFromIni(FI, "", &AO))
    AO = AntOpt0;

  name=AO.Name;

  String SectName, SS, oldcd;
  CurrentStation = Col_ST = 0;
  for (int i = 0; i < 256; ++i) {
    SectName = "STATION_" + IntToStr(i + 1);
    if (!FI->SectionExists(SectName))
      continue;
    Station* tmpStan = new Station("");
    tmpStan->pPoligon = this;
    tmpStan->AO = &AO;

    SS = FI->ReadString(SectName, "ñìfilename", tmpStan->Dat->filename);
    strncpy(tmpStan->Dat->filename, ChangeFileExt(SS, "").c_str(), sizeof(tmpStan->Dat->filename));
    String staFN = ExtractFileDir(filename) + "\\..\\" + Sta_Dir + "\\" + SS;
    SS = FI->ReadString(SectName, "ñìFullFileName", staFN);
    SS = staFN;
    tmpStan->filename= SS;

    if (tmpStan->Open(SS.c_str()) == -1) {
      if (MOD == ED)
        return -1;
      else
        continue;
    }

    tmpStan->Dat->Nom = FI->ReadInteger(SectName, "öôNom", tmpStan->Dat->Nom);

    SS = FI->ReadString(SectName, "ñìdescriptor", tmpStan->Dat->descriptor);
    strncpy(tmpStan->Dat->descriptor, SS.c_str(), sizeof(tmpStan->Dat->descriptor));
    tmpStan->Dat->MUL_X[0] = FI->ReadInteger(SectName, "öôMUL_X1", tmpStan->Dat->MUL_X[0]);
    tmpStan->Dat->MUL_X[1] = FI->ReadInteger(SectName, "öôMUL_X2", tmpStan->Dat->MUL_X[1]);
    tmpStan->Dat->MUL_Y[0] = FI->ReadInteger(SectName, "öôMUL_Y1", tmpStan->Dat->MUL_Y[0]);
    tmpStan->Dat->MUL_Y[1] = FI->ReadInteger(SectName, "öôMUL_Y2", tmpStan->Dat->MUL_Y[1]);
    tmpStan->Dat->X_begin[0] = FI->ReadInteger(SectName, "öôX_begin1", tmpStan->Dat->X_begin[0]);
    tmpStan->Dat->X_begin[1] = FI->ReadInteger(SectName, "öôX_begin2", tmpStan->Dat->X_begin[1]);
    tmpStan->Dat->Y_begin[0] = FI->ReadInteger(SectName, "öôY_begin1", tmpStan->Dat->Y_begin[0]);
    tmpStan->Dat->Y_begin[1] = FI->ReadInteger(SectName, "öôY_begin2", tmpStan->Dat->Y_begin[1]);

    CurrentStation = Col_ST++;
    ST[CurrentStation] = tmpStan;
    STB[CurrentStation] = tmpStan;
  }
  CurrentStation = 0;
  delete FI;
  return 1;
}

int Poligon::Open(const char* filename)
{
  FullFileName = filename;
  
  String FN = filename;
  if (FN.UpperCase().Pos(".YCE") == FN.Length() - 3) {
    return LoadYCE(FN.c_str());
  } else {
    return LoadYCH(FN.c_str());
  }
}

void Poligon::Show()
{
  int i = CurrentStation;
  for (CurrentStation = 0; CurrentStation < Col_ST; CurrentStation++) {
    if (CurrentStation == i)
      Current_Name = 1;
    else
      Current_Name = 0;
    if (ST[CurrentStation] != NULL) {
      if (CurrentPicture == BG)
        ST[CurrentStation]->Show();
      else
        STB[CurrentStation]->Show();
    }
  }
  CurrentStation = i;
}

int Poligon::TstXY(int x, int y)
{
  int i = CurrentStation;

  if ((CurrentPicture == BG) || ((x == -1) && (y == 14))) {
    for (CurrentStation = 0; CurrentStation < Col_ST; CurrentStation++) {
      if (ST[CurrentStation] != NULL) {
        // d = ST[CurrentStation]->TstXY(x,y);
      }
      //      if(d) return d;
    }
  } else {
    if (ST[CurrentStation] != NULL) {
      // d = ST[CurrentStation]->TstXY(x,y);
    }
    //    if(d) return d;
  }

  CurrentStation = i;
  return 0;
}

void Poligon::Go()
{
  int i = CurrentStation;
  //  setpalette(13,7);
  if (CurrentPicture == BG) {
    // for(int s=0;s<Col_ST;s++)
    //    if(ST[s]!=NULL)ST[s]->ShowTrainNumbers(true);

    for (CurrentStation = 0; CurrentStation < Col_ST; CurrentStation++) {
      if (CurrentStation == i)
        Current_Name = 1;
      else
        Current_Name = 0;
      if (ST[CurrentStation] != NULL)
        ST[CurrentStation]->Go();
    }
    // for(int s=0;s<Col_ST;s++)
    //    if(ST[s]!=NULL)ST[s]->ShowTrainNumbers(false);

    CurrentStation = i;
  } else {
    // if(ST[CurrentStation]!=NULL)STB[CurrentStation]->ShowTrainNumbers(true);
    if (ST[CurrentStation] != NULL)
      STB[CurrentStation]->Go();
    // if(ST[CurrentStation]!=NULL)STB[CurrentStation]->ShowTrainNumbers(false);
  }
}

void Poligon::ShowActives()
{
  for (int i = 0; i < Col_ST; i++)
    if (ST[i])
      ST[i]->ShowActives();
}

void Poligon::Clear()
{
  for (int i = 0; i < Col_ST; i++) {
    if (ST[i])
      ST[i]->Clear();
    if (STB[i])
      STB[i]->Clear();
  }
}

void Poligon::Save()
{
  String FN = FullFileName;
  if (FN.UpperCase().Pos(".YCE") == FN.Length() - 3) {
    return SaveYCE();
  } else {
    return SaveYCH();
  }
}

void Poligon::SaveYCH()
{
  std::ofstream file( FullFileName.c_str(), std::ios::binary);
  if (!file.is_open())
    CriticalErr("Íå ìîãó îòêðûòü ôàéë ó÷àñòêà");

  file.write( (char*)&Col_ST, sizeof(short int));
  for (int i = 0; i < Col_ST; i++) {
    ST[i]->Dat->Nom = i;
    file.write( (char*)ST[i]->Dat, sizeof(St_Dat));
    // if(mode==ALL)ST[i]->Save(mode);
  }
  
}

void Poligon::SaveYCE()
{
  AIniFile* FI = new AIniFile(FullFileName);
  St_Dat* Dat;

  for (int i = 0; i < Col_ST; i++) {
    String SectName = "STATION_" + IntToStr(i + 1);
    Dat = ST[i]->Dat;
    Dat->Nom = i;
    FI->WriteString(SectName, "ñìFullFileName", ST[i]->filename);

    FI->WriteString(SectName, "ñìfilename", ExtractFileName(ST[i]->filename));
    FI->WriteString(SectName, "ñìdescriptor", Dat->descriptor);
    FI->ReadInteger(SectName, "öôNom", Dat->Nom);
    FI->WriteInteger(SectName, "öôMUL_X1", Dat->MUL_X[0]);
    FI->WriteInteger(SectName, "öôMUL_X2", Dat->MUL_X[1]);
    FI->WriteInteger(SectName, "öôMUL_Y1", Dat->MUL_Y[0]);
    FI->WriteInteger(SectName, "öôMUL_Y2", Dat->MUL_Y[1]);
    FI->WriteInteger(SectName, "öôX_begin1", Dat->X_begin[0]);
    FI->WriteInteger(SectName, "öôX_begin2", Dat->X_begin[1]);
    FI->WriteInteger(SectName, "öôY_begin1", Dat->Y_begin[0]);
    FI->WriteInteger(SectName, "öôY_begin2", Dat->Y_begin[1]);
    // if(mode==ALL)ST[i]->Save(mode); ïóñêàé ñòàíöèè ïî îòäåëüîñòè ñîõðàíÿþòñÿ!
  }
  FI->UpdateFile();
  delete FI;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++
int Poligon::GetNumStanFor(int x, int y)
{
  static int ddd[256];
  for (int i = 0; i < 256; i++)
    ddd[i] = 2147483647;
  AComp* P = NULL;
  int sx, sy, mx, my;
  // char *name;
  for (int i = 0; i < Col_ST; i++) {
    sx = ST[i]->Dat->X_begin[BG];
    sy = ST[i]->Dat->Y_begin[BG];
    mx = ST[i]->Dat->MUL_X[BG];
    my = ST[i]->Dat->MUL_Y[BG];
    // name=ST[i]->Dat->filename;
    for (int j = 0; j < Units_Size; j++) {
      for (int k = 0; k < ST[i]->POLE[j]->GetArraySize(); k++) {
        P = ST[i]->POLE[j]->GetObjPtr(k);
        if (P != NULL) {
          if (P->GetType() == NAME) {
            int xx = P->X * mx + sx;
            int yy = P->Y * my + sy;
            ddd[i] = sqrt((xx - x) * (xx - x) + (yy - y) * (yy - y));
          }
          /*
                                  if  (P->GetType()==NAME){
                                          int xx=P->x*mx+sx;
                                          int yy=P->y*my+sy;
                                          rectangle(xx-60,yy-20+40,xx+60,yy+20+40);
                                  }
                                  if (
                                      (P->GetType()==NAME)&&
                                      (abs(P->x*mx+sx-x)<60) &&
                                      (abs(P->y*my+sy-y+40)<20)) return i;
          */
        }
      }
    }
  }

  int iii = -1;
  int _min = 2147483647;
  for (int i = 0; i < 256; i++)
    if (ddd[i] < _min) {
      _min = ddd[i];
      iii = i;
    }
  return iii;
}

void* Poligon::SetCommBuf(int8 A)
{

  try {
    if (ENG_Pack == NULL)
      return NULL;
    if (CABufCount++ > 490) {
      CriticalErr("SetCommBuf");
      return NULL;
    }

    ENG_Pack[CABufCount] = A;
    return &ENG_Pack[CABufCount];
  } catch (...) {
  }
  CriticalErr("SetCommBuf_catch");
  return NULL;
}

int Poligon::UpdateState()
{
  int res = 0;
  for (int i = 0; i < Col_ST; i++)
    res += ST[i]->UpdateState();
  return res;
}

void Poligon::for_each_chanel(TGetPacketOffset f)
{
  for (int i = 0; i < Col_ST; i++)
    ST[i]->for_each_chanel(f);
}
void Poligon::reassignChanelOffset()
{
  for (int i = 0; i < Col_ST; i++)
    ST[i]->reassignChanelOffset();
}
