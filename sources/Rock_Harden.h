#ifndef ROCKHARDEN_H
#define ROCKHARDEN_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

namespace RockHarden {

struct Player {
    string name;
    int health   = 3;
    int energy   = 5;
    bool hardened = false;
};

// changes console text color (Windows)
inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// draws an energy bar of 5 blocks with color
inline void showEnergyBar(int energy) {
    int color = (energy >= 4) ? 10    // green
             : (energy >= 2) ? 14    // yellow
             : 12;                   // red

    setColor(color);
    cout << "[";
    for (int i = 0; i < 5; ++i) {
        if (i < energy) cout << "#";
        else            cout << " ";
    }
    cout << "] (" << energy << "/5)";
    setColor(7);  // reset color
}

// random messages for success and failure
inline void specialMessage(bool success, const string& name) {
    vector<string> successMessages = {
        "Ninja reflexes! 🥷",
        "Ultra instinct activated!",
        "Like lightning! ⚡",
        "That was fast, " + name + "!",
        "Perfect timing!"
    };

    vector<string> failMessages = {
        "Like a Slowpoke! 🐢",
        "Were you asleep?",
        "Magikarp-level reaction.",
        "Way too late, " + name + " 😅",
        "You were crushed by the rock!"
    };

    string message;
    if (success) {
        message = successMessages[rand() % successMessages.size()];
        setColor(10); // green
    } else {
        message = failMessages[rand() % failMessages.size()];
        setColor(12); // red
    }

    cout << name << ": " << message << "\n";
    setColor(7);
}

// displays health and energy using the visual bar
inline void showStatus(const Player& p1, const Player& p2) {
    system("cls");
    cout << "========== ROCK HARDEN ==========\n\n";

    cout << p1.name
         << " - Health: " << p1.health
         << " | Energy: ";
    showEnergyBar(p1.energy);
    cout << "\n";

    cout << p2.name
         << " - Health: " << p2.health
         << " | Energy: ";
    showEnergyBar(p2.energy);
    cout << "\n\n";
}

// random key for each player
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
            char key = tolower(_getch());
            if (key == keyP1 && p1.energy > 0) {
                p1.hardened = true;
                p1.energy--;
            }
            if (key == keyP2 && p2.energy > 0) {
                p2.hardened = true;
                p2.energy--;
            }
        }
        Sleep(100);
        elapsed += 100;
    }

    if (!p1.hardened) {
        p1.health--;
        specialMessage(false, p1.name);
    } else {
        specialMessage(true, p1.name);
    }

    if (!p2.hardened) {
        p2.health--;
        specialMessage(false, p2.name);
    } else {
        specialMessage(true, p2.name);
    }
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
