

#include "uEXD.h"

#include "Gor_Logic.h"
#include "aheaders_cpp.h"
#include "tGorka.h"

typedef void* (*T_GetDatagramData_Func)(int typ, const char* PacketName);
extern T_GetDatagramData_Func GetDatagramData_Func;

TEXD EXD;

__fastcall TEXD::TEXD()
{
  Enabled = true;
  TN_Ver = 1;
}

__fastcall TEXD::~TEXD()
{
}

bool __fastcall TEXD::InitDll()
{
  Enabled = true;
  if (TN_Ver <= 0)
    Enabled = false;
  return Enabled;
}

void __fastcall TEXD::TN_SetVer(int AVer)
{
  TN_Ver = AVer;
  InitDll();
}

static int DoublTN[1024];
static int DoublTNCnt = 0;
bool __fastcall FindInDoublTNFilter(int imp)
{
  for (int i = 0; i < DoublTNCnt; i++)
    if (DoublTN[i] == imp)
      return true;
  return false;
}
void __fastcall AddInDoublTNFilter(int imp)
{
  DoublTN[DoublTNCnt] = imp;
  DoublTNCnt++;
  if (DoublTNCnt == 1024)
    DoublTNCnt = 0;
}

static TTrainInfo _TRINF;
TTrainInfo* __fastcall MakeTrainInfo(void* TNdata, int Ver)
{
  try {
    memset(&_TRINF, 0, sizeof(_TRINF));

    if ((Ver == 1) || (Ver == 2)) {
      TKroshTrainInfo* KTI;
      KTI = (TKroshTrainInfo*)TNdata;
      memcpy(&_TRINF, &KTI->TrainInfo, sizeof(_TRINF));
      return &_TRINF;
    }

    if (Ver == 3) {
      t_NewDescr* DD;
      DD = (t_NewDescr*)TNdata;

      _TRINF.TrainNumber = DD->D.num;
      _TRINF.TrainWeight = DD->D.ves;
      _TRINF.TrainColor = 15;

      if (DD->E.sz_struct > 0 /*sizeof(DD->E)*/) {
        _TRINF.Reserv2[0] = DD->E.STATE_D_ORDER_RC;
        if (DD->E.STATE_EXTNUM != 0)
          _TRINF.TrainNumber = DD->E.STATE_EXTNUM;
        if (DD->E.STATE_GAC_ACTIVE == 0)
          _TRINF.TrainColor = 7;
      }
      if (DD->D.err)
        _TRINF.TrainColor = 246;
      return &_TRINF;
    }

  } catch (...) {
  }
  return NULL;
}

TTrainInfo* __fastcall TEXD::TN_GetTN(int imp, const char* StanFN, const char* ChanelName, bool bUseDoublFilter)
{
  if (!Enabled)
    return NULL;
  if (GetDatagramData_Func == NULL)
    return NULL;
  try {
    imp = abs(imp);
    if (imp < 1000)
      return NULL;
    TKrPack* KrPack;
    TKroshTrainInfo* KTI;
    if (bUseDoublFilter) {
      /* Проверяем на повтоные номера */
      if (FindInDoublTNFilter(imp))
        return NULL;
    }
    int IMP = imp % 1000;

    if (TN_Ver == 1) {
      /*имя пакета = имя канала*/
      // if (strcmp(TNPackets[i]->Dtgrm.Name,ChanelName)!=0) continue;
      KrPack = (TKrPack*)GetDatagramData_Func(11, ChanelName);
      if (KrPack == NULL)
        return NULL;
      for (int j = 0; j < KrPackCnt; j++) {
        KTI = &KrPack->KTI[j];
        if (KTI->offsetimp == 0)
          break;
        if ((KTI->offsetimp % 1000 != IMP) /*||
                  (strcmp(KTI->channame,ChanelName)!=0)*/
        )
          continue;

        if (bUseDoublFilter)
          AddInDoublTNFilter(imp);
        return MakeTrainInfo(KTI, 1);
      }
    }

    if (TN_Ver == 2) {
      /* не использовать!
      for (int i=0;i<ChanelsCount;i++){
          if (TNPackets[i]==NULL) continue;
          KrPack=(TKrPack *)TNPackets[i]->Dtgrm.Data;
          for (int j=0;j<KrPackCnt;j++){
              KTI=&KrPack->KTI[j];
              if (KTI->offsetimp==0) break;
              if ((KTI->offsetimp%1000!=IMP)||
                   (strcmp(KTI->channame,ChanelName)!=0))continue;

              if (bUseDoublFilter)AddInDoublTNFilter(imp);
              return MakeTrainInfo(TNPackets[i],j,2);
          }
      }  */
      return NULL;
    }
    if (TN_Ver == 3) {
      t_Descr* DD;
      DD = GetDescr_imp1(imp, // Местоположение Головы отцепа |    N Эл РЦ в ТС     |
                         0,   // start=0/end=1
                         false);
      if ((DD != NULL) && (DD->end_slg == 0)) {
        // if (bUseDoublFilter)AddInDoublTNFilter(imp);
        return MakeTrainInfo(DD, 3);
      }
    }

  } catch (...) {
  }

  return NULL;
}
int __fastcall TEXD::TN_SetInputBuf(void* buf, int maxchanels)
{
  return 0;
}
bool __fastcall TEXD::TN_SetInputBufChanelN(void* buf, int ChanelNumber)
{
  return false;
}

void __fastcall TEXD::TN_PrepareDoublTNFilter()
{
  DoublTNCnt = 0;
}
/*int __fastcall TEXD::TN_GetTrainsCount(void)
{
     try {
         if ((Enabled)&&(dll_TN_GetTrainsCount)) return dll_TN_GetTrainsCount();
     }catch(...){}
     return 0;
}


TKroshTrainInfo * __fastcall TEXD::TN_GetTrainsInfo(size_t ind)
{
     try {
         if ((Enabled)&&(dll_TN_GetTrainsInfo)) return (TKroshTrainInfo *)dll_TN_GetTrainsInfo(ind);
     }catch(...){}
     return NULL;
}
*/

int __fastcall TEXD::MK_SetInputBuf(void* buf, int maxchanels)
{
  return 0;
}
bool __fastcall TEXD::MK_SetInputBufChanel(void* buf, int ChanelNumber)
{
  return false;
}

TMKMarshAll* __fastcall TEXD::MK_GetStan(const char* StanFN)
{
  if (GetDatagramData_Func == NULL)
    return NULL;
  TMKMarshAll* MKMarshAll = (TMKMarshAll*)GetDatagramData_Func(25, StanFN);
  return MKMarshAll;
}

int __fastcall TEXD::SI_SetInputBuf(void* buf, int maxchanels)
{
  return 0;
}
bool __fastcall TEXD::SI_SetInputBufChanel(void* buf, int ChanelNumber)
{
  return false;
}

TAVStanInfo* __fastcall TEXD::SI_GetStan(const char* StanFN)
{
  if (GetDatagramData_Func == NULL)
    return NULL;
  TAVStanInfo* AVStanInfo = (TAVStanInfo*)GetDatagramData_Func(27, StanFN);
  return AVStanInfo;
}

int __fastcall TEXD::EI_SetInputBuf(void* buf, int maxchanels)
{
  return 0;
}
bool __fastcall TEXD::EI_SetInputBufChanel(void* buf, int ChanelNumber)
{
  return false;
}

TElemCheckState* __fastcall TEXD::EI_GetEI(const char* StanFN, int obj_id)
{
  if (GetDatagramData_Func == NULL)
    return NULL;
  String stStanFN = String(StanFN);
  String ST;
  stStanFN = stStanFN.UpperCase() + "_";
  TEIPack* EIPack;
  try {
    for (int i = 0; i < 10; i++) {
      ST = stStanFN + IntToStr(i);
      /*имя пакета = имя станции + _0*/
      EIPack = (TEIPack*)GetDatagramData_Func(31, ST.c_str());
      if (EIPack == NULL)
        break;

      for (int j = 0; j < ElemStatePackCnt; j++) {
        //  не ищем в нолях
        if (EIPack->ES[j].id_obj == 0)
          break;
        if (EIPack->ES[j].id_obj == obj_id) {
          return &EIPack->ES[j];
        }
      }
    }
  } catch (...) {
  }
  return NULL;
}

TElemCheckState* __fastcall TEXD::EI_GetEINext(const char* StanFN, int obj_id, TElemCheckState* EI0)
{
  if (GetDatagramData_Func == NULL)
    return NULL;
  String stStanFN = String(StanFN);
  String ST;
  stStanFN = stStanFN.UpperCase() + "_";
  TEIPack* EIPack;
  bool beginfind = false;
  try {
    for (int i = 0; i < 10; i++) {
      ST = stStanFN + IntToStr(i);
      /*имя пакета = имя станции + _0*/
      EIPack = (TEIPack*)GetDatagramData_Func(31, ST.c_str());
      if (EIPack == NULL)
        break;

      for (int j = 0; j < ElemStatePackCnt; j++) {
        //  не ищем в нолях
        if (EIPack->ES[j].id_obj == 0)
          break;

        if ((EIPack->ES[j].id_obj == EI0->id_obj) &&
            (EIPack->ES[j].id_check == EI0->id_check) &&
            (EIPack->ES[j].state == EI0->state)) {
          beginfind = true;
          continue;
        }
        if (beginfind) {
          if (EIPack->ES[j].id_obj == obj_id) {
            return &EIPack->ES[j];
          }
        }
      }
    }
  } catch (...) {
  }
  return NULL;
}
