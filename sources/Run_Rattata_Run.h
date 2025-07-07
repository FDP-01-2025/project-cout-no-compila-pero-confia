#ifndef RATTATAGAME_H
#define RATTATAGAME_H

#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

class RattataGame {
private:
    int position;
    int speed;
    int obstacle;
    char lastKey;
    int jumps;
    int penalties;
    int bestScore;
    int bestTime;

    // Timer
    clock_t startTime;
    clock_t endTime;

    bool mustJumpNext; // Indica que la próxima tecla DEBE ser salto (W)

public:
    RattataGame() {
        srand(time(0));
        resetGame();
        bestScore = 0;
        bestTime = 9999; // Tiempo alto inicial
    }

    void showInstructions() {
        system("cls");
        cout << "=== Run, Rattata, Run! ===\n";
        cout << "Instructions:\n";
        cout << "- Alternate 'A' and 'D' to move.\n";
        cout << "- Press 'W' to jump ONLY when an obstacle appears.\n";
        cout << "- Reach 50m to win. Each miss costs 2m!\n";
        cout << "\nBest Score: " << bestScore << " points";
        if (bestTime < 9999)
            cout << " | Best Time: " << bestTime << "s";
        cout << "\n\nPress any key to start...\n";
        _getch();
    }

    void resetGame() {
        position = 0;
        speed = 0;
        obstacle = rand() % 5 + 10;
        lastKey = ' ';
        jumps = 0;
        penalties = 0;
        mustJumpNext = false;
    }

    void showStatus() {
        cout << "📍 Position: " << position << "m | ⚡ Speed: " << speed
             << " | 🐭 Jumps: " << jumps << " | ❌ Misses: " << penalties << "\n";
    }

    int calculateScore(int durationSeconds) {
        int score = 100;
        score += (50 - durationSeconds) * 2;
        score += jumps * 3;
        score -= penalties * 5;
        if (score < 0) score = 0;
        return score;
    }

    void start() {
        resetGame();
        showInstructions();
        startTime = clock();

        while (position < 50) {
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 224) key = _getch(); // Teclas especiales

                if (mustJumpNext) {
                    // Debe saltar con W sí o sí
                    if (key == 'w' || key == 'W') {
                        cout << "✅ You jumped the obstacle!\n";
                        jumps++;
                        mustJumpNext = false;
                        obstacle = position + rand() % 5 + 5;
                        speed = 0;
                        position++; // Avanza solo al saltar
                    } else {
                        cout << "❌ You missed the jump! -2m penalty\n";
                        penalties++;
                        speed = 0;
                        position = max(0, position - 2); // Retrocede 2 metros
                        // mustJumpNext sigue true, sigue sin poder avanzar
                    }
                    showStatus();
                    continue; // Esperar siguiente tecla sin procesar más
                }

                // Si no debe saltar, movimiento normal A/D
                if ((key == 'a' || key == 'A') && lastKey != 'L') {
                    speed++;
                    lastKey = 'L';
                } else if ((key == 'd' || key == 'D') && lastKey != 'R') {
                    speed++;
                    lastKey = 'R';
                } else if ((key == 'w' || key == 'W')) {
                    // W fuera de tiempo
                    cout << "❌ Wrong timing for jump!\n";
                    penalties++;
                    speed = max(0, speed - 2);
                }

                if (speed >= 2) {
                    position++;
                    speed = 0;

                    cout << "\n🏃 Rattata is now at " << position << "m\n";

                    if (position == obstacle - 1) {
                        cout << "⚠️ Obstacle ahead! NEXT key must be 'W' to jump!\n";
                        mustJumpNext = true;
                    }
                }

                showStatus();
            }
        }

        endTime = clock();
        int seconds = (endTime - startTime) / CLOCKS_PER_SEC;
        int finalScore = calculateScore(seconds);

        cout << "\nYou reached the finish line!\n";
        cout << "Time: " << seconds << " seconds\n";
        cout << "Final Score: " << finalScore << "\n";

        if (finalScore > bestScore) {
            bestScore = finalScore;
            bestTime = seconds;
            cout << "New Record!\n";
        }
    }
};

#endif

