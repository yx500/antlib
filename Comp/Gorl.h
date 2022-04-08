#ifndef GORL_H
#define GORL_H

#include "Comp.h"

#include <stdio.h>

#define Max_Gorl 40 //  люйяхлюкэмне йнкхвеярбн кнц. цнпкнбхм б ндмни
#define _Size_G 40
#define Max_Size_Strel_ 80 //  люйяхлюкэмне йнкхвеярбн ярпекнй б цнпк.
#define Max_Size_Marsh_ 20 //  люйяхлюкэмне йнкхвеярбн люпьпсрнб б цнпк.

int Def_gr(char* txt);
class Strel0;
#pragma pack(push, 1)

struct ID_ZO
{
  uint8 b[4];
};

struct Signal
{
  char name[6]; /*хлъ ябернтнпю*/
  AComp* nomer; /*юдпея(б тюике ме нопедекем)*/
};

struct Grl
{

  short int Col_Mar; // йнкхвеярбн  люпьпсрнб
  short int Col_Str; // йнкхвеярбн  ярпекнй

  char name[6];  // хлъ цнпкнбхмш
  uint8 bit_m;   // опхгмюй сопюбкемхъ люпьпсрнл
  uint8 bit_ksp; // опхгмюй сопюбкемхъ гюмърхел
  uint8 bit_kzm; // опхгмюй сопюбкемхъ гюлшйюмхел
  uint8 nom_fiz; // мнлеп тхг цнпкнбхмш

  short int impuls_ksp;  // яхцмюк гюмърхъ
  short int impuls_kzm;  // яхцмюк гюлшйюмхъ
  short int impuls_ks;   // яхцмюк ябернтнпю нропюбкемхъ
  short int impuls_ks_i; // яхцмюк ябернтнпю опхелю
  char** Matr;           // юДПЕЯ люрпхжш  люпьпсрнб
  char* Strel_N;         // юДПЕЯ мнлепю ярпекнй
  Strel0** _Strel;       // сЙЮГЮРЕКЭ МЮ сйюгюрекх (б тюике менопедекемш)
  Signal* Sign;          // сЙЮГЮРЕКЭ ябернтнпнб нропюбкемхъ
  Signal Sign_i;         // ябернтн опхелю
  short int* impuls_m;   // яхцмюкш мю сярюмнбйс люпьпсрю
  short int* impuls_km;  // яхцмюкш мю гюмърхе люпьпсрю
                         //------------======  якефемхе  =======-----------
  uint8 IN_OUT;          // ОПХЕЛ \НРОПЮБКЕМХЕ  (1)              -╛
  ID_ZO* zona_M;         // яохянй оепелеммшу хлем гнм  (4*6=24)  +
  ID_ZO zona_1;          // онярнъмюъ гнмю               (4)      ╕ 133
  short int tu_marh;
  long time_tu;
  short int priz;
  short int marh;
  short int marh_tu;
  short int marh_m;
  short int marh_sv;
  short int old_marsh;   // МНЛЕП ОПНЬКНЦН ЛЮПЬПСРЮ
  unsigned long tim_o_m; // БПЕЛЪ ОПНЬКНЦН ЛЮПЬПСРЮ ОПХ ОНРЕПЕ

  uint16 ID;
  char zapas[2];

  Grl();
};
#pragma pack(pop)

typedef Grl* PGrl;
class Strel0;

class Gorl : public AComp
{
private:
  Strel0* nom[_Size_G];
  int marsh[_Size_G],
      busi[_Size_G],
      // sign   [_Size_G],
      // sign_i [_Size_G],
      marsh_y[_Size_G],
      marsh_u[_Size_G],
      itis[_Size_G],
      clr0[_Size_G],
      isu[_Size_G],
      svu[_Size_G],
      ism[_Size_G];
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
  PGrl gorl[_Size_G];
  int TU[_Size_G];
  Gorl* comp[_Size_G];
  bool bVirtual;
  virtual const char* GetName();
  virtual void Show();
  virtual void Set();
  virtual void Get();
  virtual void GetPropMap(TPropMap& m);
  virtual void SetPropMap(TPropMap& m);
  virtual void Go();
  void Save(FILE* file);
  void Load(FILE* file);
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
