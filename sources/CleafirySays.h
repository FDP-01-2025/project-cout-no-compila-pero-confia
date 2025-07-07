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
        try {
            std::ifstream inFile("scores.txt");
            string line;

            cout << "\n📜 High Scores:\n";
            cout << "----------------------\n";
            if (!inFile) {
                throw std::runtime_error("scores.txt could not be opened.");
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
        } catch (const std::exception& e) {
            std::cerr << "⚠️ Error reading scores: " << e.what() << endl;
        }
    }

    // Displays the sequence of arrows to the player
    void showSequence(const vector<char>& sequence, int level) {
        for (char arrow : sequence) {
            clearScreen();
            cout << "\n🧠 Level " << level << ": Watch the arrow\n\n";
            showArrow(arrow);
            waitForEnter();
        }
    }

    // Gets validated input sequence from the player
    vector<char> getPlayerInput(size_t length) {
        vector<char> inputSequence;
        for (size_t i = 0; i < length; ++i) {
            char input;
            bool valid = false;
            do {
                cout << "Arrow " << i + 1 << ": ";
                cin >> input;
                input = toupper(input);
                if (isValidKey(input)) {
                    inputSequence.push_back(input);
                    valid = true;
                } else {
                    cout << "⚠️ Invalid input! Please enter W, A, S, or D.\n";
                }
            } while (!valid);
        }
        return inputSequence;
    }

    // Compares the player's input with the original sequence
    bool compareSequences(const vector<char>& seq1, const vector<char>& seq2) {
        return seq1 == seq2;
    }

    void playClefairySays() {
        srand(static_cast<unsigned int>(time(0)));

        Player player;
        vector<char> sequence;
        int level = 1;
        bool playing = true;

        cout << "🎮 Welcome to 'Clefairy Says'!\n";
        showHighScores();

        cout << "Enter your name: ";
        getline(cin, player.name);

        cout << "Repeat the sequence using W (^), A (<), S (v), D (>)\n";
        cout << "Press ENTER to start...\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

        clearScreen();

        while (playing) {
            sequence.push_back(generateRandomKey());

            showSequence(sequence, level);
            clearScreen();
            cout << "🔁 Repeat the sequence:\n";
            vector<char> playerInput = getPlayerInput(sequence.size());

            if (!compareSequences(playerInput, sequence)) {
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

        cout << "\n✨ Thanks for playing, " << player.name << "!\n";
        cout << "🎯 Your final score: " << player.score << endl;

        saveScore(player);
    }

} // namespace ClefairyGame

#endif // CLEAFIRYSAYS_H