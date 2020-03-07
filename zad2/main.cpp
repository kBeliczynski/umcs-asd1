#include <iostream>
#include <string.h>

using namespace std;


struct osoba{
public:
    string imie;
    unsigned long int x; // oznacza czas
};

int l = 10*10*10*10*10*10+3;

void SelectionSort(osoba tab [] , int n );
int main()
{

    ios_base::sync_with_stdio(false);

    int t = 0;
    int p = 0,n = 0;
    unsigned long int czas_ogolny = 0;

    cin >> t;

    for(int i = 0; i<t; i++){
      czas_ogolny = 0;
      cin >> p >> n;

      osoba * o = new osoba[p];

      for(int i=0; i<p; i++){
         cin >> o[i].imie >> o[i].x;
       }

      SelectionSort(o,p);

       for(int i=0; i<p; i++){
           if(i != 0){
                czas_ogolny =  czas_ogolny + (1+o[i].x*(i));
           }
            else
               czas_ogolny++;
       }

        for(int i=0; i<n; i++){
            cout << o[i].imie << " ";
        }
           cout << endl << czas_ogolny%l<<endl;
    }
    return 0;
}


void SelectionSort (osoba tab [] , int n ){
    for(int i=n-1; i>0;i--){
         int max =0;
    for( int j =1;j<=i;j++){
        if ( tab[max].x > tab[j].x){
            max = j ;
        }
        if((tab[max].x == tab[j].x) && (tab[max].imie < tab[j].imie)){
                max = j ;
            }
        }
        swap(tab[i],tab[max]);
    }
}



