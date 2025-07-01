#ifndef CLEAFIRYSAYS_H
#define CLEAFIRYSAYS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <conio.h>

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

int main(){
    srand(static_cast<unsigned int>(time(0)));

    vector<char> sequence;
    vector<char> playerInput;
    int level = 1;
    bool playing = true;
    int delay = 1000; // milliseconds between arrows
    cout << "Welcome to 'Cleafiry Says'!" << endl;
    cout << "Repeat the arrow sequence usign W (^), A (<), S(v), D(>)" <<  endl;
    cout << "Press ENTER to start... " << endl;
    cin.ignore();

    while (playing){
        // Add a new arrow to the sequence
        sequence.push_back(getRandomArrow());

        cout << "\nLevel " << level << "Watch the sequence... " << endl;

        //Show the sequence
        for (char arrow : sequence){
            showArrow(arrow);
            this_thread::sleep_for(chrono::milliseconds(delay));
            clearScreen();
        }

        // Get player's input
        playerInput.clear();
        cout << "Now repeat the sequence" << endl;

        for (size_t i = 0; i < sequence.size(); ++i){
            char Input;
            cout << "Arrow " << (i + 1) << ": ";
            cin >> Input;
            Input = toupper(Input);
            playerInput.push_back(Input);
        }

        
    }




}
    



