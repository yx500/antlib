
#include "common.h"

#include "Lamps.h"
#include "Strel.h"
#include "Svet.h"
#include "Ways.h"
#include "aheaders_cpp.h"

#include <iomanip>
#include <iostream>

void CriticalErr(const char* bf, bool do_throw)
{
  PrintErr(bf);
  if( do_throw ) 
    throw std::runtime_error(bf);
}

void PrintErr(const char* txt)
{
  std::cerr << "Err: " << txt << std::endl;
}

const int _ctnon = 0;
const int _ctway = 1;
const int _ctblu = 2;
const int _ctstr = 3;
const int _ctsvt = 4;
const int _ctlmp = 5;
const int _ctnpr = 6;
const int _ctuksps = 7;
String _CommonTypeName[8] = {"", "путь", "уч", "стр", "свт", "лмп", "нпр", "укс"};
//                                  0     1     2     3     4     5     6     7    8  9   10      11     12     13     14    15
String _BASHTypeName[16] = {"кгн", "кгн", "кгн", "кгн", "кгн", "кгн", "кгн", "кгн", "", "", "укспс", "саут", "кгу", "диск", "кгу", "ячейка"};
static int _CommonTypeInd[CompTypeCount] = {
    // NOTHING,WAY    ,PLOT   ,SIG_L  ,SIG_R
    _ctnon, _ctway, _ctblu, _ctsvt, _ctsvt,
    //,SWRT   ,SWLT   , SWLB   ,SWRB   ,SWL    ,SWKT   ,SWKB   ,SWrt   ,SWlt   ,SWlb   ,SWrb
    _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr,
    //,INFO   ,BLOK   ,FISH_L ,FISH_R ,FISH   ,NAME   ,GORL_L ,GORL_R ,MESS   ,
    _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon, _ctnon,
    // SzT    ,SzB    ,
    _ctstr, _ctstr,
    _ctnon,                 // GORL  ,
    _ctnpr,                 // NAPR   ,
    _ctlmp,                 // LAMP
    _ctnon, _ctnon,         //,ASN    ,KRIV
    _ctlmp,                 //,OVER
    _ctnon, _ctnon, _ctnon, //,POIN  ,NOMER  ,TUPIC  ,
    _ctblu,                 // BL_UH  ,
    _ctlmp,                 // LAM4   ,
    _ctnon, _ctnon, _ctnon, // STIK   ,ELEKTR ,PLATF  ,
    // ENGL1  ,ENGL2  ,XBOST1 ,XBOST2 ,XBOST3 ,XBOST4 ,KUS1   ,KUS2   ,
    _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr, _ctstr,
    _ctnon, _ctuksps, // P_SVE  ,BASH,
    // SWrtW   ,SWltW   ,SWlbW   ,SWrbW,
    _ctstr, _ctstr, _ctstr, _ctstr,
    _ctlmp, _ctlmp,                 // SUPERLAMP1,SUPERLAMP2,
    _ctstr, _ctstr, _ctstr, _ctstr, // Y_STREL_1,Y_STREL_2,Y_STREL_3,Y_STREL_4,
    _ctlmp                          //  LED,
};

String GetTypeName(AComp* AC)
{

  TYP AType = AC->GetType();
  if (AType == BASH) {
    Bash* B = dynamic_cast<Bash*>(AC);
    if (B != 0)
      return _BASHTypeName[B->tip];
  }
  size_t ind = _CommonTypeInd[AType];
  if (ind == _ctnon)
    return Com_Nam[AType];
  return _CommonTypeName[ind];
}

String GetTypeAndName(AComp* AC)
{
  return  GetTypeName(AC) + " " + String(AC->GetName());
}
