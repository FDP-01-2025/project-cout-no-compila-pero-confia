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
#include <stdexcept>

namespace ClefairyGame {

    using std::cout;
    using std::cin;
    using std::endl;
    using std::vector;
    using std::string;

    struct Player {
        string name;
        int score;
    };

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    char generateRandomKey() {
        const char keys[] = {'W', 'A', 'S', 'D'};
        return keys[rand() % 4];
    }

    void showArrow(char arrow) {
        switch (arrow) {
            case 'W': cout << "↑ (W)" << endl; break;
            case 'A': cout << "← (A)" << endl; break;
            case 'S': cout << "↓ (S)" << endl; break;
            case 'D': cout << "→ (D)" << endl; break;
            default:  cout << "?" << endl; break;
        }
    }

    void waitForEnter() {
        cout << "\nPress ENTER to continue...";
        cin.ignore();
    }

    // Validates if the input character is one of the valid directions
    bool isValidKey(char c) {
        c = toupper(c);
        return c == 'W' || c == 'A' || c == 'S' || c == 'D';
    }

    void saveScore(const Player& player) {
        try {
            std::ofstream outFile("scores.txt", std::ios::app);
            if (!outFile) {
                throw std::runtime_error("Unable to open scores.txt for writing.");
            }
            outFile << player.name << "," << player.score << "\n";
            outFile.close();
        } catch (const std::exception& e) {
            std::cerr << "⚠️ Error saving score: " << e.what() << endl;
        }
    }

   void showHighScores() {
    std::ifstream inFile("scores.txt");
    string line;

    cout << "\n High Scores:\n";
    cout << "----------------------\n";

    // If the file doesn't exist, create it and inform the user
    if (!inFile) {
        std::ofstream createFile("scores.txt"); // This creates the file
        createFile.close();
        cout << "(No scores yet!)\n";
        cout << "----------------------\n\n";
        return;
    }

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        string name, score;
        if (getline(iss, name, ',') && getline(iss, score)) {
            cout << name << " - " << score << endl;
        }
    }

    inFile.close();
    cout << "----------------------\n\n";
}


    void playClefairySays() {
        srand(static_cast<unsigned int>(time(0)));

        Player player;
        vector<char> sequence;
        vector<char> playerInput;
        int level = 1;
        bool playing = true;

        cout << " Welcome to 'Clefairy Says'!\n";
        showHighScores();

        cout << "Enter your name: ";
        getline(cin, player.name);

        cout << "Repeat the sequence using W (^), A (<), S (v), D (>)\n";
        cout << "Press ENTER to start...\n";
        cin.ignore();
        cin.get();


        clearScreen();

        while (playing) {
            sequence.push_back(generateRandomKey());

            for (char arrow : sequence) {
                clearScreen();
                cout << "\n Level " << level << ": Watch the arrow\n\n";
                showArrow(arrow);
                waitForEnter();
            }

            clearScreen();
            playerInput.clear();
            cout << "🔁 Repeat the sequence:\n";

            for (size_t i = 0; i < sequence.size(); ++i) {
                char input;
                bool valid = false;

                // Keep asking until valid input is given
                do {
                    cout << "Arrow " << i + 1 << ": ";
                    cin >> input;
                    input = toupper(input);
                    if (isValidKey(input)) {
                        valid = true;
                        playerInput.push_back(input);
                    } else {
                        cout << "⚠️ Invalid input! Please enter W, A, S, or D.\n";
                    }
                } while (!valid);
            }

            if (playerInput != sequence) {
                cout << "\n Incorrect! Game over at level " << level << ".\n";
                playing = false;
                player.score = level - 1;
            } else {
                cout << "\n Correct! Advancing to level " << (++level) << "...\n";
                cout << "Press ENTER to continue...";
                cin.ignore();
                cin.get();
            }
        }

        cout << "\n✨ Thanks for playing, " << player.name << "!\n";
        cout << " Your final score: " << player.score << endl;

        saveScore(player);
    }

} // namespace ClefairyGame

#endif // CLEAFIRYSAYS_H