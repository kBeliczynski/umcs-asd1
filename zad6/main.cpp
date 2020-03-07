#include <iostream>
#include <queue>


using namespace std;

struct licznik{ // kazda komorka posiada własny licznik ktory pokazuje ile przejsc i miejsc monitorowanych bylo po drodze
    int licznik_przejsc=0;
    int miejsca_monitorowane=0;
};

int nS,mS; // wspolrzedne siedziby opercyjnej
int nX,mX; // wspolrzedne miejsca spotkania
int nTMP,mTMP; // wspolrzedne aktualnej pozycji
queue<int> Q; 

void znajdz_droge(char **tab, int n, int m, licznik **l){
    tab[nS][mS] = 'o'; // oznaczamy pierwsza komorke jako odwiedzona
    Q.push(nS); // wrzucamy jej wspolrzedne do kolejki
    Q.push(mS);

    while(!Q.empty()) // dziala dopoki kolejka nie jest pusta
    {
        nTMP = Q.front(); Q.pop();   // odczytujemy z kolejki współrzędne
        mTMP = Q.front(); Q.pop();
        
        if((mTMP-1) >= 0) // sprawdzamy czy nie wyszlismy poza tabele
        if((tab[nTMP][mTMP-1] == '.') ||(tab[nTMP][mTMP-1] == 'X')) // jezeli miejsce bylo nieodwiedzone lub jest to miejsce docelowe zwiekszamy licznik
        {
            tab[nTMP][mTMP-1] = 'o';  // odwiedamy pole
            Q.push(nTMP); Q.push(mTMP-1);     // wrzucamy aktualne wspolrzedne go kolejki
            l[nTMP][mTMP-1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1); // licznik przejsc w nowym liczniku jest rowny przejsciom starego + 1
            l[nTMP][mTMP-1].miejsca_monitorowane = l[nTMP][mTMP].miejsca_monitorowane; // licznik miejsc monitorowanych sie nie zmienia bo nie bylo to miejsce monitorowane
        }
        else if((tab[nTMP][mTMP-1] == 'M')){ // jesli trafimy na miejsce monitorowane
            tab[nTMP][mTMP-1] = 'O';        // odwiedzamy je O aby odroznic ze te miejsce bylo miejscem moitorowanym
            Q.push(nTMP); Q.push(mTMP-1);
            l[nTMP][mTMP-1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1); // licznik przejsc w nowym liczniku jest rowny przejsciom starego + 1
            l[nTMP][mTMP-1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1); // trafilismy na miejsce monitorowane wiec nowy licznik miejsc monitorowanych to stary +1
        }
        else if((tab[nTMP][mTMP-1] == 'o' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP][mTMP-1].licznik_przejsc)){ // jesli trafilismy na miejsce odwiedzone (niemonitorowane) to sprawdzamy czy zrobilismy mniej krokow by do niego dotrzec (+1 poniewaz miejsce o jest o 1 wieksze) jesli tak to te miejsce przyjmuje nowe dane z licznika
            l[nTMP][mTMP-1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1); 
            if(l[nTMP][mTMP].miejsca_monitorowane < (l[nTMP][mTMP-1].miejsca_monitorowane))
                l[nTMP][mTMP-1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane);
        }
        else if((tab[nTMP][mTMP-1] == 'O' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP][mTMP-1].licznik_przejsc)){ // jesli trafilismy na miejsce odwiedzone (monitorowane) to sprawdzamy czy zrobilismy mniej krokow by do niego dotrzec jesli tak to te miejsce przyjmuje nowe dane z licznika  
            l[nTMP][mTMP-1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane+1 < (l[nTMP][mTMP-1].miejsca_monitorowane))
                l[nTMP][mTMP-1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////
        if((mTMP+1) < m) // sprawdzamy czy nie wyszlismy poza tabele
        if((tab[nTMP][mTMP+1] == '.') || (tab[nTMP][mTMP+1] == 'X'))
        {
            tab[nTMP][mTMP+1] = 'o';
            Q.push(nTMP); Q.push(mTMP+1);
            l[nTMP][mTMP+1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP][mTMP+1].miejsca_monitorowane = l[nTMP][mTMP].miejsca_monitorowane;
        }
        else if((tab[nTMP][mTMP+1] == 'M')){
            tab[nTMP][mTMP+1] = 'O';
            Q.push(nTMP); Q.push(mTMP+1);
            l[nTMP][mTMP+1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP][mTMP+1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }else if((tab[nTMP][mTMP+1] == 'o' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP][mTMP+1].licznik_przejsc)){
            l[nTMP][mTMP+1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane < (l[nTMP][mTMP+1].miejsca_monitorowane))
                l[nTMP][mTMP+1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane);
        }
        else if((tab[nTMP][mTMP+1] == 'O' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP][mTMP+1].licznik_przejsc)){
            l[nTMP][mTMP+1].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane+1 < (l[nTMP][mTMP+1].miejsca_monitorowane))
                l[nTMP][mTMP+1].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        if((nTMP+1) < n) // sprawdzamy czy nie wyszlismy poza tabele
        if((tab[nTMP+1][mTMP] == '.') || (tab[nTMP+1][mTMP] == 'X'))
        {
            tab[nTMP+1][mTMP] = 'o';
            Q.push(nTMP+1); Q.push(mTMP);
            l[nTMP+1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP+1][mTMP].miejsca_monitorowane = l[nTMP][mTMP].miejsca_monitorowane;
        }
        else if((tab[nTMP+1][mTMP] == 'M')){
            tab[nTMP+1][mTMP] = 'O';
            Q.push(nTMP+1); Q.push(mTMP);
            l[nTMP+1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP+1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }else if((tab[nTMP+1][mTMP] == 'o' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP+1][mTMP].licznik_przejsc)){
            l[nTMP+1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane < (l[nTMP+1][mTMP].miejsca_monitorowane))
                l[nTMP+1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane);
        }
        else if((tab[nTMP+1][mTMP] == 'O' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP+1][mTMP].licznik_przejsc)){
            l[nTMP+1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane+1 < (l[nTMP+1][mTMP].miejsca_monitorowane))
                l[nTMP+1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }

///////////////////////////////////////////////////////////////////////////////////////////////////////////
        if((nTMP-1) >= 0 ) // sprawdzamy czy nie wyszlismy poza tabele
        if((tab[nTMP-1][mTMP] == '.') || (tab[nTMP-1][mTMP] == 'X'))
        {
            tab[nTMP-1][mTMP] = 'o';
            Q.push(nTMP-1); Q.push(mTMP);
            l[nTMP-1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP-1][mTMP].miejsca_monitorowane = l[nTMP][mTMP].miejsca_monitorowane;
        }
        else if((tab[nTMP-1][mTMP] == 'M')){
            tab[nTMP-1][mTMP] = 'O';
            Q.push(nTMP-1); Q.push(mTMP);
            l[nTMP-1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            l[nTMP-1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }else if((tab[nTMP-1][mTMP] == 'o' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP-1][mTMP].licznik_przejsc)){
            l[nTMP-1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane < (l[nTMP-1][mTMP].miejsca_monitorowane))
                l[nTMP-1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane);
        }
        else if((tab[nTMP-1][mTMP] == 'O' && (l[nTMP][mTMP].licznik_przejsc+1) <= l[nTMP-1][mTMP].licznik_przejsc)){
            l[nTMP-1][mTMP].licznik_przejsc = (l[nTMP][mTMP].licznik_przejsc+1);
            if(l[nTMP][mTMP].miejsca_monitorowane+1 < (l[nTMP-1][mTMP].miejsca_monitorowane))
                l[nTMP-1][mTMP].miejsca_monitorowane = (l[nTMP][mTMP].miejsca_monitorowane+1);
        }
   }
}

void wyswietl_najlepsze_przejscie(licznik **l, int n, int m, char **tab){ // skrawdzamy kazda strone X o ile istnieje i z tych stron wybieramy przejscie ktore ma najmniej przejsc i najmniej miejsc monitorowanych
    l[nX][mX].licznik_przejsc = 99999; // ustawiamy na duza wartosc poniewaz chcemy by zawsze zostala zmieniona
    l[nX][mX].miejsca_monitorowane = 99999;

    if((nX-1) >= 0 && tab[nX-1][mX] != '#') // jezeli nie wyszlismy poza tabele i te miejsce nie jest #
    if(l[nX-1][mX].licznik_przejsc < l[nX][mX].licznik_przejsc){ // jezeli w nX-1 byla mniejsza wartosc niz w miejscu docelowym X to zmieniamy wartosc 
        l[nX][mX].miejsca_monitorowane = l[nX-1][mX].miejsca_monitorowane;
        l[nX][mX].licznik_przejsc = l[nX-1][mX].licznik_przejsc;
    }
    else if(l[n-1][mX].licznik_przejsc == l[nX][mX].licznik_przejsc) // jezeli licznik przejsc jest taki sam to wybieramy przejscie ktore ma mniej miejsc monitorowanych
        if(l[nX-1][mX].miejsca_monitorowane < l[nX][mX].miejsca_monitorowane)
            l[nX][mX].miejsca_monitorowane = l[nX-1][mX].miejsca_monitorowane;

    if((nX+1) < n  && tab[nX+1][mX] != '#')
    if(l[nX+1][mX].licznik_przejsc < l[nX][mX].licznik_przejsc){
        l[nX][mX].licznik_przejsc = l[nX+1][mX].licznik_przejsc;
        l[nX][mX].miejsca_monitorowane = l[nX+1][mX].miejsca_monitorowane;
    }
    else if(l[nX+1][mX].licznik_przejsc == l[nX][mX].licznik_przejsc)
        if(l[nX+1][mX].miejsca_monitorowane < l[nX][mX].miejsca_monitorowane)
            l[nX][mX].miejsca_monitorowane = l[nX+1][mX].miejsca_monitorowane;

    if((mX-1) >= 0 && tab[nX][mX-1] != '#')
    if(l[nX][mX-1].licznik_przejsc < l[nX][mX].licznik_przejsc){
        l[nX][mX].licznik_przejsc = l[nX][mX-1].licznik_przejsc;
        l[nX][mX].miejsca_monitorowane = l[nX][mX-1].miejsca_monitorowane;
    }
    else if(l[nX][mX-1].licznik_przejsc == l[nX][mX].licznik_przejsc)
        if(l[nX][mX-1].miejsca_monitorowane < l[nX][mX].miejsca_monitorowane)
            l[nX][mX].miejsca_monitorowane = l[nX][mX-1].miejsca_monitorowane;

    if((mX+1) < m && tab[nX][mX+1] != '#')
    if(l[nX][mX+1].licznik_przejsc < l[nX][mX].licznik_przejsc){
        l[nX][mX].licznik_przejsc = l[nX][mX+1].licznik_przejsc;
        l[nX][mX].miejsca_monitorowane = l[nX][mX+1].miejsca_monitorowane;
    }
    else if(l[nX][mX+1].licznik_przejsc == l[nX][mX].licznik_przejsc)
        if(l[nX][mX+1].miejsca_monitorowane < l[nX][mX].miejsca_monitorowane)
            l[nX][mX].miejsca_monitorowane = l[nX][mX+1].miejsca_monitorowane;
    //dlatego dodajemy 1 poniewaz przejscie na pole X tez sie liczy a nie zliczylismy go wczesniej
    cout << (l[nX][mX].licznik_przejsc+1) << " " << l[nX][mX].miejsca_monitorowane << endl;
}

int main()
{
   int n=0,m=0;
    cin >> n >> m; // wczytujemy wyiary naszej tabeli 
    licznik **l = new licznik *[m]; // tworzymy licznik w ktorym bedziemy zapisywac dane kazdej komorki w tabeli
    char **tab = new char *[m];     // tworzymy tabele char do przechowywania wartosci
    for(int i=0; i<n; i++){         // tworzenie licznika i tabeli
        l[i] = new licznik[m];
        tab[i] = new char[m];
        for(int j=0; j<m; j++){
            cin >> tab[i][j];
            if(tab[i][j] == 'S'){ // gdy dodamy miejsce S zapisujemy jego wspolrzedne
                nS = i;
                mS = j;
            }
            if(tab[i][j] == 'X'){ // gdy dodamy miejsce X zapisujemy jego wspolrzedne
                nX = i;
                mX = j;
            }
        }
    }
    nTMP = nS; // przypisujemy wartosci poniewaz nie chcemy zmieniac wartosci Startu tylko operowac na zzmiennym TMP ktore beda zmieniane co kazde przejscie 
    mTMP = mS;

    znajdz_droge(tab, n, m,l); // szukamy najmniejszej drogi do X 
   wyswietl_najlepsze_przejscie(l,n,m,tab); // z 4 stron X o ile istnieja wybiera najlepsze przejscie i je wyswietla dodajac 1 poniewaz wejscie na pole X tez sie zalicza

    return 0;
}
