#include "grupo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor
Grupo::Grupo() {
    grupos = new Equipo*[48];
}

// Destructor
Grupo::~Grupo() {
    delete[] grupos;
}

// Crear grupos (sin copiar solo creando un areglo de apuntadores
void Grupo::crearGrupos(Equipo* equipos, int cantidad) {

    srand(time(0));// para el random

    // Mezclar equipos
    for (int i = 0; i < cantidad; i++) {
        int j = rand() % cantidad;

        Equipo temp = equipos[i];
        equipos[i] = equipos[j];
        equipos[j] = temp;
    }

    // Guardar direcciones
    for (int i = 0; i < 48; i++) {
        grupos[i] = &equipos[i];
    }
}

// Mostrar grupos A - L
void Grupo::mostrarGrupos() {

    char letra = 'A';

    for (int i = 0; i < 12; i++) {

        cout << "Grupo " << letra << endl;

        for (int j = 0; j < 4; j++) {
            cout << " - " << grupos[i * 4 + j]->pais << endl;
        }

        cout << endl;
        letra++;
    }
}
