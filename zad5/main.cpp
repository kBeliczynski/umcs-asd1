#include <iostream>

using namespace std;

struct drzewo_l;

class Lista{
public:
    drzewo_l * pierwszy = nullptr;
    drzewo_l * ostatni = nullptr;
    int ilosc_synow = 0;

    bool czy_pusta();
    void push(int wartosc);
    void pop();
    bool czy_istnieje(int liczba);


};

struct drzewo_l {
    int wartosc ;
    bool czy_odwiedzony;
//    drzewo_l * ojciec = nullptr;
    drzewo_l * nastepny = nullptr;
    Lista synowie;
    drzewo_l(int wartosc);
    void odwiedz(drzewo_l * v);
    void preorder(drzewo_l * v);

};
static drzewo_l * odnaleziony = nullptr; // tworzymy wskaznik ktorego uzywamy do przechodzenia po elementach i ustawiania go na odpwiednim elemencie
int main()
{
    ios_base::sync_with_stdio(false);

    int n,x;
    int liczba;

    drzewo_l * korzen = new drzewo_l(0);  // ustawiamy na true by nie wyswietlac pierwszego wezla
    korzen->czy_odwiedzony=true;
    cin >> n;

    for(int i=0; i<n; i++){
        odnaleziony = korzen;   // ustawiamy nasz wsk na poczatek czyli korzen
        cin >> x;
        for(int i=0; i<x; i++){
            cin >> liczba;
//            cout << "liczba sprawdzana:" << odnaleziony->wartosc << "liczba wprowadzona: "<< liczba<<endl;
            if(odnaleziony->synowie.czy_istnieje(liczba)) // sprawdzamy czy w liscie synow juz istnieje dany element jesli tak to ustawiamy na niego wskaznik a jesli nie to dodajemy go i ustawiamy na nim wskaznik
                ;
            else{ // jezeli nie bylo elementu to dodajemy go do listy elementow
                odnaleziony->synowie.push(liczba);
                odnaleziony = odnaleziony->synowie.ostatni; // ustawiamy wskaznik na nowo dodanym elemencie
            }
        }
    }

    korzen->preorder(korzen); // uzywamy preorder do wyswietlania elementow

    return 0;
}

bool Lista::czy_pusta(){
    return (ilosc_synow == 0);
}

bool Lista::czy_istnieje(int liczba){ // sprawdza czy podany element istnieje w naszej liscie synow
    drzewo_l * it = this->pierwszy;
    for(int i=0;i<ilosc_synow;i++){
        if(it->wartosc == liczba){
            odnaleziony = it; // jesli tak to ustawiamy na nim wskaznik
            return true; 
        }
        else
            it = it->nastepny;
    }
    return false;
}

void Lista::push(int wartosc){
    drzewo_l * wsk = new drzewo_l(wartosc);
    if(pierwszy == nullptr){
        pierwszy = ostatni = wsk;
        ilosc_synow = 1;
    }
    else{
        this->ostatni -> nastepny = wsk;
        this->ostatni = wsk;
        ilosc_synow++;
        }
    }

void Lista::pop(){
    drzewo_l * tmp = this->pierwszy;
    this->pierwszy = this->pierwszy->nastepny;
    delete tmp;
}

drzewo_l::drzewo_l(int wartosc){
    this->wartosc = wartosc;
    czy_odwiedzony = false;
}

void drzewo_l::odwiedz(drzewo_l * v){
    if(v->czy_odwiedzony == false){
        cout << v->wartosc << " ";
        v->czy_odwiedzony = true;
    }
}

//void drzewo_l::preorder(drzewo_l * v){
//    odwiedz(v);
//    drzewo_l * it = v->synowie.pierwszy;
//    while(it != v->synowie.ostatni){
//       preorder(it) ;
//       it = it->nastepny;
//    }
//}
void drzewo_l::preorder(drzewo_l * v){
    odwiedz(v);
    for(int i = 0; i<v->synowie.ilosc_synow;i++){
       preorder(v->synowie.pierwszy);
       v->synowie.pierwszy = v->synowie.pierwszy->nastepny;
    }
}
