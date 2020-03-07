#include <iostream>
#include<cstdlib>
#include<iomanip>
#include<algorithm>

    using namespace std;

    void wyswietl(long long int ** tablica_pom1, long long int ** tablica_pom2, int n){
        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<7; j++)
               cout << tablica_pom1[i][j] << " ";
        cout << endl;
        }
        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<7; j++)
               cout << tablica_pom2[i][j] << " ";
        cout << endl;
        }
        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    }

    struct cytuj{
        int medium1,dzien1;
        int medium2,dzien2;

        bool operator < (const cytuj &x)const //zdefiniowanie zachowania się
        {                //operatora < potrzebnego przy sortowaniu
          if(dzien2 == x.dzien2)
              return dzien1<x.dzien1;
          return dzien2<x.dzien2;
        }
    };
    #define ilosc_dni 7
    int main()
    {

        long long int n;      // liczba analzowanych mediow
        long long int s;      // numer mediow ktore jako pierwsze uwyzkalo informacje
        long long int d;      // w ktorym dniu uzyskalo informacje
        long long int l; // liczba dni ile informacje sie rozprzestrzenialy
        long long int m;      // ilosc wierszy danych wejsciowych
        long long int ilosc_uplynietych_dni=0;
        long long int ilosc_cytowan=0;
        bool wybor_tab=true; // true - tab1, false - tab2
        bool pierwsze_przejscie=true; // oznacza ze pierwszy raz liczymy sume
//        bool pierwszy_raz=true;
        bool raz_na_petle=true;
        bool ktora_teraz_sumowana=false; // false - tab2, true - tab1
        cin >> n >> s >> d >> l >> m;

        //tworzymy tablice w ktorej bedziemy zapisywac wszystke cytowania
        long long int ** tablica_cytowan = new long long int * [4];
        for (int i = 0; i<4; i++)
            tablica_cytowan[i] = new long long int [m]{};

        //dwie tab pomocnicze w ktorych bedziemy trzymac ilosc cytowan
        long long int ** tablica_pom1 = new long long int * [n];
        for (int i = 0; i<n; i++)
            tablica_pom1[i] = new long long int [ilosc_dni]{};
        long long int ** tablica_pom2 = new long long int * [n];
        for (int i = 0; i<n; i++)
            tablica_pom2[i] = new long long int [ilosc_dni]{};

        cytuj tab_cytowan[m];
        //zapisujemy wszystkie cytowania do tablicy
        for(int i=0; i<m; i++){
            //      medium1                     dzien1                  medium2                     dzien2
            cin >> tab_cytowan[i].medium1 >>  tab_cytowan[i].dzien1 >>  tab_cytowan[i].medium2 >>  tab_cytowan[i].dzien2;
        }
         sort(tab_cytowan,tab_cytowan+m);

         //wyswielta otrzymana tablice cytown
//         for(int i=0; i<m; i++){
//             cout << tab_cytowan[i].medium1   <<  tab_cytowan[i].dzien1 <<  tab_cytowan[i].medium2 <<  tab_cytowan[i].dzien2 << endl;
//         }
        if(n==1){
            cout << "1";
            return 0;
        }

        tablica_pom1[s][d] = 1;  // medium ktore jako pierwsze dostaje informacje

    while(1){   //petla nieskonczona ktora ciagle wywoluje cytowania w kazdym kolejnym tygodniu az do spelnienia warunku gdzie ilosc_dni > l
        ktora_teraz_sumowana=!ktora_teraz_sumowana;
        wybor_tab=ktora_teraz_sumowana;
        raz_na_petle=true;
        for(int i=0; i<m; i++){
 //                wyswietl(tablica_pom1,tablica_pom2,n); //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@222
                if(tab_cytowan[i].dzien1 >= tab_cytowan[i].dzien2){
                    if(raz_na_petle==false){
                        wybor_tab=!wybor_tab;
                        raz_na_petle=true;
                    }
                    if(wybor_tab == true){
                   tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                        tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1] += tablica_pom1[tab_cytowan[i].medium2][tab_cytowan[i].dzien2]%100000007;
 //                  tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                        continue;
                    }
                    else{
                tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                        tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1] += tablica_pom2[tab_cytowan[i].medium2][tab_cytowan[i].dzien2]%100000007;
 //                  tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                        continue;
                    }
                }
                if(tab_cytowan[i].dzien1 < tab_cytowan[i].dzien2){
                    if(raz_na_petle==true){
                        wybor_tab=!wybor_tab;
                        raz_na_petle=false;
                    }
                    if(wybor_tab==false){
  //                 tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                           tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1] += tablica_pom1[tab_cytowan[i].medium2][tab_cytowan[i].dzien2]%100000007;
//                    tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                    }
                    else{
 //                  tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                        tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1] += tablica_pom2[tab_cytowan[i].medium2][tab_cytowan[i].dzien2]%100000007;
                    }
                 }
                tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom1[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
                 tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]=tablica_pom2[tab_cytowan[i].medium1][tab_cytowan[i].dzien1]%100000007;
            }
//            wyswietl(tablica_pom1,tablica_pom2,n); //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@222
            if(wybor_tab == false){
                pierwsze_przejscie=false;
            }
//            gdy petla sie skonczy to wiemy ze wykonalismy wszystkie cytowania, wybor_tab jest ustawione na przeciwny, wiec ustawiamy znowu na przeciwny i mozemy zliczac sume i przeminiete dni
//            cout << "teraz sumujemy wyniki z tablicy o numerze:" << (wybor_tab)?"tablica 1":"tablica2";
            for(long long int i=0; i<ilosc_dni; i++){
                if(pierwsze_przejscie){
                    i=(d-1);
                    pierwsze_przejscie=false;
                    continue;
                }
                for(int j=0; j<n; j++){
//                   ilosc_cytowan=ilosc_cytowan%100000007;
//                    if(pierwszy_raz){
//                         ilosc_cytowan += tablica_pom1[j][i]%100000007;
////                         ilosc_cytowan=ilosc_cytowan%100000007;
//                         tablica_pom1[j][i]=0;
//                    }
                    if(ktora_teraz_sumowana==false){
                         ilosc_cytowan += tablica_pom2[j][i]%100000007;
                         tablica_pom2[j][i]=0;
                        ilosc_cytowan=ilosc_cytowan%100000007;
                    }
                    else{
                        ilosc_cytowan += tablica_pom1[j][i]%100000007;
                        tablica_pom1[j][i]=0;
//                        ilosc_cytowan=ilosc_cytowan%100000007;
                    }
                    ilosc_cytowan=ilosc_cytowan%100000007;
                }
                ilosc_uplynietych_dni++;
                if(ilosc_uplynietych_dni >= l ){
                    ilosc_cytowan=ilosc_cytowan%100000007;
                    cout << ilosc_cytowan%100000007;
                    return 0;
                }
            }
    }
    }
