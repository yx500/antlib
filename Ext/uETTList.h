//---------------------------------------------------------------------------

#ifndef uETTListH
#define uETTListH
//---------------------------------------------------------------------------

#include <vector>

enum TEventType_Class {YZ_GRAF=0,RV_MARSHRUT=1,RV_MACRO=2,NB_GORKA=3};
enum TEventDest_Class {dAll=0,dDNC=1,dSHCD=2};                        //  ;���� '���' - ���� '���'- ��� '���' - ���              (yxDEST = 0,1,2)
enum TEventAction_Class {act0=0,act1=1,act2=2,act3=3,act11=11};       //��� '�'-��������� '�'-�������������� '�'-�����������  (yxACTION=1,2,3)


class TETTListItem
{
  public:
   bool Enabled;                     // ���(1)/����(0)
   TEventType_Class EventType_Class; // ID ������ ���������
   unsigned int _EventType_ID;        // ID ���� ��������� - ���������� ��� ���� 3 ������� ���������
   String EventType_NAME;            // ��� ���� ��������� - ��� Claba, �� ����� ���������!
   unsigned int ID_OBJ;              // ID_OBJ , ��� �������� �����. NUM_COM
   String ObjName;                   // ��� ������� , ���� ����� - ����� �� ���������

   int iMacro;                       // ����� ������� � ������� �������� ��������
   String DateUnEnabled;             // ����� ������ � ��������
   String UsedData;                  // ������������ ������ ��� ������
   String ExtData;                   // ������������ ������

   TEventDest_Class Dest;            // ���������� ��������� �� ���������
   String DestNames;                 // ����� �������� ����������� ����� ������ ,* -  ���
   TEventAction_Class Act;

   int TOShow;                        // ����� ����������� ���������
   int Sound;                         // ����
   bool Kvit;                         // �����������
   bool Speak;                         // ����

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

     //int ru_imp, su_imp; // ��� �������� ��� �����!
     //int ru_fimp, su_fimp; // �������� ��������� MKS

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
