//
#include "aheaders_cpp.h"
#include "APch.h"

#include "gorl.h"
#include "elem.h"
#include "strel.h"
#include "scrin.h"
#include "Vatempl.h"
#include "Stan.h"
#include "Svet.h"
#include "f.h"

#include "propmap.h"
#include "uParString.h"


#define tutim 200
PGorl Curr_G;

Grl::Grl()
{
    Col_Mar = 0;
    Col_Str = 0;

    memset(name, 0, sizeof(name));
    Matr = NULL;
    Strel_N = NULL;
    _Strel = NULL;
    Sign = NULL;
    memset(&Sign_i, 0, sizeof(Sign_i));
    impuls_m = NULL;
    impuls_km = NULL;
    zona_M = NULL;
}



char * Gorl::GetName()
{
    //static char ansiname[sizeof(gorl[0]->name)];
    //OemToChar(gorl[0]->name,ansiname);
    return gorl[0]->name;
}

#define TU 1

int Col_Gorl = 0;
//int  Size_G = 1;  /* 14.02.2003 перенёс в класс  */

//extern int nm,ng;

int  Test_KSP(int j, int *Flag_KSP, int *mem_KSP, int C_s)
{
    int acc = 0;
    if (Flag_KSP[j] == 1) {
        return 0;
    }
    for (int i = 0; i < C_s; i++) {
        if (
            (Flag_KSP[i] != 0) &&
            (Flag_KSP[i] == mem_KSP[j])) acc = 1;//подняли флаг занятия по маршруту
    }
    if (acc) return 1;
    return 0;
}
/*--------------------------------------------------------------------------¬
¦    Рисование Горловины                                                    ¦
L--------------------------------------------------------------------------*/

void Gorl::Go()
{
    UpdateState();
}
void Gorl::UpdateState()
{
    Get();
//PAComp G;
    //Size_G = MEM.mas;
    if (Size_G > _Size_G) return;
//Подстановка количества стррелок в горловине
    /*    if(Size_G>10) Size_G = 7;   !!!  */
//-------------------------------------------

//PElement  sgn;
//PStrel0 nom_s;
    PStrel0 stre;

//int i,j;

    memset(nom, 0, sizeof(nom));
    memset(marsh, -1, sizeof(marsh));
    memset(busi, 0, sizeof(busi));
//memset(sign,0,sizeof(sign));
//memset(sign_i,0,sizeof(sign_i));
    memset(marsh_y, 0, sizeof(marsh_y));
    memset(marsh_u, 0, sizeof(marsh_u));
    memset(itis, D, sizeof(itis));
    memset(clr0, 0, sizeof(clr0));
    memset(isu, 0, sizeof(isu));
    memset(svu, 0, sizeof(svu));
    memset(ism, 0, sizeof(ism));
    memset(State, 0, sizeof(State));
    memset(Flag_KSP_, 0, sizeof(Flag_KSP_));
    memset(mem_KSP, 0, sizeof(mem_KSP));

    priznak_marsh_in_fiz_gorl_for_filter_kzm = 0;



    for (int i = 0; i < gorl[0]->Col_Str; i++) {
        Flag_KSP_[i] = 0;
        mem_KSP[i] = 0;
    }
    for (int j = 0; j < Size_G; j++) {
        if (gorl[j] == NULL) continue;
        for (int i = 0; i < gorl[j]->Col_Str; i++) { //!!!!
            if ((stre = gorl[j]->_Strel[i]) == NULL) continue;
            else {

                mem_KSP[i] = stre->impuls_busi;
            }
        }
    }


    usFindMarshruts(); /*------Поиск установленного и устанавливаемого маршрута -----  */

    usOpredKSP();      /* определение флага ксп */// определение запрещенных маршрутов


    /*==========ОСНОВНОЙ БЛОК ======================================*/
    for (int i = 0; i < gorl[0]->Col_Str; i++) {
        for (int j = 0; j < Size_G; j++) {
            ism[j] = D;
            isu[j] = D;
            if (gorl[j] == NULL) continue;
            if ((nom[j] = gorl[j]->_Strel[i]) == NULL) {
                clr0[j] = LIN; itis[j] = D; continue;
            }/*если нет стрелки*/
            /*   if(marsh[j]>=gorl[0]->Col_Mar){ clr0[j]=LIN;itis[j]=D; if((gorl[0]->bit_m)==2)   itis[j]=State[i];  } */
            else {
                clr0[j] = COLOR_S;
                /*--Положение----*/
                switch (gorl[j]->bit_m) {
                case 1:
                    if (marsh[j] >= gorl[0]->Col_Mar)itis[j] = D;
                    else  itis[j] = gorl[j]->Matr[marsh[j]][i];
                    break;
                case 2:
                    itis[j] = State[i];
                    break;
                }
                /*--КЗМ----*/
                switch (gorl[j]->bit_kzm) {
                case 1:
                    if (f(gorl[j]->impuls_kzm) == 1)clr0[j] = COLOR_SET;
                    if (f(gorl[j]->impuls_kzm) == 33)clr0[j] = BIRUZOVIJ;
                    break;
                case 2:
                    if (f(nom[j]->impuls_kzm) == 1)clr0[j] = COLOR_SET;
                    if (f(nom[j]->impuls_kzm) == 33)clr0[j] = BIRUZOVIJ;
                    break;
                }
                /*--КСП----*/
                switch (gorl[j]->bit_ksp) {
                case 1:
                    if (f(gorl[j]->impuls_ksp) == 1) clr0[j] = COLOR_B;
                    if (f(gorl[j]->impuls_ksp) == 33) clr0[j] = BIRUZOVIJ;
                    break;
                case 2:
                    if (f(nom[j]->impuls_busi) == 1)clr0[j] = COLOR_B;
                    if (f(nom[j]->impuls_busi) == 33)clr0[j] = BIRUZOVIJ;
                    break;
                }
            }  /* конец else */
            if ((marsh_y[j] < gorl[0]->Col_Mar) && (marsh_y[j] >= 0)) ism[j] = gorl[j]->Matr[marsh_y[j]][i];
            else   ism[j] = D;
            if (marsh_u[j] != -1) isu[j] = gorl[j]->Matr[marsh_u[j]][i];
            else   isu[j] = D;

            usFiltrs(i, j); /*=========фильтры================*/

        }/* конец for по горловинам*/

        usOutStrel(); /*-----Логическое сложение стрелок ---*/
    }


    /*==========ВСЕ ОСНОВНОЙ БЛОК==============================*/

    usOutSvet(); /*----Вывод светофоров-----------------------------------------*/


    /*------------Все Вывод----------------------------------------*/
}

void Gorl::usFindMarshruts()
{
    /*------Поиск установленного и устанавливаемого маршрута -----  */
    PStrel0 stre;
    int priznak_2_marsh;
    switch (gorl[0]->bit_m) {
    case 1:
        for (int j = 0; j < Size_G; j++) {
            //   20/03/2000 - решение проблемы если более одного маршрута
            //   при маршрутном управлении
            // запоминаем первый в признак
            // а потм проверяем
            priznak_2_marsh = -1;
            for (marsh[j] = 0; marsh[j] < gorl[0]->Col_Mar; marsh[j]++) {
                if (f(gorl[j]->impuls_km[marsh[j]]) == 1) {
                    if (priznak_2_marsh == -1) {
                        priznak_2_marsh = marsh[j];
                    } else {
                        priznak_2_marsh = gorl[0]->Col_Mar + 1; break;
                    }
                }
            }
            if (priznak_2_marsh != -1)  marsh[j] = priznak_2_marsh;
            for (marsh_y[j] = 0; marsh_y[j] < gorl[0]->Col_Mar; marsh_y[j]++)
                if (f(gorl[j]->impuls_m[marsh_y[j]]) == 1) break;
            /*---------------------
            if((gorl[j]->tu_marh)&&(labs(gorl[j]->time_tu-time__)>tutim)){
            if(gorl[j]->Sign_i.nomer!=0){
            gorl[j]->Sign_i.nomer->pr=0;
            gorl[j]->Sign_i.nomer->set[C_M]=-1;
            }
            else{
            int r=0;
            }

            if( gorl[j]->Sign[gorl[j]->tu_marh-1].nomer!=0){
            gorl[j]->Sign[gorl[j]->tu_marh-1].nomer->pr=0;
            gorl[j]->Sign[gorl[j]->tu_marh-1].nomer->set[C_M]=-1;
            }
            else{
            int r=0;
            }
            gorl[j]->tu_marh=0;
            Out_Info_(_Diag, 0,0,0);
            //          Out_Info_(_Diag, "Не прошел ","Маршрут ",0);
            }
            */

            if (TU && gorl[j]->tu_marh) {
                marsh_u[j] = gorl[j]->tu_marh - 1;
            } else           {
                marsh_u[j] = -1;
            }
            /* --------------------------------------------------*/

        }
        break;
    case 2:
        /*---формирование State ----*/
        for (int i = 0; i < gorl[0]->Col_Str; i++)State[i] = D;
        for (int j = 0; j < Size_G; j++) {
            for (int i = 0; i < gorl[0]->Col_Str; i++) {
                if (gorl[j] == NULL) continue;
                if ((stre = gorl[j]->_Strel[i]) == NULL) {
                    continue;
                }/*если нет стрелки*/
                else {

                    if ((stre->GetType() == SzT) || (stre->GetType() == SzB)) {
                        State[i] = f(stre->impuls_kmu) * 2 + f(stre->impuls_mu);
                        if (
                            (!f(stre->impuls_plus)) &&
                            f(stre->impuls_mnus)
                        ) State[i] = W;

                    } else

                        State[i] = f(stre->impuls_plus) * 2 + f(stre->impuls_mnus);
                }
            }
        }
        /*--- Сравнение State c Matr   ----*/
        for (int j = 0; j < Size_G; j++) {
            if (gorl[j] == NULL) continue;
            for (marsh[j] = 0; marsh[j] < gorl[0]->Col_Mar; marsh[j]++) {
                Count_empty = 0;
                int i = 0;
                for (i = 0; i < gorl[0]->Col_Str; i++) {

                    if (!((gorl[j]->Matr[marsh[j]][i] == D) ||
                            (gorl[j]->Matr[marsh[j]][i] == H))) {
                        if (State[i] != gorl[j]->Matr[marsh[j]][i])break;
                    } else/*пропустить пустую запись */ Count_empty++;
                }
                if ((i >= gorl[0]->Col_Str) && (Count_empty != gorl[0]->Col_Str))break;
            }
            for (marsh_y[j] = 0; marsh_y[j] < gorl[0]->Col_Mar; marsh_y[j]++)
                if (f(gorl[j]->impuls_m[marsh_y[j]]) == 1) break;
            if (TU && gorl[j]->tu_marh) {
                marsh_u[j] = gorl[j]->tu_marh - 1;
            } else          {
                marsh_u[j] = -1;
            }
            /*    ---------------------------------    */
        }
        break;
    };
    /*______________________все поиск_______________________________*/
}

void Gorl::usOpredKSP()
{
    for (int j = 0; j < Size_G; j++) {
        if (gorl[j] == NULL) continue;
        gorl[j]->marh_tu = marsh_u[j];

        if (
            (marsh[j] < gorl[0]->Col_Mar)
        )
            gorl[j]->marh    = marsh  [j];
        else
            gorl[j]->marh    = -1;

        if (
            (f(gorl[j]->impuls_ks) || f(gorl[j]->impuls_ks_i))
        )
            gorl[j]->marh_sv    = 1;
        else
            gorl[j]->marh_sv    = -1;

        if (marsh_y[j] >= gorl[0]->Col_Mar)
            gorl[j]->marh_m  = -1;
        else
            gorl[j]->marh_m  = marsh_y[j];
    }

    for (int i = 0; i < gorl[0]->Col_Str; i++) {
        for (int j = 0; j < Size_G; j++) {
            clr0[j] = 0; itis[j] = D;
            if (gorl[j] == NULL) continue;
            if ((nom[j] = gorl[j]->_Strel[i]) == NULL)continue;/*если нет стрелки*/
            if (gorl[0]->bit_ksp == 1) {
                if (f(gorl[j]->impuls_ksp) == 1) busi[j] = 1; continue;
            }
            if (marsh[j] >= gorl[0]->Col_Mar) {
                if (f(nom[j]->impuls_busi) == 1) busi[j] = 1; continue;
            }
            itis[j] = gorl[j]->Matr[marsh[j]][i];
            if (f(nom[j]->impuls_busi) == 1) clr0[j] = COLOR_B;
            if ((clr0[j] == COLOR_B) &&
                    ((itis[j] == P) ||
                     (itis[j] == M) ||
                     (itis[j] == W))
               ) {
                Flag_KSP_[i] = mem_KSP[i];
                busi[j] = 1;
            }
        }
    }
// определяем есть ли вообще маршут в горловине
    for (int j = 0; j < Size_G; j++) {
        if (marsh[j] < gorl[0]->Col_Mar)
            priznak_marsh_in_fiz_gorl_for_filter_kzm = 1;

    }

    /*------ конец этого ------*/
}

void Gorl::usFiltrs(int i, int j)
/*=========фильтры================*/
{
    PStrel0 stre;
    if (!AO->USE_GORL_OTCECH) {
    
        if ((
                    ((itis[j] == D) || (itis[j] == H)) &&
                    (gorl[j]->bit_ksp == 2) &&
                    (gorl[j]->bit_m == 1) &&
                    (clr0[j] == COLOR_B) &&
                    (Test_KSP(i, Flag_KSP_, mem_KSP, gorl[0]->Col_Str))) ||
                (((itis[j] == D) || (itis[j] == H)) &&
                 (gorl[j]->bit_ksp == 1))
           )                      clr0[j] = LIN;

           /*Фильтр ксп для м=1*/
        /*не забудь что возможен только один маршрут в горловине(секущий)
        в этом случае надо проверить на наличие маршрута*/
        // ХМ ХМ
        if (
            (marsh[j] >= gorl[0]->Col_Mar) &&
            (gorl[j]->bit_ksp == 2) &&
            (gorl[j]->bit_m == 2) &&
            (clr0[j] == COLOR_B) &&
            (Test_KSP(i, Flag_KSP_, mem_KSP, gorl[0]->Col_Str))
        )   clr0[j] = LIN;

        if (    /*??????*/
            (marsh[j] < gorl[0]->Col_Mar) &&
            ((gorl[j]->Matr[marsh[j]][i] == D) || (gorl[j]->Matr[marsh[j]][i] == H)) &&
            (gorl[j]->bit_ksp == 2) &&
            (gorl[j]->bit_m == 2) &&
            (clr0[j] == COLOR_B) &&
            (Test_KSP(i, Flag_KSP_, mem_KSP, gorl[0]->Col_Str)) ||
            (((itis[j] == D) || (itis[j] == H)) &&
             (gorl[j]->bit_ksp == 1))
        )                      clr0[j] = LIN; /*Фильтр ксп для м=2*/

        if (
            (((itis[j] == D) || (itis[j] == H)) &&
             (gorl[j]->bit_kzm == 1) &&
             (clr0[j] == COLOR_SET))
            //  А вот попробую это исправить
            // дополнив проверкой  что нет мершрута
            // что бы при потере маршрута
            // оставалось замыкание
            && (marsh[j] < gorl[0]->Col_Mar)
        )clr0[j] = LIN; /*Фильтр кзп*/

        if (
            //попробуем так
            // попробуем этак
            // две нижнии строчки закоментарены в Могилеве 25/02/2000
            // (иначе пропадало занятие при потере маршрута на горке )
            //  Оно отсекало занятие по другим маршрутам в этой физ горловине
            // хм ! И так и этак не правильно
            //    /*

            (
                (priznak_marsh_in_fiz_gorl_for_filter_kzm == 1) &&
                (marsh[j] >= gorl[0]->Col_Mar)
            ) ||
        //   */

            (
                (marsh[j] < gorl[0]->Col_Mar) &&
                ((itis[j] == D) || (itis[j] == H)) &&
                (gorl[j]->bit_m == 1) &&
                (gorl[j]->bit_kzm == 2) &&
                (clr0[j] == COLOR_SET))
        ) clr0[j] = LIN;

        /*Фильтр кзп для Люды */
        if
        (((itis[j] == D) || (itis[j] == H)) &&
                (gorl[j]->bit_m == 1) &&
                (clr0[j] == COLOR_S))
            clr0[j] = LIN; /*Фильтр m*/


        //  22/10/2002  Горький !
        /*
        Вот и ответ !
        Невозможно при потере маршрута на 2-х путке верно определить
        что надо отсекать а что нет ;-)
        все очень просто - представь 2-е 3-х стрелочные секции подряд и после них 1стрелку
        стрелка потеряла контроль - все невозможно определить как  рисовать секции ;-)
        задача не имеет решения !
        Отсечка ! Только отсечка.....
        вопрос что делать с светофорами отправления ?
        слежением ?
        маршрутным управлением ?
        секционым занятием (ага  ...   нарисуй отсечку на 6 стрелок ?)
        МУ
        КМУ
        эхе-хе    думать надо
        вот еслиб заменить
        */

        if ((marsh[j] >= gorl[0]->Col_Mar) &&
                (gorl[j]->bit_m == 2) &&
                ((clr0[j] == COLOR_S) || (clr0[j] == COLOR_SET))) clr0[j] = LIN;


        //       ((clr0[j]==COLOR_S)/*||(clr0[j]==COLOR_SET)*/)) clr0[j]=LIN;
        else if (
            (marsh[j] < gorl[0]->Col_Mar) &&
            (gorl[j]->bit_m == 2) &&

            ((gorl[j]->Matr[marsh[j]][i] == D) ||
             (gorl[j]->Matr[marsh[j]][i] == H)) &&

            ((clr0[j] == COLOR_S) || (clr0[j] == COLOR_SET)))
            clr0[j] = LIN;/*Фильтр для м=2*/ /*????*/
    } else {
        //     if()


        //  Значить так !
        //  Новый фильтр

        // забыли про МУ.КМ

        if ((stre = gorl[j]->_Strel[i]) != NULL) {
            if (stre->nomer == 33) {
                //int f=0;
                //f=1;
            }
        };

        if (
            ((marsh[j] >= gorl[0]->Col_Mar) ||
             (marsh[j] == -1))
            &&
            (gorl[j]->bit_m == 2) &&
            (clr0[j] == COLOR_S)
        ) clr0[j] = LIN;
        if (
            (marsh[j] < gorl[0]->Col_Mar) &&
            (gorl[j]->bit_m == 2) &&
            ((gorl[j]->Matr[marsh[j]][i] == D) ||
             (gorl[j]->Matr[marsh[j]][i] == H)) &&
            (clr0[j] == COLOR_S)
        )  clr0[j] = LIN;

        if ((stre = gorl[j]->_Strel[i]) != NULL) {
            if (f(stre->impuls_mu) || f(stre->impuls_kmu))
                clr0[j] = LIN;
        }
    }

    //---------  Конец фильтра ! -----------------------------
}

void Gorl::usOutStrel()
{
    int     is_D, is_P, is_M, is_W;
    int st1 = 1, st2 = 1, st3 = 1;
    int clr1 = LIN;
    int is = 1;
    PStrel0 nom_s;
    /*-----Логическое сложение стрелок ---*/
    is_D = 0; is_P = 0; is_M = 0; is_W = 0;
    clr1 = 0; st1 = 1; st2 = 1; st3 = 1;
    for (int j = 0; j < Size_G; j++) {
        if (itis[j] == D)is_D++;
        if ((itis[j] == P) || (itis[j] == H))is_P++;
        if (itis[j] == M)is_M++;
        if (itis[j] == W)is_W++;
        if (clr1 < Clr_lev(clr0[j]))clr1 = Clr_lev(clr0[j]);

        if (ism[j] == P) st1 = 5;
        if (ism[j] == M)
            st2 = 5;
        if (ism[j] == W)
            st3 = 5;
        //установка маршрута
        if (isu[j] == P)
            st1 = 6;
        if (isu[j] == M)
            st2 = 6;
        if (isu[j] == W)
            st3 = 6;
    }
    if (is_P != 0)is = P;
    if (is_M != 0)is = M;
    if (is_W != 0)is = W;
    if ((is_P != 0) && (is_M != 0))is = D;      /*здесь добавить  */
    if ((is_P == 0) && (is_M == 0) && (is_W == 0))is = D;
    clr1 = Lev_clr(clr1);
    //if((is==D)&&(st1!=1))is=P;
    //if((is==D)&&(st2!=1))is=M;
    if ((is == D) && (st3 != 1)) {
        is = W;/*st2=st3;*/
    }
//   if((is==D)&&(st3!=1)){is=W;st2=5;}
    /*---------все сложение----------------*/
    nom_s = NULL;
    for (int j = 0; j < Size_G; j++) {
        if (nom[j] != NULL) {
            nom_s = nom[j]; break;
        }
    }
    if (nom_s != NULL) {

        nom_s->clr = clr1;
        nom_s->is = is;
        nom_s->styll1 = st1;
        nom_s->styll2 = st2;
        nom_s->styll3 = st3;
        //nom_s->StateChanged=true;

        //nom_s->Go();   << РИСУЕМСЯ САМИ !!!
    }
} /* конец for по стрелкам */

void Gorl::usOutSvet()
{

    /*----Вывод светофоров-----------------------------------------*/
    int clr1 = LIN;
    PElement  sgn;
    /*отправление*/
    int clr_svt[Max_Size_Marsh_];/*сумматор для светофоров  поттом надо переделать*/
    for (int i = 0; i < gorl[0]->Col_Mar; i++) {
        clr_svt[i] = FON;
        //    clr_svt[i]=Clr_SetC(0,0);
        for (int j = 0; j < Size_G; j++) {
            ///!!!!!  <БЛЯЯЯЯЯЯЯЯ!
            if (gorl[j] == NULL) continue;
            if ((gorl[j]->Sign[i].name != 0) &&
                    (gorl[j]->Sign[i].name[0] != 0) &&
                    (gorl[j]->Sign[i].name[0] != ' ')
               ) {
                clr1 = Clr_SetC((f(gorl[j]->impuls_ks) == 1) && (i == marsh[j]), gorl[j]->Sign[i].name);
                if (clr_svt[i] != Clr_SetC(1, gorl[j]->Sign[i].name)) clr_svt[i] = clr1; //??? c маневрами
            }
        }
    }

    for (int j = 0; j < Size_G; j++) {
        if (gorl[j] == NULL) continue;
        for (int i = 0; i < gorl[0]->Col_Mar; i++) {
            if ((sgn = (PElement)(gorl[j]->Sign[i].nomer)) == NULL)continue;
            else {
                sgn->clr = clr_svt[i];  //  << ВАУ !
                //sgn->Get();                      29.08.07
                //if(MEM.impuls_busi==0){
                if ((sgn->impuls_busi == 0) && (gorl[j]->impuls_ks == 0)) sgn->clr = FON;
                sgn->Clear();
                //sign[j]=f(gorl[j]->impuls_ks);
                //sgn->StateChanged=true;
                //sgn->Show(); //  << ВАУ !
                //}else{
                //sign[j]=f(MEM.impuls_busi);
                //}
            }
        }
    }
    /*---------------------*/
    /*прием*/
    for (int j = 0; j < Size_G; j++) {
        if (gorl[j] == NULL) continue;
        if ((sgn = (PElement)(gorl[j]->Sign_i.nomer)) == NULL)continue;
        else {
            clr1 = Clr_SetC(f(gorl[j]->impuls_ks_i), gorl[j]->Sign_i.name);
            sgn->clr = clr1;
            sgn->Get();
            if (MEM.impuls_busi == 0) {
                if (gorl[j]->impuls_ks_i == 0)
                    sgn->clr = FON;
                //sign_i[j]=f(gorl[j]->impuls_ks_i);
                //sgn->StateChanged=true;
                //sgn->Show();
            } else {
                //sign_i[j]=f(MEM.impuls_busi);
            }/*if*/
        }
    }
}

Gorl::Gorl()
{
    bVirtual = false;
    Size_G = 1;
    int i;
    for (i = 0; i < Size_G; i++) {
        gorl[i] = NULL;
        comp[i] = NULL;
    }
    for (i = 0; i < Size_G; i++) {
        gorl[i] = new Grl;
    }
}

Gorl::Gorl(int c_s, int c_m)
{
    bVirtual = false;
    Size_G = 1;
    int i;
    for (i = 0; i < Size_G; i++) {
        gorl[i] = NULL;
        comp[i] = NULL;
    }
    for (i = 0; i < Size_G; i++) {
        gorl[i] = new Grl;
    }
    gorl[0]->Col_Str = c_s;
    gorl[0]->Col_Mar = c_m;
    Creat();
}

Gorl::~Gorl()
{
    for (int i = 0; i < Size_G; i++)
        if (gorl[i] != NULL) delete gorl[i];
}


void Gorl::Connect()
{
    int j;
    for (int i = 0; i < Size_G; i++) {
        for (j = 0; j < gorl[0]->Col_Str; j++)
            gorl[i]->_Strel[j] = (Strel0*)pVisibleArray->pStation->Trans(&(gorl[i]->Strel_N[j]), STRE);
        for (j = 0; j < gorl[0]->Col_Mar; j++) {
            Svet_0 * S = dynamic_cast <Svet_0 *>(pVisibleArray->pStation->Trans((gorl[i]->Sign[j].name), CEMA));
            gorl[i]->Sign[j].nomer = S;
            if ((S != NULL) && (gorl[i]->impuls_ks != 0)) S->bGorl = true;
        }
        Svet_0 * S = dynamic_cast <Svet_0 *>(pVisibleArray->pStation->Trans((gorl[i]->Sign_i.name), CEMA));
        gorl[i]->Sign_i.nomer = S;
        if (S != NULL) S->bGorl = true;
    }
}

void Gorl::Get()
{
    AComp::Get();
    //strcpy(MEM.name,gorl[0]->name);
    CharToOemBuff(gorl[0]->name, MEM.name, 6);

    //memset(MEM.name,'\x0',9);
    //memcpy(MEM.name,gorl[0]->name,7);
    //MEM.name[7]='\x0';
    //memcpy( MEM.name+9  ,&ID      , 2);

    MEM.impuls_busi = -1;
};






void Gorl::Set()
{
    AComp::Set();

    //strnset(gorl[0]->name,'\x0',8);
    //memcpy(gorl[0]->name,MEM.name,7);
    //gorl[0]->name[7]='\x0';
    //memcpy(&ID,     MEM.name+9,2);
};



/*
void Gorl::

};
*/
void Gorl::Show()
{
    if (MOD != ED) return;
    if ((CurrentPicture == BG)) return;
    setcolor(TXT);
    barx(X*MUL_X + _X_, Y*MUL_Y + _Y_, X*MUL_X + _X_ + 7, Y*MUL_Y + _Y_ + 7);
    _SetText(F_LITT, CENTER_TEXT, TOP_TEXT);
    setcolor(LIN);
    OutTextXY(X*MUL_X + _X_, Y*MUL_Y + _Y_ + 7, gorl[0]->name);
    _SetText(F_DEFAULT, LEFT_TEXT, TOP_TEXT);


};

void Gorl::Save(FILE *file)
{

    Grl gorl_0;
    memcpy(&gorl_0, gorl[0], sizeof(Grl));


    Signal oemSign;
    CharToOemBuff(gorl[0]->name, gorl_0.name, 5);
    CharToOemBuff(gorl[0]->Sign_i.name, gorl_0.Sign_i.name, 5);



    fwrite(&gorl_0, sizeof(Grl), 1, file);
    for (int i = 0; i < gorl[0]->Col_Mar; i++) {
        fwrite(gorl[0]->Matr[i], sizeof(char), gorl[0]->Col_Str, file);
    }
    fwrite(gorl[0]->Strel_N, sizeof(char), gorl[0]->Col_Str, file);

    for (int i = 0; i < gorl[0]->Col_Mar; i++) {
        memcpy(&oemSign, &gorl[0]->Sign[i], sizeof(Signal));
        CharToOemBuff(gorl[0]->Sign[i].name, oemSign.name, 6);
        fwrite(&oemSign, sizeof(Signal), 1, file);
    }

    //fwrite(gorl[0]->Sign,sizeof(Signal),gorl[0]->Col_Mar,file);

    fwrite(gorl[0]->impuls_m, sizeof(short int), gorl[0]->Col_Mar, file);
    fwrite(gorl[0]->impuls_km, sizeof(short int), gorl[0]->Col_Mar, file);

    fwrite(gorl[0]->zona_M, sizeof(ID_ZO), gorl[0]->Col_Mar, file);

    /*         */

    /*         */
    Get();
    fwrite(&MEM, sizeof(AMemory), 1, file);
};

void Gorl::Load(FILE *file)
{
    if (MOD == ED) {

        fread(gorl[0], sizeof(Grl), 1, file);
        if (gorl[0]->nom_fiz > Col_Gorl) Col_Gorl = gorl[0]->nom_fiz;
        Creat();
        for (int i = 0; i < gorl[0]->Col_Mar; i++) {
            fread(gorl[0]->Matr[i], sizeof(char), gorl[0]->Col_Str, file);
        }
        for (int i = 0; i < gorl[0]->Col_Mar; i++) {
            for (int j = 0; j < gorl[0]->Col_Str; j++) {
                if (
                    (gorl[0]->Matr[i][j] <= 0) ||
                    (gorl[0]->Matr[i][j] > 7)
                )
                    gorl[0]->Matr[i][j] = 3;
            }
        }

        fread(gorl[0]->Strel_N, sizeof(char), gorl[0]->Col_Str, file);

        fread(gorl[0]->Sign, sizeof(Signal), gorl[0]->Col_Mar, file);
        fread(gorl[0]->impuls_m, sizeof(short int), gorl[0]->Col_Mar, file);
        fread(gorl[0]->impuls_km, sizeof(short int), gorl[0]->Col_Mar, file);
        fread(gorl[0]->zona_M, sizeof(ID_ZO), gorl[0]->Col_Mar, file);
        fread(&MEM, sizeof(AMemory), 1, file);
        MEM.type = GORL;
        Set();
        /*-------------------------------------------------*/

        /*-------------------------------------------------*/
    } else {
        if (gorl[0] == NULL) Qui("нет памяти для горловин", 1, 0);

        fread(gorl[0], sizeof(Grl), 1, file);
        if (gorl[0]->nom_fiz > Col_Gorl) Col_Gorl = gorl[0]->nom_fiz;
        Creat();

        for (int i = 0; i < gorl[0]->Col_Mar; i++) {
            fread(gorl[0]->Matr[i], sizeof(char), gorl[0]->Col_Str, file);
        }
        fread(gorl[0]->Strel_N, sizeof(char), gorl[0]->Col_Str, file);

        fread(gorl[0]->Sign, sizeof(Signal), gorl[0]->Col_Mar, file);
        fread(gorl[0]->impuls_m, sizeof(short int), gorl[0]->Col_Mar, file);
        fread(gorl[0]->impuls_km, sizeof(short int), gorl[0]->Col_Mar, file);
        fread(gorl[0]->zona_M, sizeof(ID_ZO), gorl[0]->Col_Mar, file);


        fread(&MEM, sizeof(AMemory), 1, file);
        Set();


    }
    char   ansiname[6];
    OemToCharBuff(gorl[0]->name, ansiname, 5);
    strncpy(gorl[0]->name, ansiname, 5);
    OemToCharBuff(gorl[0]->Sign_i.name, ansiname, 5);
    strncpy(gorl[0]->Sign_i.name, ansiname, 5);
    for (int i = 0; i < gorl[0]->Col_Mar; i++) {
        OemToCharBuff(gorl[0]->Sign[i].name, ansiname, 5);
        strncpy(gorl[0]->Sign[i].name, ansiname, 5);
    }



};

void Gorl::Creat(void)
{
    gorl[0]->Matr = new char*[gorl[0]->Col_Mar];
    for (int i = 0; i < gorl[0]->Col_Mar; i++) {
        gorl[0]->Matr[i] = new char[gorl[0]->Col_Str];
    }
    gorl[0]->Strel_N = new char[gorl[0]->Col_Str];
    gorl[0]->_Strel = new PStrel0[gorl[0]->Col_Str];
    gorl[0]->Sign = new Signal[gorl[0]->Col_Mar];
    gorl[0]->impuls_m = new short int[gorl[0]->Col_Mar];
    gorl[0]->impuls_km = new short int[gorl[0]->Col_Mar];
    gorl[0]->zona_M = new ID_ZO[gorl[0]->Col_Mar];
    gorl[0]->tu_marh =  0;
    gorl[0]->marh_tu = -1;
    gorl[0]->marh_m  = -1;
    gorl[0]->marh    = -1;
};
void Gorl::Destroy(void)
{

    if (gorl[0]->Matr) {
        for (int i = 0; i < gorl[0]->Col_Mar; i++) {
            if (gorl[0]->Matr[i]) delete[] gorl[0]->Matr[i];
        }
        delete[] gorl[0]->Matr;
    }
    if (gorl[0]->Strel_N)delete[]gorl[0]->Strel_N;
    if (gorl[0]->_Strel)delete[]gorl[0]->_Strel;
    if (gorl[0]->Sign)delete[]gorl[0]->Sign;
    if (gorl[0]->impuls_m)delete[]gorl[0]->impuls_m;
    if (gorl[0]->impuls_km)delete[]gorl[0]->impuls_km;
    if (gorl[0]->zona_M)delete[]gorl[0]->zona_M;
};

TYP  Gorl::GetType()
{
    return GORL;
};
UNIT Gorl::GetUnit()
{
    return GORE;
};





void Gorl::GetMarsh(int &Marsh, bool &BUSY, bool &KZM, bool &SvOpen0, bool &SvOpen1)
{
    try {
        Marsh = -1;
        KZM = false;
        SvOpen0 = false;
        SvOpen1 = false;
        BUSY = false;
        char State[Max_Size_Strel_];
        //PStrel0 nom[_Size_G]= {0,0,0,0,0,0,0,0,0,0};
        PStrel0 str;
        int Count_empty;
        /*------Поиск установленного и устанавливаемого маршрута -----  */
        int priznak_2_marsh;
        switch (gorl[0]->bit_m) {
        case 1:
            priznak_2_marsh = -1;
            for (int i = 0; i < gorl[0]->Col_Mar; i++) {
                if (f(gorl[0]->impuls_km[i]) == 1) {
                    if (priznak_2_marsh == -1) {
                        priznak_2_marsh = i;
                    } else {
                        priznak_2_marsh = gorl[0]->Col_Mar + 1; break;
                    }
                }
            }
            if (priznak_2_marsh != -1)  Marsh = priznak_2_marsh;
            break;
        case 2:
            /*---формирование State ----*/
            for (int i = 0; i < gorl[0]->Col_Str; i++)State[i] = D;
            for (int i = 0; i < gorl[0]->Col_Str; i++) {
                if ((str = gorl[0]->_Strel[i]) == NULL) {
                    continue;
                }/*если нет стрелки*/ else {
                    if ((str->GetType() == SzT) || (str->GetType() == SzB)) {
                        State[i] = f(str->impuls_kmu) * 2 + f(str->impuls_mu);
                        if (
                            (!f(str->impuls_plus)) &&
                            f(str->impuls_mnus)
                        ) State[i] = W;

                    } else
                        State[i] = f(str->impuls_plus) * 2 + f(str->impuls_mnus);
                }
            }
            /*--- Сравнение State c Matr   ----*/
            int i;
            for (int m = 0; m < gorl[0]->Col_Mar; m++) {
                Count_empty = 0;
                for (i = 0; i < gorl[0]->Col_Str; i++) {

                    if (!((gorl[0]->Matr[m][i] == D) ||
                            (gorl[0]->Matr[m][i] == H))) {
                        if (State[i] != gorl[0]->Matr[m][i])break;
                    } else Count_empty++;
                }
                if ((i >= gorl[0]->Col_Str) && (Count_empty != gorl[0]->Col_Str)) {
                    Marsh = m;
                    break;
                }
            }
            break;
        }
        KZM = true;
        for (int i = 0; i < gorl[0]->Col_Str; i++) {
            str = gorl[0]->_Strel[i];
            if (str == NULL)continue;/*если нет стрелки*/
            if (gorl[0]->bit_ksp == 1) {
                if (f(gorl[0]->impuls_ksp) == 1) BUSY = true;
            }
            if (gorl[0]->bit_ksp == 2) {
                if (f(str->impuls_busi) == 1) BUSY = true;
            }
            if (gorl[0]->bit_kzm == 1) {
                if (f(gorl[0]->impuls_kzm) != 1) KZM = false;
            }
            if (gorl[0]->bit_kzm == 2) {
                if (f(str->impuls_kzm) != 1) KZM = false;
            }
        }
        if (gorl[0]->Sign_i.nomer != NULL) {
            if (f(gorl[0]->Sign_i.nomer->impuls_busi) == 1) SvOpen0 = true;
        }
        if ((Marsh >= 0) && (Marsh < gorl[0]->Col_Mar)) {
            if (gorl[0]->Sign[Marsh].nomer != NULL) {
                if (f(gorl[0]->Sign[Marsh].nomer->impuls_busi) == 1) SvOpen1 = true;
            }
        }
    } catch (...) {}

}

int Gorl::GetDoneMarsh()
{
    try {
        int Marsh;
        bool BUSY;
        bool KZM;
        bool SvOpen0;
        bool SvOpen1;
        GetMarsh(Marsh, BUSY, KZM, SvOpen0, SvOpen1);
        if ((Marsh >= 0) && (!BUSY) && (KZM) && (SvOpen0 || SvOpen1)) return Marsh;
    } catch (...) {}
    return 0;
}

unsigned int  Gorl::GetID(void)
{
    if (bVirtual) return 0;
    if (gorl[0] != NULL)
        return gorl[0]->ID; else
        return 0;
}
void Gorl::SetID(unsigned int IDn)
{
    if (bVirtual) return ;
    if (gorl[0] != NULL) gorl[0]->ID = (unsigned __int16)IDn;
}


void Gorl::GetPropMap(TPropMap &m)
{
    AComp::GetPropMap(m);

    m.put("смИМЯ", gorl[0]->name);

    m.put("цфCol_Mar", gorl[0]->Col_Mar);
    m.put("цфCol_Str", gorl[0]->Col_Str);
    m.put("цфbit_m", gorl[0]->bit_m);
    m.put("цфbit_ksp", gorl[0]->bit_ksp);
    m.put("цфbit_kzm", gorl[0]->bit_kzm);
    m.put("цфnom_fiz", gorl[0]->nom_fiz);
    m.putEx("тсimpuls_ksp", gorl[0]->impuls_ksp  , GetRealImp(gorl[0]->impuls_ksp));
    m.putEx("тсimpuls_kzm", gorl[0]->impuls_kzm  , GetRealImp(gorl[0]->impuls_kzm));
    m.putEx("тсimpuls_ks", gorl[0]->impuls_ks    , GetRealImp(gorl[0]->impuls_ks));
    m.putEx("тсimpuls_ks_i", gorl[0]->impuls_ks_i, GetRealImp(gorl[0]->impuls_ks_i));

    m.put("смSign_i_name", gorl[0]->Sign_i.name);

    TParString ps("", ";");
    // сохраняем номера стрелок
    ps.SetVal("");
    for (int j = 0; j < gorl[0]->Col_Str; j++) ps.SetInt(j, gorl[0]->Strel_N[j]);
    m.put("СТР", ps.ResultStr());
    // сохраняем матрицу   +;+;+;Нд;impuls_m;impuls_km
    int cm = gorl[0]->Col_Mar;
    for (int i = 0; i < cm; i++) {
        ps.SetVal("");
        for (int j = 0; j < gorl[0]->Col_Str; j++) ps.SetInt(j, gorl[0]->Matr[i][j]);
        ps.SetStr(cm + 0, gorl[0]->Sign[i].name);
        ps.SetInt(cm + 1, gorl[0]->impuls_m[i]);
        ps.SetInt(cm + 2, gorl[0]->impuls_km[i]);
        m.put("M" + IntToStr(i), ps.ResultStr());
    }

}


void Gorl::SetPropMap(TPropMap &m)
{
    AComp::SetPropMap(m);

    strncpy(gorl[0]->name, m.get("смИМЯ").c_str(), 6);
    int cm = m.geti("цфCol_Mar");
    int cs = m.geti("цфCol_Str");
    if ((gorl[0]->Col_Mar != cm) || (gorl[0]->Col_Str != cs)) {
        Destroy();
        gorl[0]->Col_Mar = cm;
        gorl[0]->Col_Str = cs;
        Creat();
    }
    // при изменении размеров - пересоздаем
    gorl[0]->bit_m             = m.geti("цфbit_m");
    gorl[0]->bit_ksp           = m.geti("цфbit_ksp");
    gorl[0]->bit_kzm           = m.geti("цфbit_kzm");
    gorl[0]->nom_fiz           = m.geti("цфnom_fiz");
    gorl[0]->impuls_ksp        = m.geti("тсimpuls_ksp");
    gorl[0]->impuls_kzm        = m.geti("тсimpuls_kzm");
    gorl[0]->impuls_ks         = m.geti("тсimpuls_ks");
    gorl[0]->impuls_ks_i       = m.geti("тсimpuls_ks_i");

    strncpy(gorl[0]->Sign_i.name, m.get("смSign_i_name").c_str(), 6);

    TParString ps("", ";");
    // загружаем номера стрелок
    ps.SetVal(m.get("СТР"));
    for (int j = 0; j < gorl[0]->Col_Str; j++)
        gorl[0]->Strel_N[j] = (char)ps.GetInt(j, 0);
    // загружаем матрицу   +;+;+;Нд;impuls_m;impuls_km
    for (int i = 0; i < cm; i++) {
        ps.SetVal(m.get("M" + IntToStr(i)));
        for (int j = 0; j < gorl[0]->Col_Str; j++)
            gorl[0]->Matr[i][j] = (char)ps.GetInt(j, 0);

        strncpy(gorl[0]->Sign[i].name, ps.GetStr(cm + 0).c_str(), 6);
        gorl[0]->impuls_m[i] = ps.GetInt(cm + 1, 0);
        gorl[0]->impuls_km[i] = ps.GetInt(cm + 2, 0);
    }

}

