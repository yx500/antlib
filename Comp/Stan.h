#ifndef STAN_H
#define STAN_H

#include "ACom_T.h"
#include "Elem.h"
#include "Marshrut.h"
#include "Vatempl.h"

#include <cstring>
#include <vector>

class AComp;
class Poligon;
class VisibleArray;
struct TEnergStanLamps;

typedef int (*TGetPacketOffset)(int typ, const char* PacketName, int WantNamber);
extern TGetPacketOffset CustomGetPacketOffset;

typedef void (*TEachStan)(Station*);
extern TEachStan EachStanPostShow;

#pragma pack(push, 1)
struct St_Dat
{
  short int Nom;        /*����� ������� */
  char filename[13];    /*��� �����     */
  char descriptor[13];  /*��� �������   */
  int8 MUL_X[2];        /*���������� ���������   �� X */
  int8 MUL_Y[2];        /*���������� ���������   �� Y */
  short int X_begin[2]; /*�������� ��  X  */
  short int Y_begin[2]; /*�������� ��  Y  */

  St_Dat() { memset(this, 0, sizeof(*this)); }
};

#pragma pack(pop)

struct TUseChanelName
{
  int type;
  char name[12];

  TUseChanelName() { memset(this, 0, sizeof(*this)); }
};

class TETTList;

class Station
{
  St_Dat TheData;

protected:
  TETTList* ETTList;
  bool bETTListNotFound;

public:
  St_Dat* Dat;
  std::vector<VisibleArray*> POLE;
  Poligon* pPoligon;
  int ChanelOffset[255];
  char ChanelNames[255][12];
  std::vector<TUseChanelName> vUseChanelNames;
  int ID_RP;                       /*   */
  String filename;                 /*��� �����     */
  String name;                     /*���      */
  TEnergStanLamps* EnergStanLamps; // ����� �����������
  TMarshList MARSHLIST;
  TAntOpt* AO;
  char ElemsSostPacketName[12];

  bool OpenIniFile();
  void Adapter();
  int GetImpVal(int imp);

  Station(const char* ifilename = 0);
  ~Station();

  void Close();
  String FullFN();
  void Show();
  void ShowActives();
  void Hide();
  void GoEachACompStanPreFun();
  void GoEachACompStanPostFun();
  void ShowElemsSost();
  void ShowElemsTagStr();
  void Go();
  void Clear();
  int TstXY(int _x, int _y);

  int Save();
  int SaveSTA();
  int SaveSTE();
  int SaveAs(const char* NewFileName);

  int Open(const char* fn);
  int LoadSTA();
  int LoadSTE();
  void ReadChanelsInfo(AStringList* SL);
  void ConnectGorls();

  void SetMas(int imul_x, int imul_y);
  void SetBegin(int x_, int y_);
  AComp* GetObjByID(unsigned int ObjID);
  AComp* Trans(char* uk, int unit);
  AComp* GetObjByID_Imp(unsigned int ObjID, int Imp);
  AComp* GetObjByName_Unit(const char* CompName, int unit);
  AComp* GetObjByName_InTypes(const char* CompName, TYP* Types, int TypesCnt);

  const char* Name4Canal(uint8 canal)
  {
    if (canal > 0 && canal < 255)
      return ChanelNames[canal];
    else
      return "none";
  }

  String Name()
  {
    if (name.Length() > 0)
      return name;
    static char n_name[256];
    memset(n_name, 0, sizeof(n_name));
    cp866_to_cp1251_buff(Dat->descriptor, n_name, strlen(Dat->descriptor));
    return n_name;
  }

  const char* FileName()
  {
    return Dat->filename;
  }

  void BeginGenerateTN();
  int UpdateState();
  void ShowTrainNumbers(bool bHide);
  // bool GetObjByImpulsName(String &impname, String & respropname, int &resimpabsnumber);
  void GetPropMap(TPropMap& m);
  void SetPropMap(TPropMap& m);
  AComp* SetFocus(unsigned int ObjID, int focus);
  void Connect_stNext();
  uint16 SetUnicalID(uint16 ID);
  void for_each_chanel(TGetPacketOffset f);
  void reassignChanelOffset();

  int GetStrelkiCount();

  // bool GetParamsEttItem(unsigned int EventType_ID,int ID_OBJ,int &Visible,int &Act,int &TOShow);
};

class SubStation : public Element
{
protected:
  TRect boundRCT;
  bool bAlreadyEmbedded;

public:
  int dx0, dy0;

  Station* substan;
  char filename[13]; /*��� �����     */
  char repl[10][64];
  bool bNoRebuildID;

  SubStation();

  virtual void UpdateState();

  virtual void Set();
  virtual void Get();
  TYP GetType();
  UNIT GetUnit();

  void LoadSTE();

  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);

  virtual void Show();
};

extern TAntOpt AntOpt0;
TAntOpt* GetUsedAntOpt();

#endif
