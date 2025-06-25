#include <iostream>
using namespace std;

int main(){
    int num;
    cout << endl << " === GAME BOX 4.0 === " << endl << endl;
    cout << "1. Clefairy Says" << endl;
    cout << "2. Golpea a Diglett" << endl;
    cout << "3. Corre Rattata Corre!!!" << endl;
    cout << "4. Rock Harden" << endl;
    cout << "Selecciona el juego que quieres jugar: ";

    cin >> num;

    switch (num)
    {
    case 1:
        //Funcion del juego de Clefairy Says
        break;
    case 2:
        //Funcion del juego de Golpe a Diglett
        break;
    case 3:
        //Funcion del juego de Corre Rattata Corre
        break;
    case 4:
        //Funcion del juego de Rock Harden
        break;
    default:
        cout << "Opcion no valida";
        break;
    }
return 0;
}

