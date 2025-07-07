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
    int misses;
    int bestScore;
    int bestTime;

    // Timer
    clock_t startTime;
    clock_t endTime;

    bool mustJumpNext; // Indicates that next key MUST be a jump (W)

public:
    RattataGame() {
        srand(time(0));
        resetGame();
        bestScore = 0;
        bestTime = 9999; // Initial high value
    }

    void showInstructions() {
        system("cls");
        cout << "=== Run, Rattata, Run! ===\n";
        cout << "Instructions:\n";
        cout << "- Alternate 'A' and 'D' to run.\n";
        cout << "- Press 'W' to jump ONLY when an obstacle appears.\n";
        cout << "- Reach 50m to win. Each mistake costs 2m!\n";
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
        misses = 0;
        mustJumpNext = false;
    }

    void showStatus() {
        cout << " Position: " << position << "m |  Speed: " << speed
             << " |  Jumps: " << jumps << " |  Misses: " << misses << "\n";
    }

    int calculateScore(int durationSeconds) {
        int score = 100;
        score += (50 - durationSeconds) * 2;
        score += jumps * 3;
        score -= misses * 5;
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
                if (key == 0 || key == 224) key = _getch(); // Special keys

                if (mustJumpNext) {
                    // Must jump with W
                    if (key == 'w' || key == 'W') {
                        cout << "You jumped over the obstacle!\n";
                        jumps++;
                        mustJumpNext = false;
                        obstacle = position + rand() % 5 + 5;
                        speed = 0;
                        position++; // Advances only when jumping
                    } else {
                        cout << "You failed the jump! -2m penalty\n";
                        misses++;
                        speed = 0;
                        position = max(0, position - 2); // Go back 2 meters
                        // mustJumpNext remains true
                    }
                    showStatus();
                    continue; // Wait for next key without further processing
                }

                // Normal movement with A/D when not jumping
                if ((key == 'a' || key == 'A') && lastKey != 'L') {
                    speed++;
                    lastKey = 'L';
                } else if ((key == 'd' || key == 'D') && lastKey != 'R') {
                    speed++;
                    lastKey = 'R';
                } else if ((key == 'w' || key == 'W')) {
                    // Jump out of place
                    cout << "Wrong timing for jump!\n";
                    misses++;
                    speed = max(0, speed - 2);
                }

                if (speed >= 2) {
                    position++;
                    speed = 0;

                    cout << "\nRattata is now at " << position << "m\n";

                    if (position == obstacle - 1) {
                        cout << "Obstacle ahead! NEXT key must be 'W' to jump!\n";
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
    }
};

#endif
