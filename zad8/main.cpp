#include <iostream>
#include <iostream>

using namespace std;

//string test(unsigned &x, unsigned &y, unsigned &id) {
//    unsigned xTest, yTest;
//    std::string direction = "";
//    switch( id ) {
//    case 0:
//        xTest = 0;
//        yTest = 0;
//        break;
//    case 1:
//        xTest = 99;
//        yTest = 99;
//        break;
//    default:
//        xTest = 0;
//        yTest = 0;
//        break;
//    }
//    if(yTest < y)
//        direction = "S";
//    else if(yTest > y)
//        direction = "N";
//    if(xTest < x)
//        direction += "W";
//    else if(xTest > x)
//        direction += "E";
//    return direction;
//}

int main()
{
    ios_base::sync_with_stdio(false);
    unsigned int x,y,t; // x - rozmiar domu na osi x, y- rozmiar domu na osi y, t - ilosc pluskiew
    unsigned int pozX, pozY, szukanyIndex=0; // aktualna pozycja x i y i numer akt szukanego indexu
    unsigned int przesuniecieX, przesuniecieY;

    cin >> x >> y >> t;
    string tmp;

    for(unsigned int i=0; i<t; i++){
        przesuniecieX = pozX = x/2;
        przesuniecieY = pozY = y/2;

        while(1){
            tmp = test(pozX,pozY,szukanyIndex);
            if(tmp == ""){
                cout << pozX << " " << pozY << endl;
                szukanyIndex++;
                break;
            }
            if(przesuniecieY > 1) // nie pozwalamy przesunieciu zejsc ponzej wartosci 0
                 przesuniecieY /=2;
            if(przesuniecieX > 1)
                przesuniecieX /=2;

            if(tmp[0] == 'S'){
                pozY -= przesuniecieY;

            }
            else if(tmp[0] == 'N'){
                pozY += przesuniecieY;

            }
            if(tmp[0] == 'W' || tmp[1] == 'W'){
                pozX -= przesuniecieX;
            }
            else if(tmp[0] == 'E' || tmp[1] == 'E'){
                pozX += przesuniecieX;

            }

        }
    }
    return 0;
}
