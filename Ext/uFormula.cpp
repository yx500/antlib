//---------------------------------------------------------------------------


#include "aheaders_cpp.h"

#include "uFormula.h"

#include <algorithm>
#include <iterator>
#include "Impuls.h"
#include "Comp.h"
//---------------------------------------------------------------------------



// уровень операции
int _levst(long v)
{
    switch (v) {
    case _CI: return 1;//"(";
    case _AN: return 3;//"&";
    case _OR: return 2;//"^";
    case _NT: return 4;//"!";

    case _PL: return 2;//"+";
    case _MN: return 2;//"-";
    case _MU: return 3;//"*";
    case _DV: return 3;//"*";
    default :
        return 99;
    }
}


// ставим номер ТС
void fevFormulaSetlVal(TvFormulaElement & vFormulaElement)
{
    for (TvFormulaElement::iterator i = vFormulaElement.begin(); i != vFormulaElement.end(); ++i) {
        if (i->Tip == 1) {
            // если не число то ТС
            i->lVal = StrToIntDef(i->szVal, -12345);
            if (i->lVal != 12345) {
                i->Tip = 2;
                i->R = i->lVal;
            } else
                i->lVal = NewStrToOldImp(i->szVal);
        }  else {
            i->lVal = i->Tip;

        }
    }
}

// ставим значение ТС
void fevFormulaSetR(AComp * ac, TvFormulaElement & vFormulaElement)
{
    for (TvFormulaElement::iterator i = vFormulaElement.begin(); i != vFormulaElement.end(); ++i) {
        if (i->Tip == 1) {
            i->R = ac->f(i->lVal);
        }
    }
}


int _stf(char ch)
{
    switch (ch) {
    case '(': return _CI;
    case ')': return _CO;
    case '&': return _AN;
    case '^': return _OR;
    case '!': return _NT;

    case '+': return _PL;
    case '-': return _MN;
    case '*': return _MU;
    case '/': return _DV;
    default :

        return 1;

    }
}

int _feOP(int OPTip, int R1, int R2)
{
    switch (OPTip) {
    case _AN: return R1 && R2;//"&";
    case _OR: return R1 || R2;;//"^";
    case _NT: if (R1==0) return 1; else  return 0;//"!";

    case _PL: return R1 + R2;;//"+";
    case _MN: return R2 - R1;;//"-";
    case _MU: return R1 * R2;;//"*";
    case _DV: return R2 / R1;;//"/";


    default :
        return 33;
    }

}

int feRFormula(TvFormulaElement & vFormulaElement, int &N)
{
    int R1, R2;
    if (N < 0) return 33;
    TFormulaElement &feOp = vFormulaElement.at(N) ;
    N--;
    // если текущий знгачение - выдаем значение
    if (feOp.Tip == 1) return feOp.R;
    // если текущий цифра - выдаем значение
    if (feOp.Tip == 2) return feOp.R;
    // если операция - собираем переменные
    R1 = feRFormula(vFormulaElement, N);
    if (feOp.Tip == _NT) return _feOP(feOp.Tip, R1, 0);
    R2 = feRFormula(vFormulaElement, N);
    return _feOP(feOp.Tip, R1, R2);
}

void feSt2vFormula(const char * szFormula, TvFormulaElement & vFormulaElement)
{
    std::string st(szFormula);
    TFormulaElement fe;
    vFormulaElement.clear();
    int N = 1;
    std::string st1 = "";
    memset(&fe, 0, sizeof(fe));
    for (unsigned int i = 0; i < st.length(); i++) {
        if (_stf(st[i]) < 0) { // операция
            // если предидущий значенин вносим
            if (fe.Tip == 1) {
                strncpy(fe.szVal, st1.c_str(), sizeof(fe.szVal));
                vFormulaElement.push_back(fe);
                memset(fe.szVal, 0, sizeof(fe.szVal));
                N++;
                st1 = "";
            }
            fe.Tip = _stf(st[i]);
            fe.szVal[0] = st[i];
            fe.N = N;
            vFormulaElement.push_back(fe);
            N++;
            memset(fe.szVal, 0, sizeof(fe.szVal));
        } else {

            fe.Tip = 1;
            fe.N = N;
            st1 += st[i];

        }
    }
    if (fe.Tip == 1) {
        strncpy(fe.szVal, st1.c_str(), sizeof(fe.szVal));
        vFormulaElement.push_back(fe);
    }
    // ставим номер ТС
    fevFormulaSetlVal(vFormulaElement);

}

const char * fevFormula2St(TvFormulaElement & vFormulaElement)
{
    static std::string szout = "";
    szout = "";
    for (TvFormulaElement::iterator i = vFormulaElement.begin(); i != vFormulaElement.end(); ++i)
        szout += i->szVal;
    return szout.c_str();
}

const char * fevFormula2StN(TvFormulaElement & vFormulaElement)
{

    static std::string szout = "";
    szout = "";
    TAImpuls IMP;
    for (TvFormulaElement::iterator i = vFormulaElement.begin(); i != vFormulaElement.end(); ++i) {
        if (i->Tip == 1) {
            IMP.FromString(i->szVal);
            szout += IMP.ImpName;
        } else {
            szout += i->szVal;
        }
    }

    return szout.c_str();

}

const char * feGetSimpleFormula(const char * szFormula)
{
    TvFormulaElement vFormulaElement;
    feSt2vFormula(szFormula, vFormulaElement);
    return fevFormula2StN(vFormulaElement);
}



//---------------------------------------------------------------------------
int fevFormulaElement2PolskaNota(TvFormulaElement & vFormulaElement, TvFormulaElement & vFormulaElementP)
{
    //TvFormulaElement  vFormulaElement1;
    TsFormulaElement  vStack;
    //feSt2vFormula(st.c_str(),vFormulaElement1);
    bool bSCok;

    vFormulaElementP.clear();
    for (TvFormulaElement::iterator i = vFormulaElement.begin(); i != vFormulaElement.end(); ++i) {
        if (i->Tip != 1) {
            // Если очеpедной символ - ')'то выталкиваем из стека в выходную стpоку
            // все знаки опеpаций до ближайшей откpывающей скобки
            if (i->Tip == _CO) {
                bSCok = false;
                while (vStack.size() > 0) {
                    TFormulaElement &fe = vStack.back();
                    if (fe.Tip == _CI) {
                        vStack.pop_back();
                        bSCok = true;
                        break;
                    }
                    vFormulaElementP.push_back(fe);
                    vStack.pop_back();
                }
                if (!bSCok) return i->N;

            } else
                // Если очеpедной символ - '(' , то заталкиваем её в стек
                if (i->Tip == _CI) {
                    vStack.push_back(*i);
                } else
                    //если стек пуст, то опеpация из входной стpоки пеpеписывается в стек;
                    if (vStack.size() == 0) {
                        vStack.push_back(*i);
                    } else {
                        // если пpиоpитет поступившей опеpации больше пpиоpитета опеpации на веpшине стека
                        // заталкиваем поступившую опеpацию на стек
                        TFormulaElement &fe = vStack.back();
                        if (_levst(fe.Tip) < _levst(i->Tip)) {
                            vStack.push_back(*i);
                        } else {
                            // если пpиоpитет меньше пеpеписываем в выходную стpоку все опеpации
                            // с большим или pавным пpиоpитетом
                            while (vStack.size() > 0) {
                                TFormulaElement &fe = vStack.back();
                                if (_levst(fe.Tip) < _levst(i->Tip)) break;
                                vFormulaElementP.push_back(fe);
                                vStack.pop_back();
                            }
                            //записываем в стек поступившую  опеpацию
                            vStack.push_back(*i);

                        }
                    }
        } else {
            // Если очеpедной символ - буква , то пеpеписываем её в выходную стpоку
            vFormulaElementP.push_back(*i);
        }
    }
    // после pассмотpения всего выpажения Пеpеписываем все опеpации из стека в выходную стpоку
    while (vStack.size() > 0) {
        TFormulaElement &fe = vStack.back();
        if (fe.Tip == _CI) return fe.N;
        vFormulaElementP.push_back(fe);
        vStack.pop_back();
    }

    // проверяем
    TvFormulaElement vFormulaElement2;
    vFormulaElement2 = vFormulaElementP;
    bool ex;
    int n;
    do {
        ex = false;
        for (TvFormulaElement::iterator i = vFormulaElement2.begin(); i != vFormulaElement2.end(); ++i) {
            TvFormulaElement::iterator b = vFormulaElement2.begin();
            n = std::distance(b, i);
            if ((n >= 2) &&
                    ((i->Tip == _AN) || (i->Tip == _OR)) &&
                    (((i - 1)->Tip == 1) || ((i - 2)->Tip == 1))
               ) {
                vFormulaElement2.erase(i - 1, i + 1);
                ex = true;
                break;
            }
            if ((n >= 1) &&
                    ((i->Tip == _NT)) &&
                    (((i - 1)->Tip == 1))
               ) {
                vFormulaElement2.erase(i, i + 1);
                ex = true;
                break;
            }
        }
    } while (ex) ;
    if ((vFormulaElement2.size() > 1)) {
        int NN = (vFormulaElement2.begin() + 1)->N;
        ///vFormulaElement=vFormulaElement2;
        return NN;
    }


    return 0;
}

int  feFormulaResult(AComp * ac, const char * szFormula)
{
    TvFormulaElement vFormulaElement;
    feSt2vFormula(szFormula, vFormulaElement);
    fevFormulaSetR(ac, vFormulaElement);
    return feFormulaResult(vFormulaElement);
}
int  feFormulaResult(TvFormulaElement & vFormulaElement)
{
    TvFormulaElement vFormulaElementP;
    if (fevFormulaElement2PolskaNota(vFormulaElement, vFormulaElementP) < 0) return 33;
    return feFormulaResultP(vFormulaElementP);
}
int  feFormulaResultP(TvFormulaElement & vFormulaElementP)
{
    if (vFormulaElementP.size() == 0) return 0;
    int N = vFormulaElementP.size() - 1;
    return feRFormula(vFormulaElementP, N);

}

int  feFormulaResult(const char * szFormula)
{
    TvFormulaElement vFormulaElement;
    feSt2vFormula(szFormula, vFormulaElement);
    return feFormulaResult(vFormulaElement);
}

