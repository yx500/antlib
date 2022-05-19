#ifndef GORL_H
#define GORL_H

#include "Comp.h"

#include <stdio.h>
#include <stdio.h>

#define Max_Size_Gorl_ 40  //  ������������ ���������� ���. �������� � �����
#define Max_Size_Strel_ 80 //  ������������ ���������� ������� � ����.
#define Max_Size_Marsh_ 20 //  ������������ ���������� ��������� � ����.

int Def_gr(char* txt);
class Strel0;
#pragma pack(push, 1)

struct ID_ZO
{
  uint8 b[4];
};

struct Signal_file
{
  char name[6]; /*��� ���������*/
  uint32 _nomer; /*�����(� ����� �� ���������)*/
};


struct Signal :public Signal_file
{
    AComp* nomer; /*�����(� ����� �� ���������)*/
};

struct Grl_file
{

  short int Col_Mar; // ����������  ���������
  short int Col_Str; // ����������  �������

  char name[6];  // ��� ���������
  uint8 bit_m;   // ������� ���������� ���������
  uint8 bit_ksp; // ������� ���������� ��������
  uint8 bit_kzm; // ������� ���������� ����������
  uint8 nom_fiz; // ����� ��� ���������

  int16 impuls_ksp;  // ������ �������
  int16 impuls_kzm;  // ������ ���������
  int16 impuls_ks;   // ������ ��������� �����������
  int16 impuls_ks_i; // ������ ��������� ������
  uint32 _Matr;           // ����� �������  ���������
  uint32 _Strel_N;         // ����� ������ �������
  uint32 __Strel;       // ��������� �� ��������� (� ����� ������������)
  uint32 _Sign;          // ��������� ���������� �����������
  Signal_file _Sign_i;         // ������� ������
  uint32 _impuls_m;   // ������� �� ��������� ��������
  uint32 _impuls_km;  // ������� �� ������� ��������
                         //------------======  ��������  =======-----------
  uint8 IN_OUT;          // ����� \�����������  (1)              -�
  uint32 _zona_M;         // ������ ���������� ���� ���  (4*6=24)  +
  ID_ZO zona_1;          // ��������� ����               (4)      � 133
  int16 tu_marh;
  int32 time_tu;
  int16 priz;
  int16 marh;
  int16 marh_tu;
  int16 marh_m;
  int16 marh_sv;
  int16 old_marsh;   // ����� �������� ��������
  uint32 tim_o_m; // ����� �������� �������� ��� ������

  uint16 ID;
  char zapas[2];

  Grl_file();
};

struct Grl 
{
    short int    Col_Mar;                   // ����������  ���������
    short int    Col_Str;                   // ����������  �������

    char   name[6];                   // ��� ���������
    uint8   bit_m;                     // ������� ���������� ���������
    uint8   bit_ksp;                   // ������� ���������� ��������
    uint8   bit_kzm;                   // ������� ���������� ����������
    uint8   nom_fiz;                   // ����� ��� ���������

    int16    impuls_ksp;                // ������ �������
    int16    impuls_kzm;                // ������ ���������
    int16    impuls_ks;                 // ������ ��������� �����������
    int16    impuls_ks_i;               // ������ ��������� ������
    char   **Matr;                // ����� �������  ���������
    char   *Strel_N;                // ����� ������ �������
    Strel0    * *_Strel;               // ��������� �� ��������� (� ����� ������������)
    Signal *Sign;                 // ��������� ���������� �����������
    Signal     Sign_i;                // ������� ������
    int16    *impuls_m;             // ������� �� ��������� ��������
    int16    *impuls_km;            // ������� �� ������� ��������
//------------======  ��������  =======-----------
    int8   IN_OUT  ;                 // ����� \�����������  (1)              -�
    ID_ZO  *zona_M;              // ������ ���������� ���� ���  (4*6=24)  +
    ID_ZO  zona_1    ;               // ��������� ����               (4)      � 133
    int16    tu_marh;
    int32   time_tu;
    int16    priz;
    int16    marh;
    int16    marh_tu;
    int16    marh_m;
    int16    marh_sv;
    int16    old_marsh;      // ����� �������� ��������
    uint32 tim_o_m; // ����� �������� �������� ��� ������

    uint16 ID;
    char zapas[2];



  Grl();
  void toGrl_file(Grl_file *gf);
  void fromGrl_file(Grl_file *gf);
};
#pragma pack(pop)

typedef Grl* PGrl;
class Strel0;

class Gorl : public AComp
{

  Grl TheData;
  
private:
  Strel0* nom[Max_Size_Gorl_];
  int marsh[Max_Size_Gorl_],
      busi[Max_Size_Gorl_],
      // sign   [Max_Size_Gorl_],
      // sign_i [Max_Size_Gorl_],
      marsh_y[Max_Size_Gorl_],
      marsh_u[Max_Size_Gorl_],
      itis[Max_Size_Gorl_],
      clr0[Max_Size_Gorl_],
      isu[Max_Size_Gorl_],
      svu[Max_Size_Gorl_],
      ism[Max_Size_Gorl_];
  char State[Max_Size_Strel_];
  int Flag_KSP_[Max_Size_Strel_];
  int mem_KSP[Max_Size_Strel_];

  int Count_empty;
  int priznak_marsh_in_fiz_gorl_for_filter_kzm;

  void usFindMarshruts();
  void usOpredKSP();
  void usFiltrs(int i, int j);
  void usOutStrel();
  void usOutSvet();

public:
  int Size_G;
  PGrl gorl[Max_Size_Gorl_];
  int TU[Max_Size_Gorl_];
  Gorl* comp[Max_Size_Gorl_];
  bool bVirtual;
  virtual const char* GetName();
  virtual void Show();
  virtual void Set();
  virtual void Get();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
  virtual void Go();
  void Save(std::ostream& file);
  void Load(std::istream& file);
  TYP GetType();
  UNIT GetUnit();
  Gorl();
  Gorl(int, int);
  void Creat(void);
  void Destroy(void);

  virtual unsigned int GetID(void);
  virtual void SetID(unsigned int);
  void GetMarsh(int& Marsh, bool& BUSY, bool& KZM, bool& SvOpen0, bool& SvOpen1);
  int GetDoneMarsh();

  ~Gorl();

  void Connect();

  // void LoadDB(char* DBfile,int n);
  // void SaveDB(char* DBfile,int n);

  virtual void UpdateState();
};

extern int Col_Gorl;
extern int Size_G;

typedef Gorl* PGorl;
extern PGorl Curr_G;







#endif
