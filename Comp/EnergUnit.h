#ifndef EnergUnitH
#define EnergUnitH

//---------------------------------------------------------------------------
#include "ACom_T.h"
#include "Lamps.h"
#include "LampExtDraw.h"


#pragma pack(push,1)

struct TE_KeySost {
    uint8 onoff_ok: 1;
    uint8 podlojka: 3;
    uint8 zemlya: 1;
    uint8 plakat: 1;
    uint8 zapas: 2;
};

struct TEnergLampData {
    uint16 ObjID;
    TE_KeySost KeySost;
};

const int _MaxLampsInPacket = 490 / sizeof(TEnergLampData);
struct TEnergStanLamps {
    TEnergLampData Lamps[_MaxLampsInPacket];
};

#pragma pack(pop)




TEnergLampData * GetEnergLampData(TEnergStanLamps * EnergStanLamps, uint16 ObjID);
int SetEnergLampData(TEnergStanLamps * EnergStanLamps, uint16 ObjID, TEnergLampData * EnergLampData);
void LoadTEnergStanLamps(char * fn, TEnergStanLamps * EnergStanLamps);

void LampsLSFromNet(Station *Stan);

void LoadLampsLS(Station *Stan);
void SaveLampsLS(Station *Stan);

enum TE_type_obj {eng_key = 1, eng_lmp = 2};
enum TE_type_tu  {eng_tu_astmu = 0, eng_tu_luch = 1};

const int MaxWimp = 30;
const int MaxAimp = 30;

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
    uint8 TypKp;
    uint8 NKp;
    uint8 NGr;
    uint8 NOb;
    bool bTUOnlyVkl;
    int tun_in_csv[10];
    int tipVklOkc;
    int usedimpuls;
    int TO;

    int Aimp[MaxAimp];
    int Wimp[MaxWimp];

    int impulsTU;

    std::string stTI_1;
    std::string stTI_2;
    std::string stTI_3;


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
