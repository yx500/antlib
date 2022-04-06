#include "aheaders_cpp.h"

#include <algorithm>
#include <string>
#include <vector>
#include <time.h>

#include "CompHint.h"
#include "Stan.h"
#include "Elem.h"
#include "APch.h"
//---------------------------------------------------------------------------

TACOMPHINT ACOMPHINT;

TACOMPHINT::TACOMPHINT()
{
    WidthDef = 300;
    HeightDef = 60;
    FontSize = 16;
}

void TACOMPHINT::AddHint(const char *sta_filename, int ID, const char *stHint, int Type, int TOsec, const char *Dest)
{
    HintItem ACHintItem;
    // ������� ��� ������ ����
    strncpy(ACHintItem.filename, sta_filename, 13);
    ACHintItem.stHint = stHint;
    ACHintItem.ID = ID;
    ACHintItem.Type = Type; // 1 �, 2 � , 3�
    ACHintItem.TOsec = TOsec;
    ACHintItem.Time_Begin = time(NULL);
    ACHintItem.ac = NULL;
    ACHintItem.acX = 0, ACHintItem.acY = 0;
    ACHintItem.stDest = Dest;

    items.push_back(ACHintItem);
}

/*void TACOMPHINT::AddEttHint(char * sta_filename,int ID,int EventType_ID,const char *stHint,int Type,int TOsec,char * Dest)
{
     HintItem ACHintItem;
     // ������� ��� ������ ����
     strncpy(ACHintItem.filename,sta_filename,13);
     ACHintItem.stHint=stHint;
     ACHintItem.stDest=Dest;
     ACHintItem.ID=ID;
     ACHintItem.Type=Type; // 1 �, 2 � , 3�
     ACHintItem.TOsec=TOsec;
     ACHintItem.Time_Begin=time(NULL);
     ACHintItem.ac=NULL;
     ACHintItem.acX=0,ACHintItem.acY=0;
     //ACHintItem.bUseEttSettings=true;
     //ACHintItem.bEttSettingsLoaded=false;
     ACHintItem.EventType_ID=EventType_ID;

     items.push_back(ACHintItem);
}
*/

void TACOMPHINT::HideHint(const char *sta_filename, int ID)
{
    for (unsigned int i = 0; i < items.size(); i++)
    {
        HintItem &hint = items[i];
        if ((strncmp(hint.filename, sta_filename, sizeof(hint.filename)) == 0) || (strlen(hint.filename) == 0))
        {
            if (hint.ID == ID)
                hint.TOsec = 5;
        }
    }
}

void TACOMPHINT::HideAll()
{
    items.clear();
}

void TACOMPHINT::ShowHints(Station *stan)
{
    // ������� ������ ������
    time_t now;
    now = time(NULL);
    for (items_type::iterator hi = items.begin(); hi != items.end(); ++hi)
    {
        if (now - hi->Time_Begin >= hi->TOsec)
        {
            // �������� �����
            if (hi->ac != NULL)
                _ShowHint(hi->ac, *hi, true);
            items.erase(hi);
            hi--;
        }
    }

    // ��������� ��������� �� �� ETT, � ��������� EttReciveName
    std::string stDestYch = stan->AO->EttReciveName;
    for (items_type::iterator hi = items.begin(); hi != items.end(); ++hi)
    {
        if (hi->stDest != "*")
        {
            if ((stDestYch.length() != 0) && (hi->stDest.find(stDestYch) == std::string::npos))
            {
                items.erase(hi);
                hi--;
            }
        }
    }

    if (items.size() > 0)
    {
        AComp *ac;
        for (int i = Units_Size - 1; i >= 1; i--)
        {
            for (int i = 0; i < Units_Size; i++)
            {
                for (int j = 0; j < stan->POLE[i]->GetArraySize(); j++)
                {
                    ac = stan->POLE[i]->GetObjPtr(j);
                    if (((ac->ExtPriz.NoShowYch == 1) && (CurrentPicture == BG)) ||
                        ((ac->ExtPriz.NoShowStan == 1) && (CurrentPicture == LT)))
                        continue;
                    for (unsigned int v = 0; v < items.size(); v++)
                    {
                        HintItem &hi = items[v];
                        if ((ac->ID == hi.ID) &&
                            ((strncmp(stan->Dat->filename, hi.filename, sizeof(stan->Dat->filename)) == 0) || (strlen(hi.filename) == 0)))
                        {
                            _ShowHint(ac, hi);
                            hi.ac = ac;
                        }
                    }
                }
            }
        }
    }
}

char *PN[3] = {"IMCH", "IMLH", "IMRH"};
void TACOMPHINT::_ShowHint(AComp *ac, HintItem &hi, bool bFON)
{
    // ��������� ���������
    if (ac != hi.ac)
    {
        hi.ac = ac;
        _SetText(TIMES20b, LEFT_TEXT, TOP_TEXT);
        _SetTextSize(FontSize);
        hi.WW = textwidth(hi.stHint.c_str()) + 4;
        hi.HH = textheight(hi.stHint.c_str());
        hi.HH = hi.HH + hi.HH / 4;
        if (hi.WW < WidthDef)
            hi.WW = WidthDef;
        if (hi.HH < HeightDef)
            hi.HH = HeightDef;
        _SetTextSize(1);
    }
    // ���������� �� ����������?
    if ((hi.acX != ac->X * MUL_X + _X_) ||
        (hi.acY != ac->Y * MUL_Y + _Y_))
    {
        hi.acX = ac->X * MUL_X + _X_;
        hi.acY = ac->Y * MUL_Y + _Y_;
        // ������� ����
        hi.acRECT = ClearBgiCoverRect();
        ac->Show();
        hi.acRECT = GetBgiCoverRect();
    }
    if (hi.acRECT.left == 0x7fffffff)
        return; // ���� ��� �� ������
    int pallign = 1;
    int X = (hi.acRECT.left + hi.acRECT.right) / 2;
    int Y = (hi.acRECT.top + hi.acRECT.bottom) / 2;
    if (X + hi.WW > ac->Stan()->AO->MaxX)
        pallign = 2;
    if (Y - hi.HH < 0)
        Y = hi.HH;

    if (pallign == 1)
        X = X;
    else if (pallign == 2)
        X = X - hi.WW;
    else
        X = X + hi.WW / 2;
    RECT RCT;
    RCT.left = X;
    RCT.right = X + hi.WW;
    RCT.top = Y - hi.HH;
    RCT.bottom = Y;
    if (bFON)
    {
        setcolor(FON);
        setfillstyle(1, FON);
        rectangle(RCT.left, RCT.top, RCT.right, RCT.bottom);
    }
    else
    {
        drawemf(&RCT, PN[pallign], CommonAnimationStep % 2);
        int clr = C_D;
        switch (hi.Type)
        {
        case 0:
            clr = C_D;
            break;
        case 1:
            clr = KRA;
            break;
        case 2:
            clr = C_D;
            break;
        case 3:
            clr = ZEL;
            break;
        }
        setcolor(clr);
        _SetText(TIMES20b, CENTER_TEXT, CENTER_TEXT);
        _SetTextSize(FontSize);
        DrawText(RCT.left, RCT.top, hi.WW, hi.HH - hi.HH / 4, hi.stHint.c_str());
    }
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);
    _SetTextSize(1);
}
