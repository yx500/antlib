#ifndef Gor_LogicH
#define Gor_LogicH

#include "aheaders_h.h"

double TPVal(uint16 w);

struct t_Descr;
struct t_NewDescr;
struct t_OsyCell_21;
bool GetZamData(int AddrLKSlot,
                int addr,
                int& V,     //Скорость
                int& Voleg, //Скорость
                int& RC,
                int& RRC,
                int& ErrCS);

bool GetOsyData(int tip,
                int addr,
                int& V,
                int& E);

t_OsyCell_21* GetOsyData21(int tip, int addr, String& PacketName_21);

t_Descr* GetDescr_imp(int* start, // Местоположение Головы / жопы отцепа
                      int startcnt,
                      int se, // start=0/end=1
                      bool end_slg_inc);
t_Descr* GetDescr_imp1(int start, // Местоположение Головы / жопы отцепа
                       int se,    // start=0/end=1
                       bool end_slg_inc);
t_NewDescr* GetDescr_imp1_all(int start, // Местоположение Головы / жопы отцепа
                              int& cnt);

bool GetKZPData(int addr,
                int& D, // Значение
                int& E, // Ошибка обработанная
                int& V,
                int& P);
bool GetZKRData(int ZKR_N,
                int& ves_osi);
String GetADAM_val(String packetName);
struct tADK3Cell;
tADK3Cell* GetADK3Cell(int AddrLKSlot, int addr, uint32& biostime);

struct t_ARSDescrCell;
t_ARSDescrCell* GetZamDataCell(int AddrLKSlot, int addr, uint32& biostime);
t_Descr* GetDescr_mar(int mar);

struct tDescrCom;
tDescrCom* GetDescrCom();

#endif
