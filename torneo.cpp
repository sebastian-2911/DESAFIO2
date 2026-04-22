#include "torneo.h"
#include "Equipo.h"
#include "Jugador.h"
#include <iostream>
#include <fstream>

using namespace std;

int convertirEntero(string texto) {
    int num = 0;
    int i = 0;

    while (i < texto.length() && texto[i] == ' ') {
        i++;
    }

    for (; i < texto.length(); i++) {
        if (texto[i] >= '0' && texto[i] <= '9') {
            num = num * 10 + (texto[i] - '0');
        } else {
            break;
        }
    }

    return num;
}

Torneo::Torneo() {
    equipos = new Equipo[48];
    cantidad = 0;
}

Torneo::~Torneo() {
    delete[] equipos;
}

void Torneo::cargarEquipos(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    cantidad = 0;

    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea) && cantidad < 48) {

        if (linea == "") {
            continue;
        }

        string c[10];
        int indiceColumna = 0;
        int inicio = 0;
        int pos = 0;

        while ((pos = linea.find(";", inicio)) != string::npos && indiceColumna < 9) {
            c[indiceColumna] = linea.substr(inicio, pos - inicio);
            indiceColumna++;
            inicio = pos + 1;
        }

        c[indiceColumna] = linea.substr(inicio);

        if (indiceColumna < 9) {
            cout << "Linea invalida: " << linea << endl;
            continue;
        }

        Equipo& e = equipos[cantidad];

        e.rankingFIFA = convertirEntero(c[0]);
        e.pais = c[1];
        e.tecnico = c[2];
        e.confederacion = c[4];

        e.historico.golesF = convertirEntero(c[5]);
        e.historico.golesC = convertirEntero(c[6]);
        e.historico.ganados = convertirEntero(c[7]);
        e.historico.empatados = convertirEntero(c[8]);
        e.historico.perdidos = convertirEntero(c[9]);

        e.reiniciarActual();

        cantidad++;
    }

    archivo.close();

    cout << "Equipos cargados: " << cantidad << endl;
}

void Torneo::mostrarTodo() {
    cout << "\n====== EQUIPOS DEL TORNEO ======\n";

    for (int i = 0; i < cantidad; i++) {
        Equipo& e = equipos[i];

        int puntosActuales = e.actual.ganados * 3 + e.actual.empatados;
        int puntosHistoricos = e.historico.ganados * 3 + e.historico.empatados;
        int partidosHistoricos = e.historico.ganados + e.historico.empatados + e.historico.perdidos;

        cout << "\n" << i + 1 << ". " << e.pais << endl;
        cout << "-------------------------" << endl;
        cout << "Confederacion: " << e.confederacion << endl;
        cout << "Tecnico: " << e.tecnico << endl;
        cout << "Ranking FIFA: " << e.rankingFIFA << endl;

        cout << "\nACTUAL (TORNEO)" << endl;
        cout << "Puntos: " << puntosActuales << endl;
        cout << "GF: " << e.actual.golesF << " | GC: " << e.actual.golesC << endl;
        cout << "G: " << e.actual.ganados
             << " | E: " << e.actual.empatados
             << " | P: " << e.actual.perdidos << endl;

        cout << "\nHISTORICO" << endl;
        cout << "Puntos: " << puntosHistoricos << endl;
        cout << "Partidos: " << partidosHistoricos << endl;
        cout << "GF: " << e.historico.golesF << " | GC: " << e.historico.golesC << endl;
        cout << "G: " << e.historico.ganados
             << " | E: " << e.historico.empatados
             << " | P: " << e.historico.perdidos << endl;
    }

    cout << endl;
}

void Torneo::mostrarEstadisticasEquipos() {
    cout << "\n====== ESTADISTICAS DE EQUIPOS ======\n";

    for (int i = 0; i < cantidad; i++) {
        Equipo& e = equipos[i];

        int puntos = e.actual.ganados * 3 + e.actual.empatados;
        int diferencia = e.actual.golesF - e.actual.golesC;
        int partidos = e.actual.ganados + e.actual.empatados + e.actual.perdidos;

        cout << "\n" << e.pais << endl;
        cout << "-------------------------" << endl;
        cout << "Confederacion: " << e.confederacion << endl;
        cout << "Partidos: " << partidos << endl;
        cout << "Puntos: " << puntos << endl;
        cout << "GF: " << e.actual.golesF << endl;
        cout << "GC: " << e.actual.golesC << endl;
        cout << "DG: " << diferencia << endl;
        cout << "Ganados: " << e.actual.ganados << endl;
        cout << "Empatados: " << e.actual.empatados << endl;
        cout << "Perdidos: " << e.actual.perdidos << endl;
    }

    cout << endl;
}

void Torneo::mostrarEstadisticasJugadores() {
    cout << "\n====== ESTADISTICAS DE JUGADORES ======\n";

    for (int i = 0; i < cantidad; i++) {
        Equipo& e = equipos[i];

        cout << "\nEquipo: " << e.pais << endl;
        cout << "-------------------------" << endl;

        for (int j = 0; j < 26; j++) {
            cout << e.jugadores[j].nombre << " " << e.jugadores[j].apellido
                 << " | N: " << e.jugadores[j].numero
                 << " | Goles: " << e.jugadores[j].goles
                 << " | Amarillas: " << e.jugadores[j].amarillas
                 << " | Rojas: " << e.jugadores[j].rojas
                 << " | Min: " << e.jugadores[j].minutos
                 << endl;
        }
    }

    cout << endl;
}

Equipo* Torneo::getEquipos() {
    return equipos;
}

int Torneo::getCantidad() {
    return cantidad;
}
