//---------------------------------------------------------------------------

#ifndef EnergUnitH
#define EnergUnitH
//---------------------------------------------------------------------------
#include "ACom_T.h"
#include "Lamps.h"
#include "LampExtDraw.h"
#include<pshpack1.h>

struct TE_KeySost {
    unsigned onoff_ok: 1;
    unsigned podlojka: 3;
    unsigned zemlya: 1;
    unsigned plakat: 1;
    unsigned zapas: 2;
};

struct TEnergLampData {
    unsigned __int16 ObjID;
    TE_KeySost KeySost;
};
const _MaxLampsInPacket = 490 / sizeof(TEnergLampData);
struct TEnergStanLamps {
    TEnergLampData Lamps[_MaxLampsInPacket];
};
#include<poppack.h>

TEnergLampData * __fastcall GetEnergLampData(TEnergStanLamps * EnergStanLamps, unsigned __int16 ObjID);
int __fastcall SetEnergLampData(TEnergStanLamps * EnergStanLamps, unsigned __int16 ObjID, TEnergLampData * EnergLampData);
void __fastcall LoadTEnergStanLamps(char * fn, TEnergStanLamps * EnergStanLamps);

void __fastcall LampsLSFromNet(Station *Stan);

void __fastcall LoadLampsLS(Station *Stan);
void __fastcall SaveLampsLS(Station *Stan);

enum TE_type_obj {eng_key = 1, eng_lmp = 2};
enum TE_type_tu  {eng_tu_astmu = 0, eng_tu_luch = 1};

const MaxWimp = 30;
const MaxAimp = 30;

class TE_OBJ : public TLED
{
protected:
    int clrplmp, clrblmp;
    int fAimp[MaxAimp];
    int fAimp0;
    int fWimp[MaxAimp];
    int txtclr;
    int xx, yy, ww, hh, tx, ty;
    unsigned int font;
    unsigned int font_size;
    TSize sz;

public:

    TE_type_obj type_obj;
    TE_type_tu  type_tu;
    std::string FullName;
    std::string FParentName;
    TE_KeySost KeySost_default;
    TE_KeySost KeySost_current;
    byte TypKp;
    byte NKp;
    byte NGr;
    byte NOb;
    bool bTUOnlyVkl;
    int tun_in_csv[10];
    int tipVklOkc;
    int usedimpuls;
    int TO;

    int Aimp[MaxAimp];
    int Wimp[MaxWimp];

    int impulsTU;


    TE_OBJ();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);
    int  GetSubType() {
        return type_obj;
    };


    TYP  GetType();
    virtual void UpdateState();
    virtual void Show();
    void ShowText();
};









#endif
