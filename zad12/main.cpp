#include <iostream>
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

struct Dokumenty{
public:
    int id; // unikalne id  (od 1 do n)
    int priorytet;  // (od 0 do 10)
    int kod;    // losowy kod niekoniecnie unikalny (od 0 do 10000000)
    int tematyka[4]{-1,-1,-1,-1};
    int n;  //ilosc elementow

    bool operator < (const Dokumenty &x)const //zdefiniowanie zachowania się
               {                //operatora < potrzebnego przy sortowaniu
                 return kod<x.kod;
               }
};
void wczytaj(int n, Dokumenty* d){
    int tmp;
    for(int i=0; i<n; i++){
        cin >> tmp;
        cin >> d[tmp-1].priorytet >> d[tmp-1].kod >> d[tmp-1].n;
        d[tmp-1].id=tmp;
        for(int j=0; j<d[tmp-1].n; j++){
            cin >> d[tmp-1].tematyka[j];
        }
    }
}
void sortuj_priorytet(int n, Dokumenty* tab){
    int pom[11]{0};         // tworzymy tablice o rozmiarze 11 by miescila wartosci od 0 do 10
    Dokumenty * sort = new Dokumenty[n];
    int i;
    for(i=0;i<n;i++)        //count sort z wykladu
        pom[tab[i].priorytet]++;
    pom[0]--;
    for(i=1;i<11;i++)
        pom[i]+= pom[i-1];
    for(i=n-1;i>=0;i--){
        sort[pom[tab[i].priorytet]]=tab[i];
    pom[tab[i].priorytet]--;
    }
    //przepisywanie do struktury d
    for(int i=0; i<n; i++){
        tab[i] = sort[i];
    }
    delete [] sort;
}
//                       dokumenty,    0     , 10000000,  kon/4,   n
void sortuj_kody(Dokumenty * tab, int pocz ,long int kon ,int k , int n ){  //sortowanie kubelkowe z wykladu
    vector<Dokumenty> *pom = new vector<Dokumenty>[k];
    for(int i=0;i<n;i++){
        double suma = 1.0*tab[i].kod/kon;   //na pocztku zapisujemy to do double poniewaz wystepowaly bledy i zamienialo na liczbe z -
        unsigned long long int indeks=k*suma;
        pom[indeks].push_back(tab[i]);
    }
    int ind=0;
    for(int i=0;i<k;i++){
//        bubbleSort(pom[i],pom[i].size());
        stable_sort(pom[i].begin(),pom[i].end());
        for(int j=0; j<pom[i].size();j++){
            tab[ind]=pom[i][j];
            ind++;
        }
    }
//    delete [] pom;
}
void sortuj_leksykograficznie( Dokumenty * tab, int n){ //tab - tablica elementow, n - ilosc elementow
    int k=3; //poniewaz posiada 4 pola a chcemy sie dostac do pol od 0 do 3
    int pom[257]{0};    //poniewaz mamy wartosci od 0 do 255 + gdy nie ma danych to -1 , lecz bedziemy to reprezentowaac jako wartosc+1 by wyeliminowac wartosc -1
    Dokumenty tmp[n]; //tworzymy tablice tmp do ktorej bedziemy na zmiane przepisywali wartosci
    for(int i=k; i>=0; i--){            //sortowanie przez zliczanie z wykladu
        //zerujemy tablice pomocnicza
        for(int j=0; j<257; j++){
            pom[j]=0;
        }
        if(i%2==1){   // jezeli nieparzysta to przepisujemy do tmp
            for(int j=0;j<n;j++)
                pom[tab[j].tematyka[i]+1]++;
            pom[0]--;
            for(int j=1;j<257;j++)
                pom[j]+= pom[j-1];
            for(int j=n-1;j>=0;j--){
                tmp[pom[tab[j].tematyka[i]+1]]=tab[j];
            pom[tab[j].tematyka[i]+1]--;
            }
        }
        else{   //jezeli parzyst to przepisujemy do oryginalnej tab (dzieki temu oszczedzimy miejsce na tworzenie kilku tablic tmp)
            for(int j=0;j<n;j++)
                pom[tmp[j].tematyka[i]+1]++;
            pom[0]--;
            for(int j=1;j<257;j++)
                pom[j]+= pom[j-1];
            for(int j=n-1;j>=0;j--){
                tab[pom[tmp[j].tematyka[i]+1]]=tmp[j];
            pom[tmp[j].tematyka[i]+1]--;
            }
        }
    }
}

unsigned long long int licz_sume(Dokumenty* d,int n){
    unsigned long long int suma=0;
    for(unsigned long long int i=0; i<n; i++){
        suma += ((d[i].kod*i)%100000007);
        suma %= 100000007;
    }
    return suma;
}

int main(){
    ios_base::sync_with_stdio(false);
    int n; // ilosc dokumendow
    int kolejnosc_sortowan[4];

    cin >> n;
    Dokumenty * dokumenty = new Dokumenty[n];
    wczytaj(n,dokumenty);
    for(int i=0; i<4; i++){
        cin >> kolejnosc_sortowan[i];
    }

    if(kolejnosc_sortowan[1] == 1){
        //wtedy sortujemy tylko dla kolejnosc_sortowan[0] i liczymy sume
        if(kolejnosc_sortowan[0] == 2)
            sortuj_priorytet(n,dokumenty);
        if(kolejnosc_sortowan[0] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        if(kolejnosc_sortowan[0] == 4)
            sortuj_leksykograficznie(dokumenty,n);
    }
    else if(kolejnosc_sortowan[2] == 1){
        if(kolejnosc_sortowan[1] == 2)
            sortuj_priorytet(n,dokumenty);
        else if(kolejnosc_sortowan[1] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        else
            sortuj_leksykograficznie(dokumenty,n);
        if(kolejnosc_sortowan[0] == 2)
            sortuj_priorytet(n,dokumenty);
        else if(kolejnosc_sortowan[0] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        else
            sortuj_leksykograficznie(dokumenty,n);
    }
    else if(kolejnosc_sortowan[3] == 1){
        if(kolejnosc_sortowan[2] == 2)
            sortuj_priorytet(n,dokumenty);
        else if(kolejnosc_sortowan[2] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        else
            sortuj_leksykograficznie(dokumenty,n);
        if(kolejnosc_sortowan[1] == 2)
            sortuj_priorytet(n,dokumenty);
        else if(kolejnosc_sortowan[1] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        else
            sortuj_leksykograficznie(dokumenty,n);
        if(kolejnosc_sortowan[0] == 2)
            sortuj_priorytet(n,dokumenty);
        else if(kolejnosc_sortowan[0] == 3)
            sortuj_kody(dokumenty,0,10000000,350000,n);
        else
            sortuj_leksykograficznie(dokumenty,n);
    }
    cout << licz_sume(dokumenty,n);
    return 0;
}
