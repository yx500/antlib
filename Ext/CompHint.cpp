//---------------------------------------------------------------------------

#include "aheaders_cpp.h"
#include <string>
#include <vector>
#include <time.h>

#include "CompHint.h"
#include "Stan.h"
#include "Elem.h"
#include "APch.h"
//---------------------------------------------------------------------------



TACOMPHINT ACOMPHINT;

struct tACHintItem{
       char filename[13];
       std::string stHint;
       std::string stDest;
       int ID;
       int Type; // 1 А, 2 П , 3Н
       int TOsec;
       time_t Time_Begin;
       AComp * ac;
       int acX,acY;
       RECT acRECT;
       int WW,HH;
       //bool bUseEttSettings;
       //bool bEttSettingsLoaded;
       int EventType_ID;
};

std::vector <tACHintItem> vACHintItems;

TACOMPHINT::TACOMPHINT()
{
   WidthDef=300;
   HeightDef=60;
   FontSize=16;
}

void TACOMPHINT::AddHint(char * sta_filename,int ID,const char *stHint,int Type,int TOsec,const char * Dest)
{
     tACHintItem ACHintItem;
     // считаем что обьект есть
     strncpy(ACHintItem.filename,sta_filename,13);
     ACHintItem.stHint=stHint;
     ACHintItem.ID=ID;
     ACHintItem.Type=Type; // 1 А, 2 П , 3Н
     ACHintItem.TOsec=TOsec;
     ACHintItem.Time_Begin=time(NULL);
     ACHintItem.ac=NULL;
     ACHintItem.acX=0,ACHintItem.acY=0;
     ACHintItem.stDest=Dest;

     vACHintItems.push_back(ACHintItem);
}

/*void TACOMPHINT::AddEttHint(char * sta_filename,int ID,int EventType_ID,const char *stHint,int Type,int TOsec,char * Dest)
{
     tACHintItem ACHintItem;
     // считаем что обьект есть
     strncpy(ACHintItem.filename,sta_filename,13);
     ACHintItem.stHint=stHint;
     ACHintItem.stDest=Dest;
     ACHintItem.ID=ID;
     ACHintItem.Type=Type; // 1 А, 2 П , 3Н
     ACHintItem.TOsec=TOsec;
     ACHintItem.Time_Begin=time(NULL);
     ACHintItem.ac=NULL;
     ACHintItem.acX=0,ACHintItem.acY=0;
     //ACHintItem.bUseEttSettings=true;
     //ACHintItem.bEttSettingsLoaded=false;
     ACHintItem.EventType_ID=EventType_ID;

     vACHintItems.push_back(ACHintItem);
}
*/


void TACOMPHINT::HideHint(char * sta_filename,int ID)
{
     for (unsigned int i=0;i<vACHintItems.size();i++){
         tACHintItem *hi=&vACHintItems[i];
         if ((strncmp(hi->filename,sta_filename,sizeof(hi->filename))==0)||(strlen(hi->filename)==0)){
            if (hi->ID==ID){
               hi->TOsec=5;
            }
         }
     }
}

void TACOMPHINT::HideAll()
{
     vACHintItems.clear();
}


void TACOMPHINT::ShowHints(Station * stan)
{
     // сначала уберем старье
     time_t now;
     now = time(NULL);
     for (unsigned int i=0;i<vACHintItems.size();i++){
         tACHintItem *hi=&vACHintItems[i];
         if (now-hi->Time_Begin>=hi->TOsec){
            // затираем фоном
            if (hi->ac!=NULL)
               _ShowHint(hi->ac,hi,true);
            vACHintItems.erase(hi);
            i--;
         }
     }

     // проставим параметры не из ETT, а сравнивая EttReciveName

     std::string stDestYch=stan->AO->EttReciveName;
     for (unsigned int i=0;i<vACHintItems.size();i++){
         tACHintItem *hi=&vACHintItems[i];
         if (hi->stDest!="*"){
            if ((stDestYch.length()!=0)&&(hi->stDest.find(stDestYch)==std::string::npos)){
                  vACHintItems.erase(hi);
                  i--;
            }
         }
     }


     if (vACHintItems.size()>0) {
         AComp *ac;
         for (int i = Units_Size - 1; i >= 1; i--) {
             for (int i = 0; i < Units_Size; i++) {
                 for (int j = 0; j < stan->POLE[i]->GetArraySize(); j++) {
                        ac = stan->POLE[i]->GetObjPtr(j);
                        if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                            ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT))) continue;
                        for (unsigned int v=0;v<vACHintItems.size();v++){
                            tACHintItem *hi=&vACHintItems[v];
                            if ((ac->ID== hi->ID)&&
                                ((strncmp(stan->Dat->filename,hi->filename,sizeof(stan->Dat->filename))==0)||(strlen(hi->filename)==0))
                            ){

                                    _ShowHint(ac,hi);
                                    hi->ac=ac;
                            }
                        }
                 }
             }
         }
     }

}
char *PN[3]={"IMCH","IMLH","IMRH"};
void TACOMPHINT::_ShowHint(AComp* ac,tACHintItem *hi,bool bFON)
{
     // начальная установка
     if (ac!=hi->ac){
        hi->ac=ac;
        _SetText(TIMES20b, LEFT_TEXT, TOP_TEXT);
        _SetTextSize(FontSize);
        hi->WW=textwidth(hi->stHint.c_str())+4;
        hi->HH=textheight(hi->stHint.c_str());
        hi->HH=hi->HH+hi->HH/4;
        if (hi->WW<WidthDef) hi->WW=WidthDef;
        if (hi->HH<HeightDef) hi->HH=HeightDef;
        _SetTextSize(1);
     }
     // Изменились ли координаты?
     if ((hi->acX!=ac->X * MUL_X + _X_)||
         (hi->acY!=ac->Y * MUL_Y + _Y_)){
        hi->acX =ac->X * MUL_X + _X_;
        hi->acY =ac->Y * MUL_Y + _Y_;
        // находим рект
        hi->acRECT=ClearBgiCoverRect();
        ac->Show();
        hi->acRECT=GetBgiCoverRect();
     }
     if (hi->acRECT.left==MaxInt) return; // типа нет на экране
     int pallign=1;
     int X=(hi->acRECT.left+hi->acRECT.right)/2;
     int Y=(hi->acRECT.top+hi->acRECT.bottom)/2;
     if (X+hi->WW>ac->Stan()->AO->MaxX) pallign=2;
     if (Y-hi->HH<0) Y=hi->HH;

     if (pallign==1)
           X=X; else
     if (pallign==2)
           X=X-hi->WW; else
           X=X+hi->WW/2;
     RECT RCT;
     RCT.left=X;RCT.right=X+hi->WW;RCT.top=Y-hi->HH;RCT.bottom=Y;
     if (bFON){
        setcolor(FON);
        setfillstyle(1,FON);
        rectangle(RCT.left, RCT.top, RCT.right, RCT.bottom);
     } else {
        drawemf(&RCT, PN[pallign], CommonAnimationStep % 2);
        int clr=C_D;
        switch (hi->Type){
          case 0: clr=C_D; break;
          case 1: clr=KRA; break;
          case 2: clr=C_D; break;
          case 3: clr=ZEL; break;
        }
        setcolor(clr);
        _SetText(TIMES20b, CENTER_TEXT, CENTER_TEXT);
        _SetTextSize(FontSize);
        DrawText(RCT.left, RCT.top, hi->WW, hi->HH-hi->HH/4, (char*)hi->stHint.c_str());
     }
     _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);_SetTextSize(1);
}
