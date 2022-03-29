//---------------------------------------------------------------------------


#include "aheaders_cpp.h"
#include "Gor_Logic.h"
#include "tGorka.h"
//---------------------------------------------------------------------------


typedef void *(*T_GetDatagramData_Func)(int typ, const char * PacketName);
extern T_GetDatagramData_Func GetDatagramData_Func;
const VMetrPacketType = 4;
const OsyPacketType = 17;
const KzpCellsPacketType = 5;
const DescrPacketType = 9;
const MaxDescrPacketCount = 99;
const MaxtVMetrCell = 480 / sizeof(t_VMetrCell);
const MaxtOsyCell = 480 / sizeof(t_OsyCell);

double TPVal(unsigned __int16 w)
{
    return (!w || w == 0xffff) ?  0. : (1000000. / (70.*w));
}


char  ZamPacketName[8][12] = {"mog2_v", "ARS1", "ARS2", "ARS3", "ARS4", "ARS5", "ARS6", "ARS7"};

t_ARSDescrCell*  GetZamDataCell(int AddrLKSlot,           int addr , unsigned int     &biostime)
{
    biostime = 0;
    if (GetDatagramData_Func == NULL) return NULL;
    t_ARSDescrCellsPacket *  VMetrCellsPacket = (t_ARSDescrCellsPacket *) GetDatagramData_Func(VMetrPacketType, ZamPacketName[AddrLKSlot]);
    if (VMetrCellsPacket == NULL) return NULL;
    biostime = VMetrCellsPacket->biostime;
    for (int i = 0; i < MaxtVMetrCell; i++) {
        if (VMetrCellsPacket->Cells[i].addr == 0) continue;
        if (VMetrCellsPacket->Cells[i].addr == addr) {
            return &VMetrCellsPacket->Cells[i];
        }
    }
    return NULL;
}


bool  GetZamData(int AddrLKSlot,
                 int addr,
                 int &V,       //—корость
                 int &Voleg,   //—корость
                 int &RC,
                 int &RRC,
                 int &ErrCS)
{
    V = 0; Voleg = 0; RC = 0; RRC = 0;
    if (addr == 0) return true;
    unsigned __int32     biostime;
    t_ARSDescrCell *  VMetrCells = GetZamDataCell(AddrLKSlot,           addr,     biostime);

    if (VMetrCells == NULL) {
        RRC = 33;
        return false;

    }

    V = VMetrCells->V;
    Voleg = VMetrCells->Voleg ;
    RC = VMetrCells->RC.RC ;
    if (VMetrCells->RC.RC_pred==1) RC=1;
    RRC = VMetrCells->RC.RRC;
    ErrCS=VMetrCells->RC.ErrCS;
    return true;

}

bool  GetOsyData(int tip,int addr,
                 int &V,
                 int &E
                )
{
    V = 0; E = 0;
    if (addr < 0) return false;
    if (GetDatagramData_Func == NULL) return false;
    static char  PacketName_1[12] = "diso";
    static char  PacketName_2[12] = "ZKR1_DSO";
    static char  PacketName_3[12] = "ZKR2_DSO";


    if ((tip>=1) && (tip<=3)){
        if (addr >= MaxtOsyCell) return false;
        t_OsyCellsPacket *    OsyCellsPacket = NULL;
        if (tip==1)   OsyCellsPacket = (t_OsyCellsPacket *) GetDatagramData_Func(OsyPacketType, PacketName_1);
        if (tip==2)   OsyCellsPacket = (t_OsyCellsPacket *) GetDatagramData_Func(17, PacketName_2);
        if (tip==3)   OsyCellsPacket = (t_OsyCellsPacket *) GetDatagramData_Func(17, PacketName_3);
        if (OsyCellsPacket == NULL) return false;
        V = OsyCellsPacket->Cells[addr].V;
        return true;
    }
    return false;

}
t_OsyCell_21*  GetOsyData21(int tip,int addr,
                 String &PacketName_21
                )
{
    if (addr < 0) return NULL;
    if (GetDatagramData_Func == NULL) return NULL;

    if (tip==21){
        if (addr >= (480 / sizeof(t_OsyCell_21))) return NULL;

        t_OsyCellsPacket_21 *OsyCellsPacket_21 = (t_OsyCellsPacket_21 *) GetDatagramData_Func(17, PacketName_21.c_str());
        if (OsyCellsPacket_21!=NULL) return &OsyCellsPacket_21->Cells[addr];
    }
    return NULL;

}



bool DescrCached = false;
static t_Descr *Descr_x[MaxDescrPacketCount];
t_Descr*  GetDescr_imp(int *start,       // ћестоположение √оловы / жопы отцепа
                       int startcnt,
                       int se,          // start=0/end=1
                       bool end_slg_inc
                      )
{
    if (GetDatagramData_Func == NULL) return NULL;
    t_Descr*  Descr;
    //ищем те у которых голова или хвост в зоне
    for (int j = 0; j < startcnt; j++) { // выбираем те кто ближе к “ѕ
        if (start[j] == 0) continue;
        Descr=GetDescr_imp1(start[j],se,end_slg_inc);
        if (Descr!=NULL) return Descr;
    }
    return NULL;
}

t_Descr*  GetDescr_imp1(int start,       // ћестоположение √оловы / жопы отцепа
                       int se,          // start=0/end=1
                       bool end_slg_inc
                      )
{
    if (GetDatagramData_Func == NULL) return NULL;
//>

    if (!DescrCached) {
        DescrCached = true;
        for (int i = 0; i < MaxDescrPacketCount; i++) {
            String stPacketName = "descr" + IntToStr(i);
            Descr_x[i] = (t_Descr *) GetDatagramData_Func(DescrPacketType, stPacketName.c_str());
        }

    }
    t_Descr*  Descr;
    //ищем те у которых голова или хвост в зоне
    if (start == 0) return NULL;
    if (!end_slg_inc){
        for (int i = 0; i < MaxDescrPacketCount; i++) {
            Descr = Descr_x[i];
            if (Descr == NULL) continue;
            // начало или конец
            if (Descr->end_slg == 0) {
                if ((se == 0) && (Descr->start + 1000 - 1 == start))
                    return Descr;
                if ((se == 1) && (Descr->end + 1000 - 1 == start))
                    return Descr;
            }

        }
    } else {
        for (int i = MaxDescrPacketCount-1; i >=0 ; i--) {
            Descr = Descr_x[i];
            if (Descr == NULL) continue;
            // начало или конец
                if ((se == 0) && (Descr->start + 1000 - 1 == start))
                    return Descr;
                if ((se == 1) && (Descr->end + 1000 - 1 == start))
                    return Descr;
        }
    }
    return NULL;
}

t_NewDescr*  GetDescr_imp1_all(int start,       // ћестоположение √оловы / жопы отцепа
                       int &cnt
                      )
{
    cnt=0;
    static t_NewDescr _descr10[10];
    if (GetDatagramData_Func == NULL) return _descr10;
//>

    memset(_descr10,0,sizeof(_descr10));

    t_Descr*  Descr;
    //ищем те у которых голова
    if (start == 0) return _descr10;
    for (int i = MaxDescrPacketCount-1; i >=0 ; i--) {
        Descr = Descr_x[i];
        if (Descr == NULL) continue;
        if (Descr->end_slg == 0) {
                if ((Descr->start + 1000 - 1 == start)) {
                        memcpy(&_descr10[cnt],Descr,sizeof(t_NewDescr));
                        cnt++;
                        if (cnt>=10) break;
                }
        }
    }
    return _descr10;
}

t_Descr*  GetDescr_ARS(int tp,
                       int Slot,
                       int Addr
                      )
{
    if (GetDatagramData_Func == NULL) return NULL;
//>

    if (!DescrCached) {
        DescrCached = true;
        for (int i = 0; i < MaxDescrPacketCount; i++) {
            String stPacketName = "descr" + IntToStr(i);
            Descr_x[i] = (t_Descr *) GetDatagramData_Func(DescrPacketType, stPacketName.c_str());
        }

    }
    t_Descr*  Descr;
    for (int i = MaxDescrPacketCount-1; i >= 0; i--) {
            Descr = Descr_x[i];
            if (Descr == NULL) continue;
            int a = (Slot - 1) * 100 + Addr;
            if (Descr->addr_tp[ tp-1 ] == a) {
                return Descr;
            }
    }
    return NULL;
}

static t_KzpCellsPacket *KzpCellsPacket = NULL;
static char PacketName[] = "KZP";
bool GetKZPData(int addr,
                int &D,   // «начение
                int &E,      // ќшибка обработанна€
                int &V,
                int &P
               )
{
    D = 0; E = 1;V=0;P=0;
    /*if (KzpCellsPacket==NULL){
       KzpCellsPacket = (tKzpCellsPacket *) GetDatagramData_Func(KzpCellsPacketType,PacketName);
    } */
    if (GetDatagramData_Func != NULL)
        KzpCellsPacket = (t_KzpCellsPacket *) GetDatagramData_Func(KzpCellsPacketType, PacketName); else
        KzpCellsPacket = NULL;
    if (KzpCellsPacket != NULL) {
        D = KzpCellsPacket->Cells[addr].D;
        E = KzpCellsPacket->Cells[addr].E;
        V = KzpCellsPacket->Cells_V[addr].V;
        P = KzpCellsPacket->Cells_V[addr].P;
        //E = E & 0x8000; заебало
        if (D < 0) E = 1;
        return true;
    }
    return false;
}



bool GetZKRData(int ZKR_N,
                int &ves_osi
               )
{
    ves_osi=-33;
    if (GetDatagramData_Func != NULL){
        String stPacketName = IpxNameZKR + IntToStr(ZKR_N);
        t_BufZkr * BufZkr =(t_BufZkr *) GetDatagramData_Func(IpxTypeZKR,stPacketName.c_str());
        if (BufZkr != NULL) {
           ves_osi=BufZkr->ves_osi;
           return true;
        }
    }
    return false;
}

String GetADAM_val(String packetName)
{
     if (GetDatagramData_Func != NULL){
        char * buf =(char *) GetDatagramData_Func(21,packetName.c_str());
        if (buf==0) return "---";
        char res[8];
        memset(res,0,sizeof(res));
        strncpy(res,buf,sizeof(res)-1);
        return String(res);
    }
    return "--";
}
const MaxADK3Cell=490/sizeof(tADK3Cell);
tADK3Cell* GetADK3Cell(int AddrLKSlot, int addr, unsigned __int32     &biostime)
                             // 1Ц 1 байт Ц собственный адрес, должен совпадать с запросом.
                             // 2Ц 2 байт Ц уровн€ давлени€ в ¬”ѕ« є1.
                             // 3Ц 3 байт уровн€ давлени€ в ¬”ѕ« є2 (аналогично как дл€ ¬”ѕ« є1).
                             // 4Ц 4 байт уровн€ температуры в Ѕ”  Ёѕ ¬”ѕ« є1.
                             // 5Ц 5 байт уровн€ температуры в Ѕ”  Ёѕ ¬”ѕ« є2 (аналогично как дл€ ¬”ѕ« є1).
                             // 6Ц 6 байт уровн€ напр€жени€ питани€ в ¬”ѕ« є1.
                             // 7Ц 7 байт уровн€ напр€жени€ питани€ в ¬”ѕ« є2 (аналогично как дл€ ¬”ѕ« є1).
                             // 8Ц 8 байт Ц резервный, все биты равны нулю.
{
     biostime=0;
     if (GetDatagramData_Func != NULL){
        tADK3CellsPacket* ADK3CellsPacket =(tADK3CellsPacket*) GetDatagramData_Func(IpxTypeADK3,IpxNameADK3);
        if (ADK3CellsPacket==0) return NULL;
        biostime=ADK3CellsPacket->biostime;
        for (int i = 0; i < MaxADK3Cell; i++) {
                if (ADK3CellsPacket->Cells[i].a == 0) continue;
                if (ADK3CellsPacket->Cells[i].a == addr)
                return &ADK3CellsPacket->Cells[i];
        }
    }
    return NULL;
}



t_Descr*  GetDescr_mar(int mar)
{
    if (GetDatagramData_Func == NULL) return NULL;
//>
    if (!DescrCached) {
        DescrCached = true;
        for (int i = 0; i < MaxDescrPacketCount; i++) {
            String stPacketName = "descr" + IntToStr(i);
            Descr_x[i] = (t_Descr *) GetDatagramData_Func(DescrPacketType, stPacketName.c_str());
        }
    }
    t_Descr*  Descr;
    for (int i = 0; i < MaxDescrPacketCount; i++) {
            Descr = Descr_x[i];
            if (Descr == NULL) continue;
            // начало или конец
            if (Descr->end_slg == 0)
                if (Descr->mar  == mar)
                    return Descr;
    }
    return NULL;
}

tDescrCom * GetDescrCom()
{
        if (GetDatagramData_Func == NULL) return NULL;
        tDescrCom *DescrCom=(tDescrCom *) GetDatagramData_Func(8,"COM2OLG");
        return DescrCom;
}
