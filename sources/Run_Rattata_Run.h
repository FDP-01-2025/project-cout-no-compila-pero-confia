#ifndef RATTATAGAME_H
#define RATTATAGAME_H

#include <iostream>
#include <conio.h>  
#include <ctime>
#include <cstdlib>

using namespace std;

class RattataGame {
private:
    int position;
    int speed;
    int obstacle;
    char lastKey;
    int jumps;
    bool waitingForJump;

public:
    RattataGame() {
        srand(time(0));
        position = 0;
        speed = 0;
        obstacle = rand() % 5 + 3;
        lastKey = ' ';
        jumps = 0;
        waitingForJump = false;
    }

    void showInstructions() {
        cout << "=== Run, Rattata, Run! ===\n";
        cout << "Instructions:\n";
        cout << "- Alternate 'A' and 'D' quickly to run.\n";
        cout << "- Press 'W' to jump when an obstacle appears.\n";
        cout << "- Reach the finish line at 50m to win!\n";
        cout << "\nPress any key to start...\n";
        _getch();
    }

    void start() {
        showInstructions();

        clock_t startTime = clock();  

        while (position < 50) {
            if (_kbhit()) {
                int key = _getch();

                if (key == 0 || key == 224)
                    key = _getch();

                if (waitingForJump) {
                    if (key == 'w' || key == 'W') {
                        cout << "✔️ You jumped over the obstacle!\n";
                        jumps++;
                        waitingForJump = false;
                        obstacle = position + rand() % 5 + 3;  
                        speed = 0;
                    } else {
                        cout << "❌ Failed jump! -2m\n";
                        position -= 2;
                        if (position < 0) position = 0;
                        cout << "You're still at " << position << "m. Press 'W' to jump!\n";
                    }
                    continue;
                } else {
                    if ((key == 'a' || key == 'A') && lastKey != 'L') {
                        speed++;
                        lastKey = 'L';
                    }
                    else if ((key == 'd' || key == 'D') && lastKey != 'R') {
                        speed++;
                        lastKey = 'R';
                    }
                    else if (key == 'w' || key == 'W') {
                        cout << "⚠️ Jumped at wrong time! -2 speed\n";
                        speed -= 2;
                        if (speed < 0) speed = 0;
                    }
                }

                if (speed >= 2) {
                    position++;
                    speed = 0;
                    cout << "🐭 Rattata is now at " << position << "m\n";

                    if (position == obstacle) {
                        cout << "🪨 Obstacle ahead! Press 'W' to jump!\n";
                        waitingForJump = true;
                    }
                }
            }
        }

        clock_t endTime = clock();  
        double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;

        cout << "\n🏁 You reached the finish line!\n";
        cout << "🕒 Time taken: " << totalTime << " seconds\n";
        cout << "🦘 Total jumps: " << jumps << "\n";
    }
};

#endif
