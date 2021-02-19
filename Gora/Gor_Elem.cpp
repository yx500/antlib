//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include "Gor_Elem.h"


#include "common.h"
#include "comp.h"
#include "Vatempl.h"
#include "stan.h"
#include "polig.h"
#include "WinBgi.h"
#include "Impuls.h"
#include "Col.h"
#include "Gor_Logic.h"
#include "scrin.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
bool    IsClrMig(int Clr);
void ShowPictXY(int PictNumber, int x, int y, int WP, int HP);
typedef void *(*T_GetDatagramData_Func)(int typ, const char * PacketName);
extern T_GetDatagramData_Func GetDatagramData_Func;
String GorElemTypeName[9] = {"???", "РЦ", "ЗКР", "Стрелка", "Зам.инт", "Зам.парк", "Стрелка1", "Стрелка2", "РЦ2"};

int GetGorWayNum(Station *stan, int olegwaynum)
{
    // ищем все тп3 кзп2
    AComp * ac;
    for (int i = 0; i < Units_Size; i++){
        for (int j = 0; j < stan->POLE[i]->GetArraySize(); j++) {
            ac = stan->POLE[i]->GetObjPtr(j);
            if (ac->GetType() ==G_ZAMP ) {
               tG_ZAMP * zamp=dynamic_cast<tG_ZAMP *>(ac);
               if ((zamp->MinWay==olegwaynum)&&(zamp->PutPark!=0)) return zamp->PutPark;
            }
            if (ac->GetType() ==G_KZP2 ) {
               tG_KZP2 * kzp2=dynamic_cast<tG_KZP2 *>(ac);
               if (kzp2->mar==olegwaynum) return kzp2->PutPark;
            }
        }
    }
    return 0;
}

int PA(TPoint *P, ...)
{
   va_list ap;
   TPoint *arg;
   int cnt=0;
   va_start(ap, P);
   while ((arg = va_arg(ap,TPoint*)) != NULL) {
      P[cnt]=*arg;
      cnt++;
   }
   va_end(ap);
   return cnt;
}
int IA(int *P, ...)
{
   va_list ap;
   int *arg;
   int cnt=0;
   va_start(ap, P);
   while ((arg = va_arg(ap,int*)) != NULL) {
      P[cnt]=*arg;
      cnt++;
   }
   va_end(ap);
   return cnt;
}



bool IsGorElem(int T)
{
    if ((T >= G_STREL_Y) && (T <= G_STREL_2)) return true;
    return false;
}



tGRC0::tGRC0()
{

    for (int d = 0; d < 2; d++)
        for (int i = 0; i < 2; i++)
            stNext[d][i] = "";
    MinWay = 0;
    MaxWay = 0;
    Len = 0;
    PutPark = 0;
    bUseGAC = true;
    _tagptr=0;
    _tag=0;
    impuls_sv[0]=impuls_sv[1]=0;
    fimpuls_sv[0]=fimpuls_sv[1]=0;
}

static String _GRC_0_PropName[] = {
    "цфТипРЦ",      // 0
    "смТипРЦ",      // 1
    "тс_Занятие",   // 2
    "цфМин.путь",   // 3
    "цфМакс.путь",  // 4
    "цфДлина",      // 5
    "цфПутьПарка",  // 6
    "смСледующий",  // 7
    "смСледующий_мн",  // 8
    "смПредидующий",  // 9
    "смПредидующий_мн",  // 10
    "лгИспольз.ГАЦ",   // 11
    "цфМин.путь1",   // 12
    "цфМакс.путь1",  // 13
    "тс_Свет_0",     //14
    "тс_Свет_1"      //15


};


void tGRC0::GetPropMap(TPropMap &m)
{
    TY_Strel::GetPropMap(m);
    m.put(_GRC_0_PropName[0], GetGorElemType());
    m.put(_GRC_0_PropName[1], GorElemTypeName[GetGorElemType()].c_str());
    m.putEx(_GRC_0_PropName[2], OldImpToNewStr(impuls_busi, this), (void*)GetRealImp(impuls_busi));

    m.put(_GRC_0_PropName[3], MinWay);
    m.put(_GRC_0_PropName[4], MaxWay);
    m.put(_GRC_0_PropName[5], Len);
    m.put(_GRC_0_PropName[6], PutPark);
    for (int d = 0; d < 2; d++) {
        for (int i = 0; i < 2; i++) {
            m.put(_GRC_0_PropName[d*2+i+7], stNext[d][i]);
            /*if (pNext[d][i]==NULL)
               m.put( _GRC_StrelPropName[d*2+i+3],"NULL"); else
               m.put( _GRC_StrelPropName[d*2+i+3],pNext[d][i]->GetName());
            */
        }
    }
    m.put(_GRC_0_PropName[11], bUseGAC);
    m.put(_GRC_0_PropName[12], MinWay1,0);
    m.put(_GRC_0_PropName[13], MaxWay1,0);
    m.putEx(_GRC_0_PropName[14], OldImpToNewStr(impuls_sv[0], this), (void*)GetRealImp(impuls_sv[0]));
    m.putEx(_GRC_0_PropName[15], OldImpToNewStr(impuls_sv[1], this), (void*)GetRealImp(impuls_sv[1]));

}
void tGRC0::SetPropMap(TPropMap &m)
{
    TY_Strel::SetPropMap(m);
    impuls_busi = NewStrToOldImp(m.get(_GRC_0_PropName[2]).c_str());
    MinWay =    m.geti(_GRC_0_PropName[3]);
    MaxWay =    m.geti(_GRC_0_PropName[4]);
    Len =       m.geti(_GRC_0_PropName[5]);
    PutPark =       m.geti(_GRC_0_PropName[6]);
    for (int d = 0; d < 2; d++)
        for (int i = 0; i < 2; i++)
            stNext[d][i] = m.get(_GRC_0_PropName[d*2+i+7]);

    bUseGAC = (bool)m.geti(_GRC_0_PropName[11]);
    MinWay1 =    m.geti(_GRC_0_PropName[12]);
    MaxWay1 =    m.geti(_GRC_0_PropName[13]);
    impuls_sv[0] = NewStrToOldImp(m.get(_GRC_0_PropName[14]).c_str());
    impuls_sv[1] = NewStrToOldImp(m.get(_GRC_0_PropName[15]).c_str());


}

void tGRC0::UpdateState()
{
    TY_Strel::UpdateState();
    int rimpuls_sv[2];
    for (int i = 0; i < 2; i++) rimpuls_sv[i] = f(impuls_sv[i]);
    for (int i = 0; i < 2; i++) StateChanged = StateChanged | (rimpuls_sv[i] != fimpuls_sv[i]);
    for (int i = 0; i < 2; i++) fimpuls_sv[i] = rimpuls_sv[i];
}


//=============================================================

tG_Strel_Y::tG_Strel_Y()
{
    memset(impuls_pr, 0, sizeof(impuls_pr));
    memset(fimpuls_pr, 0, sizeof(fimpuls_pr));
    memset(TU_pr, 0, sizeof(TU_pr));
    memset(StrelName, 0, sizeof(StrelName));
    masx2 = 2;
    masy = 3;
    mas = 3;

    nomer = 1;
    NP[0] = TPoint(10, 10);
    NP[1] = TPoint(10, -10);
    frm_blok.clear();
    StrelPrizak[0] = 0;
    StrelPrizak[1] = 0;
    prSTIK[0] = 11; prSTIK[1] = 11; prSTIK[2] = 11;
}

void tG_Strel_Y::ShowFON()
{
     TPoint P3W[13] = {T[0], T[1],  T[3], T[5], T[6], T[7],  T[17], T_[7], T_[6], T_[5], T_[3], T_[1], T[13]};
    /* затирем фоном на случай изм. положения */
    {
        int clr3[13] = {   FON, FON, FON, FON, FON, FON, FON, FON, FON, FON, FON,   FON,  FON};
        PolyColor(FON, P3W, clr3, 13);
    }
}

void tG_Strel_Y::Show()
{
    Strel0::Show1();

    tGRC0::Show();


    CalcPRRTDS();
    ShowPR();
    ShowRTDS_IPD();

    int PW = 1;
    TPoint P3W[13] = {T[0], T[1],  T[3], T[5], T[6], T[7],  T[17], T_[7], T_[6], T_[5], T_[3], T_[1], T[13]};


    /*  НЕТ СИГН */
    if (_is == D) {
        setfillstyle(_styll3, clBP);
        TPoint P1[5] = {T[0], T[1], T[16], T_[1], T[13]};
        int fillclr1[5] = {clPP, clPP, clPP, clPP, clS1};
        TPoint P3[6] = {T[1], T[3], T[5], T[6], T[7], T[8]};
        int fillclr3M[6] = {   clPP, clPP, clS3, clPP, clPP, clPP};
        int fillclr3P[6] = {   clPP, clPP, clS2, clPP, clPP, clPP};
        TPoint P3_[6] = {T_[1], T_[3], T_[5], T_[6], T_[7], T_[8]};
        PolyColor(clBP, P1, fillclr1, 5, PW);
        PolyColor(clBP, P3, fillclr3M, 6, PW);
        PolyColor(clBP, P3_, fillclr3P, 6, PW);
    }
    /*  неопр */
    if (_is == W) {
        int fillclr3[13] = {   clPP, clPP, clPP, clS3, clPP, clPP, clPP,   clPP,  clS2,  clPP , clPP,  clPP, clS1};
        setfillstyle(_styll3, clBP); PolyColor(clBP, P3W, fillclr3, 13, PW);
    }
    /*  + */
    if (_is == P) {
        TPoint PM[6] = {Td[1], T[3], T[5], T[6], T[7], Td[2]};
        int fillclrM[6] = {    clPM, clPM, clS3, clPM, clPM, clPM};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, fillclrM, 6, PW);
        TPoint PP[10] = {T[0], T_[11], Td_[2], T_[7], T_[6], T_[5], T_[3], Td_[1], T_[1], T[13]};
        int fillclrP[10] = {   clPP,   clPP,   clPP,  clPP,  clS2,  clPP,  clPP,   clPP,  clPP,  clS1};
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, fillclrP, 10, PW);

    }
    /*  - */
    if (_is == M) {
        TPoint PM[10] = {T[0], T[1], Td[1], T[3], T[5], T[6], T[7], T[8], T[11], T[13]};
        int fillclrM[10] = {   clPM, clPM,  clPM, clPM, clS3, clPM, clPM,  clPM,  clPM, clS1};
        setfillstyle(_styll2, clBM); PolyColor(clBM, PM, fillclrM, 10, PW);
        TPoint PP[6] = {Td_[1], T_[3], T_[5], T_[6], T_[7], Td_[2]};
        int fillclrP[6] = {    clPP, clPP, clS2, clPP, clPP, clPP};
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, fillclrP, 6, PW);
    }



    // Вывод номера
    int textfillclr = BLUE_m;
    ShowStrelNum(x_n, y_n, textfillclr, StrelName);

    ShowStik(YP.M[1].x, YP.M[1].y, prSTIK[0]);
    ShowStik(YP.M[4].x, YP.M[4].y, prSTIK[2]);
    ShowStik(YP.M[6].x, YP.M[6].y, prSTIK[1]);
    if (MOD == ED) {
        if (stNext[1][0] == "") ShowStik(YP.M[1].x, YP.M[1].y, 61);
        if (stNext[0][1] == "") ShowStik(YP.M[4].x, YP.M[4].y, 61);
        if (stNext[0][0] == "") ShowStik(YP.M[6].x, YP.M[6].y, 61);

        // Отрисовываем места под номер
        if (bShowNumberPosition) {
            int _oldis = _is;
            int xn, yn;
            setcolor(GELT); _SetText(F_LITT, LEFT_TEXT, TOP_TEXT);
            _is = P; GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "+N"); fillellipse(xn, yn, 2, 2);
            _is = M; GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "-N"); fillellipse(xn, yn, 2, 2);
            _is = _oldis;
        }
    }

    if (bShowPol) ShowNormPol();

    Strel0::Show2();

}


int tG_Strel_Y::getospolyline(TPoint * PK,int Psz)
{
     int cntrez=0;
     if (Psz<4) return 0;
     if (_is == P)
        cntrez=PA(PK,&YP.M[1],&YP.M[0],&YP.M[5],&YP.M[6],NULL);
     if (_is == M)
        cntrez=PA(PK,&YP.M[1],&YP.M[0],&YP.M[3],&YP.M[4],NULL);
     return cntrez;

}

void tG_Strel_Y::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int Pol = _is;
    if (InvertStrel) {
        if (_is == P) Pol = M;
        if (_is == M) Pol = P;
    }
    if (Pol == P) {
        X = YP.M[0].x + NP[0].x * MUL_X / 10; Y = YP.M[0].y + NP[0].y * MUL_Y / 10;
    } else if (Pol == M) {
        X = YP.M[0].x + NP[1].x * MUL_X / 10; Y = YP.M[0].y + NP[1].y * MUL_Y / 10;
    } else {
        X = YP.M[0].x                 ; Y = YP.M[0].y                 ;
    }
}

bool tG_Strel_Y::CheckNegabarit()
{
    // проверяем негабарит
    tGRC0 * rc_next;
    for (int m = 0; m < 2; m++) {
        rc_next = dynamic_cast<tGRC0 *>(this->pNext[0][m]);
        for (int n = 0; n < StrelPrizak[m]; n++) {
            if ((rc_next != NULL) && (rc_next->fimpuls_busi == 1))
                return true;
            if (rc_next != NULL) rc_next = dynamic_cast<tGRC0 *>(rc_next->pNext[0][0]);
        }
    }
    return false;

}

void tG_Strel_Y::UpdateState()
{
    //Y_Strel_2.pVisibleArray=pVisibleArray;
    tGRC0::UpdateState();
    //StateChanged=Y_Strel_2.StateChanged;
    int rimpuls_pr[7];
    for (int i = 0; i < 8; i++) rimpuls_pr[i] = f(impuls_pr[i]);
    for (int i = 0; i < 8; i++) StateChanged = StateChanged | (rimpuls_pr[i] != fimpuls_pr[i]);
    for (int i = 0; i < 8; i++) fimpuls_pr[i] = rimpuls_pr[i];



    // расставляем цвета ручки
    for (int i = 0; i < 8; i++) {
        clrp[i] = FON; clrb[i] = FON;
        if (fimpuls_pr[i] == 33) {
            clrp[i] = C_D; clrb[i] = BIRUZOVIJ;
        }
    }

    // если нет занятия но есть кзп то рисуем красный кантик
    if ((fimpuls_busi == 0) && (fimpuls_pr[i_m] == 1)) {
        cbord1 = RED; cbord2 = RED;
    }

    if ((impuls_pr[i_sk ] != 0) && (fimpuls_pr[i_sk ] == 1)) {
        clrp[i_sk] = C_D; clrb[i_sk] = GELT;
        if (CheckNegabarit() == true)
            clrb[i_sk] = RED;
        if ((impuls_pr[i_uvk_block] != 0) && (fimpuls_pr[i_uvk_block] == 1))
                clrb[i_sk] = RED;

    }
    if ((impuls_pr[i_prp] != 0) && (fimpuls_pr[i_prp] == 1)) {
        clrp[i_prp] = GELT; clrb[i_prp] = RED;/*clrp[i_sk]=clrp[i_prp];*/
    }
    if ((impuls_pr[i_prm] != 0) && (fimpuls_pr[i_prm] == 1)) {
        clrp[i_prm] = GELT; clrb[i_prm] = RED;/*clrp[i_sk]=clrp[i_prm];*/
    }
    if ((impuls_pr[i_m  ] != 0) && (fimpuls_pr[i_m  ] == 1)) {
        clrp[i_m] = C_D; clrb[i_m] = RED;
    }
    if ((impuls_pr[i_ipd] != 0) && (fimpuls_pr[i_ipd] == 1)) {
        clrp[i_ipd] = RED; clrb[i_ipd] = RED;
    }

    if ((impuls_pr[i_ped1] != 0) && (fimpuls_pr[i_ped1] == 1)) {
        clrp[i_ipd] = GELT; clrb[i_ipd] = RED;/*clrp[i_sk]=clrp[i_prp];*/
    }
    if ((impuls_pr[i_ped2] != 0) && (fimpuls_pr[i_ped2] == 1)) {
        clrp[i_ipd] = GELT; clrb[i_ipd] = RED;/*clrp[i_sk]=clrp[i_prp];*/
    }
    if ((impuls_pr[i_uvk_block] != 0) && (fimpuls_pr[i_uvk_block] == 1)) {
        clrp[i_uvk_block] = RED; clrb[i_uvk_block] = RED;
    }

    fevFormulaSetR(this, frm_blokP);
    ffrm_blok = feFormulaResultP(frm_blokP);

}

static String _G_Strel_YPropName[] = {
    "тс_Плюс" ,     // 0
    "тс_Минус",     // 1
    "тс_ПРП",   // 2
    "тс_ПРМ",   // 3
    "тс_СК" ,   // 4
    "тс_М",     // 5
    "тс_ИПД",     // 6
    "тс_ПЕД1",     // 7
    "тс_ПЕД2",     // 8
    "тс_УВК_БЛОК",    // 9
    "цф_ТУ_ПРП",   // 10
    "цф_ТУ_ПРМ",   // 11
    "смИмя_стрелки",     // 12
    "цфНомерПлюсX",     // 13
    "цфНомерПлюсY",     // 14
    "цфНомерМинусX",    // 15
    "цфНомерМинусY",    // 16
    "лгНегабарит",    // 17
    "фсБлокировка",    // 18
    "цфПризнакПлюс",     // 19
    "цфПризнакМинус"     // 20
};

void tG_Strel_Y::SetPropMap(TPropMap &m)
{
    //Y_Strel_2.SetPropMap(m);
    tGRC0::SetPropMap(m);

    String N = m.get("смИМЯ");
    __int8 nn = N.ToIntDef(0);
    N = "$" + N;
    if ((nn != 0) && (nomer == 0)) nomer = nn;
    strncpy(name, N.c_str(), sizeof(name) - 1);
    N = m.get(_G_Strel_YPropName[12]);
    strncpy(StrelName, N.c_str(), 14);

    //impuls_plus = NewStrToOldImp(m.get(_G_Strel_YPropName[0]).c_str());
    //impuls_mnus = NewStrToOldImp(m.get(_G_Strel_YPropName[1]).c_str());

    for (int i = 0; i < 8; i++)
        impuls_pr[i] = NewStrToOldImp(m.get(_G_Strel_YPropName[i+2]).c_str());
    for (int i = 0; i < 2; i++)
        TU_pr[i] = m.geti(_G_Strel_YPropName[i+10]);


    NP[0].x = m.geti(_G_Strel_YPropName[13]);
    NP[0].y = m.geti(_G_Strel_YPropName[14]);
    NP[1].x = m.geti(_G_Strel_YPropName[15]);
    NP[1].y = m.geti(_G_Strel_YPropName[16]);

    bNegabarit = m.geti(_G_Strel_YPropName[17]);

    feSt2vFormula(m.get(_G_Strel_YPropName[18]).c_str(), frm_blok);
    fevFormulaElement2PolskaNota(frm_blok, frm_blokP);

    StrelPrizak[0] = m.geti(_G_Strel_YPropName[19]);
    StrelPrizak[1] = m.geti(_G_Strel_YPropName[20]);

}

void tG_Strel_Y::GetPropMap(TPropMap &m)
{
    //Y_Strel_2.GetPropMap(m);
    tGRC0::GetPropMap(m);
    m.putEx(_G_Strel_YPropName[0], OldImpToNewStr(impuls_plus, this), (void*)GetRealImp(impuls_plus), OldImpToNewStr(0, this));
    m.putEx(_G_Strel_YPropName[1], OldImpToNewStr(impuls_mnus, this), (void*)GetRealImp(impuls_mnus), OldImpToNewStr(0, this));
    for (int i = 0; i < 8; i++)
        m.putEx(_G_Strel_YPropName[i+2], OldImpToNewStr(impuls_pr[i], this), (void*)GetRealImp(impuls_pr[i]), OldImpToNewStr(0, this));
    for (int i = 0; i < 2; i++)
        m.put(_G_Strel_YPropName[i+10], TU_pr[i], 0);

    m.put(_G_Strel_YPropName[12], StrelName);

    m.put(_G_Strel_YPropName[13], NP[0].x, 0);
    m.put(_G_Strel_YPropName[14], NP[0].y, 0);
    m.put(_G_Strel_YPropName[15], NP[1].x, 0);
    m.put(_G_Strel_YPropName[16], NP[1].y, 0);
    m.put(_G_Strel_YPropName[17], bNegabarit, 0);
    m.put(_G_Strel_YPropName[18], fevFormula2St(frm_blok), "");
    m.put(_G_Strel_YPropName[19], StrelPrizak[0], 0);
    m.put(_G_Strel_YPropName[20], StrelPrizak[1], 0);


}

/* Вращение точки вокруг центра с координатами x_org и y_org на угол theta */
void rotate_point(double theta, TPoint &P, TPoint Pc)
{
    double tx, ty;
    /* нормализация X и Y к начальному адресу */
    tx = P.x - Pc.x; ty = P.y - Pc.y;
    /* вращение */
    P.x = tx * cos(theta) - ty * sin(theta);
    P.y = tx * sin(theta) + ty * cos(theta);
    /* возвращение значений координат */
    P.x += Pc.x; P.y += Pc.y;
}
void rotate_points(double theta, TPoint Pc, TPoint *Points, int Points_Count)
{
    for (int i = 0; i < Points_Count; i++)
        rotate_point(theta, Points[i], Pc);
}
void offset_points(int dx, int dy, TPoint *Points, int Points_Count)
{
    for (int i = 0; i < Points_Count; i++) {
        Points[i].x += dx; Points[i].y += dy;
    }
}

void tG_Strel_Y::CalcPRRTDS()
{
    rr = sh_y * 2;//MUL_Y/3;
    int dx0 = 3 * MUL_X;   // отступ до центра круга
    int dx1 = rr * 3 / 4;//MUL_Y*2/4; // отступ до ручки
    int dx2 = 1 * MUL_X;//MUL_Y;   // длина ручки
    int dx22 = rr;//1*MUL_X/2;//MUL_Y;   // длина треугольника
    int shpr = sh_y / 2;   // 1/2 ширины ручки
    int shpr2 = dx22 / 2 - shpr;   // отступ ширины треугольника
    int prd = 4; // отступ от ручки
    int n = 1;


    if (DX < 0) {
        n = -n;//dx0=-dx0;dx1=-dx1;dx2=-dx2;shpr=-shpr;Prdx=-Prdx;
    }
    Mr[0] = Point(YP.M[0].x + dx0 * n, YP.M[0].y);
    Mr[1] = Point(YP.M[0].x + dx0 * n, YP.M[0].y - rr);
    Mr[2] = Point(YP.M[0].x + dx0 * n, YP.M[0].y + rr);

    Tr[0] = Point(Mr[0].x + dx1 * n, Mr[0].y - shpr);
    Tr[1] = Point(Tr[0].x + dx2 * n, Tr[0].y);
    Tr[2] = Point(Tr[1].x      , Tr[1].y - shpr2);
    Tr[3] = Point(Tr[2].x + dx22 * n, Mr[0].y);
    Tr[6] = Point(Mr[0].x + dx1 * n, Mr[0].y + shpr);
    Tr[5] = Point(Tr[6].x + dx2 * n, Tr[6].y);
    Tr[4] = Point(Tr[5].x      , Tr[5].y + shpr2);


    Pr[0] = Point(Mr[0].x - (rr + prd) * n, Mr[1].y - prd);
    Pr[1] = Point(Tr[1].x + prd * n, Pr[0].y);
    Pr[2] = Point(Pr[1].x, Mr[2].y + prd);
    Pr[3] = Point(Pr[0].x, Pr[2].y);

    //rotate_points(M_PI_4,Mr[0],Mr,3);
    //rotate_points(-M_PI_4,Mr[0],Mr,3);
}

void tG_Strel_Y::ShowRTDS_IPD()
{
    if (MOD == ED) {
        clrp[i_m] = C_D; clrb[i_m] = FON1; clrb[i_ipd] = FON1;
        if (impuls_pr[i_m] == 0) {clrp[i_m] = FON;clrb[i_m] = FON;}
        if (impuls_pr[i_ipd] == 0) {clrp[i_ipd] = FON;clrb[i_ipd] = FON;}
    }
    /* затирем фоном на случай изм. положения */
    setfillstyle(SOLID_FILL, FON); setcolor(FON);
    bar(Mr[0].x - rr / 2 - 2, Mr[0].y - rr / 2 - 2, Mr[0].x + rr / 2 + 2, Mr[0].y + rr / 2 + 2);

    {
        setfillstyle(SOLID_FILL, clrb[i_ipd]);
        setcolor(clrp[i_ipd]);
        bar(Mr[0].x - rr / 2 - 3, Mr[0].y - rr / 2 - 3, Mr[0].x + rr / 2 + 2, Mr[0].y + rr / 2 + 2);
    }

    if ((fimpuls_pr[i_m] != 0) || ((MOD == ED) && (impuls_pr[i_m] != 0))) {
        setfillstyle(SOLID_FILL, clrb[i_m]);
        setcolor(clrp[i_m]);
        fillellipse(Mr[0].x, Mr[0].y, rr / 2, rr / 2);
    }
    {
        setfillstyle(SOLID_FILL, clrb[i_m]);
        setcolor(clrp[i_m]);
        fillellipse(Mr[0].x, Mr[0].y, rr / 2, rr / 2);
    }
}


void tG_Strel_Y::ShowPR()
{
    if (MOD == ED) {
        for (int i = 0; i < 4; i++) {
            clrp[i] = C_D; clrb[i] = FON1;
        }
    }

    //TPoint Pr [3]={Tr[0],Tr[1],Tr[2]};

    int DXS = sh_y;
    int DXS1 = sh_y / 2;
    if (DX < 0) {
        DXS = -DXS; DXS1 = -DXS1;
    }
    TPoint Prm2[3] = {Td[1], Td[1], T[2]}; Prm2[1].x -= DXS;
    TPoint Prm1[3] = {T[7], Td[2], Td[2]}; Prm1[1].x += DXS;
    offset_points(DXS1, 0, Prm1, 3); offset_points(-DXS1, 0, Prm2, 3);
    TPoint Prp2[3] = {Td_[1], Td_[1], T_[2]}; Prp2[1].x -= DXS;
    TPoint Prp1[3] = {T_[7], Td_[2], Td_[2]}; Prp1[1].x += DXS;
    offset_points(DXS1, 0, Prp1, 3); offset_points(-DXS1, 0, Prp2, 3);

    TPoint *Prpm[2][2] = {{Prp1, Prp2}, {Prm1, Prm2}};
    int PolPl = 0; int PolMn = 1;
    if (InvertStrel) {
        PolPl = 1; PolMn = 0;
    }

    /* затирем фоном на случай изм. положения */
    int clrF[7] = {FON, FON, FON, FON, FON, FON, FON};
    setfillstyle(SOLID_FILL, FON); setcolor(FON);
    //PolyColor(FON,Pr,clrF,4);
    PolyColor(FON, Prp1, clrF, 3);//PolyColor(FON,Prp2,clrF,3);
    PolyColor(FON, Prm1, clrF, 3);//PolyColor(FON,Prm2,clrF,3);
    PolyColor(FON, Tr, clrF, 7);

    // рисуем подложку под среднее положеие
    //if ((fimpuls_pr[i_sk ]==1)) {
    //   setfillstyle(SOLID_FILL,COLOR_GOR_A);setcolor(FON1);
    //   roundrect(Pr[0].x,Pr[0].y,Pr[2].x,Pr[2].y,sh_y,sh_y);
    //}


    if ((fimpuls_pr[i_prp] != 0) || ((MOD == ED) && (impuls_pr[i_prp] != 0))) {
        int clr1[3] = {clrp[i_prp], clrp[i_prp], clrp[i_prp]};
        PolyColor(clrb[i_prp], Prpm[PolPl][0], clr1, 3);//PolyColor(clrb[i_prp],Prpm[PolPl][1],clr1,3);
    }

    if ((fimpuls_pr[i_prm] != 0) || ((MOD == ED) && (impuls_pr[i_prm] != 0))) {
        int clr1[3] = {clrp[i_prm], clrp[i_prm], clrp[i_prm]};
        PolyColor(clrb[i_prm], Prpm[PolMn][0], clr1, 3);//PolyColor(clrb[i_prm],Prpm[PolMn][1],clr1,3);
    }
    // среднее положение

    if ((fimpuls_pr[i_sk ] != 0) || ((MOD == ED) && (impuls_pr[i_sk ] != 0))) {
        int clr1[7] = {clrp[i_sk], clrp[i_sk], clrp[i_sk], clrp[i_sk], clrp[i_sk], clrp[i_sk], clrp[i_sk]};
        PolyColor(clrb[i_sk], Tr, clr1, 7);
    }

}

//=============================================================

tG_Strel_1::tG_Strel_1()
{
    masx2 = 2;
    masy = 3;
    mas = 3;
    prSTIK[0] = 11; prSTIK[1] = 11; prSTIK[2] = 11;
    nomer = 1;
    tsMarshrut = 0;
}

void tG_Strel_1::Show()
{
    ///Y_Strel_1.X=X;Y_Strel_1.Y=Y;Y_Strel_1.mas=mas;Y_Strel_1.masx2=masx2;Y_Strel_1.masy=masy;
    //Y_Strel_1.Show();
    Strel0::Show1();
    TY_Strel::Show();

    TPoint P3W[10] = {T[0], T[1], T[3], T[5], T[6], T[7], T[8], T[9], T[10], T[13]};
    if (L2 <= 0) {
        P3W[7] = T[8]; P3W[8] = T[11];
    }
    /* затирем фоном на случай изм. положения */
    {
        int clr3[10] = {   FON, FON, FON, FON, FON, FON, FON, FON,  FON, FON};
        if (L2 <= 0) clr3[7] = clPP;
        PolyColor(FON, P3W, clr3, 10);
    }
    /*  НЕТ СИГН */
    if (_is == D) {
        setfillstyle(_styll3, clBP);
        TPoint P1[4] = {T[0], T[1], T[12], T[13]};
        int clr1[4] = {clPP, clPP, clPP, clS1};
        TPoint P3[6] = {T[1], T[3], T[5], T[6], T[7], T[8]};
        int clr3[6] = {   clPP, clPP, clS3, clPP, clPP, clPP};
        TPoint P2[4] = {T[8], T[9], T[10], T[11]};
        int clr2[4] = {   clPP, clS2, clPP, clPP};
        PolyColor(clBP, P1, clr1, 4);
        PolyColor(clBP, P3, clr3, 6);
        if (L2 > 0) {
            PolyColor(clBP, P2, clr2, 4);
        }
    }
    /*  неопр */
    if (_is == W) {
        int clr3[10] = {   clPP, clPP, clPP, clS3, clPP, clPP, clPP, clS2,  clPP, clS1};
        if (L2 <= 0)clr3[7] = clPP;
        setfillstyle(_styll3, clBP);PolyColor(clBP, P3W, clr3, 10);
    }
    /*  + */
    if (_is == P) {
        TPoint PM[6] = {Td[1], T[3], T[5], T[6], T[7], Td[2]};
        int clrM[6] = {    clPM, clPM, clS3, clPM, clPM, clPM};
        setfillstyle(_styll2, clBM);PolyColor(clBM, PM, clrM, 6);
        TPoint PP[4] = {T[0], T[9], T[10], T[13]};
        int clrP[4] = {    clPP, clS2, clPP, clS1};
        if (L2 <= 0) {
            PP[1] = T[8]; PP[2] = T[11];
            clrP[1] = clPP;
        }
        setfillstyle(_styll1, clBP); PolyColor(clBP, PP, clrP, 4);
    }
    /*  - */
    if (_is == M) {
        TPoint PM[8] = {T[0], T[1], T[3], T[5], T[6], T[7], T[11], T[13]};
        int clrM[8] = {   clPM, clPM, clPM, clS3, clPM, clPM,  clPM, clS1};
        setfillstyle(_styll2, clBM);PolyColor(clBM, PM, clrM, 8);
        if (L2 > 0) {
            TPoint PP[4] = {Td[3], T[9], T[10], Td[4]};
            int clrP[4] = {    clPP, clS2, clPP, clPP};
            setfillstyle(_styll1, clBP);PolyColor(clBP, PP, clrP, 4);
        }
    }
    // Вывод номера
    int textfillclr = BLUE_m;
    ShowStrelNum(x_n, y_n, textfillclr, StrelName);


    // проверяем связи
    ShowStik(YP.M[1].x, YP.M[1].y, prSTIK[0]);
    ShowStik(YP.M[4].x, YP.M[4].y, prSTIK[2]);
    ShowStik(YP.M[2].x, YP.M[2].y, prSTIK[1]);
    if (MOD == ED) {
        //if (idNext[1][0]==0) Y_Strel_1.ShowStik(Y_Strel_1.YP.M[1.x,Y_Strel_1.YP.M[1.y,61);
        //if (idNext[0][1]==0) Y_Strel_1.ShowStik(Y_Strel_1.YP.M[4.x,Y_Strel_1.YP.M[4.y,61);
        //if (idNext[0][0]==0) Y_Strel_1.ShowStik(Y_Strel_1.YP.M[2.x,Y_Strel_1.YP.M[2.y,61);
        // Отрисовываем места под номер
        if (bShowNumberPosition) {
            int _oldis = _is;
            int xn, yn;
            setcolor(GELT); _SetText(F_LITT, LEFT_TEXT, TOP_TEXT);
            _is = P; GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "+N"); fillellipse(xn, yn, 2, 2);
            _is = M; GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "-N"); fillellipse(xn, yn, 2, 2);
            _is = _oldis;
        }
    }

    if (bShowPol) ShowNormPol();
    Strel0::Show2();

}

void tG_Strel_1::ShowNormPol()
{
     setcolor(C_D);
    int clr1[4] = {   C_D, C_D, C_D, C_D};
    if (!InvertStrel){
       TPoint P1[4] = {TNPOL[0+0], TNPOL[0+1], TNPOL[0+2], TNPOL[0+3]};
       PolyColor(C_D, P1, clr1, 4);
    } else {
       TPoint P1[4] = {TNPOL[4+0], TNPOL[4+1], TNPOL[4+2], TNPOL[4+3]};
       PolyColor(C_D, P1, clr1, 4);
    }
}

void tG_Strel_1::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int Pol = _is;
    if (InvertStrel) {
        if (_is == P) Pol = M;
        if (_is == M) Pol = P;
    }
    if (Pol == P) {
        X = YP.M[0].x + NP[0].x * MUL_X / 10; Y = YP.M[0].y + NP[0].y * MUL_Y / 10;
    } else if (Pol == M) {
        X = YP.M[0].x + NP[1].x * MUL_X / 10; Y = YP.M[0].y + NP[1].y * MUL_Y / 10;
    } else {
        X = YP.M[0].x                 ; Y = YP.M[0].y                 ;
    }
}

int tG_Strel_1::getospolyline(TPoint * PK,int Psz)
{
    int cntrez=0;
     if (Psz<4) return 0;
     if (_is == P)
        cntrez=PA(PK,&YP.M[1],&YP.M[0],&YP.M[2],NULL);
     if (_is == M)
        cntrez=PA(PK,&YP.M[1],&YP.M[0],&YP.M[3],&YP.M[4],NULL);
     return cntrez;
}



void tG_Strel_1::UpdateState()
{
    tGRC0::UpdateState();

}

static String _G_Strel_1PropName[] = {
    "тс_Маршрут" ,     // 0
    "тс_Минус",     // 1
    "цфCтык1",     // 2
    "цфCтык2",     // 3
    "цфCтык3",     // 4
    "цфНомерПлюсX",     // 5
    "цфНомерПлюсY",     // 6
    "цфНомерМинусX",    // 7
    "цфНомерМинусY",    // 8
    "смИмя_стрелки"     // 9
};

void tG_Strel_1::SetPropMap(TPropMap &m)
{

    tGRC0::SetPropMap(m);
    String N = m.get("смИМЯ");
    __int8 nn = N.ToIntDef(0);
    N = "$" + N;
    if ((nn != 0) && (nomer == 0)) nomer = nn;
    strncpy(name, N.c_str(), sizeof(name) - 1);
    N = m.get(_G_Strel_1PropName[9]);
    strncpy(StrelName, N.c_str(), 14);

    tsMarshrut = NewStrToOldImp(m.get(_G_Strel_1PropName[0]).c_str());
    //impuls_mnus= NewStrToOldImp(m.get(_G_Strel_1PropName[1]).c_str());

    prSTIK[0] = m.geti(_G_Strel_1PropName[2]);
    prSTIK[1] = m.geti(_G_Strel_1PropName[3]);
    prSTIK[2] = m.geti(_G_Strel_1PropName[4]);
    NP[0].x = m.geti(_G_Strel_1PropName[5]);
    NP[0].y = m.geti(_G_Strel_1PropName[6]);
    NP[1].x = m.geti(_G_Strel_1PropName[7]);
    NP[1].y = m.geti(_G_Strel_1PropName[8]);
}

void tG_Strel_1::GetPropMap(TPropMap &m)
{
    tGRC0::GetPropMap(m);
    m.putEx(_G_Strel_1PropName[0], OldImpToNewStr(tsMarshrut, this), (void*)GetRealImp(tsMarshrut), OldImpToNewStr(0, this));
    m.putEx(_G_Strel_1PropName[1],OldImpToNewStr(impuls_mnus,this), (void*)GetRealImp(impuls_mnus),OldImpToNewStr(0,this));
    m.put(_G_Strel_1PropName[2], prSTIK[0], 0);
    m.put(_G_Strel_1PropName[3], prSTIK[1], 0);
    m.put(_G_Strel_1PropName[4], prSTIK[2], 0);
    m.put(_G_Strel_1PropName[5], NP[0].x, 0);
    m.put(_G_Strel_1PropName[6], NP[0].y, 0);
    m.put(_G_Strel_1PropName[7], NP[1].x, 0);
    m.put(_G_Strel_1PropName[8], NP[1].y, 0);
    m.put(_G_Strel_1PropName[9], StrelName);
}
//=============================================================

tG_Strel_2::tG_Strel_2()
{
    masx2 = 2;
    masy = 3;
    mas = 3;
    prSTIK[0] = 11; prSTIK[1] = 11; prSTIK[2] = 11;
    nomer = 1;
    impuls_busy_m[0] = 0; impuls_busy_m[1] = 0;
    fimpuls_busy_m[0] = 0; fimpuls_busy_m[1] = 0;
}

void tG_Strel_2::Show()
{
    tG_Strel_1::Show();
}

void tG_Strel_2::UpdateState()
{
    tG_Strel_1::UpdateState();
    int rimpuls_busy_m[2];
    rimpuls_busy_m[0] = fimpuls_busy_m[0];
    rimpuls_busy_m[1] = fimpuls_busy_m[1];
    fimpuls_busy_m[0] = f(impuls_busy_m[0]);
    fimpuls_busy_m[1] = f(impuls_busy_m[1]);
    StateChanged = StateChanged | (rimpuls_busy_m[0] != fimpuls_busy_m[0]) | (rimpuls_busy_m[1] != fimpuls_busy_m[1]);
    if (((!InvertStrel) && (fimpuls_mnus == 0) && (fimpuls_plus == 1)) ||
            ((InvertStrel) && (fimpuls_mnus == 1) && (fimpuls_plus == 0))) {

    } else {
        // Убрали за поканенадобностью 29.11.11
        //if (fimpuls_busy_m[0]==1) clr=COLOR_B;
        //if (fimpuls_busy_m[1]==1) clr=COLOR_B;
    }

}

static String _G_Strel_2PropName[] = {
    "тс_Плюс",         // 0
    "тс_ЗанятиеМ1",    // 1
    "тс_ЗанятиеМ2",    // 2

};

void tG_Strel_2::SetPropMap(TPropMap &m)
{

    tG_Strel_1::SetPropMap(m);

    impuls_busy_m[0] = NewStrToOldImp(m.get(_G_Strel_2PropName[1]).c_str());
    impuls_busy_m[1] = NewStrToOldImp(m.get(_G_Strel_2PropName[2]).c_str());

}

void tG_Strel_2::GetPropMap(TPropMap &m)
{
    tG_Strel_1::GetPropMap(m);
    m.putEx(_G_Strel_2PropName[0], OldImpToNewStr(impuls_plus, this), (void*)GetRealImp(impuls_plus), OldImpToNewStr(0, this));
    m.putEx(_G_Strel_2PropName[1], OldImpToNewStr(impuls_busy_m[0], this), (void*)GetRealImp(impuls_busy_m[0]), OldImpToNewStr(0, this));
    m.putEx(_G_Strel_2PropName[2], OldImpToNewStr(impuls_busy_m[1], this), (void*)GetRealImp(impuls_busy_m[1]), OldImpToNewStr(0, this));
}


//=======================================================================

tG_RC::tG_RC()
{
    mas = 4;
    prSTIK[0] = 11; prSTIK[1] = 11;
    nomer = 1;
    Prz[0] = 1; Prz[3] = 1; mas = 2;
};



void tG_RC::Show()
{
    Strel0::Show1();
    TY_Strel::Show();

    /*if (MOD==ED){
     clPP=C_D;clr=LIN;
     if (impuls_busi==0)clr=FON;
    } */
    setfillstyle(_styll1, clr);
    if (YP.M[3].y == YP.M[0].y) {
        cntP1=PA(P1,&T[0], &T[5], &T[6], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clS3, &clPP, &clS1,NULL);

    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x == YP.M[3].x)) { //  /
        cntP1=PA(P1,&T[16], &T[18], &T[19], &T[17],NULL);
        cntP1=IA(clr1,&clPP,  &clS3, &clPP, &clS1,NULL);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { //  /-
        cntP1=PA(P1,&T[16], &T[3], &T[5], &T[6], &T[7], &T[17],NULL);
        cntP1=IA(clr1,&clPP, &clPP, &clS3, &clPP, &clPP, &clS1,NULL);
    } else if ((YP.M[1].x == YP.M[0].x) && (YP.M[4].x != YP.M[3].x)) { // _/
        cntP1=PA(P1,&T[0], &T[1], &T[18], &T[19], &T[11], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clPP,  &clS3, &clPP,  &clPP, &clS1,NULL);
    } else {
        cntP1=PA(P1,&T[0], &T[1], &T[2], &T[3], &T[5], &T[6], &T[7], &T[8], &T[11], &T[13],NULL);
        cntP1=IA(clr1,&clPP, &clPP, &clPP, &clPP, &clS3, &clPP, &clPP, &clPP, &clPP, &clS1,NULL);
    }
    PolyColor(clr, P1, clr1, cntP1);


    Strel0::Show2();

    ShowStik(YP.M[1].x, YP.M[1].y, prSTIK[0]);
    ShowStik(YP.M[4].x, YP.M[4].y, prSTIK[2]);
    if (MOD == ED) {
        if (stNext[0][0] == "") ShowStik(YP.M[4].x, YP.M[4].y, 61);
        if (stNext[1][0] == "") ShowStik(YP.M[1].x, YP.M[1].y, 61);
        if (bShowNumberPosition) {
            int xn, yn;
            setcolor(GELT); _SetText(F_LITT, LEFT_TEXT, TOP_TEXT);
            GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "N"); fillellipse(xn, yn, 2, 2);
        }

    }
}

int tG_RC::getospolyline(TPoint * PK,int Psz)
{
    int cntrez=0;
    if (Psz<4) return 0;
    cntrez=PA(PK,&YP.M[1],&YP.M[0],&YP.M[3],&YP.M[3],NULL);
    return cntrez;
}


void tG_RC::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    X = YP.M[1].x + NP.x * MUL_X / 10;
    Y = YP.M[1].y + NP.y * MUL_Y / 10;
}


static String _G_RCPropName[] = {
    "цфCтык1",     // 0
    "цфCтык2",     // 1
    "цфНомерX",     // 2
    "цфНомерY"      // 3
};


void tG_RC::UpdateState()
{
    tGRC0::UpdateState();
    is = P;
    clPP = C_D;
}
void tG_RC::GetPropMap(TPropMap &m)
{
    tGRC0::GetPropMap(m);
    m.put(_G_RCPropName[0], prSTIK[0]);
    m.put(_G_RCPropName[1], prSTIK[2]);
    m.put(_G_RCPropName[2], NP.x);
    m.put(_G_RCPropName[3], NP.y);


};
void tG_RC::SetPropMap(TPropMap &m)
{
    tGRC0::SetPropMap(m) ;
    prSTIK[0] = m.geti(_G_RCPropName[0]);
    prSTIK[2] = m.geti(_G_RCPropName[1]);
    NP.x = m.geti(_G_RCPropName[2]);
    NP.y = m.geti(_G_RCPropName[3]);

    String N = m.get("смИМЯ");
    __int8 nn = N.ToIntDef(0);
    N = "$" + N;
    if ((nn != 0) && (nomer == 0)) nomer = nn;
    strncpy(name, N.c_str(), sizeof(name) - 1);
};

//==================================================================

tG_ZAMI::tG_ZAMI()
{
    memset(impuls_zam, 0, sizeof(impuls_zam));
    memset(fimpuls_zam, 0, sizeof(fimpuls_zam));
    RRC = 0;
    TipStupen = 0;
    DopMashtab = 0;
    G_TPLABEL.Width = 0; G_TPLABEL.Height = 0;
}
enum ttrchast {_trfull, _trhalf};
void ShowTR1(int x, int y, int clrp, int clrb, int napr, ttrchast trchast = _trfull)
{

    TPoint Tr[3];

    Tr[0] = Point(x, y);
    Tr[1] = Point(Tr[0].x - sh_y / 2 * napr, Tr[0].y - sh_y * napr);
    Tr[2] = Point(Tr[0].x + sh_y / 2 * napr, Tr[0].y - sh_y * napr);
    if (trchast == _trhalf) clrp = TXT;//Tr[2].x=Tr[0].x+sh_y/2*napr/2;
    int clr1[3] = {clrp, clrp, clrp};
    PolyColor(clrb, Tr, clr1, 3);

}






int _clrbPP[8] = {     //           A  РРC  Ступ
    FON ,              //    0      0   0   0
    FON ,              //    1      0   0   1
    FON ,              //    2      0   1   0
    FON ,              //    3      0   1   1
    KRA_ZEL,           //    4      1   0   0
    KRA_ZEL,           //    5      1   0   1
    COLOR_GOR_A,       //    6      1   1   0
    COLOR_GOR_A        //    7      1   1   1
};



int _clrbPPRRC[8] = {  //          тсРРC мкРРС А
    FON ,              //    0      0     0    0                       обычное , индикация ступеней
    COLOR_GOR_A ,      //    1      0     0    1                       обычное , индикация ступеней, А
    FON ,              //    2      0     1    0       !!!!            Красное обрамление
    KRA_ZEL,           //    3      0     1    1                       красно/зеленый мигающий
    FON,               //    4      1     0    0                       Красное обрамление
    KRA_ZEL,           //    5      1     0    1                       красно/зеленый мигающий
    FON,               //    6      1     1    0                       обычное , индикация ступеней
    COLOR_GOR_A        //    7      1     1    1                       обычное , индикация ступеней, А
};
void tG_ZAMI::SetZamColors(int T1, int T2, int T3, int T4, int R, int A, int mkRRC,int mkErrCS,int tsRRC)
//                  int &kolTR,  // кол-во рисуемых треугольников
//                  int &clrpTR, // цвет окантовки треугольников
//                  int &clrbTR, // цвет заполнения треугольников
//                  int &clrpK,  // цвет окантовки прямоугольника
//                  int &clrbK,  // цвет заполнения прямоугольника
//                  int &clrpPP, // цвет окантовки подлжки
//                  int &clrbPP  // цвет заполнения подлжки
//                 )
{
    kolTR = 0; clrpTR = C_D; clrpK = C_D; clrpPP = FON1; clrbPP = FON;

    // подложка
    if (mkRRC == 33) {
        // Если не нашли в массиве
        clrpPP = C_D;
        clrbPP = FON1;
        if (A == 1) clrbPP = KRA_ZEL;
    }  else  {
        // Если подвязано то рисуем по таблице
        int n =0;
        if (tsRRC==33){
           int stup = T1 + T2 + T3 + T4 + R;
           if (stup > 1) stup = 1;
           n = stup + mkRRC * 2 + A * 4;
           if (n > 7) n = 0;
           clrbPP = _clrbPP[n];
        } else {
           n = A + mkRRC * 2 + tsRRC * 4;
           if (n > 7) n = 0;
           clrbPP = _clrbPPRRC[n];
        }
        if (clrbPP == FON) clrpPP = FON; else clrpPP = FON1;
        if ((A == 1)) clrpPP = GELT;
        if ((A != 1) && (mkRRC == 1)) clrpPP = COLOR_GOR_A; // обрамление при RRC=1
        if ((mkRRC!=tsRRC)&&(tsRRC!=33)) clrpPP = RED;
        if (!bNomkErrCS)
           if ( ((impuls_zam[_impROSPUSK]==0) || (fimpuls_zam[_impROSPUSK]==1)) && (A == 1) && (mkErrCS==1)) clrbPP = KRA_ZEL;

    }

    // проверяем тс
    if ((T1 == 33) | (T2 == 33) | (T3 == 33) | (T4 == 33) | (R == 33) | (A == 33)) {
        clrbTR = BIRUZOVIJ; clrbK = BIRUZOVIJ;
        return;
    }
    //находим кол-во треугольников

    if (T1 == 1) kolTR = 1;
    if (T2 == 1) kolTR = 2;
    if (T3 == 1) kolTR = 3;
    if (T4 == 1) kolTR = 4;
    if (R == 1) kolTR = 2;
    // если ничего нет
    if (T1 + T2 + T3 + T4 + R == 0) {
        clrpK = C_D; clrbK = FON1;
        //if (clrbPP!=FON) clrpPP=clrpK;
    }
    // торможение
    if (T1 + T2 + T3 + T4 >= 1) {
        clrbK = 205; clrbTR = 211;
    }
    // расторможка
    if (R == 1) {
        clrbK = 251/*GELT*/;
        clrbTR = TXT;
        clrbK = TXT;
    }
    // если ступеней куча - ошибка
    /*if (T1+T2+T3+T4+R>1) {
       clrbK=0;  // черный
       clrbTR=0;
       kolTR=4;
    } */


}



void tG_ZAMI::ShowZAM(float stupen)
{
    int shzam = sh_y * 3 / 4; // толщина полоски зама
    int ddx = 3;      // отсуп с краев рц
    int ddy = 1;      // отсуп
    int ddyTR = 2;    // отсуп от колбаски до треугольников
    int naprK[2];
    naprK[0] = 1; naprK[1] = -1;
    int naprTR[2];
    int yTR[2];
    naprTR[0] = 1; naprTR[1] = -1;
    TPoint ZT[2][2];
    //int clrpK=C_D;
    //int clrbK=RED;
    //int clrpTR=C_D;
    //int clrbTR=RED;
    TPoint ZTr[4];


    /*clrpTR=C_D;
    if       (stupen==0){ //
       clrbK=FON1;
    }else if (stupen==-1){ //расторможка
       clrbK=251;clrbTR=GELT;
    }else if (stupen==-33){ //ошибка
       clrbK=KRA_ZEL;
       clrbTR=KRA_SER;
       kolTR=4;
    }else {
       clrbK=205;
       clrbTR=211;
    }
    */

    if (stupen == -33) { //ошибка
        clrbK = KRA_ZEL;
        clrbTR = KRA_SER;
        kolTR = 4;
    }

    // расставляем сдвиги и направления треугольников
    if (stupen == 0) { //
        ddy = sh_y * 1;
    } else if (stupen == -1) { //расторможка
        naprTR[0] = -naprTR[0]; naprTR[1] = -naprTR[1];
        ddy = sh_y / 2;
        //yTR[0]=T[0].y-3-/*sh_y-ddy-*/shzam-ddyTR;
        //yTR[1]=T[13].y+3+/*sh_y+ddy+*/shzam+ddyTR;
        yTR[0] = T[0].y - ddy - shzam - sh_y;
        yTR[1] = T[13].y + ddy + shzam + sh_y;
    } else {
        ddy = 1;
        yTR[0] = T[0].y - ddy - shzam - ddyTR;
        yTR[1] = T[13].y + ddy + shzam + ddyTR;
    }

    ZT[0][0] = Point(T[0].x + ddx, T[0].y - ddy - shzam);
    ZT[0][1] = Point(T[5].x - ddx, T[5].y - ddy - shzam);
    ZT[1][0] = Point(T[13].x + ddx, T[13].y + ddy + shzam);
    ZT[1][1] = Point(T[6].x - ddx, T[6].y + ddy + shzam);
    int hpodl = shzam + sh_y + ddyTR + (sh_y) / 2;
    if (stupen == -2) { //ситрание фоном
        int clr1[4] = {FON, FON, FON, FON};
        ZTr[0] = Point(ZT[0][0].x - 2, T[0].y - 1);
        ZTr[1] = Point(ZT[0][0].x - 2, ZTr[0].y - hpodl);
        ZTr[2] = Point(ZT[0][1].x + 2, ZTr[1].y); ZTr[3] = Point(ZT[0][1].x + 2, ZTr[0].y);
        PolyColor(FON, ZTr, clr1, 4);
        ZTr[0] = Point(ZT[1][0].x - 2, T[13].y + 1);
        ZTr[1] = Point(ZT[1][0].x - 2, ZTr[0].y + hpodl);
        ZTr[2] = Point(ZT[1][1].x + 2, ZTr[1].y); ZTr[3] = Point(ZT[1][1].x + 2, ZTr[0].y);
        PolyColor(FON, ZTr, clr1, 4);
        return;
    }


    if ((clrbPP != FON) || (clrpPP != FON)) {
        setfillstyle(SOLID_FILL, clrbPP); setcolor(clrpPP);
        ZTr[0] = Point(ZT[0][0].x - 2, T[0].y - 1);
        ZTr[1] = Point(ZT[0][0].x - 2, ZTr[0].y - hpodl);
        ZTr[2] = Point(ZT[0][1].x + 3, ZTr[1].y); ZTr[3] = Point(ZT[0][1].x + 2, ZTr[0].y);
        roundrect(ZTr[0].x, ZTr[0].y, ZTr[2].x, ZTr[2].y, sh_y, sh_y);
        ZTr[0] = Point(ZT[1][0].x - 2, T[13].y + 1);
        ZTr[1] = Point(ZT[1][0].x - 2, ZTr[0].y + hpodl);
        ZTr[2] = Point(ZT[1][1].x + 3, ZTr[1].y); ZTr[3] = Point(ZT[1][1].x + 2, ZTr[0].y);
        roundrect(ZTr[0].x, ZTr[0].y, ZTr[2].x, ZTr[2].y, sh_y, sh_y);
    }


    // колбаска
    for (int d = 0; d < 2; d++) {
        ZTr[0] = ZT[d][0]; ZTr[1] = ZT[d][1];
        ZTr[2] = Point(ZT[d][1].x, ZT[d][1].y + shzam * naprK[d]);
        ZTr[3] = Point(ZT[d][0].x, ZT[d][0].y + shzam * naprK[d]);
        int clr1[4] = {clrpK, clrpK, clrpK, clrpK};
        PolyColor(clrbK, ZTr, clr1, 4);

    }
    // треугольники целые
    double dxTR = 0;
    int kolTRhalf = 0;
    if ((TipStupen != 0) && (stupen > 0)) {
        if ((stupen - (int)stupen) > 0) kolTRhalf = 1;
        kolTR = (int)stupen + kolTRhalf;
    }
    if (kolTR > 0)dxTR = (ZT[0][1].x - ZT[0][0].x) / (kolTR + 1);

    for (int d = 0; d < 2; d++) {
        for (int tr = 0; tr < kolTR - kolTRhalf; tr++) { // треугольники целые
            ShowTR1(ZT[0][0].x + dxTR*(tr + 1), yTR[d], clrpTR, clrbTR, naprTR[d]);
        }
        // // треугольники не целые
        if (kolTRhalf > 0) ShowTR1(ZT[0][0].x + dxTR*(kolTR), yTR[d], clrpTR, clrbTR, naprTR[d], _trhalf);
    }


    if ((TipStupen != 0) && (stupen > 0)) {

        //String SS="x.x";
        //if ((int)stupen != stupen) SS.printf("%2.1f",stupen); else
        //                           SS=IntToStr((int)stupen);
        //_SetText(F_DEFAULT,CENTER_TEXT,CENTER_TEXT);

        //int len_t=textwidth(SS.c_str())/2+1;
        //setcolor(C_D);
        //_SetTextSize(-sh_y*4-1);
        //DrawText(MM[1].x+1+1,MM[1].y-sh_y-1+1,MM[4].x-MM[1].x-1+1,sh_y*2+2+1,SS.c_str());
        //setcolor(GELT_LIN);
        //DrawText(MM[1].x+1,MM[1].y-sh_y-1,MM[4].x-MM[1].x-1,sh_y*2+2,SS.c_str());
        //_SetTextSize(1);
        //_SetText(F_DEFAULT,LEFT_TEXT,BOTTOM_TEXT);

    }

    // focused
    if (ExtFocus > 0) {
        int clp = clInfoBk;
        if (ExtFocus == 2) clp = FON;
        //if (ExtFocus==2) ExtFocus=0;
        setcolor(clp);
        line(T[0].x - 1, T[0].y - hpodl - 3, T[0].x - 1, T[0].y - hpodl - 3 + sh_y);
        line(T[0].x - 1, T[0].y - hpodl - 3, T[0].x - 1 + sh_y, T[0].y - hpodl - 3);

        line(T[5].x + 1, T[5].y - hpodl - 3, T[5].x + 1, T[5].y - hpodl - 3 + sh_y);
        line(T[5].x + 1, T[5].y - hpodl - 3, T[5].x + 1 - sh_y, T[5].y - hpodl - 3);

        line(T[13].x - 1, T[13].y + hpodl + 3, T[13].x - 1, T[13].y + hpodl + 3 - sh_y);
        line(T[13].x - 1, T[13].y + hpodl + 3, T[13].x - 1 + sh_y, T[13].y + hpodl + 3);

        line(T[6].x + 1, T[6].y + hpodl + 3, T[6].x + 1, T[6].y + hpodl + 3 - sh_y);
        line(T[6].x + 1, T[6].y + hpodl + 3, T[6].x + 1 - sh_y, T[6].y + hpodl + 3);
    }


}
void tG_ZAMI::Show()
{

    // расставляем цвета

    if (MOD == ED) {
        kolTR = 0;
        for (int i = 0; i < 4; i++) if (impuls_zam[i] != 0) kolTR++;
        clrpTR = C_D; clrbTR = FON;
        clrpK = C_D; clrbK = FON1;
        clrpPP = FON; clrbPP = FON;
        if (impuls_zam[_impA ] != 0)clrbPP = FON1;
        if (AddrLK != 0)clrpPP = C_D;


    } else {
        int impRRC=fimpuls_zam[_impRRC ];
        if (impuls_zam[_impRRC ]==0) impRRC=33;
        SetZamColors(fimpuls_zam[_impT1],
                     fimpuls_zam[_impT2],
                     fimpuls_zam[_impT3],
                     fimpuls_zam[_impT4],
                     fimpuls_zam[_impR ],
                     fimpuls_zam[_impA ],
                     RRC,
                     ErrCS,
                     impRRC
                    );
    }


    sh_y += DopMashtab;

    tG_RC::Show();
    //затираем фоном
    ShowZAM(-2);
    // считаем ступень
    float stupen = 0;
    if (fimpuls_zam[_impR] == 1) stupen = -1; else if (fimpuls_zam[_impT4] == 1) stupen = 4; else if (fimpuls_zam[_impT3] == 1) stupen = 3; else if (fimpuls_zam[_impT2] == 1) stupen = 2; else if (fimpuls_zam[_impT1] == 1) stupen = 1;

    if (TipStupen != 0) {
        if (MOD == ED) {
            stupen = 0.4;
            if (impuls_zam[_impR ] != 0) stupen += 1;
            if (impuls_zam[_impT1] != 0) stupen += 1;
            if (impuls_zam[_impT2] != 0) stupen += 1;
            if (impuls_zam[_impT3] != 0) stupen += 1;
        } else {
            if ((fimpuls_zam[_impT1] == 1) && (fimpuls_zam[_impT2] == 1)) stupen = 0.5; else if ((fimpuls_zam[_impT1] == 1) && (fimpuls_zam[_impT3] == 1)) stupen = 1.5; else if ((fimpuls_zam[_impT2] == 1) && (fimpuls_zam[_impT3] == 1)) stupen = 2.5;
            if ((fimpuls_zam[_impT1] == 1) && (fimpuls_zam[_impT2] == 1) && (fimpuls_zam[_impT3] == 1)) stupen = 3.5;
        }

    }

    // проверяем чтобы был только один активный импульс
    if ((TipStupen == 0) ||
            ((TipStupen == 1) && (fimpuls_zam[_impA ] == 0))) {
        int actimp = 0;
        for (int i = 0; i < 5; i++) if (fimpuls_zam[i] == 1) actimp++;
        if (actimp > 1)
            stupen = -33;
    }
    if ((TipStupen == 0) && (MOD == ED)) stupen = 1;





    ShowZAM(stupen);





    sh_y -= DopMashtab;

    if ((G_TPLABEL.Width != 0) && (G_TPLABEL.Height != 0)) {
        G_TPLABEL.X = X + DX_LABEL;
        G_TPLABEL.Y = Y + DY_LABEL;
        if (MOD == ED) G_TPLABEL.SetParamsFromZam(this);
        G_TPLABEL.Show();
    }


}

void tG_ZAMI::UpdateState()
{
    tG_RC::UpdateState();

    if ((G_TPLABEL.Width != 0) && (G_TPLABEL.Height != 0)) {
        G_TPLABEL.SetParamsFromZam(this);
        G_TPLABEL.UpdateState();
        StateChanged = StateChanged | G_TPLABEL.StateChanged;
    }

    int rimpuls_zam[11];
    for (int i = 0; i < 11; i++) rimpuls_zam[i] = f(impuls_zam[i]);

    for (int i = 0; i < 11; i++) StateChanged = StateChanged | (rimpuls_zam[i] != fimpuls_zam[i]);

    for (int i = 0; i < 11; i++) fimpuls_zam[i] = rimpuls_zam[i];

    int V = 0, Voleg = 0, RC = 0, _RRC = 0,_ErrCS=0;

    if (!GetZamData(AddrLKSlot, AddrLK, V, Voleg, RC, _RRC,_ErrCS)) {
        // если нет посылок
    }
    StateChanged = StateChanged | (_RRC != RRC)|(_ErrCS!=ErrCS);
    RRC = _RRC;
    ErrCS=_ErrCS;


    //if (packetname[0]==0)
    //   {clrbPP=FON;clrpPP=FON;}

    if ((IsClrMig(clrpTR)) || (IsClrMig(clrpTR)) || (IsClrMig(clrbTR)) ||
            (IsClrMig(clrpK)) || (IsClrMig(clrbK)) || (IsClrMig(clrpPP)) || (IsClrMig(clrbPP))) StateChanged = true;

}
static String _GZAM_StrelPropName[] = {
    "смИмя_Зам",   // 0
    "цф№_ТП",   // 1
    "цфТип_ЗМ", // 2
    "цфАдрес_ЛК",     // 3
    "цфАдрес_ЛК_Слот",     // 4
    "цфАдрес_КЗП",     // 5
    "цфТипСтупеней",     // 6

    "тс_Т1",     //  7
    "тс_Т2",     //  8
    "тс_Т3",     //  9
    "тс_Т4",     //  10
    "тс_Р",      //  11
    "тс_А",      //  12
    "тс_КЗ",     //  13
    "тс_Ман",    //  14
    "тс_ОГ",     //  15
    "тс_РРС",     //  15
    "тс_РОСПУСК",     //  16

    "цфНе_масштаб", //  17
    "цфDX_V",   //  18
    "цфDY_V",    //  19
    "цфШирина_V",   //  20
    "цфВысота_V",    //  21
    "цфВесБуквы_V",   //  22
    "цфmasy_V",   //  23
    "лгNomkErrCS",   //24
    "лгНетСкВых",     // 25
    "цфПровVвых"


};

void tG_ZAMI::GetPropMap(TPropMap &m)
{
    tG_RC::GetPropMap(m);
    int i=0;
    m.put(_GZAM_StrelPropName[i++],  NZAM);
    m.put(_GZAM_StrelPropName[i++],  NTP);
    m.put(_GZAM_StrelPropName[i++],  TipZM);
    m.put(_GZAM_StrelPropName[i++],  AddrLK);
    m.put(_GZAM_StrelPropName[i++],  AddrLKSlot);
    i++;// КЗП
    m.put(_GZAM_StrelPropName[i++],  TipStupen);

    for (int ii = 0; ii < 11; ii++)
        m.putEx(_GZAM_StrelPropName[i++], OldImpToNewStr(impuls_zam[ii], this), (void*)GetRealImp(impuls_zam[ii]));

    m.put(_GZAM_StrelPropName[i++],  DopMashtab);

    m.put(_GZAM_StrelPropName[i++],  DX_LABEL);
    m.put(_GZAM_StrelPropName[i++],  DY_LABEL);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.Width);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.Height);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.VesBukv);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.masy);
    m.put(_GZAM_StrelPropName[i++],  bNomkErrCS);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.NoShowVout);
    m.put(_GZAM_StrelPropName[i++],  G_TPLABEL.provV);


}
void tG_ZAMI::SetPropMap(TPropMap &m)
{
    tG_RC::SetPropMap(m);
    int i=0;
    NZAM =   m.get(_GZAM_StrelPropName[i++]);
    NTP =    m.geti(_GZAM_StrelPropName[i++]);
    TipZM =  m.geti(_GZAM_StrelPropName[i++]);
    AddrLK = m.geti(_GZAM_StrelPropName[i++]);
    AddrLKSlot = m.geti(_GZAM_StrelPropName[i++]);
    i++;// КЗП
    TipStupen = m.geti(_GZAM_StrelPropName[i++]);
    for (int ii = 0; ii < 11; ii++)
        impuls_zam[ii] = NewStrToOldImp(m.get(_GZAM_StrelPropName[i++]).c_str());

    DopMashtab = m.geti(_GZAM_StrelPropName[i++]);
    DX_LABEL = m.geti(_GZAM_StrelPropName[i++]);
    DY_LABEL = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.Width = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.Height = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.VesBukv = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.masy = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.pVisibleArray=this->pVisibleArray;

    bNomkErrCS= m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.NoShowVout = m.geti(_GZAM_StrelPropName[i++]);
    G_TPLABEL.provV = m.geti(_GZAM_StrelPropName[i++]);




}

void tG_ZAMP::GetPropMap(TPropMap &m)
{
    tG_ZAMI::GetPropMap(m);
    m.put(_GZAM_StrelPropName[5],  AddrKZP);
}
void tG_ZAMP::SetPropMap(TPropMap &m)
{
    tG_ZAMI::SetPropMap(m);
    AddrKZP = m.geti(_GZAM_StrelPropName[5]);
}

//==================================================================

static String _G_ZKR_PropName[] = {
    "тс_РТДС1",   // 0
    "тс_РТДС2",   // 1
    "тс_СветКр",  // 2
    "тс_СветЖ",   // 3
    "тс_СветЗ",   // 4
    "тс_СветБ",   // 5
    "тс_Авт",     // 6
    "тс_Расцеп",  // 7
    "тс_Д1",      // 8
    "тс_Д2",      // 9
    "тс_Д3",      // 10
    "тс_ДН1",     // 11
    "тс_ДН2",     // 12
    "тс_ДН3",     // 13
    "тс_Д11",      // 14
    "тс_Д12",      // 15
    "тс_Д21",      // 16
    "тс_Д22",      // 17
    "тс_Д31",      // 17
    "тс_Д32",      // 18
    "тс_Роспуск",      //
    "цф_ТУ_РРС",  //
    "цф_ДИСО1",   //
    "цф_ДИСО2",   //
    "цф_ДИСО3",   //
    "цф_Режим",   //
    "цф_Вагон",   //
    "цф_ПутьНадвига",//
    "цфАдрес_ЛК",     //
    "цфАдрес_ЛК_Слот",
    "цфТипВыводДСО",
    "цфСдвигРТДС_Y",
    "цфРазмерРТДС_Y",
    "лгНевыводРТДС"
        //


};

tG_ZKR::tG_ZKR()
{
    memset(impuls_zkr, 0, sizeof(impuls_zkr));
    memset(params_zkr, 0, sizeof(params_zkr));
}
void tG_ZKR::makebs(int dn)
{
    for (int i = 0; i < 3; i++) {
        xt = x0 + (i + 1) * dx;
        Bs[i][0][0] = xt;            Bs[i][0][1] = y - sh_y / 2 - 1;
        Bs[i][0][2] = xt;            Bs[i][0][3] = Bs[i][0][1] - sh_y - 2;
        Bs[i][0][4] = xt + sh_y * dn;    Bs[i][0][5] = Bs[i][0][1] - sh_y / 2 - 1;
        Bs[i][0][6] = Bs[i][0][0];   Bs[i][0][7] = Bs[i][0][1];

        Bs[i][1][0] = xt;            Bs[i][1][1] = y + sh_y / 2 + 1;
        Bs[i][1][2] = xt;            Bs[i][1][3] = Bs[i][1][1] + sh_y + 2;
        Bs[i][1][4] = xt + sh_y * dn;    Bs[i][1][5] = Bs[i][1][1] + sh_y / 2 + 1;
        Bs[i][1][6] = Bs[i][1][0];   Bs[i][1][7] = Bs[i][1][1];
    }
    int xt2[6];
    xt2[0] = x0 + 1 * dx2; xt2[2] = x0 + 3 * dx2;xt2[4] = x0 + 5 * dx2;
    xt2[1] = x0 + 2 * dx2; xt2[3] = x0 + 4 * dx2;xt2[5] = x0 + 6 * dx2;

    for (int i = 0; i < 6; i++) {
        xt = xt2[i];
        if ((i == 0) || (i == 2)|| (i == 4)) {
            Bs2[i][0][0] = xt;            Bs2[i][0][1] = y - sh_y / 2 - 1;
            Bs2[i][0][2] = xt - sh_y / 2;     Bs2[i][0][3] = Bs2[i][0][1] - sh_y - 2;
            Bs2[i][0][4] = xt + sh_y / 2;     Bs2[i][0][5] = Bs2[i][0][1] - sh_y - 2;
            Bs2[i][0][6] = Bs2[i][0][0];  Bs2[i][0][7] = Bs2[i][0][1];
        } else {
            Bs2[i][0][0] = xt;            Bs2[i][0][1] = y + sh_y / 2 + 1;
            Bs2[i][0][2] = xt - sh_y / 2;     Bs2[i][0][3] = Bs2[i][0][1] + sh_y + 2;
            Bs2[i][0][4] = xt + sh_y / 2;     Bs2[i][0][5] = Bs2[i][0][1] + sh_y + 2;
            Bs2[i][0][6] = Bs2[i][0][0];  Bs2[i][0][7] = Bs2[i][0][1];

        }
    }


}
void tG_ZKR::Show()
{
    int clrD[3];
    int clrD2[6];
    int clrRTDS[2];
    if (MOD == ED) {
        for (int i = 0; i < 3; i++)
                if (impuls_zkr[i_D1+i] != 0) clrD[i] = TXT; else clrD[i] = FON;
        for (int i = 0; i < 6; i++)
                if (impuls_zkr[i_D11+i] != 0) clrD2[i] = TXT; else clrD2[i] = FON;
        for (int i = 0; i < 2; i++)
                if (impuls_zkr[i_rtds1+i] != 0) clrRTDS[i] = TXT; else clrRTDS[i] = FON;
    } else {
        for (int i = 0; i < 3; i++) {
            if (impuls_zkr[i_D1+i] == 0) continue;
            if (fimpuls_zkr[i_D1+i] == 1) clrD[i] = COLOR_B; else if (fimpuls_zkr[i_D1+i] == 0) clrD[i] = FON1; else
                clrD[i] = BIRUZOVIJ;
        }
        for (int i = 0; i < 2; i++) {
            if (fimpuls_zkr[i_rtds1+i] == 0) clrRTDS[i] = FON1; else if (fimpuls_zkr[i_rtds1+i] == 1) clrRTDS[i] = COLOR_B; else
                clrRTDS[i] = BIRUZOVIJ;
        }
        for (int i = 0; i < 6; i++) {
            if (impuls_zkr[i_D11+i] == 0) continue;
            if (fimpuls_zkr[i_D11+i] == 1) clrD2[i] = TXT; else if (fimpuls_zkr[i_D11+i] == 0) clrD2[i] = FON1; else
                clrD2[i] = BIRUZOVIJ;
        }

    }


    tG_RC::Show();

    // Д1 Д2 Д3
    int d = 1;
    x0 = YP.M[1].x;
    if (mas < 0) {
        d = -1;
        //x0=YP.M[4].x;
    }



    int dn;
    dx = (YP.M[4].x - YP.M[1].x) / 4;
    dx2 = (YP.M[4].x - YP.M[1].x) / 8;
    if (params_zkr[_zkr_rtds_hide]!=1){
    int y_rtds=y-params_zkr[_zkr_rtds_y]*MUL_Y;
    int h_rtds=sh_y*4+params_zkr[_zkr_rtds_h]*MUL_Y;

    if (impuls_zkr[i_rtds1+0] != 0) {
        setcolor(clrRTDS[0]); setfillstyle(1, clrRTDS[0]);
        fillellipse(x0, y_rtds - h_rtds,     sh_y / 2 + 1, sh_y / 2 + 1);
        fillellipse(x0 + dx*2, y_rtds + h_rtds, sh_y / 2 + 1, sh_y / 2 + 1);
        line(x0, y_rtds - h_rtds, x0 + dx*2, y_rtds + h_rtds);
    }

    if (impuls_zkr[i_rtds1+1] != 0) {
        setcolor(clrRTDS[1]); setfillstyle(1, clrRTDS[1]);
        fillellipse(x0, y_rtds + h_rtds,     sh_y / 2 + 1, sh_y / 2 + 1);
        fillellipse(x0 + dx*2, y_rtds - h_rtds, sh_y / 2 + 1, sh_y / 2 + 1);
        line(x0, y_rtds + h_rtds, x0 + dx*2, y_rtds - h_rtds);
    }
    }
    // затираем фоноm
    if (params_zkr[_zkr_tip_vivod_dso]==0){
    makebs(1);
    for (int i = 0; i < 3; i++) {
        if (impuls_zkr[i_D1+i] == 0) continue;
        setfillstyle(1, FON); setcolor(FON);
        fillpoly(4, Bs[i][0]); fillpoly(4, Bs[i][1]);
    }
    makebs(-1);
    for (int i = 0; i < 3; i++) {
        if (impuls_zkr[i_D1+i] == 0) continue;
        setfillstyle(1, FON); setcolor(FON);
        fillpoly(4, Bs[i][0]); fillpoly(4, Bs[i][1]);
    }
    for (int i = 0; i < 6; i++) {
        if (impuls_zkr[i_D11+i] == 0) continue;
        setfillstyle(1, FON); setcolor(FON);
        fillpoly(4, Bs2[i][0]);
    }

    for (int i = 0; i < 3; i++) {
        if (impuls_zkr[i_D1+i] == 0) continue;
        dn = d;
        if ((fimpuls_zkr[i_D1+i] == 1) && (fimpuls_zkr[i_DN1+i] == 0)) dn = -d;

        xt = x0 + (i + 1) * dx;
        Bs[i][0][4] = xt + sh_y * dn;    Bs[i][0][5] = Bs[i][0][1] - sh_y / 2 - 1;
        Bs[i][1][4] = xt + sh_y * dn;    Bs[i][1][5] = Bs[i][1][1] + sh_y / 2 + 1;

        setfillstyle(1, clrD[i]); setcolor(C_D);
        fillpoly(4, Bs[i][0]); fillpoly(4, Bs[i][1]);
    }

    for (int i = 0; i < 6; i++) {
        if (impuls_zkr[i_D11+i] == 0) continue;
        setfillstyle(1, clrD2[i]); setcolor(C_D);
        fillpoly(4, Bs2[i][0]);
    }
    }





}
void tG_ZKR::UpdateState()
{
    tG_RC::UpdateState();
    int rimpuls_zkr[_zkr_max_imp];
    for (int i = 0; i < _zkr_max_imp; i++) rimpuls_zkr[i] = f(impuls_zkr[i]);
    for (int i = 0; i < _zkr_max_imp; i++) StateChanged = StateChanged | (rimpuls_zkr[i] != fimpuls_zkr[i]);
    for (int i = 0; i < _zkr_max_imp; i++) fimpuls_zkr[i] = rimpuls_zkr[i];

}
void tG_ZKR::GetPropMap(TPropMap &m)
{
    tG_RC::GetPropMap(m);
    for (int i = 0; i < _zkr_max_imp; i++)
        m.putEx(_G_ZKR_PropName[i], OldImpToNewStr(impuls_zkr[i], this), (void*)GetRealImp(impuls_zkr[i]));
    for (int i = 0; i < 13; i++)
        m.put(_G_ZKR_PropName[_zkr_max_imp+i], params_zkr[i]);

}
void tG_ZKR::SetPropMap(TPropMap &m)
{
    tG_RC::SetPropMap(m);
    for (int i = 0; i < _zkr_max_imp; i++)
        impuls_zkr[i] = NewStrToOldImp(m.get(_G_ZKR_PropName[i]).c_str());
    for (int i = 0; i < 13; i++)
        params_zkr[i] = m.geti(_G_ZKR_PropName[i+_zkr_max_imp]);
}



//   =============   tOTCLABEL   =======================



static String _G_OTCLABEL_PropName[] = {
    "Имя",
    "цфНомерТП",
    "цфШирина",
    "цфВысота",
    "тсimp_descr_start1",
    "тсimp_descr_start2",
    "тсimp_descr_start3",
    "тсimp_descr_start4",
    "тсimp_descr_start5",
    "тсimp_descr_end1",
    "тсimp_descr_end2",
    "тсimp_descr_end3",
    "тсimp_descr_end4",
    "тсimp_descr_end5",
    "цфАдрес_ЛК1",
    "цфАдрес_ЛК1_Слот",
    "цфАдрес_ЛК2",
    "цфАдрес_ЛК2_Слот"
};

tG_OTCLABEL::tG_OTCLABEL()
{
    memset(imp_descr_start, 0, sizeof(imp_descr_start));
    memset(imp_descr_end, 0, sizeof(imp_descr_end));
    Height = 20; Width = 60;
    Name = ""; NTP = 0;
    memset(&Descr, 0, sizeof(Descr));
}


void tG_OTCLABEL::Show()
{
    int x = X * MUL_X + _X_;
    int y = Y * MUL_Y + _Y_;
    setcolor(C_D);
    int H_2 = Height / 2;
    int HH1 = Height - 4; // размер квадрата категории
    TPoint T[4];
    T[0] = Point(x, y - H_2);
    T[1] = Point(T[0].x + Width, T[0].y);
    T[2] = Point(T[1].x, T[0].y + Height);
    T[3] = Point(T[0].x, T[2].y);

    TPoint TT[4];
    TT[0] = Point(T[0].x + 2, T[0].y + 3);
    TT[1] = Point(T[1].x - 2, TT[0].y);
    TT[2] = Point(TT[1].x, T[2].y - 2);
    TT[3] = Point(TT[0].x, TT[2].y);

    int clrP = clInfoBk;
    int clrB = clInfoBk;


    //Stupen = Descr->st;  // типа реальная ступень какаято 06 08 2007


    if (mar_f <= 0) {
        clrP = FON;//clInfoBk;
        clrB = FON;//clSilver;
    } else if (V_out != 0) {
        clrB = clSilver;
        clrP = clSilver;
    }


    int c1[4] = {   clrP, clrP, clrP, clrP};
    PolyColor(clrB, T, c1, 4);

    Draw_Ramka(TT[0].x, TT[0].y, TT[2].x, TT[2].y, EDGE_BUMP);

    String SS;
    if (mar_f <= 0) SS = ""; else
        SS = IntToStr(mar_f);
    if (MOD == ED) {
        SS = IntToStr(AddrLK1Slot) + " " + IntToStr(addr1);
        clrB = clSilver;
        clrP = clSilver;
    }
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(1, HORIZ_DIR, HH1 - 4);
    DrawText(TT[0].x, TT[0].y, Width - 2, Height, SS.c_str());
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}

t_Descr* FindDescr(tGRC0 * RCstart,
                   int d,           // направление
                   int se,          // start=0/end=1
                   bool onlyBusy,
                   bool end_slg_inc,
                   int maxRC)
{
    tGRC0 * RC = RCstart;
    tGRC0 * RCN = NULL;
    for (int i = 0; i < maxRC; i++){
        if (RC != NULL) {
            if ((onlyBusy) && (RC->fimpuls_busi!=1)) return NULL;
            t_Descr* DD=GetDescr_imp1(RC->impuls_busi,       // Местоположение Головы / жопы отцепа
                                      se,          // start=0/end=1
                                      end_slg_inc
            );
            if (DD!=NULL) return DD;
            int m=0;
            if  (RC->fimpuls_mnus == 1)
                if (RC->pNext[d][1]!=NULL) m=1;

            RCN = dynamic_cast<tGRC0 *>(RC->pNext[d][m]);
            // проверяем обратку
            if (RCN != NULL) {
                int m1 = 0;
                if (RCN->fimpuls_mnus == 1) m1 = 1;
                if ((RCN->pNext[1-d][m1]!=NULL)&&(RCN->pNext[1-d][m1] != RC))
                    return NULL;
            }
            RC = RCN;
        }
    }
    return NULL;

}

void tG_OTCLABEL::UpdateState()
{

    //int fnum   = num;
    //int fmar_f = mar_f;
    //int fves   = ves;
   // int flen   = len;
    //int fStupen = Stupen;
    //int fV_Zad = V_Zad;
    //int fV_out = V_out;

    //int adr_tp1 = (AddrLK1Slot - 1) * 100 + addr1;
    //int adr_tp2 = (AddrLK2Slot - 1) * 100 + addr2;
    V_out = 0;
    mar_f = -1;
    V_Zad=0;
    num = 0;
    ves = 0;
    len = 0;
    Stupen = 0;
    p_rzp=0;

    // смотрим заняте ТП

    // Смотрим голову
    t_Descr* _Descr= GetDescr_imp(imp_descr_start,       // Местоположение Головы / жопы отцепа
                       5,
                       0,//  se,          // start=0/end=1
                       false//end_slg_inc
                      );
    if (_Descr==NULL)  _Descr= GetDescr_imp(imp_descr_start,       // Местоположение Головы / жопы отцепа
                       5,
                       1,//  se,          // start=0/end=1
                       false//end_slg_inc
                      );

    /*if (mar_f == -1) {
        if (!GetDescrData_imp(imp_descr_start,          // Местоположение Головы отцепа |    N Эл РЦ в ТС     |
                              5, 0,       // start
                              NTP,
                              num, mar_f  , ves , len    , Stupen , V_Zad, fV_out,p_rzp)
           ) mar_f = -1;
    }
    // Смотрим хвост
    if (mar_f == -1) {
        if (!GetDescrData_imp(imp_descr_end,          // Местоположение хвоста отцепа |    N Эл РЦ в ТС     |
                              5,  1,       // end
                              NTP,
                              num, mar_f  , ves , len    , Stupen , V_Zad, V_out,p_rzp)
           ) mar_f = -1;
    }
    */
    if (_Descr!=NULL){
       if (memcmp(&Descr,_Descr,sizeof(Descr))!=0) StateChanged =true;
       memcpy(&Descr,_Descr,sizeof(Descr));
       mar_f = GetGorWayNum(this->Stan(),Descr.mar_f);
       switch (NTP) {
       case 2 :V_Zad=Descr.V_zad2; V_out=Descr.V_out2; break;
       case 3 :V_Zad=Descr.V_zad3; V_out=Descr.V_out3; break;
       default:V_Zad=Descr.V_zad ; V_out=Descr.V_out;
       };
       num = Descr.num;
       ves = Descr.ves;
       len = Descr.len;
       Stupen = Descr.st;  // типа реальная ступень какаято 06 08 2007
       p_rzp=Descr.p_rzp;
    }

    //StateChanged = (fnum != num) || (fmar_f != mar_f) || (fves != ves) || (flen != len) || (fStupen != Stupen) || (fV_Zad != V_Zad);

}
void tG_OTCLABEL::GetPropMap(TPropMap &m)
{
    AComp::GetPropMap(m);
    int ii = 0;
    m.put(_G_OTCLABEL_PropName[ii++], Name.c_str());
    m.put(_G_OTCLABEL_PropName[ii++], NTP);
    m.put(_G_OTCLABEL_PropName[ii++], Width);
    m.put(_G_OTCLABEL_PropName[ii++], Height);
    for (int i = 0; i < 5; i++)
        m.putEx(_G_OTCLABEL_PropName[ii++], OldImpToNewStr(imp_descr_start[i], this), (void*)GetRealImp(imp_descr_start[i]));
    for (int i = 0; i < 5; i++)
        m.putEx(_G_OTCLABEL_PropName[ii++], OldImpToNewStr(imp_descr_end[i], this), (void*)GetRealImp(imp_descr_end[i]));

    m.put(_G_OTCLABEL_PropName[ii++], addr1);
    m.put(_G_OTCLABEL_PropName[ii++], AddrLK1Slot);
    m.put(_G_OTCLABEL_PropName[ii++], addr2);
    m.put(_G_OTCLABEL_PropName[ii++], AddrLK2Slot);


}
void tG_OTCLABEL::SetPropMap(TPropMap &m)
{
    AComp::SetPropMap(m);

    int ii = 0;
    Name = m.get(_G_OTCLABEL_PropName[ii++]);
    NTP = m.geti(_G_OTCLABEL_PropName[ii++]);
    Width = m.geti(_G_OTCLABEL_PropName[ii++]);
    Height = m.geti(_G_OTCLABEL_PropName[ii++]);
    for (int i = 0; i < 5; i++)
        imp_descr_start[i] = NewStrToOldImp(m.get(_G_OTCLABEL_PropName[ii++]).c_str());
    for (int i = 0; i < 5; i++)
        imp_descr_end[i] = NewStrToOldImp(m.get(_G_OTCLABEL_PropName[ii++]).c_str());

    addr1 =      m.geti(_G_OTCLABEL_PropName[ii++]);
    AddrLK1Slot = m.geti(_G_OTCLABEL_PropName[ii++]);
    addr2 =      m.geti(_G_OTCLABEL_PropName[ii++]);
    AddrLK2Slot = m.geti(_G_OTCLABEL_PropName[ii++]);
}





//   =============   tTPLABEL   =======================



static String _G_TPLABEL_PropName[] = {
    "цфВесБуквы",
    "тсКраснЗаданV",
    "тсКраснМигЗаданV",
    "цфZKR",
    "лгНетСкВых",
    "стADAM",
    "цфADK3",
    "лгVнадвиг",
    "цфПровVвых"
};

tG_TPLABEL::tG_TPLABEL()
{
    Height = 20; Width = 60;
    addr1 = addr2 = AddrLK1Slot = AddrLK2Slot = 0;
    fimp_krasn = fimp_krasn_mig = 0;
    imp_krasn = imp_krasn_mig = 0;
    ZKR_N=0;fves_osi=0;p_rzp=0;
    VesBukv=0;
    G_ZAMI=NULL;
    NoShowVout=false;
    ADAM="";
    ADK3="";
    bShowVnadv=false;
    provV=0;
}
void tG_TPLABEL::GetPropMap(TPropMap &m)
{
    tG_OTCLABEL::GetPropMap(m);
    int i = 0;

    m.put(_G_TPLABEL_PropName[i++], VesBukv,0);
    m.putEx(_G_TPLABEL_PropName[i++], OldImpToNewStr(imp_krasn, this), (void*)GetRealImp(imp_krasn),0);
    m.putEx(_G_TPLABEL_PropName[i++], OldImpToNewStr(imp_krasn_mig, this), (void*)GetRealImp(imp_krasn_mig),0);
    m.put(_G_TPLABEL_PropName[i++], ZKR_N,0);
    m.put(_G_TPLABEL_PropName[i++], NoShowVout,0);
    m.put(_G_TPLABEL_PropName[i++], ADAM,"");
    m.put(_G_TPLABEL_PropName[i++], ADK3,"");
    m.put(_G_TPLABEL_PropName[i++], bShowVnadv,0);
    m.put(_G_TPLABEL_PropName[i++], provV,0);



}
void tG_TPLABEL::SetPropMap(TPropMap &m)
{
    tG_OTCLABEL::SetPropMap(m);
    int i = 0;
    VesBukv =       m.geti(_G_TPLABEL_PropName[i++]);
    imp_krasn =     NewStrToOldImp(m.get(_G_TPLABEL_PropName[i++]).c_str());
    imp_krasn_mig = NewStrToOldImp(m.get(_G_TPLABEL_PropName[i++]).c_str());
    ZKR_N =         m.geti(_G_TPLABEL_PropName[i++]);
    NoShowVout=     m.geti(_G_TPLABEL_PropName[i++]);
    ADAM=           m.get(_G_TPLABEL_PropName[i++]);
    ADK3=           m.get(_G_TPLABEL_PropName[i++]);
    bShowVnadv=     m.geti(_G_TPLABEL_PropName[i++]);
    provV =         m.geti(_G_TPLABEL_PropName[i++]);

}

void ShowPictXY(int PictNumber, int x, int y, int WP, int HP);
void tG_TPLABEL::Show()
{
    int x = X * MUL_X + _X_;
    int y = Y * MUL_Y + _Y_;
    setcolor(C_D);
    int H_2 = Height / 2;
    int HH1 = Height - 4; // размер квадрата категории
    int HH2 = (Width - HH1) / 2 - 8;//HH1;      // размер квадрата зад скорости
    TPoint T[4];
    T[0] = Point(x, y - H_2);
    T[1] = Point(T[0].x + Width, T[0].y);
    T[2] = Point(T[1].x, T[0].y + Height);
    T[3] = Point(T[0].x, T[2].y);


    TPoint TZ[4];
    TZ[0] = Point(T[1].x - HH2 - 2, T[0].y + 3);
    TZ[1] = Point(TZ[0].x + HH2, TZ[0].y);
    TZ[2] = Point(TZ[1].x, T[2].y - 2);
    TZ[3] = Point(TZ[0].x, TZ[2].y);

    TPoint TF[4];
    TF[0] = Point(T[0].x + 2, T[0].y + 3);
    TF[1] = Point(TZ[0].x - HH1 - 2 - 2, TF[0].y);
    TF[2] = Point(TF[1].x, T[2].y - 2);
    TF[3] = Point(TF[0].x, TF[2].y);

    TPoint TV[4];
    TV[0] = Point(T[0].x + 2, T[0].y + 3);
    TV[1] = Point(TZ[0].x - HH1 - 2 - 2, TF[0].y);
    TV[2] = Point(TV[1].x, T[2].y - 2);
    TV[3] = Point(TV[0].x, TF[2].y);


    double w1 = TPVal(V1);
    double w2 = TPVal(V2);
    double w = w1;
    if (w < w2) w = w2;


        //Показуха по команде руководителей бе...
        if (RC1 != 0 && RC2 == 0)  w = w1;
        if (RC2 != 0 && RC1 == 0)  w = w2;
        if (RC1 != 0 && RC2 != 0)  w1 < w2 ? w2 : w1;// max
        if (RC1 == 0 && RC2 == 0) w = 0.;

     // когда махонькая выводит толко себя
    if (masy >= 100) w=w1;



    double dV_Zad = V_Zad / 10.;
    int clrP = clBlack;
    int clrB = clInfoBk;
    if (w <= 2) w = 0; //  Anton Minsk 29.03.07
    if ((w == 0) && (Stupen <= 0) && (V_Zad == 0)) {
        clrP = FON;////clInfoBk;
        clrB = FON;
    }
    // выход
    int colV=C_D;

    if ((w == 0) && (V_out != 0) && (V_out!=65535)) {
       if (!NoShowVout) {
          clrP = FON;////clInfoBk;
          clrB = clSilver;
          if (provV!=0){
                if (V_out-V_Zad>provV) colV=RED;
          }
          // скорость выхода вместо фактической
          w = V_out / 10.;
       } else {
          clrP = FON;clrB = FON;dV_Zad=0;Stupen=0;
       }
    }

    String stV_Zad = "";
    //if ((dV_Zad > 4.5) && (dV_Zad < 30)) нахрена оно вообще тут было???
    if (dV_Zad > 0)    stV_Zad.printf("%2.1f", dV_Zad);

    String SS;
    if (w == 0) SS = ""; else {
        if (w >= 50) SS = "--"; else
            SS.printf("%2.1f", w);
    }


    if (MOD == ED) {
        SS = IntToStr(addr1);
        stV_Zad = IntToStr(AddrLK1Slot);
        clrP = clBlack;
        clrB = clInfoBk;
        Stupen = 2;
        w = 5;
        p_rzp=mas;
    }

    if (masy == 0) {

        if ((VesBukv != 0) && (w <= 2) && (Stupen <= 0)) {
            int c1[4] = {   clrP, clrP, clrP, clrP/*clSilver, clSilver, clSilver, clSilver*/};
            PolyColor(clrB, T, c1, 4);
        } else {
            int c1[4] = {   clSilver, clSilver, clSilver, clSilver};
            PolyColor(clrB, T, c1, 4);

            //int cF[4]={   clSilver, clSilver, clSilver, clSilver};
            //PolyColor(clSilver,TF,cF,4);
            if (VesBukv != 0) {
                int cZ[4] = {   clSilver, clSilver, clSilver, clSilver};
                PolyColor(clSilver, TZ, cZ, 4);
            }


            //Draw_Ramka(T[0].x,T[0].y,T[2].x,T[2].y,EDGE_SUNKEN );
            Draw_Ramka(TF[0].x, TF[0].y, TF[2].x, TF[2].y, EDGE_BUMP);
            Draw_Ramka(TZ[0].x, TZ[0].y, TZ[2].x, TZ[2].y, EDGE_BUMP);

            int pictn;
            String stVes;
            if (VesBukv == 0) {
                switch (Stupen) {
                case 1: pictn=132; stVes="Л"; break;
                case 2: pictn=133; stVes="ЛС"; break;
                case 3: pictn=134; stVes="С"; break;
                case 4: pictn=135; stVes="Т"; break;
                default:pictn=131; stVes="";
                }
            } else {
                switch (Stupen) {
                case 1: pictn=136; stVes="Л"; break;
                case 2: pictn=137; stVes="ЛС"; break;
                case 3: pictn=138; stVes="С"; break;
                case 4: pictn=139; stVes="Т"; break;
                default:pictn=131; stVes="";
                }
            }

            ShowPictXY(pictn, TF[1].x + 2, T[1].y + 2, HH1 + 1, HH1 + 1);




            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(1, HORIZ_DIR, HH1 - 4);
            setcolor(colV);
            DrawText(TF[0].x, TF[0].y, Width - HH1 - HH2 - 2 - 2 - 2, Height, SS.c_str());
            if ((!bShowVnadv)&&(p_rzp > 0)&&(NTP<=2)) {
               int cZ[4] = {   C_D, C_D, C_D, C_D};
               PolyColor(0x00246BFF, TZ, cZ, 4);
               int fontcol=C_D;
               if (p_rzp == 4) {   //  4 - скорость не откорректирована
                fontcol=C_D;
               } else
               if (p_rzp <= 3) {   //  1,2,3 - скорость откорретирована
                fontcol=COLOR_PSV;
               }
               setcolor(fontcol);
            }
            if ((fimp_krasn == 1)) {
                int clrzad;
                if (fimp_krasn == 1) {
                    clrzad = KRA;
                    if (fimp_krasn_mig == 1) clrzad = COLOR_PSV;
                }
                int cZ[4] = {   clrzad, clrzad, clrzad, clrzad};
                PolyColor(clrzad, TZ, cZ, 4);
            }
            if (stV_Zad != "") {
                settextstyle(1, HORIZ_DIR, HH1 - 4/*HH2/2*/);
                DrawText(TZ[0].x, TZ[0].y, HH2, Height, stV_Zad.c_str());
            }
        }

    }
    if (masy >= 100) {

        if (ZKR_N==0){
            if ((w <= 2) && (Stupen <= 0)) {
                clrP = FON1;
                clrB = FON;//clSilver;
            } else {
                clrP = clBlack;
            }
        } else {
            if (MOD==ED){
               clrB = clInfoBk;
               SS="ZKR"+IntToStr(ZKR_N);
            } else {
              if (fves_osi==-33){
                 clrB = BIRUZOVIJ;
                 SS="--";
              } else {
                 clrB = clInfoBk;
                 //SS.printf("%2.1f", w);
                 SS.printf("%2.1f", (1.*fves_osi/10));
              }
            }
        }
        if (ADAM!=""){
             if (MOD==ED){
               clrB = clInfoBk;
               SS=ADAM;
            } else {
                SS=FADAV_val;
                clrB = clInfoBk;
            }
        }
        if (ADK3!=""){
             if (MOD==ED){
               clrB = clInfoBk;
               SS=/*ADK3+"_"+*/IntToStr(AddrLK1Slot)+"-"+IntToStr(addr1);
            } else {
                SS=FADK3_val;
                if (SS=="") clrB = BIRUZOVIJ; else
                clrB = clInfoBk;
            }
        }

        TF[0] = Point(T[0].x + 2, T[0].y + 3);
        TF[1] = Point(T[1].x - 2, T[1].y + 3);
        TF[2] = Point(TF[1].x, T[2].y - 3);
        TF[3] = Point(TF[0].x, TF[2].y);


        //int c1[4]={   clSilver, clSilver, clSilver, clSilver};
        //PolyColor(clSilver,TF,c1,4);
        int cF[4] = {   clrP, clrP, clrP, clrP};
        PolyColor(clrB, TF, cF, 4);

        //Draw_Ramka(T[0].x,T[0].y,T[2].x,T[2].y,EDGE_SUNKEN   );
        //Draw_Ramka(TF[0].x,TF[0].y,TF[2].x,TF[2].y,EDGE_BUMP);
        setcolor(colV);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(1, HORIZ_DIR, HH1 - 4);
        DrawText(TF[0].x, TF[0].y, Width - 2, Height - 3, SS.c_str());
    }

    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}
t_Descr*  GetDescr_ARS(int tp,
                       int Slot,
                       int Addr
                      );
void tG_TPLABEL::UpdateState()
{
    //tG_OTCLABEL::UpdateState();
   // int fnum   = num;
   // int fmar_f = mar_f;
   // int fves   = ves;
    //int flen   = len;
   // int fStupen = Stupen;
  //  int fV_Zad = V_Zad;
  //  int fV_out = V_out;
   // int fp_rzp=p_rzp;

    //int adr_tp1 = (AddrLK1Slot - 1) * 100 + addr1;
    //int adr_tp2 = (AddrLK2Slot - 1) * 100 + addr2;

    V_out = 0;
    mar_f = -1;
    V_Zad=0;
    num = 0;
    ves = 0;
    len = 0;
    Stupen = 0;
    p_rzp=0;

    // смотрим заняте ТП
    // скорость забираем
    int fV1 = V1;
    int fV2 = V2;
    int RRC;
    int ErrCS;
     p_rzp=0;






    if (AddrLK1Slot+addr1+AddrLK2Slot+addr2>0){
        GetZamData(AddrLK1Slot, addr1, V1, Voleg1, RC1, RRC,ErrCS);
        GetZamData(AddrLK2Slot, addr2, V2, Voleg2, RC2, RRC,ErrCS);

        int rimp_krasn = f(imp_krasn);
        int rimp_krasn_mig = f(imp_krasn_mig);

        StateChanged = StateChanged | (fV1 != V1) | (fV2 != V2) | (rimp_krasn != rimp_krasn) | (rimp_krasn_mig != fimp_krasn_mig);

        fimp_krasn = rimp_krasn; fimp_krasn_mig = rimp_krasn_mig;

        V_Zad = 0;
        V_out = 0;
        mar_f = -1;
        t_Descr* _Descr=NULL;

        // по олыку
        _Descr=GetDescr_ARS(NTP,
                       AddrLK1Slot,
                       addr1
                      );
        if (_Descr==NULL)  _Descr=GetDescr_ARS(NTP,
                       AddrLK2Slot,
                       addr2
                      );


        // мы будем жить теперь по новому
        if (G_ZAMI!=NULL){
           // если свободно ищем сзади до 5 рц

           if (G_ZAMI->fimpuls_busi==0){
              int _maxRC=5;
              if (masy == 100) _maxRC=2;

              if (_Descr==NULL) _Descr=FindDescr(G_ZAMI,
                   1,          // направление
                   0,          // start=0/end=1
                   false,      //onlyBusy,
                   false,      // end_slg_inc,
                   _maxRC      //maxRC
                   );
              if (_Descr==NULL) _Descr=FindDescr(G_ZAMI,
                   1,          // направление
                   1,          // start=0/end=1
                   false,      //onlyBusy,
                   false,      // end_slg_inc,
                   5           //maxRC
                   );
           } else // если занято ищем сзади далеко хвост
           if (_Descr==NULL) _Descr=FindDescr(G_ZAMI,
                   1,          // направление
                   1,          // start=0/end=1
                   true,      //onlyBusy,
                   false,      // end_slg_inc,
                   15           //maxRC
                   );
           // ищем ушедшее
           if (_Descr==NULL) _Descr=FindDescr(G_ZAMI,
                   0,          // направление
                   1,          // start=0/end=1
                   false,      //onlyBusy,
                   false,      // end_slg_inc,
                   5           //maxRC
                   );
           if (_Descr==NULL) _Descr=FindDescr(G_ZAMI,
                   0,          // направление
                   0,          // start=0/end=1
                   false,      //onlyBusy,
                   false,      // end_slg_inc,
                   5           //maxRC
                   );
           // ищем ушедшее вконец
           if ((_Descr==NULL)&&(G_ZAMI->NTP==3)) _Descr=FindDescr(G_ZAMI,
                   0,          // направление
                   1,          // start=0/end=1
                   false,      //onlyBusy,
                   true,      // end_slg_inc,
                   1           //maxRC
                   );
        } else {
                if (_Descr==NULL) _Descr= GetDescr_imp(imp_descr_start,       // Местоположение Головы / жопы отцепа
                       5,
                       0,//  se,          // start=0/end=1
                       false//end_slg_inc
                      );
                if (_Descr==NULL)  _Descr= GetDescr_imp(imp_descr_start,       // Местоположение Головы / жопы отцепа
                       5,
                       1,//  se,          // start=0/end=1
                       false//end_slg_inc
                      );
                if (_Descr==NULL)  _Descr= GetDescr_imp(imp_descr_end,       // Местоположение Головы / жопы отцепа
                       5,
                       1,//  se,          // start=0/end=1
                       false//end_slg_inc
                      );
        }

        if (_Descr!=NULL){
           if (memcmp(&Descr,_Descr,sizeof(Descr))!=0) StateChanged =true;
           memcpy(&Descr,_Descr,sizeof(Descr));
           if (Descr.mar_f>0) mar_f = GetGorWayNum(this->Stan(),Descr.mar_f);
           switch (NTP) {
           case 2 :V_Zad=Descr.V_zad2; V_out=Descr.V_out2; break;
           case 3 :V_Zad=Descr.V_zad3; V_out=Descr.V_out3; break;
           default:V_Zad=Descr.V_zad ; V_out=Descr.V_out;
           };
           num = Descr.num;
           ves = Descr.ves;
           len = Descr.len;
           Stupen = Descr.st;  // типа реальная ступень какаято 06 08 2007
           p_rzp=Descr.p_rzp;
        }
        //StateChanged = (fnum != num) || (fmar_f != mar_f) || (fves != ves) || (flen != len) || (fStupen != Stupen) || (fV_Zad != V_Zad)|| (fp_rzp != p_rzp);
    }
    if (ZKR_N>0){
       int rves_osi=-33;
       GetZKRData(ZKR_N,rves_osi);
       StateChanged = StateChanged | (fves_osi!=rves_osi);
       fves_osi=rves_osi;
    }
    if (ADAM!="")
        FADAV_val=GetADAM_val(ADAM); else
        FADAV_val="";
    if (ADK3!="") {
        String _FADK3_val=FADK3_val;
        uint32     biostime=0;
        tADK3Cell* ADK3Cell=GetADK3Cell(AddrLK1Slot, addr1,biostime);
        if (ADK3Cell!=NULL){
                if (ADK3=="a")   {
                        FADK3_val.printf("%2i",ADK3Cell->a);
                } else
                if ((ADK3=="p[0]")||(ADK3=="p[1]")) {
                        double p=ADK3Cell->p[0];
                        if (ADK3=="p[1]")p=ADK3Cell->p[1];
                        if (p==0) FADK3_val="---"; else {
                        p=((p+1)/256-0.04)/0.0012858; //кПа
                        p=p*1000/101325; //Атм
                        FADK3_val.printf("%1.3f",p);
                        }
                }else
                if ((ADK3=="t[0]")||(ADK3=="t[1]")) {
                        double t=ADK3Cell->t[0];
                        if (ADK3=="t[1]")t=ADK3Cell->t[1];
                        if (t==0) FADK3_val="---";  else {
                        t=(t+177)*(500./512.)-273.16; // Cгр
                        FADK3_val.printf("%2.1f",t);
                        }
                }else
                if ((ADK3=="u[0]")||(ADK3=="u[1]")) {
                        double u=ADK3Cell->u[0];
                        if (ADK3=="u[1]")u=ADK3Cell->u[1];
                        if (u==0) FADK3_val="---"; else {
                        u=(u/256.)*50.; // В
                        FADK3_val.printf("%4.1f",u);
                        }
                } else
                if (ADK3=="r")    FADK3_val.printf("%2i",ADK3Cell->r);
        } else {
                FADK3_val="";
        }
        if (_FADK3_val!=FADK3_val) StateChanged=true;
    }
    if (bShowVnadv){
        V_Zad=0;
        tDescrCom *DescrCom=GetDescrCom();
        if (DescrCom!=NULL)
                V_Zad=DescrCom->Vnadv;
    }


}

void tG_TPLABEL::SetParamsFromZam(tG_ZAMI * G_ZAMI)
{
    NTP = G_ZAMI->NTP;
    this->G_ZAMI=G_ZAMI;
    /*tGRC0 * RC = G_ZAMI;
    tGRC0 * RCN = NULL;
    int m;
    memset(imp_descr_start, 0, sizeof(imp_descr_start));
    memset(imp_descr_end, 0, sizeof(imp_descr_end));
    for (int i = 0; i < 5; i++)
        if (RC != NULL) {
            imp_descr_start[i] = RC->impuls_busi;
            RCN = dynamic_cast<tGRC0 *>(RC->pNext[1][0]);
            if (RCN != NULL) {
                m = 0;
                if (RCN->fimpuls_mnus == 1) m = 1;
                if (RCN->pNext[0][m] != RC)
                    RCN = NULL;
            }
            RC = RCN;
        }
    RC = G_ZAMI;
    for (int i = 0; i < 5; i++)
        if (RC != NULL) {
            imp_descr_end[i] = RC->impuls_busi;
            m = 0;
            if (RC->fimpuls_mnus == 1) m = 1;
            RC = dynamic_cast<tGRC0 *>(RC->pNext[0][m]);
        }
    */
    addr1 =      G_ZAMI->AddrLK;
    AddrLK1Slot = G_ZAMI->AddrLKSlot;
    tG_ZAMI * G_ZAMI2=dynamic_cast<tG_ZAMI *>(G_ZAMI->pNext[0][0]);
    if (G_ZAMI2!=NULL){
       addr2 =      G_ZAMI2->AddrLK;
       AddrLK2Slot = G_ZAMI2->AddrLKSlot;
    }

}


//   =============   tG_KZP   =======================



static String _G_KZP_PropName[] = {
    "Имя",
    "цфШирина",
    "цфВысота",
    "цфШиринаT",
    "цфВысотаT",
    "цфНаправление",
    "цфМаксЗнач",
    "цфВыводУВ",
    "цфaddr",
    "цфEmask"

};

tG_KZP::tG_KZP()
{
    Height = 20; Width = 160;
    HeightT = 30; WidthT = 60;
    D = 0; E = 0; _D = 0; D1 = 0; _E = 0;
    MaxD = 1000;
    Direct = 0; inUV = 0;
    Emask=0;
}


void tG_KZP::Show()
{
    int x = X * MUL_X + _X_;
    int y = Y * MUL_Y + _Y_;
    setcolor(C_D);
    int H_2 = Height / 2;
    int H_2T = HeightT / 2;
    int HH1 = HeightT - 4; // размер квадрата категории
    int dxT = 4; // сдвиг до цифры
    int xx; // ширина реального
    int xx1;// ширина предидущего

    int W = Width - 1;
    if (MaxD == 0) MaxD = 1000;
    if (D > MaxD) xx = W; else
        xx = W * D / MaxD;
    if (D1 > MaxD) xx1 = W; else
        xx1 = W * D1 / MaxD;

    int clrbPodl = COLOR_F_P;
    //int clrbD1=206;
    int clrbD = 210;
    String SS;
    if ((E != 0)) {
        clrbPodl = clTeal;
        xx = -1; xx1 = -1;
    }
    if (MOD == ED) {
        clrbPodl = clSilver;
        xx = -1; xx1 = -1;
    }
    TPoint Tpr = Point(x, y);
    TPoint Ttxt = Point(x + Width + dxT, y);
    // переворот
    if (Direct == 1) {
        Ttxt = Point(x, y);
        Tpr = Point(x + WidthT + dxT, y);
        xx = W - xx; xx1 = W - xx1;
    }
    if (W > 0) {
        // Подложка
        TPoint T[4];
        T[0] = Point(Tpr.x, Tpr.y - H_2); T[1] = Point(T[0].x + Width, T[0].y);
        T[2] = Point(T[1].x, T[0].y + Height); T[3] = Point(T[0].x, T[2].y);
        int c1[4] = {   clrbPodl, clrbPodl, clrbPodl, clrbPodl};
        PolyColor(clrbPodl, T, c1, 4);
        Draw_Ramka(T[0].x, T[0].y, T[2].x + 1, T[2].y + 1, EDGE_BUMP);
        // реальная величина
        if (xx >= 0) {
            if (Direct == 0) {
                T[0] = Point(Tpr.x + xx, T[0].y); T[3] = Point(Tpr.x + xx, T[3].y);
            } else {
                T[1] = Point(Tpr.x + xx, T[1].y); T[2] = Point(Tpr.x + xx, T[2].y);
            }
            int c1[4] = {   clrbD, clrbD, clrbD, clrbD};
            PolyColor(clrbD, T, c1, 4);
        }
        /* // прошлая
        if (xx1>=0){
           if (Direct==0) {T[0]=Point(Tpr.x+xx1,T[0].y);T[3]=Point(Tpr.x+xx1,T[3].y);} else
                          {T[1]=Point(Tpr.x+xx1,T[1].y);T[2]=Point(Tpr.x+xx1,T[2].y);}
           int c1[4]={   clrbD1, clrbD1, clrbD1, clrbD1};
           PolyColor(clrbD1,T,c1,4);
        }
        */

        T[0] = Point(Tpr.x, Tpr.y - H_2); T[1] = Point(T[0].x + Width, T[0].y);
        T[2] = Point(T[1].x, T[0].y + Height); T[3] = Point(T[0].x, T[2].y);
        Draw_Ramka(T[0].x, T[0].y, T[2].x + 1, T[2].y + 1, EDGE_BUMP);
    }

    TPoint TT[4];
    TT[0] = Point(Ttxt.x, Ttxt.y - H_2T);
    TT[1] = Point(TT[0].x + WidthT, TT[0].y);
    TT[2] = Point(TT[1].x, TT[0].y + HeightT);
    TT[3] = Point(TT[0].x, TT[2].y);

    int clrP = clrbPodl;
    int clrB = clrbPodl;
    int ct[4] = {   clrP, clrP, clrP, clrP};
    PolyColor(clrB, TT, ct, 4);
    setfillstyle(1, FON);
    Draw_Ramka(TT[0].x, TT[0].y, TT[2].x + 1, TT[2].y + 1, EDGE_BUMP/*EDGE_SUNKEN*/);

    if (MOD == ED) {
        SS = IntToStr(addr);
    } else {
        if (E != 0) SS = "---"; else {
            if (inUV == 0) SS = IntToStr(D); else
                SS = IntToStr(int(D / 14.));
        }
    }
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(1, HORIZ_DIR, HH1 - 0);
    DrawText(TT[0].x, TT[0].y, WidthT - 2, HeightT, SS.c_str());
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}
void tG_KZP::UpdateState()
{
    int V,P;
    GetKZPData(addr, D, E,V,P);
    //if (Emask!=0) E=E & Emask;
    if (E==65535) E=1; else E=0;
    StateChanged = (_D != D) || (_E != E);
    // запоминаем предыдущее
    // сброс на 0
    if (E == 0) {
        // если меньше 5 и предид больше 5
        if ((D < _D) && (D < 5) && (_D > 5)) {
            D1 = _D;
        }
        if (D1 < D) D1 = D;
        _D = D;
    }
    _E = E;
    // D=200;D1=600;E=0;


}
void tG_KZP::GetPropMap(TPropMap &m)
{
    AComp::GetPropMap(m);
    int ii = 0;
    m.put(_G_KZP_PropName[ii++], Name.c_str());
    m.put(_G_KZP_PropName[ii++], Width);
    m.put(_G_KZP_PropName[ii++], Height);
    m.put(_G_KZP_PropName[ii++], WidthT);
    m.put(_G_KZP_PropName[ii++], HeightT);
    m.put(_G_KZP_PropName[ii++], Direct);
    m.put(_G_KZP_PropName[ii++], MaxD);
    m.put(_G_KZP_PropName[ii++], inUV);
    m.put(_G_KZP_PropName[ii++], addr);
    m.put(_G_KZP_PropName[ii++], Emask);


}
void tG_KZP::SetPropMap(TPropMap &m)
{
    AComp::SetPropMap(m);

    int ii = 0;
    Name = m.get(_G_KZP_PropName[ii++]);
    Width = m.geti(_G_KZP_PropName[ii++]);
    Height = m.geti(_G_KZP_PropName[ii++]);
    WidthT = m.geti(_G_KZP_PropName[ii++]);
    HeightT = m.geti(_G_KZP_PropName[ii++]);
    Direct = m.geti(_G_KZP_PropName[ii++]);
    MaxD = m.geti(_G_KZP_PropName[ii++]);
    inUV = m.geti(_G_KZP_PropName[ii++]);
    addr = m.geti(_G_KZP_PropName[ii++]);
    Emask = m.geti(_G_KZP_PropName[ii++]);

}



//   =============   KZP   =======================



static String _G_OSY_PropName[] = {
    "цфaddr",
    "тсОси",
    "цфТип",
    "лгВыводОси",
    "PacketName_21",
    "смСледующий",
    "смПредидующий"
};

tG_OSY::tG_OSY()
{
    AddrLK = -1;
    imp_osy=0;
    tip=0;
    bShowOs=true;
    PacketName_21="";
    stNext[0]="";
    stNext[1]="";
}
void tG_OSY::GetPropMap(TPropMap &m)
{
    Element::GetPropMap(m);
    int ii = 0;
    m.put(_G_OSY_PropName[ii++], AddrLK);
    m.putEx(_G_OSY_PropName[ii++], OldImpToNewStr(imp_osy, this), (void*)GetRealImp(imp_osy),       OldImpToNewStr(0, this));
    m.put(_G_OSY_PropName[ii++], tip);
    m.put(_G_OSY_PropName[ii++], bShowOs);
    m.put(_G_OSY_PropName[ii++], PacketName_21);
    for (int d = 0; d < 2; d++)
            m.put(_G_OSY_PropName[ii++], stNext[d]);
}
void tG_OSY::SetPropMap(TPropMap &m)
{
    Element::SetPropMap(m);
    int ii = 0;
    AddrLK = m.geti(_G_OSY_PropName[ii++]);
    imp_osy = NewStrToOldImp(m.get(_G_OSY_PropName[ii++]).c_str());
    tip = m.geti(_G_OSY_PropName[ii++]);
    bShowOs=m.geti(_G_OSY_PropName[ii++]);
    PacketName_21 = m.get(_G_OSY_PropName[ii++]);
    for (int d = 0; d < 2; d++)
            stNext[d] = m.get(_G_OSY_PropName[ii++]);
}

int  tG_OSY::GetSubType()
{
     return tip;
}


void tG_OSY::Show()
{
    int x = X * MUL_X + _X_;
    int y = Y * MUL_Y + _Y_;
    int Bs[8];
    //int s=sh_y/2+2;
    //int yy = y-s;

    int pencol = C_D;
    int fillcol = FON;

    if (fimpuls_busi == 1) fillcol = TXT;
    if (fimpuls_plus == 1) fillcol = TXT;
    if (E!=0) pencol = RED;
    if (impuls_mnus != 0){
        if (fimpuls_mnus == 0) pencol = KRA_SER;
    }



    setfillstyle(1, fillcol);
    setcolor(pencol);
    int xt,yt;
    xt=x;
    yt=y;
    switch (mas) {
    default:
    case 0:Bs[0]=x;                    Bs[1]=y-sh_y/2-1;
           Bs[2] = x - sh_y / 2 - 1;   Bs[3] = y - 1.5 * sh_y - 2;
           Bs[4] = x + sh_y / 2 + 1;   Bs[5] = y - 1.5 * sh_y - 2;
           Bs[6] = x;                  Bs[7] = y - sh_y / 2 - 1;
           yt=Bs[5]-1.5 * sh_y-1;
        break;
    case 1:Bs[0]=x;            Bs[1]=y+sh_y/2+1;
        Bs[2] = x - sh_y / 2 - 1;   Bs[3] = y + 1.5 * sh_y + 2;
        Bs[4] = x + sh_y / 2 + 1;   Bs[5] = y + 1.5 * sh_y + 2;
        Bs[6] = x;            Bs[7] = y + sh_y / 2 + 1;
        yt=Bs[5]+1.5 * sh_y+1;
        break;
    }
    if (mas<2) fillpoly(4, Bs);
    int osi =0;
    if (tip==0){
        if ((imp_osy!=0)&&(f(imp_osy)!=33))
        {
                 osi =
                (f(imp_osy + 0)) * 1 +
                (f(imp_osy + 1)) * 2 +
                (f(imp_osy + 2)) * 4 +
                (f(imp_osy + 3)) * 8 +
                (f(imp_osy + 4)) * 16 +
                (f(imp_osy + 5)) * 32 +
                (f(imp_osy + 6)) * 64 +
                (f(imp_osy + 7)) * 128 ;
        }
    }  else {
        osi=V;
        char bf[10];
        if (MOD==ED){
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                _SetTextSize(-1.5 * sh_y);
                itoa(AddrLK, bf, 10);
                OutTextXY(x, yt, bf);
                _SetTextSize(1);
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        } else {
             if ((osi!=0)&&(bShowOs))      {
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                _SetTextSize(-1.5 * sh_y);

                itoa(osi, bf, 10);
                OutTextXY(x, yt, bf);
                _SetTextSize(1);
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
             }
        }
    }


}
void tG_OSY::UpdateState()
{

    int rimpuls_busi = f(impuls_busi);
    int rimpuls_plus = f(impuls_plus);
    int rimpuls_mnus = f(impuls_mnus);

    StateChanged = (rimpuls_busi != fimpuls_busi) |(rimpuls_plus != fimpuls_plus)|(rimpuls_mnus != fimpuls_mnus);
    fimpuls_busi = rimpuls_busi;
    fimpuls_plus = rimpuls_plus;
    fimpuls_mnus = rimpuls_mnus;

    int fV   = V;
    int fE   = E;
    if (tip!=0){
        if (!GetOsyData(tip,AddrLK,
                    V,       //
                    E,
                    PacketName_21)
       );
    };

    StateChanged = StateChanged | (V != fV) | (E != fE);

}


//======================= KZP2 ============================

static String _G_KZP2_PropName[] = {
    "цфМаршрут",
    "цфАдрес_КЗП",
    "цфШирина",
    "цфВысота",
    "цфСдвигXТнпути",
    "цфВысотаТнпути",
    "цфШиринаТсвоб",
    "цфВысотаТсвоб",
    "цфСдвигXТзан",
    "цфСдвигYТзан",
    "цфШиринаТзан",
    "цфВысотаТзан",
    "цфШиринаV",
    "цфВысотаV",
    "цфНаправление",
    "цфМасштаб",
    "цфВыводУВ",
    "цфВыводV",
    "цфdXV",
    "цфСтарыйВвод",
    "цфВыводЗанят",
    "цфнп_mas",
    "цфнп_masy",
    "цфнп_masx2",
    "цфнп_Prz0",
    "цфнп_Prz1",
    "цфнп_Prz2",
    "тснп_impuls_busi",
    "тснп_impuls_plus",
    "тснп_impuls_minus",
    "тснп_impuls_kzm",
    "лгПодсвОтц",
    "цфEmask",
    "цфКолОтц"


};

tG_KZP2::tG_KZP2()
        : tG_RC()
{
    szAll.cx = 120; szAll.cy = 14;// размер всего без текста свободности и текста занятости
    xxNP = szAll.cx + 5;
    szNSV.cx = 24;  szNSV.cy = 14;// размер текста свободности
    szNP.cx = 32;   szNP.cy = 24;// размер текста текста свободности
    szV.cx = 32;    szV.cy = 24;// размер ячейки скорости
    szNZ.cx = 32;   szNZ.cy = 20;// размер текста текста занятости
    xxNZ = xxNP + szNP.cx + 5;
    memset(&KvKzp, 0, sizeof(KvKzp));
    memset(&KzpInf, 0, sizeof(KzpInf));
    memset(_TV, 0, sizeof(_TV));
    Len = 1000; Direct = 0; inUV = 0;
    mar = 0;
    yyNZ = 0;
    mashtab = 0;
    outV = 0;
    dxV = 5;
    outD=0;
    outZZ=1;
    Lmp.Prz[0]=szNZ.cy;
    bOtcMig=false;
    Lmp.pVisibleArray=pVisibleArray;
    Emask=0;
    kolvo_otc=0;
}

void tG_KZP2::GetPropMap(TPropMap &m)
{
    tG_RC::GetPropMap(m);
    int ii = 0;
    m.put(_G_KZP2_PropName[ii++], mar);
    m.put(_G_KZP2_PropName[ii++], AddrKZP);
    m.put(_G_KZP2_PropName[ii++], szAll.cx);
    m.put(_G_KZP2_PropName[ii++], szAll.cy);
    m.put(_G_KZP2_PropName[ii++], xxNP);
    m.put(_G_KZP2_PropName[ii++], szNP.cy);
    m.put(_G_KZP2_PropName[ii++], szNSV.cx);
    m.put(_G_KZP2_PropName[ii++], szNSV.cy);
    m.put(_G_KZP2_PropName[ii++], xxNZ);
    m.put(_G_KZP2_PropName[ii++], yyNZ);
    m.put(_G_KZP2_PropName[ii++], szNZ.cx);
    m.put(_G_KZP2_PropName[ii++], szNZ.cy);
    m.put(_G_KZP2_PropName[ii++], szV.cx);
    m.put(_G_KZP2_PropName[ii++], szV.cy);
    m.put(_G_KZP2_PropName[ii++], Direct);
    m.put(_G_KZP2_PropName[ii++], mashtab);
    m.put(_G_KZP2_PropName[ii++], inUV);
    m.put(_G_KZP2_PropName[ii++], outV);
    m.put(_G_KZP2_PropName[ii++], dxV);
    m.put(_G_KZP2_PropName[ii++], outD);
    m.put(_G_KZP2_PropName[ii++], outZZ);

    m.put(_G_KZP2_PropName[ii++], Lmp.mas);
    m.put(_G_KZP2_PropName[ii++], Lmp.masy);
    m.put(_G_KZP2_PropName[ii++], Lmp.masx2);
    m.put(_G_KZP2_PropName[ii++], Lmp.Prz[0]);
    m.put(_G_KZP2_PropName[ii++], Lmp.Prz[1]);
    m.put(_G_KZP2_PropName[ii++], Lmp.Prz[2]);

    m.putEx(_G_KZP2_PropName[ii++], OldImpToNewStr(Lmp.impuls_busi, this), (void*)GetRealImp(Lmp.impuls_busi),       OldImpToNewStr(0, this));
    m.putEx(_G_KZP2_PropName[ii++], OldImpToNewStr(Lmp.impuls_plus, this), (void*)GetRealImp(Lmp.impuls_plus),       OldImpToNewStr(0, this));
    m.putEx(_G_KZP2_PropName[ii++], OldImpToNewStr(Lmp.impuls_mnus, this), (void*)GetRealImp(Lmp.impuls_mnus),       OldImpToNewStr(0, this));
    m.putEx(_G_KZP2_PropName[ii++], OldImpToNewStr(Lmp.impuls_kzm, this), (void*)GetRealImp(Lmp.impuls_kzm),      OldImpToNewStr(0, this));

    m.put(_G_KZP2_PropName[ii++], bOtcMig);
    m.put(_G_KZP2_PropName[ii++], Emask);
    m.put(_G_KZP2_PropName[ii++], kolvo_otc);
}
void tG_KZP2::SetPropMap(TPropMap &m)
{
    tG_RC::SetPropMap(m);

    int ii = 0;
    mar =         m.geti(_G_KZP2_PropName[ii++]);
    AddrKZP =     m.geti(_G_KZP2_PropName[ii++]);
    szAll.cx =    m.geti(_G_KZP2_PropName[ii++]);
    szAll.cy =    m.geti(_G_KZP2_PropName[ii++]);
    xxNP =        m.geti(_G_KZP2_PropName[ii++]);
    szNP.cy =     m.geti(_G_KZP2_PropName[ii++]);
    szNSV.cx =    m.geti(_G_KZP2_PropName[ii++]);
    szNSV.cy =    m.geti(_G_KZP2_PropName[ii++]);
    xxNZ =        m.geti(_G_KZP2_PropName[ii++]);
    yyNZ =        m.geti(_G_KZP2_PropName[ii++]);
    szNZ.cx =     m.geti(_G_KZP2_PropName[ii++]);
    szNZ.cy =     m.geti(_G_KZP2_PropName[ii++]);
    szV.cx =      m.geti(_G_KZP2_PropName[ii++]);
    szV.cy =      m.geti(_G_KZP2_PropName[ii++]);
    Direct =      m.geti(_G_KZP2_PropName[ii++]);
    mashtab =     m.geti(_G_KZP2_PropName[ii++]);
    inUV =        m.geti(_G_KZP2_PropName[ii++]);
    outV =        m.geti(_G_KZP2_PropName[ii++]);
    dxV =         m.geti(_G_KZP2_PropName[ii++]);
    outD=         m.geti(_G_KZP2_PropName[ii++]);
    outZZ=        m.geti(_G_KZP2_PropName[ii++]);

    Lmp.mas=      m.geti(_G_KZP2_PropName[ii++]);
    Lmp.masy=     m.geti(_G_KZP2_PropName[ii++]);
    Lmp.masx2=    m.geti(_G_KZP2_PropName[ii++]);
    Lmp.Prz[0]=   m.geti(_G_KZP2_PropName[ii++]);
    Lmp.Prz[1]=   m.geti(_G_KZP2_PropName[ii++]);
    Lmp.Prz[2]=   m.geti(_G_KZP2_PropName[ii++]);

    Lmp.impuls_busi=NewStrToOldImp(m.get(_G_KZP2_PropName[ii++]).c_str());
    Lmp.impuls_plus=NewStrToOldImp(m.get(_G_KZP2_PropName[ii++]).c_str());
    Lmp.impuls_mnus=NewStrToOldImp(m.get(_G_KZP2_PropName[ii++]).c_str());
    Lmp.impuls_kzm= NewStrToOldImp(m.get(_G_KZP2_PropName[ii++]).c_str());

    bOtcMig=   m.geti(_G_KZP2_PropName[ii++]);
    Emask = m.geti(_G_KZP2_PropName[ii++]);
    kolvo_otc = m.geti(_G_KZP2_PropName[ii++]);

}

void tG_KZP2::UpdateState()
{
    tG_RC::UpdateState();
    
    t_KvKzp * pKvKzp = NULL;
    t_KzpInf * pKzpInf = NULL;
    String stPacketName;
    if (GetDatagramData_Func != NULL) {
        stPacketName = IpxNameKZP + IntToStr(AddrKZP);
        pKvKzp = (t_KvKzp *) GetDatagramData_Func(IpxTypeKZP, stPacketName.c_str());
        stPacketName = IpxNameKZPINF + IntToStr(AddrKZP);
        pKzpInf = (t_KzpInf *) GetDatagramData_Func(IpxTypeKZPINF, stPacketName.c_str());
    }
    if (pKvKzp != NULL) {
        if (memcmp(&KvKzp, pKvKzp, sizeof(KvKzp)) != 0) StateChanged = true;
        memcpy(&KvKzp, pKvKzp, sizeof(KvKzp));
    } else {
        memset(&KvKzp, 0, sizeof(KvKzp));
    }
    if (pKzpInf != NULL) {
        if (memcmp(&KzpInf, pKzpInf, sizeof(KzpInf)) != 0) StateChanged = true;
        memcpy(&KzpInf, pKzpInf, sizeof(KzpInf));
    } else {
        memset(&KzpInf, 0, sizeof(KzpInf));
    }
    if (outD==1) {
       int KzpD, KzpE,KzpV,KzpP;
       if (GetKZPData(AddrKZP-1,KzpD,KzpE,KzpV,KzpP)){
          if ((KvKzp.val!=KzpD)||(KvKzp.stat!=KzpE)||(KvKzp.val_ks!=KzpV)||(KvKzp.val_ks_i!=KzpP)) StateChanged = true;
          KvKzp.val=KzpD;
          //KvKzp.stat=KzpE;
          if (KzpE==65535) KvKzp.stat=1;
          //if (Emask!=0)
          //      KvKzp.stat=KzpE & Emask;
          KvKzp.val_ks=KzpV;
          KvKzp.val_ks_i=KzpP;

       } else {
          KvKzp.stat=1;
       }
    }
    Lmp.pVisibleArray=this->pVisibleArray;
    Lmp.UpdateState();
    if (Lmp.StateChanged) StateChanged = true;


}
const _dd = 2;// отступ от края
const _ddNP = 8;// отступ от края для NP

uint16 delta_time(uint32 t2, uint32 t1)
{
    uint16 _t2 = t2 & 0x0000ffff;
    uint16 _t1 = t1 & 0x0000ffff;
    uint16 res = (_t2 > _t1) ? (_t2 - _t1) : (0xffff - _t1 + _t2);
    return res;
}
double GetVkzp(t_KzpInf *KzpInf, int dxV)
{
    int dl, dl1, val1;
    uint32 dtim, dtim1,  tim1;
    // считаем что tim  абс точно
    // нужная точность не меньше 0.1 м/с
    if ((KzpInf->points_count < 2) ||(KzpInf->points_count > 16)) return KzpInf->v;
    int i = KzpInf->points_count - 1;
    dl = 0; dtim = 0;
    /*do {
        dl1=KzpInf->points[i].val-KzpInf->points[i-1].val;
        dtim1=delta_time(KzpInf->points[i].tim,KzpInf->points[i-1].tim);
        dl=dl+dl1;
        dtim=dtim+dtim1;
        if (dl==-1) dl=0;
        dtim0=1000*10/(dl+1); // мин время для нужной точности в mс.
        i--;
    } while ((i>=1) &&(dl<10) && (dtim<dtim0));   */
    tim1 = KzpInf->points[i].tim; val1 = KzpInf->points[i].val;
    do {
        dl1 = val1 - KzpInf->points[i-1].val;
        if (dl1 > 0) {
            dtim1 = delta_time(tim1, KzpInf->points[i-1].tim);
            if (dtim1 <= 6000) {
                dl = dl + dl1;
                dtim = dtim + dtim1;
            } else break;
            tim1 = KzpInf->points[i].tim; val1 = KzpInf->points[i].val;
        }
        i--;
    } while ((i >= 1) && (dl < 10));

    //  в тупую
    dl = 0;
    for (int i = 1; i < KzpInf->points_count; i++)
        dl = dl + KzpInf->points[i].val - KzpInf->points[i-1].val;
    //dl=KzpInf->points[KzpInf->points_count-1].val-KzpInf->points[0].val;
    dtim = delta_time(KzpInf->points[KzpInf->points_count-1].tim, KzpInf->points[0].tim);
    double v = 0;
    if (dtim == 0) return 0;
    if (KzpInf->points[KzpInf->points_count-1].val < 30) return 0;
    if ((dtim != 0) && (dl >= dxV)) v = (1.*dl / dtim * 1000) * 36.;
    return v;
}
extern int ShowTrainNumbers_nn;
void tG_KZP2::GetNumberPosition(int &X, int &Y, int Width, int Height, int direct)
{
    int xx = this->X * MUL_X + _X_;
    int yy = this->Y * MUL_Y + _Y_;
    xx=xx+NP.x * MUL_X/10;
    yy=yy+NP.y * MUL_Y/10;
    int len = szAll.cx;
    int xdv=0;
    int nn=ShowTrainNumbers_nn;
    if (nn>kolvo_otc) nn=kolvo_otc;
    if (kolvo_otc>1) xdv=szAll.cx/kolvo_otc*ShowTrainNumbers_nn;
    if (direct == 0) X = xx-xdv  ; else X = xx +xdv;
    Y = yy - Height / 2 ;
}

void FlipPx(TPoint *P,int cnt,int X,int DX=0);
void tG_KZP2::Show()
{
    int x = X * MUL_X + _X_;
    int y = Y * MUL_Y + _Y_;
    setcolor(C_D);
    int H_2 = szAll.cy / 2;
    int D, UD, V, Z, ZV, ZV1, ZZ;
    clr_podl = clSilver;  // цвет подложки
    clr_Z = COLOR_B;//210;  // цвет занятости
    clr_S = COLOR_F_P;  // цвет свободности
    clr_US = 77;  // цвет усл свободности

    String stS = "--";
    String stZ = "";
    String stV = "0.0";
    String stP = IntToStr(PutPark);

    if (MOD == ED) {
        D = mas * 10;
        V = AddrKZP;
        UD = masy * 10;
        ZV = 200;
        stS = IntToStr(D);
        stZ = IntToStr(Len);
        if (bShowNumberPosition) {
            int xn, yn;
            setcolor(GELT); _SetText(F_LITT, LEFT_TEXT, TOP_TEXT);
            GetNumberPosition(xn, yn, 0, 0, 0); OutTextXY(xn, yn, "N"); fillellipse(xn, yn, 2, 2);
        }
    } else {
        if (KvKzp.mar == 0) {
            clr_S = clr_podl;
        }
        if (KvKzp.val_ks != 0) clr_Z = 0x000101FF;
        if ((KvKzp.stat != 0) || (KvKzp.val == 0xFFFF)) {
            clr_Z = BIRUZOVIJ;
            clr_S = BIRUZOVIJ;
            D = Len;
        } else {
            D = KvKzp.val;
            if (inUV == 0) stS = IntToStr(D); else
                stS = IntToStr(int(D / 14.));
        }
        UD = KzpInf.pred_val_kzp;
        V = 0;
        if (outV == 1) V = KzpInf.v;
        if (outV == 2) V = GetVkzp(&KzpInf, dxV);//

        Z = Len - D;
        ZV = KzpInf.sum_vag_len;
        ZV1 = KzpInf.pred_vag_len;
        if (ZV > 0) {
            ZZ = (Z - ZV);
            if (inUV != 0) {
                ZZ = ZZ / 14.;
            }
            stZ = "[" + IntToStr(ZZ) + "]";
        }

    }

    int WA = szAll.cx;
    if (Len == 0) Len = 1000;
    if (mashtab > 0)
        WA = Len * (0.01 * mashtab);
    int W = WA - _dd * 2;
    int xx;
    double kx = 1;
    if (W != 0) kx = 1.*W / Len;
    if (D >= Len) xx = W; else xx = 1.*D * kx;


    T[0] = TPoint(x,         y - H_2);
    T[1] = TPoint(x + WA, y - H_2);
    T[2] = TPoint(x + WA, y + H_2);
    T[3] = TPoint(x         , y + H_2);


    // свободглсть
    int svob_tj=LEFT_TEXT;
    TS[0] = TPoint(T[0].x + _dd,         T[0].y + _dd);
    TS[1] = TPoint(T[0].x + _dd + xx,      T[0].y + _dd);
    TS[2] = TPoint(T[0].x + _dd + xx,      T[3].y - _dd);
    TS[3] = TPoint(T[0].x + _dd   ,      T[3].y - _dd);

    /*int xxSV=xx/2-szNSV.cx/2;
    TNS[0]=TPoint(T[0].x+_dd+xxSV         ,         y-szNSV.cy/2);
    TNS[1]=TPoint(T[0].x+_dd+xxSV+szNSV.cx,         TNS[0].y);
    TNS[2]=TPoint(T[0].x+_dd+xxSV+szNSV.cx,         y+szNSV.cy/2);
    TNS[3]=TPoint(T[0].x+_dd+xxSV         ,         TNS[2].y);*/

    TZ[0] = TS[1];
    TZ[1] = TPoint(T[1].x - _dd,         T[1].y + _dd);
    TZ[2] = TPoint(T[1].x - _dd,         T[2].y - _dd);
    TZ[3] = TS[2];


    // Номер Пути
    TNP[0] = TPoint(x + xxNP        , y - szNP.cy / 2);
    TNP[1] = TPoint(x + xxNP + szNP.cy * 2, y - szNP.cy / 2);
    TNP[2] = TPoint(x + xxNP + szNP.cy * 2, y + szNP.cy / 2);
    TNP[3] = TPoint(x + xxNP        , y + szNP.cy / 2);

    // занятость
    if (D < Len) {

        TNZ[0] = TPoint(x + xxNZ                ,     y + yyNZ - szNZ.cy / 2);
        TNZ[1] = TPoint(x + xxNZ + szNZ.cx        ,     y + yyNZ - szNZ.cy / 2);
        TNZ[2] = TPoint(x + xxNZ + szNZ.cx        ,     y + yyNZ + szNZ.cy / 2);
        TNZ[3] = TPoint(x + xxNZ                ,     y + yyNZ + szNZ.cy / 2);
    }

    // усл  занятость
    if (UD > D) {
        int xx_do = 1.*kx * UD;
        // Пршлая занятость
        TUS[0] = TPoint(TZ[0].x            , TZ[0].y);
        TUS[1] = TPoint(TS[0].x + xx_do      , TZ[0].y);
        TUS[2] = TPoint(TS[0].x + xx_do      , TZ[3].y);
        TUS[3] = TPoint(TZ[3].x            , TZ[3].y);
        // занятость вагонами
        if (ZV1 > 0) {
            if (D + ZV1 < UD) {
                int xx_do_dirki = 1.*kx * (D + ZV1);
                TUS[1] = TPoint(TS[0].x + xx_do_dirki      , TZ[0].y);
                TUS[2] = TPoint(TS[0].x + xx_do_dirki      , TZ[3].y);
            }
        }
    }
    // скорость
    if (outV != 0) {
        memset(_TV, 0, sizeof(TV));
        if (V > 0) {
            TV[0] = TPoint(TZ[0].x       ,     T[0].y - _dd - szV.cy);
            TV[1] = TPoint(TZ[0].x + szV.cx,     T[0].y - _dd - szV.cy);
            TV[2] = TPoint(TZ[0].x + szV.cx,     T[0].y - _dd);
            TV[3] = TPoint(TZ[0].x       ,     T[0].y - _dd);
        }
    }

    // переворот
    int fmx=1;
    if (Direct==1){
       fmx=-1;
       int fx=x;
       FlipPx(T,4,          fx);
       FlipPx(TS,4,          fx);
       FlipPx(TZ,4,          fx);
       FlipPx(TNP,4,          fx);  FlipPx(TNP,4,          TNP[0].x,TNP[1].x-TNP[0].x);
       FlipPx(TNZ,4,          fx);
       FlipPx(TUS,4,          fx);
       FlipPx(TV,4,          fx);   FlipPx(TV,4,          TV[0].x,TV[1].x-TV[0].x);
       svob_tj=RIGHT_TEXT;
    }

    // Подложка
    int c1[4] = {   C_D, C_D, C_D, C_D};
    if (WA>0)
       PolyColor(clr_podl, T, c1, 4);

    // Номер Пути
    if (szNP.cy>0){
       setcolor(GELT);
       if (bOtcMig){
           if ((GetDescr_mar(MinWay)!=NULL)||(MOD==ED)){
                setfillstyle(SOLID_FILL, GELT_SER);
                bar(TNP[0].x, TNP[0].y, TNP[0].x+szNP.cy*2, TNP[0].y+szNP.cy);
                setcolor(C_D);
           }
       }

       settextjustify(CENTER_TEXT, CENTER_TEXT);
       settextstyle(1, HORIZ_DIR, szNP.cy - 2);

       DrawText(TNP[0].x, TNP[0].y, szNP.cy*2, szNP.cy, stP.c_str());
    } else {

       strncpy(Lmp.name,stP.c_str(),sizeof(Lmp.name)-1);
       Lmp.X=X+xxNP;
       Lmp.Y=Y;
       Lmp.Show();
       if (bOtcMig){
           unsigned int font = Lmp.Prz[1] ? Lmp.Prz[1] : 10u;
                unsigned int font_size = Lmp.Prz[0] ? (BYTE)(Lmp.Prz[0]) : 10u;
                _SetText(font, CENTER_TEXT , CENTER_TEXT);
                _SetTextSize(font_size);
                int tw = textwidth(Lmp.name)+4;
                int th = textheight(Lmp.name)+4;
           if ((GetDescr_mar(MinWay)!=NULL)||(MOD==ED)){
                setfillstyle(SOLID_FILL, GELT_SER);
                setcolor(FON1);
                barx(Lmp.x-tw/2, Lmp.y-th/2, Lmp.x+tw/2, Lmp.y+th/2);
                Lmp.Show();
           }else {
                setfillstyle(EMPTY_FILL, FON1);
                setcolor(FON1);
                barx(Lmp.x-tw/2, Lmp.y-th/2, Lmp.x+tw/2, Lmp.y+th/2);

           }

       }

    }

    // занятость

    if ((WA>0)&&(D < Len)) {
        int cZ[4] = {   clr_Z, clr_Z, clr_Z, clr_Z};
        PolyColor(clr_Z, TZ, cZ, 4);
        if (outZZ!=0){
           int cF[4] = {   FON, FON, FON, FON};
           PolyColor(FON, TNZ, cF, 4);
           if ((outZZ!=0)&&(ZZ != 0)) {
              setcolor(C_D);
              settextjustify(CENTER_TEXT, CENTER_TEXT);
              settextstyle(1, HORIZ_DIR, szNZ.cy);
              DrawText(TNZ[0].x, TNZ[0].y, szNZ.cx, szNZ.cy, stZ.c_str());
           }
        }
    }
    // усл  занятость
    if ((WA>0)&&(UD > D)) {
        //int xx_do = 1.*kx * UD;
        // Пршлая занятость
        int cUS[4] = {   clr_US, clr_US, clr_US, clr_US};
        PolyColor(clr_US, TUS, cUS, 4);
        // занятость вагонами
        if (ZV1 > 0) {
            int cZ[4] = {   clr_Z, clr_Z, clr_Z, clr_Z};
            PolyColor(clr_Z, TUS, cZ, 4);
        }
    }

    // свободглсть
    if ((WA>0)&&(D > 0)) {
        int cS[4] = {   clr_S, clr_S, clr_S, clr_S};
        PolyColor(clr_S, TS, cS, 4);
        settextjustify(svob_tj, CENTER_TEXT);
        /*if (szNSV.cx>xx) {
           settextstyle(1, HORIZ_DIR, szNSV.cy+2);
           setcolor(LIN);
           DrawText(T[0].x + (_dd-1)*fmx, T[0].y-1, xx*fmx, szNSV.cy+1, stS.c_str());
        } */
        settextstyle(1, HORIZ_DIR, szNSV.cy);
        setcolor(C_D);
        DrawText(T[0].x + _dd*fmx, T[0].y, xx*fmx, szNSV.cy, stS.c_str());


    }

    // скорость
    if ((WA>0)&&(outV != 0)) {
        // стираем
        if ((_TV[0].x != 0)) {
            int cF[4] = {   FON, FON, FON, FON};
            PolyColor(FON, _TV, cF, 4);
        }
        if (V > 0) {
            memcpy(_TV, TV, sizeof(TV));
            double dV_Zad = V / 10.;
            //if ((dV_Zad>4.5) && (dV_Zad<30))
            stV.printf("%2.1f", dV_Zad);
            int cV[4] = {   C_D, C_D, C_D, C_D};
            PolyColor(clInfoBk, TV, cV, 4);
            setcolor(C_D);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(1, HORIZ_DIR, szV.cy);
            DrawText(TV[0].x, TV[0].y, szV.cx, szV.cy, stV.c_str());
        }
    }
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}

void tG_KZP2::ShowTrainNumber()
{
    EXD_ShowTrainNumbers(this, fimpuls_busi );
}



int tG_KZP2::getospolyline(TPoint * PK,int Psz)
{
    if (Psz<2) return 0;
    int y = Y * MUL_Y + _Y_;
    PK[0] = TPoint(T[0].x,         y);
    PK[1] = TPoint(T[1].x     ,    y);
    return 2;

}


static String _tG_RC_2_PropName[] = {
    "тсОси",
    "тсДСО1",
    "тсДСО2",
    "тсДСО1счет",
    "тсДСО2счет"
};

tG_RC_2::tG_RC_2()
 : tG_RC()
{
       imp_osy_cnt=0;
       imp_dso_cnt[0]=0;
       imp_dso_cnt[1]=0;
       imp_dso[0]=0;
       imp_dso[1]=0;
}
void tG_RC_2::GetPropMap(TPropMap &m)
{
    tG_RC::GetPropMap(m);
    int ii = 0;
    m.putEx(_tG_RC_2_PropName[ii++], OldImpToNewStr(imp_osy_cnt   , this), (void*)GetRealImp(imp_osy_cnt   ),       OldImpToNewStr(0, this));
    m.putEx(_tG_RC_2_PropName[ii++], OldImpToNewStr(imp_dso[0], this), (void*)GetRealImp(imp_dso[0]),       OldImpToNewStr(0, this));
    m.putEx(_tG_RC_2_PropName[ii++], OldImpToNewStr(imp_dso[1], this), (void*)GetRealImp(imp_dso[1]),       OldImpToNewStr(0, this));
    m.putEx(_tG_RC_2_PropName[ii++], OldImpToNewStr(imp_dso_cnt[0], this), (void*)GetRealImp(imp_dso_cnt[0]),       OldImpToNewStr(0, this));
    m.putEx(_tG_RC_2_PropName[ii++], OldImpToNewStr(imp_dso_cnt[1], this), (void*)GetRealImp(imp_dso_cnt[1]),       OldImpToNewStr(0, this));

}
void tG_RC_2::SetPropMap(TPropMap &m)
{
    tG_RC::SetPropMap(m);
    int ii = 0;
    imp_osy_cnt    = NewStrToOldImp(m.get(_tG_RC_2_PropName[ii++]).c_str());
    imp_dso[0] = NewStrToOldImp(m.get(_tG_RC_2_PropName[ii++]).c_str());
    imp_dso[1] = NewStrToOldImp(m.get(_tG_RC_2_PropName[ii++]).c_str());
    imp_dso_cnt[0] = NewStrToOldImp(m.get(_tG_RC_2_PropName[ii++]).c_str());
    imp_dso_cnt[1] = NewStrToOldImp(m.get(_tG_RC_2_PropName[ii++]).c_str());

}



