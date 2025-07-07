// Hit_Diglett.h
#ifndef HIT_DIGLETT_H
#define HIT_DIGLETT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>    // For _kbhit() and _getch()
#include <windows.h>  // for Sleep()

using namespace std;

void showGrid(int position) {
    system("cls");
    cout << "Hit Diglett (press the correct number)!\n\n";

    int layout[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3}; // Numeric keypad layout

    for (int i = 0; i < 9; ++i) {
        if (layout[i] == position) {
            cout << "[D] ";
        } else {
            cout << "[" << layout[i] << "] ";
        }
        if ((i + 1) % 3 == 0) cout << endl;
    }
}

int getRandomPosition() {
    return rand() % 9 + 1;
}

void applyTimePenalty(int& startTime, int penalty) {
    startTime += penalty;
}

void updateSpeed(int hits, int& speed) {
    if (hits % 4 == 0 && speed > 400) {
        speed -= 150;
    }
}

void startGame() {
    srand(time(NULL));
    int score = 0;
    int hits = 0;
    int penalty = 3;            // seconds subtracted upon failure
    int duration = 60;          // total game duration
    int startTime = time(0);
    int speed = 1500;           // Diglett visible time in ms

    while (time(0) - startTime < duration) {
        int diglett = getRandomPosition();
        showGrid(diglett);
        int appearanceTime = time(0);
        bool successfulHit = false;

        while (time(0) - appearanceTime < speed / 1000.0) {
            if (_kbhit()) {
                char key = _getch();
                if (key == diglett + '0') {
                    score++;
                    hits++;
                    updateSpeed(hits, speed);
                    successfulHit = true;
                    break;
                } else {
                    applyTimePenalty(startTime, penalty);
                    break;
                }
            }
        }

        if (!successfulHit) {
            applyTimePenalty(startTime, penalty);
        }
    }

    system("cls");
    cout << "Time's up! Your final score: " << score << endl;
}

#endif
