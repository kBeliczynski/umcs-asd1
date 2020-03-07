#include <iostream>
using namespace std;
unsigned long long eulera_r (unsigned long long e, unsigned long long phi )
{
  long int noweE = e;  // na poczatku dostaje wartosc e, pozniej przyjmuje wartosc reszty jaka zostaje np dla phi=60, e=13 : 60 = 13*4 + '8'(reszta)
  long int stareE = phi;  // na pocztku dostaje wartosc phi a pozniej dostaje stara wartosc reszty np phi=60, e=13 : 60 = '13'(dostaje ta wartosc)*4 + 8 , a pozniej dostaje 8
  long int tmp1 = 0;      // na poczatku przyjmuje wartosc 0 a pozniej dostaje stare wartosci z tmp2
  long int tmp2 = 1;      // na poczatku dostaje 1 a pozniej co obrot dostaje wartosc z d aby nie przepadla
  long int mnoznik = stareE / noweE;   // oznacza ile razy trzeba przemnozyc noweE + reszta aby wyszlo stareR np e=13, phi=60,  60=13*'4'(to jest ten mnoznik)+8
  long int reszta = stareE % noweE;    // jest to reszta pozostala
  long int d;   // szukana wartosc d
  while( reszta > 0 )   //jezeli reszta jest wieksza od 0
  {
    d = tmp1 - mnoznik * tmp2;  //to liczymy d i sprawdzamy czy jest wieksze od 0
    if( d >= 0 )
      d = d % phi;              //jezeli tak to liczymy modulo
    else
      d = phi-((-d)%phi);       //jezeli nie to liczymy modulo z jej ujemnej wartosci np -1mod4 to 3 (z 1 do 4 jest odleglosc 3)
    tmp1 = tmp2; tmp2 = d;      // tmp1 dostaje stara wartosc d a tmp2 nowa wartosc d
    stareE = noweE; noweE = reszta; //stareE dostaje stara wartosc noweE a noweE dostaje wartosc reszty
    mnoznik  = stareE / noweE;      //aktualicujemy mnoznik (opis wyzej)
    reszta = stareE % noweE;        //aktualicujemy reszte (opis wyzej)
  }
  return tmp2;                      //jesli znalezlismy to zwracamy nasze d
}
unsigned long long potegowanie_modulo(unsigned long long podstawa, unsigned long long wykladnik, unsigned int modulo){
    unsigned long long wiadomosc = 1;         // szukana wiadomosc ktora odszyfrowujemy
    unsigned long long x = podstawa%modulo;   // zmienna tymczasowa x przechowujaca modulo z podstawy aby jak najbardziej zmniejszyc zakres (wartosc mnozona)
    for (unsigned long long k=1; k<=wykladnik; k*=2){
        if ((wykladnik&k) != 0){        // robimy operacje AND wykladnika z k
            wiadomosc *= x;
            wiadomosc %= modulo;
        }
        x *= x;
        x %= modulo;
    }
    return wiadomosc;
}
unsigned long long Euklid(unsigned long long a , unsigned long long b ){
    if(a<b)
        return Euklid(b,a);
    if(a%b==0)
        return b ;
    return Euklid(b,a%b) ;
}
int main(){
    unsigned long long p,q,e,c,d,m,phi; // m jest to odszyfrowna liczba c, phi to ((p-1)*(q-1))
    unsigned long long t; //liczba zestawow danych
    cin >> t;
    for(unsigned long long i=0; i<t; i++){
        cin >> p >> q >> e >> c;
        phi=((p-1)*(q-1));
        d = eulera_r(e,phi);
        m=potegowanie_modulo(c,d,(p*q));
        cout << m << endl;
    }
    return 0;
}
