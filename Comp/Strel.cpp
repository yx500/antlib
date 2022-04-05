#include "aheaders_cpp.h"

#include "APch.h"


#include "Strel.h"
#include "Str_fun.h"
#include "Gorl.h"
#include "Scrin.h"
#include "Elem.h"
#include "F.h"
#include "Impuls.h"
#include "Vatempl.h"

#include "propmap.h"
#include"out_num.h"
#include "bgi.h"


void SetGradientFactor(float AGradientFactor);



int X4 = 4;

int dlen(int num, char *name)
{
    int r;
    if (name[0] == '$') r = strlen(name) - 1;
    else {
        if (abs(num) < 1000) r = 3;
        if (abs(num) < 100) r = 2;
        if (abs(num) < 10) r = 1;
        if (abs(num) == 0) r = 0;
    }
    return r;

}

int priznak_pereris_strel_if_change_mu;

int Strel0::TestMu(void)
{



    if (fimpuls_mu == 1) {
        styll1 = 3;
        styll2 = 3;
    }

    if (fimpuls_kmu == 1) {

        styll1 = 7;
        styll2 = 7;
        /*
        styll1 = 7;
        styll2 = 7;
        */
    }
    return 1;
}

void Strel::Set()
{
    Ways::Set();
    /*-------------------------*/
    Prz[0]  = MEM.name[13];
    Prz[1]  = MEM.name[14];
    //Prz[2]  = MEM.name[15];
    Prz[3]  = MEM.name16;

    InvertStrel = MEM.name[15] & 0x01;
    bText =       MEM.name[15] & 0x02;
    bShowPol =    MEM.name[15] & 0x04;

    /*-------------------------*/
    impuls_plus = MEM.impuls_plus;
    impuls_mnus = MEM.impuls_mnus;
    impuls_kzm = MEM.impuls_kzm;
    impuls_kmu = MEM.impuls_kmu;
    impuls_mu = MEM.impuls_mu;

    memcpy(&ID,   MEM.name + 11    , 2);
    nomer = MEM.Nomer;

    if (ExtPriz.MEM2) {
        impuls_IR = MEM2.impuls_busi;
        impuls_PKS = MEM2.impuls_plus;
        impuls_ZS = MEM2.impuls_mnus;
        impuls_ZS2 = MEM2.impuls_kzm;
        impuls_kmu2 = MEM2.impuls_kmu;
        impuls_mu2 = MEM2.impuls_mu;
    }

    if (((GetType() == BL_UH) ||
            (GetType() == POIN) ||
            (GetType() == SUPERLAMP2) ||
            (GetType() == COMMLMP) ||
            (GetType() == LAM4) ||
            (GetType() == BASH) ||
            (GetType() == P_SVE) ||
            (GetType() == NAPR))) {
        OemToCharBuff(MEM.name, name, 9);   /*strncpy(name,MEM.name,9)*/; return;
    }
    if (MEM.name[0] == '$')
        OemToCharBuff(MEM.name, name, 9);
    else
        memset(name, 0, 9);


}
static char _StrelPropName[24][20] = {
    "цфPrz0",          // 0
    "цфPrz1",          // 1
    "цфPrz2",          // 2
    "цфPrz3",          // 3

    "цфNomer",         // 4
    "смname_",          //5
    "смИМЯ",            //6

    "тсimpuls_PKS",     // 7
    "тсimpuls_ZS",      // 8
    "тсimpuls_ZS2" ,   // 9
    "тсimpuls_kmu2" ,   // 10
    "тсimpuls_mu2",     // 11
    "лгTextM",          // 12
    "лгInversPol",      // 13
    "лгShowPol",        // 14
    "тсОтсечка1",       // 15
    "тсimpuls_SPU" ,    // 16
    "тсimpuls_AV",      // 17
    "тсimpuls_block",   // 18
    "тсimpuls_predSA",  // 19
    "тсimpuls_predSApl",  // 20
    "тсimpuls_predSAmn",  // 21

    "тсimpuls_otkl_plus",// 22
    "тсimpuls_otkl_minus"// 23

};

void Strel::SetPropMap(TPropMap &m)
{
    Ways::SetPropMap(m);
    int _n = 0;
    Prz[0]  = m.geti(_StrelPropName[_n++]);
    Prz[1]  = m.geti(_StrelPropName[_n++]);
    _n++;//Prz[2]  = m.geti(_StrelPropName[ 2]);
    Prz[3]  = m.geti(_StrelPropName[_n++]);

    nomer = m.geti(_StrelPropName[_n++]);
    memset(name, 0, sizeof(name));
    strncpy(name, m.get(_StrelPropName[_n++]).c_str(), sizeof(name));
    _n++; //смИМЯ

        //impuls_IR = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
        impuls_PKS = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
        impuls_ZS = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
        impuls_ZS2  = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
        impuls_kmu2  = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
        impuls_mu2   = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());

    bText = (bool)m.geti(_StrelPropName[_n++]);
    InvertStrel = (bool)m.geti(_StrelPropName[_n++]);
    bShowPol = (bool)m.geti(_StrelPropName[_n++]);
    impuls_otc = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_SPU = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_AV = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());

    impuls_block = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_predSA = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_predSAplus = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_predSAminus = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    //impuls_predSEIR = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());

    impuls_otkl_plus = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());
    impuls_otkl_minus = NewStrToOldImp(m.get(_StrelPropName[_n++]).c_str());



}


void Strel::GetPropMap(TPropMap &m)
{
    Ways::GetPropMap(m);
    int _n = 0;
    m.put(_StrelPropName[_n++], Prz[0],                                0);
    m.put(_StrelPropName[_n++], Prz[1],                                0);
    _n++;//m.put(_StrelPropName[ 2],Prz[2]);
    m.put(_StrelPropName[_n++], Prz[3],                                0);

    m.put(_StrelPropName[_n++], nomer);
    m.put(_StrelPropName[_n++], name);
    String N = GetName();
    m.put(_StrelPropName[_n++], N);

        //m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_IR, this), GetRealImp(impuls_IR),       OldImpToNewStr(0, this));
        m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_PKS, this), GetRealImp(impuls_PKS),     OldImpToNewStr(0, this));
        m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_ZS, this), GetRealImp(impuls_ZS),        OldImpToNewStr(0, this));
        m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_ZS2, this), GetRealImp(impuls_ZS2),    OldImpToNewStr(0, this));
        m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_kmu2, this), GetRealImp(impuls_kmu2),  OldImpToNewStr(0, this));
        m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_mu2, this), GetRealImp(impuls_mu2),   OldImpToNewStr(0, this));



    m.put(_StrelPropName[_n++], bText,                           0);
    m.put(_StrelPropName[_n++], InvertStrel,                     0);
    m.put(_StrelPropName[_n++], bShowPol,                        0);
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_otc, this), GetRealImp(impuls_otc), OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_SPU, this), GetRealImp(impuls_SPU), OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_AV, this), GetRealImp(impuls_AV),  OldImpToNewStr(0, this));

    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_block, this), GetRealImp(impuls_block),  OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_predSA, this), GetRealImp(impuls_predSA),  OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_predSAplus, this), GetRealImp(impuls_predSAplus),  OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_predSAminus, this), GetRealImp(impuls_predSAminus),  OldImpToNewStr(0, this));
    //m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_predSEIR, this), GetRealImp(impuls_predSEIR),  OldImpToNewStr(0, this));

    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_otkl_plus, this), GetRealImp(impuls_otkl_plus),  OldImpToNewStr(0, this));
    m.putEx(_StrelPropName[_n++], OldImpToNewStr(impuls_otkl_minus, this), GetRealImp(impuls_otkl_minus),  OldImpToNewStr(0, this));

}


void Strel::Get()
{
    Ways::Get();

    /*-------------------------*/
    MEM.name[13]  = Prz[0]  ;
    MEM.name[14]  = Prz[1]  ;
    MEM.name[15]  = InvertStrel * 1 + bText * 2 + bShowPol * 4;//Prz[2]  ;
    MEM.name16  = Prz[3];



    /*-------------------------*/
    MEM.impuls_plus = impuls_plus;
    MEM.impuls_mnus = impuls_mnus;
    MEM.impuls_kzm = impuls_kzm;
    MEM.impuls_kmu = impuls_kmu;
    MEM.impuls_mu  = impuls_mu;

    if (ExtPriz.MEM2) {
        MEM2.impuls_busi = impuls_IR;
        MEM2.impuls_plus = impuls_PKS;
        MEM2.impuls_mnus = impuls_ZS;
        MEM2.impuls_kzm = impuls_ZS2;
        MEM2.impuls_kmu = impuls_kmu2;
        MEM2.impuls_mu  = impuls_mu2;
    }

    // эмуляция лампочки
    MEM2.type = 29;
    MEM2.X_ = X; MEM2.Y_ = Y; MEM2.masy = 0;
    memset(MEM2.name, 0, sizeof(MEM2.name));
    CharToOemBuff(name, MEM2.name, 9);
    //memcpy(MEM2.name,name,9);
    MEM2.name[0] = '~';
    MEM2.ExtPriz.MEM2 = 0;


    MEM.Nomer = nomer;
    memset(MEM.name, 0, 10);
    CharToOemBuff(name, MEM.name, 9);
    //memcpy(MEM.name,name,9);

    //memcpy( MEM.name+7   ,RezBuf   , 4);
    memcpy(MEM.name + 11  , &ID       , 2);


}


void Strel::UpdateState()
{
    Ways::UpdateState();
    /*int rimpuls_busi=f(impuls_busi);
    int rimpuls_mnus=f(impuls_mnus);
    int rimpuls_plus=f(impuls_plus);
    int rimpuls_kzm=f(impuls_kzm);
    int rimpuls_kmu=f(impuls_kmu);
    int rimpuls_mu=f(impuls_mu);*/

    int rimpuls_IR = 0;
    int rimpuls_PKS = 0;
    int rimpuls_ZS = 0;
    int rimpuls_ZS2 = 0;
    int rimpuls_kmu2 = 0;
    int rimpuls_mu2 = 0;

    int rimpuls_block = f(impuls_block);
    int rimpuls_predSA = f(impuls_predSA);
    int rimpuls_predSAplus = f(impuls_predSAplus);
    int rimpuls_predSAminus = f(impuls_predSAminus);
    int rimpuls_predSEIR = f(impuls_predSEIR);

    int rimpuls_otkl_plus = f(impuls_otkl_plus);
    int rimpuls_otkl_minus = f(impuls_otkl_minus);

    int rimpuls_otc = f(impuls_otc);
    int rimpuls_SPU = f(impuls_SPU);
    int rimpuls_AV = f(impuls_AV);
    StateChanged = StateChanged | (rimpuls_otc != fimpuls_otc) | (rimpuls_SPU != fimpuls_SPU) | (rimpuls_AV != fimpuls_AV)|
                                  (rimpuls_block!=fimpuls_block)|(rimpuls_predSA!=fimpuls_predSA)|(rimpuls_predSAplus!=fimpuls_predSAplus)|(rimpuls_predSAminus!=fimpuls_predSAminus)|(rimpuls_predSEIR!=fimpuls_predSEIR) |
                                  (rimpuls_otkl_plus!=fimpuls_otkl_plus)|(rimpuls_otkl_minus!=fimpuls_otkl_minus);

    fimpuls_otc = rimpuls_otc;
    fimpuls_SPU = rimpuls_SPU;
    fimpuls_AV = rimpuls_AV;
    fimpuls_block = rimpuls_block;
    fimpuls_predSA = rimpuls_predSA;
    fimpuls_predSAplus = rimpuls_predSAplus;
    fimpuls_predSAminus = rimpuls_predSAminus;
    fimpuls_predSEIR = rimpuls_predSEIR;
    fimpuls_otkl_plus = rimpuls_otkl_plus;
    fimpuls_otkl_minus = rimpuls_otkl_minus;


    if (ExtPriz.MEM2) {
        rimpuls_IR = f(impuls_IR);
        rimpuls_PKS = f(impuls_PKS);
        rimpuls_ZS = f(impuls_ZS);
        rimpuls_ZS2 = f(impuls_ZS2);
        rimpuls_kmu2 = f(impuls_kmu2);
        rimpuls_mu2 = f(impuls_mu2);
    }



    StateChanged = StateChanged |
                   /*(rimpuls_busi!=fimpuls_busi)|
                   (rimpuls_plus!=fimpuls_plus)|
                   (rimpuls_mnus!=fimpuls_mnus)|
                   (rimpuls_kzm!=fimpuls_kzm)|
                   (rimpuls_kmu!=fimpuls_kmu)|
                   (rimpuls_mu!=fimpuls_mu)|*/
                   (rimpuls_IR != fimpuls_IR) |
                   (rimpuls_ZS != fimpuls_ZS) |
                   (rimpuls_PKS != fimpuls_PKS) |
                   (rimpuls_ZS2 != fimpuls_ZS2) |
                   (rimpuls_kmu2 != fimpuls_kmu2) |
                   (rimpuls_mu2 != fimpuls_mu2);
    /*fimpuls_busi=rimpuls_busi;
    fimpuls_mnus=rimpuls_mnus;
    fimpuls_plus=rimpuls_plus;
    fimpuls_kzm=rimpuls_kzm;
    fimpuls_kmu=rimpuls_kmu;
    fimpuls_mu=rimpuls_mu;*/

    fimpuls_IR = rimpuls_IR;
    fimpuls_PKS = rimpuls_PKS;
    fimpuls_ZS = rimpuls_ZS;
    fimpuls_ZS2 = rimpuls_ZS2;
    fimpuls_kmu2 = rimpuls_kmu2;
    fimpuls_mu2 = rimpuls_mu2;

}

void Strel0::UpdateState()
{
    Strel::UpdateState();
    EXD_UpdateTrainNumber(this, fimpuls_busi);

    // Вычисляем все параметры прорисовки
    // is - положение
    // styll1 -  штриховка заполнения по +
    // styll2 -  штриховка заполнения по -
    // styll3 -?
    // clr - цвет заполнения по положению
    // cbord1;     // цвет окантовки +
    // cbord2;     // цвет окантовки -

    int priz_otse = 0;
    if (nomer < 0) priz_otse++;
    if (nomer < 0) {

        //цвет заливки положения
        clr = LIN;

        if (impuls_busi) clr = Clr_Set(fimpuls_busi);
        if (clr != COLOR_B) {
            if (impuls_kzm)  clr = Clr_SetK(fimpuls_kzm);
            // Доп замыкание
            if ((impuls_kzm)&&(fimpuls_kzm==0)&&(impuls_kmu2)&&(fimpuls_mu2!=1)){
                clr = Clr_SetK(impuls_kmu2);
            }

            if ((clr != COLOR_SET) && (bShowInSpyMarsh)) clr = COLOR_S;
        }

        // искуственная разделка
        if ((ExtPriz.MEM2) && (impuls_IR != 0) && (fimpuls_IR == 1)) {
            if (clr == COLOR_B) clr = COLOR_IR_B; else if (clr == COLOR_SET) clr = COLOR_IR_Z; else
                clr = COLOR_IR_F;
        }


        //Положение стрелки
        is = P;
        {
            // нормальные
            if ((GetType() == SzT) || (GetType() == SzB)) {
                is = fimpuls_kmu * 2 + fimpuls_mu;
                if (is > 3) is = 3;
                if (
                    (!fimpuls_plus) &&
                    fimpuls_mnus
                ) is = W;
            } else {
                if (fimpuls_kmu || fimpuls_mu) {
                    if (fimpuls_busi != 33) clr = LIN;
                    priz_otse++;
                }
                is = fimpuls_plus * 2 + fimpuls_mnus;
                // при отключении надо сохранить положение
                if ((fimpuls_otkl_plus==1)&&(fimpuls_mnus==0)) is = 2;
                if ((fimpuls_otkl_minus==1)&&(fimpuls_plus==0)) is = 1;
            }
            if (!is)is = 3;
            if (is != W) {
                if (is > 3) is = 3;
            }
            //if ((is==D)&&(impuls_plus + impuls_mnus==0)) is=W;
        }

        // штриховка Styll
        /* styll1=1;styll2=1;styll3=1; - внешние ставят
        if(
           (GetType()!=SzB)&&
           (GetType()!=SzT)&&
           (priz_otse==0)) TestMu();*/
    } else {
        // Горловинная обработка
        //    TestMu();
        if (!AO->USE_GORL_OTCECH) {
            if (
                (GetType() != SzB) &&
                (GetType() != SzT))    TestMu();
        }

        if ((_clr != clr) || (_is != is) || (_styll1 != styll1) || (_styll2 != styll2) || (_styll3 != styll3)) StateChanged = true;
        _clr = clr; _is = is; _styll1 = styll1; _styll2 = styll2; _styll3 = styll3;




    }
    // Цвет окантовки
    cbord1 = C_D;
    cbord2 = C_D;

    if (bShowUIR) {
        cbord1 = SV_MIG;
        cbord2 = SV_MIG;
    }


    if ((ExtPriz.MEM2) &&
            ((impuls_ZS != 0) && (fimpuls_ZS == 1)) ||
            ((impuls_ZS2 != 0) && (fimpuls_ZS2 == 1)))

    {
        cbord1 = KRAYARK;
        cbord2 = KRAYARK;
    }

    if ((ExtPriz.MEM2) && (impuls_PKS != 0) && (fimpuls_PKS == 1)) {
        cbord1 = COLOR_PSV;
        cbord2 = COLOR_PSV;
    }

    if ((impuls_predSEIR != 0) && (fimpuls_predSEIR == 1)) {
        cbord1 = KRA_BEL;
        cbord2 = KRA_BEL;
    }
    if ((impuls_predSA != 0) && (fimpuls_predSA == 1)) {
        cbord1 = KRA_BEL;
        cbord2 = KRA_BEL;
    }
    if ((impuls_predSAplus != 0) && (fimpuls_predSAplus == 1)) {
        cbord1 = KRA_BEL;
    }
    if ((impuls_predSAminus != 0) && (fimpuls_predSAminus == 1)) {
        cbord2 = KRA_BEL;
    }

    // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
    if ((IsClrMig(clr)) || (IsClrMig(cbord1)) || (IsClrMig(cbord2))) StateChanged = true;

}


bool Strel0::isBusy(){
        if (nomer < 0) {
            if (f(impuls_busi)==1){
                if ((f(impuls_kmu)==0)&&(f(impuls_mu)==0))
                        return 1;
            }
            return 0;
        } else return Ways::isBusy();
}
bool Strel0::isKzm(){
        if (nomer < 0) {
            if (f(impuls_kzm)==1){
                if ((f(impuls_kmu)==0)&&(f(impuls_mu)==0))
                        return 1;
            }
        }
        return 0;
}
bool Strel0::isBusyKzmAccepted(){
    if (nomer < 0) {
        if((impuls_busi!=0)&&(impuls_kzm!=0)) return true;
    }
    return false;
}

int Def_gr(char *name)
{
    if ((name[0] == 'Ч') && (name[1] == 'П'))return 0; // ЧЕТНЫЕ СТРЕЛКИ
    if ((name[0] == 'Н') && (name[1] == 'О'))return 0;
    if ((name[0] == 'Н') && (name[1] == 'П'))return 1; //  НЕЧЕТНЫЕ СТРЕЛКИ
    if ((name[0] == 'Ч') && (name[1] == 'О'))return 1;
    return 1;

}
void Strel0::Tst_Opis_PKS(void)
{
    if (
        (impuls_plus >= 1000) && (impuls_mnus >= 1000)
    )      Tip_Opis_PKS = 1;        else  Tip_Opis_PKS = 2;
};
void Strel::Go()
{
    bool b = StateChanged;
    UpdateState();
    if (b || StateChanged) Show();
    StateChanged = false;
}
void Strel::Show()
{
    x = X * MUL_X + _X_;
    y = Y * MUL_Y + _Y_;
}
/*
void Strel::Show(){
  Tst_Opis_PKS();
  int sav_sh;
  int sav_sh2;
  int sn;
  mas__ = masx2*MUL_X;
//  int A=18,B=80;
  int c;
//  printf("%d",Prz[0]);

  if((Prz[0]<=0)||(Prz[0]>=20)) X4 = 4;
  else{ if(Prz[0]==1) X4=600; else X4 = Prz[0];}
  if((Prz[2]==2)||(Prz[2]==3)) NomerHeight=1;else NomerHeight=0;


  len_4=((STREL_X/*+mas*)*MUL_X)/X4;
  if(masy){
    sav_sh=sh;
    sav_sh2=sh2;
    sh =sh*(masy+1)-sh_y*masy;
    sh2 =sh;
    }
/*if(NIKOLA)/  clr = LIN;
  is = P;
  styll1=1;
  styll2=1;
  if(sh_y==2) clr=BLUE_m;
                                                                                                      /*****/
/* if((GetType()==INFO)||(GetType()==LAM4)||(GetType()==NAPR)||(GetType()==ASN)||(GetType()==POIN)||(GetType()==P_SVE)){
   ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);
  if(masy){
    sh=sav_sh;
    sh2=sav_sh2;
    }
    return;
  }
  if(FLG==1){
    if(nomer<0){
      if(masy){
    sh=sav_sh;
    sh2=sav_sh2;
       }
      return;
    }
    if(Def_gr(Curr_G->gorl[0]->name)!=nomer%2){
      if(masy){
    sh=sav_sh;
    sh2=sav_sh2;
    }
       return;
    }
    is = Curr_G->gorl[0]->Matr[MARSH][nomer/2+Def_gr(Curr_G->gorl[0]->name)];
    clr = COLOR_SET;
    if(is==H) {is = P;clr=LIN;};
    if(is==D) clr=LIN;
  }
  if (nomer<0){
        /*
    if(NIKOLA){
      sn =  nomer;
      nomer = 0;
      }else / nomer = -nomer;

      ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);
      /*
      if(NIKOLA) nomer = sn;
      else
      *
         nomer = -nomer;
  }
  else
      ShowXY(x*MUL_X+_X_,y*MUL_Y+_Y_);
  if(masy){
    sh=sav_sh;
    sh2=sav_sh2;
    }


}
*/
void Strel0::SetStrelShowParams(int Aclr, int Ais, int Astyll1, int Astyll2, int Acbord1, int Acbord2)
{
    // устанавливает извне параметры для рисовки стрелки
    // если значение<0 стрелка определяется сама
    UpdateState();
    if (Aclr < 0) {
        //clr=LIN;
    } else {
        clr = Aclr;
    }
    if (Ais < 0) {
        //is=W;
    } else {
        is = Ais;
    }

    if ((Acbord1 < 0) || (Acbord2 < 0)) {
        //cbord1=C_D;
        //cbord2=C_D;
    } else {
        cbord1 = Acbord1;
        cbord2 = Acbord2;
    }
    if ((Astyll1 < 0) || (Astyll2 < 0)) {
        styll1 = 1;
        styll2 = 1;
    } else {
        styll1 = Astyll1;
        styll2 = Astyll2;
    }
}

void Strel0::SetUstPol(int pol)
{
    // устанавливет решетку на стрелке в положение
    // если Pol !=1,2,3 стирает
    switch (pol) {
    case 1: SetStrelShowParams(-1, -1, 6, 1, -1, -1); break;
    case 2: SetStrelShowParams(-1, -1, 1, 6, -1, -1); break;
    case 3: SetStrelShowParams(-1, -1, 7, 6, -1, -1); break;

    case 4: SetStrelShowParams(-1, -1, 6, 1, -1, -1); break;
    case 5: SetStrelShowParams(-1, -1, 1, 6, -1, -1); break;
    case 6: SetStrelShowParams(-1, -1, 6, 6, -1, -1); break;

    case 7: SetStrelShowParams(-1, -1, 5, 1, -1, -1); break;
    case 8: SetStrelShowParams(-1, -1, 1, 5, -1, -1); break;
    case 9: SetStrelShowParams(-1, -1, 5, 5, -1, -1); break;

    default: SetStrelShowParams(-1, -1, -1, -1, -1, -1); break;
    }
}


void  Strel0::Show1()
{

    x = X * MUL_X + _X_;
    y = Y * MUL_Y + _Y_;

    Tst_Opis_PKS();

    //if ((AO->NIKOLA) && (nomer > 0)) clr = LIN;


    mas__ = masx2 * MUL_X;

    if ((Prz[0] <= 0) || (Prz[0] >= 20)) X4 = 4;
    else {
        if (Prz[0] == 1) X4 = 600; else X4 = Prz[0];
    }

    if (bText) NomerHeight = 1; else NomerHeight = 0;


    len_4 = ((STREL_X/*+mas*/) * MUL_X) / X4;

    sav_sh = sh;
    sav_sh2 = sh2;
    if (Prz[0] == 20) {
        sh = sh * (masy + 1) / 2 - sh_y * masy / 2;
        sh2 = sh;
    }
    if (masy) {
        sh = sh * (masy + 1) - sh_y * masy;
        sh2 = sh;
    }

    /*if(nomer<0){
      if ((fimpuls_kmu==1)||(fimpuls_mu==1))
         SetGradientFactor(1.5);
    } */

    rnomer = nomer;
    if (nomer < 0) {
        nomer = -nomer;
        if (impuls_busi == 0) clr = FON;
    }

    if (fimpuls_otc == 1)
        SetGradientFactor(1.5);


}


void  Strel0::Show2()
{
    /* debug
    String SS=String(Tagstr.c_str());
    int xx,yy;
    GetNumberPosition(xx, yy, 64, 24, 0);
    OutTextXY(xx, yy-12, SS.c_str() );
    */
    nomer = rnomer;
    sh = sav_sh;
    sh2 = sav_sh2;
    if (masy) {

    }
    SetGradientFactor(1);
    setfillstyle(1, FON);
}



const char * Strel::GetName()
{
    static char nname[sizeof(name)];
    memset(nname, 0, sizeof(nname));
    //OemToChar(name,ansiname);
    TYP t = GetType();
    switch (t) {
    case  BL_UH  :
    case  LAM4   :
    case  BASH   :
    case  P_SVE  :
    case LOG_LAMP:
    case SUPERLAMP2:
    case LED:          return name;
    case  NAPR   : if (name[0]=='-')return name+1; else return name;
    }

    if (name[0] == '$') {
        //OemToChar(name+1,ansiname);
        return name + 1;
    } else {
        itoa(abs(nomer), nname, 10);
    }
    return nname;
}



int X_Text(int len, int x, uint8 prz, int priz1, int ColCifr)
{
    int sdvig = (4 * ColCifr) + S(len);
    int x_text;
    if (prz == 1)  sdvig = (sdvig + 4) * (-1);
    if (priz1)
        x_text = x + len - len_4 - S(len) + sdvig;//*2  /*-dlen(nomer,name)*4-4*/;
    else
        x_text = x + len_4 + S(len)   - sdvig;    // *2       /*+dlen(nomer,name)*4+4*/;

    return x_text;
};


#define Z66 6

int Y_Text(int len, int y, uint8 prz, int priz1)
{
    int y_text;
    if (priz1)
        y_text = y + WAY_Y - 2;
    else {
        if (NomerHeight != 0) y_text = y - (sh_y * 2 + 2) - 1 ; else
            y_text = y - 14    + 3 - 11 ;
    }
    return y_text;
};

void  SwRTop::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1], 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);

    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);
    //if (!AO->bDopPriznak) Prz[3]=0;
    KB(x, y - sh + sh_y, Len, 1, Prz[3]*MUL_X);
    Strelka(is, SW, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();

}
TYP  SwRTop::GetType()
{
    return SWRT;
}

void  SwRBot:: Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1], 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 1);

    if ((CurrentPicture == LT) && (AO->MaxX > 801))   y_text += 6;
    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);
    //if (!AO->bDopPriznak) Prz[3]=0;
    KT(x, y + sh, Len, 1, Prz[3]*MUL_X);
    Strelka(is, SW, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();

}
TYP  SwRBot::GetType()
{
    return SWRB;
}

void  SwLBot::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1], 0, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 1);
    if ((CurrentPicture == LT) && (AO->MaxX > 801))  y_text += 6;
    L(x, y, Len);
    //if (!AO->bDopPriznak) Prz[3]=0;
    KB(x, y, Len, 0, Prz[3]*MUL_X);
    Strelka(is, SW, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SwLBot::GetType()
{
    return SWLB;
}

void  SwLTop::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1], 0, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);
    L(x, y, Len);
    //if (!AO->bDopPriznak) Prz[3]=0;
    KT(x, y + sh_y, Len, 0, Prz[3]*MUL_X);
    Strelka(is, SW, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SwLTop::GetType()
{
    return SWLT;
}
void   Line::Show()
{
    Strel0::Show1();
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        if (clr != LIN) ; else
            clr = BLUE_mmm;
        setcolor(BLUE_mmm);
    }
    Len = (STREL_X + mas) * MUL_X;
    L(x, y, Len);
    setfillstyle(styll1, clr);
    setcolor(cbord1);
    if (sh_y == 0)
        line(pr1[0], pr1[1], pr1[2], pr1[3]);
    else
        _bar3d_(pr1[0], pr1[1], pr1[2], pr1[3], 0, 0);

    Strel0::Show2();

}
TYP  Line::GetType()
{
    return SWL;
}

void    fillpoly_z(int nt_x, int *kr_x, int clr_x, int prz_x)
{
    fillpoly(nt_x, kr_x);
    setcolor(clr_x);
    if (nt_x == 7) {
        line(kr_x[0], kr_x[1] - 1, kr_x[2], kr_x[3]);

        /*
              setcolor(C_D);
                 OutTextXY(kr_x[0],kr_x[1],"0");
                 OutTextXY(kr_x[2],kr_x[3],"1");
                 OutTextXY(kr_x[4],kr_x[5],"2");
                 OutTextXY(kr_x[6],kr_x[7],"3");

                 OutTextXY(kr_x[10],kr_x[11],"7");
        */

        if (prz_x == 1) {

            setcolor(clr_x);

            if (kr_x[11] > kr_x[7]) {

//        setcolor(RED);
//         line(kr_x[0],kr_x[1],kr_x[2],kr_x[3]);
                line(kr_x[2], kr_x[3], kr_x[4], kr_x[5]);
            } else {
                //      setcolor(GREEN);
                line(kr_x[0], kr_x[1], kr_x[2], kr_x[3]);
                line(kr_x[10], kr_x[11], kr_x[0], kr_x[1]);
            }
        }

    }
    if (nt_x == 9) {
        // clr  =ZEL;

        /*
              setcolor(C_D);
                 OutTextXY(kr_x[0],kr_x[1],"0");
                 OutTextXY(kr_x[2],kr_x[3],"1");
                 OutTextXY(kr_x[4],kr_x[5],"2");
                 OutTextXY(kr_x[6],kr_x[7],"3");

                 OutTextXY(kr_x[10],kr_x[11],"7");

                 OutTextXY(kr_x[14],kr_x[15],"9");
        */

//     setcolor(RED);
        if (kr_x[1] > kr_x[3])
            line(kr_x[0], kr_x[1] - 1, kr_x[2], kr_x[3]);
        else
            line(kr_x[0], kr_x[1] + 1, kr_x[2], kr_x[3]);
//     setcolor(GREEN);

        if (kr_x[9] > kr_x[11])
            line(kr_x[8], kr_x[9] - 1, kr_x[10], kr_x[11]);
        else
            line(kr_x[8], kr_x[9], kr_x[10], kr_x[11]);
    }
};


void  KTop::Show()
{
    Strel0::Show1();
    int n = 0;
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    Len = (STREL_X + mas) * MUL_X;
    KT(x, y + sh_y, Len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(9, kr);
    else
        fillpoly_z(9, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  KTop::GetType()
{
    return SWKT;
}



void   KBot::Show()
{
    Strel0::Show1();
    int n = 0;
//   int n = atoi(name+1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    Len = (STREL_X + mas) * MUL_X;
    KB(x, y, Len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(9, kr);
    else
        fillpoly_z(9, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  KBot::GetType()
{
    return SWKB;
}

void  SRTop::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;

    //   x_text=x+Len-len_4-S(Len)*2-dlen(nomer,name)*4-4;
    x_text = X_Text(Len, x, Prz[1] + 1, 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);
    krt(x, y, Len, 1);

    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SRTop::GetType()
{
    return SWrt;
}

void  SRBot::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
//   x_text=x+Len-len_4-S(Len)*2-dlen(nomer,name)*4-4;
    x_text = X_Text(Len, x, Prz[1] + 1, 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 1);
    if ((CurrentPicture == LT) && (AO->MaxX > 801))  y_text += Z66;

    krb(x, y, Len, 0);
    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SRBot::GetType()
{
    return SWrb;
}

void  SLBot::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;

    x_text = X_Text(Len, x, Prz[1] + 1, 0, dlen(nomer, name));
//   x_text=x+len_4+S(Len)*2+dlen(nomer,name)*4+4;
    y_text = Y_Text(Len, y, Prz[1], 1);
    if ((CurrentPicture == LT) && (AO->MaxX > 801))  y_text += Z66;


    klb(x, y, Len, 0);
    L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SLBot::GetType()
{
    return SWlb;
}

void  SLTop::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
//   x_text=x+len_4+S(Len)*2+dlen(nomer,name)*4+4;
    x_text = X_Text(Len, x, Prz[1] + 1, 0, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);
    klt(x, y, Len, 0);
    L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SLTop::GetType()
{
    return SWlt;
}


void  SzTop::Show()
{
    Strel0::Show1();
    int len;
    len = (STREL_X + mas) * MUL_X;
    int nm1, nm2;
    int x_text, y_text;
    int is1 = is, is2 = is;
    int styll2x, styll3x;
    int clr1 = clr,
               clr2 = clr;
    x_text = x + len / 10 - 2;
    y_text = y - 14;
    nm1 = nomer;
    nm2 = -1;

    Len = len;

    if ((is == W) || (is == M)) {
        is1 = P; is2 = M; clr1 = LIN;
    }

    if (is == M) {
        styll2x = styll3;
        styll3x = styll2;
        krt(x, y, len, 0);
    } else {
        styll2x = styll2;
        styll3x = styll3;
        klt(x, y, len, 0);
    }

    if (((len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, len);
    else
        L(x, y, len);
//   settextjustify(CENTER_TEXT,TOP_TEXT);
    Strelka(is1, SZ, styll1, styll2x, clr1, nm1, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    x_text = x + len - len / 10;
    if (is == M) {
        klt(x, y, len, 0);
    } else     {
        krt(x, y, len, 0);
    }
//   settextjustify(CENTER_TEXT,TOP_TEXT);
    Strelka(is2, SZ, styll1, styll3x, clr2, nm2, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Len = len;
    Strel0::Show2();
}

TYP  SzTop::GetType()
{
    return SzT ;
}

void  SzBot::Show()
{
    Strel0::Show1();
    int len = (STREL_X + mas) * MUL_X;
    int nm1, nm2;
    int x_text, y_text;
    int is1 = is, is2 = is;
    int styll2x, styll3x;
    int clr1 = clr, clr2 = clr;
    x_text = x + len / 10 - 2;
    y_text = y + WAY_Y + 6;
    nm1 = nomer;
    nm2 = -1;

    Len = len;

    if ((is == W) || (is == M)) {
        is1 = P; is2 = M; clr1 = LIN;
    }

    x_text = x + len / 10;
    if (((len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, len);
    else
        L(x, y, len);


    if (is == M) {
        styll2x = styll3;
        styll3x = styll2;
        klb(x, y, len, 0);
    } else {
        styll3x = styll3;
        styll2x = styll2;
        krb(x, y, len, 0);
    }
    Strelka(is1, SZ, styll1, styll2x, clr1, nm1, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    x_text = x + len - len / 10;
    if (is == M) {
        krb(x, y, len, 0);
    } else    {
        klb(x, y, len, 0);
    }
    Strelka(is2, SZ, styll1, styll3x, clr2, nm2, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  SzBot::GetType()
{
    return SzB ;
}

void Info::ShowX(int xx, int y)
{
    int TC[6];
    int x;
    char *nms[6] = {
        "ТС",
        "СБ",
        "ТУ",
        "МУ",
        "ПК",
        "БКП"
    };
    TC[0] = f(impuls_busi);
    TC[1] = f(impuls_plus);
    TC[2] = f(impuls_mnus);
    TC[3] = f(impuls_kzm);
    TC[4] = f(impuls_kmu);
    TC[5] = f(impuls_mu);

    int dlx = sh_y * 4;
    int dl = sh_y * 4;
    if (dlx < 16) dlx = 16;
    _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
    x = xx  - dlx * 3;
    // if(1){
//      if(CurrentPicture==LT){
    for (int i = 0; i < 5; i++) {
        if ((TC[i] == 1) && (i != 1)) {
            setfillstyle(1, KRA); setcolor(TXT);
        }
        if ((TC[i] == 1) && (i != 1)) {
            setfillstyle(1, KRA); setcolor(TXT);
        } else                  {
            setfillstyle(1, FON); setcolor(C_D);
        }
        if ((TC[i] == 0) && (i == 1)) {
            setfillstyle(1, KRA); setcolor(TXT);
        }
        setcolor(C_D);
        barx(x + i*dlx, y, x + (i + 1)*dlx, y + dl);
        OutTextXY(x + dlx*i + dlx / 2, y + dl / 2, nms[i]);
    }
    //   }
}

void  Info::Show()
{
    Strel::Show();
    int styll2 = fimpuls_plus;
    int styll1 = fimpuls_mnus;
    int styll3 = 1;  //  << ИСПРАВИЛ ПРАВИЛЬНО ????
    clr = fimpuls_busi;
    if (nomer == -1) {
        ShowX(x, y); return;
    }
    //
    //if(!Test_strel(clr,styll1,styll2,styll3,1)&&(MOD==RD)&&(fimpuls_kmu!=1)&&(fimpuls_kzm!=1))return;
    //
    int XX = x; int YY_ = y; int is1 = clr; int is2 = impuls_busi; int is3 = styll1 | fimpuls_kmu; int is4 = styll2 | fimpuls_kzm;

    int clr1;
    if (MUL_Y < 10) YY_ += 10;
    _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
//     Super_Box(XX-60,YY_-10,XX+60,YY_+25,2,C_D,C_D,LIN,LIN);
    setcolor(C_D);
    if ((CurrentPicture == LT) && (mas != 1)) {
        if (! AO->FLAG_POINT_REVERS)
            OutTextXY(XX, YY_ - 2,   "АДН       АДЧ");
        else
            OutTextXY(XX, YY_ - 2,   "АДЧ       АДН");
    }
    if (is2) {
        OutTextXY(XX, YY_ - 2, "Р.Упр");
        if (is1 == 1) clr1 = COLOR_B;
        else  clr1 = FON;
        setfillstyle(1, clr1);
        fillellipse(x, y + 10, 5, 5);
    }
    setcolor(BLUE_m);
    if (is3 == 1) {
        if (styll1 == 1)clr1 = 14; else  clr1 = FON;
        if (fimpuls_kmu == 1)  setcolor(SV_MIG);
    } else  clr1 = FON;
    setfillstyle(1, clr1);
    Str(XX - 25, YY_ + 10, 3, 0, 0, 0, clr1, AO->LUDOCHKA);
    setcolor(BLUE_m);
    if (is4 == 1) {
        if (styll2 == 1)clr1 = 14; else  clr1 = FON;
        if (fimpuls_kzm == 1)  setcolor(SV_MIG);
    } else  clr1 = FON;
    setfillstyle(1, clr1);
    Str(XX + 25, YY_ + 10, 2, 0, 0, 0, clr1, AO->LUDOCHKA);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
    setfillstyle(1, LIN);
    setcolor(LIN);
}
TYP  Info::GetType()
{
    return INFO;
}

extern int   Out_Info_(int, char *, char *, int);



#define SS0 0
#define SS1 1
#define SS2 2
#define SS3 3
#define SS4 4
#define SS5 5



void  Asn::Show()
{
//  int clr=LIN;
    //int Sost=f(impuls_busi)+
    //         f(impuls_plus)*2+
    //         f(impuls_mnus)*4;
    Strel::Show();
    int chn;
    int x1, x2, y1, y2;
    int x11, x21, y11, y21;
    int tr[8];
    int Zan = fimpuls_busi;
    int Sig = fimpuls_plus;
//  int Zam = f(impuls_mnus);


    int Mar = fimpuls_kzm && fimpuls_kmu  && fimpuls_mu && fimpuls_mnus;
    //if ((OldSost!=Sost) ||(Sost==0)||(Sost>=33)){
//   OldSost=Sost;
    switch (SS) {
    case SS0:
        if ((!Zan) && Sig && Mar) SS = SS1;
        break;
    case SS1:
        if ((!Zan) && Sig && Mar) break;
        if ((!Zan) && (!Sig) && Mar) SS = SS2;
        else SS = SS0;
        break;
    case SS2:
        if ((!Zan) && (!Sig) && Mar) break;
        if (Zan && (!Sig) && Mar) SS = SS3;
        else SS = SS0;
        break;
    case SS3:
        if (!Zan) SS = SS4;
        break;
    case SS4:
        if (!Zan) SS = SS5;
        else     SS = SS3;
        break;
    case SS5:
        if (!Zan) SS = SS0;
        else     SS = SS3;
        break;
    default:  SS = SS0;
        break;
    }
//  }
    chn = nomer % 2;

    if (impuls_plus==0) {
        if (Zan==1) SS = SS3; else SS = SS0;
    }
    if (MOD == ED) SS = SS3;
    if (SS == SS3) {
        setcolor(C_D);
        setfillstyle(1, COLOR_B);
    } else {
        setcolor(FON);
        setfillstyle(1, FON);

    }

//    if(chn)
    int swop;
    x1 = x + 1                  ;
    x2 = x + MUL_X              ;
    y1 = y - sh_y / 2 - 1 - 1         ;
    y2 = y - sh_y / 2 - 1 - 1 - sh_y / 2     ;

    x11 = x + 1                  ;
    x21 = x + MUL_X              ;
    y11 = y - sh_y / 2 + sh_y + 1 + 1    ;
    y21 = y - sh_y / 2 + sh_y + 1 + 1 + sh_y / 2;


    if (!chn) {
        swop = x1; x1 = x2; x2 = swop;
        swop = x11; x11 = x21; x21 = swop;

    }

// gotoxy(10,10);
//       setcolor(RED);
    tr[0] = x1 ; tr[1] = y1;
    tr[2] = x2 ; tr[3] = y1;
    tr[4] = x2 ; tr[5] = y2;
    tr[6] = x1 ; tr[7] = y1;
    fillpoly(4, tr);
    tr[0] = x11 ; tr[1] = y11;
    tr[2] = x21 ; tr[3] = y11;
    tr[4] = x21 ; tr[5] = y21;
    tr[6] = x11 ; tr[7] = y11;
    fillpoly(4, tr);

}
TYP  Asn::GetType()
{
    return ASN;
}
void Napr::SetPropMap(TPropMap &m)
{
     Strel::SetPropMap(m);
     impuls_svob2 = NewStrToOldImp(m.get("тсimpuls_svob2").c_str());
}

void Napr::GetPropMap(TPropMap &m)
{
    Strel::GetPropMap(m);
    m.putEx("тсimpuls_svob2", OldImpToNewStr(impuls_svob2, this), GetRealImp(impuls_svob2),       OldImpToNewStr(0, this));
}
void Napr::UpdateState()
{
    Strel::UpdateState();
    int rimpuls_svob2=f(impuls_svob2);

    StateChanged = StateChanged | (rimpuls_svob2!=fimpuls_svob2) ;
    fimpuls_svob2=rimpuls_svob2;
}

void  Napr::Show()
{
    Strel::Show();
    int is, _is1, _is2;
    int a1 = 0;
    int a2 = 0;
    int pclr = C_D;
    if ((CurrentPicture == BG) && (name[0] == '-')) return;
    if (MOD == RD) {
        clr = ZEL;


        if (fimpuls_busi == 1) clr = COLOR_B;
        if (fimpuls_kzm == 1)  clr = COLOR_B;

        if ((mas == 1) && (clr == COLOR_B)) {
            if ((fimpuls_busi == 1) && (fimpuls_plus == 0) && (fimpuls_mnus == 1) && (fimpuls_kzm == 0)) {
                clr = ZEL; pclr = COLOR_B;
            }
            if ((fimpuls_kzm == 1)  && (fimpuls_mnus == 0) && (fimpuls_plus == 1) && (fimpuls_busi == 0))  {
                clr = ZEL; pclr = COLOR_B;
            }
            if (
            (fimpuls_kzm == 33) ||
            (fimpuls_busi == 33))  clr = BIRUZOVIJ;
        }
        // несовпадение занятости/свободности
        if ((impuls_busi!=0)&&(impuls_svob!=0)&&((fimpuls_busi+fimpuls_svob==0)||(fimpuls_busi+fimpuls_svob==2))) pclr=KRA_ZEL;
        if ((impuls_kzm!=0)&&(impuls_svob2!=0)&&((fimpuls_kzm+fimpuls_svob2==0)||(fimpuls_kzm+fimpuls_svob2==2))) pclr=KRA_ZEL;


        /* 13.07.02  */
        //if ((fimpuls_kmu==1)||(fimpuls_mu==1))  pclr =LIN;
        //if ((fimpuls_kmu==1)&&(fimpuls_mu==1))  pclr =SV_MIG;
        if (fimpuls_kmu == 1) a1 = 1;
        if (fimpuls_mu == 1)  a2 = 1;
        // 12.05.04
        if (
            (fimpuls_kzm == 33) &&
            (fimpuls_busi == 33))  clr = BIRUZOVIJ;
        if (
            FLAG_NAPRAVLENIJA_PO_MINSK
        ) {
            _is1 = (fimpuls_plus == 1) || (fimpuls_busi == 1) ;
            _is2 = (fimpuls_mnus == 1) || (fimpuls_kzm == 1)  ;
        } else {
            _is1 = (fimpuls_plus == 1)   ;
            _is2 = (fimpuls_mnus == 1)  ;
        }
        is = _is1 + _is2 * 2;
        
        ///
        ///if(!Test_strel(clr,is,0,0,0)&&(fimpuls_kmu!=1)&&(fimpuls_mu!=1))return;
        //
        // стирание
        setcolor(FON);
        setfillstyle(1, FON);
        Str(x, y, 1, 0, 0, 0, FON, AO->LUDOCHKA);
    } else {
        is = 3;
        clr = COLOR_B;
    }
    if (is == 5) {
        setcolor(FON);
        setfillstyle(1, FON);
        Str(x, y, 1, 0, 0, 0, FON, AO->LUDOCHKA);
    } else {
        is = is % 3 + 1;
        //setcolor(BLUE_m);
        if ((impuls_busi == 0) && (impuls_kzm == 0) && (impuls_plus == 0) && (impuls_mnus == 0)) clr = FON;

        setcolor(pclr);
        setfillstyle(1, clr);
        Str(x, y, is, uc, a1, a2, clr, AO->LUDOCHKA);
    }
}
TYP  Napr::GetType()
{
    return NAPR;
}

void pntl(int x, int y , int x1, int y1)
{
    int xx[12];
    int s = 7;
    int c = (y1 - y) / 2;
    xx[0] = x   ; xx[1] = y    ; // 0
    xx[2] = x1 - s; xx[3] = y    ;  // 1
    xx[4] = x1  ; xx[5] = y + c  ;  // 2
    xx[6] = x1 - s; xx[7] = y1   ;  // 3
    xx[8] = x   ; xx[9] = y1   ; // 4
    xx[10] = x  ; xx[11] = y   ; // 5
    fillpoly(6, xx);
}

void pntr(int x, int y , int x1, int y1)
{
    int xx[12];
    int s = 7;
    int c = (y1 - y) / 2;
    xx[0] = x   ; xx[1] = y + c  ;  // 0
    xx[2] = x + s ; xx[3] = y    ;  // 1
    xx[4] = x1  ; xx[5] = y    ; // 2
    xx[6] = x1  ; xx[7] = y1   ; // 3
    xx[8] = x + s ; xx[9] = y1   ;  // 4
    xx[10] = x  ; xx[11] = y + c ;  // 5
    fillpoly(6, xx);
}

void  APoint::Show()
{
    if (!AO->ShowBottomPeregons) return;
    if (CurrentPicture == BG)return;
    Strel::Show();
    int nom;
    int nap = 0;
    int s = 3;
    int len = mas;//!!!!!!!!!!!!!!!!!!!!!
    int ch__cod = 0;
    int nch_cod = 1;
    int ch__len = len - 2;
    int nch_len = 2;
    int nom2 = 0;
    char *ptr = 0;
    char nx[8];
    char nm[8];
    char nm2[8];
    clr = LIN;
    if (MOD == RD) {
        if (fimpuls_busi == 1) {
            if (fimpuls_plus == 1) clr = COLOR_B;
            if (impuls_plus == -2)   clr = FON;
        }
        if (fimpuls_mnus == 1) {
            if (fimpuls_kzm == 1) clr = COLOR_B;
            if (impuls_kzm == -2)   clr = FON;
        }
        if (fimpuls_busi == fimpuls_mnus) {
            if (
                (fimpuls_plus == 1) ||
                (fimpuls_kzm == 1)
            ) clr = COLOR_B;
        }
    }

    //
    //if(!Test_strel(clr,nap,0,0,0)&&(MOD==RD))return;
    //
    if (AO->FLAG_POINT_REVERS) {
        ch__cod = 1;
        nch_cod = 0;
    }

    if (MOD == ED) clr = LIN;
    x = (x - _X_) / MUL_X;
    y = (y - _Y_) / MUL_Y;
    //if(MaxY>351)y+=135;//NB

    y += DELTA_Y;
    x += DELTA_X;
    nom = atoi(name);
    if (nom == 0) clr = FON;

    if (name[0] == '+') {
        clr = FON; strncpy(nx, name + 1,sizeof(nx)-1);
    } else {
        strncpy(nx, name,sizeof(nx)-1);
    }
    ptr = strchr(nx, '/');
    if (ptr) {
        strncpy(nm, nx,sizeof(nm)-1);
        ptr = strchr(nm, '/');
        strncpy(nm2, ptr + 1,sizeof(nm2)-1);
        (*ptr) = 0;
        nom2 = atoi(nm2);
    } else {
        strncpy(nm, nx,sizeof(nm)-1);

    }

    setfillstyle(1, clr);
    setcolor(BLUE_m);
    barx(x + 1, y - s, x + len - 1, y + s);

    if ((AO->FLAG_POINT_NUMBER) && (nom > 0)) {
        _SetText(F_LITT_S, CENTER_TEXT, BOTTOM_TEXT);
//        setusercharsize(14,10,14,10);

        if (nom % 2 == nch_cod) {
            OutTextXY(x + ch__len, y - s - 1, nm);
            OutTextXY(x + ch__len + 1, y - s - 1, nm);
        }
        if ((nom2 % 2 == nch_cod) && nom2) {
            OutTextXY(x + nch_len, y - s - 1, nm2);
            OutTextXY(x + nch_len + 1, y - s - 1, nm2);
        }
        _SetText(F_LITT_S, CENTER_TEXT, TOP_TEXT);
        if (nom % 2 == ch__cod) {
            OutTextXY(x + nch_len, y + s + 1, nm);
            OutTextXY(x + nch_len + 1, y + s + 1, nm);
        }
        if ((nom2 % 2 == ch__cod) && (nom2)) {
            OutTextXY(x + ch__len, y + s + 1, nm2);
            OutTextXY(x + ch__len + 1, y + s + 1, nm2);
        }
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
    }
}
TYP   APoint::GetType()
{
    return POIN;
};





void  Engl1::Show()
{
    Strel0::Show1();
    int len;
    len = (STREL_X + mas) * MUL_X;
    len_4 = (STREL_X + mas) * MUL_X / X4;
    int x_text, y_text;
    x_text = x + len / 3;
    if ((CurrentPicture == LT) && (AO->MaxX > 801))
        y_text = y + WAY_Y - 2 + 2 + 6;//-----Bot----
    else
        y_text = y + WAY_Y - 2 + 2;//-----Bot----
    krb(x - len / 4, y, len, 0);
    L(x, y, len);
    Strelka(is, SZ, styll1, styll2, clr, 0, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);

//   int len;
    len = (STREL_X + mas) * MUL_X;
//   int x_text,y_text;
    x_text = x + len * 2 / 3;
    y_text = y - 14;
    klt(x + len / 4, y, len, 0);
    L(x, y, len);
    Strelka(is, SZ, styll1, styll2, clr, 0, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();

}
TYP  Engl1::GetType()
{
    return ENGL1;
}

void  Engl2::Show()
{
    Strel0::Show1();
    int len;
    len = (STREL_X + mas) * MUL_X;
    len_4 = (STREL_X + mas) * MUL_X / X4;
    int x_text, y_text;
    x_text = x + len / 3;
    if ((CurrentPicture == LT) && (AO->MaxX > 801))
        y_text = y + WAY_Y - 2 + 2 + 6;//-----Bot----
    else
        y_text = y + WAY_Y - 2 + 2;//-----Bot----
    krt(x - len / 4, y, len, 0);
    L(x, y, len);
    Strelka(is, SZ, styll1, styll2, clr, 0, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);

//   int len;
    len = (STREL_X + mas) * MUL_X;
//   int x_text,y_text;
    x_text = x + len * 2 / 3;
    y_text = y - 14;
    klb(x + len / 4, y, len, 0);
    L(x, y, len);
    Strelka(is, SZ, styll1, styll2, clr, 0, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    Strel0::Show2();
}
TYP  Engl2::GetType()
{
    return ENGL2;
}


void  Xbost1::Show()
{
    Strel0::Show1();
    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    krb(x, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  Xbost1::GetType()
{
    return XBOST1;
}

void  Xbost2::Show()
{
    Strel0::Show1();
    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    krt(x, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  Xbost2::GetType()
{
    return XBOST2;
}

void  Xbost3::Show()
{
    Strel0::Show1();
    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    klb(x, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  Xbost3::GetType()
{
    return XBOST3;
}

void  Xbost4::Show()
{
    Strel0::Show1();
    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    klt(x, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    Strel0::Show2();
}
TYP  Xbost4::GetType()
{
    return XBOST4;
}

void  Kus1::Show() {}
TYP  Kus1::GetType()
{
    return KUS1;
}

void  Kus2::Show() {}

TYP  Kus2::GetType()
{
    return KUS2;
}
long Sicl = 0;

extern T_GetSigName_Func _GetSigName_Func;
static String _PerName = "";
const char * P_Sve::GetName()
{
    _PerName = Strel::GetName();
    if (_PerName != "") return _PerName.c_str();
    if (_GetSigName_Func != NULL)_PerName = _GetSigName_Func(GetRealImp(impuls_busi));
    else _PerName = "?";
    return _PerName.c_str();
}

int  P_Sve::GetSubType()
{
    switch (AO->TypPere) {
    case 32: return 32;
    case 321: return 321;
    default: return masy;
    }
}

void P_Sve::UpdateState()
{
    //int i1,i2,i3,i4,i5;
    Strel::UpdateState();
    clrl = C_D;
    clrt = FON;
    clr = FON;
    clrz = FON;
    switch (AO->TypPere) {
    case 32:  if (fimpuls_plus) clrt=COLOR_PSV; else  clrt=FON;
        if (fimpuls_kmu)  clrz = KRA; else        clrz = FON;
        if (fimpuls_busi == 1)            clrl = KRA;
        if (fimpuls_busi == 0)            clrl = ZEL;
        break;

    case 321: if (fimpuls_plus) clrt=COLOR_PSV; else   clrt=FON;
        clrl = TXT;
        if (fimpuls_busi == 1)    clrl = KRA;
        if (fimpuls_kmu == 1)     clrl = ZEL;
        if ((impuls_busi == 0) && (impuls_plus)) clrl = C_D;
        break;
    default:
        clr = FON;
        clrl = C_D;
        if (masy == 1) {
            int cc = fimpuls_busi * 1 + fimpuls_plus * 2 + fimpuls_mnus * 4 + fimpuls_kzm * 8;
            if ((cc >= 32) || (fimpuls_busi == 33)) {
                clr = BIRUZOVIJ;
            } else {
                clr = PerSvetStateColors[cc][0];
                clrl = PerSvetStateColors[cc][1];
            }
            if ((CurrentPicture == BG) &&
                    (fimpuls_busi + fimpuls_plus + fimpuls_mnus + fimpuls_kzm == 0) &&
                    (fimpuls_kmu == 0)
               ) {
                clr = FON; clrl = FON;
            }
        } else if (masy == 2) {
            int fzakr = fimpuls_busi;
            int pit1fid = impuls_plus;
            int pit2fid = impuls_mnus;
            int lamp1A = impuls_kzm;
            int lamp1B = impuls_kmu;
            int fpit1fid = fimpuls_plus;
            int fpit2fid = fimpuls_mnus;
            int flamp1A = fimpuls_kzm;
            int flamp1B = fimpuls_kmu;

            int fap = fimpuls_mu;
            int lamp2A = impuls_IR;
            int lamp2B = impuls_PKS;
            int flamp2A = fimpuls_IR;
            int flamp2B = fimpuls_PKS;

            int fpit = 0;
            if ((pit1fid != 0) && (fpit1fid == 1)) fpit = 1;
            if ((pit2fid != 0) && (fpit2fid == 1)) fpit = 1;
            if ((lamp1A != 0) && (flamp1A == 1)) fpit = 1;
            if ((lamp2A != 0) && (flamp2A == 1)) fpit = 1;
            if ((lamp1B != 0) && (flamp1B == 1)) fpit = 1;
            if ((lamp2B != 0) && (flamp2B == 1)) fpit = 1;

            int cc = fpit * 4 + fap * 2 + fzakr * 1;
            if ((cc >= 8) || (fimpuls_busi == 33)) {
                clrl = C_D;
                clr = BIRUZOVIJ;
            } else {
                clr = PerSvetStateColors3[cc][0];
                clrl = PerSvetStateColors3[cc][1];
            }


            if ((CurrentPicture == BG) &&
                    (fpit1fid + fpit2fid + flamp1A + flamp1B + flamp2A + flamp2B + fzakr + fap == 0)
               ) {
                clr = FON; clrl = FON;
            }
        } else if (masy == 3) {
            //int fzakr=fimpuls_busi;
            int pit1fid = impuls_plus;
            int pit2fid = impuls_mnus;
            int fpit1fid = fimpuls_plus;
            int fpit2fid = fimpuls_mnus;
            int fzakrdsp = fimpuls_kzm;
            //int flamp1B=fimpuls_kmu;

            int fap = fimpuls_mu;
            //int flamp2A=fimpuls_IR;
            //int flamp2B=fimpuls_PKS;

            int fpit = 0;
            if ((pit1fid != 0) && (fpit1fid == 1)) fpit = 1;
            if ((pit2fid != 0) && (fpit2fid == 1)) fpit = 1;
            int cc = fpit * 4 + fap * 2 + fzakrdsp * 1;
            if ((cc >= 8) || (fimpuls_busi == 33)) {
                clrl = C_D;
                clr = BIRUZOVIJ;
            } else {
                clr = TonnelStateColors[cc][0];
                clrl = TonnelStateColors[cc][1];
            }


        } else if (masy == 4) {
             // переезд ЭЦ12
            int fzakr = fimpuls_busi;   //  закрытие
            int fap1 = fimpuls_plus;     //  авария 1
            int fizv = fimpuls_mnus;     //  извещение/закрытие
            int fispr = fimpuls_kzm;    //  исправность
            int fap2 = fimpuls_kmu;     //  авария 2
            clrl = C_D;
            clr = FON;
            if (fzakr == 33) {
                clr = BIRUZOVIJ;
            } else {
                if (fispr==1) clrl=TXT;
                if ((fap1==1)||(fap2==1)) clrl=COLOR_PSV;
                if (fizv==1) clr=KRA_SER;
                if (fzakr==1) clr=KRA;

            }

        } else {
            if (fimpuls_busi) clr = KRA;
            if (fimpuls_plus) {
                if (AO->LUDOCHKA == 1) clr = COLOR_PSV; else  clrl = COLOR_PSV;
            } else if (impuls_kmu != -2) {
                if (fimpuls_kmu)  clr = FON;
                if (fimpuls_kmu == fimpuls_busi) {
                    clr = TXT; clrl = TXT;
                }
            }
            /*if(
               ((fimpuls_mnus==0)&&(fimpuls_kzm==0)&&(clr!=TXT)) &&
               (CurrentPicture==BG)){
               if((set[0]==99)&&(MOD!=ED))return;
               clr = FON;clrl=FON;
               set[0]=99;
            }else{
                  set[0] = clr;
            } */
        }
    }
    if ((IsClrMig(clr)) ||
            (IsClrMig(clrl))) StateChanged = true;
}



void  P_Sve::Show()
{
    Strel::Show();
//xx=x;

    int s;
    int xx;
    int x2;
    int y2;
    int y3;
    int len, sh;

    if (MOD == ED) {
        clrl = C_D;
        clrt = FON;
        clr = FON;
        clrz = FON;
    }

    switch (AO->TypPere) {
    case 32:
        //  Ну значить это изображение перезда - согласно ОСТ32
        // Основываясь тока на сигналах занятия? аварии и ОГРАЖДЕНИЯ

        s = MUL_Y / 3;
        xx = x - MUL_X / 3;
        x2 = x + MUL_X / 3;
        //  ЗДЕСЬ СДЕЛАНЫ ИЗМЕНЕНИЯ ДЛЯ 2Х2
        if (AO->_2X2_)
            y3 = y - (10 + mas) * MUL_Y;
        else
            y3 = y - (5 + mas) * MUL_Y;
        y2 = y;
        y  = y3;
        //АВАРИЯ !!!!
        setcolor(clrt);

        _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
        OutTextXY(xx + s / 2, y - s*2, "Ђ");

        // заграждение
        setcolor(clrz);
        line(xx - s, y, xx - s, y2);
        line(x2 + s, y, x2 + s, y2);

        setcolor(clrl);

        if (CurrentPicture == LT)
            setlinestyle(SOLID_LINE, 0, 3);
        else
            setlinestyle(SOLID_LINE, 0, 1);
        line(xx, y, xx, y2);
        line(xx - s, y2 + s, xx, y2);
        line(xx - s, y - s, xx, y);
        line(x2, y, x2, y2);
        line(x2 + s, y - s, x2, y);
        line(x2 + s, y2 + s, x2, y2);

        setlinestyle(SOLID_LINE, 0, 1);


        break;
    case 321:

        //  Ну значить это изображение перезда - согласно ОСТ32
        // нО без ограждения и с учетом 3-х сигналов !

        s = MUL_Y / 3;
        xx = x - MUL_X / 3;
        x2 = x + MUL_X / 3;
        //  ‡„…‘њ ‘„…‹ЂЌ› €‡Њ…Ќ…Ќ€џ „‹џ 2•2
        if (AO->_2X2_)
            y3 = y - (10 + mas) * MUL_Y;
        else
            y3 = y - (5 + mas) * MUL_Y;
        y2 = y;
        y  = y3;
        //Ђ‚Ђђ€џ !!!!
        if (impuls_plus) {
            setcolor(clrt);
            _SetText(F_DEFAULT, CENTER_TEXT, CENTER_TEXT);
            OutTextXY(xx + s / 2, y - s*2, "Ђ");
        }

        setcolor(clrl);


        if (CurrentPicture == LT)
            setlinestyle(SOLID_LINE, 0, 3);
        else
            setlinestyle(SOLID_LINE, 0, 1);
        line(xx, y, xx, y2);
        line(xx - s, y2 + s, xx, y2);
        line(xx - s, y - s, xx, y);
        line(x2, y, x2, y2);
        line(x2 + s, y - s, x2, y);
        line(x2 + s, y2 + s, x2, y2);
        setlinestyle(SOLID_LINE, 0, 1);


        break;
    default:
        //  Это старое изображение !


        xx = x;//-MUL_X/3;
        sh  = (sv_ras_y[MUL_Y] * 2) / 3;
        len = sv_ras_y[MUL_Y] * 2;

        if (masy == 3) {
            int len = (S_WAY_X + mas) * MUL_X;
            TPoint P[2][4] ;
            // 1\-------------/ 2
            //  0\___________/ 3
            //  Y1------------------
            int dy = sh_y / 2;
            int d2 = MUL_X / 2;
            int shy = sh_y;
            P[0][0] = TPoint(xx + d2 + shy  , y - sh_y / 2 - dy);
            P[0][1] = TPoint(xx + d2      , P[0][0].y - shy);
            P[0][2] = TPoint(xx + len - d2  , P[0][1].y);
            P[0][3] = TPoint(xx + len - d2 - shy, P[0][0].y);
            P[1][0] = TPoint(P[0][0].x  , y + sh_y / 2 + dy);
            P[1][1] = TPoint(P[0][1].x  , P[1][0].y + shy);
            P[1][2] = TPoint(P[0][2].x  , P[1][1].y);
            P[1][3] = TPoint(P[0][3].x  , P[1][0].y);
            int clrF[4] = {clrl, clrl, clrl, clrl};
            PolyColor(clr, P[0], clrF, 4);
            PolyColor(clr, P[1], clrF, 4);
        } else {
            setcolor(clrl);
            setfillstyle(1, clr);
            if (clr == TXT) setfillstyle(1, FON);

            line(xx, y, xx, y - len - len / 2);
            line(xx - len / 2, y, xx + len / 2, y);
            line(xx - len / 2, y - len, xx + len / 2, y - len);
            line(xx - len / 2, y - len, xx + len / 2, y - len);

            fillellipse(xx - len / 2, y - len, sh, sh);
            fillellipse(xx + len / 2, y - len, sh, sh);
            if (CurrentPicture != BG) {
                setcolor(TXT);
                _SetText(F_LITT, CENTER_TEXT, CENTER_TEXT);
                /*if(name[0]!='1')*/   OutTextXY(xx, y + 7, name);
            }
        }
        break;
    }

}

Bash::Bash()
{
    tip = 0;
    pencol = C_D;
    fillcol = FON;
    ColorNum = 0;
}

static String _BashName = "";
const char * Bash::GetName()
{
    if (_GetSigName_Func != NULL) {
        if (impuls_busi > 1000) _BashName = _GetSigName_Func(GetRealImp(impuls_busi)); else if (impuls_plus > 1000) _BashName = _GetSigName_Func(GetRealImp(impuls_plus));
    } else _BashName = "?";
    return _BashName.c_str();
}

int  Bash::GetSubType()
{
    int stip = atoi(name);
    if (stip == 0) stip = nomer;
    //if (stip < 10) return 0;
    return stip;
}

void Bash::UpdateState()
{
    int i1, i2, i3, i4, i5;
    Strel::UpdateState();

    tip = atoi(name);
    if (tip == 0) tip = nomer;

    i1 = fimpuls_busi;
    i2 = fimpuls_plus;
    i3 = fimpuls_mnus;
    i4 = fimpuls_kzm;
    i5 = fimpuls_kmu;

    pencol = C_D;

    if ((i1 == 33) ||
            (i2 == 33) ||
            (i3 == 33) ||
            (i4 == 33) ||
            (i5 == 33)) {

        fillcol = BIRUZOVIJ;
    } else {
        if (tip == 14) {
            if (i1 <= 1) i1 = 1 - i1;
            if (i2 <= 1) i2 = 1 - i2;
            if (i3 <= 1) i3 = 1 - i3;
            if (i4 <= 1) i4 = 1 - i4;
            if (i5 <= 1) i5 = 1 - i5;
            ColorNum = i1 * 8 + i2 * 4 + i3 * 2  + i4;
        }
        ColorNum = i1 * 8 + i2 * 4 + i3 * 2  + i4;
        fillcol = FON;
        switch (tip) {
        default : if (AO->TypRAMK==1) fillcol = ColorBash2[i1*8 + i2*4 + i3*2  +i4]; else
                fillcol = ColorBash[i1*8 + i2*4 + i3*2  +i4];
            break;
        case 10 : if (ColorNum<16) fillcol=UKSPSColors[ColorNum][1]; else fillcol=BIRUZOVIJ;
            if (ColorNum < 16) pencol = UKSPSColors[ColorNum][0]; else fillcol = C_D;
            break;
        case 11 : if (ColorNum<16) pencol =SAUTPenColors[ColorNum]; else pencol =C_D;
            fillcol = FON;
            break;
        case 12 :
        case 14 : if (ColorNum<16) pencol =KGUPenColors[ColorNum]; else pencol =C_D;
            break;
        case 13 : if (ColorNum<16) pencol =DISKPenColors[ColorNum]; else pencol =C_D;
            if (ColorNum < 16) fillcol = DISKFillColors[ColorNum]; else fillcol = BIRUZOVIJ;
            break;
        case 15 : if (fimpuls_busi==33) fillcol=BIRUZOVIJ; else if (MOD == RD) {
                if (ColorNum < 16) pencol = BASH15Colors[ColorNum][1]; else pencol = C_D;
                if (ColorNum < 16) fillcol = BASH15Colors[ColorNum][0]; else fillcol = BIRUZOVIJ;
            }
            break;
        case 16 : if (ColorNum>0) pencol =C_D; else pencol =FON1;
            if (ColorNum > 0) fillcol = TXT; else fillcol = FON;
            break;
        case 17 : if (ColorNum<16) pencol =UTSStateColors[ColorNum][1]; else pencol =C_D;
            if (ColorNum < 16) fillcol = UTSStateColors[ColorNum][0]; else fillcol = BIRUZOVIJ;
            break;
        }
        // для УЧАСТКА
        if (CurrentPicture == BG) {
            switch (tip) {
            default : break;
            case 10 : if ((ColorNum<16)&&(UKSPSColors[ColorNum][2]==0)) {
                    fillcol = FON; pencol = FON;
                }
                break;
            case 11 :
            case 12 :
            case 14 :
            case 13 :
            case 15 : if (fimpuls_kmu!=1) {
                    fillcol = FON; pencol = FON;
                }
                break;
            case 16 :break;
            case 17 :if (ColorNum==0) {
                    fillcol = FON; pencol = FON;
                } break;
            }
        }

    } // if 33

    // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
    if ((IsClrMig(fillcol)) ||
            (IsClrMig(pencol))) StateChanged = true;

}

void  Bash::Show()
{
    Strel::Show();

    int len, sh;
    //int c;
    int Bs[8];
    int s = sh_y / 2 + 2;
    int yy = y - s;

    sh  = (sv_ras_y[MUL_Y]) * 2;

    len = sh * 2;
    //setcolor(C_D);
    tip = atoi(name);
    if (tip == 0) tip = nomer;

//     if(tip==0){
    Bs[0] = x;     Bs[1] = yy;
    Bs[2] = x + len; Bs[3] = yy;
    Bs[4] = x + len; Bs[5] = yy - sh;
    Bs[6] = x;     Bs[7] = yy;
//    }
    if (tip == 1) {
        Bs[0] = x;     Bs[1] = yy   - MUL_Y / 3;
        Bs[2] = x + len; Bs[3] = yy   - MUL_Y / 3;
        Bs[4] = x + len; Bs[5] = yy + sh - MUL_Y / 3;
        Bs[6] = x;     Bs[7] = yy   - MUL_Y / 3;
    }
    if (tip == 2) {
        Bs[0] = x;     Bs[1] = yy;
        Bs[2] = x + len; Bs[3] = yy;
        Bs[4] = x;     Bs[5] = yy - sh;
        Bs[6] = x;     Bs[7] = yy;
    }
    if (tip == 3) {
        Bs[0] = x;     Bs[1] = yy   - MUL_Y / 3;
        Bs[2] = x + len; Bs[3] = yy   - MUL_Y / 3;
        Bs[4] = x;     Bs[5] = yy + sh - MUL_Y / 3;
        Bs[6] = x;     Bs[7] = yy   - MUL_Y / 3;
    }


    if (tip == 4) {
        Bs[0] = x;     Bs[1] = yy;
        Bs[2] = x + sh ; Bs[3] = yy;
        Bs[4] = x + sh ; Bs[5] = yy - len;
        Bs[6] = x;     Bs[7] = yy;
    }
    if (tip == 5) {
        Bs[0] = x;     Bs[1] = yy   - MUL_Y / 3;
        Bs[2] = x + sh;  Bs[3] = yy   - MUL_Y / 3;
        Bs[4] = x + sh;  Bs[5] = yy + len - MUL_Y / 3;
        Bs[6] = x;     Bs[7] = yy   - MUL_Y / 3;
    }
    if (tip == 6) {
        Bs[0] = x;     Bs[1] = yy;
        Bs[2] = x + sh;  Bs[3] = yy;
        Bs[4] = x;     Bs[5] = yy - len;
        Bs[6] = x;     Bs[7] = yy;
    }
    if (tip == 7) {
        Bs[0] = x;     Bs[1] = yy   - MUL_Y / 3;
        Bs[2] = x + sh;  Bs[3] = yy   - MUL_Y / 3;
        Bs[4] = x;     Bs[5] = yy + len - MUL_Y / 3;
        Bs[6] = x;     Bs[7] = yy   - MUL_Y / 3;
    }


    setfillstyle(1, fillcol);
    setcolor(pencol);

    /* 21/06/2002   */
    /*      УКСПС   */

    if (tip == 10) {
        //if((CurrentPicture==BG)&&(ColorNum<16)&&(UKSPSColors[ColorNum][2]==0)) return;

        line(x, y - sh_y*1.5 - masy, x, y + sh_y*1.5 + masy);
        fillellipse(x, y - sh_y*1.5 - masy, sh_y / 2 + 1, sh_y / 2 + 1);
        fillellipse(x, y + sh_y*1.5 + 1 + masy, sh_y / 2 + 1, sh_y / 2 + 1);
        return;
    }
    /*      САУТ      */
    if (tip == 11) {
        //if((CurrentPicture==BG)&&(fimpuls_kmu!=1)) return;
        switch (mas) {
        case 0: barx(x, y-sh_y/2-1, x+sh_y*2, y-1.5*sh_y-1); break;
        case 1: barx(x, y+sh_y/2+1, x+sh_y*2, y+1.5*sh_y+1); break;
        case 2: barx(x, y-sh_y/2-2, x+sh_y*2, y-1.5*sh_y-2); break;
        case 3: barx(x, y+sh_y/2+2, x+sh_y*2, y+1.5*sh_y+2); break;
        default:barx(x, y-sh_y/2-1, x+sh_y*2, y-1.5*sh_y-1);
        }
        return;
    }
    /*    КГУ      */
    if ((tip == 12) || (tip == 14)) {
        if ((MOD!=ED)&&(CurrentPicture==BG) && (fimpuls_kmu==0) && (fimpuls_busi==0)) return;
        //if((CurrentPicture==BG)&&(fimpuls_kmu!=1)) return;
        int sx = mas * MUL_X / 3;
        int sy = masy * MUL_Y / 2;
        int dy = sh_y / 4 + 1;

        line(x, y - sh_y, x + sx, y - sh_y);
        line(x + sx, y - sh_y, x + sx, y + sh_y + sy);
        line(x + sx, y + sh_y + sy, x, y + sh_y + sy);
        line(x, y - sh_y - dy, x, y - sh_y + dy);
        line(x, y + sh_y + sy - dy, x, y + sh_y + sy + dy);
        return;
    }
    /*    ДИСК  ПАД    */

    if ((tip == 13) || (tip == 16)) {
        //if((CurrentPicture==BG)&&(fimpuls_kmu!=1)) return;
        switch (mas) {
        default:
        case 0:Bs[0]=x;            Bs[1]=y-sh_y/2-1;
            Bs[2] = x - sh_y / 2 - 1;   Bs[3] = y - 1.5 * sh_y - 2;
            Bs[4] = x + sh_y / 2 + 1;   Bs[5] = y - 1.5 * sh_y - 2;
            Bs[6] = x;            Bs[7] = y - sh_y / 2 - 1;
            break;
        case 1:Bs[0]=x;            Bs[1]=y+sh_y/2+1;
            Bs[2] = x - sh_y / 2 - 1;   Bs[3] = y + 1.5 * sh_y + 2;
            Bs[4] = x + sh_y / 2 + 1;   Bs[5] = y + 1.5 * sh_y + 2;
            Bs[6] = x;            Bs[7] = y + sh_y / 2 + 1;
            break;
        }
        fillpoly(4, Bs);
        return;
    }

    /*      ЯЧЕЙКА    */
    if (tip == 15) {
        //if((CurrentPicture==BG)&&(fimpuls_kmu!=1)) return;
        // не рисуем если не активно
        if (MOD == ED) {
            pencol = C_D;
            fillcol = FON;
            setfillstyle(1, fillcol);
            setcolor(pencol);
        }

        int y_sdv = 1;
        int x_sdv = 1;
        int wy = sh_y;
        int wx = sh_y * 1;
        int y_off = sh_y / 2;
        switch (mas) {
        default: y_sdv=1; break;
        case 1 :
        case 11: y_sdv=2; break;
        }
        switch (masx2) {
        default: x_sdv=1; break;
        case 1 : x_sdv=-1-sh_y*1; break;
        case 2 : x_sdv=-1-sh_y*0.5; break;
        }
        switch (masy) {
        default: wy=sh_y; break;
        case 1 : wy=sh_y/2; break;
        }
        if (mas < 10) {
            barx(x + x_sdv, y - y_off - y_sdv, x + x_sdv + wx, y - y_off - wy - y_sdv);
            barx(x + x_sdv, y + y_off + y_sdv + 1, x + x_sdv + wx, y + y_off + wy + y_sdv);
        } else {
            pie(x + x_sdv, y - y_off - y_sdv + wy, x + x_sdv + wx, y - y_off - wy - y_sdv,
                x + x_sdv + wx , y - y_off - y_sdv, x + x_sdv, y - y_off - y_sdv);
            pie(x + x_sdv, y + y_off + y_sdv - wy, x + x_sdv + wx, y + y_off + wy + y_sdv,
                x + x_sdv, y + y_off + y_sdv, x + x_sdv + wx , y + y_off + y_sdv);
        }

        return;
    }

    /*      УТС    */
    if (tip == 17) {
        int x1, x2, y1, y2, x11, x21, y11, y21;
        int tr[8];
        int swop;
        int chn = mas;
        //if((CurrentPicture==BG)&&(fimpuls_kmu!=1)) return;
        // не рисуем если не активно
        if (MOD == ED) {
            pencol = C_D;
            fillcol = FON;
            setfillstyle(1, fillcol);
            setcolor(pencol);
        }
        x1 = x + 1                  ;
        x2 = x + MUL_X              ;
        y1 = y - sh_y / 2 - 1 - 1         ;
        y2 = y - sh_y / 2 - 1 - 1 - sh_y / 2     ;

        x11 = x + 1                  ;
        x21 = x + MUL_X              ;
        y11 = y - sh_y / 2 + sh_y + 1 + 1    ;
        y21 = y - sh_y / 2 + sh_y + 1 + 1 + sh_y / 2;
        if (!chn) {
            swop = x1; x1 = x2; x2 = swop;
            swop = x11; x11 = x21; x21 = swop;
        }
        tr[0] = x1 ; tr[1] = y1;
        tr[2] = x2 ; tr[3] = y1;
        tr[4] = x2 ; tr[5] = y2;
        tr[6] = x1 ; tr[7] = y1;
        fillpoly(4, tr);
        tr[0] = x11 ; tr[1] = y11;
        tr[2] = x21 ; tr[3] = y11;
        tr[4] = x21 ; tr[5] = y21;
        tr[6] = x11 ; tr[7] = y11;
        fillpoly(4, tr);
        return;
    }

    /* 05.08.2002  */
    fillpoly(4, Bs);
}



Strel::Strel()
{
    impuls_plus = 0;
    impuls_mnus = 0;
    impuls_kzm = 0;
    impuls_kmu = 0;
    impuls_mu = 0;
    impuls_otc = 0;
    impuls_SPU = 0;
    impuls_AV = 0;
    impuls_block = 0;
    impuls_predSA = 0;
    impuls_predSEIR = 0;

    impuls_IR=0;
    impuls_PKS=0;
    impuls_ZS=0;
    impuls_ZS2=0;
    impuls_kmu2=0;
    impuls_mu2=0;

    fimpuls_IR=0;
    fimpuls_PKS=0;
    fimpuls_ZS=0;
    fimpuls_ZS2=0;
    fimpuls_kmu2=0;
    fimpuls_mu2=0;


    fimpuls_busi = 0;
    fimpuls_plus = 0;
    fimpuls_mnus = 0;
    fimpuls_kzm = 0;
    fimpuls_kmu = 0;
    fimpuls_otc = 0;
    fimpuls_SPU = 0;
    fimpuls_AV = 0;
    fimpuls_block = 0;
    fimpuls_predSA = 0;
    fimpuls_predSEIR = 0;

    impuls_otkl_plus=0;
    impuls_otkl_minus=0;
    fimpuls_otkl_plus=0;
    fimpuls_otkl_minus=0;

    impuls_predSAplus=0;
    impuls_predSAminus=0;
    fimpuls_predSAplus=0;
    fimpuls_predSAminus=0;

    nomer = 0;
    memset(Prz, 0, sizeof(Prz));
    memset(name, 0, sizeof(name));
    InvertStrel = false;
    bText = false;
    bShowPol = false;

}
Strel0::Strel0()
        : Strel()
{
    is = 2;
    styll1 = 1;
    styll2 = 1;
    styll3 = 1;
    cbord1 = C_D;
    cbord2 = C_D;
    bShowInSpyMarsh = false;
    clr = LIN;
    /*bSetIs=true;
    bSetClr=true;
    bSetStyll=true;
    bSetcbord=true;*/

}










void  SRTopW::Show()
{
    Strel0::Show1();
    int s4 = len_4;
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1] + 1, 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);
    krt(x, y, Len, 1);

    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);

    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    len_4 = s4;

    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    int m__ = mas__;
    mas__ = 0;
    len = (STREL_X + mas) * MUL_X;
    klb(x + Len, y, len, 1);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    mas__ = m__;
    Strel0::Show2();
}
TYP  SRTopW::GetType()
{
    return SWrtW;
}

void  SRBotW::Show()
{
    Strel0::Show1();
    int s4 = len_4;
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1] + 1, 1, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 1);
    if ((CurrentPicture == LT) && (AO->MaxX > 801))  y_text += Z66;

    krb(x, y, Len, 0);
    if (((Len + mas__) >= 0) && (mas__ < 0))
        L(x - mas__, y, Len);
    else
        L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    len_4 = s4;

    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    int m__ = mas__;
    mas__ = 0;
    klt(x + Len, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    mas__ = m__;
    Strel0::Show2();

}
TYP  SRBotW::GetType()
{
    return SWrbW;
}
void  SLBotW::Show()
{
    Strel0::Show1();
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    int s4 = len_4;
    x_text = X_Text(Len, x, Prz[1] + 1, 0, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 1);
    if ((CurrentPicture == LT) && (AO->MaxX > 801))  y_text += Z66;
    klb(x, y, Len, 0);
    L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    len_4 = s4;
    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    int m__ = mas__;
    mas__ = 0;
    krt(x - Len, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    mas__ = m__;
    Strel0::Show2();
}
TYP  SLBotW::GetType()
{
    return SWlbW;
}
void  SLTopW::Show()
{
    Strel0::Show1();
    int s4 = len_4;
    Len = (STREL_X + mas) * MUL_X;
    int x_text, y_text;
    x_text = X_Text(Len, x, Prz[1] + 1, 0, dlen(nomer, name));
    y_text = Y_Text(Len, y, Prz[1], 0);
    klt(x, y, Len, 0);
    L(x, y, Len);
    Strelka(is, SZ, styll1, styll2, clr, nomer, x_text, y_text, name, InvertStrel, cbord1, cbord2, bShowPol);
    len_4 = s4;


    int n = atoi(name + 1);
    int bord_act = BLUE_m;
    setcolor(BLUE_m);
    if (sh_y <= 2) {
        bord_act = BLUE_mmm; if (clr != LIN)bord_act = clr; else clr = BLUE_mmm; setcolor(BLUE_mmm);
    }
    int len;
    int Save_sh = sh;
    if (n > 0) sh = sh * (n + 1) - sh_y * n;
    len = (STREL_X + mas) * MUL_X;
    int m__ = mas__;
    mas__ = 0;
    krb(x - Len, y, len, 0);
    setfillstyle(styll1, clr);
    setcolor(bord_act);
    if (sh_y == 0)
        drawpoly(7, kr);
    else
        fillpoly_z(7, kr, clr, Prz[0]);
    sh = Save_sh;
    mas__ = m__;
    Strel0::Show2();
}
TYP  SLTopW::GetType()
{
    return SWltW;
}





void Strel0::ShowTrainNumber()
{
    if ((fimpuls_kmu == 0) && (fimpuls_mu == 0)) //отсечка
        EXD_ShowTrainNumber(this, fimpuls_busi);
};
void Strel0::HideTrainNumber()
{
    EXD_HideTrainNumber(this);
};

void Strel0::ShowStik(int xx, int yy, int prSTIK)
{
    if ((prSTIK <= 0) || (CurrentPicture == BG)) return; // в режиме участка только разрыв
    if (prSTIK == 0) return;
    setcolor(BLUE_m);
    int st_st = sh_y / 2 + 2;
    switch (prSTIK) {
    default : break;
    case 11  : line(xx, yy-st_st, xx, yy+st_st+1); break;
    case 12  : line(xx, yy-st_st, xx, yy+st_st+1);
        circle(xx, yy, st_st + 2);
        break;
    case 21  : line(xx-st_st, yy, xx+st_st, yy); break;
    case 22  : line(xx-st_st, yy, xx+st_st, yy);
        circle(xx, yy, st_st + 2);
        break;
    case 61  : setcolor(RED);
        circle(xx, yy, st_st);
        break;
    }
}

/*
static String _SS_GetStrelInfo;
char * Strel0::GetStrelInfo()
{
    _SS_GetStrelInfo = "";
    //name;ObjID,inv;packet_name;busy;plus;minus;kzm
    String packet_name = "";
    String ss;
    int imp[4];
    String impname[4];
    imp[0] = impuls_busi;
    imp[1] = impuls_plus;
    imp[2] = impuls_mnus;
    imp[3] = impuls_kzm;
    char* CnlName;
    int RealOffset;
    for (int i = 0; i < 4; i++) {
        impname[i] = "";
        GetImpulsInfo(imp[i], CnlName, RealOffset);
        ss = String(CnlName);
        if ((packet_name == "") && (ss != "NONE")) packet_name = ss;
        if (_GetSigName_Func != NULL) {
            impname[i] = _GetSigName_Func(RealOffset);
        }
    }
    _SS_GetStrelInfo = String(GetName()) + ";" +
                       IntToStr(GetID()) + ";" +
                       IntToStr(InvertStrel) + ";" +
                       packet_name;
    for (int i = 0; i < 4; i++) {
        _SS_GetStrelInfo = _SS_GetStrelInfo + ";" + IntToStr(imp[i]) + ";" + impname[i];
    }
    return _SS_GetStrelInfo.c_str();
}
*/






















