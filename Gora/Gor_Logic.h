//---------------------------------------------------------------------------

#ifndef Gor_LogicH
#define Gor_LogicH
//---------------------------------------------------------------------------

double TPVal(unsigned __int16 w);

struct t_Descr;
bool  GetZamData(int AddrLKSlot,
                 int addr,
                 int &V,       //��������
                 int &Voleg,   //��������
                 int &RC,
                 int &RRC,
                 int &ErrCS
                );

bool  GetOsyData(int tip,
                 int addr,
                 int &V,
                 int &E,
                 String &PacketName_21
                );





t_Descr*  GetDescr_imp(int *start,       // �������������� ������ / ���� ������
                       int startcnt,
                       int se,          // start=0/end=1
                       bool end_slg_inc
                      );
t_Descr*  GetDescr_imp1(int start,       // �������������� ������ / ���� ������
                       int se,          // start=0/end=1
                       bool end_slg_inc
                      );



bool GetKZPData(int addr,
                int &D,   // ��������
                int &E,      // ������ ������������
                int &V,
                int &P
               );
bool GetZKRData(int ZKR_N,
                int &ves_osi
               );
String GetADAM_val(String packetName);
struct tADK3Cell;
tADK3Cell* GetADK3Cell(int AddrLKSlot, int addr, unsigned __int32     &biostime);

struct t_ARSDescrCell;
t_ARSDescrCell*  GetZamDataCell(int AddrLKSlot,           int addr , unsigned __int32     &biostime);
t_Descr*  GetDescr_mar(int mar);

struct tDescrCom;
tDescrCom * GetDescrCom();

#endif
