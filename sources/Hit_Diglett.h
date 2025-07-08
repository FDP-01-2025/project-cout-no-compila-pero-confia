// Hit_Diglett.h
#ifndef HIT_DIGLETT_H
#define HIT_DIGLETT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>   // for _kbhit(), _getch()
#include <windows.h> // for Sleep()
#include <string>

using namespace std;

void displayGrid(int position,
                 int score,
                 int timeLeft,
                 int duration,
                 int comboStreak);
int  getRandomPosition();
void penalizeTime(int& startTime, int penaltySeconds);
void updateSpeed(int hits, int& speed);
void startGame();



// Draws the game grid with score, time bar and combo indicator
void displayGrid(int position,
                 int score,
                 int timeLeft,
                 int duration,
                 int comboStreak) {
    system("cls");
    cout << "Hit Diglett (press the correct number)!\n\n";

    // Score display
    cout << "Score: " << score << "\n";

    // Time bar display
    const int BAR_WIDTH = 20;
    int filled = timeLeft * BAR_WIDTH / duration;
    cout << "Time : [";
    for (int i = 0; i < BAR_WIDTH; ++i)
        cout << (i < filled ? '=' : ' ');
    cout << "] " << timeLeft << "s\n";

    // Combo streak display
    if (comboStreak > 1) {
        cout << "  🔥 Combo x" << comboStreak << "! 🔥\n\n";
    } else {
        cout << "\n";
    }

    // Numeric grid with ASCII border
    int layout[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
    const int WIDTH = 11;  

    // Top border
    cout << '+' << string(WIDTH, '-') << "+\n";

    // Grid rows
    for (int r = 0; r < 3; ++r) {
        cout << "| ";
        for (int c = 0; c < 3; ++c) {
            int idx = r * 3 + c;
            if (layout[idx] == position)
                cout << "[D]";
            else
                cout << "[" << layout[idx] << "]";
            cout << ' ';
        }
        cout << "|\n";
    }

    
    cout << '+' << string(WIDTH, '-') << "+\n\n";
}

// Returns a random keypad position 1–9
int getRandomPosition() {
    return rand() % 9 + 1;
}

// Adds penalty seconds to the start time
void penalizeTime(int& startTime, int penaltySeconds) {
    startTime += penaltySeconds;
}

// Speeds up the game every 4 hits, down to a minimum speed
void updateSpeed(int hits, int& speed) {
    if (hits % 4 == 0 && speed > 400) {
        speed -= 150;
    }
}

// Main game loop
void startGame() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int score        = 0;
    int hits         = 0;
    int comboStreak  = 0;     // consecutive hits
    int penaltySec   = 3;     // seconds subtracted on miss
    int duration     = 60;    // total game time in seconds
    int startTime    = time(nullptr);
    int speed        = 1500;  // milliseconds per Diglett appearance

    while (time(nullptr) - startTime < duration) {
        int diglettPos = getRandomPosition();

        // Calculate remaining time
        int elapsed  = time(nullptr) - startTime;
        int timeLeft = duration - elapsed;
        if (timeLeft < 0) timeLeft = 0;

        // Display grid, score, time and combo
        displayGrid(diglettPos, score, timeLeft, duration, comboStreak);

        int appearTime = time(nullptr);
        bool hit       = false;

        // Wait for key press until timeout
        while (time(nullptr) - appearTime < speed / 1000.0) {
            if (_kbhit()) {
                char key = _getch();
                if (key == diglettPos + '0') {
                    // Hit
                    score++;
                    hits++;
                    comboStreak++;
                    updateSpeed(hits, speed);
                    hit = true;
                } else {
                    // Miss
                    penalizeTime(startTime, penaltySec);
                    comboStreak = 0;
                }
                break;
            }
        }

        // If nobody pressed or timed out
        if (!hit) {
            penalizeTime(startTime, penaltySec);
            comboStreak = 0;
        }
    }

    system("cls");
    cout << "Time's up! Your final score: " << score << endl;
}

#endif // HIT_DIGLETT_H