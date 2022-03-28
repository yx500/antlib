//---------------------------------------------------------------------------

#ifndef uFormulaH
#define uFormulaH
//---------------------------------------------------------------------------
#include <vector>
#include <deque>

class AComp;
struct TFormulaElement {
    int N;             // Номер по порядку
    int Tip;           // 1 ТС,2-число, <0 операция
    char szVal[32];    // переменная
    long lVal;         // lЗначение
    int R;             // Состояние переменной
};

typedef std::vector<TFormulaElement> TvFormulaElement;
typedef std::deque<TFormulaElement>  TsFormulaElement;

const int _CI = -3;
const int _CO = -4;
const int _AN = -5;
const int _OR = -6;
const int _NT = -7;
const int _PL = -10;
const int _MN = -11;
const int _MU = -12;
const int _DV = -13;


void feSt2vFormula(const char * szFormula, TvFormulaElement & vFormulaElement);
const char * fevFormula2St(TvFormulaElement & vFormulaElement);
const char * fevFormula2StN(TvFormulaElement & vFormulaElement);
const char * feGetSimpleFormula(const char * szFormula);
void fevFormulaSetlVal(TvFormulaElement & vFormulaElement);
int fevFormulaElement2PolskaNota(TvFormulaElement & vFormulaElement, TvFormulaElement & vFormulaElementP);
void fevFormulaSetR(AComp * ac, TvFormulaElement & vFormulaElement);
int  feRFormula(TvFormulaElement & vFormulaElement, int &N);
int  feFormulaResult(TvFormulaElement & vFormulaElement);
int  feFormulaResult(AComp * ac, const char * szFormula);
int  feFormulaResult(const char * szFormula);
int  feFormulaResultP(TvFormulaElement & vFormulaElementP);

#endif


