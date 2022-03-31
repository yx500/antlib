//---------------------------------------------------------------------------


#include "aheaders_cpp.h"

#include "APch.h"
#include "Scrin.h"
#include "EnergUnit.h"
#include "Stan.h"
#include "Comp.h"
#include "Elem.h"
#include "Lamps.h"
#include "Polig.h"
#include "uImgContainer.h"
#include "Impuls.h"
#include "LampExtDraw.h"
//---------------------------------------------------------------------------





TEnergLampData * __fastcall GetEnergLampData(TEnergStanLamps * EnergStanLamps, uint16 ObjID)
{
    for (int i = 0; i < _MaxLampsInPacket; i++) {
        if (EnergStanLamps->Lamps[i].ObjID == 0) break;
        if (EnergStanLamps->Lamps[i].ObjID == ObjID)
            return &EnergStanLamps->Lamps[i];
    }
    return NULL;
}

int __fastcall SetEnergLampData(TEnergStanLamps * EnergStanLamps, uint16 ObjID, TEnergLampData * EnergLampData)
{
    int res;
    int exi = -1;
    int lasti = 0;
    for (int i = 0; i < _MaxLampsInPacket; i++) {
        if (EnergStanLamps->Lamps[i].ObjID == 0) {
            lasti = i;
            break;
        }
        if (EnergStanLamps->Lamps[i].ObjID == ObjID) {
            if (exi >= 0) {
                return -1;
            }
            exi = i; res = 0;
        }
    }
    if (exi < 0) {
        exi = lasti; res = 1;
    }
    if (exi >= _MaxLampsInPacket) return -2;
    memcpy(&EnergStanLamps->Lamps[exi], EnergLampData, sizeof(TEnergLampData));
    return res;
}

void __fastcall LoadTEnergStanLamps(char * fn, TEnergStanLamps * EnergStanLamps)
{
    if (FileExists(fn)) {
        TFileStream * FS = new TFileStream(fn, fmOpenRead);
        FS->Read(EnergStanLamps, sizeof(TEnergStanLamps));
        delete FS;
    }

}
void __fastcall LampsLSFromNet(Station *Stan)
{
    /* ����������� ������ �������  */
    if (GetDatagramData_Func == NULL) return;
    TEnergStanLamps * ESL = (TEnergStanLamps *)GetDatagramData_Func(8, Stan->Dat->filename);

    if (ESL != NULL) {
        memset(Stan->EnergStanLamps, 0, sizeof(TEnergStanLamps));
        // �������� �����
        memcpy(Stan->EnergStanLamps, ESL, sizeof(TEnergStanLamps));
    } else {
        

    }

    // ������� �� ����
// if (ESL->T.Val==0) return;

    // ���������� �� �������
    //if ((Stan->EnergStanLamps->T.Val==0)||
    //    (Stan->EnergStanLamps->T<ESL->T)) {

    // ����������� �����

    TE_OBJ * eo;
    TEnergLampData * ELD;
    for (int j = 0; j < Stan->POLE[WAYS]->GetArraySize(); j++) {
        eo = dynamic_cast<TE_OBJ *>(Stan->POLE[WAYS]->GetObjPtr(j));
        if (eo == NULL) continue;
        // ������ �� ������ �����-������ �� ���������
        if (ESL == NULL) {
            // ��� ������ ������ � �� �������
            //memcpy(&eo->KeySost_current, &eo->KeySost_default, sizeof(TE_KeySost));
            continue;
        }
        // ���� � ������
        ELD = GetEnergLampData(Stan->EnergStanLamps, eo->GetID());
        if (ELD == NULL) {
            // ������ �� ������ �����-������
            memcpy(&eo->KeySost_current, &eo->KeySost_default, sizeof(TE_KeySost));
            continue;
        }
        memcpy(&eo->KeySost_current, &ELD->KeySost, sizeof(TE_KeySost));
    }
// }
}





void __fastcall SaveLampsLS(Station *Stan)
{
    //��������� �����
    int cnt = 0;
    TE_OBJ * eo;
    memset(Stan->EnergStanLamps, 0, sizeof(Stan->EnergStanLamps));
    for (int j = 0; j < Stan->POLE[WAYS]->GetArraySize(); j++) {
        eo = dynamic_cast<TE_OBJ *>(Stan->POLE[WAYS]->GetObjPtr(j));
        if (eo == NULL) continue;
        //lmp->LS->__MyStat5=lmp->MyStat5;
        if (memcmp(&eo->KeySost_current, &eo->KeySost_default, sizeof(TE_KeySost)) == 0) continue;
        Stan->EnergStanLamps->Lamps[cnt].ObjID = eo->GetID();
        memcpy(&Stan->EnergStanLamps->Lamps[cnt].KeySost, &eo->KeySost_current, sizeof(TE_KeySost));
        //memset(&Stan->EnergStanLamps->Lamps[cnt].Reserv,0,sizeof(Stan->EnergStanLamps->Lamps[cnt].Reserv));
        cnt++;
        if (cnt == _MaxLampsInPacket) {
            ShowMessage("������������ ������ ����������� �� ������� " + String(Stan->Dat->filename));
            cnt = _MaxLampsInPacket - 1;
        }
    }
    String fn = ChangeFileExt(Stan->FullFN(), ".stx");
    TFileStream * FS = new TFileStream(fn, fmCreate);
    FS->Write(Stan->EnergStanLamps, sizeof(TEnergStanLamps));
    delete FS;

}

void __fastcall LoadLampsLS(Station *Stan)
{
    //��������� �����
    //int cnt=0;
    TE_OBJ * eo;
    memset(Stan->EnergStanLamps, 0, sizeof(TEnergStanLamps));
    String fn = ChangeFileExt(Stan->FullFN(), ".stx");
    if (!FileExists(fn))
        return;
    TFileStream * FS = new TFileStream(fn, fmOpenRead);
    FS->Read(Stan->EnergStanLamps, sizeof(TEnergStanLamps));
    delete FS;
    bool ex;
    for (int j = 0; j < Stan->POLE[WAYS]->GetArraySize(); j++) {
        eo = dynamic_cast<TE_OBJ *>(Stan->POLE[WAYS]->GetObjPtr(j));
        if (eo == NULL) continue;
        ex = false;
        for (int cnt = 0; cnt < _MaxLampsInPacket; cnt++) {
            if (Stan->EnergStanLamps->Lamps[cnt].ObjID != eo->GetID())continue;
            memcpy(&eo->KeySost_current, &Stan->EnergStanLamps->Lamps[cnt].KeySost, sizeof(TE_KeySost));
            ex = true;
            break;
            //lmp->MyStat2=lmp->LS->__MyStat2;
            //memset(&Stan->EnergStanLamps->Lamps[cnt].Reserv,0,sizeof(Stan->EnergStanLamps->Lamps[cnt].Reserv));
        }
        if (!ex)
            memcpy(&eo->KeySost_current, &eo->KeySost_default, sizeof(TE_KeySost));

    }


}

//=============================================================================

//int   _E_def_WK[2]={32,16};
int   _E_def_FontsSzLmp[2] = {18, 14};

TE_OBJ::TE_OBJ()
        : TLED()
{
    //ENERG=2;
    type_obj = eng_key;
    type_tu = eng_tu_astmu;
    memset(tun_in_csv, 0, sizeof(tun_in_csv));
    TextAllign = 0;
    memset(&KeySost_default, 0, sizeof(KeySost_default));
    memset(&KeySost_current, 0, sizeof(KeySost_current));
    Width[0] = 0; Width[1] = 0;
    Height[0] = 0; Height[1] = 0;
    bAlarmLamp = true;
    bCheck = true;
    tipVklOkc = 0;
    usedimpuls = 0;
    bTUOnlyVkl = false;
    memset(Aimp, 0, sizeof(Aimp));
    memset(fAimp, 0, sizeof(fAimp));
    memset(Wimp, 0, sizeof(Wimp));
    memset(fWimp, 0, sizeof(fWimp));
    TO = 0;
    impulsTU=0;
    stTI_1.clear();
    stTI_2.clear();
    stTI_3.clear();
}



static String _E_OBJPropName[] = {
    "��type_obj" ,
    "��type_tu" ,
    "��FullName" ,
    "FParentName" ,
    "��key_onoff" ,
    "��podlojka"  ,
    "��zemlya" ,
    "��plakat",
    "�����������",
    "����������������"  ,
    "��TypKp"           ,
    "��NKp"             ,
    "��NGr"             ,
    "��NOb"             ,
    "�������������"     ,
    "����"    ,
    "����������",
    "��TI_1",
    "��TI_2",
    "��TI_3"

};


void TE_OBJ::GetPropMap(TPropMap &m)
{
    TLED::GetPropMap(m);


    int i = 0;
    m.put(_E_OBJPropName[ i++], type_obj);
    m.put(_E_OBJPropName[ i++], type_tu);
    m.put(_E_OBJPropName[ i++], FullName.c_str());
    m.put(_E_OBJPropName[ i++], FParentName.c_str());

    m.put(_E_OBJPropName[ i++], KeySost_default.onoff_ok     , 0);
    m.put(_E_OBJPropName[ i++], KeySost_default.podlojka     , 0);
    m.put(_E_OBJPropName[ i++], KeySost_default.zemlya       , 0);
    m.put(_E_OBJPropName[ i++], KeySost_default.plakat       , 0);
    m.put(_E_OBJPropName[ i++], tipVklOkc         , 0);
    m.put(_E_OBJPropName[ i++], usedimpuls        , 0);

    m.put(_E_OBJPropName[ i++],              TypKp, 0);
    m.put(_E_OBJPropName[ i++],                NKp, 0);
    m.put(_E_OBJPropName[ i++],                NGr, 0);
    m.put(_E_OBJPropName[ i++],                NOb, 0);
    m.put(_E_OBJPropName[ i++],                bTUOnlyVkl, 0);
    m.put(_E_OBJPropName[ i++],                TO, 0);
    m.putEx(_E_OBJPropName[ i++], OldImpToNewStr(impulsTU  , this), GetRealImp(impulsTU), OldImpToNewStr(0  , this));
    m.put(_E_OBJPropName[ i++], stTI_1.c_str());
    m.put(_E_OBJPropName[ i++], stTI_2.c_str());
    m.put(_E_OBJPropName[ i++], stTI_3.c_str());

    std::string PropName;
    char ss[4];

    for (int i = 0; i < 10; i++) {
        PropName = "��tun_in_csv";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        //if ((tun_in_csv[i]!=0)||(MOD==ED))
        m.put(PropName.c_str(), tun_in_csv[i], 0);
    }

    for (int i = 0; i < MaxAimp; i++) {
        PropName = "���������";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        //if ((Aimp[i]!=0)||(MOD==ED))
        m.putEx(PropName.c_str(), OldImpToNewStr(Aimp[i]  , this), GetRealImp(Aimp[i]), OldImpToNewStr(0  , this));
    }
    for (int i = 0; i < MaxWimp; i++) {
        PropName = "���������";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        //if ((Wimp[i]!=0)||(MOD==ED))
        m.putEx(PropName.c_str(), OldImpToNewStr(Wimp[i]  , this), GetRealImp(Wimp[i]), OldImpToNewStr(0  , this));
    }






}
void TE_OBJ::SetPropMap(TPropMap &m)
{

    TLED::SetPropMap(m);

    int i = 0;
    type_obj = (TE_type_obj)     m.geti(_E_OBJPropName[ i++]);
    type_tu = (TE_type_tu)     m.geti(_E_OBJPropName[ i++]);
    FullName =                  m.get(_E_OBJPropName[ i++]).c_str();
    FParentName =                  m.get(_E_OBJPropName[ i++]).c_str();
    //for (int ii=0;ii<5;ii++)
    //tun_in_csv[ii]=            m.geti(_E_OBJPropName[ i++]);
    int kk =                    m.geti(_E_OBJPropName[ i++]);
    KeySost_default.onoff_ok = kk;
    KeySost_default.podlojka =  m.geti(_E_OBJPropName[ i++]);
    KeySost_default.zemlya =    m.geti(_E_OBJPropName[ i++]);
    KeySost_default.plakat =    m.geti(_E_OBJPropName[ i++]);

    KeySost_current = KeySost_default;

    tipVklOkc =                 m.geti(_E_OBJPropName[ i++]);
    usedimpuls =                 m.geti(_E_OBJPropName[ i++]);

    TypKp                       = m.geti(_E_OBJPropName[ i++]);
    NKp                         = m.geti(_E_OBJPropName[ i++]);
    NGr                         = m.geti(_E_OBJPropName[ i++]);
    NOb                         = m.geti(_E_OBJPropName[ i++]);
    bTUOnlyVkl                  = m.geti(_E_OBJPropName[ i++]);
    TO                          = m.geti(_E_OBJPropName[ i++]);
    impulsTU  = NewStrToOldImp(m.get(_E_OBJPropName[ i++]).c_str());

    stTI_1 =                  m.get(_E_OBJPropName[ i++]).c_str();
    stTI_2 =                  m.get(_E_OBJPropName[ i++]).c_str();
    stTI_3 =                  m.get(_E_OBJPropName[ i++]).c_str();

    std::string PropName;
    char ss[4];

    for (int i = 0; i < 10; i++) {
        PropName = "��tun_in_csv";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        tun_in_csv[i] =            m.geti(PropName.c_str());
    }
    for (int i = 0; i < MaxAimp; i++) {
        PropName = "���������";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        Aimp[i]   = NewStrToOldImp(m.get(PropName.c_str()).c_str());
    }
    for (int i = 0; i < MaxWimp; i++) {
        PropName = "���������";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        Wimp[i]   = NewStrToOldImp(m.get(PropName.c_str()).c_str());
    }





}


TYP  TE_OBJ::GetType()
{
    return E_OBJ;
};
void TE_OBJ::UpdateState()
{
    //

    Strel::UpdateState();

    fAimp0 = 0;
    if (type_obj == eng_lmp) {
        int st1 = fimpuls_busi;
        int st2 = fimpuls_plus;
        int st3 = fimpuls_mnus;
        int st4 = fimpuls_kzm;

        if (masy < 0) {
            if ((st1 == 33) || (st2 == 33) || (st3 == 33) || (st4 == 33)) {
                clrblmp = BIRUZOVIJ; clrplmp = FON1;
            } else if (st1 == 1) {
                clrblmp = -masy; clrplmp = C_D;
            } else {
                clrblmp = FON; if (CurrentPicture == LT) clrplmp = C_D; else clrplmp = FON1;
            }

        } else {
            int setc = st1 * 8 + st2 * 4 + st3 * 2 + st4;
            int TypeLamp = ((masy < MaxLampType) && (masy >= 0)) ? masy : 0;

            if ((st1 == 33) || (st2 == 33) || (st3 == 33) || (st4 == 33)) clrblmp = BIRUZOVIJ; else
                clrblmp = wc_GetColor(TypeLamp, setc);
            clrplmp = FON1;
            if (tun_in_csv[0] + tun_in_csv[1] + tun_in_csv[2] + tun_in_csv[3] + tun_in_csv[4] + tun_in_csv[5] + tun_in_csv[6] + tun_in_csv[7] + tun_in_csv[8] + tun_in_csv[9] != 0) clrplmp = C_D;
            if ((st1 == 1) || (st2 == 1) || (st3 == 1) || (st4 == 1) || (CurrentPicture == LT)) clrplmp = C_D;
            // ���� �������� ���� ����������� ������ ! (��� ����� '�����������' ?)

        }
        if (clrplmp == clrblmp)clrplmp = clrblmp + 1;
        if (IsClrMig(clrblmp)) StateChanged = true;
    } else {
        for (int i = 0; i < MaxAimp; i++) {
            fAimp[i] = f(Aimp[i]);
            if (fAimp[i] > fAimp0) fAimp0 = fAimp[i];
        }
        for (int i = 0; i < MaxWimp; i++)
            fWimp[i] = f(Wimp[i]);
    }

}

static int UprKlPictNumber0[4] = {
//     N          ����    ����
    2  ,  //   0       0    ����.����  |
    5  ,  //   0       1    ���.����  |
    6  ,  //   1       0    ����.����  |
    1     //   1       1    ���.����   |
};

static int UprKlPictNumber1[4] = {
//     N           ����    ����
    1  ,  //   0       0    ����.����  |
    6  ,  //   0       1    ���.����  |
    5  ,  //   1       0    ����.����  |
    2     //   1       1    ���.����   |
};


const char * GetEImageName(std::string Picture, int  onoff, int onoff_ok, int ii)
{
    static std::string res = "";
    res = "";
    if (Picture == "") return res.c_str();
    res = Picture;
    if (onoff == 0) onoff = 1; else if (onoff == 1) onoff = 0;
    int nn = onoff * 2 + onoff_ok;
    int resn;
    char ss[4];

    if (Picture == "0") {
        if (ii == 0) {
            resn = 13 + 1 - onoff_ok;
        } else if (onoff == 33) {
            if (onoff_ok == 1) resn = 9 + 0; else
                resn = 9 + 1;
        } else {
            resn = UprKlPictNumber0[nn];
        }
        itoa(resn, ss, 10);
        res = ss;
    } else if (Picture == "1") {
        if (ii == 0) {
            resn = 14 - (1 - onoff_ok);
        } else if (onoff == 33) {
            if (onoff_ok == 1) resn = 9 + 1; else
                resn = 9 + 0;
        } else {
            resn = UprKlPictNumber1[nn];
        }

        itoa(resn, ss, 10);
        res = ss;

    } else {
        char ch1[3];
        char ch2[3];
        itoa(onoff, ch1, 10);
        itoa(onoff_ok, ch2, 10);
        if (ii == 30) res = Picture + "_N_N"; else
            res = Picture + '_' + ch1 + '_' + ch2;
    }
    return res.c_str();
}
static int cZ[4] = { TXT,  C_D, C_D, TXT  };
int ShowTextMode = 0;
void SetGridAlignXY(int GridAllign, int &x, int &y, int WP, int HP);
void SetTextAlignXY(int tp, int &tx, int &ty, int x, int y, int WP, int HP, TSize sz);
//const char * GetImageName(std::string Picture, int  PictureState);
static int wwhh_podl[2] = {6, 4};  //LT BG
void TE_OBJ::Show()
{
    TE_KeySost *KeySost = &KeySost_current;
    txtclr = C_D;
    if (MOD == ED) {
        KeySost = &KeySost_default;
        // ������� �� ����!
        //if (impuls_busi==0) fimpuls_busi=33; else fimpuls_busi=0;
        clrplmp = FON1;
        clrblmp = FON;
        fimpuls_busi = KeySost_default.onoff_ok;


    }

    if (type_obj == eng_lmp) {
        if (impuls_busi == 0) {
            clrplmp = FON - 1;
            clrblmp = FON;
        }
    }

    xx = X + _X_;
    yy = Y + _Y_;
    int _xx, _yy, _hh, _ww;
    RECT Rect;
    if (bUseGrid) {
        xx = X * MUL_X + _X_;
        yy = Y * MUL_Y + _Y_;

    }


    font = Prz[1];//Prz[1] ? Prz[1] : 10u;
    font_size = Prz[0] ? (BYTE)(Prz[0]) : 0;
    if (CurrentPicture == BG) font_size = Prz[2] ? (BYTE)(Prz[2]) : 0;
    if (font_size == 0) {
        if (type_obj == eng_lmp)
            font_size =    _E_def_FontsSzLmp[CurrentPicture]; else
            font_size = AO->_E_def_FontsSz[CurrentPicture];

    }
    // �����
    if (TextStr != "") {
        _SetText(font, CENTER_TEXT , CENTER_TEXT);
        _SetTextSize(font_size);
        sz.cx = textwidth(TextStr.c_str());
        sz.cy = textheight(TextStr.c_str());
    } else {
        sz.cx = 0;
        sz.cy = 0;
    }


    ww = Width[CurrentPicture];
    hh = Height[CurrentPicture];
    if ((ww == 0) && (hh == 0)) {
        ww = AO->_E_def_WK[CurrentPicture];
        hh = AO->_E_def_WK[CurrentPicture];
    }
    if (type_obj == eng_lmp) {
        ww = (masx2 + 1) * MUL_X;
        hh = sz.cy;
    }

    SetGridAlignXY(GridAllign, xx, yy, ww, hh);

    // ��������
    // ���� ���� �������������� �� ������� ��������������
    if (KeySost->zemlya + KeySost->plakat > 0) {
        /*_xx=xx+ww/2;_yy=yy+hh/2;_ww=ww+ww/2;_hh=hh+hh/2;
        if (_ww %2 !=0)_ww++;
        if (_hh %2 !=0)_hh++;
        SetGridAlignXY(0, _xx, _yy, _ww, _hh);
        Rect.left=_xx;Rect.top=_yy;Rect.right=_xx+_ww;Rect.bottom=_yy+_hh;
        */

        int w = ww * 0.4;
        int ddy = (1.*1 / 8 * (ww + w * 2));
        Rect.left = xx - w; Rect.top = yy - w - ddy; Rect.right = xx + ww + w; Rect.bottom = yy + ww + w - ddy;
        drawemf(&Rect, "41");
    }

    if (KeySost->podlojka > 0) {
        //_xx=xx+ww/2;_yy=yy+hh/2;_ww=ww+ww/4;_hh=hh+hh/4;
        int dd = wwhh_podl[CurrentPicture];
        Rect.left = xx - dd; Rect.top = yy - dd; Rect.right = xx + ww + dd; Rect.bottom = yy + hh + dd;

        //if (_ww %2 !=1)_ww++;
        //if (_hh %2 !=1)_hh++;
        //SetGridAlignXY(0, _xx, _yy, _ww, _hh);
        //Rect.left=_xx;Rect.top=_yy;Rect.right=_xx+_ww;Rect.bottom=_yy+_hh;
        char ss[4];
        itoa(30 + KeySost->podlojka, ss, 10);
        drawemf(&Rect, ss);
    }


    // ��� ������
    if (type_obj == eng_key) {
        if (tipVklOkc) {
            if (MOD != ED) {
                // ������������ � ����������
                if (impuls_busi < 0) {
                    if ((fimpuls_busi == 1) && (fimpuls_plus == 0)) fimpuls_plus = 1; else if ((fimpuls_busi == 0) && (fimpuls_plus == 1)) fimpuls_plus = 1; else if ((fimpuls_busi == 0) && (fimpuls_plus == 0)) fimpuls_plus = 0; else if ((fimpuls_busi == 1) && (fimpuls_plus == 1)) fimpuls_plus = 0;
                } else {
                    if ((fimpuls_busi == 0) && (fimpuls_plus == 0)) fimpuls_plus = 1; else if ((fimpuls_busi == 1) && (fimpuls_plus == 1)) fimpuls_plus = 1; else if ((fimpuls_busi == 1) && (fimpuls_plus == 0)) fimpuls_plus = 0; else if ((fimpuls_busi == 0) && (fimpuls_plus == 1)) fimpuls_plus = 0;
                }
            }
        }
        // ���
        if (/*(fAimp0==1)||*/(fimpuls_plus == 1) || ((MOD == ED) && (impuls_plus != 0))) {
            txtclr = 12;
            _xx = xx + ww / 2; _yy = yy + hh / 2; _ww = ww + ww / 2; _hh = hh + hh / 2;
            if (ww % 2 != 0)ww++;
            if (hh % 2 != 0)hh++;
            SetGridAlignXY(0, _xx, _yy, _ww, _hh);
            Rect.left = _xx; Rect.top = _yy; Rect.right = _xx + _ww; Rect.bottom = _yy + _hh;
            drawemf(&Rect, "ENG_LMP_ERROR", CommonAnimationStep % 4);

        }
        // ��
        if (fimpuls_mnus == 1) {
            /*_xx=xx+ww/2;_yy=yy+hh/2;_ww=ww+ww/3;_hh=hh+hh/3;

            if (ww %2 !=0)ww++;
            if (hh %2 !=0)hh++;
            SetGridAlignXY(0, _xx, _yy, _ww, _hh);
            Rect.left=_xx;Rect.top=_yy;Rect.right=_xx+_ww;Rect.bottom=_yy+_hh;
            */
            int dd = wwhh_podl[CurrentPicture];
            Rect.left = xx - dd; Rect.top = yy - dd; Rect.right = xx + ww + dd; Rect.bottom = yy + hh + dd;
            char ss[4];
            itoa(30 + 5, ss, 10);
            drawemf(&Rect, ss);

        }
        // ����� ��
        if (impuls_mu != 0) {
            if (fimpuls_mu == 0) {
                int dd = wwhh_podl[CurrentPicture];
                Rect.left = xx - dd; Rect.top = yy - dd; Rect.right = xx + ww + dd; Rect.bottom = yy + hh + dd;
                char ss[4];
                itoa(30 + 3, ss, 10);
                drawemf(&Rect, ss);
            }
        }

        const char * szimagename = GetEImageName(Picture, fimpuls_busi, KeySost->onoff_ok, impuls_busi);
        // ������� ������� ������� � ����������
        RECT Rect;
        Rect.left = xx; Rect.top = yy; Rect.right = xx + ww; Rect.bottom = yy + hh;
        //int animstep=CommonAnimationStep%4;
        if (!drawemf(&Rect, szimagename, 0)) {
            // ����� ���� � ������ ���������
            if (!drawemf(&Rect, Picture.c_str())) {
                barx(xx, yy, xx + ww, yy + hh);
                line(xx, yy, xx + ww, yy + hh);
                line(xx + ww, yy, xx, yy + hh);
            }
        }
        if (ShowTextMode != 1)
            ShowText();
        // ��
        if (fimpuls_kzm == 1) {
            txtclr = 12;
            _xx = xx + ww / 2; _yy = yy + hh / 2; _ww = ww / 2; _hh = hh / 2;
            if (ww % 2 != 0)ww++;
            if (hh % 2 != 0)hh++;
            SetGridAlignXY(0, _xx, _yy, _ww, _hh);
            Rect.left = _xx; Rect.top = _yy; Rect.right = _xx + _ww; Rect.bottom = _yy + _hh;
            drawemf(&Rect, "ENG_PK", CommonAnimationStep % 4);

        }
    }
    if (type_obj == eng_lmp) {
         if (Picture.length()>0){
            // ����� LED
            PictureState=0;//sost0;
            if (fAimp0==1) PictureState=100;//sostError;
            TLED::Show();
         }else {
            setcolor(clrplmp);
            setfillstyle(1, clrblmp);
            if (clr == FON1) setcolor(FON);

            bool bTU = false;
            if ((type_tu == eng_tu_astmu) && (tun_in_csv[0] + tun_in_csv[1] + tun_in_csv[2] + tun_in_csv[3] + tun_in_csv[4] + tun_in_csv[5] + tun_in_csv[6] + tun_in_csv[7] + tun_in_csv[8] + tun_in_csv[9]  != 0)) bTU = true;
            if ((type_tu == eng_tu_luch) && (TypKp != 0)) bTU = true;
            if (bTU) {
                //Draw_Ramka(xx+1,yy,xx+ww-0,yy+hh+4,EDGE_BUMP  );
                setcolor(C_D);
                _xx = xx; _yy = yy - 1; _ww = ww; _hh = hh + 3;
                SetGridAlignXY(1, _xx, _yy, _ww, _hh);
                Rect.left = _xx; Rect.top = _yy; Rect.right = _xx + _ww; Rect.bottom = _yy + _hh;
                if (masy == 0) {
                    if (fimpuls_busi == 33) drawemf(&Rect, "23"); else if (fimpuls_busi == 1) drawemf(&Rect, "22"); else
                        drawemf(&Rect, "21");
                } else {

                    TPoint TNP[4];
                    TNP[0] = TPoint(xx + 1        , yy);
                    TNP[1] = TPoint(xx + 1 + ww - 2,    yy);
                    TNP[2] = TPoint(xx + 1 + ww - 2, yy + hh + 2);
                    TNP[3] = TPoint(xx + 1, yy + hh + 2);
                    PolyColor(clrblmp, TNP, cZ, 4);
                }
            } else {
                barx(xx + 1, yy, xx + ww - 1, yy + hh + 2);
            }
            _SetText(font, CENTER_TEXT , CENTER_TEXT);
            DrawText(xx + 2, yy + 1, ww - 2, hh, (char*)TextStr.c_str());
        }
    }

    // �������������� ��� ����
    if (KeySost->zemlya + KeySost->plakat > 0) {

        if (KeySost->zemlya) {
            _xx = xx + ww; _yy = yy + hh / 2; _ww = ww; _hh = hh;
            SetGridAlignXY(1, _xx, _yy, _ww, _hh);
            Rect.left = _xx; Rect.top = _yy; Rect.right = _xx + _ww; Rect.bottom = _yy + _hh;
            drawemf(&Rect, "43");
        }
        if (KeySost->plakat) {
            _xx = xx + ww; _yy = yy + hh / 2; _ww = ww; _hh = hh;
            SetGridAlignXY(7, _xx, _yy, _ww, _hh);
            Rect.left = _xx; Rect.top = _yy; Rect.right = _xx + _ww; Rect.bottom = _yy + _hh;
            drawemf(&Rect, "42");
        }
    }


    _SetTextSize(1);
    _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);

}

void TE_OBJ::ShowText()
{
    if (type_obj == eng_key) {
        if (TextStr != "") {
            _SetText(font, CENTER_TEXT , CENTER_TEXT);
            _SetTextSize(font_size);
            int wwt=ww;int hht=hh;int xxt=xx;int yyt=yy;
            if (KeySost_current.podlojka > 0) {
               int dd = wwhh_podl[CurrentPicture];
               xxt = xx - dd; yyt = yy - dd; wwt = ww + dd*2; hht = hh + dd*2;
            }
            tx = xx + wwt / 2; ty = yy + hht / 2;

            SetTextAlignXY(TextAllign, tx, ty, xxt, yyt, wwt, hht, sz);

            //setcolor(FON);
            //setfillstyle(1,FON);
            //barx(tx+1,ty,tx+sz.cx-2,ty+sz.cy);
            // _SetText(23,LEFT_TEXT , TOP_TEXT);
            //OutTextXY(tx,ty,(char*)TextStr.c_str());
            //OutTextXY(tx+1,ty+1,(char*)TextStr.c_str());

            setcolor(txtclr);
            setfillstyle(1, FON);
            _SetText(font, LEFT_TEXT , TOP_TEXT);
            OutTextXY(tx, ty, (char*)TextStr.c_str());
            _SetTextSize(1);
            _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);

        }
    }
}

