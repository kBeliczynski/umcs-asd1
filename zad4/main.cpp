#include <iostream>
#include <cmath>

using namespace std;

class Naukowiec{
public:
    string imie;
    string nazwisko;
    int zdolnosc;
    Naukowiec * nastepny;
    Naukowiec(string imie, string nazwisko, int zdolnosc){
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->zdolnosc = zdolnosc;
        this->nastepny = nullptr;
    }
};

class Kolejka{
public:
    Naukowiec* pierwszy=nullptr;
    Naukowiec* ostatni=nullptr;
    Naukowiec* wsk_poczatek1=nullptr; // wskaznik na poczatek pierwszego bloku w kolejce (blok to polowa naukowcow)
    Naukowiec* wsk_poczatek2=nullptr; // wskaznik na poczatek drugiego bloku
    Naukowiec* najlepsza_poz=nullptr; // wskazuje najlepsza pozycje poczatek1
    int max1=0,max2=0; // max wartosc dla pierwszeo bloku i drugiego bloku
    int min1=1000,min2=1000; // min wartosc dla pierwszego i drugiego bloku
    int ilosc_min1=0,ilosc_min2=0; // liczymy wystapienia min w kolejce aby przy usuwaniu min nie przechodzic calej kolejki
    int ilosc_max1=0,ilosc_max2=0; // liczymy wystapienia max w kolejce aby przy usuwaniu max nie przechodzic calej kolejki
    int sum1=0,sum2=0; // suma dla pierwszego i drugiego bloku
    double sr1=0.0,sr2=0.0; // potrzebna do liczenia najlepszego indexu (njalepszego ulozenia elementow)
    double najlepsze_ustawienie=2000; 
    int ile; // ilosc elementow
    int roznica=0;

    Kolejka(int roznica, int ile_elementow){ // potrzebna jest ilosc by podczas podawania elementow od razu liczyc max min i sume
        this->ile = ile_elementow;
        this->roznica = roznica;
    }
    void licz_sr(){
        sr1 = (1.0*sum1)/(1.0*ile/2.0);
        sr2 = (1.0*sum2)/(1.0*ile/2.0);
    }
    void push(string imie,string nazwisko,int zdolnosc){ // dodaje element, wyznacza min,max oraz ich ilosc i liczy sume (robie to na poczatku by zminimalizowac czas wykonania i nie edytowac dzialajacych funckji)
        static int licznik=0;
        Naukowiec* n = new Naukowiec(imie,nazwisko,zdolnosc);
        if(licznik < (ile/2)){
            sum1+=n->zdolnosc;
            
            if(min1 > n->zdolnosc){
                min1 = n->zdolnosc;
                ilosc_min1 = 1;
            }
            else if(min1 == n->zdolnosc){
                ilosc_min1++;
            }
                
            if(max1 < n->zdolnosc){
                max1 = n->zdolnosc;
                ilosc_max1 = 1;
            }
            else if(max1 == n->zdolnosc){
                ilosc_max1++;
            }
                
        }else{
            sum2+=n->zdolnosc;
            if(min2 > n->zdolnosc){
                min2 = n->zdolnosc;
                ilosc_min2 = 1;
            }
            else if(min2 == n->zdolnosc){
                ilosc_min2++;
            }
            if(max2 < n->zdolnosc){
                max2 = n->zdolnosc;
                ilosc_max2 = 1;
            }
            else if(max2 == n->zdolnosc){
                ilosc_max2++;
            }
        }
        if(this->pierwszy == nullptr){ 
            this->pierwszy = this->ostatni = this->wsk_poczatek1 = n;
        }else{
            this->ostatni->nastepny = n;
            this->ostatni = n;
            this->ostatni->nastepny=this->pierwszy;
        }
        licznik++;
    }
    void ustaw_poczatek2(){ // ustawia poczatek 2 wskznika 
        Naukowiec* tmp = this->pierwszy;
        for(int i=0; i<=((ile/2)-1); i++){
             tmp = tmp->nastepny;
        }
        this->wsk_poczatek2 = tmp;
    }
    void showPoz(){ // wyswietl najlepsze ustawienie dwoch kolejek oddzielone spacja 
        Naukowiec * tmp = this->najlepsza_poz;
        for(int i=0;i<ile;i++){
            cout << tmp->imie << " " << tmp->nazwisko << " " <<endl;
            if(i == ((ile/2)-1)){
                cout << endl;
            }
        tmp = tmp->nastepny;
        }
    }
    void czy_mozliwe(){ // sprawdza czy miesci sie w roznicy i liczy najlepsze ustawienie
        if(!((max1-min1)>roznica || ((max2-min2)>roznica))){
            licz_sr();
            if(najlepsze_ustawienie > abs(sr1-sr2)){ 
                najlepsze_ustawienie = abs(sr1-sr2);
                najlepsza_poz = wsk_poczatek1;
            }
        }
    }
    void szukaj_max1(){
        if(ilosc_max1 == 1){
           Naukowiec* tmp = wsk_poczatek1;
           tmp = tmp->nastepny;
           max1 = tmp->zdolnosc;
           for(int i=0; i<((ile/2)-1);i++){
               if(max1 < tmp->zdolnosc)
                   max1 = tmp->zdolnosc;
               tmp = tmp->nastepny;
        }
    }else
            ilosc_max1--;
    }
    void szukaj_min1(){
        if(ilosc_min1 == 1){
           Naukowiec* tmp = wsk_poczatek1;
           tmp = tmp->nastepny;
           min1 = tmp->zdolnosc;
           for(int i=0; i<((ile/2)-1);i++){
               if(min1 > tmp->zdolnosc)
                   min1 = tmp->zdolnosc;
               tmp = tmp->nastepny;
           }
        }else
            ilosc_min1--;
    }
    void szukaj_max2(){
        if(ilosc_max2 == 1){
           Naukowiec* tmp = wsk_poczatek2;
           tmp = tmp->nastepny;
           max2 = tmp->zdolnosc;
           for(int i=0; i<((ile/2)-1);i++){
               if(max2 < tmp->zdolnosc)
                   max2 = tmp->zdolnosc;
               tmp = tmp->nastepny;
           }
        }else
            ilosc_max2--;
    }
    void szukaj_min2(){
        if(ilosc_min2 == 1){
           Naukowiec* tmp = wsk_poczatek2;
           tmp = tmp->nastepny;
           min2 = tmp->zdolnosc;
           for(int i=0; i<((ile/2)-1);i++){
               if(min2 > tmp->zdolnosc)
                   min2 = tmp->zdolnosc;
               tmp = tmp->nastepny;
           }
        }else
            ilosc_min2--;
    }

    void sprawdz(){

        if(wsk_poczatek2->zdolnosc >= max1)
               max1 = wsk_poczatek2->zdolnosc;
        else if(wsk_poczatek1->zdolnosc == max1)
                szukaj_max1();
        if(wsk_poczatek2->zdolnosc <= min1)
               min1 = wsk_poczatek2->zdolnosc;
        else if(wsk_poczatek1->zdolnosc == min1)
                szukaj_min1();
        sum1 += (wsk_poczatek2->zdolnosc - wsk_poczatek1->zdolnosc);
        if(wsk_poczatek1->zdolnosc >= max2)
                max2 = wsk_poczatek1->zdolnosc;
        else if(wsk_poczatek2->zdolnosc == max2)
                szukaj_max2();
        if(wsk_poczatek1->zdolnosc <= min2)
                min2 = wsk_poczatek1->zdolnosc;
        else if(wsk_poczatek2->zdolnosc == min2)
                szukaj_min2();
        sum2 += (wsk_poczatek1->zdolnosc - wsk_poczatek2->zdolnosc);
        wsk_poczatek1 = wsk_poczatek1->nastepny;
        wsk_poczatek2 = wsk_poczatek2->nastepny;
        czy_mozliwe();

    }


};







int main()
{
    ios_base::sync_with_stdio(false);
    int n,v; // n - ilosc naukowcow, v - max roznica miedzy zdolnosciami naukowcow
    string f,s; // f - imie naukowca, s - nazwisko naukowca
    int i; // zdolnosc naukowca

    cin >> n >> v;
    Kolejka k1(v,n);
    for(int j=0;j<n;j++){
        cin >> f >> s >> i;
        k1.push(f,s,i);
    }
    k1.czy_mozliwe();
    k1.ustaw_poczatek2();

    for(int i=0; i<((n/2)-1);i++){
        k1.sprawdz();
    }


    if(k1.najlepsza_poz == nullptr)
        cout<<"NIE";
    else
    k1.showPoz();


    return 0;
}