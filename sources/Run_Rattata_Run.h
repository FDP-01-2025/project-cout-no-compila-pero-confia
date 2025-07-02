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

    
};

#endif
