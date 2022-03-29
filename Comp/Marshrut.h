//---------------------------------------------------------------------------

#ifndef MarshrutH
#define MarshrutH
//---------------------------------------------------------------------------

#include "propmap.h"
#include "EXDH.h"

class AComp;
class Station;
class Ways;
class TMarshList;
class TY_ZONA;

// �������� ���� �������� W- ����, B-������
enum TMarshSectType {mstUnknow = 0, mstBW = 1, mstWB = 2, mstWW = 3, mstBB = 4};
enum TImpMarsh {ii_busySV = 0, ii_busyS_PRED = 1, ii_busyS_PAST = 2, ii_kzmS_PRED = 3, ii_kzmS_PAST = 4};
// NO_CHECK_BUSY  ��������� ������ ��������� ��� �������
// NO_CHECK_IS    ��������� ������ ������� ��� ���������

enum TStrInMarshChek  {cNORMAL = 0, cNO_CHECK_BUSY = 1, cNO_CHECK_IS = 2};

enum TMarshOdd_Even {mOdd = 0, mEven = 1, mUnknown = 2};  // <-�   � ->
enum TMarshDirType {mdirUnknown = 0, mdirDep = 1, mdirArr = 2, mdirMove = 3};

const NOORDER = 0;
const MarshrutPropNameCount = 9;

extern String MarshrutPropName[];

struct _tTULite {
    uint8   mid;            // ������������� �����������
    uint8   stan ;          // �������
    uint8   group;          // ������
    uint8   cod;            // �������
    uint8   num;            // ����� � ������ � ������
};

struct _tTU {
    _tTULite tu[2];
};


class TStrInMarsh  // �������� ������� � ��������
{
public:
    char   STRELNAME[10];

    int    IS;      // ��������
    TStrInMarshChek DOCHEK;  // ��� ��������

    int    ORDER;    // ������� � �������� 1..N

    AComp * pStrel;  // ��������� �� ����������

    //String PacketName;        // ��� ������ �������� � csv
    //int    ObjID;             // id �������� � csv
    //int    imp[4];            // �������� �������� � csv

    int     realIS;  //
    int     realBUSY;// ������� ��������
    int     realKZM; //

    void UpdateState(); // ������������� ������� ��������
    //void UpdateState2();
    void FromString(String stSrc);

    String  ToString();

    TStrInMarsh();
    TY_ZONA * YZ_STR;  // ��������� �� ���� � �����
};

// �������� ����� - �������
class TMarshrut
{
private:
    void          __fastcall SetSTRELS(int Index, TStrInMarsh * value);
    TStrInMarsh * __fastcall GetSTRELS(int Index);
    int           __fastcall GetSTRELSCOUNT();
    void          __fastcall SetSTRELSORD(int Index, TStrInMarsh * value);
    TStrInMarsh * __fastcall GetSTRELSORD(int Index);

protected:
    TList * FStrels;   // ������ �� �����.
    // �� �������� , ��� �� ������ �� ������������ �������
public:
    TMarshList * MarshList;

    // �� �����
    int     NUMCOM;
    int     GROUP;
    String  NAME;
    String  SV;
    String  SV2; // �������� ��������
    String  S_PRED;
    String  S_PAST;
    String  ORDER;
    String  GORL;

    /*String PacketName;  // �������� � csv
    int    imp[5];      // �������� � csv
    String impname[5];  // �������� ����� �������� � csv
    int    ObjID[3];    // �������� � csv
    */

    // ������������ ��� ���������� � �������
    AComp*  pSV;
    AComp*  pSV2;
    Ways*   pS_PRED;
    Ways*   pS_PAST;
    TMarshSectType MarshSectType;  //���� ��������

    // ���������� � UpdateState()
    int     realbusySV;
    int     realbusyS_PRED;
    int     realbusyS_PAST;
    int     realkzmS_PRED;
    int     realkzmS_PAST;

    void * TagPtr;

    _tTU TUCmd;
    String TUPacketName;

    bool bErrorData; // ������ � ��������� ������


    /*
    

    // APILOT===========================
    state_mk       apilotState, oldapilotState;
    state_mk_ex    apilotStateEx;
    int            apilotEsr;
    int            apilotId_mar;
    */
    TY_ZONA * YZ_PRED;  // ��������� �� ���� � �����
    TY_ZONA * YZ_PAST;
    TY_ZONA * YZ_TNZ;
    TY_ZONA * YZ_TNO;


    int imp_per_napr[2];  //������ ����������� �� �������� � �
    int imp_per_busy[2];  //������ ������� �������� � �
    // ���������� � UpdateState()
    int rimp_per_napr[2];
    int rimp_per_busy[2];

    // APILOT===========================
        //--------------------------------------------------------------
    TMarshrut();
    virtual ~TMarshrut();

    void Clear();

    TStrInMarsh * GetStrelByName(String StrelName);    // �������� ������ �� ����� �������

    void GetPropMap(TPropMap &m);
    void SetPropMap(TPropMap &m);

    void UpdateState(); // ������������� ������� ��������
    //void UpdateState2();
    bool UpdateStrelOrder(); // ������������� �������� ORDER ��� �������
    void SetMarshSectType(); // ������������� �������� ���� ��������
    int  GetMaxORDER(void); // �������� ������������ ���������


    void Show(bool bSetIs, bool bSetClr, bool bSetStyll, int Clr, int Styll);
    void SetForShowUst(bool bHide = false);
    TStrInMarsh * SetStrInMarsh(String StrelName, int IS, TStrInMarshChek DOCHEK, int ORDER);
    bool IsUstanovlen();

    void AddStrInMarsh(TStrInMarsh *sim);
    void DelStrInMarsh(TStrInMarsh *sim);

    void CheckStat(bool &IsOK, bool &BusyOK, bool &KzmOK, bool &SVOk);
    void CheckStatFull(int &Pol, int &Busy, int &Kzm, int &SV);
    String      GetStateString();
    String      GetUsedDataStr();  // ������ ��� �������� ������������

    bool CommonSections(TMarshrut * M);

    TMarshDirType GetDirType();
    TMarshOdd_Even GetOddEven();
    //int CheckGoodDir();
#ifndef QT_ANTLIB
    __property TStrInMarsh * STRELS[ int Index ]  = { read = GetSTRELS, write = SetSTRELS };  // ������ ������� �� �������
    __property int           STRELSCOUNT  = { read = GetSTRELSCOUNT };
    __property TStrInMarsh * STRELSORD[ int Index ]  = { read = GetSTRELSORD, write = SetSTRELSORD };
#endif
};

class TMarshList
{
private:
    void          __fastcall SetSTRELS(int Index, TStrInMarsh * value);
    TStrInMarsh * __fastcall GetSTRELS(int Index);
    int           __fastcall GetSTRELSCOUNT();
    TMarshrut*    __fastcall GetMARSHRUTS(int Index);
    int           __fastcall GetMARSHRUTSCOUNT();

protected:

    TList * FMarshuts;   // ������ ���������
    TList * FStrels;     // ��� ������� �������
    //void        UpdateLoadedImps();
    int indMarshrutPropName[MarshrutPropNameCount];

public:
    Station * pStan;
    String FileName;
    TMarshList();
    void Clear();
    virtual ~TMarshList();

    void        ConnectToStanSTA(Station * pS);
    void        ConnectToStanBD(Station * pS);
    bool        LoadFromCSV(String stFN);
    bool        SaveToCSV(String stFN);
    bool        LoadTUFromCSV(String stFN);

    void        UpdateState();
    //void        UpdateState2();

    TStrInMarsh * GetStrelByName(String StrelName);    // �������� ������ �� ����� �������
    TMarshrut * GetMarshrutByNum(int Num);
    TMarshrut * GetMarshrutByTU(_tTU * TUCmd);


    void ShowUstMarsh(bool Only_1 = false);

    void        AddMarshrut(TMarshrut* M);  // ���������� ������ ��������
    void        DelMarshrut(TMarshrut* M);

#ifndef QT_ANTLIB
    __property TStrInMarsh * STRELS[ int Index ]  = { read = GetSTRELS, write = SetSTRELS };  // ������ ������� �� �������
    __property int           STRELSCOUNT  = { read = GetSTRELSCOUNT };
    __property TMarshrut*    MARSHRUTS[ int Index ]  = { read = GetMARSHRUTS };
    __property int           MARSHRUTSCOUNT  = { read = GetMARSHRUTSCOUNT };
#endif
};


extern int PropStrBegin;

#endif




