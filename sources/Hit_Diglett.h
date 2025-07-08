// Hit_Diglett.h
#ifndef GOLPEAADIGLETT_H
#define GOLPEAADIGLETT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>    // For _kbhit() and _getch()
#include <windows.h>  // for Sleep()

using namespace std;

void mostrarGrid(int posicion) {
    system("cls");
    // (si usas mostrarCabecera, llámala aquí)

    int layout[9] = {7,8,9,4,5,6,1,2,3};
    const int width = 13;  // ajusta si cambias espaciado

    // Borde superior
    cout << "+";
    for (int i = 0; i < width; ++i) cout << "-";
    cout << "+\n";

    // Celdas en 3 filas
    for (int r = 0; r < 3; ++r) {
        cout << "| ";
        for (int c = 0; c < 3; ++c) {
            int idx = r*3 + c;
            if (layout[idx] == posicion)
                cout << "[D]";
            else
                cout << "[" << layout[idx] << "]";
            cout << " ";
        }
        cout << "|\n";
    }

    // Borde inferior
    cout << "+";
    for (int i = 0; i < width; ++i) cout << "-";
    cout << "+\n\n";
}

int obtenerPosicionAleatoria() {
    return rand() % 9 + 1;
}

void penalizarTiempo(int& tiempoInicio, int penalizacion) {
    tiempoInicio += penalizacion;
}

void actualizarVelocidad(int aciertos, int& velocidad) {
    if (aciertos % 4 == 0 && velocidad > 400) {
        velocidad -= 150;
    }
}

void startGame() {
    srand(time(NULL));
    int puntuacion = 0;
    int aciertos = 0;
    int penalizacion = 3;             // seconds subtracted upon failure
    int duracion = 60;                // total game duration
    int tiempoInicio = time(0);
    int velocidad = 1500;             // longer than a visible Diglett lasts

    while (time(0) - tiempoInicio < duracion) {
        int diglett = obtenerPosicionAleatoria();
        mostrarGrid(diglett);
        int tiempoAparicion = time(0);
        bool acertado = false;

        while (time(0) - tiempoAparicion < velocidad / 1000.0) {
            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == diglett + '0') {
                    puntuacion++;
                    aciertos++;
                    actualizarVelocidad(aciertos, velocidad);
                    acertado = true;
                    break;
                } else {
                    penalizarTiempo(tiempoInicio, penalizacion);
                    break;
                }
            }
        }

        if (!acertado) {
            penalizarTiempo(tiempoInicio, penalizacion);
        }
    }

    system("cls");
    cout << "¡Time's up! Your final score: " << puntuacion << endl;
}

#endif