#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include "torneo.h"
#include "fase.h"

using namespace std;

bool esEnteroValido(const string& texto) {
    if (texto.empty()) return false;

    int inicio = 0;
    if (texto[0] == '-') {
        if (texto.length() == 1) return false;
        inicio = 1;
    }

    for (int i = inicio; i < texto.length(); i++) {
        if (!isdigit(texto[i])) return false;
    }

    return true;
}

void mostrarMenu() {
    cout << "\n=============================\n";
    cout << "         MENU TORNEO         \n";
    cout << "=============================\n";
    cout << "1. Avanzar un dia\n";
    cout << "2. Mostrar todos los equipos\n";
    cout << "3. Mostrar grupos\n";
    cout << "4. Mostrar estadisticas de equipos\n";
    cout << "5. Mostrar estadisticas de jugadores\n";
    cout << "0. Salir\n";
    cout << "Seleccione: ";
}

int main() {
    srand((unsigned)time(NULL));

    Torneo torneo;
    torneo.cargarEquipos("fifa.csv");

    Fase fase;
    fase.iniciarFase(torneo.getEquipos(), torneo.getCantidad());
    fase.iniciarCalendario();

    int opcion = -1;
    string linea;

    do {
        mostrarMenu();

        if (!getline(cin, linea)) {
            break;
        }

        if (!esEnteroValido(linea)) {
            cout << "Opcion invalida\n";
            continue;
        }

        opcion = stoi(linea);

        switch (opcion) {
        case 1:
            fase.avanzarDia();
            break;

        case 2:
            torneo.mostrarTodo();
            break;

        case 3:
            fase.mostrarGrupos();
            break;

        case 4:
            torneo.mostrarEstadisticasEquipos();
            break;

        case 5:
            torneo.mostrarEstadisticasJugadores();
            break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
