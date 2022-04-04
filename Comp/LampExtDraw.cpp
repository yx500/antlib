#include "aheaders_cpp.h"

#include "LampExtDraw.h"

#include "APch.h"
#include "Stan.h"
#include "Strel.h"
#include "Scrin.h"
#include "col.h"
#include "F.h"

#include "propmap.h"
#include "uImgContainer.h"
#include "uEXD.h"
#include "Impuls.h"

#include "winbgi_vcl.h"
//#include "bgi.h"

//---------------------------------------------------------------------------




const int sost0 = 0;
const int sostOk = 1;
const int sostWait = 2;
const int sostError = 100;
const int sostNoNet = -100;
const int sostNotAccept = -101;


static T_LED_EXT_Func LED_EXT_Func = NULL;
static TLED_EXTData LEDEXD;

void Set_LED_EXT_Func(T_LED_EXT_Func ALED_EXT)
{
    LED_EXT_Func = ALED_EXT;
}


TLED::TLED(): SuperLamp2()
{
    ExtPropStr = "";
    TextStr = "";
    TagStr = "";
    Width[0] = 20; Width[1] = 20;
    Height[0] = 20; Height[1] = 20;
    PersistInt = 0;
    PersistVoid = 0;
    bUseGrid = true;
    PictureState = 0;
    TextAllign = 0;
    GridAllign = 0;
}

//TCanvas* __fastcall DC(void);
int TLED::SetLED_EXT(int xx, int yy, int ww, int hh)
{
    memset(&LEDEXD, 0, sizeof(LEDEXD));
    if (BgiCanvas() != NULL)
        LEDEXD.hdc = BgiCanvas()->Handle;

    LEDEXD.pElement = this;
    // ãðàôèêà
    LEDEXD.X = xx;
    LEDEXD.Y = yy;
    LEDEXD.Width = ww;
    LEDEXD.Height = hh;
    LEDEXD.YchStan = CurrentPicture;

    LEDEXD.Picture = (char*)Picture.c_str();
    LEDEXD.PictureState = 0;
    LEDEXD.bDefaultState = false;
    LEDEXD.PictureAnimateStep = 0;  // Picture_State_PictureAnimateStep

    LEDEXD.ObjData.imps[0] = this->impuls_busi;
    LEDEXD.ObjData.imps[1] = this->impuls_plus;
    LEDEXD.ObjData.imps[2] = this->impuls_mnus;
    LEDEXD.ObjData.imps[3] = this->impuls_kzm;
    LEDEXD.ObjData.imps[4] = this->impuls_mu;
    LEDEXD.ObjData.imps[5] = this->impuls_kmu;

    // ñîáñòâåííî äàííûå Îáüåêòà äëÿ âíåøíåé îáðàáîòêè
    LEDEXD.ObjData.ID_OBJ = GetID();
    LEDEXD.ObjData.Type = GetType();
    LEDEXD.ObjData.Tag = Tag;
    strncpy(LEDEXD.ObjData.STA_FN, Stan()->Dat->filename, sizeof(LEDEXD.ObjData.STA_FN));

    LEDEXD.ObjData.PropStr = (char*)ExtPropStr.c_str();

    LEDEXD.ObjData.PersistInt = PersistInt;
    LEDEXD.ObjData.PersistVoid = PersistVoid;

    return LEDEXD.hdc != 0;
}

void SetGridAlignXY(int GridAllign, int &x, int &y, int WP, int HP);
void SetTextAlignXY(int tp, int &tx, int &ty, int x, int y, int WP, int HP, TSize sz);

extern void __fastcall tracecoord(int x, int y);
//static char n_str[ 256 ];



const char * GetImageName(std::string Picture, int  PictureState)
{
    static std::string res = "";
    res = "";
    if (Picture == "") return res.c_str();
    res = Picture;
    if (PictureState == sost0) return res.c_str();

    switch (PictureState) {
    case sostOk        : res=res+"_OK"; break;
    case sostWait         : res=res+"_WAIT"; break;
    case sostError        : res=res+"_ERROR"; break;
    case sostNoNet      : res=res+"_NONET"; break;
    case sostNotAccept      : res=res+"_NOTACCEPT"; break;
    default        : {
        char ss[32];
        itoa(PictureState, ss, 10);
        res = res + "_" + ss;
    }; break;
    }
    return res.c_str();
}
void  TLED::Show()
{

    int xx = X + _X_;
    int yy = Y + _Y_;
    if (bUseGrid) {
        xx = X * MUL_X + _X_;
        yy = Y * MUL_Y + _Y_;

    }

    int ww = Width[CurrentPicture];
    int hh = Height[CurrentPicture];
    if (ww==0) ww=mas*MUL_X;
    if (hh==0) hh=masy*MUL_Y;

    SetGridAlignXY(GridAllign, xx, yy, ww, hh);

    if (LED_EXT_Func == NULL) {
        // ðèñóåì ñàìè
        //PictureState=EXD....
        const char * szimagename = GetImageName(Picture, PictureState);
        // ñíà÷àëà ïðîáóåì ãîòîâóþ ñ ñîñòîÿíèåì
        RECT Rect;
        Rect.left = xx; Rect.top = yy; Rect.right = xx + ww; Rect.bottom = yy + hh;
        int animstep = CommonAnimationStep % 4;
        if (!drawemf(&Rect, szimagename, animstep)) {
            // ðèñóì ñàìó è ñâåðõó ñîñòîÿíèå
            if (!drawemf(&Rect, Picture.c_str())) {
                barx(xx, yy, xx + ww, yy + hh);
                line(xx, yy, xx + ww, yy + hh);
                line(xx + ww, yy, xx, yy + hh);
            }
            szimagename = GetImageName("DEFAULT", PictureState);
            drawemf(&Rect, szimagename, animstep);
        }
    } else {
        tracecoord(xx, yy);
        tracecoord(xx + ww, yy);
        tracecoord(xx, yy + hh);
        tracecoord(xx + ww, yy + hh);
        if (SetLED_EXT(xx, yy, ww, hh)) {
            LED_EXT_Func(&LEDEXD);
            this->PersistInt = LEDEXD.ObjData.PersistInt;
            this->PersistVoid = LEDEXD.ObjData.PersistVoid;
        }
    }
    // òåêñò
    if (TextStr != "") {
        TSize sz;
        unsigned int font = Prz[1] ? Prz[1] : 10u;
        unsigned int font_size = Prz[0] ? (uint8)(Prz[0]) : 10u;
        if (CurrentPicture == BG)
            font_size = Prz[2] ? (uint8)(Prz[2]) : 10u;
        _SetText(font, LEFT_TEXT , TOP_TEXT);
        _SetTextSize(font_size);

        //OemToAnsi( TextStr.c_str(),n_str );

        sz.cx = textwidth(TextStr.c_str());
        sz.cy = textheight(TextStr.c_str());

        int tx, ty;
        SetTextAlignXY(TextAllign, tx, ty, xx, yy, ww, hh, sz);
        tracecoord(tx, ty);
        tracecoord(tx + sz.cx, ty);
        tracecoord(tx, ty + sz.cy);
        tracecoord(tx + sz.cx, ty + sz.cy);
        setcolor(C_D);
        setfillstyle(1, FON);
        OutTextXY(tx, ty, (char*)TextStr.c_str());
        _SetTextSize(1);
        _SetText(F_DEFAULT, LEFT_TEXT, BOTTOM_TEXT);

    }
}

TYP  TLED::GetType()
{
    return LED;
};
UNIT TLED::GetUnit()
{
    return WAYS;
};

void TLED:: Set()
{
    SuperLamp2::Set();

    //Width[0]=mas;Width[1]=masx2;
    //Height[0]=masy;Height[1]=nomer;


    //nomer = MEM.Nomer;
    //GridAllign= MEM.GID;
    //ExtPropStr.assign(MEM.DMD);
    //strncpy(szExtPropStr,MEM.DMD,sizeof(szExtPropStr)-1);

};


static String _LEDPropName[] = {
    "öôPictX" ,   // 0
    "öôPictY" ,   // 1
    "öôPictWidthStan" ,   // 2
    "öôPictHeightStan",   // 3
    "öôPictWidthYch"  ,   // 4
    "öôPictHeightYch" ,   // 5
    "öôPictGridAllign",   // 6
    "ëãGrid",             // 7
    "ñìPict",             // 8
    "öôTextAllign",       // 9
    "ñìText",             // 10
    "ñìPropStr"           // 11
};


void TLED::SetPropMap(TPropMap &m)
{
    SuperLamp2::SetPropMap(m);

    X                  = m.geti(_LEDPropName[ 0]); //X
    Y                  = m.geti(_LEDPropName[ 1]); //Y
    Width[0]           = m.geti(_LEDPropName[ 2]); //mas
    Height[0]          = m.geti(_LEDPropName[ 3]); //masy
    Width[1]           = m.geti(_LEDPropName[ 4]); //masx2
    Height[1]          = m.geti(_LEDPropName[ 5]); //nomer

    GridAllign         = m.geti(_LEDPropName[ 6]);
    bUseGrid           = m.geti(_LEDPropName[ 7]);
    Picture            = m.get(_LEDPropName[8]).c_str();

    TextAllign         = m.geti(_LEDPropName[ 9]);

    TextStr            = m.get(_LEDPropName[10]).c_str();
    ExtPropStr         = m.get(_LEDPropName[11]).c_str();
    if (strlen(name) == 0)
        strncpy(name, TextStr.c_str(), sizeof(name));




}

void TLED::GetPropMap(TPropMap &m)
{
    SuperLamp2::GetPropMap(m);

    m.put(_LEDPropName[ 0], X          , 0);
    m.put(_LEDPropName[ 1], Y          , 0);
    m.put(_LEDPropName[ 2], Width[0]   , 0);
    m.put(_LEDPropName[ 3], Height[0]  , 0);
    m.put(_LEDPropName[ 4], Width[1]   , 0);
    m.put(_LEDPropName[ 5], Height[1]  , 0);
    m.put(_LEDPropName[ 6], GridAllign , 0);
    m.put(_LEDPropName[ 7], bUseGrid   , 0);
    m.put(_LEDPropName[ 8], Picture.c_str());
    m.put(_LEDPropName[ 9], TextAllign , 0);

    m.put(_LEDPropName[10], TextStr.c_str());
    m.put(_LEDPropName[11], ExtPropStr.c_str(), "");
}


void TLED::Get()
{
    //mas=Width[0];masx2=Width[1];
    //masy=Height[0];nomer=Height[1];

    SuperLamp2::Get();
    //MEM.Nomer= nomer ;
    //MEM.GID  = GridAllign;

    //strncpy(MEM.DMD,ExtPropStr.c_str(),sizeof(MEM.DMD)-1);

};

void TLED::UpdateState()
{
    int rPictureState = PictureState;

    TElemCheckState * EI = EXD.EI_GetEI(Stan()->Dat->filename, GetID());
    if (EI != NULL)
        PictureState = EI->state; else
        PictureState = 0;

    StateChanged = rPictureState != PictureState;
}

//=============================================================================

TLED30::TLED30()
{
    memset(imp, 0, sizeof(imp));
    memset(fimp, 0, sizeof(fimp));
    bAlarmLamp = true;
    bCheck = true;
}


void TLED30::GetPropMap(TPropMap &m)
{
    std::string PropName;
    TLED::GetPropMap(m);
    char ss[32];
    for (int i = 1; i < 30; i++) {
        PropName = "òñÑèãíàë";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        //if ((MOD==ED)||(imp[i]!=0))
        m.putEx(PropName.c_str(), OldImpToNewStr(imp[i]  , this), GetRealImp(imp[i]), OldImpToNewStr(0, this));
    }


}
void TLED30::SetPropMap(TPropMap &m)
{
    std::string PropName;
    TLED::SetPropMap(m);
    char ss[32];
    imp[0] = impuls_busi;
    for (int i = 1; i < 30; i++) {

        PropName = "òñÑèãíàë";
        itoa(i + 1, ss, 10);
        PropName = PropName + ss;
        imp[i]   = NewStrToOldImp(m.get(PropName.c_str()).c_str());
    }

}


TYP  TLED30::GetType()
{
    return LED30;
};
void TLED30::UpdateState()
{
    int rPictureState = PictureState;

    PictureState = sostOk;
    for (int i = 0; i < 30; i++) {
        fimp[i] = f(imp[i]);
        if (fimp[i] == 33) {
            PictureState = sostNoNet; break;
        }
    }
    if (PictureState != sostNoNet) {
        for (int i = 0; i < 30; i++) {
            if (fimp[i] == 1) {
                PictureState = sostError; break;
            }
        }
    }

    StateChanged = rPictureState != PictureState;

}
void TLED30::Show()
{
    if (MOD == ED) {
        int cnt = 0;
        for (int i = 0; i < 30; i++) {
            if (imp[i] != 0)cnt++;
        }
        if (cnt == 0)  PictureState = sostNotAccept;
    }
    TLED::Show();

}
