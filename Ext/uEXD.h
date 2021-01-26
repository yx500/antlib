//---------------------------------------------------------------------------

#ifndef uEXDH
#define uEXDH
//---------------------------------------------------------------------------
#include "EXDH.h"  //  EXDH.h - структуры данных для обмена с dll
//#include "ACom_T.h"






class /*_ALIB_*/ TEXD
{
private:




protected:

public:
    bool Enabled;
    int TN_Ver;

    __fastcall TEXD();
    __fastcall ~TEXD();
    bool __fastcall InitDll();

    void __fastcall TN_SetVer(int AVer);
    TTrainInfo * __fastcall TN_GetTN(int imp, const char * StanFN, const char * ChanelName, bool bUseDoublFilter);
    int  __fastcall TN_SetInputBuf(void * buf, int maxchanels);
    bool __fastcall TN_SetInputBufChanelN(void * buf, int ChanelNumber);
    void __fastcall TN_PrepareDoublTNFilter();

    //int __fastcall TN_GetTrainsCount(void);
    //TKroshTrainInfo * __fastcall TN_GetTrainsInfo(int ind);


    int  __fastcall MK_SetInputBuf(void * buf, int maxchanels);
    bool __fastcall MK_SetInputBufChanel(void * buf, int ChanelNumber);
    TMKMarshAll * __fastcall MK_GetStan(const char * StanFN);

    int  __fastcall SI_SetInputBuf(void * buf, int maxchanels);
    bool __fastcall SI_SetInputBufChanel(void * buf, int ChanelNumber);
    TAVStanInfo * __fastcall SI_GetStan(const char * StanFN);

    int  __fastcall EI_SetInputBuf(void * buf, int maxchanels);
    bool __fastcall EI_SetInputBufChanel(void * buf, int ChanelNumber);
    TElemCheckState * __fastcall EI_GetEI(const char * StanFN, int obj_id);
    TElemCheckState * __fastcall EI_GetEINext(const char * StanFN, int obj_id,TElemCheckState *EI0);


};

extern TEXD /*_ALIB_*/ EXD;

#endif
