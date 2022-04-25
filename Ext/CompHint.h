#ifndef CompHintH
#define CompHintH

#include "aheaders_h.h"
#include <time.h>

class Station;
class AComp;

class TACOMPHINT
{
  struct HintItem
  {
    char filename[13];
    String stHint;
    String stDest;
    int ID;
    int Type; // 1 À, 2 Ï , 3Í
    int TOsec;
    time_t Time_Begin;
    AComp* ac;
    int acX, acY;
    RECT acRECT;
    int WW, HH;
    // bool bUseEttSettings;
    // bool bEttSettingsLoaded;
    int EventType_ID;
  };

  typedef std::vector<HintItem> items_type;
  items_type items;

  void _ShowHint(AComp* ac, HintItem& hi, bool bFON = false);

public:
  int WidthDef;
  int HeightDef;
  int FontSize;

  TACOMPHINT();
  void AddHint(const char* sta_filename, int ID, const char* stHint, int Type, int TOsec, const char* Dest);
  void AddHint(int ID, const char* stHint, int Type, int TOsec, char* Dest) { AddHint("", ID, stHint, Type, TOsec, Dest); }
  void ShowHints(Station* stan);
  void HideHint(const char* sta_filename, int ID);
  void HideHint(int ID) { HideHint("", ID); };
  void HideAll();
};
extern TACOMPHINT ACOMPHINT;

#endif
