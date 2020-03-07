#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int p;  //numer panstwa
    int w;  //wspolczynnik
};
void wGore(Node tab[], int indeks[],int &zmiany,int i)
{
    while(( tab[(i-1)/2].w < tab[i].w)){
        if(i<=0)
            break;
        cout << "porownywane wartosci : (ojciec)" << tab[(i-1)/2].w << " syn: " << tab[i].w << endl;
        Node tmp;
        int tmp_indeks;
        tmp = tab[(i-1)/2];                         //zapisujemy panstwo ktore jest ojcem
        tmp_indeks = indeks[tab[(i-1)/2].p];        //zapamietuje indeks ojca
        indeks[tab[(i-1)/2].p] = indeks[tab[i].p];  //zmieniam ojcu indeks z indeksem syna
        tab[(i-1)/2] = tab[i];                      //zastampiam ojca synem/
        indeks[tab[i].p] = tmp_indeks;          //syn dostaje indeks ojca
        tab[i] = tmp;                           //w miejsce syna zapisauje ojca
        zmiany++;
        i--;
        i/=2;

        cout << "porownywane wartosci : (ojciec)" << tab[(i-1)/2].w << " syn: " << tab[i].w << endl;//zmniejszam i poniewaz w nastepnym kroku znowu bede porownywal ojca z synem
    }
}
void wDol(Node tab[],int *indeks, int wielkosc_tab,int &zmiany,int i)
{
    int indeks_syna = 2*i+1;                    //indeks lewego syna
    while (indeks_syna <= wielkosc_tab){
        if ((indeks_syna < wielkosc_tab) && (tab[indeks_syna].w < tab[indeks_syna+1].w)) indeks_syna++;     //jezeli syn lewy był <= to inkrementuje indeks by dostac sie do prawego syna
        if (tab[i].w > tab[indeks_syna].w) break;
        //zamienaimy wartosci i indeksy
        Node tmp;
        int tmp_indeks;
        tmp = tab[i];                                   //zapisuje ojca do tmp
        tmp_indeks = indeks[tab[i].p];                  //zapamietuje indeks ojca
        indeks[tab[i].p] = indeks[tab[indeks_syna].p];  //zmieniam ojcu indeks na syna
        tab[i] = tab[indeks_syna];                      //zamieniam ojca z synem
        indeks[tab[indeks_syna].p] = tmp_indeks;        //przypisuje do indeksu syna indeks ojca
        tab[indeks_syna] = tmp;
        zmiany++;
        i = indeks_syna;
        indeks_syna = 2*i+1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;      //liczba rozwazanych panstw
    int m;      //liczba zmian
    int p,w;    //numerowi p zmienia w
    int zmiany=0;   //liczba zmian
    cin >> n;
    Node panstwo[n];        //tablica panst ktora dostajemy na wejsciu
    int indeksy[1001]{0};   //tworzymy tak dla kazdej liczby ktora moze wystapic, w ktorej bedziemy przechowywali jej indeks
    for(int i=0; i<n; i++){
        cin >> panstwo[i].p >> panstwo[i].w;
        indeksy[panstwo[i].p]=i;            //dla panstwa o numerze p zapisujemy jego indeks ktory jest naszym 'i'
    }
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> p >> w;
        if(panstwo[indeksy[p]].w < w){    //przesiewamy w gore
            panstwo[indeksy[p]].w = w;
            wGore(panstwo,indeksy,zmiany,indeksy[p]);
        }else if(panstwo[indeksy[p]].w > w){                              //przesiewamy w dol
            panstwo[indeksy[p]].w = w;
            wDol(panstwo,indeksy,n,zmiany,indeksy[p]);
        }
    }
    cout<<zmiany;
    return 0;
}
