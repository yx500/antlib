
#include "aheaders_cpp.h"
#include "APch.h"

#include <StrUtils.hpp>
#include <typeinfo>
#include "Stan.h"
#include "Comp.h"

#include "Strel.h"
#include "static.h"
#include "line.h"
#include "Gorl.h"
#include "vatempl.h"
#include "Polig.h"
#include <inifiles.hpp>
#include "YchParams.h"
#include "uEXD.h"
#include "actools.h"

#include "EnergUnit.h"
#include "Str_fun.h"
#include "Gor_Elem.h"
#include "uImgContainer.h"
#include "Impuls.h"
#include "uFormula.h"
#include "CompHint.h"

void Init_strel(void);
extern bool DescrCached;

TAntOpt AntOpt0;                    // используется если нет участка( для станции 1ой)
TAntOpt *UsedAntOpt = &AntOpt0;     // для редактора

TEachStan EachStanPostShow=NULL; // внешняя функция для дополнительной прорисовки станции

TAntOpt * GetUsedAntOpt()
{
    return UsedAntOpt;
}
//---------------------------------------------------------------------------
const char* Station::FullFN()
{
    static char FULL_PATH[255];
    memset(FULL_PATH, 0, sizeof(FULL_PATH));
    strncat(FULL_PATH, Sta_Dir, strlen(Sta_Dir));
    strncat(FULL_PATH, Dat->filename, 8);
    strcat(FULL_PATH, ".sta");
    return (filename[0] != 0) ? filename : FULL_PATH ;
}

FILE* Station::_fopen(char *mod)
{
    const char *FN = FullFN();
    return fopen(CommitFile(FN), mod);
}


FILE* Station::_fopenTu(char *mod)
{
    String FN = FullFN();
    FN = ChangeFileExt(FN, ".tu");
    FILE* fileTU = fopen(CommitFile(FN.c_str()) , mod);
    return fileTU;
}
//---------------------------------------------------------------------------
void Station::Adapter()
{

    /* set ych params */

    if (pPoligon != NULL) AO = &pPoligon->AO; else
        AO = &AntOpt0;

    UsedAntOpt = AO;
    AO->SetANTON();

    MUL_X =   Dat->MUL_X[CurrentPicture];
    MUL_Y =   Dat->MUL_Y[CurrentPicture];
    DELTA_Y = 0;
    DELTA_X = 0;
    if (AO->_2X2_) {
        sv_ras_y = sv_ras_y_2d ;
        ras      = ras_2d      ;
        ras_6    = ras_6_2d    ;
        BLOK_Y   = 16;
        SH_WAY   =  6;
        STREL_X  =  8;
        STREL_Y  =  3;
        //   STREL_y  =  2;
        WAY_X    = 24;
        WAY_Y    =  6;
        DL_US    =  4;
        S_WAY_X  =  6;
        S_WAY_Y  =  4;
        SIG_X    = 18;
        SIG_Y    = 20;
    } else {
        sv_ras_y = sv_ras_y_1d ;
        ras      = ras_1d      ;
        ras_6    = ras_6_1d    ;
        BLOK_Y   =  8;
        SH_WAY   =  3;
        STREL_X  =  4;
        STREL_Y  =  3;
        //      STREL_y  =  1;
        WAY_X    = 12;
        WAY_Y    =  3;
        DL_US    =  2;
        S_WAY_X  =  3;
        S_WAY_Y  =  2;
        SIG_X    =  9;
        SIG_Y    = 10;
    }
    if (AO->MaxY > 351) DELTA_Y = 135;                       // NB 480
    if ((AO->MaxY > 351) && (AO->MaxY < 470)) DELTA_Y -= 480 - AO->MaxY;        // NB 460
    if (AO->MaxY > 481) {
        DELTA_Y += 121; DELTA_X = (800 - 640 - 10) / 2;
    }// NB  600
    if ((AO->MaxY > 481) && (AO->MaxY < 590)) DELTA_Y -= 600 - AO->MaxY;        // NB 580

    if (AO->MaxY > 601) {
        DELTA_Y += 168; DELTA_X = (1024 - 640 - 10) / 2;
    }  //NB 768
    if ((AO->MaxY > 601) && (AO->MaxY < 760)) DELTA_Y -= 768 - AO->MaxY; //NB 738

    if (AO->MaxY == 769) {
        DELTA_Y = DELTA_Y - 100; DELTA_X = (1024 - 640 - 10) / 2;
    }  //NB 768

    if ((AO->MaxY > 769) && (AO->MaxY < 1025)) {
        DELTA_Y += (1024 - 768);          //NB 738
        DELTA_Y -= 1024 - AO->MaxY;          //NB 738
//        DELTA_Y = 770;            //NB 738
        DELTA_X = (1280 - 640 - 10) / 2;
    }
    if (AO->MaxY > 1025) {
        DELTA_Y += (1024 - 768);          //NB 738
        DELTA_Y -= 1024 - AO->MaxY + 40;        //NB 738
//        DELTA_Y = 770;            //NB 738
        DELTA_X = (AO->MaxX - 640 - 10) / 2;
    }

    if (AO->MaxY < 430) {
        if (CurrentPicture == LT)
            MUL_Y =  MUL_Y * 2 / 3 ;
        else
            MUL_Y =  MUL_Y - 1;
    }
    _X_   =   Dat->X_begin[CurrentPicture];
    _Y_   =   Dat->Y_begin[CurrentPicture];
    if (AO->MaxY < 430) {
        if (CurrentPicture == LT)
            _Y_ =  _Y_ * 2 / 3 ;
        else
            _Y_ = (int)((((long)_Y_) * 350L) / 480L);
    }
    //void Init_strel(void)
    if (AO->MaxX > 641)sh_y = ras[MUL_Y]; else
        sh_y = ras_6[MUL_Y];
    sh2 = MUL_Y * STREL_Y + sh_y;
    sh = sh2;
    EXD.TN_Ver = AO->TN_Ver;
    DescrCached = false;

}
//---------------------------------------------------------------------------
void Station::Show()
{
    Adapter();
    GoEachACompStanPreFun();
    for (int i = Units_Size - 1; i >= 0; i--) {
        POLE[i]->ShowAll();
    }
    GoEachACompStanPostFun();
    ShowElemsSost();
}
//---------------------------------------------------------------------------
void Station::Hide()
{
    Adapter();
    for (int i = Units_Size - 1; i >= 0; i--) {
        POLE[i]->HideAll();
    }
}
//---------------------------------------------------------------------------
int Station::TstXY(int _x, int _y)
{
    Adapter();
    int d = 0;
    d = POLE[WAYS]->TstXY(_x, _y);
    d = POLE[CEMA]->TstXY(_x, _y);
    return d;
}
extern int ShowTextMode;
//---------------------------------------------------------------------------
void Station::Go()
{
    Adapter();

    GoEachACompStanPreFun();
    extern  int  priznak_pereris_strel_if_change_mu ;
    priznak_pereris_strel_if_change_mu = 0;
    // стираем старые номера
    ShowTrainNumbers(true);


    // забираем ключи новые
    if (AO->ENERG != 0) {
        LampsLSFromNet(this);
    }

    /* Сначала считаем горловины  */
    POLE[0]->GoAll();
    /* Выводим всё ! */
    ShowTextMode = 1;
    for (int i = Units_Size - 1; i >= 1; i--)
        POLE[i]->ShowLayer(-1);
    for (int i = Units_Size - 1; i >= 1; i--) {
        POLE[i]->GoAll();
    }
    for (int i = Units_Size - 1; i >= 1; i--)
        POLE[i]->ShowLayer(+1);
    ShowTextMode = 0;
    MARSHLIST.UpdateState();
    // выводим установленные маршруты
    if (AO->bShowUstETTMarshruts)
        MARSHLIST.ShowUstMarsh(AO->bShowUstETTMarshrutsOnly_1);

    // приходится отдельно рисовать стыки сверху
    if (CurrentPicture == LT) {
        for (int j = 0; j < POLE[CIFR]->GetArraySize(); j++) {
            AComp * ac = POLE[CIFR]->GetObjPtr(j);
            if (ac->GetType() == STIK) {
                ac->StateChanged = true;
                ac->Go();
            }
        }
    }

    // рисуем сверху номера
    ShowTrainNumbers(false);

    // приходится отдельно рисовать text сверху
    for (int j = 0; j < POLE[WAYS]->GetArraySize(); j++) {
        AComp * ac = POLE[WAYS]->GetObjPtr(j);
        if (ac->GetType() == E_OBJ) {
            ((TE_OBJ*) ac)->ShowText();
        }
    }

    GoEachACompStanPostFun();
    ShowElemsSost();
    //ShowElemsTagStr();
    // рисуем сверху Хинты!
    ACOMPHINT.ShowHints(this);
}
//---------------------------------------------------------------------------
void Station::ShowActives()
{
// жестко прорисовываем активные эл-ты
    Adapter();
    GoEachACompStanPreFun();
    POLE[0]->ClearAll(); POLE[0]->GoAll();
    POLE[WAYS]->ClearAll(); POLE[WAYS]->GoAll();
    POLE[STRE]->ClearAll(); POLE[STRE]->GoAll();
    POLE[STRE]->ClearAll(); POLE[STRE]->GoAll();
    GoEachACompStanPostFun();
    ShowElemsSost();
}
//---------------------------------------------------------------------------
void Station::Clear()
{
    for (int i = Units_Size - 1; i >= 0; i--)
        if (POLE[i]) POLE[i]->ClearAll();
}
//---------------------------------------------------------------------------
int  Station::Open(const char *fn)
{
//  Close();
    strncpy(filename, fn, sizeof(filename) - 1);
    strncpy(Dat->filename,
            ChangeFileExt(ExtractFileName(fn), "").c_str(),
            sizeof(Dat->filename) - 1);

    String FN = FullFN();
    if (FN.UpperCase().Pos(".STE") == FN.Length() - 3) {
        return LoadSTE();
    } else {
        return LoadSTA();
    }
}
//---------------------------------------------------------------------------
void  Station::Close()
{
    memset(filename, 0, sizeof(filename));
    memset(name, 0, sizeof(name));
    pPoligon = NULL;
    memset(ChanelOffset, 0, sizeof(ChanelOffset));
    memset(ChanelNames, 0, sizeof(ChanelNames));
    vUseChanelNames.clear();
    //memset(UseChanelNames,0,sizeof(UseChanelNames));
    ID_RP = 0;
    memset(Dat->descriptor, 0, sizeof(Dat->descriptor));
    memset(Dat->filename, 0, sizeof(Dat->filename));
    for (int i = 0; i < Units_Size; i++) {
        if (POLE[i]) delete POLE[i];
        POLE[i] = NULL;
    }


}
//---------------------------------------------------------------------------
String GetPrevDirStr(String FName)    //функция развращает пред.каталог файла
{
    FName = ExtractFileDir(FName);
    ExcludeTrailingBackslash(FName);
    while ((FName.Length() > 0) && (FName[FName.Length()] != '\\')) {
        FName.Delete(FName.Length(), 1);
    }
    return FName;
}
//---------------------------------------------------------------------------
String  GetStrParam(String st, int ind, String DefaultStr);

void  Station::ConnectGorls()
{
    int G_NALL = POLE[GORE]->GetArraySize();
    POLE[GORE]->ConnectAll();
    if ((G_NALL != 0) && (MOD == RD)) {
        PGorl Even_Gorl = (PGorl) POLE[GORE]->New(GORL);
        PGorl Odd_Gorl  = (PGorl) POLE[GORE]->New(GORL);
        Even_Gorl->bVirtual = true;
        Odd_Gorl->bVirtual = true;
        PGorl G;
//   delete Even_Gorl->gorl[0];
//   delete Odd_Gorl->gorl[0];
        Even_Gorl->gorl[0] = NULL;
        Odd_Gorl->gorl[0] = NULL;
        int Even_co = 0;
        int Odd_co = 0;
        //   int _co_=0;
        for (int i = 0; i < G_NALL; i++) {
            G = (PGorl)POLE[GORE]->GetObjPtr(i);

            if (Def_gr(G->gorl[0]->name) == 1) {
                Even_Gorl->gorl[Even_co] = G->gorl[0];
                Even_Gorl->comp[Even_co] = G;
                Even_co++;
            } else {
                Odd_Gorl->gorl[Odd_co] = G->gorl[0];
                Odd_Gorl->comp[Odd_co] = G;
                Odd_co++;
            }
        }
        Even_Gorl->Size_G=Even_co;//  mas = Even_co;
        Odd_Gorl->Size_G=Odd_co;// mas = Odd_co;
        if (Even_co) {
            POLE[GORE]->Add(Even_Gorl); POLE[GORE]->RTGorlCnt++;
        }
        if (Odd_co) {
            POLE[GORE]->Add(Odd_Gorl); POLE[GORE]->RTGorlCnt++;
        }
    }
}
//---------------------------------------------------------------------------
int Station::LoadSTA()
{
    int i;
    FILE *file = NULL;
    int NALL = 0;
    Col_Gorl = 0;
    St_Dat A;

    if ((file = this->_fopen("rb")) == NULL) {
        Qui((String("No file: ") + FullFN()).c_str(), 1, 0);
        return -1;
    }
    fread(&A, sizeof(St_Dat), 1, file);
    if (Dat->descriptor[0] == 0) memcpy(Dat , &A, sizeof(A));

    OpenIniFile();

    for (i = 0; i < Units_Size; i++) {
        if (feof(file)) NALL = 0;
        else   fread(&NALL, sizeof(short int), 1, file);
        if (feof(file)) NALL = 0;

        if (POLE[i])  delete POLE[i];
        if ((!((i == GORE) && (MOD == RD)))) {
            POLE[i] = new VisibleArray(NALL, this);
        }
        if ((i == GORE) && (MOD == RD)) {
            POLE[i] = new VisibleArray(NALL + 2, this);
        }
        if (POLE[i]->LoadAll(NALL, file, i) < 0) {
            WriteToErr((String("Bad file: ") + FullFN()).c_str());
            return -1;
        }
    }

    ConnectGorls();

    fclose(file);
    file = NULL;

// Пытаемся открыть маршруты
    String stFN = FullFN();
    String stDir = GetPrevDirStr(stFN);
    stFN =  stDir + "ETT\\" + ExtractFileName(stFN);
    stFN = ChangeFileExt(stFN, ".csv");
    MARSHLIST.LoadFromCSV(stFN);
    MARSHLIST.ConnectToStanSTA(this);
    Connect_stNext();
    return 1;
};
//---------------------------------------------------------------------------
int Station::SaveAs(const char * NewFileName)
{
    strncpy(filename, NewFileName, sizeof(filename) - 1);
    strncpy(Dat->filename,
            ChangeFileExt(ExtractFileName(NewFileName), "").c_str(),
            sizeof(Dat->filename) - 1);
    return Save();
}
//---------------------------------------------------------------------------
int Station::Save()
{
    String FN = FullFN();
    FN = FN.UpperCase();
    if (FN.Pos(".STE") == FN.Length() - 3) {
        return SaveSTE();
    } else {
        return SaveSTA();
    }
}
//---------------------------------------------------------------------------
int Station::SaveSTA()
{
    int NALL = 0;
    FILE *file = this->_fopen("wb");
    if (file == NULL) return -1;
    fwrite(Dat, sizeof(St_Dat), 1, file);
    for (int i = 0; i < Units_Size; i++) {
        NALL = POLE[i]->GetArraySize();
        if ((NALL >= 2) && (i == GORE)) NALL = NALL - POLE[i]->RTGorlCnt;

        // увеличиваем NALL на кол-во МЕМ2
        if (i != GORE) {
            int cnt = POLE[i]->GetArraySize();
            for (int count = 0; count < cnt;   count++) {
                POLE[i]->GetObjPtr(count)->Get();
                if ((MEM.ExtPriz.MEM2))
                    NALL++;
            }
        }

        fwrite(&NALL, sizeof(short int), 1, file);
        POLE[i]->SaveAll(file, i);
    }
    fclose(file);

    file = NULL;

    return 1;
};
//---------------------------------------------------------------------------
void Station::SetMas(int imul_x, int imul_y)
{
    Dat->MUL_X[CurrentPicture] = imul_x;
    Dat->MUL_Y[CurrentPicture] = imul_y;
}
//---------------------------------------------------------------------------
void Station::SetBegin(int x_, int y_)
{
    Dat->X_begin[CurrentPicture] = x_;
    Dat->Y_begin[CurrentPicture] = y_;
}
//---------------------------------------------------------------------------
Station::Station(char *ifilename)
{
    memset(ElemsSostPacketName,0,sizeof(ElemsSostPacketName));
    memset(ChanelOffset,0,sizeof(ChanelOffset));
    memset(ChanelNames,0,sizeof(ChanelNames));
    ID_RP=0;
    memset(filename,0,sizeof(filename));
    memset(name,0,sizeof(name));


    Dat = new St_Dat;
    AO = &AntOpt0;
    memset(Dat, 0, sizeof(St_Dat));
    for (int i = 0; i < Units_Size; i++)  POLE[i] = NULL;

    //EnergStanLamps=NULL;
    //if (ENERG2) {
    EnergStanLamps = new TEnergStanLamps;
    memset(EnergStanLamps, 0, sizeof(TEnergStanLamps));
    //}
    Close();

    pPoligon = NULL;
    memset(name, 0, sizeof(name));
    ID_RP = 0;
//  memset(Dat->descriptor,0,sizeof(Dat->descriptor));
//  memset(Dat->filename,0,sizeof(Dat->filename));
    if (ifilename) strncpy(Dat->filename, ifilename, 12);
    ETTList=NULL;
    bETTListNotFound=false;



}
//---------------------------------------------------------------------------
Station::~Station()
{
    Close();
    if (Dat) {
        delete Dat;
        Dat = NULL;
    }
    if (ETTList!=NULL) delete ETTList;
    if (EnergStanLamps != NULL) delete EnergStanLamps;
}
//---------------------------------------------------------------------------
AComp *  Station::GetObjByID(unsigned int ObjID)
{
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) if (POLE[i]->GetObjPtr(j)->GetID() == ObjID) return POLE[i]->GetObjPtr(j);
    }
    return NULL;
}
AComp *  Station::GetObjByID_Imp(unsigned int ObjID, int Imp)
{
    AComp * ac;
    int ii = Imp % 1000;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            if ((ObjID != 0) && (ac->GetID() == ObjID)) return ac;
            if ((ac->GetID() == 0) && (ac->impuls_busi % 1000 == ii))return ac;
        }
    }
    return NULL;

}
//---------------------------------------------------------------------------
AComp * Station::Trans(char *uk, int unit)
{
    Strel * pStrel = NULL;
    Element * pElement = NULL;
    if (uk == NULL)return NULL;
    for (int i = 0; i < POLE[unit]->GetArraySize(); i++) {
        if (unit == STRE) {
            pStrel = (Strel *)POLE[STRE]->GetObjPtr(i);
            if (pStrel->nomer == *uk) return pStrel;
        }
        if (unit == CEMA) {
            pElement = (Element *)POLE[CEMA]->GetObjPtr(i);
            if (!strcmp(pElement->name, uk))return pElement;
        }
    }
    return NULL;

}
//---------------------------------------------------------------------------
/*  1..256 (+1)        */
int  GetPacketOffset(int PacketType, String PacketName, String PathNBDRV)
{
    int num, typ, CountWatch, Len;
    String S;
    try {
        PacketName = PacketName.UpperCase();
        if (!FileExists(PathNBDRV))return 0;
        std::ifstream fil(PathNBDRV.c_str());
        if (!fil.is_open())  return 0;
        fil >> num;
        for (int i = 0; i < num && fil.good(); i++)  {
            fil >> typ;
            fil >> CountWatch >> Len;
            if ((typ < 0) || (typ >= 256))  return -1;
            if (CountWatch >= 256) return -1;
            for (int j = 0; j < CountWatch; j++)  {
                char str[20];
                fil >> std::setw(19) >> str; str[19] = 0;
                S = String(str).UpperCase();
                if ((S.AnsiCompare(PacketName) == 0) && (PacketType == typ))
                    return j + 1;
            }
        }
    } catch (...) {}
    return 0;
}

TGetPacketOffset CustomGetPacketOffset = 0;
//---------------------------------------------------------------------------
bool Station::OpenIniFile()
{
    memset(ChanelNames, 0, sizeof(ChanelNames));
    try {
        String FN = FullFN();
        FN = ChangeFileExt(FN, ".ini");
        FN = CommitFile(FN.c_str());
        if (!FileExists(FN)) return false;
        TIniFile * FI = new TIniFile(FN);
        ID_RP = FI->ReadInteger("MAIN", "ID_RP", 0);

        TStringList * SLChanels = new TStringList();
        FI->ReadSectionValues("CHANELS", SLChanels);
        ReadChanelsInfo(SLChanels);
        delete SLChanels;

        /*if (FI->SectionExists("CHANELS")){
           //* Грузим смещения  *
           String PacketName;
           for (int i=1;i<255;i++){
               PacketName=FI->ReadString("CHANELS",IntToStr(i),"");
               if (PacketName!=""){
                  strncpy(ChanelNames[i], PacketName.c_str(),11);
                  if (CustomGetPacketOffset!=NULL) ChanelOffset[i]=CustomGetPacketOffset(1,PacketName.c_str(),i)*1000; else
                                                   ChanelOffset[i]=GetPacketOffset(1,PacketName,NBDRV_Path)*1000;
                  //* если не можем найти смещение  *
                  if (MOD==ED)
                     if (ChanelOffset[i]==0) ChanelOffset[i]=i*1000;


               }
           }
        }   */
        delete FI;
        return true;
    } catch (...) {}
    return false;
}
bool GetNumberRct(AComp *AC, int &X, int &Y, int Width, int Height, int direct);// out_num.cpp
TColor GetTNBrushClr(int NUMBER);           // out_num.cpp

void GenerateTN(int NUMBER, int X, int Y, TColor TNCOLOR, int direct, AComp * AC);
void * GetTNData(const char * StaFN);
//---------------------------------------------------------------------------
int Station::UpdateState()
{
    int res = 0;
    AComp * ac;
    // забираем ключи новые
    if (AO->ENERG != 0) {
        LampsLSFromNet(this);
    }
    /* Сначала считаем горловины  */
    POLE[0]->GoAll();

    for (int i = 1; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            ac->StateChanged = false;
            ac->UpdateState();
            if (ac->StateChanged)
                res++;
        }
    }
    return res;
}
//---------------------------------------------------------------------------
AComp *  Station::GetObjByName_Unit(const char * CompName, int unit)
{
    if (strlen(CompName) == 0) return NULL;
    AComp * ac;
    char * cn;
    for (int i = 0; i < Units_Size; i++) {
        if ((unit == -1) || (unit == i)) {
            for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
                ac = POLE[i]->GetObjPtr(j);
                cn = ac->GetName();
                if (strcmp(CompName, cn) == 0) return ac;
            }
        }
    }
    return NULL;

}
//---------------------------------------------------------------------------
AComp *  Station::GetObjByName_InTypes(const char * CompName, TYP *Types, int TypesCnt)
{
    AComp * ac;
    TYP t;
    char * cn;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            cn = ac->GetName();
            t = ac->GetType();
            for (int k = 0; k < TypesCnt; k++) {
                if (t == Types[k]) {
                    if ((CompName == 0) || (strcmp(CompName, cn) == 0)) return ac;
                    break;
                }
            }
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
void Station::ShowTrainNumbers(bool bHide)
{
    //Adapter();
    // стираем пропавшие номера
    if ((TRAINNUM_SHOW) && (AO->TRAINNUM)) {
        EXD.TN_PrepareDoublTNFilter();

        AComp * ac;
        for (int i = 1; i < Units_Size; i++) {
            for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
                ac = POLE[i]->GetObjPtr(j);
                if (bHide)
                    ac->HideTrainNumber(); else
                    ac->ShowTrainNumber();
            }
        }
    }
}

extern T_GetSigName_Func _GetSigName_Func;
/*
static TImpPropNamesInfo _II;
bool Station::GetObjByImpulsName(String &impname, String & respropname, int &resimpabsnumber)
{
    AComp * ac;
    static String _S;
    if (_GetSigName_Func == NULL) return false;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            _GetImpPropNamesInfo(ac, _II);
            for (int ii = 0; ii < _II.ImpCount; ii++) {
                if ((_II.RealOffset[ii] == 0) || (_II.RealOffset[ii] == -1) || (_II.RealOffset[ii] == -2)) continue;
                _S = _GetSigName_Func(_II.RealOffset[ii]);
                if (_S == impname) {
                    respropname = _II.ImpName[ii];
                    resimpabsnumber = _II.RealOffset[ii];
                    return true;
                }
            }
        }
    }
    return false;

}
*/
//---------------------------------------------------------------------------
static String _StanPropName[14] = {
    "цфNom"   ,          // 0
    "смfilename" ,       // 1
    "смdescriptor"   ,   // 2
    "цфMUL_X1"   ,       // 3
    "цфMUL_Y1"  ,        // 4
    "цфX_begin1" ,       // 5
    "цфY_begin1",        // 6
    "цфMUL_X2"   ,       // 7
    "цфMUL_Y2"  ,        // 8
    "цфX_begin2" ,       // 9
    "цфY_begin2" ,       // 10
    "цфObjCnt",          // 11
    "смFullName",         // 12
    "смElemsSostPacketName",         // 13
};

void Station::GetPropMap(TPropMap &m)
{
    // считаем обьекты
    int NALL = 0;
    int cnt = 0;
    for (int i = 0; i < Units_Size; i++) {
        NALL = POLE[i]->GetArraySize();
        if ((NALL >= 2) && (i == GORE)) NALL = NALL - POLE[i]->RTGorlCnt;
        cnt += NALL;
    }
    m.put(_StanPropName[0], Dat->Nom);
    m.put(_StanPropName[1], Dat->filename);
    m.putOEM(_StanPropName[2], Dat->descriptor);
    m.put(_StanPropName[3], Dat->MUL_X[0]);
    m.put(_StanPropName[4], Dat->MUL_Y[0]);
    m.put(_StanPropName[5], Dat->X_begin[0]);
    m.put(_StanPropName[6], Dat->Y_begin[0]);
    m.put(_StanPropName[7], Dat->MUL_X[1]);
    m.put(_StanPropName[8], Dat->MUL_Y[1]);
    m.put(_StanPropName[9], Dat->X_begin[1]);
    m.put(_StanPropName[10], Dat->Y_begin[1]);
    m.put(_StanPropName[11], cnt);
    m.put(_StanPropName[12], name);
    m.put(_StanPropName[13], ElemsSostPacketName);

}

void Station::SetPropMap(TPropMap &m)
{
    Dat->Nom           = m.geti(_StanPropName[0]);
    strncpy(Dat->filename, m.get(_StanPropName[1]).c_str(), 13);
    strncpy(Dat->descriptor, m.getOEM(_StanPropName[2]).c_str(), 13);
    Dat->MUL_X[0]      = m.geti(_StanPropName[3]);
    Dat->MUL_Y[0]      = m.geti(_StanPropName[4]);
    Dat->X_begin[0]    = m.geti(_StanPropName[5]);
    Dat->Y_begin[0]    = m.geti(_StanPropName[6]);
    Dat->MUL_X[1]      = m.geti(_StanPropName[7]);
    Dat->MUL_Y[1]      = m.geti(_StanPropName[8]);
    Dat->X_begin[1]    = m.geti(_StanPropName[9]);
    Dat->Y_begin[1]    = m.geti(_StanPropName[10]);
    strncpy(name, m.get(_StanPropName[12]).c_str(), 255);
    strncpy(ElemsSostPacketName, m.get(_StanPropName[13]).c_str(), 12);

}


const String _objprzS = "Object ";
const String _objprzF = "End_object ";

void WritePmToIni(TPropMap &pm, TCustomIniFile *FI, String SectionName)
{
    TStringList *SL = pm.createStringList();
    SL->Sort();
    for (int i = 0; i < SL->Count; i++)
        FI->WriteString(SectionName, SL->Names[i], SL->Values[SL->Names[i]]);
    delete SL;
//     for ( int i=0; i<pm.GetItemsCount; i++ )
//         FI->WriteString(SectionName,pm.GetKeys(i),pm.GetVal(i));
}
//---------------------------------------------------------------------------
int Station::SaveSTE()
{
    TPropMap pm;
    pm.bNotPutDefault = true;
    AComp * ac;

    //TStringList * SL=new TStringList();
    //int oldmod=MOD;
    //MOD=RD; // надо чтоб лишнее не писалось

    String FN = FullFN();
    if (FileExists(FN))
        unlink(FN.c_str());
    TMemIniFile * FI = new TMemIniFile(FN);

    // Сверху пишем свое
    GetPropMap(pm);
    WritePmToIni(pm, FI, "STATION");

    for (int i = 1; i < 255; i++) {
        if (ChanelNames[i][0] != 0)
            FI->WriteString("STATION", "Chanel_" + IntToStr(i), ChanelNames[i]);
    }
    for (unsigned int i = 0; i < vUseChanelNames.size(); i++) {
        //if (UseChanelNames[i][0]!=0)
        FI->WriteString("STATION", "UseChanel_" + IntToStr(i + 1), IntToStr(vUseChanelNames[i].type) + ";" + String(vUseChanelNames[i].name));
    }

    // пишем обьекты
    int NALL = 0;
    String SectName;
    for (int i = 0; i < Units_Size; i++) {
        NALL = POLE[i]->GetArraySize();
        if ((NALL >= 2) && (i == GORE)) NALL = NALL - POLE[i]->RTGorlCnt;
        for (int j = 0; j < NALL; j++) {
            ac = POLE[i]->GetObjPtr(j);
            pm.clear();
            ac->GetPropMap(pm);
            SectName = "Comp_" + IntToStr(i) + "x" + IntToStr(j);
            FI->WriteString(SectName, "typeid", typeid(*ac).name());
            WritePmToIni(pm, FI, SectName);
        }
    }

    FI->UpdateFile();
    delete FI;
    //MOD=oldmod;

    return 1;
}
//---------------------------------------------------------------------------
void ReadPmFromIni(TPropMap &pm, TCustomIniFile * FI, String SectionName, TStrings * SL)
{
    SL->Clear();
    FI->ReadSectionValues(SectionName, SL);
    String ST;
    for (int i = 0; i < SL->Count; i++) {
        ST = SL->Strings[i];
        pm.putkeyvalst(ST);
    }
}

void Station::ReadChanelsInfo(TStringList * SL)
{
    String stK, PacketName;
    TUseChanelName uname;
    for (int i = 0; i < SL->Count; i++) {
        String ST = SL->Strings[i];
        stK = "";
        PacketName = "";
        int p1 = ST.Pos("=");
        if (p1 > 1) {
            stK = ST.SubString(1, p1 - 1);
            PacketName = ST.SubString(p1 + 1, ST.Length() - p1);
        }

        if (stK.Pos("UseChanel_") == 1) {
            int p = PacketName.Pos(";");
            if (p > 1) {
                uname.type = PacketName.SubString(1, p - 1).ToIntDef(-1);
                PacketName = PacketName.SubString(p + 1, PacketName.Length() - p);
                strncpy(uname.name, PacketName.c_str(), 12);
                vUseChanelNames.push_back(uname);
                if (CustomGetPacketOffset != NULL) CustomGetPacketOffset(uname.type, uname.name, 0);
            }
        } else if (stK.Pos("Chanel_") == 1) {
            int i = stK.SubString(7 + 1, stK.Length() - 7).ToIntDef(-1);
            strncpy(ChanelNames[i], PacketName.c_str(), 12);
            if (CustomGetPacketOffset != NULL) ChanelOffset[i] = CustomGetPacketOffset(1, PacketName.c_str(), i) * 1000; else
                ChanelOffset[i] = GetPacketOffset(1, PacketName, NBDRV_Path) * 1000;
            if (MOD == ED)
                if (ChanelOffset[i] == 0) ChanelOffset[i] = i * 1000;
        } else if (stK.ToIntDef(-1) > 0) {
            int i = stK.ToInt();
            strncpy(ChanelNames[i], PacketName.c_str(), 12);
            if (CustomGetPacketOffset != NULL) ChanelOffset[i] = CustomGetPacketOffset(1, PacketName.c_str(), i) * 1000; else
                ChanelOffset[i] = GetPacketOffset(1, PacketName, NBDRV_Path) * 1000;
            if (MOD == ED)
                if (ChanelOffset[i] == 0) ChanelOffset[i] = i * 1000;

        }
    }
}
//---------------------------------------------------------------------------
int Station::LoadSTE()
{
    TPropMap pm;
    AComp * ac;

    TStringList * SL = new TStringList();
    TStringList * SLsect = new TStringList();
    String FN = FullFN();
    //SL->LoadFromFile(FN);
    TMemIniFile * FI = new TMemIniFile(FN);
    pm.clear();
    int type;
    UNIT unit;
    // ищем сверху свое
    ReadPmFromIni(pm, FI, "STATION", SL);

    SetPropMap(pm);

    /* ----  */

    TStringList * SLChanels = new TStringList();
    FI->ReadSectionValues("STATION", SLChanels);
    ReadChanelsInfo(SLChanels);
    
    delete SLChanels;

    // читаем обьекты
    //cnt=pm.geti(_StanPropName[11]);
    // создаем ватеры
    for (int i = 0; i < Units_Size; i++)
        POLE[i] = new VisibleArray(0, this);

    FI->ReadSections(SLsect);
    String SectName;
    for (int i = 0; i < SLsect->Count; i++) {
        SectName = SLsect->Strings[i];
        if (SectName.Pos("Comp_") != 1) continue;
        pm.clear();
        ReadPmFromIni(pm, FI, SectName, SL);
        type = pm.geti("цфtype");
        ac = POLE[0]->New((TYP)type);
        ac->SetPropMap(pm);
        unit = ac->GetUnit();
        POLE[unit]->Add(ac);
    }

    ConnectGorls();
    delete SL;
    delete SLsect;
    delete FI;

    // Пытаемся открыть маршруты
    String stFN = FullFN();
    String stDir = GetPrevDirStr(stFN);
    stFN =  stDir + "ETT\\" + ExtractFileName(stFN);
    stFN = ChangeFileExt(stFN, ".csv");
    MARSHLIST.LoadFromCSV(stFN);
    MARSHLIST.ConnectToStanSTA(this);
    Connect_stNext();

    if (AO->ENERG != 0) {
        LoadLampsLS(this) ;
    }

    return 1;
}
//---------------------------------------------------------------------------
AComp * Station::SetFocus(unsigned int ObjID, int focus)
{
    AComp * ac = GetObjByID(ObjID);
    if (ac != NULL) {
        if (focus == 1) ac->ExtFocus = 1; else ac->ExtFocus = 2;
        ac->Show();
        return ac;
    }
    return NULL;
}
//---------------------------------------------------------------------------
void Station::Connect_stNext()
{
    AComp * ac;
    tGRC0 * rc;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            Ways *w=dynamic_cast<Ways *>(ac);
            if (w==0)  continue;
            for (int d=0;d<2;d++)
                for (int m=0;m<2;m++) {
                        w->pNext[d][m] =0;
                        if (w->IDnext[d][m]!=0) w->pNext[d][m]=GetObjByID(w->IDnext[d][m]);
                }

            rc = dynamic_cast<tGRC0 *>(ac);
            if (rc == NULL) continue;
            if (rc->stNext[0][0] != "") rc->pNext[0][0] = GetObjByName_Unit(rc->stNext[0][0].c_str() , -1);
            if (rc->stNext[0][1] != "") rc->pNext[0][1] = GetObjByName_Unit(rc->stNext[0][1].c_str() , -1);
            if (rc->stNext[1][0] != "") rc->pNext[1][0] = GetObjByName_Unit(rc->stNext[1][0].c_str() , -1);
            if (rc->stNext[1][1] != "") rc->pNext[1][1] = GetObjByName_Unit(rc->stNext[1][1].c_str() , -1);
            /*if (rc->pNext[0][0]!=NULL)  rc->IDnext[0][0]=rc->pNext[0][0]->ID;
            if (rc->pNext[1][0]!=NULL)  rc->IDnext[1][0]=rc->pNext[1][0]->ID;
            if (rc->pNext[0][1]!=NULL)  rc->IDnext[0][1]=rc->pNext[0][1]->ID;
            if (rc->pNext[1][1]!=NULL)  rc->IDnext[1][1]=rc->pNext[1][1]->ID;*/
        }
    }
}
//---------------------------------------------------------------------------
void Station::GoEachACompStanPreFun()
{
    if (!EachACompStanPreFun) return;
    AComp * ac;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            EachACompStanPreFun(ac);
        }
    }
}
void Station::GoEachACompStanPostFun()
{
    if (EachStanPostShow!=NULL)
       EachStanPostShow(this);
    if (!EachACompStanPostFun) return;
    AComp * ac;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            EachACompStanPostFun(ac);
        }
    }
}
//---------------------------------------------------------------------------
const char * GetImageName(std::string Picture, int  PictureState);
void Station::ShowElemsSost()
{
    if (!AO->bShowInfStatAll) return;
    AComp * ac;
    char * packetname=Dat->filename;
    if (strlen(ElemsSostPacketName)!=0) packetname=ElemsSostPacketName;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            if (ac->GetType() == LED) continue;
            //---
            if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) || ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) continue;
            //---
            TElemCheckState * EI = EXD.EI_GetEI(packetname, ac->GetID());
            if ((EI != NULL) && (EI->state != 0)) {
                const char *szimagename = GetImageName("DEFAULT", EI->state);
                TRect RCT=ac->RCT;
                if (RCT.Width()>40){
                   int w=RCT.Width()-40;
                   RCT.left+=w/2;
                   RCT.right-=w/2;
                }
                if (RCT.Height()>40){
                   int w=RCT.Height()-40;
                   RCT.top+=w/2;
                   RCT.bottom-=w/2;
                }
                drawemf(&RCT, szimagename, CommonAnimationStep % 4);
            }
        }
    }
}

void Station::ShowElemsTagStr()
{
    AComp * ac;

    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            if (ac->GetType() == LED) continue;
            //---
            if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) || ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) continue;
            //---
            if (!ac->Tagstr.empty()){
                String SS=String(ac->Tagstr.c_str());
                setcolor(TXT);
                TRect RCT=ac->RCT;
                OutTextXY(RCT.left,RCT.top,SS.c_str());
            }
        }
    }
}

//---------------------------------------------------------------------------
uint16 Station::SetUnicalID(uint16 ID)
{
    // уже уникум?
    AComp * ac;
    bool unic = true;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            if (ac->GetID() == ID) {
                unic = false; break;
            }
        }
    }
    if (unic)  return ID;
    // Ищем макс за стартом
    uint16 maxID = 0;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            if (ac->GetID() > maxID) maxID = ac->GetID();
        }
    }
    if (maxID >= 0xFFFF) {
        ShowMessage("Максимальное кол-во!");
        return 0;
    }
    return maxID + 1;
}
//---------------------------------------------------------------------------
void Station::for_each_chanel(TGetPacketOffset f)
{
    for (int i = 1; i < 255; i++)
        if (strlen(ChanelNames[i]) != 0) f(1, ChanelNames[i], i);
    for (int i = 0; i < vUseChanelNames.size(); i++)
        f(vUseChanelNames[i].type , vUseChanelNames[i].name, i + 1);
    // добавляем 11
    if (AO->TRAINNUM)
        for (int i = 1; i < 255; i++)
            if (strlen(ChanelNames[i]) != 0) f(11, ChanelNames[i], i);

    // добавляем ENRG
    String STAFN = String(Dat->filename);

    if (AO->ENERG != 0)
        f(8 , STAFN.c_str(), 1);
    // добавляем DIAG
    STAFN = STAFN.UpperCase();
    if (AO->bShowInfStat) {
        STAFN = STAFN + "_0";
        f(31 , STAFN.c_str(), 1);
    }
}
//---------------------------------------------------------------------------

void Station::reassignChanelOffset()
{
     for (int i = 1; i < 255; i++){
        if (strlen(ChanelNames[i]) != 0) {
           if (CustomGetPacketOffset != NULL) ChanelOffset[i] = CustomGetPacketOffset(1, ChanelNames[i], i) * 1000; else
                                              ChanelOffset[i] = GetPacketOffset(1, ChanelNames[i], NBDRV_Path) * 1000;
           if (MOD == ED)
                if (ChanelOffset[i] == 0) ChanelOffset[i] = i * 1000;
        }
     }
}

//-------------------------

int Station::GetStrelkiCount()
{
    int count = 0;
    AComp * ac;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < POLE[i]->GetArraySize(); j++) {
            ac = POLE[i]->GetObjPtr(j);
            switch (ac->GetType()) {
            default: break;
            case Y_STREL_1:
            case Y_STREL_2:
            case Y_STREL_3:
            case Y_STREL_4:
            case G_STREL_Y:
            case G_STREL_1:
            case SWRT:
            case SWLT:
            case SWLB:
            case SWRB:
            case SWrt:
            case SWlt:
            case SWlb:
            case SWrb:
                count++;
                break;
            }
        }
    }
    return count;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

SubStation::SubStation()
        : Element()
{
    substan = NULL;
    bAlreadyEmbedded = false;
    bNoRebuildID=false;
}

void SubStation::UpdateState()
{
    if (substan != NULL)
        substan->UpdateState();

}

void SubStation::Set()
{
    Element::Set();
}


void SubStation::Get()
{
    Element::Get();
}

static String _SubStationPropName[12] = {
    "смSTE_FN",          // 0
    "лгНе_пересч_ID",    // 1
    "смЗам1",            // 2
    "смЗам2",            // 3
    "смЗам3",            // 4
    "смЗам4",            // 5
    "смЗам5",            // 6
    "смЗам6",            // 7
    "смЗам7",            // 8
    "смЗам8",            // 9
    "смЗам9",            // 1
    "смЗам10"            // 11
};

void Replaceacprop(AComp * ac, TPropMap &mrpl)
{
    TPropMap m;
    String pmstr = ac->Tagstr.c_str();
    for (int i = 0; i < mrpl.GetItemsCount(); i++) {
        //String stKey=mrpl.Keys[i];
        //if (
        //    if ()
        pmstr = AnsiReplaceStr(pmstr, mrpl.Keys[i], mrpl.Val[i]);
        //ac->Tagstr.replace() ()
    }
    m.text(pmstr.c_str());
    //ac->SetPropMap(m);
    // хитрозамена
    //ac->GetPropMap(m);
    if (ac->pmRepl != NULL) {
        String pmReplstr = ac->pmRepl->text();
        for (int i = 0; i < mrpl.GetItemsCount(); i++) {
            pmReplstr = AnsiReplaceStr(pmReplstr, mrpl.Keys[i], mrpl.Val[i]);
        }
        TPropMap m2;
        m2.text(pmReplstr.c_str());
        for (int i = 0; i < m2.GetItemsCount(); i++) {
            if (m2.Val[i] != "") {
                String stK = m2.Keys[i];
                String stV = m2.Val[i];
                // а фдруг формула
                if ((stV.Pos("+") > 1) ||
                        (stV.Pos("+") > 1) ||
                        (stV.Pos("*") > 1) ||
                        (stV.Pos("/") > 1)) stV = IntToStr(feFormulaResult(stV.c_str()));
                stK = stK.Delete(1, 1);

                m.put(stK, stV);
            }
        }
    }
    ac->SetPropMap(m);
}

void Replaceactsprop(AComp * ac, int chNFrom, int chNTo, int chD)
{
    TPropMap m;
    String pmstr = ac->Tagstr.c_str();
    m.text(pmstr.c_str());
    String pmNAME, NAME, VALUE;
    TAImpuls AImpuls;
    ac->GetPropMap(m);
    bool bChange = false;
    for (int i = 0; i < m.GetItemsCount(); i++) {
        pmNAME = m.GetKeys(i);
        VALUE = m.GetVal(i);
        if (pmNAME.Pos("тс") == 1) {
            if (VALUE != "000:0000:0:00") {
                AImpuls.FromString(VALUE.c_str());
                if ((AImpuls.Chanel > 0) && (chNFrom > 0) && (AImpuls.Chanel == chNFrom)) {
                    bChange = true;
                    AImpuls.Chanel = chNTo;
                    if (AImpuls.Number >= 0)
                        AImpuls.Number += chD;
                    VALUE = AImpuls.ToString();
                    m.GetVal(i) = VALUE;
                }
            }
        }
    }
    if (bChange)
        ac->SetPropMap(m);



}

void SubStation::GetPropMap(TPropMap &m)
{
    Element::GetPropMap(m);
    int _n = 0;
    m.put(_SubStationPropName[_n++], filename);
    m.put(_SubStationPropName[_n++], bNoRebuildID);

    for (int i = 0; i < 10; i++)
        m.put(_SubStationPropName[_n++], repl[i]);
}
void SubStation::SetPropMap(TPropMap &m)
{
    if (bAlreadyEmbedded)
        return;
    Element::SetPropMap(m);
    int _n = 0;
    char newfilename[13]; memset(newfilename, 0, 13);
    strncpy(newfilename, m.get(_SubStationPropName[_n++]).c_str(), 12);

    bNoRebuildID=m.geti(_SubStationPropName[_n++]);

    for (int i = 0; i < 10; i++)
        strncpy(repl[i], m.get(_SubStationPropName[_n++]).c_str(), 64);

    if (strcmp(newfilename, filename) != 0) {
        strncpy(filename, newfilename,12);
        TGetPacketOffset ACustomGetPacketOffset = CustomGetPacketOffset;
        CustomGetPacketOffset = 0;
        LoadSTE();
        CustomGetPacketOffset = ACustomGetPacketOffset;
    }
    if (substan == NULL)
            return;

    TPropMap mrpl;
    for (int i = 0; i < 10; i++)
        if (strlen(repl[i]) >= 3)
            mrpl.putkeyvalst(repl[i]);
    AComp * ac;


    int ChanelN;
    int ChanelOffset;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
            ac = substan->POLE[i]->GetObjPtr(j);
            Replaceacprop(ac, mrpl);
            ChanelN = impuls_busi / 1000;
            ChanelOffset = impuls_busi % 1000;
            if (ChanelN != 0)
               Replaceactsprop(ac, 1, ChanelN, ChanelOffset);
            ChanelN = impuls_plus / 1000;
            ChanelOffset = impuls_plus % 1000;
            if (ChanelN != 0)
                Replaceactsprop(ac, 2, ChanelN, ChanelOffset);
            ChanelN = impuls_mnus / 1000;
            ChanelOffset = impuls_mnus % 1000;
            if (ChanelN != 0)
                Replaceactsprop(ac, 3, ChanelN, ChanelOffset);

            ChanelN = impuls_kzm / 1000;
            ChanelOffset = impuls_kzm % 1000;
            if (ChanelN != 0)
                Replaceactsprop(ac, 4, ChanelN, ChanelOffset);
            ChanelN = impuls_mu / 1000;
            ChanelOffset = impuls_mu % 1000;
            if (ChanelN != 0)
                Replaceactsprop(ac, 5, ChanelN, ChanelOffset);
        }
    }
    if ((!bNoEmbeddSubStations) && (AO->bEmbeddedSubStation)) {
        bAlreadyEmbedded = true;
        ac = NULL;
        for (int i = 0; i < Units_Size; i++) {
            for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
                ac = substan->POLE[i]->GetObjPtr(j);
                boundRCT.Left = ac->X; boundRCT.Top = ac->Y; boundRCT.Right = ac->X; boundRCT.Bottom = ac->Y;
                break;
            }
        }
        for (int i = 0; i < Units_Size; i++) {
            for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
                ac = substan->POLE[i]->GetObjPtr(j);
                if (boundRCT.Left < ac->X)boundRCT.Left = ac->X;
                if (boundRCT.Right > ac->X)boundRCT.Right = ac->X;
                if (boundRCT.Top < ac->Y)boundRCT.Top = ac->Y;
                if (boundRCT.Bottom > ac->Y)boundRCT.Bottom = ac->Y;
                ac->X += X;
                ac->Y += Y;
                if (bNoRebuildID)
                   ac->ID = Stan()->SetUnicalID(ac->ID); else
                   ac->ID = Stan()->SetUnicalID(10000 + (this->ID % 200) * 200 + ac->ID % 200);
                Stan()->POLE[i]->Add(ac);
                ac->AO = AO;
                ac->pVisibleArray = Stan()->POLE[i];

            }
        }
        for (int i = 0; i < Units_Size; i++) {
            substan->POLE[i]->vObjPtr.clear();
        }
        delete substan;
        substan = NULL;
    }

}

void SubStation::LoadSTE()
{
    String FN = Stan()->FullFN();
    String sFN = ExtractFileDir(FN) + "\\" + String(filename) + ".STE";
    if (substan != NULL)
        delete substan;
    substan = NULL;
    if (!FileExists(sFN)) return;

    substan = new Station("");

    substan->Open(sFN.c_str());
    //substan->Dat=Stan()->Dat;
    substan->AO = Stan()->AO;
    // пересчитываемммммм
    AComp * ac;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
            ac = substan->POLE[i]->GetObjPtr(j);
            break;
        }
    }
    int x0 = ac->X;
    int y0 = ac->Y;
    // сводим к 0
    TPropMap m;
    for (int i = 0; i < Units_Size; i++) {
        for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
            ac = substan->POLE[i]->GetObjPtr(j);
            ac->X -= x0;
            ac->Y -= y0;
            m.clear();
            //ac->Tagstr = m.text();
            ac->GetPropMap(m);
            ac->Tagstr = m.text();

        }
    }



}

TYP  SubStation::GetType()
{
    return SUBSTATION;
}
UNIT SubStation::GetUnit()
{
    return NITK;
}

void  SubStation::Show()
{
    int xx = X * MUL_X + _X_;
    int yy = Y * MUL_Y + _Y_;


    if (substan == NULL) {


    } else {
        if ((!bNoEmbeddSubStations) && (AO->bEmbeddedSubStation)) {
            setcolor(FON);
            line(xx + boundRCT.left*MUL_X, yy + boundRCT.top*MUL_Y, xx + boundRCT.left*MUL_X, yy + boundRCT.top*MUL_Y);
            line(xx + boundRCT.right*MUL_X, yy + boundRCT.bottom*MUL_Y, xx + boundRCT.right*MUL_X, yy + boundRCT.bottom*MUL_Y);
        } else {

            substan->Clear();
            int _X_0 = _X_;
            int _Y_0 = _Y_;
            memcpy(substan->Dat, Stan()->Dat, sizeof(St_Dat));
            _X_ = _X_ + X * MUL_X;
            _Y_ = _Y_ + Y * MUL_Y;
            PAComp ac;

            substan->GoEachACompStanPreFun();
            /* Выводим всё ! */
            for (int i = Units_Size - 1; i >= 1; i--) {
                for (int i = 0; i < Units_Size; i++) {
                    for (int j = 0; j < substan->POLE[i]->GetArraySize(); j++) {
                        ac = substan->POLE[i]->GetObjPtr(j);
                        if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                                ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) continue;
                        //if ((ExtPriz.NoShowExtInfo==1)&&(!bShowExtInfo))  continue ;
                        if (EachACompPreFun) EachACompPreFun(ac);
                        ac->Go();
                        if (EachACompPostFun) EachACompPostFun(ac);
                    }
                }
            }
            _X_ = _X_0;
            _Y_ = _Y_0;
        }
    }
}



/*
bool Station::GetParamsEttItem(unsigned int EventType_ID,int ID_OBJ,int &Visible,int &Act,int &TOShow)
{
     Visible=true;
     Act=0;
     TOShow=5;
     // проверяем есть ли лист?
     if (ETTList==NULL){
        // а загружали уже?
        if (bETTListNotFound) return false;
        bETTListNotFound=true;
        String FN=GetETTLISTFileName(filename);
        ETTList=new TETTList();
        if (!ETTList->Load(FN)){
           delete ETTList;
           ETTList=NULL;
           return false;
        }
     }
     TETTListItem * ei=ETTList->FindItem((TEventType_Class)0, EventType_ID,ID_OBJ);
     if (ei==NULL) return false;
     Visible=ei->Enabled;
     if (ei->Act!=0) Act=ei->Act;
     if (ei->TOShow!=0) TOShow=ei->TOShow;
     return true;
}
*/

