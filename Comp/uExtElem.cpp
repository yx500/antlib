//---------------------------------------------------------------------------


#include "aheaders_cpp.h"
#include "APch.h"

#include "uExtElem.h"
#include "Elem.h"
#include "Lamps.h"
#include "WinPalet.h"
#include "F.h"



//---------------------------------------------------------------------------




static TGrpahExElem GE;

//   567
//   408
//   321
void SetGridAlignXY(int GridAllign, int &x, int &y, int WP, int HP)
{
    switch (GridAllign) {
    case 0: x-=WP/2; y-=HP/2; break;
    case 1: break;
    case 2: x-=WP/2; break;
    case 3: x-=WP; break;
    case 4: x-=WP; y-=HP/2; break;
    case 5: x-=WP; y-=HP; break;
    case 6: x-=WP/2; y-=HP; break;
    case 7: y-=HP; break;
    case 8: y-=HP/2; break;
    }

}


//   627
//   143
//   508

void SetTextAlignXY(int tp, int &tx, int &ty, int x, int y, int WP, int HP, TSize sz)
{
    switch (tp) {
    case 0 :tx=x+WP/2-sz.cx/2; ty=y+HP; break;
    case 1 :tx=x-sz.cx; ty=y+HP/2-sz.cy/2; break;
    case 2 :tx=x+WP/2-sz.cx/2; ty=y-sz.cy; break;
    case 3 :tx=x+WP; ty=y+HP/2-sz.cy/2; break;
    case 4 :tx=x+WP/2-sz.cx/2; ty=y+HP/2-sz.cy/2; break;
    case 5 :tx=x-sz.cx; ty=y+HP; break;
    case 6 :tx=x-sz.cx; ty=y-sz.cy; break;
    case 7 :tx=x+WP; ty=y-sz.cy; break;
    case 8 :tx=x+WP; ty=y+HP; break;
    case 9 :tx=x+WP/2; ty=y+HP; break;
    case 10:tx=x+WP/2-sz.cx; ty=y+HP; break;
    case 11:tx=x+WP/2; ty=y-sz.cy; break;
    case 12:tx=x+WP/2; ty=y-sz.cy; break;
    }
}


void ShowPictText(int x, int y, void * AGE, char * szText, int YS)
{


    TGrpahExElem *G = (TGrpahExElem *)AGE;

    int HP = G->PictHeightStan;
    int WP = G->PictWidthStan;
    if (YS == BG) {
        HP = G->PictHeightYch;
        WP = G->PictWidthYch;
    }

    SetGridAlignXY(G->GridAllign, x, y, WP, HP);
    char ii[4];
    itoa(G->PictNumber, ii, 10);
    RECT Rect;
    Rect.left = x; Rect.top = y; Rect.right = x + WP; Rect.bottom = y + HP;
    drawemf(&Rect, ii);

    int tx = x;
    int ty = y;
    int FontN = G->TextFontNStan;
    if (YS == BG)FontN = G->TextFontNYch;
    TSize sz;
    sz.cy = 0; sz.cx = 0;
    if ((FontN > 0) && (FontN < 255)) {


        //_SetText(9,CENTER_TEXT , CENTER_TEXT);
        _SetText(9, LEFT_TEXT , TOP_TEXT);
        switch (FontN) {
        case 1: _SetTextSize(10+4);
            //Cnv->Font->Style= TFontStyles()<< fsBold;
            break;
        case 2: _SetTextSize(8+4); break;
        default: _SetTextSize(FontN);
        }
        /*if (G->TextRotate!=0){
           oldH=Cnv->Font->Handle;
           LOGFONT lf; // Windows native font structure
           ZeroMemory(&lf, sizeof(LOGFONT));
           lf.lfHeight = Cnv->Font->Height;
           lf.lfEscapement = 10 * G->TextRotate; // degrees to rotate
           lf.lfOrientation = 10 * G->TextRotate;
           lf.lfCharSet = DEFAULT_CHARSET;
           strcpy(lf.lfFaceName,Cnv->Font->Name.c_str());
           RotFont=CreateFontIndirect(&lf);
           Cnv->Font->Handle = RotFont;
        }*/
        //sz=Cnv->TextExtent(String(n_str));
        sz.cx = textwidth(szText);
        sz.cy = textheight(szText);
        int tp = G->TextPosStan;
        if (YS == BG)tp = G->TextPosYch;
        SetTextAlignXY(tp, tx, ty, x, y, WP, HP, sz);

        /*if (G->TextFontColor!=0) */setcolor(G->TextFontColor);
        if (G->TestExSet == 101) setcolor(12);

        OutTextXY(tx, ty, szText);
        //Cnv->TextOut(tx,ty,String(szText));
        _SetTextSize(1);
    }

    /*if (G->TextRotate!=0){
       if (RotFont!=NULL) DeleteObject(RotFont);
       RotFont=NULL;
       Cnv->Font->Handle =oldH;
       Cnv->Font->Style= TFontStyles();
    } */


}


void ShowPictXY(int PictNumber, int x, int y, int WP, int HP)
{
    TGrpahExElem G;
    G.Enabled = true;
    G.PictNumber = PictNumber;
    G.PictWidthStan = WP;
    G.PictHeightStan = HP;
    G.GridAllign = 1;
    ShowPictText(x, y, &G, "", LT);

}




enum TLampType {lt_rectbt1, lt_rectbt2, lt_r_kl, lt_kl};

static int UprKlPictNumber[8] = {
//     N        П   ВклП    С
    3,    // 0   0       0    вкл.прав.  -   0
    5,    // 0   0       1    выкл.непр  -   1
    7  ,  // 0   1       0    вкл.непр   -   2
    1  ,  // 0   1       1    выкл.прав. -   3
    8  ,  // 1   0       0    вкл.непр   |   4
    2  ,  // 1   0       1    выкл.прав. |   5
    4  ,  // 1   1       0    вкл.прав.  |   6
    6     // 1   1       1    выкл.непр  |   7
};





bool ExShowLamp(int x, int y, Lamp * AL, int YS)
{
    if ((AL == NULL) || (AL->GrpahExData.Enabled != 1)) return false;

    int NPict = 0;
    GE = AL->GrpahExData;
    String stName = String(AL->name);
    int H = AL->GrpahExData.PictHeightStan;
    int W = AL->GrpahExData.PictWidthStan;
    if (YS == BG) {
        H = AL->GrpahExData.PictHeightYch;
        W = AL->GrpahExData.PictWidthYch;
    }
    int xx = x;
    int yy = y;
    SetGridAlignXY(GE.GridAllign, xx, yy, W, H);
    xx = xx + W / 2;
    yy = yy + H / 2;
    int ii = AL->f(AL->impuls_busi);
    TLampType LTYP;
    //* Находим тип лампочки *
    LTYP = lt_kl;
    if (stName.Length() > 0) {
        if (stName[1] == '!') {
            stName.Delete(1, 1); LTYP = lt_r_kl;
        } else if (stName[1] == '%') {
            stName.Delete(1, 1); LTYP = lt_rectbt1;
        } else if (stName[1] == '&') {
            stName.Delete(1, 1); LTYP = lt_rectbt2;
        }
    }

    if (AL->AO->ENERG != 0) {

        switch (LTYP) {
        case lt_rectbt1: {
            //*  управляемые лампочки *
            GE.PictNumber = 21;
            if (ii == 1)GE.PictNumber = 22;
            if (ii == 33)GE.PictNumber = 23;
            //AL->GrpahExData.GridAllign=0;
            GE.TextPosStan = 4; GE.TextPosYch = 4;
            GE.TextFontColor = 1;
            ShowPictText(x, y, &GE, stName.c_str(), YS);
        } break;
        case lt_rectbt2: {
            //*  сигнальные лампочки *
            GE.TextFontColor = 9;
            if (ii == 1) {
                GE.PictNumber++;
                GE.TextFontColor = 1;
            }
            if (ii == 33) {
                GE.PictNumber += 2;
                GE.TextFontColor = 1;
            }
            ShowPictText(x, y, &GE, stName.c_str(), YS);
        } break;
        case lt_r_kl:
        case lt_kl: {
            //* Общие для ключей  *
            if (AL->LS != NULL) {
                //* подложки *
                if (AL->LS->MyStat4 > 0) {
                    GE = AL->GrpahExData;
                    GE.PictWidthYch = GE.PictWidthYch + GE.PictWidthYch / 2; if (GE.PictWidthYch % 2 != 0)GE.PictWidthYch++;
                    GE.PictHeightYch = GE.PictHeightYch + GE.PictHeightYch / 2; if (GE.PictHeightYch % 2 != 0)GE.PictHeightYch++;
                    GE.PictWidthStan = GE.PictWidthStan + GE.PictWidthStan / 2; if (GE.PictWidthStan % 2 != 0)GE.PictWidthStan++;
                    GE.PictHeightStan = GE.PictHeightStan + GE.PictHeightStan / 2; if (GE.PictHeightStan % 2 != 0)GE.PictHeightStan++;
                    GE.PictNumber = 41;
                    GE.GridAllign = 0;
                    ShowPictText(xx, yy, &GE, "", YS);
                }

                if (AL->LS->MyStat3 > 0) {
                    GE = AL->GrpahExData;
                    GE.PictWidthYch = GE.PictWidthYch + GE.PictWidthYch / 5; if (GE.PictWidthYch % 2 != 0)GE.PictWidthYch++;
                    GE.PictHeightYch = GE.PictHeightYch + GE.PictHeightYch / 5; if (GE.PictHeightYch % 2 != 0)GE.PictHeightYch++;
                    GE.PictWidthStan = GE.PictWidthStan + GE.PictWidthStan / 5; if (GE.PictWidthStan % 2 != 0)GE.PictWidthStan++;
                    GE.PictHeightStan = GE.PictHeightStan + GE.PictHeightStan / 5; if (GE.PictHeightStan % 2 != 0)GE.PictHeightStan++;
                    GE.PictNumber = 30 + AL->LS->MyStat3;
                    GE.GridAllign = 0;
                    ShowPictText(xx, yy, &GE, "", YS);
                }
                //* епотеря канала *
                if ((ii == 30) || (ii == 31)) {
                    GE = AL->GrpahExData;
                    ii = ii - 30;
                    GE.PictWidthYch = GE.PictWidthYch + GE.PictWidthYch / 5; if (GE.PictWidthYch % 2 != 0)GE.PictWidthYch++;
                    GE.PictHeightYch = GE.PictHeightYch + GE.PictHeightYch / 5; if (GE.PictHeightYch % 2 != 0)GE.PictHeightYch++;
                    GE.PictWidthStan = GE.PictWidthStan + GE.PictWidthStan / 5; if (GE.PictWidthStan % 2 != 0)GE.PictWidthStan++;
                    GE.PictHeightStan = GE.PictHeightStan + GE.PictHeightStan / 5; if (GE.PictHeightStan % 2 != 0)GE.PictHeightStan++;
                    GE.PictNumber = 36;
                    GE.GridAllign = 0;
                    ShowPictText(xx, yy, &GE, "", YS);
                }
                //* епотеря канала *
                if ((ii == 33)) {
                    ii = 30 - 30;
                    GE.PictWidthYch = GE.PictWidthYch + GE.PictWidthYch / 5; if (GE.PictWidthYch % 2 != 0)GE.PictWidthYch++;
                    GE.PictHeightYch = GE.PictHeightYch + GE.PictHeightYch / 5; if (GE.PictHeightYch % 2 != 0)GE.PictHeightYch++;
                    GE.PictWidthStan = GE.PictWidthStan + GE.PictWidthStan / 5; if (GE.PictWidthStan % 2 != 0)GE.PictWidthStan++;
                    GE.PictHeightStan = GE.PictHeightStan + GE.PictHeightStan / 5; if (GE.PictHeightStan % 2 != 0)GE.PictHeightStan++;
                    GE.PictNumber = 36;
                    //GE.GridAllign=0;
                    ShowPictText(x, y, &GE, "", YS);
                }
                int pol = AL->LS->MyStat2;
                //  Ручные ключи *
                if (LTYP == lt_r_kl) {
                    NPict = 13 + pol;
                }
                //  Управляемые ключи
                if (LTYP == lt_kl) {
                    if (AL->impuls_busi < 1000) {
                        // Не подвязанные
                        NPict = pol + 11;
                    } else if (ii == 33) {
                        NPict = pol + 9;
                    } else {
                        if (AL->AO->ENERG == 2)
                            NPict = UprKlPictNumber[pol*4+AL->LS->__MyStat5*2+1-ii]; else
                            NPict = UprKlPictNumber[pol*4+AL->LS->__MyStat5*2+ii];
                    }
                }
                GE = AL->GrpahExData;
                GE.PictNumber = NPict;
                //AL->GrpahExData.GridAllign=0;
                ShowPictText(x, y, &GE, stName.c_str(), YS);
            }//LS
        }//case
        } //switch
        //* предупреждения для всех
        if ((AL->LS != NULL) && ((AL->LS->MyStat4 == 1) || (AL->LS->MyStat4 == 3))) {
            GE = AL->GrpahExData;
            //GE.PictWidthYch=GE.PictWidthYch/2;
            //GE.PictHeightYch=GE.PictHeightYch/2;
            //GE.PictWidthStan=GE.PictWidthStan/2;
            //GE.PictHeightStan=GE.PictHeightStan/2;
            GE.PictNumber = 42;
            GE.GridAllign = 7;
            ShowPictText(xx + W / 2, yy, &GE, "", YS);
        }
        if ((AL->LS != NULL) && ((AL->LS->MyStat4 == 2) || (AL->LS->MyStat4 == 3))) {
            GE = AL->GrpahExData;
            //GE.PictWidthYch=GE.PictWidthYch/2;
            //GE.PictHeightYch=GE.PictHeightYch/2;
            //GE.PictWidthStan=GE.PictWidthStan/2;
            //GE.PictHeightStan=GE.PictHeightStan/2;
            GE.PictNumber = 43;
            GE.GridAllign = 1;
            ShowPictText(xx + W / 2, yy, &GE, "", YS);
        }
        /* TU  *
        if ((AL->LS!=NULL)&&(AL->LS->MyStat22==1)){
           GE=AL->GrpahExData;
           GE.PictWidthYch=40;
           GE.PictHeightYch=30;
           GE.PictWidthStan=60;
           GE.PictHeightStan=60;
           GE.PictNumber=101;
           int H1=AL->GrpahExData.PictHeightStan;
           int W1=AL->GrpahExData.PictWidthStan;
           if (YS==BG){
              H1=AL->GrpahExData.PictHeightYch;
              W1=AL->GrpahExData.PictWidthYch;
           }
           AL->GrpahExData.TextFontColor=1;
           ShowPictText(x+W/2+W1/2,y-H/2-H1/2,&GE,"",YS);
        }
        */
    } else {//ENERG
        //  сигнальные лампочки
        GE.TextFontColor = 9;
        if (ii == 1) {
            GE.PictNumber++;
            GE.TextFontColor = 1;
        }
        if (ii == 33) {
            GE.PictNumber += 2;
            GE.TextFontColor = 1;
        }
        ShowPictText(x, y, &GE, stName.c_str(), YS);
    }
    if (GE.TestExSet == 0) {
        // СТАНДАРТ
    } else if (GE.TestExSet == 11) {
        // ГОРКА  ЗАМЕДЛИТЕЛИ
        if (ii == 1) {
            GE.PictNumber++;
            //AL->GrpahExData.TextFontColor=1;
        }
        if (ii == 33) {
            GE.PictNumber += 3;
            //AL->GrpahExData.TextFontColor=1;
        }
        ShowPictText(x, y, &GE, stName.c_str(), YS);
    }

    return true;
}








