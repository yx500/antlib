#ifndef COMP_H
#define COMP_H

#include "pmComp.h"
#include <string>
struct TExtPriz;
struct TTrainInfo;

class VisibleArray;
class Station;
class Poligon;
class TAntOpt;

struct TACompPad
{
    int xy[8];
    char cmd[12];
    char param[12];
};

class AComp : public pmComp
{

private:
public:
    short int X;
    short int Y;
    signed char mas;
    signed char masy;
    signed char masx2;
    int iMacro;
    int clr, _clr;
    signed char pr;
    int impuls_busi;
    int fimpuls_busi;
    TExtPriz ExtPriz;
    VisibleArray *pVisibleArray;
    TAntOpt *AO;
    void *Data;
    std::string Tagstr;
    int Tag;
    uint16 ID;

    bool StateChanged;
    TRect RCT;
    TACompPad Pad[3];

    int ExtFocus; // 0 - 0, 1-Set, 2- Clear

    AComp *pNext[2][2];

    TPropMap *pmRepl;

    char name[64];

    AComp();
    virtual ~AComp();

    virtual int TstXY(int, int);

    virtual void GetNumberPosition(int &X, int &Y, int Width, int Height, int direct);

    void Clear();
    virtual void Set();
    virtual void Get();
    virtual void Show() = 0;
    virtual void ShowLayer(int Layer){};
    virtual const char *GetName();
    virtual void Go();
    virtual unsigned int GetID();
    virtual const char *GetIDObj();

    virtual void SetID(unsigned int);
    virtual TYP GetType() = 0;
    virtual int GetSubType()
    {
        return 0;
    };
    virtual UNIT GetUnit() = 0;
    char *GetText(char *txt);
    void Hide(void);
    void Move(int DeltaX, int DeltaY);
    int f(int impls);
    int GetRealImp(int impls);
    bool SetNativeImp(int RealImpls, short int &NativeImp);
    int GetNativeImp(int RealImpls);
    const char *GetImpulsName(char *PropName);
    // virtual char * GetCompInfo();

    virtual void UpdateState();

    virtual int IsAlarmState();

    virtual void UpdateRCT();

    virtual void GetPropMap(TPropMap &m);
    virtual void SetPropMap(TPropMap &m);

    // virtual int GetUsedImpulsCount();
    // virtual char *  GetUsedImpulsInfo(int NumImpProp, int &RealOffset); // � 0

    // int  GetImpulsInfo(int aimp, const char* &CnlName, int &RealOffset);  // � 0
    // char * GetImpulsInfo2(char * PropName, int &RealOffset);
    // char * GetImpulsInfo3(char * PropName, const char* &CnlName, int &RealOffset);
    virtual void ShowTrainNumber();
    virtual void HideTrainNumber();

    Station *Stan();
    Poligon *Polig();

    virtual int GetMarkerAtXY(int X, int Y);
    virtual void ChangeMarkerXY(int iMarker, int aX, int aY){};
    virtual int GetMarkerCount() { return 0; };
    virtual void GetMarkerPoint(int iMarker, int &aX, int &aY){};

    void ShowPads();
};

typedef AComp *PAComp;
PAComp Trans(char *, int);

typedef int (*T_f_Func)(int, void *);
void Set_f_Func(T_f_Func A_f_);

typedef int (*T_f2_Func)(int, const char *);
void Set_f2_Func(T_f2_Func A_f2_);

typedef char *(*T_GetSigName_Func)(int);
void Set_T_GetSigName_Func(T_GetSigName_Func AGetSigName_Func);

typedef void *(*T_GetDatagramData_Func)(int typ, const char *PacketName);
void Set_GetDatagramData_Func(T_GetDatagramData_Func AGetDatagramData_Func);

typedef void *(*T_GetDatagramPacket2_Func)(int typ, const char *PacketName);
void Set_GetDatagramPacket2_Func(T_GetDatagramPacket2_Func AGetDatagramPacket2_Func);

extern T_GetDatagramData_Func GetDatagramData_Func;
extern T_GetDatagramPacket2_Func GetDatagramPacket2_Func;

#endif
