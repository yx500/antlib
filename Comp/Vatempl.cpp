//#include <vcl.h>
#pragma hdrstop
#include <algorithm>

#include "APch.h"

#include "Vatempl.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

#include "elem.h"
#include "Ways.h"
#include "Svet.h"
#include "Lamps.h"
#include "strel.h"
#include "static.h"
#include "line.h"
#include "gorl.h"
#include "f.h"
#include "stan.h"
#include "Polig.h"
#include "Y_STREL.h"
#include "Gor_Elem.h"
#include "LampExtDraw.h"
#include "EnergUnit.h"

TSetCommBufFunc SetCommBuf = NULL;
void SetSetCommBufFunc(TSetCommBufFunc ASetCommBuf)
{
    SetCommBuf = ASetCommBuf;
}


TEachAComp EachACompPreFun = 0;
TEachAComp EachACompPostFun = 0;
TEachAComp EachACompStanPreFun = 0;
TEachAComp EachACompStanPostFun = 0;

TEachAComp MakeNewComp = 0;

FILE*      CurStanFile = 0;
long int FTellPos = 0;



PAComp VisibleArray::New(TYP type)
{
    try {
        PAComp RT = NULL;
        switch (type) {
        case    GORL:RT=new Gorl();
            break;
        case    WAY:RT= new Way();
            break;
        case   PLOT:RT= new Plot();
            break;
        case   NAME:RT= new Name();
            break;
        case   MESS:RT= new Mess();
            break;
        case  POIN:RT= new APoint();
            break;
        case   FISH:RT= new Stn();
            break;
        case FISH_R:RT= new StnR();
            break;
        case FISH_L:RT= new StnL();
            break;
        case   BLOK:RT= new Blok();
            break;
        case   INFO:RT= new Info();
            break;
        case   NAPR:RT= new Napr();
            break;
        case  SIG_R:RT= new Svet_R();
            break;
        case  SIG_L:RT= new Svet_L();
            break;
        case GORL_R:RT= new Gorl_R();
            break;
        case GORL_L:RT= new Gorl_L();
            break;
        case  SWRT :RT=new SwRTop();
            break;
        case  SWLT :RT=new SwLTop();
            break;
        case  SWLB :RT=new SwLBot();
            break;
        case  SWRB :RT=new SwRBot();
            break;
        case  SWrt :RT=new SRTop();
            break;
        case  SWlt :RT=new SLTop();
            break;
        case  SWlb :RT=new SLBot();
            break;
        case  SWrb :RT=new SRBot();
            break;
        case  SWL  :RT=new Line() ;
            break;
        case  SWKB :RT=new KBot() ;
            break;
        case  SWKT :RT=new KTop();
            break;
        case  SzT  :RT=new SzTop();
            break;
        case  SzB  :RT=new SzBot();
            break;
        case  LAMP :RT=new Lamp();
            break;
        case  ASN  :RT=new Asn();
            break;
        case  KRIV :RT=new Kriv();
            break;
        case  OVER :
            RT = new Over();

//      RT = (Comp *)malloc( sizeof(Over));
            break;
        case  NOMER:RT= new Nomer();
            break;
        case  TUPIC:RT= new Tupic();
            break;
        case  BL_UH:RT= new Bl_uh();
            break;
        case  LAM4 :RT= new Lam4();
            break;

        case  STIK :RT= new Stik();
            break;
        case  ELEKTR:RT= new Elektr();
            break;
        case  PLATF :RT= new Platf();
            break;

        case   ENGL1:RT=new   Engl1()  ;
            break;
        case   ENGL2:RT=new   Engl2()  ;
            break;
        case  XBOST1:RT=new   Xbost1() ;
            break;
        case  XBOST2:RT=new   Xbost2() ;
            break;
        case  XBOST3:RT=new   Xbost3() ;
            break;
        case  XBOST4:RT=new   Xbost4() ;
            break;
        case    KUS1:RT=new   Kus1()   ;
            break;
        case    KUS2:RT=new   Kus2()   ;
            break;

        case    P_SVE:RT=new   P_Sve() ;
            break;
        case    BASH: RT=new   Bash()  ;
            break;
        case  SWrtW :RT=new SRTopW();
            break;
        case  SWltW :RT=new SLTopW();
            break;
        case  SWlbW :RT=new SLBotW();
            break;
        case  SWrbW :RT=new SRBotW();
            break;

        case  SUPERLAMP2 :RT=new SuperLamp2(); break;
        case  Y_STREL_1 :RT=new TY_Strel_1();  break;
        case  Y_STREL_2 :RT=new TY_Strel_2();  break;
        case  Y_STREL_3 :RT=new TY_Strel_3();  break;
        case  Y_STREL_4 :RT=new TY_Strel_4();  break;
        case  Y_STREL_5 :RT=new TY_Strel_5();  break;
        case  Y_STREL_6 :RT=new TY_Strel_6();  break;

        case  LED :RT=new TLED(); break;

        case  G_STREL_Y :RT=new tG_Strel_Y(); break;
        case  G_STREL_1 :RT=new tG_Strel_1(); break;
        case  G_RC      :RT=new tG_RC();    break;
        case  G_ZAMI    :RT=new tG_ZAMI();  break;
        case  G_ZKR     :RT=new tG_ZKR();   break;
        case  G_ZAMP    :RT=new tG_ZAMP();  break;
        case  G_TPLABEL :RT=new tG_TPLABEL();  break;
        case  G_OTCLABEL:RT=new tG_OTCLABEL();  break;
        case  G_KZP     :RT=new tG_KZP();  break;
        case  G_OSY     :RT=new tG_OSY();  break;
        case  G_STREL_2 :RT=new tG_Strel_2(); break;

        case  COMMLMP  :RT=new CommLmp();  break;
        case  DTGLMP  :RT=new DtgLmp();  break;
        case  VERSION :RT=new Version();  break;
        case  LOG_LAMP:RT=new tLOG_LAMP();  break;
        case  LINI2:RT=new Lini2();  break;
        case  SUBSTATION:RT=new SubStation();  break;
        case  LED30 :RT=new TLED30(); break;
        case  E_OBJ :RT=new TE_OBJ(); break;
        case  G_KZP2 :RT=new tG_KZP2(); break;
        case  G_RC_2 :RT=new tG_RC_2(); break;


        default:
            Qui("����������� ��� �������� � *.sta ", 1, type);
            break;
        }
        if (MakeNewComp && RT) MakeNewComp(RT);
        if (!RT) {
            Qui("����� ���� ��� ���� �� ����� ���� %)", 1, 0);
            return NULL;
        } else    {
            RT->pr = 0;
            RT->AO = pStation->AO;
            RT->pVisibleArray = this;
            return RT;
        }

    } catch (...) {
        Qui("������ ������������ ", 1, type);
    }
    return NULL;
}



VisibleArray::VisibleArray(int ArraySize, Station * pAStation)
{
    pStation = pAStation;
    RTGorlCnt = 0;
}

_fastcall VisibleArray::~VisibleArray()
{
    RemoveAll();
}


int VisibleArray::Add(PAComp ptr)
{
    vObjPtr.push_back(ptr);
    ptr->pVisibleArray = this;
    return vObjPtr.size();
}
int  VisibleArray::Insert(PAComp ptr, int p)
{
    vObjPtr.insert(vObjPtr.begin() + p, ptr);
    ptr->pVisibleArray = this;
    return vObjPtr.size();
}

int VisibleArray::Remove(int p)
{
    if (vObjPtr.size() <= p) return 0;
    PAComp ac =   vObjPtr.at(p);
    if (ac != NULL) {
        delete ac;
    }
    vObjPtr.erase(vObjPtr.begin() + p);
    return 1;
}


void VisibleArray::RemoveAll()
{
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) delete(*i);
    vObjPtr.clear();

}

void __fastcall tracecoord(int x, int y);
void VisibleArray::Show(PAComp ac)
{
    if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
            ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) {
        //������ �����
        tracecoord(ac->X*MUL_X + _X_, ac->Y*MUL_Y + _Y_);
        return;
    }
    if (EachACompPreFun) EachACompPreFun(ac);
    ac->Show();
    if (EachACompPostFun) EachACompPostFun(ac);

}


/*
void VisibleArray::Get(int Number)
{
if(Number<1 || Number>vObjPtr->Count)
  return;
((PAComp)vObjPtr->Items[Number-1])->Get();
}
void VisibleArray::Set(int Number)
{
if(Number<1 || Number>vObjPtr->Count)
  return;
((PAComp)vObjPtr->Items[Number-1])->Set();
}
*/
PAComp VisibleArray::GetObjPtr(int p)
{
    if (p < 0 || p >= vObjPtr.size())  return NULL;
    return vObjPtr.at(p);
}
PAComp VisibleArray::SetObjPtr(int p, PAComp ac)
{
    PAComp ac2 = vObjPtr.at(p);
    vObjPtr.at(p) = ac;
    return ac2;
}

void VisibleArray::Move(PAComp ac, int DeltaX, int DeltaY)
{
    ac->Move(DeltaX, DeltaY);
}

void VisibleArray::ShowAll()
{
    PAComp ac;
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) {
        ac = (*i);
        if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG))) continue;
        Show((ac));
    }
}

void VisibleArray::ShowLayer(int Layer)
{
    PAComp ac;
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) {
        ac = (*i);
        if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) || ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) continue;
        ac->ShowLayer(Layer);
    }
}
void VisibleArray::GoAll()
{
    if (vObjPtr.size() == 0) return;
    TvObjPtr::iterator b = vObjPtr.begin();
    TvObjPtr::iterator e = vObjPtr.end();
    PAComp ac;

    if ((*b)->GetType() == GORL)b = e - RTGorlCnt;
    for (TvObjPtr::iterator i = b; i != e; ++i) {
        ac = (*i);
        if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT)))
            continue;
        //if ((ac->ExtPriz.NoShowExtInfo==1)&&(!bShowExtInfo))  continue ;
        if (EachACompPreFun) EachACompPreFun(ac);
        // ������ ����� ������� ��� �����!
        ClearBgiCoverRect();
        ac->Go();
        ac->RCT = GetBgiCoverRect();
        if (EachACompPostFun) EachACompPostFun(ac);

    }
}


int VisibleArray::TstXY(int x, int y)
{
    if (vObjPtr.size() == 0) return 0;

    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i)(*i)->TstXY(x, y);
    return 0;
}


void VisibleArray::ConnectAll()
{
    PGorl G;
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) {
        G = dynamic_cast<PGorl>((*i));
        G->Connect();
    }
}

void VisibleArray::HideAll()
{
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i)(*i)->Hide();
}
void VisibleArray::MoveAll(int DeltaX, int DeltaY)
{
    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) Move((*i), DeltaX, DeltaY);
}
int VisibleArray::GetArraySize()
{
    return vObjPtr.size();
}


int VisibleArray::LoadAll(int NALL, FILE *file, int ut)
{
    PGorl Member;
    PAComp G;
    TYP type;
    CurStanFile = file;
    for (int count = 0; count < NALL;   count++) {
        if (ut != GORE) {
            FTellPos = ftell(file);
            fread(&MEM, sizeof(AMemory), 1, file);
            //�������������� ���
            if ((MEM.ExtPriz.MEM2)) {
                if (count == NALL) {
                    MEM.ExtPriz.MEM2 = 0;
                } else {
                    fread(&MEM2, sizeof(AMemory), 1, file);
                    // ��������� �� �����
                    if ((MEM2.type != 29) || (MEM2.name[0] != '~')) {
                        fseek(file, -sizeof(AMemory), SEEK_CUR);
                        memset(&MEM2, 0, sizeof(MEM2));
                        MEM.ExtPriz.MEM2 = 0;
                    } else {
                        count++;
                    }
                }
            }
            type = (TYP)MEM.type;
            G = New(type);
            if (!G)
                return -1;
            Add(G);
            G->Set();
        } else {
            Member = (PGorl)(New(GORL));
            Add(Member);
            Member->Load(file);
            Member->pr = 0;
        }
    }
    return 1;
}

int VisibleArray::SaveAll(FILE *file, int ut)
{
    PGorl Member;
//Lamp *Lmp;
    PAComp G;
    int cnt = vObjPtr.size();
    TvObjPtr::iterator b = vObjPtr.begin();
    TvObjPtr::iterator e = vObjPtr.end();
    if ((cnt >= 2) && (ut == GORE)) e = e - RTGorlCnt;
    for (TvObjPtr::iterator i = b; i != e; ++i) {
        if (ut != GORE) {
            G = (*i);
            memset(&MEM, 0, sizeof(MEM));
            memset(&MEM2, 0, sizeof(MEM2));
            G->Get();


            fwrite(&MEM, sizeof(AMemory), 1, file);
            //�������������� ���
            if ((MEM.ExtPriz.MEM2) && (MEM2.type == 29) && (MEM2.name[0] == '~')) {
                fwrite(&MEM2, sizeof(AMemory), 1, file);
            }
            //  if(MEM.type == LAMP){
//            Lmp = (Lamp*)G;
//            if(fileTU!=0)
//            fprintf(fileTU,"%d %d %d %d \n",&Lmp->TypKp,&Lmp->NKp,&Lmp->NGr,&Lmp->NOb);
            //  }

        } else {
            Member = dynamic_cast<PGorl>((*i));
            Member->Save(file);
        }
    }
    return 1;
}


void VisibleArray::ClearAll(void)
{
    PAComp ac;

    for (TvObjPtr::iterator i = vObjPtr.begin(); i != vObjPtr.end(); ++i) {
        ac = (*i);
        if (ac->GetType() != ASN) ac->Clear();
    }
}

int VisibleArray::IndexOf(PAComp ac)
{
    TvObjPtr::iterator i = std::find(vObjPtr.begin(), vObjPtr.end(), ac);
    if (i == vObjPtr.end()) return -1;
    return i - vObjPtr.begin();


}
