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
    unsigned  Razr: 1;                 //разрядный
    unsigned  Oversize: 1;             //негабаритный
    unsigned  Theavy: 1;               //тяжеловесный
    unsigned  Long: 1;                 //длинносоставный
    unsigned  United: 1;               //соединенный
    unsigned  SpeedLimit: 1;           //с ограничением скорости
    unsigned  WithTolkach: 1;          //с толкачем
    unsigned  ALSN_RS_Error: 1;        //неисправные АЛСН или РС
};

struct TTrainInfo  {
    uint16 TrainNumber;             // 2 байта - номер поезда в ГИД.
    uint8  TrainColor;              // 1 байт  - цвет, которым отображается в ГИД нитка поезда с этим номером.
    TIUTrainPriznak TrainPriznak;    // 1 байт - спец. признаки поезда
    uint8  TrainLength;             // 1 байт - условная длина поезда
    uint16 TrainWeight;             // 2 байта - вес поезда (с тарой)
    uint16 TrainIndex[3];           // 6 байт - индекс поезда (ст. формирования - 2 байта,номер состава - 2 байта , ст. назначения - 2 байта)
    uint16 LocomSeries;             // 2 байта - серия головного локомотива
    uint8  LocomNumber[3];          // 3 байта - номер головной секции локомотива
    uint8  Reserv2[7];              // 7 байт - резерв
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
    uint32 id_mar;  // идентификатор маршрута в БД APilot (marsh_nsi)
    uint32 numcom;
    int32          state_mk;      // состояние маршрута ()
    int32          state_mk_ex;   // состояние маршрута ()
};

const int MKMarshPackCnt = 480 / sizeof(TMKMarshItem);
struct TMKMarshAll {
    uint32 esr;
    int              cnt;
    TMKMarshItem     M[MKMarshPackCnt];
};

enum state_mk {
    mk_state_Ready = 1, //    Готов к установке   Маршрут не занят, враждебного маршрута нет (не устанавливается)
    mk_state_Done =  2, //    Установлен  Установлен,  замкнут, не занят, светофор открыт
    mk_state_Busy = -1, //    Занят для установки Маршрут занят или установлен (устанавливается) враждебный маршрут
    mk_state_Close = -2  //    Закрыт  В "marsh_nsi" поле Close=1
};
enum state_mk_ex {
    mk_state_ex_Nothing = 0, //    Ничего
    mk_state_ex_Unknown = 1, //    Не определено   Отсутствуют (сбой) сигналы ТС, потеря контроля стрелки
    mk_state_ex_Making = 2, //    Устанавливается Поймана команда ТУ для установки
    mk_state_ex_AUmode = 3, //   Активен сигнал РУ или СУ
    mk_state_ex_DirBusy = 4 //   Занят перегон  Для маршрута отправления замкнуто встречное направление
};




struct TAVMarshItem {
    uint32 id;      // идентификатор маршрута в БД APilot (marsh_nsi)
    uint32 id_zak;  // идентификатор маршрута в БД APilot (marsh_nsi)
    uint32 id_mar;  // идентификатор маршрута в БД APilot (marsh_nsi)
    uint32 numcom;
    int32          state_av;      // состояние маршрута ()
    int32          state_av_ex;   // состояние маршрута ()
    TDateTime           time_op;
    TDateTime           time_tu;
    uint32 num_train;

};

const int AVMarshPackCnt = 420 / sizeof(TAVMarshItem);

const int izNO = 0; // Нечетное отправление    < . . .
const int izCP = 1; // четное прием            . > . .
const int izNP = 2; // Нечетное прием          . . < .
const int izCO = 3; // четное отправление      . . . >

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
