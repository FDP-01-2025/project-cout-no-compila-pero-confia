#ifndef CLEAFIRYSAYS_H
#define CLEAFIRYSAYS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

namespace ClefairyGame {

    using std::cout;
    using std::cin;
    using std::endl;
    using std::vector;

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
        cout << "\nPresiona ENTER para continuar...";
        cin.ignore();
    }

    void playClefairySays() {
        srand(static_cast<unsigned int>(time(0)));

        vector<char> sequence;
        vector<char> playerInput;
        int level = 1;
        bool playing = true;

        cout << "🎮 Bienvenido a 'Clefairy Says'!\n";
        cout << "Repite la secuencia usando W (^), A (<), S (v), D (>)\n";
        cout << "Presiona ENTER para comenzar...\n";
        cin.ignore();

        while (playing) {
            sequence.push_back(generateRandomKey());

            for (char arrow : sequence) {
                clearScreen();
                cout << "\n🧠 Nivel " << level << ": Observa la flecha\n\n";
                showArrow(arrow);
                waitForEnter(); // ← ahora pausás manualmente entre flechas
            }

            clearScreen();
            playerInput.clear();
            cout << "🔁 Repite la secuencia:\n";

            for (size_t i = 0; i < sequence.size(); ++i) {
                char input;
                cout << "Flecha " << i + 1 << ": ";
                cin >> input;
                input = toupper(input);
                playerInput.push_back(input);
            }

            if (playerInput != sequence) {
                cout << "\n❌ ¡Incorrecto! Juego terminado en el nivel " << level << ".\n";
                playing = false;
            } else {
                cout << "\n✅ ¡Correcto! Avanzando al nivel " << (++level) << "...\n";
                cout << "Presiona ENTER para continuar...";
                cin.ignore();
                cin.get();
            }
        }

        cout << "\n✨ Gracias por jugar 'Clefairy Says'. ¡Hasta la próxima!\n";
    }

} // namespace ClefairyGame

#endif // CLEAFIRYSAYS_H