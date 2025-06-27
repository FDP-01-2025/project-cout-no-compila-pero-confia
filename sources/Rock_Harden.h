// RockHarden.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep()

using namespace std;

struct Player {
    string nombre;
    int vida = 3;
    int energia = 5;
    bool endurecido = false;
};

void mostrarEstado(const Player& p1, const Player& p2) {
    system("cls");
    cout << "========== ROCK HARDEN ==========\n";
    cout << p1.nombre << " - Life: " << p1.vida << " | Energy: " << p1.energia << "\n";
    cout << p2.nombre << " - Life: " << p2.vida << " | Energy: " << p2.energia << "\n\n";
}

void resolverRonda(Player& p1, Player& p2) {
    p1.endurecido = false;
    p2.endurecido = false;

    cout << "A rock is falling! Press [A] to " << p1.nombre << ", [L] for " << p2.nombre << "!\n";

    int tiempoEspera = rand() % 2000 + 1000; // Wait between 1 to 3 seconds
    Sleep(tiempoEspera);

    cout << "¡GO!\n";

    int tiempoRespuesta = 1500; // Milliseconds to react
    int elapsed = 0;
    while (elapsed < tiempoRespuesta) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'a' || tecla == 'A') {
                if (p1.energia > 0) {
                    p1.endurecido = true;
                    p1.energia--;
                }
            } else if (tecla == 'l' || tecla == 'L') {
                if (p2.energia > 0) {
                    p2.endurecido = true;
                    p2.energia--;
                }
            }
        }
        Sleep(100);
        elapsed += 100;
    }

    // Resolve the damage
    if (!p1.endurecido) p1.vida--;
    if (!p2.endurecido) p2.vida--;

    // Energy recovery
    if (p1.energia < 5) p1.energia++;
    if (p2.energia < 5) p2.energia++;
}