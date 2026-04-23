#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include "torneo.h"
#include "fase.h"

using namespace std;

bool esEnteroValido(const string& texto) {
    if (texto.empty()) {
        return false;
    }

    int inicio = 0;

    if (texto[0] == '-') {
        if (texto.length() == 1) {
            return false;
        }
        inicio = 1;
    }

    for (int i = inicio; i < (int)texto.length(); i++) {
        if (!isdigit(texto[i])) {
            return false;
        }
    }

    return true;
}

void mostrarMenu() {
    cout << "\n======================================" << endl;
    cout << "              MENU TORNEO             " << endl;
    cout << "======================================" << endl;
    cout << "1. Avanzar un dia" << endl;
    cout << "2. Mostrar todos los equipos" << endl;
    cout << "3. Mostrar grupos" << endl;
    cout << "4. Mostrar estadisticas de equipos" << endl;
    cout << "5. Mostrar estadisticas de jugadores" << endl;
    cout << "6. Crear y mostrar fase eliminatoria" << endl;
    cout << "7. Jugar toda la eliminatoria" << endl;
    cout << "0. Salir" << endl;
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
            cout << "Opcion invalida" << endl;
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

        case 6:
            fase.crearDieciseisavos();
            fase.mostrarDieciseisavos();
            break;

        case 7:
            fase.jugarTodaEliminatoria();
            fase.mostrarDieciseisavos();
            break;

        case 0:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opcion invalida" << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}
