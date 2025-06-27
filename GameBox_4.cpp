#include <iostream>
#include "sources/Hit_Diglett.h"
#include "sources/Rock_Harden.h"

using namespace std;

int main(){
    int num;
    cout << endl << " === GAME BOX 4.0 === " << endl << endl;
    cout << "1. Clefairy Says" << endl;
    cout << "2. Hit Diglett" << endl;
    cout << "3. Run Rattata Run!!!" << endl;
    cout << "4. Rock Harden" << endl;
    cout << "Select the game you want to play: ";

    cin >> num;

    switch (num)
    {
    case 1:
        //Clefairy Says Game Function
        break;
    case 2:

        iniciarJuego();
        return 0;

        //Diglett Heist Game Function
        break;

    case 3:
        //Function of the Run Rattata Run game
        break;

    case 4:

        iniciarJuego();
        return 0;

        //Rock Harden Game Feature
        break;
        
    default:
        cout << "Invalid option";
        break;
    }
return 0;
}

