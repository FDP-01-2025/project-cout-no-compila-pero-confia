#ifndef ROCKHARDEN_H
#define ROCKHARDEN_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

namespace RockHarden {

struct Player {
    string name;
    int health = 3;
    int energy = 5;
    bool hardened = false;
};

inline void showStatus(const Player& p1, const Player& p2) {
    system("cls");
    cout << "========== ROCK HARDEN ==========\n";
    cout << p1.name << " - Health: " << p1.health << " | Energy: " << p1.energy << "\n";
    cout << p2.name << " - Health: " << p2.health << " | Energy: " << p2.energy << "\n\n";
}

inline void playRound(Player& p1, Player& p2) {
    p1.hardened = false;
    p2.hardened = false;

    cout << "A rock is falling! Press [A] for " << p1.name << ", [L] for " << p2.name << "!\n";
    Sleep(rand() % 2000 + 1000);
    cout << "NOW!\n";

    int elapsed = 0;
    while (elapsed < 1500) {
        if (_kbhit()) {
            char key = _getch();
            if ((key == 'a' || key == 'A') && p1.energy > 0) {
                p1.hardened = true;
                p1.energy--;
            }
            if ((key == 'l' || key == 'L') && p2.energy > 0) {
                p2.hardened = true;
                p2.energy--;
            }
        }
        Sleep(100);
        elapsed += 100;
    }

    if (!p1.hardened) p1.health--;
    if (!p2.hardened) p2.health--;

    if (p1.energy < 5) p1.energy++;
    if (p2.energy < 5) p2.energy++;
}

inline void runGame(int maxDurationSeconds = 60) {
    using namespace std::chrono;
    srand(time(0));
    Player player1{"Metapod"}, player2{"Kakuna"};

    auto startTime = steady_clock::now();

    while (player1.health > 0 && player2.health > 0) {
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime).count();
        int remaining = maxDurationSeconds - static_cast<int>(elapsed);

        if (elapsed >= maxDurationSeconds) {
            cout << "Time's up! Max duration reached (" << maxDurationSeconds << "s)\n";
            break;
        }

        // Show player status
        showStatus(player1, player2);

        // Show visual time bar
        cout << "Time elapsed: " << elapsed << "s / " << maxDurationSeconds << "s\n";
        cout << "[";
        int barWidth = 20;
        int filled = static_cast<int>((elapsed * barWidth) / maxDurationSeconds);
        for (int i = 0; i < filled; ++i) cout << "=";
        for (int i = filled; i < barWidth; ++i) cout << " ";
        cout << "]\n";

        // Visual warning
        if (remaining <= 5) {
            cout << "\n FINAL SECONDS! " << remaining << "s left! Be quick!\n";
        }

        cout << endl;
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

#endif