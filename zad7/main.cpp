#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

struct Node{
    string nazwa;
    bool odwiedzony=false;
};

int main()
{
    ios_base::sync_with_stdio(false);
    int t; // liczba zestawow danych
    int n,m; // n - liczba nazwisk, m - liczba par nazwisk
    cin >> t;
    bool czy_dobra_lista;


    for(int i=0; i<t; i++){ // pobieramy zestawy danych
       string nazwa1; // zmienna ktora przechowuje proponowana kolejnosc nazwisk
        string nazwa2;
        unordered_map<string,int> mapa;
        cin >> n >> m;

        list<Node*> * sasiedzi = new list<Node*>[n]; // tworzymy tablice list sasiadow 
        Node * osoba = new Node[n]; // tworzymy tablice nodow ktore wkladamy do listy
        czy_dobra_lista=true;
        list<Node*>::iterator il;   // iterator potrzebny do przechodzenia listy od poczatku do konca

        for(int j = 0; j < n; j++){     //pobieramy nazwiska
            cin >> osoba[j].nazwa;
            mapa.emplace(osoba[j].nazwa,j);
        }
        for(int j = 0; j < m; j++){     // pobieramy pary nazwisk
            cin >> nazwa1 >> nazwa2;
            sasiedzi[mapa[nazwa2]].push_back(osoba+mapa[nazwa1]);
        }
        for(int i=0; i<n; i++){
            cin >> nazwa1;
            if(czy_dobra_lista == false){
//               if(i > n/2){     // aby nie robic wielu niepotrzebnych okrazen to po spelnieniu warunku wzytujemy wszystkie dane ktore i tak nie sa nam potrzebne ale musimy je wczytac bo inaczej program nie bedzie dzialal
//                    getline(cin,nazwa1);  // jednak to nie zdaje egzaminu nie dotego ze zwieksza pamiec to i zwieksza czas xD
//                    i=n;
//                }
                continue;
            }
            int tmp = mapa[nazwa1]; // przechowujemy wartosc kojenosci aktualnej nazwy w zmiennej tmp 
            il = sasiedzi[tmp].begin();
            if(sasiedzi[tmp].empty() == true)   // jezeli lista jest pusta czyli nie potrzebuje nikogo wczesniej wiec od razu ja mozna odwiedzic
                osoba[tmp].odwiedzony=true;
            else{
                while(il != sasiedzi[tmp].end()){   // jezeli sa elementy to sprawdzamy czy wszystkie sa odwiedzone
                    if((*il)->odwiedzony == true){
                        il++;
                        continue;
                    }else{
                        czy_dobra_lista=false;  // jesli nie to lista jet zla konczymy przegladanie
                        break;
                    }
                }
            }
            osoba[tmp].odwiedzony=true; // jezeli jest dobra to odwiedzamy przeszukiwany wierzcholek
        }
        if(czy_dobra_lista == true) // wyswietlenie
            cout << "TAK"<<endl;
        else
            cout << "NIE"<<endl;

        delete [] osoba;
    }


    return 0;
}
