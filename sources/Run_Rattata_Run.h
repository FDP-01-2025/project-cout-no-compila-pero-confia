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

public:
    RattataGame() {
        srand(time(0));
        position = 0;
        speed = 0;
        obstacle = rand() % 30 + 10;
        lastKey = ' ';
        jumps = 0;
    }

    void showInstructions() {
        cout << "=== Run, Rattata, Run! ===\n";
        cout << "Instructions:\n";
        cout << "- Alternate LEFT and RIGHT arrows (or 'A' and 'D') quickly to run.\n";
        cout << "- Press 'A' to jump when an obstacle appears.\n";
        cout << "- Reach the finish line at 50m before others!\n";
        cout << "\nPress any key to start...\n";
        _getch();
    }
    
        void start() {
        showInstructions();

        while (position < 50) {
            if (_kbhit()) {
                char key = _getch();

                // Left or right movement
                if ((key == 75 || key == 'a' || key == 'A') && lastKey != 'L') {
                    speed++;
                    lastKey = 'L';
                } else if ((key == 77 || key == 'd' || key == 'D') && lastKey != 'R') {
                    speed++;
                    lastKey = 'R';
                } else if (key == 'a' || key == 'A') {
                    if (position == obstacle) {
                        cout << "You jumped over the obstacle!\n";
                        jumps++;
                        obstacle = position + rand() % 20 + 10;
                    } else {
                        cout << "You jumped too early or too late!\n";
                        speed -= 2;
                        if (speed < 0) speed = 0;
                    }
                }

                if (speed >= 2) {
                    position++;
                    speed = 0;
                    cout << "Rattata is now at " << position << "m\n";

                    if (position == obstacle) {
                        cout << "Obstacle ahead! Press 'A' to jump!\n";
                    }
                }
            }
        }

        cout << "\n🏁 You reached the finish line!\n";
        cout << "Total jumps: " << jumps << "\n";
    }
    
};

#endif
