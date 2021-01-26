//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uETTList.h"
#include "uParString.h"
#include <inifiles.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)



char * ETTSectName[4]={"YZ_GRAF","RV_MARSHRUT","RV_MACRO","NB_GORKA"};
const par_Enabled=0;
const par_EventType_Class=1;
const par_EventType_ID=2;
const par_EventType_NAME=3;
const par_ID_OBJ=4;
const par_ObjName=5;
const par_iMacro=6;
const par_DateUnEnabled=7;
const par_UsedData=8;
const par_ExtData=9;
const par_Dest=10;
const par_Act=11;
const par_TOShow=12;
const par_Sound=13;
const par_Kvit=14;
const par_DestNames=15;
const par_Speak=16;








String TETTListItem::ToString()
{
       TParString wordsline("",";",false);
       wordsline.SetInt(par_Enabled,Enabled);
       wordsline.SetInt(par_EventType_Class,EventType_Class);
       wordsline.SetInt(par_EventType_ID,_EventType_ID);
       wordsline.SetStr(par_EventType_NAME,EventType_NAME);
       wordsline.SetInt(par_ID_OBJ,ID_OBJ);
       wordsline.SetStr(par_ObjName,ObjName);
       wordsline.SetInt(par_iMacro,iMacro);
       wordsline.SetStr(par_DateUnEnabled,DateUnEnabled);
       wordsline.SetStr(par_UsedData,UsedData);
       wordsline.SetStr(par_ExtData,ExtData);
       wordsline.SetInt(par_Dest,Dest);
       wordsline.SetInt(par_Act,Act);
       wordsline.SetInt(par_TOShow,TOShow);
       wordsline.SetInt(par_Sound,Sound);
       wordsline.SetInt(par_Kvit,Kvit);
       wordsline.SetStr(par_DestNames,DestNames);
       wordsline.SetInt(par_Speak,Speak);
       return wordsline.ResultStr();
}
void TETTListItem::FromString(String ST)
{
       TParString wordsline("",";",false);
       wordsline.SetVal(ST);

       Enabled=        wordsline.GetInt(par_Enabled);
       EventType_Class=(TEventType_Class)(wordsline.GetInt(par_EventType_Class));
       _EventType_ID=   wordsline.GetInt(par_EventType_ID);
       EventType_NAME= wordsline.GetStr(par_EventType_NAME);
       ID_OBJ=         wordsline.GetInt(par_ID_OBJ);
       ObjName=        wordsline.GetStr(par_ObjName);
       iMacro=         wordsline.GetInt(par_iMacro,0);
       DateUnEnabled=  wordsline.GetStr(par_DateUnEnabled);
       UsedData=       wordsline.GetStr(par_UsedData);
       ExtData=        wordsline.GetStr(par_ExtData);
       Dest=           (TEventDest_Class)wordsline.GetInt(par_Dest,dAll);
       Act=            (TEventAction_Class)wordsline.GetInt(par_Act,act1);
       TOShow=         wordsline.GetInt(par_TOShow,0);
       Sound=          wordsline.GetInt(par_Sound,0);
       Kvit=           wordsline.GetInt(par_Kvit,0);
       DestNames=      wordsline.GetStr(par_DestNames);
       Speak=           wordsline.GetInt(par_Speak,0);
}



__fastcall TETTList::TETTList()
{
        UsedFileName="";
        RusStanName="";
        su_str="";
        ru_str="";
}

bool TETTList::Load(String FN)
{
     if (!FileExists(FN)){
        ShowMessage("Не могу найти "+FN); return false;
     }
     UsedFileName=FN;
     TMemIniFile * FI= new TMemIniFile(FN);

     vETTList.clear();

     TETTListItem ELI;
     String ST;

     // COMMON
     RusStanName=FI->ReadString("COMMON","RusStanName",RusStanName);
     ru_str=FI->ReadString("COMMON","ru_str","");
     su_str=FI->ReadString("COMMON","su_str","");
     for (int etc=0;etc<4;etc++){
         int cnt=FI->ReadInteger(ETTSectName[etc],"Кол-во",0);
         for (int i=0;i<cnt;i++){
             ST=FI->ReadString(ETTSectName[etc],IntToStr(i+1),"");
             if (ST=="") continue;
             ELI.FromString(ST);
             vETTList.push_back(ELI);
         }
     }
     delete FI;
     return true;
}

bool  TETTList::Save(String FN)
{
     TMemIniFile * FI= new TMemIniFile(FN);

     TETTListItem *pELI;
     String ST;
     FI->WriteString("COMMON","RusStanName",RusStanName);
     if (ru_str!="")FI->WriteString("COMMON","ru_str",ru_str);
     if (su_str!="") FI->WriteString("COMMON","su_str",su_str);

     for (int etc=0;etc<4;etc++){
         int cnt=0;
         FI->EraseSection(ETTSectName[etc]);
         for (unsigned int i=0;i<vETTList.size();i++){
             pELI=&vETTList[i];
             if (pELI->EventType_Class!=etc) continue;
             cnt++;
             ST=pELI->ToString();

             FI->WriteString(ETTSectName[etc],IntToStr(cnt),ST);
         }
         if (cnt>0)
                FI->WriteInteger(ETTSectName[etc],"Кол-во",cnt);
     }
     FI->UpdateFile();
     delete FI;
     return true;


}

TETTListItem * TETTList::AddItem(TETTListItem * ELI)
{
        vETTList.push_back(*ELI);
        return ELI;

}

void TETTList::EraseItem(TETTListItem * ELI)
{
        vETTList.erase(ELI);
}

TETTListItem * TETTList::AddItem(bool AEnabled,
                            TEventType_Class AEventType_Class,
                            unsigned int AEventType_ID,
                            String AEventType_NAME,
                            unsigned int AID_OBJ,
                            String AObjName,
                            int AiMacro,
                            String AUsedData,
                            String AExtData)
{
     TETTListItem ELI;
     ELI.Enabled = AEnabled;
     ELI.EventType_Class = AEventType_Class;
     ELI._EventType_ID = AEventType_Class;
     ELI.EventType_NAME =AEventType_NAME;
     ELI.ID_OBJ = AID_OBJ;
     ELI.ObjName = AObjName;
     ELI.iMacro = AiMacro;
     ELI.DateUnEnabled="";
     ELI.UsedData=AUsedData;
     ELI.ExtData=AExtData;

     vETTList.push_back(ELI);
     return &vETTList[vETTList.size()-1];
}

TETTListItem * TETTList::FindItem(
                            unsigned int AEventType_ID,
                            unsigned int AID_OBJ)
{

     TETTListItem *pELI;
     String ST;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI=&vETTList[i];
         if (
             (pELI->_EventType_ID==AEventType_ID)&&
             (pELI->ID_OBJ==AID_OBJ))
          {
            return pELI;
          }
     }
     return NULL;
}

TETTListItem * TETTList::FindItem(TEventType_Class AEventType_Class,
                            unsigned int AEventType_ID,
                            unsigned int AID_OBJ)
{

     TETTListItem *pELI;
     String ST;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI=&vETTList[i];
         if (/*(pELI->EventType_Class==AEventType_Class)&&*/
             (pELI->_EventType_ID==AEventType_ID)&&
             (pELI->ID_OBJ==AID_OBJ))
          {
            return pELI;
          }
     }
     return NULL;
}


void TETTList::EraseItems(TEventType_Class AEventType_Class)
{
     TETTListItem *pELI;
     String ST;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI=&vETTList[i];
         //vETTList_t::iterator f = &vETTList.at(i);
         if (pELI->EventType_Class==AEventType_Class) {
            vETTList.erase(pELI);
            i--;
         }
     }
}


TETTListItem * __fastcall TETTList::GetItems(int ind)
{
         return &vETTList[ind];
}

int __fastcall TETTList::GetItemsCount()
{
        return vETTList.size();
}

int TETTList::MergeItems(TETTList * ETTList2,TEventType_Class AEventType_Class)
{
     TETTListItem *pELI1;
     TETTListItem *pELI2;
     String ST;
     int cntupd=0;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI1=&vETTList[i];
         if ((pELI1->EventType_Class!=AEventType_Class)&&(AEventType_Class!=-1)) continue;
         pELI2=ETTList2->FindItem(pELI1->EventType_Class,pELI1->_EventType_ID,pELI1->ID_OBJ);
         if (pELI2!=NULL){
            // вносим старые данные элемента
               pELI1->Enabled=pELI2->Enabled;
               pELI1->ObjName=pELI2->ObjName;
               // бля не забудь переписать- переписал
               pELI1->Dest=pELI2->Dest;
               pELI1->Act=pELI2->Act;
               pELI1->TOShow=pELI2->TOShow;
               pELI1->DestNames=pELI2->DestNames;
               cntupd++;
         }
     }
     return cntupd;

}
int TETTList::MergeItems(TETTList * ETTList2)
{
    return MergeItems(ETTList2,(TEventType_Class)-1);
}

bool TETTList::Like(TETTList * ETTList2)
{
     TETTListItem *pELI1;
     TETTListItem *pELI2;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI1=&vETTList[i];
         pELI2=ETTList2->FindItem(pELI1->EventType_Class,pELI1->_EventType_ID,pELI1->ID_OBJ);
         if (pELI2!=NULL){
               if (pELI1->Enabled!=pELI2->Enabled) return false;
               if (pELI1->ObjName!=pELI2->ObjName) return false;
               if (pELI1->EventType_NAME!=pELI2->EventType_NAME) return false;
         } else return false;

     }
     return true;

}

int TETTList::GetItemsCountSect(TEventType_Class C)
{
     TETTListItem *pELI1;
     int cnt=0;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI1=&vETTList[i];
         if (pELI1->EventType_Class!=C)continue;
         cnt++;
     }
     return cnt;
}

TETTListItem * TETTList::GetItemSect(TEventType_Class C, int ind)
{
     int cnt=0;
     TETTListItem *pELI1;
     for (unsigned int i=0;i<vETTList.size();i++){
         pELI1=&vETTList[i];
         if (pELI1->EventType_Class!=C)continue;
         if (cnt==ind) return pELI1;
         cnt++;
     }
     return NULL;
}

String GetETTLISTFileName(String STAFN)
{
     String ETTListFN=ExtractFileName(STAFN);
     ETTListFN=ChangeFileExt(ETTListFN,".ettlist");
     ETTListFN=/*PrevDir(STAFN)*/ExtractFileDir(STAFN)+"\\..\\ETT\\"+ETTListFN;
     return ETTListFN;
}

void TETTList::Clear()
{
     vETTList.clear();
}
