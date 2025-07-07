#ifndef CLEAFIRYSAYS_H
#define CLEAFIRYSAYS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>

namespace ClefairyGame {

    using std::cout;
    using std::cin;
    using std::endl;
    using std::vector;
    using std::string;

    // Structure to hold player information
    struct Player {
        string name;
        int score;
    };

    // Clears the console screen depending on the OS
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Generates a random direction key (W, A, S, D)
    char generateRandomKey() {
        const char keys[] = {'W', 'A', 'S', 'D'};
        return keys[rand() % 4];
    }

    // Displays the corresponding arrow symbol for the direction
    void showArrow(char arrow) {
        switch (arrow) {
            case 'W': cout << "↑ (W)" << endl; break;
            case 'A': cout << "← (A)" << endl; break;
            case 'S': cout << "↓ (S)" << endl; break;
            case 'D': cout << "→ (D)" << endl; break;
            default:  cout << "?" << endl; break;
        }
    }

    // Pauses execution until the user presses ENTER
    void waitForEnter() {
        cout << "\nPress ENTER to continue...";
        cin.ignore();
    }

    // Saves the player's name and score to a file
    void saveScore(const Player& player) {
        std::ofstream outFile("scores.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << player.name << "," << player.score << "\n";
            outFile.close();
        } else {
            std::cerr << "⚠️ Could not open scores file for writing.\n";
        }
    }

    // Displays all previously saved scores
    void showHighScores() {
        std::ifstream inFile("scores.txt");
        string line;
        cout << "\n📜 High Scores:\n";
        cout << "----------------------\n";
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                std::istringstream iss(line);
                string name;
                string score;
                if (getline(iss, name, ',') && getline(iss, score)) {
                    cout << name << " - " << score << endl;
                }
            }
            inFile.close();
        } else {
            cout << "No high scores available yet.\n";
        }
        cout << "----------------------\n\n";
    }

    // Main game logic for Clefairy Says
    void playClefairySays() {
        srand(static_cast<unsigned int>(time(0))); // Initialize RNG

        Player player;
        vector<char> sequence;
        vector<char> playerInput;
        int level = 1;
        bool playing = true;

        cout << "🎮 Welcome to 'Clefairy Says'!\n";
        showHighScores(); // Show previous scores

        // Ask for player's name
        cout << "Enter your name: ";
        getline(cin, player.name);

        cout << "Repeat the sequence using W (^), A (<), S (v), D (>)\n";
        cout << "Press ENTER to start...\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

        clearScreen();

        while (playing) {
            // Add a new arrow to the sequence
            sequence.push_back(generateRandomKey());

            // Show the sequence to the player
            for (char arrow : sequence) {
                clearScreen();
                cout << "\n🧠 Level " << level << ": Watch the arrow\n\n";
                showArrow(arrow);
                waitForEnter(); // Pause between arrows
            }

            clearScreen();
            playerInput.clear();
            cout << "🔁 Repeat the sequence:\n";

            // Get input from the player
            for (size_t i = 0; i < sequence.size(); ++i) {
                char input;
                cout << "Arrow " << i + 1 << ": ";
                cin >> input;
                input = toupper(input); // Normalize input to uppercase
                playerInput.push_back(input);
            }

            // Check if input matches the sequence
            if (playerInput != sequence) {
                cout << "\n❌ Incorrect! Game over at level " << level << ".\n";
                playing = false;
                player.score = level - 1;
            } else {
                cout << "\n✅ Correct! Advancing to level " << (++level) << "...\n";
                cout << "Press ENTER to continue...";
                cin.ignore();
                cin.get();
            }
        }

        // Show final result and save score
        cout << "\n✨ Thanks for playing, " << player.name << "!\n";
        cout << "🎯 Your final score: " << player.score << endl;

        saveScore(player); // Save current player's score
    }

} // namespace ClefairyGame

#endif // CLEAFIRYSAYS_H