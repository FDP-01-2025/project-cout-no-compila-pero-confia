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
        obstacle = rand() % 5 + 3;  // Primer obstáculo muy cercano
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

        while (position < 50) {
            if (_kbhit()) {
                int key = _getch();

                // Leer tecla especial (flechas)
                if (key == 0 || key == 224) {
                    key = _getch();
                }

                cout << "🔹 Key pressed: " << key << endl;

                if (waitingForJump) {
                    if (key == 'w' || key == 'W') {
                        cout << "You jumped over the obstacle!\n";
                        jumps++;
                        waitingForJump = false;
                        // Nuevo obstáculo entre 3 y 7 metros adelante para más saltos frecuentes
                        obstacle = position + rand() % 5 + 3;
                        speed = 0; // reset velocidad
                    } else {
                        cout << "You failed to jump! You fall back 2 meters.\n";
                        position -= 2;
                        if (position < 0) position = 0;
                        cout << "Still at obstacle at position " << position << ". Press 'W' to jump!\n";
                    }
                    continue; // esperar salto antes de seguir
                } else {
                    // Corre alternando A y D
                    if ((key == 'a' || key == 'A') && lastKey != 'L') {
                        speed++;
                        lastKey = 'L';
                    }
                    else if ((key == 'd' || key == 'D') && lastKey != 'R') {
                        speed++;
                        lastKey = 'R';
                    }
                    else if (key == 'w' || key == 'W') {
                        cout << "You jumped at the wrong time!\n";
                        speed -= 2;
                        if (speed < 0) speed = 0;
                    }
                }

                if (speed >= 2) {
                    position++;
                    speed = 0;
                    cout << "Rattata is now at " << position << "m\n";

                    if (position == obstacle) {
                        cout << "Obstacle ahead! Press 'W' to jump!\n";
                        waitingForJump = true;
                    }
                }
            }
        }

        cout << "\n🏁 You reached the finish line!\n";
        cout << "Total jumps: " << jumps << "\n";
    }
};

#endif