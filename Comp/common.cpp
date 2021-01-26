#include <vcl.h>
#pragma hdrstop


#include "common.h"
#include "Ways.h"
#include "Svet.h"
#include "Lamps.h"
#include "Strel.h"
#include <iostream>
#include <iomanip>



//---------------------------------------------------------------------------
void Qui(char *bf, int, int)
{
    //throw(const char*)bf;
    WriteToErr(bf);
}
//---------------------------------------------------------------------------
void WriteToLog(const std::string& Str)
{
    std::clog << "Log: " << Str.c_str() << std::endl;
}
//---------------------------------------------------------------------------
void WriteToErr(const std::string& Str)
{
    std::cerr << std::endl << "Err: " << Str.c_str() << std::endl << std::endl;
}
//---------------------------------------------------------------------------


void  _GetImpPropNamesInfo(AComp * ac , TImpPropNamesInfo &I)
{
    strncpy(I.CompName, ac->GetName(),sizeof(I.CompName)-1);
    //I.CompName = ac->GetName();

    strncpy(I.CompType, Com_Nam[ac->GetType()],sizeof(I.CompType)-1);
    //I.CompType =String(st1);
    I.ImpCount = 0;


    switch (ac->GetType()) {
    default     :  {
        I.ImpCount = 1;
        strcpy(I.ImpName[0], "impuls_busi");       I.RealOffset[0] = ac->GetRealImp(ac->impuls_busi);
        /*strcpy(I.ImpName[1],"impuls_plus");       I.RealOffset[1]=ac->GetRealImp(ac->impuls_plus  );
        strcpy(I.ImpName[2],"impuls_mnus");       I.RealOffset[2]=ac->GetRealImp(ac->impuls_mnus  );
        strcpy(I.ImpName[3],"impuls_kzm");        I.RealOffset[3]=ac->GetRealImp(ac->impuls_kzm);
        strcpy(I.ImpName[4],"impuls_kmu");        I.RealOffset[4]=ac->GetRealImp(ac->impuls_kmu);
        strcpy(I.ImpName[5],"impuls_mu");         I.RealOffset[5]=ac->GetRealImp(ac->impuls_mu);
        */
    } break;
    case WAY    : {
        Way * way = dynamic_cast<Way *>(ac);
        I.ImpCount = 2;
        strcpy(I.ImpName[0], "«¿Õﬂ“»≈");   I.RealOffset[0] = way->GetRealImp(way->impuls_busi);
        strcpy(I.ImpName[1], "«¿Ã€ ¿Õ»≈"); I.RealOffset[1] = way->GetRealImp(way->impuls_plus);
    } break;
    case PLOT   : {
        Plot * plot = dynamic_cast<Plot *>(ac);
        switch (plot->masy) {
        default : I.ImpCount=2;
            strcpy(I.ImpName[0], "«¿Õﬂ“»≈");       I.RealOffset[0] = plot->GetRealImp(plot->impuls_busi);
            strcpy(I.ImpName[1], "Õ≈»—œ–¿¬ÕŒ—“‹"); I.RealOffset[1] = plot->GetRealImp(plot->impuls_plus);
            break;
        case 1:
        case 2:   I.ImpCount=4;
            strcpy(I.ImpName[0], "«¿Õﬂ“»≈ 1");       I.RealOffset[0] = plot->GetRealImp(plot->impuls_busi);
            strcpy(I.ImpName[1], "Õ≈»—œ–¿¬ÕŒ—“‹");   I.RealOffset[1] = plot->GetRealImp(plot->impuls_plus);
            strcpy(I.ImpName[2], "«¿Õﬂ“»≈ 2");       I.RealOffset[2] = plot->GetRealImp(plot->impuls_kmu);
            strcpy(I.ImpName[3], "«¿Õﬂ“»≈ 3");       I.RealOffset[3] = plot->GetRealImp(plot->impuls_mu);
            break;
        }
    }; break;
    case SIG_L  :
    case SIG_R  : {
        Svet_0 * svet = dynamic_cast<Svet_0 *>(ac);
        switch (svet->masy) {
        default : I.ImpCount=3;
            strcpy(I.ImpName[0], "Œ“ –€“»≈");       I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "Õ≈»—œ–¿¬ÕŒ—“‹");  I.RealOffset[1] = svet->GetRealImp(svet->impuls_plus);
            strcpy(I.ImpName[2], "¿¬“Œƒ≈…—“¬»≈");   I.RealOffset[2] = svet->GetRealImp(svet->impuls_mnus);
            break;
        case 1  : I.ImpCount=3;
            strcpy(I.ImpName[0], "»Ãœ”À‹— 1");       I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "»Ãœ”À‹— 2");       I.RealOffset[1] = svet->GetRealImp(svet->impuls_plus);
            strcpy(I.ImpName[2], "¬€¬Œƒ»“‹ Õ¿ ”◊- ≈");   I.RealOffset[2] = svet->GetRealImp(svet->impuls_mnus);
            break;
        case 2  :
        case 3  : I.ImpCount=2;
            strcpy(I.ImpName[0], "?");       I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "?");       I.RealOffset[1] = svet->GetRealImp(svet->impuls_kzm);
            break;
        case 4  : I.ImpCount=5;
            strcpy(I.ImpName[0], "Œ“ –€“»≈");       I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "Õ≈»—œ–¿¬ÕŒ—“‹");  I.RealOffset[1] = svet->GetRealImp(svet->impuls_plus);
            strcpy(I.ImpName[2], "¿¬“Œƒ≈…—“¬»≈");   I.RealOffset[2] = svet->GetRealImp(svet->impuls_mnus);
            strcpy(I.ImpName[3], "¡≈À€…");          I.RealOffset[3] = svet->GetRealImp(svet->impuls_kzm);
            strcpy(I.ImpName[4], " –¿—Õ€…");        I.RealOffset[4] = svet->GetRealImp(svet->impuls_kmu);
            break;
        case 5  : I.ImpCount=2;
            strcpy(I.ImpName[0], "¡≈À€…");          I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "¡≈À€… - Ã»√");    I.RealOffset[1] = svet->GetRealImp(svet->impuls_kzm);
            break;
        case 6  : I.ImpCount=6;
            strcpy(I.ImpName[0], "Œ“ –€“»≈");       I.RealOffset[0] = svet->GetRealImp(svet->impuls_busi);
            strcpy(I.ImpName[1], "Õ≈»—œ–¿¬ÕŒ—“‹");  I.RealOffset[1] = svet->GetRealImp(svet->impuls_plus);
            strcpy(I.ImpName[2], "¿¬“Œƒ≈…—“¬»≈");   I.RealOffset[2] = svet->GetRealImp(svet->impuls_mnus);
            strcpy(I.ImpName[3], "Õ≈»—œ–¿¬ÕŒ—“‹ —Œ"); I.RealOffset[3] = svet->GetRealImp(svet->impuls_kzm);
            strcpy(I.ImpName[4], "«¿ –€“»≈");        I.RealOffset[4] = svet->GetRealImp(svet->impuls_kmu);
            strcpy(I.ImpName[5], "Õ≈»—œ–¿¬ÕŒ—“‹  Œ"); I.RealOffset[5] = svet->GetRealImp(svet->impuls_mu);
            break;
        }
    } ; break;
    case SWRT   :
    case SWLT   :
    case SWLB   :
    case SWRB   :
    case SWL    :
    case SWKT   :
    case SWKB   :
    case SWrt   :
    case SWlt   :
    case SWlb   :
    case SWrb   :
    case ENGL1  :
    case ENGL2  :
    case XBOST1 :
    case XBOST2 :
    case XBOST3 :
    case XBOST4 :
    case KUS1   :
    case KUS2   :
    case SWrtW  :
    case SWltW  :
    case SWlbW  :
    case SWrbW  :
    case Y_STREL_1:
    case Y_STREL_2:
    case Y_STREL_3:
    case Y_STREL_4: {
        Strel * strel = dynamic_cast<Strel *>(ac);
        I.ImpCount = 6;
        strcpy(I.ImpName[0], "«¿Õﬂ“»≈");       I.RealOffset[0] = strel->GetRealImp(strel->impuls_busi);
        strcpy(I.ImpName[1], "œÀﬁ—");          I.RealOffset[1] = strel->GetRealImp(strel->impuls_plus);
        strcpy(I.ImpName[2], "Ã»Õ”—");         I.RealOffset[2] = strel->GetRealImp(strel->impuls_mnus);
        strcpy(I.ImpName[3], "«¿Ã€ ¿Õ»≈");     I.RealOffset[3] = strel->GetRealImp(strel->impuls_kzm);
        if (strel->nomer > 0) {
            strcpy(I.ImpName[4], " ŒÕ“–ŒÀ‹ Ã”"); I.RealOffset[4] = strel->GetRealImp(strel->impuls_kmu);
            strcpy(I.ImpName[5], "Ã”");         I.RealOffset[5] = strel->GetRealImp(strel->impuls_mu);
        } else {
            strcpy(I.ImpName[4], "Œ“—≈◊ ¿ 1");  I.RealOffset[4] = strel->GetRealImp(strel->impuls_kmu);
            strcpy(I.ImpName[5], "Œ“—≈◊ ¿ 2");  I.RealOffset[5] = strel->GetRealImp(strel->impuls_mu);
        }
    } ; break;
    case NAPR :  {
        Napr * napr = dynamic_cast<Napr *>(ac);
        I.ImpCount = 4;
        strcpy(I.ImpName[0], "«¿Õﬂ“»≈ ->");     I.RealOffset[0] = napr->GetRealImp(napr->impuls_busi);
        strcpy(I.ImpName[1], "Õ¿œ–¿¬À≈Õ»≈ ->");         I.RealOffset[1] = napr->GetRealImp(napr->impuls_plus);
        strcpy(I.ImpName[2], "Õ¿œ–¿¬À≈Õ»≈ <-");         I.RealOffset[2] = napr->GetRealImp(napr->impuls_mnus);
        strcpy(I.ImpName[3], "«¿Õﬂ“»≈ <-");     I.RealOffset[3] = napr->GetRealImp(napr->impuls_kzm);
    }; break;
    case LAMP :  {
        Lamp * lamp = dynamic_cast<Lamp *>(ac);
        I.ImpCount = 1;
        strcpy(I.ImpName[0], "»Ãœ”À‹— 1");     I.RealOffset[0] = lamp->GetRealImp(lamp->impuls_busi);
    }; break;
    case LAM4 : {
        Lam4 * lamp = dynamic_cast<Lam4 *>(ac);
        I.ImpCount = 4;
        strcpy(I.ImpName[0], "—»√Õ¿À 1");     I.RealOffset[0] = lamp->GetRealImp(lamp->impuls_busi);
        strcpy(I.ImpName[1], "—»√Õ¿À 2");     I.RealOffset[1] = lamp->GetRealImp(lamp->impuls_plus);
        strcpy(I.ImpName[2], "—»√Õ¿À 3");     I.RealOffset[2] = lamp->GetRealImp(lamp->impuls_mnus);
        strcpy(I.ImpName[3], "—»√Õ¿À 4");     I.RealOffset[3] = lamp->GetRealImp(lamp->impuls_kzm);
    } break;
    case BASH : {
        Bash * bash = dynamic_cast<Bash *>(ac);
        I.ImpCount = 4;
        strcpy(I.ImpName[0], "—»√Õ¿À 1");     I.RealOffset[0] = bash->GetRealImp(bash->impuls_busi);
        strcpy(I.ImpName[1], "—»√Õ¿À 2");     I.RealOffset[1] = bash->GetRealImp(bash->impuls_plus);
        strcpy(I.ImpName[2], "—»√Õ¿À 3");     I.RealOffset[2] = bash->GetRealImp(bash->impuls_mnus);
        strcpy(I.ImpName[3], "—»√Õ¿À 4");     I.RealOffset[3] = bash->GetRealImp(bash->impuls_kzm);
        switch (bash->tip) {
        default : strcpy(I.CompType , "¡¿ÿÃ¿ "); break;
        case 10 : strcpy(I.CompType , "” —œ—"); break;
        case 11 : strcpy(I.CompType , "—¿”“"); break;
        case 12 :
        case 14 : strcpy(I.CompType , " √”"); break;
        case 13 : strcpy(I.CompType , "ƒ»— "); break;
        case 15 : strcpy(I.CompType , "ﬂ◊≈… ¿"); break;
        }
    }; break;
    case P_SVE :  {
        P_Sve * p_sve = dynamic_cast<P_Sve *>(ac);
        I.ImpCount = 4;
        strcpy(I.ImpName[0], "«¿ –€“»≈");     I.RealOffset[0] = p_sve->GetRealImp(p_sve->impuls_busi);
        strcpy(I.ImpName[1], "¿¬¿–»ﬂ");       I.RealOffset[1] = p_sve->GetRealImp(p_sve->impuls_plus);
        strcpy(I.ImpName[2], "«¿√–¿∆ƒ≈Õ»≈");  I.RealOffset[2] = p_sve->GetRealImp(p_sve->impuls_kmu);
    }; break;
    case SUPERLAMP2 : {
        SuperLamp2 * slamp = dynamic_cast<SuperLamp2 *>(ac);
        I.ImpCount = 4;
        strcpy(I.ImpName[0], "—»√Õ¿À 1");     I.RealOffset[0] = slamp->GetRealImp(slamp->impuls_busi);
        strcpy(I.ImpName[1], "—»√Õ¿À 2");     I.RealOffset[1] = slamp->GetRealImp(slamp->impuls_plus);
        strcpy(I.ImpName[2], "—»√Õ¿À 3");     I.RealOffset[2] = slamp->GetRealImp(slamp->impuls_mnus);
        strcpy(I.ImpName[3], "—»√Õ¿À 4");     I.RealOffset[3] = slamp->GetRealImp(slamp->impuls_kzm);
    } break;
    }





}

/*
INFO   ,
BLOK   ,
FISH_L ,
FISH_R ,
FISH   ,
NAME   ,
GORL_L ,GORL_R ,MESS   ,SzT    ,SzB    , GORL  ,
          ASN    ,KRIV   ,OVER   ,POIN  ,NOMER  ,
          TUPIC  ,BL_UH  ,STIK   ,ELEKTR ,PLATF  ,

            ,

          SUPERLAMP1,,

          BD_SVET,BD_STREL,BD_WAY,BD_BLOK,BD_LAMP,BD_SPECEL, BD_STATIC

 */

const _ctnon = 0;
const _ctway = 1;
const _ctblu = 2;
const _ctstr = 3;
const _ctsvt = 4;
const _ctlmp = 5;
const _ctnpr = 6;
static char _CommonTypeName[7][5] = {"", "ÔÛÚ¸", "Û˜", "ÒÚ", "Ò‚Ú", "ÎÏÔ", "Ì‡Ô"};
//                                  0     1     2     3     4     5     6     7    8  9   10      11     12     13     14    15
static char _BASHTypeName[16][7] = {"Í„Ì", "Í„Ì", "Í„Ì", "Í„Ì", "Í„Ì", "Í„Ì", "Í„Ì", "Í„Ì", "", "", "ÛÍÒÔÒ", "Ò‡ÛÚ", "Í„Û", "‰ËÒÍ", "Í„Û", "ˇ˜ÂÈÍ‡"};
static int _CommonTypeInd[CompTypeCount] = {
//NOTHING,WAY    ,PLOT   ,SIG_L  ,SIG_R
    _ctnon, _ctway, _ctblu,  _ctsvt, _ctsvt,
//,SWRT   ,SWLT   , SWLB   ,SWRB   ,SWL    ,SWKT   ,SWKB   ,SWrt   ,SWlt   ,SWlb   ,SWrb
    _ctstr,  _ctstr,  _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr,  _ctstr, _ctstr, _ctstr,
//,INFO   ,BLOK   ,FISH_L ,FISH_R ,FISH   ,NAME   ,GORL_L ,GORL_R ,MESS   ,
    _ctnon, _ctnon,  _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon,
//SzT    ,SzB    ,
    _ctstr,  _ctstr,
    _ctnon, //GORL  ,
    _ctnpr,// NAPR   ,
    _ctlmp,//LAMP
    _ctnon, _ctnon,//,ASN    ,KRIV
    _ctlmp,//,OVER
    _ctnon, _ctnon, _ctnon,//,POIN  ,NOMER  ,TUPIC  ,
    _ctblu,//BL_UH  ,
    _ctlmp,//LAM4   ,
    _ctnon, _ctnon, _ctnon,//STIK   ,ELEKTR ,PLATF  ,
//ENGL1  ,ENGL2  ,XBOST1 ,XBOST2 ,XBOST3 ,XBOST4 ,KUS1   ,KUS2   ,
    _ctstr, _ctstr,  _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr,
    _ctnon, _ctnon,//P_SVE  ,BASH,
//SWrtW   ,SWltW   ,SWlbW   ,SWrbW,
    _ctstr, _ctstr, _ctstr, _ctstr,
    _ctlmp, _ctlmp,//SUPERLAMP1,SUPERLAMP2,
    _ctstr, _ctstr, _ctstr, _ctstr,//Y_STREL_1,Y_STREL_2,Y_STREL_3,Y_STREL_4,
    _ctlmp//  LED,
};

char * GetTypeName(AComp * AC)
{

    TYP AType = AC->GetType();
    if (AType == BASH) {
        Bash * B = dynamic_cast<Bash *>(AC);
        if (B != 0) return _BASHTypeName[B->tip];
    }
    int ind = _CommonTypeInd[AType];
    if (ind == _ctnon) {
        return Com_Nam[AType];
    }
    return _CommonTypeName[_CommonTypeInd[AType]];
}

static String _TypeAndName;
char * GetTypeAndName(AComp * AC)
{
    _TypeAndName = String(GetTypeName(AC)) + " " + AC->GetName();
    return _TypeAndName.c_str();
}



