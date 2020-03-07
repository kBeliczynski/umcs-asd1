#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int  p : 28; // numer panstwa    <0,10000000>
    int w : 28; // wspolczynnik panstwa
}__attribute__((packed));
void szukaj_najmniejszego(vector<Node> &panstwa,int &tmp){
    tmp = panstwa[0].p;
    for(int i=1; i<panstwa.size(); i++){
        if(tmp > panstwa[i].p)
            tmp = panstwa[i].p;
    }
}
void szukaj_indeks(vector<Node> &panstwa, int poczatek, int koniec,int indeks, int & znaleziona_wartosc){
    vector<Node> mniejsze,rowne,wieksze;
    Node srodek = panstwa[(poczatek+koniec)/2];
    int iloscM=0,iloscR=0,iloscW=0;
    for(unsigned int i=0; i<panstwa.size();i++){
        if(panstwa[i].w < srodek.w)
            iloscM++;
        else if(panstwa[i].w == srodek.w)
            iloscR++;
        else{
            iloscW++;
        }
    }
    for(unsigned int i=0; i<panstwa.size();i++){
        if(indeks <= iloscM){
            if(panstwa[i].w < srodek.w)
                 mniejsze.push_back(panstwa[i]);
        }
        else if((indeks > iloscM) && (indeks <= iloscM+iloscR)){
            if(panstwa[i].w == srodek.w)
                 rowne.push_back(panstwa[i]);
        }
        else{
            if(panstwa[i].w > srodek.w)
                wieksze.push_back(panstwa[i]);
        }
    }
    if(mniejsze.size() > 0){
       szukaj_indeks(mniejsze,0,mniejsze.size(),indeks,znaleziona_wartosc);
    }
    else if(rowne.size() > 0){
        szukaj_najmniejszego(rowne,znaleziona_wartosc);
        return;
    }
    else{
        indeks-=(iloscM+iloscR);
        poczatek=0;
        koniec=iloscW;
        szukaj_indeks(wieksze,poczatek,koniec,indeks,znaleziona_wartosc);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;  // liczba rozwazanych panstw    <1,500000>
    int m;  // liczba zapytan <1,200>
    int indeks; // indeks szukanego elementu
    int poczatek, koniec;   //indeksy poczatku i konca aktualnie sprawdzanej tablicy
    int znaleziona_wartosc;
    int a,b;
    cin >> n;
    Node *panstwa = new Node[n];
    vector<Node> wszystkie_panstwa;
    for(int i=0; i<n; i++){     //wprowadzamy dane do tablicy panstw
        cin >> a >> b;
        panstwa[i].p = a;
        panstwa[i].w = b;
        wszystkie_panstwa.push_back(panstwa[i]);
    }
    delete [] panstwa;
    cin >> m;
    for(int i=1; i<=m; i++){    //podajemy indeks i szukamy go w tablicy panstw
        cin >> indeks;
        szukaj_indeks(wszystkie_panstwa,0,wszystkie_panstwa.size(),indeks,znaleziona_wartosc);
        cout << znaleziona_wartosc << endl;
    }
    return 0;
}


