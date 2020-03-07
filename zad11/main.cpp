#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
struct liczba{
    short wartosc;
    bool czy_wystepuje=false;
};
struct Node{
    liczba *a,*b;
    bool operator < (const Node &x)const{ //zdefiniowanie zachowania się
             return a->wartosc<x.a->wartosc;
           }
};
bool czy_obsadzone(vector<Node>* polaczenia){
    for(short i=polaczenia->size()-1; i>=0; --i)
        if((polaczenia->at(i).a->czy_wystepuje == false) && (polaczenia->at(i).b->czy_wystepuje == false))
            return false;
    return true;
}
int zwroc_indeks_obsadzanej(vector<Node>& polaczenia){
    for(int i=0; i<polaczenia.size(); ++i)
        if((polaczenia.at(i).a->czy_wystepuje == false) && (polaczenia.at(i).b->czy_wystepuje == false))
            return i;
    return -1;
}
void obsadz(short l,liczba * wszystkie_liczby){
    wszystkie_liczby[l-1].czy_wystepuje = true;
}
void zdejmij(short l,liczba * wszystkie_liczby){
    wszystkie_liczby[l-1].czy_wystepuje = false;
}
bool rek(vector<Node>& polaczenia,short pozostali_wolontariusze,liczba * wszystkie_liczby){
    if(pozostali_wolontariusze > 0){
        short indeks = zwroc_indeks_obsadzanej(polaczenia);
        obsadz(polaczenia[indeks].a->wartosc,wszystkie_liczby);
        pozostali_wolontariusze--;
        if(rek(polaczenia,pozostali_wolontariusze,wszystkie_liczby))
            return true;
        else{
            zdejmij(polaczenia[indeks].a->wartosc,wszystkie_liczby);
            obsadz(polaczenia[indeks].b->wartosc,wszystkie_liczby);
            if(rek(polaczenia,pozostali_wolontariusze,wszystkie_liczby))
                return true;
        }
        zdejmij(polaczenia[indeks].b->wartosc,wszystkie_liczby);
        pozostali_wolontariusze++;
    }
    else
        if(czy_obsadzone(&polaczenia))
            return true;
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    short t;  //liczba zestawow danych
    short n;  //liczba stacji kolejowych
    short m;  //liczba odcinkow kolejowych
    short r;  //liczba wolontariuszy
    short a,b;
    cin >> t;
    for(short i=0; i<t; i++){
         cin >> n >> m >> r;
         liczba * wszystkie_liczby = new liczba[n]; //tworze tablice wszystkich stacji
         for(short i=0; i<n; i++){
             wszystkie_liczby[i].wartosc=i+1;
         }
         Node pol[m];
         vector<Node> polaczenia;
        for(short j=0; j<m; j++){
            cin >> a >> b;
            pol[j].a = &wszystkie_liczby[a-1];
            pol[j].b = &wszystkie_liczby[b-1];
            polaczenia.push_back(pol[j]);
        }
        sort(polaczenia.begin(),polaczenia.end());
        if(rek(polaczenia,r,wszystkie_liczby))
            cout<<"TAK"<<endl;
         else
             cout<<"NIE"<<endl;
        }
    return 0;
}
