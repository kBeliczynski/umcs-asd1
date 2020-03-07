#include <iostream>

using namespace std;

struct pasazer{
    int a;  // wartosc na ktorej stacji wsiada
    int b;  // wartosc na ktorej stacji wysiada
};

int podziel(pasazer tab[], int tmp1, int tmp2) // funkcja ktora ustawia liczny mniejsze i rowne od x w pierwszej czesci a wieksz ew drugiej czesci
{
    int x = tab[tmp1].b; // obieramy x
    int i = tmp1;   // index oznaczajacy pozycje
    int j = tmp2;   // index oznaczajacy pozycje
    int  tempA, tempB;      // zmienna tymczasowa przechowujaca wartosci A i B struktury pasazer
    while (true)
    {
        while (tab[j].b > x) // dopoki elementy sa wieksze od x    //dzieki tym warunkom sortujemy malejaco jezeli chceli bysmy
            j--;                                                   //sortowac rosnaco musimy zminic znaki < i > na przeciwne
        while (tab[i].b < x) // dopoki elementy sa mniejsze od x   // czyli  { (tab[j].b < x) j-- } i { (tab[i].b > x) i++}
            i++;
        if (i < j) // zamieniamy miejscami gdy i < j
        {
            tempA = tab[i].b;
            tempB = tab[i].a;
            tab[i].b = tab[j].b;
            tab[i].a = tab[j].a;
            tab[j].b = tempA;
            tab[j].a = tempB;
            i++;
            j--;
        }
        else // gdy i >= j zwracamy j jako punkt podzialu tablicy
            return j;
    }
}

void quicksort(pasazer tab[], int tmp1, int tmp2) //  sortowanie malejace
{
    int miejsce_podzialu;
    if (tmp1 < tmp2)
    {
        miejsce_podzialu = podziel(tab,tmp1,tmp2); // dzielimy tablice na dwie czesci i zapisuejmy miejsce podzialu
        quicksort(tab, tmp1, miejsce_podzialu); // quick sort rekurencyjnie dla piewszej polowy tab
        quicksort(tab, miejsce_podzialu+1, tmp2); // quick sort rekurencyjnie dla drugiej polowy tab
    }
}


int main()
{
    int t; // liczba zestawow danych;
    int n; // liczba pasazerow
    int wsiadanie;
    int wysiadanie;
    int licznik;

    ios_base::sync_with_stdio(false);

    cin >> t;

    for(int i=0; i<t; i++){         // wczytujemy wartosci kiedy pasarzer siada i wysiada
        cin >> n;
        pasazer * tab = new pasazer[n]; //tworzymy tablice pasazerow
        for(int j=0; j<n; j++){         //wczytujemy kiedy pasazer wsiada i wysiada
            cin >> tab[j].a >> tab[j].b;
        }
        quicksort(tab,0,n-1);           //sortujemy malejaco po b

//        for(int j=0; j<n; j++){
//            cout << tab[j].a << " " << tab[j].b << endl;  // wyswietlanie tablicy do sprawdzenia czy wartosci sa dobrze posortowane
//        }

        wsiadanie = tab[1].a;           //ustawiamy 'a' na drugim elemencie ktory bedziemy sprawdzac a 'b' na pierwszym
        wysiadanie = tab[0].b;          // poniewaz zakladamy ze pierwszy element jest odwiedzony stad
        licznik=1;                      //licznik jest ustawiany na wartosc 1
        for(int j=0; j<n-1; j++){
            if(wsiadanie < wysiadanie){ // sprawdzamy czy wsiadanie jest mniejsze niz wysiadanie
                if(j<n-2)               //warunek ktory sprwadza czy nie wprowadzamy do 'wsiadaj' wartosci spoza zakresu tablicy
                    wsiadanie = tab[j+2].a;
                continue;               // jezeli tak to sprawdza nastepny element
            }
            else{                       //jesli nie to znaczy ze znowu trzeba przejsc przes pociag wiec ustawiamy nowe wsiadanie i wysiadanie i licznik ++
                if(j<n-2){              //warunek ktory sprwadza czy nie wprowadzamy do 'wsiadaj' wartosci spoza zakresu tablicy
                  wysiadanie = tab[j+1].b;
                  wsiadanie = tab[j+2].a;
                }
                licznik++;
            }
        }
        cout << licznik << endl;
    }
    return 0;
}
