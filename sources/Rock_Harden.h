#ifndef ROCKHARDEN_H
#define ROCKHARDEN_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

namespace RockHarden {

struct Player {
    string name;
    int health   = 3;
    int energy   = 5;
    bool hardened = false;
};

// cambia el color del texto en consola (Windows)
inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// dibuja una barra de energía de 5 bloques con color
inline void mostrarBarraEnergia(int energia) {
    int color = (energia >= 4) ? 10    // verde
             : (energia >= 2) ? 14    // amarillo
             : 12;                    // rojo

    setColor(color);
    cout << "[";
    for (int i = 0; i < 5; ++i) {
        if (i < energia) cout << "#";
        else             cout << " ";
    }
    cout << "] (" << energia << "/5)";
    setColor(7);  // restaura color
}

// muestra vida y energía usando la barra visual
inline void showStatus(const Player& p1, const Player& p2) {
    system("cls");
    cout << "========== ROCK HARDEN ==========\n\n";

    cout << p1.name
         << " - Health: " << p1.health
         << " | Energy: ";
    mostrarBarraEnergia(p1.energy);
    cout << "\n";

    cout << p2.name
         << " - Health: " << p2.health
         << " | Energy: ";
    mostrarBarraEnergia(p2.energy);
    cout << "\n\n";
}

// tecla aleatoria para cada jugador
inline char getRandomKey() {
    const string valid = "asdfghjklzxcvbnmqwertyuiop";
    return valid[rand() % valid.size()];
}

inline void playRound(Player& p1, Player& p2) {
    p1.hardened = p2.hardened = false;

    char keyP1 = getRandomKey();
    char keyP2 = getRandomKey();

    cout << "A rock is falling!\n";
    cout << p1.name << ": PRESS [" << (char)toupper(keyP1) << "]  |  "
         << p2.name << ": PRESS [" << (char)toupper(keyP2) << "]\n\n";

    Sleep(rand() % 2000 + 1000);
    cout << "NOW!\n";

    int elapsed = 0;
    while (elapsed < 1500) {
        if (_kbhit()) {
            char tecla = tolower(_getch());
            if (tecla == keyP1 && p1.energy > 0) {
                p1.hardened = true;
                p1.energy--;            // resta energía aquí
            }
            if (tecla == keyP2 && p2.energy > 0) {
                p2.hardened = true;
                p2.energy--;            // y aquí
            }
        }
        Sleep(100);
        elapsed += 100;
    }

    if (!p1.hardened) p1.health--;
    if (!p2.hardened) p2.health--;

    // eliminamos la regeneración automática para que la barra muestre el cambio
}

inline void runGame(int maxDurationSeconds = 60) {
    srand((unsigned)time(nullptr));
    Player player1{"Metapod"}, player2{"Kakuna"};
    auto startTime = steady_clock::now();

    while (player1.health > 0 && player2.health > 0) {
        auto now     = steady_clock::now();
        int elapsedS = (int)duration_cast<seconds>(now - startTime).count();

        if (elapsedS >= maxDurationSeconds) {
            showStatus(player1, player2);
            cout << "Time's up! (" << maxDurationSeconds << "s)\n";
            break;
        }

        showStatus(player1, player2);

        // barra de tiempo al estilo original
        cout << "Time elapsed: " << elapsedS << "s / " << maxDurationSeconds << "s\n";
        cout << "[";
        int barWidth = 20;
        int filled   = elapsedS * barWidth / maxDurationSeconds;
        for (int i = 0; i < filled; ++i) cout << "=";
        for (int i = filled; i < barWidth; ++i) cout << " ";
        cout << "]\n\n";

        playRound(player1, player2);
        Sleep(1000);
    }

    showStatus(player1, player2);
    cout << "Game Over!\n";

    if (player1.health > player2.health)
        cout << player1.name << " wins!\n";
    else if (player2.health > player1.health)
        cout << player2.name << " wins!\n";
    else
        cout << "It's a draw!\n";
}

} // namespace RockHarden

#endif // ROCKHARDEN_H