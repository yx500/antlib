//---------------------------------------------------------------------------

#ifndef CompHintH
#define CompHintH
//---------------------------------------------------------------------------

struct tACHintItem;
class Station;
class AComp;

class TACOMPHINT
{
private:

protected:
       void _ShowHint(AComp* ac,tACHintItem *hi,bool bFON=false);

public:
       int WidthDef;
       int HeightDef;
       int FontSize;

       TACOMPHINT();
       void AddHint(char * sta_filename,int ID,const char *stHint,int Type,int TOsec,const char * Dest);
       void AddHint(int ID,const char *stHint,int Type,int TOsec,char * Dest){AddHint("",ID,stHint,Type,TOsec,Dest);}
       void ShowHints(Station * stan);
       void HideHint(char * sta_filename,int ID);
       void HideHint(int ID){HideHint("",ID);};
       void HideAll();


};
extern TACOMPHINT ACOMPHINT;

#endif
