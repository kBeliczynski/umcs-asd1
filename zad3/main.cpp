#include <iostream>

using namespace std;

struct wezel{
    string nazwa;
    int przesuniecie;
    int nowe_przesuniecie;
    wezel * lewy;
    wezel * prawy;
    wezel(string nazwa, int przesuniecie) {this->nazwa = nazwa; this->przesuniecie = przesuniecie; lewy=prawy=this;}
    wezel(string nazwa, int przesuniecie, int nowe_przesuniecie) {this->nazwa = nazwa; this->przesuniecie = przesuniecie; this->nowe_przesuniecie = nowe_przesuniecie; lewy=prawy=this;}
};

class Lista{
public:
    int tmp_przesuniecie; // tu zapisuje przesuniecie usuwanego elementu
    wezel * wsk; // wskaznik na dowolny element
    int ile; // ilosc dodanych wezlow
//    bool kierunek; // jezeli default(true to idz w prawo) jezeli false idz w lewo
//    bool gdzie_dodac; // default(true = dodaj wezel z prawej strony) , false = dodaj z lewej

    Lista(){
        wsk=nullptr;
        ile=0;
//        kierunek=false;
//        gdzie_dodac=true;
    }
    ~Lista(){} // niepotrzebna poniewaz w metodzie usun usuwamy wskaznik i zmieniamy go na NULL

    void licz_przesuniecie_gdy0(int liczba){ // stara wersja nie przechodzi czasu
        bool kierunek=true;
        if(liczba<0)
            liczba = -liczba;
        else
            kierunek = false;
        if(kierunek){
            for(int i=0; i<liczba; i++)
                wsk=wsk->lewy;
        }else{
            for(int i=0; i<liczba; i++)
                wsk=wsk->prawy;
        }
    }
    void licz_przesuniecie_gdy0v2(int liczba){ // szybciej sie wykonuje poniewaz nie kreci sie tyko lliczy pozycje
        int pol = ile/2;
        bool kierunek=true;
        if(liczba<0){
            liczba = -liczba;
            liczba = liczba%ile;
//            if(liczba <= pol)
//                kierunek = true;
//            else
            if(liczba > pol){
                liczba = ile-liczba;
                kierunek = false;
            }
        }else{
            liczba = liczba%ile;
            if(liczba <= pol)
                kierunek = false;
            else if(liczba > pol){
                liczba = ile-liczba;
                kierunek = true;
            }
        }
        if(kierunek){
            for(int i=0; i<liczba; i++)
                wsk=wsk->lewy;
        }else{
            for(int i=0; i<liczba; i++)
                wsk=wsk->prawy;
        }
    }

    void licz_przesuniecie_gdyN(int liczba){ // stara wersja nie przechodzi czasu
        bool kierunek=true;
        if(liczba<0){
            liczba++;
            liczba = -liczba;
        }else
            kierunek = false;
        if(kierunek){
            for(int i=0; i<liczba; i++)
                wsk=wsk->lewy;
        }else{
            for(int i=0; i<liczba; i++)
                wsk=wsk->prawy;
        }
    }
    void licz_przesuniecie_gdyNv2(int liczba){ // szybciej sie wykonuje poniewaz nie kreci sie tyko lliczy pozycje
        int pol = ile/2;
        bool kierunek=true;
        if(liczba<0){
            liczba++;
            liczba = -liczba;
            liczba = liczba%ile;
//            if(liczba <= pol)
//                kierunek = true;
//            else
            if(liczba > pol){
                liczba = ile-liczba;
                kierunek = false;
            }
        }else{
            liczba = liczba%ile;
            if(liczba <= pol)
                kierunek = false;
            else if(liczba > pol){
                liczba = ile-liczba;
                kierunek = true;
            }
        }
        if(kierunek){
            for(int i=0; i<liczba; i++)
                wsk=wsk->lewy;
        }else{
            for(int i=0; i<liczba; i++)
                wsk=wsk->prawy;
        }
    }

    void dodajWezel(string nazwa, int przesuniecie,int nowe_przesuniecie = 0, bool gdzie_dodac=false){
        wezel * nowy = new wezel(nazwa,przesuniecie,nowe_przesuniecie);
        if(ile == 0)
            wsk = nowy;
        else{
            wezel * l = wsk->lewy;
            wezel * r = wsk->prawy;
            if(!gdzie_dodac){ // dodaje za elementem
                wsk->lewy=nowy;
                nowy->prawy=wsk;
                nowy->lewy=l;
                l->prawy=nowy;
                if(ile == 1) wsk->prawy=nowy;
            }else{ //dodaje p
                wsk->prawy=nowy;
                nowy->lewy=wsk;
                nowy->prawy=r;
                r->lewy=nowy;
                if(ile == 1) wsk->lewy=nowy;
            }
        }
        ile++;
    }
    bool usun(){ // po usunieciu ustawia sie na nastepnym elemencie co skutkuje tym ze gdy bedziemy chcieli sie przesuwac do tylu trzeba bedzie sie przesunac o jedno pole mniej. Przesuniecie do przodu zostaje bez zmian
        if(ile == 0) return false;
        cout << this->wsk->nazwa << " ";
        cout.flush();
        if(ile == 1) {
            delete wsk;
            wsk=nullptr;
        }else{
            //tmp_przesuniecie = wsk->przesuniecie;
            wezel* tmp = wsk;
            wsk = wsk->lewy;
            wsk->prawy=tmp->prawy;
            wsk->prawy->lewy=wsk;
            delete tmp;
        }
        ile--;
        return true;
    }
    bool usun_bez_wyswietlania(){ // po usunieciu ustawia sie na nastepnym elemencie co skutkuje tym ze gdy bedziemy chcieli sie przesuwac do tylu trzeba bedzie sie przesunac o jedno pole mniej. Przesuniecie do przodu zostaje bez zmian
        if(ile == 0) return false;
        if(ile == 1) {
            delete wsk;
            wsk=nullptr;
        }else{
            //tmp_przesuniecie = wsk->przesuniecie;
            wezel* tmp = wsk;
            wsk = wsk->prawy;
            wsk->lewy=tmp->lewy;
            wsk->lewy->prawy=wsk;
            delete tmp;
        }
        ile--;
        return true;
    }
    void pokaz_nazwe_wezla(){
        cout<<wsk->nazwa<< "" ;
    }
    void PokazListe(){
        for(int i=0; i<ile; i++){
            cout << i << ".  " << wsk->nazwa << " " << wsk->przesuniecie << " " << wsk->nowe_przesuniecie << endl;
            licz_przesuniecie_gdy0(1);
        }
    }
    void zastapZero(string nazwa, int przesuniecie, int nowe_przesuniecie){
        dodajWezel(nazwa,przesuniecie,true);
        wsk->przesuniecie = nowe_przesuniecie;
    }

};

int main()
{

    ios_base::sync_with_stdio(false);

    int n,s,p;
    string nazwa;
    int przesuniecie;
    int nowe_przesuniecie;
    cin >> n >> s;
    Lista l1;
    for(int i=0; i<n; i++){
        cin >> nazwa >> przesuniecie;
        l1.dodajWezel(nazwa,przesuniecie);
    }
    cin >> p;
    Lista l2;
        for(int i=0; i<p; i++){
            cin >> nazwa >> przesuniecie >> nowe_przesuniecie;
            l2.dodajWezel(nazwa,przesuniecie, nowe_przesuniecie);
        }

        l1.licz_przesuniecie_gdy0(s); // ustawia nam poczatkowa wartosc
        while(1){
            if(l1.wsk->przesuniecie == 0){ // sprawdza czy przesuniecie nie jest rowne 0
                l1.zastapZero(l2.wsk->nazwa, l2.wsk->przesuniecie, l2.wsk->nowe_przesuniecie); // jezeli tak to robi miejsce przed wskaznikiem, wstawia tam wartosc z 2 listy, zmienia wartosc przesuniecia obecnego wskaznika i ustawia sie na poczatkowy wskaznik
                l2.usun_bez_wyswietlania(); // usuwa element z 2 listy
                l1.licz_przesuniecie_gdy0v2(l1.wsk->przesuniecie); // opis wyzej
            }
            else if(l1.wsk->przesuniecie != 0){
                l1.tmp_przesuniecie = l1.wsk->przesuniecie; // przed usunieciem zapisujemy wartosc przesuniecia wskaznika
                l1.usun(); // opis wyzej
                if(l1.ile == 0)
                    break; // sprawdza czy sa elementy w lilscie jesli nie przerywa petle
                l1.licz_przesuniecie_gdyNv2(l1.tmp_przesuniecie); // opis wyzej
            }
        }


    return 0;
}
