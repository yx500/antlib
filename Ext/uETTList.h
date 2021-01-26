//---------------------------------------------------------------------------

#ifndef uETTListH
#define uETTListH
//---------------------------------------------------------------------------

#include <vector>

enum TEventType_Class {YZ_GRAF=0,RV_MARSHRUT=1,RV_MACRO=2,NB_GORKA=3};
enum TEventDest_Class {dAll=0,dDNC=1,dSHCD=2};                        //  ;КУДА 'ВСЕ' - ВСЕМ 'ДНЦ'- ДНЦ 'ШЧД' - ШЧД              (yxDEST = 0,1,2)
enum TEventAction_Class {act0=0,act1=1,act2=2,act3=3,act11=11};       //ТИП 'А'-АВАРИЙНОЕ 'П'-ПРЕДУПРЕЖЖДЕИЕ 'Н'-НОТИФИКАЦИЯ  (yxACTION=1,2,3)


class TETTListItem
{
  public:
   bool Enabled;                     // Вкл(1)/Выкл(0)
   TEventType_Class EventType_Class; // ID класса обработки
   unsigned int _EventType_ID;        // ID типа обработки - уникальный для всех 3 классов обработки
   String EventType_NAME;            // Имя типа обработки - для Claba, не текст сообщения!
   unsigned int ID_OBJ;              // ID_OBJ , для маршрута соотв. NUM_COM
   String ObjName;                   // Имя объекта , если пусто - брать по умолчанию

   int iMacro;                       // Номер строчки в таблице описаний макросов
   String DateUnEnabled;             // Время снятия с проверки
   String UsedData;                  // Используемые данные для отчета
   String ExtData;                   // Используемые данные

   TEventDest_Class Dest;            // получатель сообщений по умолчанию
   String DestNames;                 // Имена обьектов получателей через пробел ,* -  все
   TEventAction_Class Act;

   int TOShow;                        // время отображения сообщения
   int Sound;                         // Звук
   bool Kvit;                         // Квитировать
   bool Speak;                         // Речь

   TETTListItem(){};
   virtual ~TETTListItem(){};

   String ToString();
   void FromString(String ST);

};

class TETTList
{
     //typedef std::map<int,TETTListItem>   mETTList_t;
     //typedef mETTList_t::iterator itELI;
     //mETTList_t                   mETTList;

     typedef std::vector<TETTListItem> vETTList_t;
     vETTList_t                   vETTList;

  public:
     String UsedFileName;
     String RusStanName;
     bool         Load(String FN);
     bool         Save(String FN);

     String su_str;
     String ru_str;

     //int ru_imp, su_imp; // при загрузке уже будут!
     //int ru_fimp, su_fimp; // Значение проставит MKS

     __fastcall TETTList();
     TETTListItem * AddItem(TETTListItem * ELI);
     void EraseItem(TETTListItem * ELI);
     TETTListItem * AddItem(bool AEnabled,
                            TEventType_Class AEventType_Class,
                            unsigned int AEventType_ID,
                            String AEventType_NAME,
                            unsigned int AID_OBJ,
                            String AObjName,
                            int AiMacro,
                            String AUsedData,
                            String AExtData);
      TETTListItem * FindItem(TEventType_Class AEventType_Class,
                            unsigned int AEventType_ID,
                            unsigned int AID_OBJ);
      TETTListItem * FindItem(
                            unsigned int AEventType_ID,
                            unsigned int AID_OBJ);
      int GetItemsCountSect(TEventType_Class C);
      TETTListItem * GetItemSect(TEventType_Class C, int ind);
      void EraseItems(TEventType_Class AEventType_Class);
      int MergeItems(TETTList * ETTList2,TEventType_Class AEventType_Class);
      int MergeItems(TETTList * ETTList2);
      bool Like(TETTList * ETTList2);
      void Clear();



        __property TETTListItem * Items[int ind]  = { read=GetItems };
        __property int ItemsCount  = { read=GetItemsCount };
private:
        TETTListItem * __fastcall GetItems(int ind);
        int __fastcall GetItemsCount();

};


//extern String ETTSectName[];
extern char * ETTSectName[];
String GetETTLISTFileName(String STAFN);


#endif
