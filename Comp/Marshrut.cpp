//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Marshrut.h"
#include "uParString.h"
#include "f.h"
#include "Strel.h"
#include "Stan.h"
#include "elem.h"
#include "col.h"
#include "common.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
extern bool ShowUstMarshOnly_1;
const String chNO_CHECK_IS = "#";
TStrInMarsh::TStrInMarsh()
{
    memset(STRELNAME, 0, sizeof(STRELNAME));
    IS = 0;
    DOCHEK = cNORMAL;
    ORDER = NOORDER;
    pStrel = NULL;
    realIS = 0;
    realBUSY = 0;
    realKZM = 0;
    //PacketName = "";
    //memset(imp, 0, sizeof(imp));
    //ObjID = 0;
}

void TStrInMarsh::UpdateState() // ������������� ������� ��������
{
    realIS = 3;
    realBUSY = 0;
    realKZM = 0;

    if (pStrel == NULL) return;
    pStrel->UpdateState();
    //������ �������
    Strel0 * S = dynamic_cast<Strel0 *>(pStrel);
    if (S != NULL) {
        // � ������ �������� ��������� ��������� ��� ����������
        // ���������� ��������� ���
        //if(S->nomer<0){
        /* TODO -c TMarshrut :
        ������ �� �������� ������� ����������� �������
        � ��������� ����������� */
        realIS = S->is;

        /* ����� �������
        if(S->InvertStrel){
                    if(realIS==1) realIS = 2;
                    else    if(realIS==2) realIS = 1;
        }*/

        //realIS=S->fimpuls_plus*2+S->fimpuls_minus;
        realBUSY = S->fimpuls_busi;
        if (S->impuls_busi == 0)realBUSY = 3;
        realKZM = S->fimpuls_kzm;
        if (S->impuls_kzm == 0)realKZM = 3;
        //�������
        if (S->fimpuls_kmu || S->fimpuls_mu) {
            realBUSY = 0;
            realKZM = 0;
        }
        //}
    }

}
/*extern T_f_Func _f_;
void        TStrInMarsh::UpdateState2()
{
    realIS = 3;
    realBUSY = 0;
    realKZM = 0;

    int fimpuls_busi = _f_(imp[0], NULL);
    int fimpuls_plus = _f_(imp[1], NULL);
    int fimpuls_mnus = _f_(imp[2], NULL);
    int fimpuls_kzm = _f_(imp[3], NULL);

    if ((imp[1] == 0) && (imp[2] == 0)) {
        realIS = 0;
    } else {
        if ((fimpuls_plus == 1) && (fimpuls_mnus == 0)) realIS = P;
        if ((fimpuls_plus == 0) && (fimpuls_mnus == 1)) realIS = M;
    }

    //realIS=S->fimpuls_plus*2+S->fimpuls_minus;
    realBUSY = fimpuls_busi;
    if (imp[0] == 0) realBUSY = 3;
    realKZM = fimpuls_kzm;
    if (imp[3] == 0)realKZM = 3;
}
*/

void TStrInMarsh::FromString(String stSrc)
{
    DOCHEK = cNORMAL;
    if (stSrc.Pos("(-)") > 0) {
        IS = M; DOCHEK = cNO_CHECK_BUSY;
    } else if (stSrc.Pos("(+)") > 0) {
        IS = P; DOCHEK = cNO_CHECK_BUSY;
    } else if (stSrc.Pos("-") > 0)  {
        IS = M;
    } else if (stSrc.Pos("+") > 0)  {
        IS = P;
    } else
        IS = 3;
    if (stSrc.Pos(chNO_CHECK_IS) > 0)  {
        DOCHEK = cNO_CHECK_IS;
    }


}
String  TStrInMarsh::ToString()
{
    String RES = "";
    switch (IS) {
    case W: break;
    case P: RES="+"; break;
    case M: RES="-"; break;
    };
    if (DOCHEK == cNO_CHECK_BUSY) RES = "(" + RES + ")";
    if (DOCHEK == cNO_CHECK_IS)   RES = RES + chNO_CHECK_IS;

    return RES;
}


// =====================================================================


TMarshrut::TMarshrut() 
        /*apilotState(mk_state_Busy),
        oldapilotState(mk_state_Busy),
        apilotStateEx(mk_state_ex_Nothing),
        apilotEsr(0),
        apilotId_mar(0)*/
{
    FStrels = new TList();
    FStrels->Capacity = 5;
    pSV = NULL;
    pSV2 = NULL;
    pS_PRED = NULL;
    pS_PAST = NULL;
    realbusySV = 0;
    realbusyS_PRED = 0;
    realbusyS_PAST = 0;
    realkzmS_PRED = 0;
    realkzmS_PAST = 0;
    //PacketName = "";
    //memset(imp, 0, sizeof(imp));
    //memset(ObjID, 0, sizeof(ObjID));
    MarshList = NULL;

    memset(&TUCmd, 0, sizeof(TUCmd));
    TUPacketName = "";

    //for (int d = 0; d < 2; d++) {
    //    imp_per_napr[d] = 0; imp_per_busy[d] = 0;
    //}
    //YZ_PRED = NULL;  // ��������� �� ���� � �����
    //YZ_PAST = NULL;
    //YZ_TNZ = NULL;
    //YZ_TNO = NULL;
    bErrorData=false;

}

void TMarshrut::Clear()
{
    for (int i = 0; i < FStrels->Count; i++) delete((TStrInMarsh *)FStrels->Items[i]);
    FStrels->Clear();
}

TMarshrut::~TMarshrut()
{
    Clear();
    delete FStrels;
}

void __fastcall TMarshrut::SetSTRELS(int Index, TStrInMarsh * value)
{
    memcpy(FStrels->Items[Index], value, sizeof(TStrInMarsh));
}
TStrInMarsh * __fastcall TMarshrut::GetSTRELS(int Index)
{
    return (TStrInMarsh *) FStrels->Items[Index];
}

int __fastcall TMarshrut::GetSTRELSCOUNT()
{
    return FStrels->Count;
}


TStrInMarsh * TMarshrut::GetStrelByName(String StrelName)
{
    //TStrInMarsh * sim;
    for (int i = 0; i < FStrels->Count; i++)
        if (String(((TStrInMarsh *)FStrels->Items[i])->STRELNAME) == StrelName)
            return (TStrInMarsh *)FStrels->Items[i];
    return NULL;
}

const indNUMCOM = 0;
const indGROUP  = 1;
const indNAME   = 2;
const indGORL   = 3;
const indSV     = 4;
const indSV2    = 5;
const indS_PRED = 6;
const indS_PAST = 7;
const indORDER  = 8;

int PropStrBegin = 9;

String MarshrutPropName[MarshrutPropNameCount] = {
    "NUMCOM",          // 0
    "GROUP",           // 1
    "NAME",            // 2
    "GORL",            // 3
    "SV",              // 4
    "SV2",             // 5
    "S_PRED",          // 6
    "S_PAST",          // 7
    "ORDER"            // 8
};
bool IsPropNameStrel(String S)
{
    for (int i = 0; i < MarshrutPropNameCount; i++)
        if (S == MarshrutPropName[i]) return false;
    return true;
}

void TMarshrut::SetPropMap(TPropMap &m)
{
    Clear();                            // �� ������ �� ������
    TStrInMarsh * sim;
    int cnt = m.ItemsCount;
    String V, K;
    for (int i = 0; i < cnt; i++) {
        K = m.Keys[i];
        V = m.Val[i];

        if (K == MarshrutPropName[indNUMCOM]) NUMCOM = V.ToIntDef(0);else
        if (K == MarshrutPropName[indGROUP ]) GROUP = V.ToIntDef(0); else
        if (K == MarshrutPropName[indNAME  ]) NAME = V;              else
        if (K == MarshrutPropName[indGORL  ]) GORL = V;              else
        if (K == MarshrutPropName[indSV    ]) SV = V;                else
        if (K == MarshrutPropName[indSV2   ]) SV2 = V;               else
        if (K == MarshrutPropName[indS_PRED]) S_PRED = V;            else
        if (K == MarshrutPropName[indS_PAST]) S_PAST = V;            else
        if (K == MarshrutPropName[indORDER ]) ORDER  = V;            else {
            // ������� ��� ��������� ��� �������
            if ((V != "") && (K != "")) {
                sim = new TStrInMarsh();
                sim->FromString(V);
                strncpy(sim->STRELNAME, K.c_str(),sizeof(sim->STRELNAME)-1);
                FStrels->Add(sim);
            }
        };
    }
}
void TMarshrut::GetPropMap(TPropMap &m)
{
    m.put(MarshrutPropName[ indNUMCOM], NUMCOM);
    m.put(MarshrutPropName[ indGROUP ], GROUP);
    m.put(MarshrutPropName[ indNAME  ], NAME);
    m.put(MarshrutPropName[ indGORL  ], GORL);
    m.put(MarshrutPropName[ indSV    ], SV);
    m.put(MarshrutPropName[ indSV2   ], SV2);
    m.put(MarshrutPropName[ indS_PRED], S_PRED);
    m.put(MarshrutPropName[ indS_PAST], S_PAST);
    m.put(MarshrutPropName[ indORDER ], ORDER);
    for (int i = 0; i < STRELSCOUNT; i++)
        m.put(STRELS[i]->STRELNAME, STRELS[i]->ToString());

}



TMarshSectType AMarshSectType[4] = {
    /*    T1  T2     T  */
    /* 0  0   0  */ mstWW,
    /* 1  0   1  */ mstWB,
    /* 2  1   0  */ mstBW,
    /* 3  1   1  */ mstBB
};


void TMarshrut::SetMarshSectType()
{
    int T1 = 3;
    int T2 = 3;
    if ((pS_PRED == NULL) || (pS_PAST == NULL)) {
        MarshSectType = mstUnknow;
        return;
    }

    if ((pS_PRED->GetType() == WAY))  T1 = 0; else if ((pS_PRED->GetType() == PLOT))T1 = 1;
    if ((pS_PAST->GetType() == WAY))  T2 = 0; else if ((pS_PAST->GetType() == PLOT))T2 = 1;
    if ((T1 == 3) || (T2 == 3)) MarshSectType = mstUnknow; else
        MarshSectType = AMarshSectType[T1*2+T2];
}

void TMarshrut::UpdateState()
{
    // ��������� ������� ���������
    for (int i = 0; i < STRELSCOUNT; i++)
        STRELS[i]->UpdateState();

    if (pSV != NULL)pSV->UpdateState();
    if (pS_PRED != NULL)pS_PRED->UpdateState();
    if (pS_PAST != NULL)pS_PAST->UpdateState();

    Element * E=NULL;
    E= dynamic_cast<Element *>(pSV);
    if (E != NULL)
        realbusySV = E->fimpuls_busi;
    E = dynamic_cast<Element *>(pSV2);
    if (E != NULL)
           realbusySV = E->fimpuls_busi;
    E = dynamic_cast<Element *>(pS_PRED);
    if (E != NULL) {
            realbusyS_PRED = E->fimpuls_busi;
            if (E->impuls_busi == 0) realbusyS_PRED = 3;
            realkzmS_PRED = E->fimpuls_plus;
            if (E->impuls_plus == 0) realkzmS_PRED = 3;
    }
    E = dynamic_cast<Element *>(pS_PAST);
    if (E != NULL) {
            realbusyS_PAST = E->fimpuls_busi;
            if (E->impuls_busi == 0) realbusyS_PAST = 3;
            realkzmS_PAST = E->fimpuls_plus;
            if (E->impuls_plus == 0) realkzmS_PAST = 3;
    }

}

/*void TMarshrut::UpdateState2()
{
    // ��������� ������� ���������
    for (int i = 0; i < STRELSCOUNT; i++)
        STRELS[i]->UpdateState2();

    realbusySV = _f_(imp[ii_busySV], NULL);
    realbusyS_PRED = _f_(imp[ii_busyS_PRED], NULL);
    realbusyS_PAST = _f_(imp[ii_busyS_PAST], NULL);
    realkzmS_PRED = _f_(imp[ii_kzmS_PRED], NULL);
    realkzmS_PAST = _f_(imp[ii_kzmS_PAST], NULL);
    if (imp[ii_busySV]    == 0) realbusySV = 3;
    if (imp[ii_busyS_PRED] == 0) realbusyS_PRED = 3;
    if (imp[ii_busyS_PAST] == 0) realbusyS_PAST = 3;
    if (imp[ii_kzmS_PRED] == 0) realkzmS_PRED = 3;
    if (imp[ii_kzmS_PAST] == 0) realkzmS_PAST = 3;

    for (int d = 0; d < 2; d++) {
        rimp_per_napr[d] = _f_(imp_per_napr[d], NULL);
        rimp_per_busy[d] = _f_(imp_per_busy[d], NULL);
        if (imp_per_napr[d] == 0) rimp_per_napr[d] = 3;
        if (imp_per_busy[d] == 0) rimp_per_busy[d] = 3;
    }


}
*/


bool TMarshrut::UpdateStrelOrder() // ������������� �������� ORDER ��� �������
{
    TParString PS(ORDER, ":");
    for (int i = 0; i < STRELSCOUNT; i++) STRELS[i]->ORDER = NOORDER;
    bool ex;
    bool err = false;
    for (int i = 0; i < PS.ParamsCount; i++) {
        ex = false;
        for (int j = 0; j < STRELSCOUNT; j++) {
            if (PS[i] == STRELS[j]->STRELNAME) {
                STRELS[j]->ORDER = i + 1;
                ex = true;
                break;
            }
        }
        if (!ex) err = true;
    }
    return !err;
}

void TMarshrut::AddStrInMarsh(TStrInMarsh *sim)
{
    FStrels->Add(sim);
}

void TMarshrut::DelStrInMarsh(TStrInMarsh *sim)
{
    int i = FStrels->IndexOf(sim);
    if (i >= 0) FStrels->Delete(i);
}


TStrInMarsh * TMarshrut::SetStrInMarsh(String StrelName, int IS, TStrInMarshChek DOCHEK, int ORDER)
{
    TStrInMarsh * simS = MarshList->GetStrelByName(StrelName);
    if (simS == NULL) {
        WriteToLog((StrelName + " ��� � ������ ������� �������.").c_str());
        return NULL;
    }
    TStrInMarsh * simM = GetStrelByName(StrelName);
    if (simM == NULL) {
        simM = new TStrInMarsh();
        strncpy(simM->STRELNAME, simS->STRELNAME,sizeof(simM->STRELNAME)-1);
        simM->pStrel = simS->pStrel;
        AddStrInMarsh(simM);
    }
    simM->IS = IS;
    simM->DOCHEK = DOCHEK;
    simM->ORDER = ORDER;
    return simM;
}

// ���������� ��� �������� �� �����������
TMarshDirType TMarshrut::GetDirType()
{
    // ��������
    if (MarshSectType == mstBW) return mdirArr;
    // �����������
    if (MarshSectType == mstWB) return mdirDep;
    // ��������
    if (MarshSectType == mstWW) return mdirMove;

    return mdirUnknown;  // ��������� ���
}
TMarshOdd_Even TMarshrut::GetOddEven()
{
    if (SV.SubString(0, 1).UpperCase() == "�") return mEven; // ������
    if (SV.SubString(0, 1).UpperCase() == "�") return mOdd;  // ��������
    return mUnknown;
}

/*int TMarshrut::CheckGoodDir()
{
    if (GetDirType() != mdirDep) return 1;  // ���� ����������� �������
    int naprOdd = imp_per_napr[0];  //������ ����������� �� �������� � �
    int naprEven = imp_per_napr[1];
    int zanOdd = imp_per_busy[0];  //������ ������� �������� � �
    int zanEven = imp_per_busy[1];
    // ���������� � UpdateState()
    int rnaprOdd = rimp_per_napr[0];
    int rnaprEven = rimp_per_napr[1];
    int rzanOdd = rimp_per_busy[0];
    int rzanEven = rimp_per_busy[1];

    TMarshOdd_Even OdEv_ = GetOddEven();

    if (OdEv_ == mUnknown) return 1;
    if (rnaprEven == 33 || rzanEven == 33 || rnaprOdd == 33 || rzanOdd == 33) return 1;
    if ((rzanEven == 1) || (rzanOdd == 1)) { // ����� �������
        if (OdEv_ == mOdd) {
            if ((rnaprEven == 1) || (rnaprEven == rnaprOdd)) return -1; // ������� �����!
        }
        if (OdEv_ == mEven) {
            if ((rnaprOdd == 1) || (rnaprEven == rnaprOdd)) return -1; // ������� �����!
        }
    }
    return 1; // ��������� ���!
}
*/
// ====================================================================================

TMarshList::TMarshList()
{
    FStrels = new TList();
    FStrels->Capacity = 20;
    FMarshuts = new TList();
    memset(indMarshrutPropName, 0, sizeof(indMarshrutPropName));
}

TMarshList::~TMarshList()
{
    Clear();
    delete FStrels;
    delete FMarshuts;
}

void TMarshList::Clear()
{
    for (int i = 0; i < FStrels->Count; i++) delete((TStrInMarsh *)FStrels->Items[i]);
    FStrels->Clear();
    for (int i = 0; i < FMarshuts->Count; i++) delete((TMarshrut *)FMarshuts->Items[i]);
    FMarshuts->Clear();
}

void __fastcall TMarshList::SetSTRELS(int Index, TStrInMarsh * value)
{
    memcpy(FStrels->Items[Index], value, sizeof(TStrInMarsh));
}
TStrInMarsh * __fastcall TMarshList::GetSTRELS(int Index)
{
    return (TStrInMarsh *) FStrels->Items[Index];
}

int __fastcall TMarshList::GetSTRELSCOUNT()
{
    return FStrels->Count;
}



bool TMarshList::LoadFromCSV(String stFN)
{
    TMarshrut * M;
    TStrInMarsh * mes;

    if (!FileExists(stFN)) return false;
    try {
        FileName = ExtractFileName(stFN); FileName = ChangeFileExt(FileName, "");
        Clear();
        TStringList * SL = new TStringList();
        SL->LoadFromFile(stFN);
        //���� �����
        String stSH, S;
        for (int i = 0; i < SL->Count; i++) {
            stSH = SL->Strings[i];
            if (stSH.Pos(MarshrutPropName[ 0]) == 1) {
                SL->Delete(i);
                break;
            }
        }
        if (stSH == "") {
            WriteToLog(("�� ������� ����� � " + stFN).c_str());
            return false;
        }
        TParString PS(stSH, ";,");         // ������� ����������� ��-�� ��������� ������ Excel
        TParString ps("", ";,");
        TPropMap m;
        //��������� PropMap
        int pcnt = PS.ParamsCount;
        for (int i = 0; i < MarshrutPropNameCount; i++)
            indMarshrutPropName[i] = PS.GetInd(MarshrutPropName[i]);
        for (int i = 0; i < pcnt; i++) {
            m.put(PS[i], "");
            if (!IsPropNameStrel(PS[i])) PropStrBegin = i + 1;
        }
        //if (m.ItemsCount!=pcnt){
        //   ShowMessage("�������� � ����� "+stFN+"\r ��������� "+IntToStr(pcnt-m.ItemsCount)+" ����(�) !");
        //   return false;
        //}

        //if (PS.GetInd(MarshrutPropName[indGORL]))<=0) PropStrBegin

        // ��������� ������ ��� �������
        for (int i = 0/*PropStrBegin*/; i < pcnt; i++) {
            if (!IsPropNameStrel(PS[i])) continue;
            mes = new TStrInMarsh();
            strncpy(mes->STRELNAME, PS[i].c_str(),sizeof(mes->STRELNAME)-1);
            FStrels->Add(mes);
        }

        for (int i = 0; i < SL->Count; i++) {
            ps.SetVal(SL->Strings[i]);
            if (ps.GetInt(0, 0) == 0) continue; //������ ���������� � �����
            for (int j = 0; j < pcnt; j++)
                m.Val[j] = ps[j];
            // ��������� �������
            M = new TMarshrut();
            M->SetPropMap(m);
            //FMarshuts->Add(M);
            AddMarshrut(M);
        }
     /*
        // ���������� �������� ����
        TStrInMarsh * SIM;
        for (int i = 0; i < SL->Count; i++) {
            ps.SetVal(SL->Strings[i]);
            if (ps[0] == "���") {
                // ���;_N;name;ObjID,inv;packet_name;busy;plus;minus;kzm
                //  0   1  2    3    4         5      67  89   1011  1213
                int ii = ps.GetInt(1);
                SIM = STRELS[ii];
                if ((SIM == NULL) || (String(SIM->STRELNAME) != ps[2])) {
                    WriteToLog(("�������� �������� ������ �� " + stFN + "\r" + SL->Strings[i]).c_str());
                    break;
                }
                SIM->ObjID = ps.GetInt(3, 0);
                SIM->PacketName = ps[5];
                SIM->imp[0] = ps.GetInt(6, 0);
                SIM->imp[1] = ps.GetInt(8, 0);
                SIM->imp[2] = ps.GetInt(10, 0);
                SIM->imp[3] = ps.GetInt(12, 0);

            }

            if (ps[0] == "M_T") {
                int ii = ps.GetInt(1); M = MARSHRUTS[ii];
                if ((M == NULL)) {
                    WriteToLog(("�������� �������� ������ �� " + stFN + "\r" + SL->Strings[i]).c_str()); break;
                }
                M->MarshSectType = (TMarshSectType)ps.GetInt(2, 0);
            }


            // M_SV;_N;name;ObjID;packet_name;busy; ;plus;  ;mnus;  ;kzm;  ;
            // 0    1    2    3        4        5  6   7   8   9  10  11  12
            if (ps[0] == "M_SV") {
                int ii = ps.GetInt(1); M = MARSHRUTS[ii];
                if ((M == NULL) || (M->SV != ps[2])) {
                    WriteToLog(("�������� �������� ������ �� " + stFN + "\r" + SL->Strings[i]).c_str()); break;
                }
                M->ObjID[ii_busySV] = ps.GetInt(3, 0);
                M->PacketName = ps[4];
                M->imp[ii_busySV] = ps.GetInt(5, 0);
                M->impname[ii_busySV] = ps.GetStr(5 + 1, 0);
            }
            if (ps[0] == "M_S_PRED") {
                int ii = ps.GetInt(1); M = MARSHRUTS[ii];
                if ((M == NULL) || (M->S_PRED != ps[2])) {
                    WriteToLog(("�������� �������� ������ �� " + stFN + "\r" + SL->Strings[i]).c_str()); break;
                }
                M->ObjID[ii_busyS_PRED] = ps.GetInt(3, 0);
                if (M->PacketName == "")M->PacketName = ps[4];
                M->imp[ii_busyS_PRED] = ps.GetInt(5, 0);
                M->impname[ii_busyS_PRED] = ps.GetStr(5 + 1, 0);
                M->imp[ii_kzmS_PRED] = ps.GetInt(7, 0);
                M->impname[ii_kzmS_PRED] = ps.GetStr(7 + 1, 0);
            }
            if (ps[0] == "M_S_PAST") {
                int ii = ps.GetInt(1); M = MARSHRUTS[ii];
                if ((M == NULL) || (M->S_PAST != ps[2])) {
                    WriteToLog(("�������� �������� ������ �� " + stFN + "\r" + SL->Strings[i]).c_str()); break;
                }
                M->ObjID[2] = ps.GetInt(3, 0);
                if (M->PacketName == "")M->PacketName = ps[4];
                M->imp[ii_busyS_PAST] = ps.GetInt(5, 0);
                M->impname[ii_busyS_PAST] = ps.GetStr(5 + 1, 0);
                M->imp[ii_kzmS_PAST] = ps.GetInt(7, 0);
                M->impname[ii_kzmS_PAST] = ps.GetStr(7 + 1, 0);
            }
        }
       */

        delete SL;
        //UpdateLoadedImps();

    } catch (...) {
        WriteToErr((" �������� � " + stFN).c_str());
        return false;

    }
    return true;
}

/*void  TMarshList::UpdateLoadedImps()
{
    int off;
    for (int i = 0; i < STRELSCOUNT; i++) {
        for (int j = 0; j < 4; j++) {

            if ((CustomGetPacketOffset != NULL) && (abs(STRELS[i]->imp[j]) >= 1000)) {
                off = CustomGetPacketOffset(1, STRELS[i]->PacketName.c_str(), 0);
                STRELS[i]->imp[j] = off * 1000 + STRELS[i]->imp[j] % 1000;
            }
        }
    }
    TMarshrut * M;
    TStrInMarsh * sim1;
    TStrInMarsh * sim2;
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        M = MARSHRUTS[i];
        // ����������� �� �����
        for (int sn1 = 0; sn1 < M->STRELSCOUNT; sn1++) {
            sim1 = M->STRELS[sn1];
            for (int sn2 = 0; sn2 < STRELSCOUNT; sn2++) {
                sim2 = STRELS[sn2];
                if (strcmp(sim1->STRELNAME, sim2->STRELNAME) == 0) {
                    sim1->PacketName = sim2->PacketName;
                    sim1->ObjID      = sim2->ObjID;

                    for (int j = 0; j < 4; j++)
                        sim1->imp[j] = sim2->imp[j];
                    break;
                }
            }
        }

        if (CustomGetPacketOffset != NULL) {
            for (int j = 0; j < 5; j++) {
                if (abs(M->imp[j]) >= 1000) {
                    M->imp[j] = CustomGetPacketOffset(1, MARSHRUTS[i]->PacketName.c_str(), 0) * 1000 + M->imp[j] % 1000;
                }
            }
        }
    }
}
*/

bool TMarshList::SaveToCSV(String stFN)
{
    //TMarshrut * M;

    if (MARSHRUTSCOUNT <= 0) return false;
    TStringList * SL = new TStringList();

    TParString PS("", ";");
    TParString ps("", ";");
    TPropMap m;

    //������� �����
    int k = 0;
    for (int i = 0; i < MarshrutPropNameCount; i++) {
        //if (indMarshrutPropName[i] < 0) continue;
        PS.SetStr(k, MarshrutPropName[i]);
        k++;
    }
    for (int i = 0; i < STRELSCOUNT; i++) {
        PS.SetStr(i + k, STRELS[i]->STRELNAME);
    }

    SL->Add(PS.ResultStr());
    int ind;
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        m.clear();
        MARSHRUTS[i]->GetPropMap(m);
        for (int j = 0; j < PS.ParamsCount; j++) ps.SetStr(j, "");
        for (int j = 0; j < m.ItemsCount; j++) {
            ind = PS.GetInd(m.Keys[j]);
            if (ind >= 0)
                ps.SetStr(ind, m.Val [j]);
        }
        SL->Add(ps.ResultStr());
    }

    // ��������� ���� �� ���������
 /*   // ���;_N;name;ObjID;inv;packet_name;busy;plus;minus;kzm
    String ST, ST2;
    Strel0 * s0;
    for (int i = 0; i < STRELSCOUNT; i++) {
        if (STRELS[i] == NULL) continue;
        s0 = dynamic_cast<Strel0*>(STRELS[i]->pStrel);
        if (s0 == NULL) continue;
        ST2 = s0->GetStrelInfo();
        ST = "���;" + IntToStr(i) + ";" + ST2;
        SL->Add(ST);
    }
    TMarshrut * M;
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        M = MARSHRUTS[i];
        //M_T;N;MarshSectType
        ST = "M_T;" + IntToStr(i) + ";" + IntToStr(M->MarshSectType); SL->Add(ST);
        // M_SV;_N;name;ObjID;packet_name;busy
        if (M->pSV != NULL) {
            ST = "M_SV;" + IntToStr(i) + ";" + M->pSV->GetCompInfo(); SL->Add(ST);
        }
        if (M->pS_PRED != NULL) {
            ST = "M_S_PRED;" + IntToStr(i) + ";" + M->pS_PRED->GetCompInfo(); SL->Add(ST);
        }
        if (M->pS_PAST != NULL) {
            ST = "M_S_PAST;" + IntToStr(i) + ";" + M->pS_PAST->GetCompInfo(); SL->Add(ST);
        }
    }
  */  
    try {
        SL->SaveToFile(stFN);
    } catch (...) {
        ShowMessage(" �� ���� �������� " + stFN);
        return false;
    }
    delete SL;
    return true;
}


void        TMarshList::AddMarshrut(TMarshrut* M)// ���������� ������ ��������
{
    // ��������� ������� ������� � ������� ��� �������
    bool ex;
    TStrInMarsh * mes;
    String N1, N2;
    for (int i = 0; i < M->STRELSCOUNT; i++) {
        ex = false;
        N1 = M->STRELS[i]->STRELNAME;
        for (int j = 0; j < STRELSCOUNT; j++) {
            N2 = STRELS[j]->STRELNAME;
            if (N1 == N2) {
                ex = true;
                break;
            }
        }
        if (!ex) {
            mes = new TStrInMarsh();
            strncpy(mes->STRELNAME, M->STRELS[i]->STRELNAME,sizeof(mes->STRELNAME)-1);
            mes->pStrel = M->STRELS[i]->pStrel;
            FStrels->Add(mes);
        }
    }
    // ��������� �������
    FMarshuts->Add(M);
    M->MarshList = this;
}
void        TMarshList::DelMarshrut(TMarshrut* M)
{
    // ������� �������
    int i = FMarshuts->IndexOf(M);
    if (i >= 0) {
        FMarshuts->Delete(i);
        delete M;
    }
}


TMarshrut* __fastcall TMarshList::GetMARSHRUTS(int Index)
{
    return (TMarshrut*)FMarshuts->Items[Index];
}

int __fastcall TMarshList::GetMARSHRUTSCOUNT()
{
    return FMarshuts->Count;
}




TYP STAStrelTypes[] = {SWRT   , SWLT   , SWLB   , SWRB   ,
                       SWL    , SWKT   , SWKB   ,
                       SWrt   , SWlt   , SWlb   , SWrb ,
                       ENGL1  , ENGL2  , XBOST1 , XBOST2 , XBOST3 , XBOST4 , KUS1   , KUS2,
                       SWrtW   , SWltW   , SWlbW   , SWrbW,
                       Y_STREL_1, Y_STREL_2, Y_STREL_3, Y_STREL_4, G_STREL_Y, G_RC, G_RC_2, G_ZAMI, G_ZKR, G_STREL_1, G_ZAMP, G_OSY, G_STREL_2,Y_STREL_5,Y_STREL_6
                      };
TYP STAWaysTypes[] = {WAY};
TYP STABlockTypes[] = {PLOT};

void TMarshList::ConnectToStanSTA(Station * pS)
{

    pStan = pS;
    //AComp * ac;
    TMarshrut* M;
    TStrInMarsh * sim;
    TStrInMarsh * sim2;

    // ���������� �������
    for (int i = 0; i < STRELSCOUNT; i++) {
        sim = STRELS[i];
        sim->pStrel = pStan-> GetObjByName_InTypes(sim->STRELNAME, STAStrelTypes, sizeof(STAStrelTypes));
        //if (sim->pStrel!=NULL) sim->ObjID=sim->pStrel->ID;
    }



    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        M = MARSHRUTS[i];
        M->pSV =    pStan->GetObjByName_Unit(M->SV.c_str(), CEMA);
        M->pSV2 =   pStan->GetObjByName_Unit(M->SV2.c_str(), CEMA);
        if (M->pSV != NULL) {
            //M->pS_PRED=pStan->GetObjByName_Unit(M->S_PRED.c_str(),WAYS);
            //M->pS_PAST=pStan->GetObjByName_Unit(M->S_PAST.c_str(),WAYS);

            //M->imp[ii_busySV] = M->pSV->impuls_busi;
            //M->ObjID[ii_busySV] = M->pSV->GetID();
        }

        // �������� ��������� ���� ���� �� � ���� � ����������� �������
        M->pS_PRED = (Ways*)pStan->GetObjByName_InTypes(M->S_PRED.c_str(), STAWaysTypes, sizeof(STAWaysTypes));
        if (M->pS_PRED == NULL) M->pS_PRED = (Ways*)pStan->GetObjByName_InTypes(M->S_PRED.c_str(), STABlockTypes, sizeof(STABlockTypes));
        if (M->pS_PRED != NULL) {
            //M->imp[ii_busyS_PRED] = M->pS_PRED->impuls_busi;
            //M->imp[ii_kzmS_PRED] = M->pS_PRED->impuls_kzm;
            //M->ObjID[ii_busyS_PRED] = M->pS_PRED->GetID();
        }
        M->pS_PAST = (Ways*)pStan->GetObjByName_InTypes(M->S_PAST.c_str(), STAWaysTypes, sizeof(STAWaysTypes));
        if (M->pS_PAST == NULL) M->pS_PAST = (Ways*)pStan->GetObjByName_InTypes(M->S_PAST.c_str(), STABlockTypes, sizeof(STABlockTypes));
        if (M->pS_PAST != NULL) {
            //M->imp[ii_busyS_PAST] = M->pS_PAST->impuls_busi;
            //M->ObjID[ii_busyS_PAST] = M->pS_PAST->GetID();
            //if (M->pS_PAST->GetType() == WAY) M->imp[ii_kzmS_PAST] = M->pS_PAST->impuls_plus;
        }

        for (int j = 0; j < M->STRELSCOUNT; j++) {
            sim = M->STRELS[j];
            for (int k = 0; k < STRELSCOUNT; k++) {
                sim2 = STRELS[k];
                if (strcmp(sim->STRELNAME, sim2->STRELNAME) == 0){
                    sim->pStrel = sim2->pStrel;
                    //sim->ObjID  = sim2->ObjID;
                }
            }
            if (sim->pStrel == NULL) M->bErrorData=true;
        }
        M->SetMarshSectType();
        M->UpdateStrelOrder();

    }

}

void TMarshList::ConnectToStanBD(Station * pS)
{
    pStan = pS;
}

void __fastcall TMarshrut::SetSTRELSORD(int Index, TStrInMarsh * value)
{

}

TStrInMarsh * __fastcall TMarshrut::GetSTRELSORD(int Index)
{
    if (!Index) return NULL;
    for (int i = 0; i < STRELSCOUNT; i++) {
        if (STRELS[ i ]->ORDER == Index) return STRELS[ i ];
    }
    return NULL;
}

int TMarshrut::GetMaxORDER(void)
{
    int MX = 0;
    for (int i = 0; i < STRELSCOUNT; i++)
        if (STRELS[ i ]->ORDER > MX) MX = STRELS[ i ]->ORDER;

    return MX;
}


void TMarshList::UpdateState()
{
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        MARSHRUTS[i]->UpdateState();
    }
}

/*void TMarshList::UpdateState2()
{
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        MARSHRUTS[i]->UpdateState2();
    }
}
*/

TStrInMarsh * TMarshList::GetStrelByName(String StrelName)
{
    for (int i = 0; i < FStrels->Count; i++)
        if (String(((TStrInMarsh *)FStrels->Items[i])->STRELNAME) == StrelName)
            return (TStrInMarsh *)FStrels->Items[i];
    return NULL;
}




TMarshrut * TMarshList::GetMarshrutByNum(int Num)
{
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        if (MARSHRUTS[i]->NUMCOM == Num) return MARSHRUTS[i];
    }
    return NULL;
}

void TMarshrut::Show(bool bSetIs, bool bSetClr, bool bSetStyll, int Clr, int Styll)
{
    // �� ��������
    TStrInMarsh * sim;
    for (int i = 0; i < STRELSCOUNT; i++) {
        sim = STRELS[i];
        if ((sim != NULL) && (sim->pStrel != NULL) && (sim->DOCHEK == cNORMAL)) {
            Strel0 * S = dynamic_cast<Strel0 *>(sim->pStrel);
            if (S == NULL) continue;

            if (bSetIs) {
                S->is = sim->IS;
            }
            if (bSetClr) {
                S->clr = Clr;
            }
            if (bSetStyll) {
                /*if (((S->is==W)||(S->is==D))&&
                    ((sim->IS==P)||(sim->IS==M))){
                    S->bSetIs=false;
                    S->is=sim->IS;
                } */
                if (sim->IS == P) S->styll1 = Styll;
                if (sim->IS == M) S->styll2 = Styll;
                if (sim->IS == W) S->styll3 = Styll;
            }
            S->UpdateState();
            S->Show();
        }

    }

}

void TMarshList::ShowUstMarsh(bool Only_1)
{
    // ������� ������
    Strel0 * S;
    for (int i = 0; i < STRELSCOUNT; i++) {
        S = dynamic_cast<Strel0 *>(STRELS[i]->pStrel);
        if (S != NULL) {
            S->Tag = S->bShowInSpyMarsh;
            S->bShowInSpyMarsh = false;
        }
    }
    //for(int i=0;i<MARSHRUTSCOUNT;i++){
    //        MARSHRUTS[i]->SetForShowUst(true);
    //}

    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        if (((!Only_1) || (MARSHRUTS[i]->GROUP == 1)) && (MARSHRUTS[i]->IsUstanovlen()))
            MARSHRUTS[i]->SetForShowUst();
    }

    for (int i = 0; i < STRELSCOUNT; i++) {
        S = dynamic_cast<Strel0 *>(STRELS[i]->pStrel);
        if (S != NULL) {
            if (S->Tag != S->bShowInSpyMarsh)
                S->StateChanged = true;
            S->Tag = 0;
        }
    }

}


void TMarshrut::SetForShowUst(bool bHide)
{
    // �� ��������
    TStrInMarsh * sim;
    for (int i = 0; i < STRELSCOUNT; i++) {
        sim = STRELS[i];
        if ((sim != NULL) && (sim->pStrel != NULL) && (sim->DOCHEK == cNORMAL)) {
            Strel0 * S = dynamic_cast<Strel0 *>(sim->pStrel);
            if (S == NULL) continue;
            //bool oldbSetClr=S->bSetClr;
            if (bHide) {
                S->bShowInSpyMarsh = false;
                //S->bSetClr=true;
                //S->UpdateState();
                //S->Show();
            } else {
                //if ((S->clr!=COLOR_B)&&(S->clr!=COLOR_SET)){
                //   S->bSetClr=false;
                //   S->clr=COLOR_S;
                //   S->UpdateState();
                //   S->Show();
                //}
                S->bShowInSpyMarsh = true;
            }
            //S->bSetClr=oldbSetClr;
        }
    }

    // pfvf[ytvcz yf ����


}

bool TMarshrut::IsUstanovlen()
{
    // �� ��������
    TStrInMarsh * sim;
    for (int i = 0; i < STRELSCOUNT; i++) {
        sim = STRELS[i];
        if ((sim != NULL) && (sim->pStrel != NULL) && (sim->DOCHEK == cNORMAL)) {
            Strel0 * S = dynamic_cast<Strel0 *>(sim->pStrel);
            if (S == NULL) return false;
            if (sim->DOCHEK == cNO_CHECK_IS) continue;
            if (sim->realIS != sim->IS) return false;
        }
    }
    return true;


}
/*
void TMarshrut::CheckStat(bool &IsOK, bool &BusyOK, bool &KzmOK,bool &SVOk)
{
    IsOK=true; BusyOK=true;  KzmOK=true; SVOk=false;
    for (int sn=0;sn<STRELSCOUNT;sn++){ // ������� �� ��������
         if ( (STRELS[sn]->DOCHEK!=cNO_CHECK_IS)/*(STRELS[sn]->pStrel!=NULL)*){
                if (IsOK){
                        int r=STRELS[sn]->realIS;
                        int c=STRELS[sn]->IS;
                        if ( (c!=r)||(r==33)||(r==D) ) {
                                IsOK=false; // ��������� �� ��
                        }
                }

         }
         if ( (STRELS[sn]->DOCHEK!=cNO_CHECK_BUSY)/*&&(STRELS[sn]->pStrel!=NULL) *){
                if (BusyOK){
                        int r=STRELS[sn]->realBUSY;
                        if (r!=0) BusyOK=false; // ��������� ����
                }
         }
         if ( (STRELS[sn]->DOCHEK!=cNO_CHECK_BUSY)&&
                (STRELS[sn]->DOCHEK!=cNO_CHECK_IS)/*&&(STRELS[sn]->pStrel!=NULL)* ){
                if (KzmOK){
                    int r=STRELS[sn]->realKZM;
                    if  (r!=0) KzmOK=false;  // ��������� ���
                }
         }
     }
     if ( (imp[ii_busyS_PAST]!=0)&&(realbusyS_PAST!=0)) BusyOK=false; // ���� �����
     if ( ((MarshSectType==mstBW)||(MarshSectType==mstWW)) ) {
          if ( (imp[ii_kzmS_PAST]!=0)&&(realkzmS_PAST!=0) ) KzmOK=false; // ���� �� �������
     }

     if (realbusySV==1) SVOk=true;

}
*/

//Pol  0 ���, 1 - � ��������, 33..
//Busy 0 - ��� �� �� �����    33..
//Kzm  0 - ��� �� �� �����    33..
//SVOk 0- ������,1 - ������,  33..

void TMarshrut::CheckStatFull(int &Pol, int &Busy, int &Kzm, int &SV)
{
    Pol = 1; Busy = 0;  Kzm = 0; SV = 0;
    for (int sn = 0; sn < STRELSCOUNT; sn++) { // ������� �� ��������
        String nn = STRELS[sn]->STRELNAME;
        if ((STRELS[sn]->DOCHEK != cNO_CHECK_IS)/*(STRELS[sn]->pStrel!=NULL)*/) {
            int r = STRELS[sn]->realIS;
            int c = STRELS[sn]->IS;
            if (r == 33 || r == D) {
                Pol = 33;
            }
            if (c != r && Pol != 33) {
                Pol = 0; // ��������� �� ��
            }

        }
        if ((STRELS[sn]->DOCHEK != cNO_CHECK_BUSY)/*&&(STRELS[sn]->pStrel!=NULL) */) {
            if (Busy != 33) {
                int r = STRELS[sn]->realBUSY;
                if (r == 33) Busy = 33;
                if (r == 1) Busy = 1; // ��������� ����
            }
            if (Kzm != 33) {
                int r = STRELS[sn]->realKZM;
                if (r == 33) Kzm = 33;
                if (r == 1) Kzm = 1;  // ��������� ���
            }
        }
    }
    //if (imp[ii_busyS_PAST] != 0) {
        if (realbusyS_PAST == 33) Busy = 33;
        if (realbusyS_PAST == 1)  Busy = 1; // ���� �����
    //}
    if (((MarshSectType == mstBW) || (MarshSectType == mstWW))) {
       // if (imp[ii_kzmS_PAST] != 0) {
            if (realkzmS_PAST == 33) Kzm = 33; // ���� �� �������
            if (realkzmS_PAST == 1)  Kzm = 1; // ���� �� �������
       // }
    }

    SV = realbusySV;

}



String GetIsStr(int IS)
{
    switch (IS) {
    case W: return "W";
    case P: return "+";
    case M: return "-";
    };
    return IntToStr(IS);
}

String      TMarshrut::GetStateString()
{
    String ST;
    TStrInMarsh *SIM;
    ST = SV + " " + IntToStr(realbusySV) + " ";
    for (int sn = 0; sn < STRELSCOUNT; sn++) { // ������� �� ��������
        SIM = STRELS[sn];
        if ((SIM->DOCHEK != cNO_CHECK_IS)) {
            ST = ST + "[" + SIM->STRELNAME + " " + SIM->ToString() + GetIsStr(SIM->realIS) + "]";
        }
    }
    return ST;
}

extern T_GetSigName_Func _GetSigName_Func;
String      TMarshrut::GetUsedDataStr()
{
    if (_GetSigName_Func == NULL) return "";
    String ST = "";
    /*TStrInMarsh *SIM;
    for (int sn = 0; sn < STRELSCOUNT; sn++) { // ������� �� ��������
        SIM = STRELS[sn];

        for (int i = 0; i < 4; i++)
            if (SIM->imp[i] > 1000)
                ST = ST + " " + _GetSigName_Func(SIM->imp[i]);
    }
    for (int i = 0; i < 5; i++)
        if (imp[i] > 1000)
            ST = ST + " " + _GetSigName_Func(imp[i]);
    */
    return ST;
}

bool TMarshrut::CommonSections(TMarshrut * M)
{
    TStrInMarsh *SIM1;
    TStrInMarsh *SIM2;
    for (int sn1 = 0; sn1 < STRELSCOUNT; sn1++) { // ������� �� ��������
        SIM1 = STRELS[sn1];
        for (int sn2 = 0; sn2 < M->STRELSCOUNT; sn2++) { // ������� �� ��������
            SIM2 = M->STRELS[sn2];
            if (strcmp(SIM1->STRELNAME, SIM2->STRELNAME) == 0) return true;
        }
    }
    if ((S_PAST != "") && (S_PAST == M->S_PAST)) return true;
    return false;
}

const ParNameCnt = 15;

String ParName[ParNameCnt] = {
    "NUMCOM",          // 0
    "GROUP",           // 1
    "NAME",            // 2
    "SNAME",           // 3
    "M1",              // 4
    "S1",              // 5
    "G1",              // 6
    "C1",              // 7
    "N1",              // 8
    "M2",              // 9
    "S2",              // 10
    "G2",              // 11
    "C2",              // 12
    "N2",              // 13
    "NETNAME"          // 14

};


const mNUMCOM       = 0;
const mGROUP        = 1;
const mNAME         = 2;
const mSNAME        = 3;
const mM1           = 4;
const mS1           = 5;
const mG1           = 6;
const mC1           = 7;
const mN1           = 8;
const mM2           = 9;
const mS2           = 10;
const mG2           = 11;
const mC2           = 12;
const mN2           = 13;
const mNETNAME      = 14;

int _CurHeadInd[ParNameCnt];

void MakeHeadInd(TParString *PS)
{
    memset(&_CurHeadInd, 0, sizeof(_CurHeadInd));
    for (int i = 0; i < ParNameCnt; i++)
        _CurHeadInd[i] = PS->GetInd(ParName[i]);
}

bool TMarshList::LoadTUFromCSV(String stFN)
{
    TMarshrut * M;

    if (!FileExists(stFN)) return false;
    try {
        TStringList * SL = new TStringList();
        SL->LoadFromFile(stFN);
        /* ���� �����  */
        TParString PS("", ";,");
        for (int i = 0; i < SL->Count; i++) {
            PS.SetVal(SL->Strings[i]);
            if ((PS.GetInd("NUMCOM") >= 0) || (PS.GetInd("���������� �����") >= 0)) {
                SL->Delete(i);
                break;
            }
        }
        if ((PS.GetInd("NUMCOM") < 0) && (PS.GetInd("���������� �����") < 0)) {
            delete SL;
            return false;
        }
        MakeHeadInd(&PS);
        TParString ps("", ";,");
        int NUMCOM;
        for (int i = 0; i < SL->Count; i++) {
            ps.SetVal(SL->Strings[i]);
            NUMCOM = ps.GetInt(_CurHeadInd[mNUMCOM]);
            M = GetMarshrutByNum(NUMCOM);
            if (M == NULL) continue;
            M->TUCmd.tu[0].mid =   ps.GetInt(_CurHeadInd[mM1]);
            M->TUCmd.tu[0].stan =  ps.GetInt(_CurHeadInd[mS1]);
            M->TUCmd.tu[0].group = ps.GetInt(_CurHeadInd[mG1]);
            M->TUCmd.tu[0].cod =  ps.GetInt(_CurHeadInd[mC1]);
            M->TUCmd.tu[0].num =  ps.GetInt(_CurHeadInd[mN1]);
            M->TUCmd.tu[1].mid =   ps.GetInt(_CurHeadInd[mM2]);
            M->TUCmd.tu[1].stan =  ps.GetInt(_CurHeadInd[mS2]);
            M->TUCmd.tu[1].group = ps.GetInt(_CurHeadInd[mG2]);
            M->TUCmd.tu[1].cod =  ps.GetInt(_CurHeadInd[mC2]);
            M->TUCmd.tu[1].num =  ps.GetInt(_CurHeadInd[mN2]);
            M->TUPacketName =     ps.GetStr(_CurHeadInd[mNETNAME]);
        }
        delete SL;
    } catch (...) {
        return false;
    }
    return true;
}


TMarshrut * TMarshList::GetMarshrutByTU(_tTU * TUCmd)
{
    for (int i = 0; i < MARSHRUTSCOUNT; i++) {
        if (memcmp(&MARSHRUTS[i]->TUCmd, TUCmd, sizeof(MARSHRUTS[i]->TUCmd)) == 0)
            return MARSHRUTS[i];
    }
    return NULL;

}
