//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "APch.h"

#include <inifiles.hpp>
#include "YchParams.h"
#include "actools.h"
#include "CompHint.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


bool bLoadYchParams = true;





bool __fastcall AOReadFromIni(void * pFI, String Sect, TAntOpt * AO)
{

    TIniFile * FI = (TIniFile *)pFI;

    TAntOpt AA;
    if (FI == NULL) return false;
    if (Sect == "") Sect = "ANTHONY";
    AA.TW = FI->ReadInteger(Sect, "TW", 0);

    AA.MaxX = FI->ReadInteger(Sect, "MaxX", AA.MaxX);
    AA.MaxY = FI->ReadInteger(Sect, "MaxY", AA.MaxY);

    AA.LUDOCHKA = FI->ReadInteger(Sect, "LUDOCHKA", 0);
    AA.NumTch = FI->ReadInteger(Sect, "NumTch", 0);
    AA.NumTchBG = FI->ReadBool(Sect, "NumTchBG", AA.NumTchBG);
    AA._2X2_ = FI->ReadInteger(Sect, "_2X2_", 0);
    AA.FLAG_POINT_NUMBER = FI->ReadBool(Sect, "FLAG_POINT_NUMBER", false);
    AA.FLAG_POINT_REVERS = FI->ReadBool(Sect, "FLAG_POINT_REVERS", false);
    AA._NAZVA_ = FI->ReadInteger(Sect, "_NAZVA_", 8);
    //AA.DELTA_CHAN=FI->ReadInteger(Sect,"DELTA_CHAN",0);
    AA.Sdv_nazv = FI->ReadInteger(Sect, "Sdv_nazv", 0);
    AA.SVET_LIM = FI->ReadInteger(Sect, "SVET_LIM", 0);


    AA.DNC_ENERG = FI->ReadBool(Sect, "DNC_ENERG", false);
    AA.TRAINNUM = FI->ReadBool(Sect, "TRAINNUM", false);
    AA.TN_Ver = FI->ReadInteger(Sect, "TN_Ver", 1);
    //AA.FISHKI_GLH=FI->ReadBool(Sect,"FISHKI_GLH",false);
    AA.ENERG = FI->ReadInteger(Sect, "ENERG", 0);


    AA.Ost32Yes = FI->ReadInteger(Sect, "Ost32Yes", 0);
    AA.TypPere = FI->ReadInteger(Sect, "TypPere", 0);
    AA.TypLamp = FI->ReadInteger(Sect, "TypLamp", 0);
    AA.TypName = FI->ReadInteger(Sect, "TypName", 0);
    AA.TypRAMK = FI->ReadInteger(Sect, "TypRAMK", 0);

    bShowExtInfo = FI->ReadBool(Sect, "bShowExtInfo", false);
    AA.bNoShowMSV = FI->ReadBool(Sect, "bNoShowMSV", AA.bNoShowMSV);
    AA.bNoShowPSV = FI->ReadBool(Sect, "bNoShowPSV", AA.bNoShowPSV);
    AA.bShowUstETTMarshrutsOnly_1 = FI->ReadBool(Sect, "bShowUstETTMarshrutsOnly_1", AA.bShowUstETTMarshrutsOnly_1);
    AA.bShowUstETTMarshruts = FI->ReadBool(Sect, "bShowUstETTMarshruts", AA.bShowUstETTMarshruts);
    AA.bShowInfStat = FI->ReadBool(Sect, "bShowInfStat", AA.bShowInfStat);
    AA.bNewNeisprPer = FI->ReadBool(Sect, "bNewNeisprPer", AA.bNewNeisprPer);

    AA.USE_GORL_OTCECH = FI->ReadBool(Sect, "USE_GORL_OTCECH", AA.USE_GORL_OTCECH);
    AA.DopMashtab = FI->ReadInteger(Sect, "DopMashtab", 0);

    AA.TRAINNUM_INVERS = FI->ReadBool(Sect, "TRAINNUM_INVERS", AA.TRAINNUM_INVERS);
    AA.bDopPriznak = FI->ReadBool(Sect, "bDopPriznak", AA.bDopPriznak);

    strncpy(AA.ENG_PackName, FI->ReadString(Sect, "ENG_PackName", AA.ENG_PackName).c_str(),sizeof(AA.ENG_PackName)-1);
    strncpy(AA.Name, FI->ReadString(Sect, "Name", "").c_str(),sizeof(AA.Name)-1);

    AA.bPodgonSvet = FI->ReadBool(Sect, "bPodgonSvet", AA.bPodgonSvet);

    AA.bShowInfStatAll = FI->ReadBool(Sect, "bShowInfStatAll", AA.bShowInfStatAll);

    AA.TsOffColor = FI->ReadInteger(Sect, "TsOffColor", BIRUZOVIJ);
    AA.bNumStrelColor = FI->ReadBool(Sect, "bNumStrelColor", AA.bNumStrelColor);

    AA.bEmbeddedSubStation = FI->ReadBool(Sect, "bEmbeddedSubStation", AA.bEmbeddedSubStation);
    AA._E_def_WK[0] = FI->ReadInteger(Sect, "_E_def_WK[0]", AA._E_def_WK[0]);
    AA._E_def_WK[1] = FI->ReadInteger(Sect, "_E_def_WK[1]", AA._E_def_WK[1]);
    AA._E_def_FontsSz[0] = FI->ReadInteger(Sect, "_E_def_FontsSz[0]", AA._E_def_FontsSz[0]);
    AA._E_def_FontsSz[1] = FI->ReadInteger(Sect, "_E_def_FontsSz[1]", AA._E_def_FontsSz[1]);

    strncpy(AA.EttReciveName, FI->ReadString(Sect, "EttReciveName", "").c_str(),sizeof(AA.EttReciveName));

    if (AO != NULL) *AO = AA;

    // ACOMPHINT ÎÁÙÈÉ ÄËß ÂÑÅÕ
     ACOMPHINT.WidthDef=FI->ReadInteger(Sect, "ACOMPHINT_WidthDef",300);
     ACOMPHINT.HeightDef=FI->ReadInteger(Sect,"ACOMPHINT_HeightDef",60);
     ACOMPHINT.FontSize=FI->ReadInteger(Sect, "ACOMPHINT_FontSize",16);


    return true;
}

bool __fastcall AOWriteToIni(void * pFI, String Sect, TAntOpt * AO)
{
    TIniFile * FI = (TIniFile *)pFI;
    TAntOpt AA;
    if (FI == NULL) return false;
    if (Sect == "") Sect = "ANTHONY";
    if (AO != NULL) AA = *AO;
    FI->EraseSection(Sect);
    FI->WriteInteger(Sect, "TW", AA.TW);
    FI->WriteInteger(Sect, "MaxX", AA.MaxX);
    FI->WriteInteger(Sect, "MaxY", AA.MaxY);

    FI->WriteInteger(Sect, "LUDOCHKA", AA.LUDOCHKA);
    FI->WriteInteger(Sect, "NumTch", AA.NumTch);
    FI->WriteBool(Sect, "NumTchBG", AA.NumTchBG);
    FI->WriteInteger(Sect, "_2X2_", AA._2X2_);
    FI->WriteBool(Sect, "FLAG_POINT_NUMBER", AA.FLAG_POINT_NUMBER);
    FI->WriteBool(Sect, "FLAG_POINT_REVERS", AA.FLAG_POINT_REVERS);
    FI->WriteInteger(Sect, "_NAZVA_", AA._NAZVA_);
    //FI->WriteInteger(Sect,"DELTA_CHAN",AA.DELTA_CHAN);
    FI->WriteInteger(Sect, "Sdv_nazv", AA.Sdv_nazv);
    FI->WriteInteger(Sect, "SVET_LIM", AA.SVET_LIM);

    FI->WriteBool(Sect, "DNC_ENERG", AA.DNC_ENERG);
    FI->WriteBool(Sect, "TRAINNUM", AA.TRAINNUM);
    FI->WriteInteger(Sect, "TN_Ver", AA.TN_Ver);

    //FI->WriteBool   (Sect,"FISHKI_GLH",AA.FISHKI_GLH);
    FI->WriteInteger(Sect, "ENERG", AA.ENERG);

    FI->WriteInteger(Sect, "Ost32Yes", AA.Ost32Yes);
    FI->WriteInteger(Sect, "TypPere", AA.TypPere);
    FI->WriteInteger(Sect, "TypLamp", AA.TypLamp);
    FI->WriteInteger(Sect, "TypName", AA.TypName);
    FI->WriteInteger(Sect, "TypRAMK", AA.TypRAMK);


    FI->WriteBool(Sect, "USE_GORL_OTCECH", AA.USE_GORL_OTCECH);
    FI->WriteInteger(Sect, "DopMashtab", AA.DopMashtab);
    FI->WriteBool(Sect, "TRAINNUM_INVERS", AA.TRAINNUM_INVERS);
    FI->WriteBool(Sect, "bShowExtInfo", bShowExtInfo);
    FI->WriteBool(Sect, "bNoShowMSV", AA.bNoShowMSV);
    FI->WriteBool(Sect, "bNoShowPSV", AA.bNoShowPSV);
    FI->WriteBool(Sect, "bShowUstETTMarshruts", AA.bShowUstETTMarshruts);
    FI->WriteBool(Sect, "bShowUstETTMarshrutsOnly_1", AA.bShowUstETTMarshrutsOnly_1);
    FI->WriteBool(Sect, "bShowInfStat", AA.bShowInfStat);
    FI->WriteBool(Sect, "bDopPriznak", AA.bDopPriznak);
    FI->WriteBool(Sect, "bNewNeisprPer", AA.bNewNeisprPer);

    FI->WriteBool(Sect, "bPodgonSvet", AA.bPodgonSvet);
    FI->WriteBool(Sect, "bShowInfStatAll", AA.bShowInfStatAll);

    FI->WriteString(Sect, "ENG_PackName", AA.ENG_PackName);
    FI->WriteString(Sect, "Name", AA.Name);

    FI->WriteInteger(Sect, "TsOffColor", AA.TsOffColor);
    FI->WriteBool(Sect, "bNumStrelColor", AA.bNumStrelColor);

    FI->WriteBool(Sect, "bEmbeddedSubStation", AA.bEmbeddedSubStation);

    FI->WriteInteger(Sect, "_E_def_WK[0]", AA._E_def_WK[0]);
    FI->WriteInteger(Sect, "_E_def_WK[1]", AA._E_def_WK[1]);
    FI->WriteInteger(Sect, "_E_def_FontsSz[0]", AA._E_def_FontsSz[0]);
    FI->WriteInteger(Sect, "_E_def_FontsSz[1]", AA._E_def_FontsSz[1]);

    FI->WriteString(Sect, "EttReciveName", AA.EttReciveName);

    // ACOMPHINT ÎÁÙÈÉ ÄËß ÂÑÅÕ
    FI->WriteInteger(Sect, "ACOMPHINT_WidthDef",  ACOMPHINT.WidthDef);
    FI->WriteInteger(Sect, "ACOMPHINT_HeightDef", ACOMPHINT.HeightDef);
    FI->WriteInteger(Sect, "ACOMPHINT_FontSize",  ACOMPHINT.FontSize);

    return true;
}

bool LoadYchParams(String FileName, TAntOpt * AO)
{
    bool b = false;
    if (!bLoadYchParams) return false;
    try {
        FileName = CommitFile(FileName.c_str());
        if (!FileExists(FileName)) {
            FileName = ExtractFileDir(FileName) + "\\default.ych.ini";
            if (!FileExists(FileName)) return false;
        }
        TIniFile * FI = new TIniFile(FileName);
        b = AOReadFromIni(FI, "", AO);
        if (FI) delete FI;
    } catch (...) {
        b = false;
    }
    return b;
}
bool SaveYchParams(String FileName, TAntOpt * AO)
{
    bool b = false;
    try {
        TIniFile * FI = new TIniFile(FileName);
        b = AOWriteToIni(FI, "", AO);
        if (FI) delete FI;
    } catch (...) {
        b = false;
    }
    return b;

}




