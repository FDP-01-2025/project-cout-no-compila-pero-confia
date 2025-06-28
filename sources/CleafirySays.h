#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
         #include <windows.h>
#else
        #include <unistd.h>
#endif

using namespace std;

// Cross-platform screen clear
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
//Generation a random arrow key (W, A, S, D)
char generateRandomKey() {
    int r = rand() % 4;
    switch (r) {
        case 0: return 'W'; // Up
        case 1: return 'A'; // Left
        case 2: return 'S'; // Down
        case 3: return 'D'; // Right
        default: return 'W';
    }
}

// Display the arrow visually
void showArrow(char arrow){
    switch (arrow){
        case 'W': cout << "^" << endl; break;
        case 'A': cout << "<" << endl; break;
        case 'S': cout << "v" << endl; break;
        case 'D': cout << ">" << endl; break;
    }
}
    



