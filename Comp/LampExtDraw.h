//---------------------------------------------------------------------------

#ifndef LampExtDrawH
#define LampExtDrawH
//---------------------------------------------------------------------------
#include "comp.h"
#include "elem.h"
#include "strel.h"
#include "Lamps.h"
#include "ACom_V.h"
#include <string>



const _sizeLEDstr = sizeof(MEM.DMD);

//---------------------------------------------------------------------------
// �������� ��� �������� ������ �� ���
#include<pshpack1.h>
struct TLED_EXTDataObj {
    unsigned int ID_OBJ;
    char         STA_FN[13];
    int          imps[6];
    int          Type;
    int          Tag;
    char *PropStr;
    // ������ ������� ���������� � ��������
    int  PersistInt;
    int  PersistVoid;
};


struct TLED_EXTData {
    AComp* pElement;
    // ������������
    // �������
    void* hdc;
    int X;
    int Y;
    int Width;
    int Height;
    int YchStan;

    char *Picture;     // Picture
    int  PictureState;   // State -  ������ ������� ��
    bool bDefaultState;  // �������� DEFAULT_State ���� ��� Picture_State
    int  PictureAnimateStep;    // Picture_State_PictureAnimateStep

    // ���������� ������ ������� ��� ������� ���������
    TLED_EXTDataObj ObjData;



};

#include<poppack.h>
//---------------------------------------------------------------------------


typedef int (*T_LED_EXT_Func)(TLED_EXTData*);
void _ALIB_ Set_LED_EXT_Func(T_LED_EXT_Func ALED_EXT);


class TLED : public SuperLamp2
{
protected:

    int SetLED_EXT(int xx, int yy, int ww, int hh);

public:
    TLED();
    unsigned int Width[2];
    unsigned int Height[2];

    signed   char nomer;
    unsigned __int8 GridAllign;
    unsigned __int8 TextAllign;
    bool bUseGrid;

    std::string ExtPropStr;
    std::string TextStr;
    std::string TagStr;
    std::string Picture;
    int  PictureState;   // State -  ������ ������� ��

    int  PersistInt;
    int  PersistVoid;

    virtual void Set();
    virtual void Get();
    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);


    TYP  GetType();
    UNIT GetUnit();
    virtual void UpdateState();
    virtual void Show();
};

class TLED30 : public TLED
{
protected:

    int fimp[30];
public:
    int imp[30];
    TLED30();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);


    TYP  GetType();
    virtual void UpdateState();
    virtual void Show();
};
#endif
