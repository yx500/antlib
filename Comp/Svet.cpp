

#include "Svet.h"

#include "APch.h"
#include "F.h"
#include "Gorl.h"
#include "Impuls.h"
#include "Scrin.h"
#include "aheaders_cpp.h"

Svet_0::Svet_0()
{
  clr = FON;
  clrP = C_D;
  bGorl = false;
  Razmer[0] = 0;
  Razmer[1] = 0;
  Stek = 0;
  impuls_yach = fimpuls_yach = 0;
  impuls_block = 0;
  fimpuls_block = 0;
  impuls_jelt = 0;
  fimpuls_jelt = 0;
  impuls_jeltzel = 0;
  fimpuls_jeltzel = 0;
  impuls_neispr2 = 0;
  fimpuls_neispr2 = 0;
  bZAKRKRA = false;
  yach_sdvig = 0;
  bNiz = false;
  impuls_aum_a = 0;
  impuls_aum_ust = 0;
  fimpuls_aum_a = 0;
  fimpuls_aum_ust = 0;
  bNoShowSV = false;
}

static String _SvetPropName[] = {
    "цфРазмерСт",       // 0
    "цфРазмерУч",       // 1
    "цфСтэк",           // 2
    "тсНачЯчейка",      // 3
    "лгЗакрКрасн",      // 4
    "цфЯчСдвигY",       // 5
    "тсimpuls_block",   //  6
    "тсimpuls_jelt",    //  7
    "тсimpuls_jeltzel", //  8
    "тсНеиспр2",        //  9
    "лгНижнПер",        // 10
    "тсimpuls_aum_a",   //  11
    "тсimpuls_aum_ust"  //  12
};

void Svet_0::SetPropMap(TPropMap& m)
{
  Element::SetPropMap(m);
  Razmer[0] = m.geti(_SvetPropName[0]);
  Razmer[1] = m.geti(_SvetPropName[1]);
  Stek = m.geti(_SvetPropName[2]);
  impuls_yach = NewStrToOldImp(m.get(_SvetPropName[3]).c_str());
  bZAKRKRA = m.geti(_SvetPropName[4]);
  yach_sdvig = m.geti(_SvetPropName[5]);
  impuls_block = NewStrToOldImp(m.get(_SvetPropName[6]).c_str());
  impuls_jelt = NewStrToOldImp(m.get(_SvetPropName[7]).c_str());
  impuls_jeltzel = NewStrToOldImp(m.get(_SvetPropName[8]).c_str());
  impuls_neispr2 = NewStrToOldImp(m.get(_SvetPropName[9]).c_str());
  bNiz = m.geti(_SvetPropName[10]);
  impuls_aum_a = NewStrToOldImp(m.get(_SvetPropName[11]).c_str());
  impuls_aum_ust = NewStrToOldImp(m.get(_SvetPropName[12]).c_str());
}

void Svet_0::GetPropMap(TPropMap& m)
{
  Element::GetPropMap(m);
  m.put(_SvetPropName[0], Razmer[0], 0);
  m.put(_SvetPropName[1], Razmer[1], 0);
  m.put(_SvetPropName[2], Stek, 0);
  m.putEx(_SvetPropName[3], OldImpToNewStr(impuls_yach, this), GetRealImp(impuls_yach), OldImpToNewStr(0, this));
  m.put(_SvetPropName[4], bZAKRKRA, 0);
  m.put(_SvetPropName[5], yach_sdvig, 0);
  m.putEx(_SvetPropName[6], OldImpToNewStr(impuls_block, this), GetRealImp(impuls_block), OldImpToNewStr(0, this));
  m.putEx(_SvetPropName[7], OldImpToNewStr(impuls_jelt, this), GetRealImp(impuls_jelt), OldImpToNewStr(0, this));
  m.putEx(_SvetPropName[8], OldImpToNewStr(impuls_jeltzel, this), GetRealImp(impuls_jeltzel), OldImpToNewStr(0, this));
  m.putEx(_SvetPropName[9], OldImpToNewStr(impuls_neispr2, this), GetRealImp(impuls_neispr2), OldImpToNewStr(0, this));
  m.put(_SvetPropName[10], bNiz, 0);
  m.putEx(_SvetPropName[11], OldImpToNewStr(impuls_aum_a, this), GetRealImp(impuls_aum_a), OldImpToNewStr(0, this));
  m.putEx(_SvetPropName[12], OldImpToNewStr(impuls_aum_ust, this), GetRealImp(impuls_aum_ust), OldImpToNewStr(0, this));
}

void ShowKMUSvet(int x, int y, int iBusy, int iPlus, int iMinus, int mas, char* name, int _NAZVA_)
{
  if ((CurrentPicture == BG) && (iMinus != 1))
    return;
  int sh = sv_ras_y[MUL_Y];
  setcolor(C_D);
  line(x - sh / 2, y, x + sh / 2, y);
  line(x, y, x, y - MUL_Y);
  int Bs[8];
  Bs[0] = x;
  Bs[1] = y - MUL_Y * 1;
  Bs[2] = x + sh;
  Bs[3] = y - MUL_Y * 1;
  Bs[4] = x;
  Bs[5] = y - MUL_Y / 3;
  Bs[6] = x;
  Bs[7] = y - MUL_Y * 1;
  int ColorNum = iBusy * 2 + iPlus;
  if (ColorNum < 4)
    setfillstyle(1, KMUSvetColors[ColorNum]);
  else
    setfillstyle(1, BIRUZOVIJ);
  fillpoly(4, Bs);
  if ((MUL_Y > _NAZVA_) && (CurrentPicture != BG)) {
    setcolor(C_D);
    // if((MUL_Y<(_NAZVA_)))
    _SetText(F_LITT, CENTER_TEXT, TOP_TEXT);
    if ((MUL_Y > (_NAZVA_ + 2)))
      _SetText(F_LITT_B, CENTER_TEXT, TOP_TEXT);
    int mm = mas;
    if (mm > 100)
      mm -= 100;
    switch (mm) {
    case 1:
      _SetTextSize(-sh * 2);
      OutTextXY(x, y, name);
      _SetTextSize(1);
      break;
    case 2:
      break;
    default:
      OutTextXY(x, y, name);
    }
    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
  }
}

void ShowRombik(int x, int y, int sh)
{
  int Bs[10];
  Bs[0] = x - sh;
  Bs[1] = y;
  Bs[2] = x;
  Bs[3] = y - sh;
  Bs[4] = x + sh;
  Bs[5] = y;
  Bs[6] = x;
  Bs[7] = y + sh;
  Bs[8] = x - sh;
  Bs[9] = y;
  fillpoly(5, Bs);
}
void ShowSvetBLOCK(int x, int y, int sh, int pencol, int fillcol)
{
  if (CurrentPicture == BG)
    sh = sh * 1.5;
  else
    sh = sh * 2;
  setfillstyle(1, fillcol);
  setcolor(pencol);
  barx(x - sh, y + sh, x + sh, y - sh);
}
void ShowYacheyka(int x, int y, int pencol, int fillcol, int sh_y)
{
  setfillstyle(1, fillcol);
  setcolor(pencol);

  int y_sdv = 0;
  int x_sdv = 0;
  int wy = sh_y / 2;
  int wx = sh_y * 1;
  int y_off = sh_y / 2;

  barx(x + x_sdv, y - y_off - y_sdv, x + x_sdv + wx, y - y_off - wy - y_sdv);
  barx(x + x_sdv, y + y_off + y_sdv + 1, x + x_sdv + wx, y + y_off + wy + y_sdv);
}
void ShowPerSvet(int x, int y, int type, int iBusy, int iPlus, int iKzm, int mas, int masy, char* name, int fimpuls_block)
{
  // if((CurrentPicture==BG)&&(iMinus!=1)) return;
  int sh = sv_ras_y[MUL_Y];
  int len;
  sh = sh_y / 2;
  if (masy == 2)
    y = y + MUL_Y - sh_y - 1;
  else if (masy == 3)
    y = y + MUL_Y + sh_y + 1;
  if (type == 4)
    len = sh_y;
  if (type == 3)
    len = -sh_y;

  int brclr, pclr;
  brclr = FON;
  pclr = C_D;
  if (iKzm == -1) { // рисуем фоном
    brclr = FON;
    pclr = FON;
  } else {
    int ColorNum = iBusy * 2 + iKzm;
    if (ColorNum < 4)
      brclr = PerSvetColors[ColorNum];
    if (iPlus == 1)
      pclr = KRA_SER;
  }
  setfillstyle(1, brclr);
  setcolor(pclr);
  bool showsv = true;
  bool showN = true;
  if (CurrentPicture == BG) {
    switch (mas) {
    default:
      showN = false;
      break;
    case 1:;
      break;
    case 2:
      showN = true;
      showsv = false;
      break;
    case 3:
      showsv = false;
      showN = false;
      break;
    }
  }
  if (showsv) {
    if ((fimpuls_block == 1) && (CurrentPicture == LT)) {
      ShowSvetBLOCK(x, y, sh, FON1, KRA);
      setfillstyle(1, brclr);
      setcolor(pclr);
    }
    line(x, y, x + len, y);
    line(x + len, y - sh, x + len, y + sh);
    if ((CurrentPicture == BG) && (brclr != FON))
      setcolor(brclr);
    fillellipse(x, y, sh, sh);
    setcolor(pclr);
  }
  if (showN) {
    _SetTextSize(-sh * 2 - 1);
    if (type == 4) {
      _SetText(F_LITT, LEFT_TEXT, CENTER_TEXT);
      OutTextXY(x + len + 4, y, name);
    }
    if (type == 3) {
      _SetText(F_LITT, RIGHT_TEXT, CENTER_TEXT);
      OutTextXY(x + len - 1, y, name);
    }
    _SetTextSize(1);
    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
  }
}

int Svet_0::GetSubType()
{
  if ((masy == 0) && (mas == 100))
    return 4;
  return masy;
}

void Svet_0::UpdateState()
{
  Element::UpdateState();
  int rimpuls_yach = f(impuls_yach);
  int rimpuls_block = f(impuls_block);
  int rimpuls_jelt = f(impuls_jelt);
  int rimpuls_jeltzel = f(impuls_jeltzel);
  int rimpuls_neispr2 = f(impuls_neispr2);
  int rimpuls_aum_a = f(impuls_aum_a);
  int rimpuls_aum_ust = f(impuls_aum_ust);

  StateChanged = StateChanged | (rimpuls_yach != fimpuls_yach) | (rimpuls_block != fimpuls_block) | (rimpuls_jelt != fimpuls_jelt) | (rimpuls_jeltzel != fimpuls_jeltzel) | (rimpuls_neispr2 != fimpuls_neispr2) |
                 (fimpuls_aum_a != rimpuls_aum_a) | (fimpuls_aum_ust != rimpuls_aum_ust);
  fimpuls_yach = rimpuls_yach;
  fimpuls_block = rimpuls_block;
  fimpuls_jelt = rimpuls_jelt;
  fimpuls_jeltzel = rimpuls_jeltzel;
  fimpuls_neispr2 = rimpuls_neispr2;
  fimpuls_aum_a = rimpuls_aum_a;
  fimpuls_aum_ust = rimpuls_aum_ust;
  M = 0;
  if (
      (name[0] == 'M') ||
      (name[0] == 'm') ||
      (name[0] == 'М') ||
      (name[0] == 'м'))
    M = 1;

  bNoShowSV = false;
  clrP = C_D;
  if ((bGorl) && (impuls_busi == 0)) {
    /* Горловина позаботилась  */
    // не рисуем маневровые если не активные

    if (((M) || (M1)) && ((AO->bNoShowMSV) && (MOD == RD) && (CurrentPicture == BG) && (clr == FON))) {
      bNoShowSV = true;
    }

  } else {

    if (impuls_busi + impuls_plus + impuls_mnus + impuls_kzm + impuls_kmu + impuls_mu == 0) {
      clrP = 9;
    } else
      // разбираем по типам
      if ((masy == 2) || (masy == 3)) { // перегон
        int bz = fimpuls_busi;
        if (fimpuls_jelt == 1)
          bz = 1;
        if (fimpuls_jeltzel == 1)
          bz = 1;
        clr = FON;
        clrP = C_D;
        if (fimpuls_kzm == -1) { // рисуем фоном ?
          clr = FON;
          clrP = FON;
        } else {
          int ColorNum = bz * 2 + fimpuls_kzm;
          if (ColorNum < 4)
            clr = PerSvetColors[ColorNum];
          if (fimpuls_plus == 1)
            clrP = KRA_SER;
          if (fimpuls_neispr2 == 1)
            clrP = KRA_SER;
          if ((CurrentPicture != BG) && (fimpuls_jelt == 1) && (fimpuls_busi == 0) && (fimpuls_kzm == 0))
            clr = GELT;
        }
      } else

          if ((masy == 4) || (mas == 100)) { // Людочкин
        int cc = fimpuls_busi * 4 + fimpuls_kzm * 2 + fimpuls_kmu;
        if (cc >= 8)
          clr = BIRUZOVIJ;
        else if (cc < 0)
          clr = RED;
        else
          clr = SvetStateColors100[cc];
        if (fimpuls_mnus)
          clrP = ZEL;
        // я не знаю зачем исключали при горящем!
        if ((fimpuls_plus == 1) && (fimpuls_busi == 0))
          clr = COLOR_PSV;
        if ((fimpuls_plus == 1) && (fimpuls_busi == 1))
          clr = ZEL_MIG;
      } else

          if ((masy == 5)) { // Приглас
        int cc = fimpuls_busi + fimpuls_kzm * 2;
        if (cc >= 4)
          clr = BIRUZOVIJ;
        else if (cc < 0)
          clr = RED;
        else
          clr = SvetStateColors101[cc];

        if (fimpuls_mnus)
          clrP = ZEL;
        if ((fimpuls_plus == 1) && (fimpuls_busi == 0))
          clr = COLOR_PSV;
        if ((fimpuls_plus == 1) && (fimpuls_busi == 1))
          clr = ZEL_MIG;
        if (clr == FON)
          clrP = FON1;
      } else

          if ((masy == 6)) { // Ант ехтра
        int cc = fimpuls_busi + fimpuls_plus * 2 + fimpuls_mnus * 4 + fimpuls_kzm * 8 + fimpuls_kmu * 16 + fimpuls_mu * 32;
        if ((cc >= 64) || (fimpuls_busi == 33)) {
          clr = BIRUZOVIJ;
        } else {
          clr = SvetStateColors006[cc][0];
          clrP = SvetStateColors006[cc][1];
        }
      } else if ((masy == 7)) { // Люд ехтра
        int cc = fimpuls_busi * 1 + fimpuls_plus * 2 + fimpuls_mnus * 4 + fimpuls_kzm * 8 + fimpuls_kmu * 16 + fimpuls_mu * 32;
        if ((cc >= 64) || (fimpuls_busi == 33)) {
          clr = BIRUZOVIJ;
        } else {
          clr = SvetStateColors007[cc][0];
          clrP = SvetStateColors007[cc][1];
        }
      } else if ((masy == 8)) { // Люд ехтра
        int cc = fimpuls_busi * 1 + fimpuls_plus * 2 + fimpuls_mnus * 4 + fimpuls_kzm * 8 + fimpuls_kmu * 16 + fimpuls_mu * 32;
        if ((cc >= 64) || (fimpuls_busi == 33)) {
          clr = BIRUZOVIJ;
        } else {
          clr = SvetStateColors008[cc][0];
          clrP = SvetStateColors008[cc][1];
        }
      } else if ((masy == 9)) { // ебилог
        clrP = C_D;
        static int SvetPColors009_AV_n[4] = {
            // N     AV  neispr
            C_D,       // 0     0   0    ФОН
            KRA,       // 1     0   1    КРАCНЫЙ
            COLOR_SVZ, // 2     1   0    ЗЕЛ
            KRA_ZEL,   // 3     1   1    ЗЕЛ-КРА
        };
        int cc = fimpuls_plus * 1 + fimpuls_mnus * 2;
        if (cc < 4)
          clrP = SvetPColors009_AV_n[cc];

        // если нет неисправности проверяем соотв ко
        if (clrP == C_D) {
          if ((fimpuls_kmu == 1) && (impuls_mu != 0) && (fimpuls_mu == 0))
            clrP = KRA_CHERN;
          if (fimpuls_neispr2 == 1)
            clrP = KRA_CHERN;
        }

        static int SvetBColors009[8] = {
            //                 З   К   Мн
            FON,       //  0 0   0   0    ФОН
            TXT,       //  1 0   0   1    БЕЛЫЙ
            KRA,       //  2 0   1   0    КРАCНЫЙ
            KRA_BEL,   //  3 0   1   1    КРА-БЕЛЫЙ
            COLOR_SVZ, //  4 1   0   0    ЗЕЛЁНЫЙ
            ZEL_LIN,   //  5 1   0   1    ЗЕЛЁНЫЙ-БЕЛЫЙ
            KRA_ZEL,   //  6 1   1   0    ЗЕЛЁНЫЙ-KPA
            KRA_ZEL    //  7 1   1   1    ЗЕЛЁНЫЙ
        };
        int bz = fimpuls_busi;
        if (fimpuls_jelt == 1)
          bz = 1;
        if (fimpuls_jeltzel == 1)
          bz = 1;
        cc = fimpuls_kzm * 1 + fimpuls_kmu * 2 + bz * 4;

        if ((cc >= 8) || (fimpuls_busi == 33))
          clr = BIRUZOVIJ;
        else
          clr = SvetBColors009[cc];
        if ((!bZAKRKRA) && (clr == KRA))
          clr = FON;

      } else if ((masy == 10)) { // // ебилог блок поездных
        clrP = C_D;
        clrP2 = C_D;
        clr = FON;
        clrB2 = FON;
        if ((impuls_busi % 1000 > 960 - 22) || (f(impuls_busi + 0) == 33)) {
          clr = BIRUZOVIJ;
          clrB2 = BIRUZOVIJ;
        }
        int clrB_BG = FON;
        if (impuls_busi >= 1000) {
          // if (f(impuls_busi-1 )==1) { clr=FON;                            clrB2=FON;}  //  Нет информации (НС)

          if (f(impuls_busi + 1) == 1) {
            clr = GELT;
            clrB_BG = COLOR_SVZ;
            clrB2 = GELT;
          } //  Два желтых (НС)
          if (f(impuls_busi + 2) == 1) {
            clr = GELT;
            clrB_BG = COLOR_SVZ;
            clrB2 = FON;
          } //  Желтый (НС)
          if (f(impuls_busi + 3) == 1) {
            clr = GELT_SER;
            clrB_BG = COLOR_SVZ;
            clrB2 = GELT;
          } //  Желтый мигающий + желтый (НС)
          if (f(impuls_busi + 4) == 1) {
            clr = COLOR_SVZ;
            clrB_BG = COLOR_SVZ;
            clrB2 = FON;
          } //Зеленый (НС)
          if (f(impuls_busi + 5) == 1) {
            clr = BEL_SER;
            clrB_BG = clr;
            clrB2 = KRA;
          } //  Белый мигающий + красный (пригласительный) (НС)
          if (f(impuls_busi + 6) == 1) {
            clr = COLOR_SVZ;
            clrB_BG = COLOR_SVZ;
            clrB2 = GELT;
          } //    Зеленый + желтый (НС)
          if (f(impuls_busi + 7) == 1) {
            clr = GELT_SER;
            clrB_BG = COLOR_SVZ;
            clrB2 = FON;
          } //      Желтый мигающий (НС)
          if (f(impuls_busi + 8) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = FON;
          } //      Белый (НС)
          if (f(impuls_busi + 9) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = GELT;
          } //      Белый + желтый (НС)
          if (f(impuls_busi + 10) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = GELT_SER;
          } //      Белый + желтый мигающий (НС)
          if (f(impuls_busi + 11) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = COLOR_SVZ;
          } //      Белый + зеленый (НС)
          if (f(impuls_busi + 12) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = GELT;
          } //      Белый + желтый (НС)
          if (f(impuls_busi + 13) == 1) {
            clr = TXT;
            clrB_BG = TXT;
            clrB2 = GELT_SER;
          } //      Белый + желтый мигающий (НС)
          // if (f(impuls_busi+14)==1) { clrB=FON;   clrB2=FON;}//      Сигнал не блокирован (НС)
          if (f(impuls_busi + 15) == 1) {
            fimpuls_block = 1;
          } //      Сигнал блокирован (НС)
          // if (f(impuls_busi+16)==1) { clrB=FON;   clrB2=FON;}//      Нет отмены маршрута от сигнала (НС)
          // if (f(impuls_busi+17)==1) { clrB=FON;   clrB2=FON;}//      Выполняется отмена маршрута от сигнала (НС)
          // if (f(impuls_busi+18)==1) { clrB=FON;   clrB2=FON;}//      Нет маршрута без открытия сигнала (НС)
          // if (f(impuls_busi+19)==1) { clrB=FON;   clrB2=FON;}//      Установлен режим маршрута без открытия сигнала (НС)
          // if (f(impuls_busi+20)==1) { clrP=FON;   clrB2=FON;}//      Автодействие выключено (НС)
          if (f(impuls_busi + 21) == 1) {
            clrP = COLOR_SVZ;
          } //      Автодействие включено (НС)
          // if (f(impuls_busi+22)==1) { clrB=FON;   clrB2=FON;}//      Ответственная команда отсутствует (НС)
          // if (f(impuls_busi+23)==1) { clrB=FON;   clrB2=FON;}//      Задана ответственная команда (НС)
          // if (f(impuls_busi+24)==1) { clrB=FON;   clrB2=FON;}//      Таймер задержки открытия выключен (НС)
          // if (f(impuls_busi+25)==1) { clrB=FON;   clrB2=FON;}//      Таймер задержки открытия включен (НС)
          // if (f(impuls_busi+26)==1) { clrB=FON;   clrB2=FON;}//      Фиксация отмены маршрута при занятом участке приближения - снятие (НС)
          // if (f(impuls_busi+27)==1) { clrB=FON;   clrB2=FON;}//      Фиксация отмены маршрута при занятом участке приближения (НС)
          // if (f(impuls_busi+28)==1) { clrB=FON;   clrB2=FON;}//      Нет занятости первого участка приближения-удаления при установке выходного маршрута (НС)
          // if (f(impuls_busi+29)==1) { clrB=FON;   clrB2=FON;}//      Первый участок приближения-удаления занят при установки выходного маршрута (НС)
          // if (f(impuls_busi+30)==1) { clrB=FON;   clrB2=FON;}//      Резервный красный не включен (НС)

          if (f(impuls_busi + 0) == 1) {
            clr = KRA;
            clrB2 = FON;
          } //  Красный (НС)

          if (CurrentPicture == BG)
            clr = clrB_BG;
        }

      } else if ((masy == 11)) { // // ебилог блок маневровых
        clrP = C_D;
        clrP2 = C_D;
        clr = FON;
        clrB2 = FON;
        if ((impuls_busi % 1000 >= 960 - 22) || (f(impuls_busi + 0) == 33)) {
          clr = BIRUZOVIJ;
          clrB2 = BIRUZOVIJ;
        }
        if (impuls_busi >= 1000) {
          if (f(impuls_busi - 1) == 1) {
            clr = FON;
          } //  Нет информации (НС)

          if (f(impuls_busi + 1) == 1) {
            clr = FON;
          } //  Погасший (М2)
          if (f(impuls_busi + 2) == 1) {
            clr = TXT;
          } //  Разрешающее показание (М2)
          if (f(impuls_busi + 3) == 1) {
            clr = FON;
          } //  Синий (М2)
          if (f(impuls_busi + 4) == 1) {
            clr = TXT;
          } //  Два белых огня (М2)
          // if (f(impuls_busi+5 )==1) { clrB=FON;  }  //  Не блокирован (М2)
          if (f(impuls_busi + 6) == 1) {
            fimpuls_block = 1;
          } //  Блокирован (М2)
          // if (f(impuls_busi+7 )==1) { clrB=FON;  }  //  Задержка открытия - таймер выключен (М2)
          // if (f(impuls_busi+8 )==1) { clrB=FON;  }  //  Задержка открытия - таймер включен (М2)
          // if (f(impuls_busi+9 )==1) { clrB=FON;  }  //  Нет отмены маршрута (М2)
          // if (f(impuls_busi+10)==1) { clrB=FON;  }  //  Выполняется отмена маршрута от сигнала (М2)
          // if (f(impuls_busi+11)==1) { clrB=FON;  }  //  Не установлен маршрут без открытия сигнала (М2)
          // if (f(impuls_busi+12)==1) { clrB=FON;  }  //  Установлен маршрут без открытия сигнала (М2)
          // if (f(impuls_busi+13)==1) { clrB=FON;  }  //  Ответственная команда отсутствует (М2)
          // if (f(impuls_busi+14)==1) { clrB=FON;  }  //  Задана ответственная команда (М2)
          // if (f(impuls_busi+15)==1) { clrB=FON;  }  //  Нет исключения проверки состояния сигнала прикрытия (М2)
          // if (f(impuls_busi+16)==1) { clrB=FON;  }  //  Исключение проверки состояния сигнала прикрытия (М2)
          // if (f(impuls_busi+17)==1) { clrB=FON;  }  //  От сигнала не устанавливается маршрут (М2)
          // if (f(impuls_busi+18)==1) { clrB=FON;  }  //  От сигнала устанавливается поездной маршрут (М2)
          // if (f(impuls_busi+19)==1) { clrB=FON;  }  //  От сигнала устанавливается маневровый маршрут (М2)

          if (f(impuls_busi + 0) == 1) {
            clr = FON;
          } //  Запрещающее показание (М2)
        }
      } else if ((masy == 0) && (mas < 100)) { // обычный
        if (M == 1) {
          clr = Clr_SetC(fimpuls_busi, M, fimpuls_plus, fimpuls_mnus);
        } else {
          int cc = fimpuls_busi * 4 + fimpuls_plus * 2 + fimpuls_mnus;
          if (cc < 8) {
            clr = SvetStateColors000[cc][0];
            clrP = SvetStateColors000[cc][1];
          } else {
            clr = BIRUZOVIJ;
          }
        }
      }
    if (impuls_aum_a != 0) {
      if (fimpuls_aum_a == 1)
        clrP = ZEL;
      if (fimpuls_aum_ust == 1)
        clrP = ZEL_MIG;
    }

    // не рисуем маневровые если не активные

    if (((M) || (M1)) && ((AO->bNoShowMSV) && (MOD == RD) && (CurrentPicture == BG) && (fimpuls_busi == 0) && (fimpuls_plus == 0) && (fimpuls_mnus == 0) && (fimpuls_kzm == 0))) {
      clr = FON;
      clrP = FON;
      bNoShowSV = true;
    }

    // не рисовать при масу=4 при активном му на участке
    if ((masy == 4) && ((M) || (M1)) && (impuls_mu != 0) && (CurrentPicture == BG) && (fimpuls_mu == 0)) {
      clr = FON;
      clrP = FON;
      bNoShowSV = true;
    }
  }

  if ((_clrP != clrP) || (_clr != clr))
    StateChanged = true;
  _clrP = clrP;
  _clr = clr;

  // если мигающий цвет превентивно рисуем ! (что такое 'превентивно' ?)
  if ((IsClrMig(clr)) ||
      (IsClrMig(clrP)))
    StateChanged = true;
}

int Svet_0::IsAlarmState()
{
  int b = 0;
  if ((bGorl) && (impuls_busi == 0)) {
    /* Горловина позаботилась  */
  } else {
    if (impuls_busi + impuls_plus + impuls_mnus + impuls_kzm + impuls_kmu + impuls_mu == 0) {
    } else
      // разбираем по типам
      if ((masy == 4) || (mas == 100)) { // Людочкин
        if (fimpuls_plus == 1)
          b = impuls_plus;
      } else if ((masy == 5)) { // Приглас
        if (fimpuls_plus == 1)
          b = impuls_plus;
      } else if ((masy == 6)) { // Ант ехтра
        if (fimpuls_plus == 1)
          b = impuls_plus;
        if ((fimpuls_kzm == 1) && (fimpuls_busi == 1))
          b = impuls_kzm;
        if (fimpuls_mu == 1)
          b = impuls_mu;
      } else if ((masy == 7)) { // Люд ехтра
        if (fimpuls_plus == 1)
          b = impuls_plus;
      } else if ((masy == 8)) { // Люд ехтра
        if (fimpuls_plus == 1)
          b = impuls_plus;
        if (fimpuls_kmu == 1)
          b = impuls_kmu;
      } else if ((masy == 9)) { // ебилог
        if (fimpuls_plus == 1)
          b = impuls_plus;
      } else if ((masy == 0) && (mas < 100)) { // обычный
        if (fimpuls_plus == 1)
          b = impuls_plus;
      }
  }
  return b;
}

bool Svet_0::Show1()
{
  if ((bNoShowSV) && (MOD == RD))
    return false;
  xx = X * MUL_X + _X_;
  yy = Y * MUL_Y + _Y_;
  M = 0;
  M1 = 0;

  M = 0;
  M1 = 0;
  if (
      (name[0] == 'm') ||
      (name[0] == 'м'))
    M = 1;
  if (
      (name[0] == 'М') ||
      (name[0] == 'M') ||
      (name[0] == 'п'))
    M1 = 1;

  ZagradSv = 0;
  if (
      (name[0] == 'П') ||
      (name[0] == 'п'))
    ZagradSv = 1;

  sh = sv_ras_y[MUL_Y];

  if ((sh < AO->SVET_LIM)) {
    // if (M==1) x--;
    sh = AO->SVET_LIM;
    len = 2 * sh;
  }

  if (Razmer[CurrentPicture] != 0) {
    sh = Razmer[CurrentPicture];
    len = 2 * sh;
  }

  if (Stek != 0)
    xx = xx + Stek * sh * 2;

  if (MOD == ED) {
    // if (impuls_block!=0)   ShowSvetBLOCK(xx,yy,sh,FON1,FON1);
    // clr=FON;
    // if (!DNC)clr = LIN;
    //      if(GetUnit()==PLOT){if(!M)clr = COLOR_B;else clr = FON; };
    //      if((!FLG)){ if(!M)clr = COLOR_B;else clr = FON;};
    //      if((FLG)){  if(!M)clr = COLOR_B;else clr = FON;
    //        if(!strcmp(Curr_G->gorl[0]->Sign[MARSH].name,name)){if(!M)clr = COLOR_SVZ;else clr = TXT;}
    //        if(!strcmp(Curr_G->gorl[0]->Sign_i.name,name)){if(!M)clr = COLOR_SVZ;else clr = TXT;}
    //      }
  } else {
    // if(!NIKOLA){ if(impuls_busi==0) return;}
    // else if(impuls_busi==0){ clr = Clr_SetC(0,0);};

    // см UpdateState()

    // не рисуем не активные на уч
    if ((ExtPriz.isNoShowYchAct()== 1) && (AO->bNoShowPSV)) {
      if ((CurrentPicture == BG) && (clr == FON) && (fimpuls_busi == 0) && (fimpuls_plus == 0) && (fimpuls_mnus == 0) && (fimpuls_kzm == 0)) {
        clrP = FON1;
      } else {
        // clrP=C_D;
      }
    }
  }

  // признак мигания
  if (pr)
    clrP = SV_MIG;
  setcolor(clrP);

  if ((masy == 1)) {
    if ((fimpuls_block == 1) && (CurrentPicture == LT))
      ShowSvetBLOCK(xx, yy, sh, FON1, KRA);
    ShowKMUSvet(xx, yy, fimpuls_busi, fimpuls_plus, fimpuls_mnus, mas, name, AO->_NAZVA_);
    return false;
  }
  if (((masy == 2) || (masy == 3))) {
    /*int bz=fimpuls_busi;
    if (fimpuls_jelt==1) bz=1;
    */

    if (Razmer[CurrentPicture] == 0)
      sh = sh_y / 2;
    if (bNiz) {
      xx = (xx - _X_) / MUL_X;
      yy = (yy - _Y_) / MUL_Y;
      yy += DELTA_Y;
      xx += DELTA_X;
      if (masy == 2)
        yy = yy + MUL_Y - sh_y - 1;
      else if (masy == 3)
        yy = yy + MUL_Y + sh_y + 1;
    } else {
      if (masy == 2)
        yy = yy + MUL_Y - sh_y / 2 - sh - sh;
      else if (masy == 3)
        yy = yy - MUL_Y + sh_y / 2 + sh + sh;
    }
    if (GetType() == 4)
      len = sh_y;
    if (GetType() == 3)
      len = -sh_y;

    // ShowPerSvet(xx, yy, GetType(), bz, fimpuls_plus, fimpuls_kzm, mas, masy, name,fimpuls_block);
    // return false;
    if ((fimpuls_block == 1) && (CurrentPicture == BG))
      ShowSvetBLOCK(xx, yy, sh, FON1, KRA);
  }

  // не рисовать у людочкиных при неактивном му на участке
  if ((mas >= 100) && (fimpuls_plus != 1)) {
    if ((impuls_mu != 0) && (CurrentPicture == BG) && (fimpuls_mu != 1))
      return false;
  }

  if ((fimpuls_block == 1) && (CurrentPicture == LT))
    ShowSvetBLOCK(xx, yy, sh, FON1, KRA);
  setcolor(clrP);

  return true;
}

void Svet_R::Show()
{
  if (!Svet_0::Show1())
    return;

  len = 2 * sh;

  // стираем фоном
  if (impuls_yach != 0)
    ShowYacheyka(xx - sh, yy + (yach_sdvig + 1) * MUL_Y, FON, FON, sh_y);
  if ((MOD == ED) && (impuls_yach != 0))
    ShowYacheyka(xx - sh, yy + (yach_sdvig + 1) * MUL_Y, C_D, FON, sh_y);
  // рисуем
  if (fimpuls_yach == 1)
    ShowYacheyka(xx - sh, yy + (yach_sdvig + 1) * MUL_Y, C_D, SV_MIG, sh_y);
  setcolor(clrP);

  // подгоняем разmер
  if (AO->bPodgonSvet) {
    int rr = MUL_Y - sh - sh_y / 2 - 2;
    if (rr < 0)
      if (masx2 == 1) /*((name[1]=='¤')||(name[1]=='„'))*/
        yy = yy - rr;
      else
        yy = yy + rr;
  }

  if ((!M) && (!M1)) {
    line(xx, yy, xx + len, yy);
    line(xx + len, yy - sh, xx + len, yy + sh);
  }
  if (M1) {
    line(xx + sh, yy - sh, xx + sh, yy + sh);
  }

  setfillstyle(1, clr);
  if ((name[1] == 'Ж') && (clr == TXT))
    setfillstyle(1, GELT);
  if ((name[1] == 'К') && (clr == TXT))
    setfillstyle(1, KRA);

  _SetText(F_DEFAULT, LEFT_TEXT, CENTER_TEXT);

  if ((M) && (Stek == 0))
    xx = xx + MUL_X - sh * 2 - 1;

  if (ZagradSv == 1)
    ShowRombik(xx, yy, sh);
  else {
    fillellipse(xx, yy, sh, sh);
    if ((masy == 10) && (CurrentPicture == LT)) {
      setfillstyle(1, clrB2);
      fillellipse(xx - 2 * sh, yy, sh, sh);
    }
  }

  if (((MUL_Y > AO->_NAZVA_) || (CurrentPicture == LT)) && (!M)) {
    if ((MUL_Y < (AO->_NAZVA_)) && (!M))
      _SetText(F_LITT, LEFT_TEXT, CENTER_TEXT);
    if ((MUL_Y > (AO->_NAZVA_ + 2)) && (!M))
      _SetText(F_LITT_B, LEFT_TEXT, CENTER_TEXT);
    if (M1)
      len = sh + 1;
    int mm = mas;
    if (mm > 100)
      mm -= 100;
    switch (mm) {
    case 1:
      _SetTextSize(-sh * 2);
      OutTextXY(xx + len + 4, yy, name);
      _SetTextSize(1);
      break;
    case 2:
      break;
    default:
      OutTextXY(xx + len + 4, yy, name);
    }
  }
  _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
}
TYP Svet_R::GetType()
{
  return SIG_R;
}
UNIT Svet_R::GetUnit()
{
  return CEMA;
}

void Svet_L::Show()
{
  if (!Svet_0::Show1())
    return;

  len = -2 * sh;

  // стираем фоном
  if (impuls_yach != 0)
    ShowYacheyka(xx + sh - sh_y, yy - (yach_sdvig + 1) * MUL_Y, FON, FON, sh_y);
  if ((MOD == ED) && (impuls_yach != 0))
    ShowYacheyka(xx + sh - sh_y, yy - (yach_sdvig + 1) * MUL_Y, C_D, FON, sh_y);
  // рисуем
  if (fimpuls_yach == 1)
    ShowYacheyka(xx + sh - sh_y, yy - (yach_sdvig + 1) * MUL_Y, C_D, SV_MIG, sh_y);
  setcolor(clrP);

  // подгоняем разmер
  if (AO->bPodgonSvet) {
    int rr = MUL_Y - sh - sh_y / 2 - 2;
    if (rr < 0)
      if (masx2 == 1) /*((name[1]=='¤')||(name[1]=='„'))*/
        yy = yy + rr;
      else
        yy = yy - rr;
  }

  if ((!M) && (!M1)) {
    line(xx, yy, xx + len, yy);
    line(xx + len, yy - sh, xx + len, yy + sh);
  }
  if (M1) {
    line(xx - sh, yy - sh, xx - sh, yy + sh);
  }

  setfillstyle(1, clr);
  if ((name[1] == 'Ж') && (clr == TXT))
    setfillstyle(1, GELT);
  if ((name[1] == 'К') && (clr == TXT))
    setfillstyle(1, KRA);

  _SetText(F_DEFAULT, RIGHT_TEXT, CENTER_TEXT);

  if (M)
    xx = xx - MUL_X + sh * 2 + 1;

  if (ZagradSv == 1)
    ShowRombik(xx, yy, sh);
  else {
    fillellipse(xx, yy, sh, sh);
    if ((masy == 10) && (CurrentPicture == LT)) {
      setfillstyle(1, clrB2);
      fillellipse(xx + 2 * sh, yy, sh, sh);
    }
  }

  if (((MUL_Y > AO->_NAZVA_) || (CurrentPicture == LT)) && (!M)) {

    if ((MUL_Y < (AO->_NAZVA_)) && (!M))
      _SetText(F_LITT, RIGHT_TEXT, CENTER_TEXT);
    if ((MUL_Y > (AO->_NAZVA_ + 2)) && (!M))
      _SetText(F_LITT_B, RIGHT_TEXT, CENTER_TEXT);

    if (M1)
      len = -sh - 1;
    int mm = mas;
    if (mm > 100)
      mm -= 100;
    switch (mm) {
    case 1:
      _SetTextSize(-sh * 2);
      OutTextXY(xx + len - 1, yy, name);
      _SetTextSize(1);
      break;
    case 2:
      break;
    default:
      OutTextXY(xx + len - 1, yy, name);
    }
  }
  _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);
}
TYP Svet_L::GetType()
{
  return SIG_L;
};
UNIT Svet_L::GetUnit()
{
  return CEMA;
};
