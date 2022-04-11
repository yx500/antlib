#include "Elem.h"

#include "APch.h"
#include "Impuls.h"
#include "Stan.h"
#include "aheaders_cpp.h"
#include "out_num.h"
#include "propmap.h"

void Element::Set()
{
  AComp::Set();

  impuls_plus = MEM.impuls_plus;
  impuls_mnus = MEM.impuls_mnus;
  impuls_kzm = MEM.impuls_kzm;
  impuls_kmu = MEM.impuls_kmu;
  impuls_mu = MEM.impuls_mu;
  memset(name, 0, sizeof(name));
  cp866_to_cp1251_buff(MEM.name, name, 7);

  // memcpy(name,MEM.name,7);
  name[7] = 0;

  if (MEM.type == PLOT)
    pr = MEM.masx2;

  memcpy(RezBuf, MEM.name + 8, 4);
  memcpy(&ID, MEM.name + 12, 2);
  memcpy(RezBuf1, MEM.name + 14, 2);
};

void Element::Get()
{
  AComp::Get();
  MEM.impuls_plus = impuls_plus;
  MEM.impuls_mnus = impuls_mnus;
  MEM.impuls_kzm = impuls_kzm;
  MEM.impuls_kmu = impuls_kmu;
  MEM.impuls_mu = impuls_mu;
  MEM.Nomer = 0;
  memset(MEM.name, 0, sizeof(MEM.name));
  cp1251_to_cp866_buff(name, MEM.name, 7);
  // strncpy(MEM.name,oemname,7);
  MEM.name[7] = 0;

  memcpy(MEM.name + 8, RezBuf, 4);
  memcpy(MEM.name + 12, &ID, 2);
  memcpy(MEM.name + 14, RezBuf1, 2);

  if (MEM.type == PLOT)
    MEM.masx2 = pr;
};

static char _ElementPropName[6][20] = {
    "òñimpuls_plus",  // 0
    "òñimpuls_minus", // 1
    "òñimpuls_kzm",   // 2
    "òñimpuls_kmu",   // 3
    "òñimpuls_mu",    // 4
    "ñìÈÌß"           // 5
};

void Element::SetPropMap(TPropMap& m)
{
  AComp::SetPropMap(m);

  impuls_plus = NewStrToOldImp(m.get(_ElementPropName[0]).c_str());
  impuls_mnus = NewStrToOldImp(m.get(_ElementPropName[1]).c_str());
  impuls_kzm = NewStrToOldImp(m.get(_ElementPropName[2]).c_str());
  impuls_kmu = NewStrToOldImp(m.get(_ElementPropName[3]).c_str());
  impuls_mu = NewStrToOldImp(m.get(_ElementPropName[4]).c_str());

  memset(name, 0, sizeof(name));
  strncpy(name, m.get(_ElementPropName[5]).c_str(), sizeof(name));
}

void Element::GetPropMap(TPropMap& m)
{
  AComp::GetPropMap(m);

  m.putEx(_ElementPropName[0], OldImpToNewStr(impuls_plus, this), GetRealImp(impuls_plus), OldImpToNewStr(0, this));
  m.putEx(_ElementPropName[1], OldImpToNewStr(impuls_mnus, this), GetRealImp(impuls_mnus), OldImpToNewStr(0, this));
  m.putEx(_ElementPropName[2], OldImpToNewStr(impuls_kzm, this), GetRealImp(impuls_kzm), OldImpToNewStr(0, this));
  m.putEx(_ElementPropName[3], OldImpToNewStr(impuls_kmu, this), GetRealImp(impuls_kmu), OldImpToNewStr(0, this));
  m.putEx(_ElementPropName[4], OldImpToNewStr(impuls_mu, this), GetRealImp(impuls_mu), OldImpToNewStr(0, this));
  m.put(_ElementPropName[5], name);
}

void Element::Go()
{

  bool b = StateChanged;
  UpdateState();
  if (b || StateChanged)
    Show();
  StateChanged = false;
}

void Element::UpdateState()
{
  int rimpuls_busi = f(impuls_busi);
  int rimpuls_plus = f(impuls_plus);
  int rimpuls_mnus = f(impuls_mnus);
  int rimpuls_kzm = f(impuls_kzm);
  int rimpuls_kmu = f(impuls_kmu);
  int rimpuls_mu = f(impuls_mu);
  StateChanged = (rimpuls_busi != fimpuls_busi) |
                 (rimpuls_plus != fimpuls_plus) |
                 (rimpuls_mnus != fimpuls_mnus) |
                 (rimpuls_kzm != fimpuls_kzm) |
                 (rimpuls_kmu != fimpuls_kmu) |
                 (rimpuls_mu != fimpuls_mu);
  fimpuls_busi = rimpuls_busi;
  fimpuls_plus = rimpuls_plus;
  fimpuls_mnus = rimpuls_mnus;
  fimpuls_kzm = rimpuls_kzm;
  fimpuls_kmu = rimpuls_kmu;
  fimpuls_mu = rimpuls_mu;
}

void Gorl_L::Show()
{
}
TYP Gorl_L::GetType()
{
  return GORL_L;
};
UNIT Gorl_L::GetUnit()
{
  return WAYS;
};

void Gorl_R::Show()
{
}
TYP Gorl_R::GetType()
{
  return GORL_R;
};
UNIT Gorl_R::GetUnit()
{
  return WAYS;
};

Element::Element()
    : AComp()
{
  impuls_plus = 0;
  impuls_mnus = 0;
  impuls_kzm = 0;
  impuls_kmu = 0;
  impuls_mu = 0;
  memset(name, 0, sizeof(name));
  ID = 0;
  memset(RezBuf, 0, sizeof(RezBuf));
  memset(RezBuf1, 0, sizeof(RezBuf1));
  clr = FON;

  fimpuls_plus = 0;
  fimpuls_mnus = 0;
  fimpuls_kzm = 0;
  fimpuls_kmu = 0;
  fimpuls_mu = 0;
}

Ways::Ways()
    : Element()
{
  memset(IDnext, 0, sizeof(IDnext));
  memset(&TrainInfo, 0, sizeof(TrainInfo));
  impuls_svob = fimpuls_svob = 0;
  impuls_IR = 0;
  fimpuls_IR = 0;
  impuls_predSEIR = 0;
  fimpuls_predSEIR = 0;
  bShowUIR = false;
}

void Ways::UpdateState()
{
  Element::UpdateState();

  int rimpuls_svob = f(impuls_svob);
  int rimpuls_IR = f(impuls_IR);
  int rimpuls_predSEIR = f(impuls_predSEIR);

  StateChanged = StateChanged | (rimpuls_svob != fimpuls_svob) | (rimpuls_IR != fimpuls_IR) | (rimpuls_predSEIR != fimpuls_predSEIR);
  fimpuls_svob = rimpuls_svob;
  fimpuls_IR = rimpuls_IR;
  fimpuls_predSEIR = rimpuls_predSEIR;

  EXD_UpdateTrainNumber(this, fimpuls_busi);
  // if (TrainInfo.TrainNumber != 0) StateChanged = true;
}

void Ways::Set()
{
  Element::Set();
  memcpy(IDnext, &MEM.DMD[0], sizeof(IDnext));
}

void Ways::Get()
{
  Element::Get();
  memcpy(&MEM.DMD[0], IDnext, sizeof(IDnext));
}

void Ways::GetPropMap(TPropMap& m)
{
  Element::GetPropMap(m);
  m.putEx("òñimpuls_svob", OldImpToNewStr(impuls_svob, this), GetRealImp(impuls_svob), OldImpToNewStr(0, this));
  m.putEx("òñimpuls_IR", OldImpToNewStr(impuls_IR, this), GetRealImp(impuls_IR), OldImpToNewStr(0, this));
  m.putEx("òñimpuls_predSEIR", OldImpToNewStr(impuls_predSEIR, this), GetRealImp(impuls_predSEIR), OldImpToNewStr(0, this));
  String ss;
  for (int d = 0; d < 2; d++) {
    for (int i = 0; i < 2; i++) {
      ss = "îáIDnext" + IntToStr(d) + IntToStr(i);
      m.put(ss, IDnext[d][i], 0);
    }
  }
}
void Ways::SetPropMap(TPropMap& m)
{
  Element::SetPropMap(m);
  impuls_svob = NewStrToOldImp(m.get("òñimpuls_svob").c_str());
  impuls_IR = NewStrToOldImp(m.get("òñimpuls_IR").c_str());
  impuls_predSEIR = NewStrToOldImp(m.get("òñimpuls_predSEIR").c_str());
  String ss;
  for (int d = 0; d < 2; d++) {
    for (int i = 0; i < 2; i++) {
      ss = "îáIDnext" + IntToStr(d) + IntToStr(i);
      IDnext[d][i] = m.geti(ss);
      pNext[d][i] = Stan()->GetObjByID(IDnext[d][i]);
    }
  }
}

static String _SS_GetCompInfo;
extern T_GetSigName_Func _GetSigName_Func;
/*
char * Ways::GetCompInfo()
{
    _SS_GetCompInfo = "";
    //name;ObjID;packet_name;busy;busyN;plus;;minus;;kzm
    String packet_name = "";
    String ss;
    String impname;

    char* CnlName;
    int RealOffset;
    impname = "";
    GetImpulsInfo(impuls_busi, CnlName, RealOffset);
    ss = String(CnlName);
    if ((ss != "NONE") && (ss != "")) packet_name = ss;
    if (_GetSigName_Func != NULL) impname = _GetSigName_Func(RealOffset);
    _SS_GetCompInfo = String(GetName()) + ";" +
                      IntToStr(GetID()) + ";" +
                      packet_name + ";" +
                      IntToStr(impuls_busi) + ";" + impname;

    impname = ""; GetImpulsInfo(impuls_plus, CnlName, RealOffset); ss = String(CnlName);
    if ((ss != "NONE") && (ss != "")) packet_name = ss;
    if (_GetSigName_Func != NULL) impname = _GetSigName_Func(RealOffset);
    _SS_GetCompInfo = _SS_GetCompInfo + ";" + IntToStr(impuls_plus) + ";" + impname;

    impname = ""; GetImpulsInfo(impuls_mnus, CnlName, RealOffset); ss = String(CnlName);
    if ((ss != "NONE") && (ss != "")) packet_name = ss;
    if (_GetSigName_Func != NULL) impname = _GetSigName_Func(RealOffset);
    _SS_GetCompInfo = _SS_GetCompInfo + ";" + IntToStr(impuls_mnus) + ";" + impname;

    impname = ""; GetImpulsInfo(impuls_kzm, CnlName, RealOffset); ss = String(CnlName);
    if ((ss != "NONE") && (ss != "")) packet_name = ss;
    if (_GetSigName_Func != NULL) impname = _GetSigName_Func(RealOffset);
    _SS_GetCompInfo = _SS_GetCompInfo + ";" + IntToStr(impuls_kzm) + ";" + impname;

    return _SS_GetCompInfo.c_str();
}
*/
void Ways::ShowTrainNumber()
{
  EXD_ShowTrainNumber(this, fimpuls_busi);
};
void Ways::HideTrainNumber()
{
  EXD_HideTrainNumber(this);
};

void Ways::SetUstIR(int AIR)
{
  // óñòàíàâëèâåò ìèãàíèå êîíòóðà ñòðåëêè
  // åñëè Pol !=1,2,3 ñòèðàåò
  switch (AIR) {
  case 1:
    bShowUIR = true;
    break; // SetStrelShowParams(-1,-1,-1,-1,SV_MIG,SV_MIG); break;
  default:
    bShowUIR = false;
    break; // SetStrelShowParams(-1,-1,-1,-1,-1,-1); break;
  }
}

bool Ways::isBusy()
{
  UpdateState();
  if (clr == COLOR_B)
    return true;
  return false;
}

bool Ways::isKzm()
{
  if (f(impuls_kzm) == 1)
    return true;
  return false;
}
bool Ways::isBusyKzmAccepted()
{
  if ((impuls_busi != 0) /*&&(impuls_kzm!=0)*/)
    return true;
  return false;
}
