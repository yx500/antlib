#ifndef EXDHH
#define EXDHH
//---------------------------------------------------------------------------
#include "aheaders_h.h"

#pragma pack(push,1)

/*
struct tTNCell{
  int16 T;
  int16 Sig;
  int16 NS;
  int16 NF;
  int16 xESR;
};

struct TTNData{
  int16 ID_OBJ;
  int16 IMPULS;
  int16 ID_CHAIN;
  int16 NUMBER;
  int16 ESR;
};
*/
struct TIUTrainPriznak {
    unsigned  Razr: 1;                 //���������
    unsigned  Oversize: 1;             //������������
    unsigned  Theavy: 1;               //������������
    unsigned  Long: 1;                 //���������������
    unsigned  United: 1;               //�����������
    unsigned  SpeedLimit: 1;           //� ������������ ��������
    unsigned  WithTolkach: 1;          //� ��������
    unsigned  ALSN_RS_Error: 1;        //����������� ���� ��� ��
};

struct TTrainInfo  {
    uint16 TrainNumber;             // 2 ����� - ����� ������ � ���.
    uint8  TrainColor;              // 1 ����  - ����, ������� ������������ � ��� ����� ������ � ���� �������.
    TIUTrainPriznak TrainPriznak;    // 1 ���� - ����. �������� ������
    uint8  TrainLength;             // 1 ���� - �������� ����� ������
    uint16 TrainWeight;             // 2 ����� - ��� ������ (� �����)
    uint16 TrainIndex[3];           // 6 ���� - ������ ������ (��. ������������ - 2 �����,����� ������� - 2 ����� , ��. ���������� - 2 �����)
    uint16 LocomSeries;             // 2 ����� - ����� ��������� ����������
    uint8  LocomNumber[3];          // 3 ����� - ����� �������� ������ ����������
    uint8  Reserv2[7];              // 7 ���� - ������
};

struct TKroshTrainInfo  {
    int offsetimp;
    char channame[12];
    TTrainInfo TrainInfo;
};
const int KrPackCnt = 499 / sizeof(TKroshTrainInfo);
struct TKrPack {
    TKroshTrainInfo KTI[KrPackCnt];
};



struct TMKMarshItem {
    uint32 id_mar;  // ������������� �������� � �� APilot (marsh_nsi)
    uint32 numcom;
    int32          state_mk;      // ��������� �������� ()
    int32          state_mk_ex;   // ��������� �������� ()
};

const int MKMarshPackCnt = 480 / sizeof(TMKMarshItem);
struct TMKMarshAll {
    uint32 esr;
    int              cnt;
    TMKMarshItem     M[MKMarshPackCnt];
};

enum state_mk {
    mk_state_Ready = 1, //    ����� � ���������   ������� �� �����, ����������� �������� ��� (�� ���������������)
    mk_state_Done =  2, //    ����������  ����������,  �������, �� �����, �������� ������
    mk_state_Busy = -1, //    ����� ��� ��������� ������� ����� ��� ���������� (���������������) ���������� �������
    mk_state_Close = -2  //    ������  � "marsh_nsi" ���� Close=1
};
enum state_mk_ex {
    mk_state_ex_Nothing = 0, //    ������
    mk_state_ex_Unknown = 1, //    �� ����������   ����������� (����) ������� ��, ������ �������� �������
    mk_state_ex_Making = 2, //    ��������������� ������� ������� �� ��� ���������
    mk_state_ex_AUmode = 3, //   ������� ������ �� ��� ��
    mk_state_ex_DirBusy = 4 //   ����� �������  ��� �������� ����������� �������� ��������� �����������
};




struct TAVMarshItem {
    uint32 id;      // ������������� �������� � �� APilot (marsh_nsi)
    uint32 id_zak;  // ������������� �������� � �� APilot (marsh_nsi)
    uint32 id_mar;  // ������������� �������� � �� APilot (marsh_nsi)
    uint32 numcom;
    int32          state_av;      // ��������� �������� ()
    int32          state_av_ex;   // ��������� �������� ()
    TDateTime           time_op;
    TDateTime           time_tu;
    uint32 num_train;

};

const int AVMarshPackCnt = 420 / sizeof(TAVMarshItem);

const int izNO = 0; // �������� �����������    < . . .
const int izCP = 1; // ������ �����            . > . .
const int izNP = 2; // �������� �����          . . < .
const int izCO = 3; // ������ �����������      . . . >

struct TAVStanInfo {
    uint32 esr;
    uint32 AV_DU;
    char     dnc_guid[40];
    uint16 z_cnt[4];
    uint16 cnt;
    TAVMarshItem     M[AVMarshPackCnt];
};


struct TElemCheckState {
    uint16 id_obj;
    int8 id_check;
    int8 state;
};
const int ElemStatePackCnt = 480 / sizeof(TElemCheckState);
struct TEIPack {
    TElemCheckState ES[ElemStatePackCnt];
};



#pragma pack(pop)

#endif
