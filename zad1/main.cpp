#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    long int t;
    long long int x,y;
    long long int n,m;
    long long int roznica;
    long long int max_wartosc;
    long long int ile_zostalo;
    long long int liczba_faz;
    bool niewystarczajacy; //zmienna ktora okresla czy da sie skonczyc funckje
//    int czy_mniejszy = false;
    cin >> t;
    for(int i=1; i<=t; ++i){
        max_wartosc = 0;
        liczba_faz = 0;
        roznica = 0;
        niewystarczajacy = false;
        cin >> n >> m;
        if(n == 0){
            cout << liczba_faz << endl;
            continue;
        }
        ile_zostalo = n;
        long long int tmp = ile_zostalo;
        for(int j=1; j <=m; j++){
            cin >> x >> y;
//            if(x < 0 || y < 0)
//                czy_mniejszy = true;
            if (roznica < (x - y))
                roznica = (x - y);
//            if((max_wartosc < x) && (roznica > 0ll))
            if((max_wartosc < x))
                max_wartosc = x;
            if(roznica <= 0 &&  j >= m && n > 0 && (tmp-max_wartosc)>0){ // sprawdzamy warunek na to ze funkcja jest w stanie sie wykonac jezeli nie to zmienna niewystarczajacy przyjmuje wartosc true
//            if(roznica <= 0 && max_wartosc <= 0 && n != 0){
                niewystarczajacy = true;
//            break;
            }
        }
//        if(czy_mniejszy){ // warunek sprawdzajacy czy ktorakolwiek podana zmienna byla mniejsza od 0 jesli tak to wykonuje sie ponizszy algorytm
//            while(ile_zostalo > 0){
//                       if(ile_zostalo <= max_wartosc){
//                          liczba_faz++;
 //                          break;
 //                          }else{
 //                        ile_zostalo -= roznica;
  //                       liczba_faz++;
 //                     }
//                  }
//        }
//        else{
        if((ile_zostalo - max_wartosc) <= 0 ){
            liczba_faz = 1;
            cout <<liczba_faz<< endl;
            continue;
        }
           liczba_faz = (long long int)((long long int)((double(ile_zostalo-max_wartosc)/roznica)+0.99)+1.0); // szybkie liczenie faz. 1 dodajemy dlatego ze odejmujemy liczbe maksymalna
//        }
        if(niewystarczajacy == false)
            cout <<liczba_faz<< endl;

        else
            cout <<"BRAK METOD\n";
      }

    return 0;
}///// /
