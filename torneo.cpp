#include "torneo.h"
#include "equipo.h"
#include <iostream>
#include <fstream>

using namespace std;

int convertirEntero(const string& texto) {
    int num = 0;
    int i = 0;

    while (i < (int)texto.length() && texto[i] == ' ') {
        i++;
    }

    for (; i < (int)texto.length(); i++) {
        if (texto[i] >= '0' && texto[i] <= '9') {
            num = num * 10 + (texto[i] - '0');
        }
        else {
            break;
        }
    }

    return num;
}

Torneo::Torneo() {
    cantidadEquipos = 0;
}

int Torneo::calcularPuntos(int ganados, int empatados) const {
    return ganados * 3 + empatados;
}

int Torneo::calcularPartidos(int ganados, int empatados, int perdidos) const {
    return ganados + empatados + perdidos;
}

void Torneo::cargarEquipos(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    cantidadEquipos = 0;

    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea) && cantidadEquipos < 48) {
        if (linea.empty()) {
            continue;
        }

        string columnas[10];
        int indiceColumna = 0;
        int inicio = 0;
        int pos = 0;

        while ((pos = (int)linea.find(';', inicio)) != (int)string::npos && indiceColumna < 9) {
            columnas[indiceColumna] = linea.substr(inicio, pos - inicio);
            indiceColumna++;
            inicio = pos + 1;
        }

        columnas[indiceColumna] = linea.substr(inicio);

        if (indiceColumna < 9) {
            cout << "Linea invalida: " << linea << endl;
            continue;
        }

        Equipo& e = equipos[cantidadEquipos];

        e.rankingFIFA = convertirEntero(columnas[0]);
        e.pais = columnas[1];
        e.tecnico = columnas[2];
        e.confederacion = columnas[4];

        e.historico.golesF = convertirEntero(columnas[5]);
        e.historico.golesC = convertirEntero(columnas[6]);
        e.historico.ganados = convertirEntero(columnas[7]);
        e.historico.empatados = convertirEntero(columnas[8]);
        e.historico.perdidos = convertirEntero(columnas[9]);

        e.reiniciarActual();
        e.inicializarJugadores();

        cantidadEquipos++;
    }

    archivo.close();

    cout << "Equipos cargados: " << cantidadEquipos << endl;
}

void Torneo::mostrarTodo() const {
    cout << "\n====== EQUIPOS DEL TORNEO ======\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        const Equipo& e = equipos[i];

        int puntosActuales = calcularPuntos(e.actual.ganados, e.actual.empatados);
        int puntosHistoricos = calcularPuntos(e.historico.ganados, e.historico.empatados);
        int partidosHistoricos = calcularPartidos(
            e.historico.ganados,
            e.historico.empatados,
            e.historico.perdidos
            );

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

void Torneo::mostrarEstadisticasEquipos() const {
    cout << "\n====== ESTADISTICAS DE EQUIPOS ======\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        const Equipo& e = equipos[i];

        int puntos = calcularPuntos(e.actual.ganados, e.actual.empatados);
        int diferencia = e.actual.golesF - e.actual.golesC;
        int partidos = calcularPartidos(
            e.actual.ganados,
            e.actual.empatados,
            e.actual.perdidos
            );

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

void Torneo::mostrarEstadisticasJugadores() const {
    cout << "\n====== ESTADISTICAS DE JUGADORES ======\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        const Equipo& e = equipos[i];

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

void Torneo::guardarEquiposCSV(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << "RankingFIFA;Pais;Tecnico;Confederacion;GF_Historico_Total;GC_Historico_Total;Ganados_Historico_Total;Empatados_Historico_Total;Perdidos_Historico_Total\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        const Equipo& e = equipos[i];

        int golesFTotal = e.historico.golesF + e.actual.golesF;
        int golesCTotal = e.historico.golesC + e.actual.golesC;
        int ganadosTotal = e.historico.ganados + e.actual.ganados;
        int empatadosTotal = e.historico.empatados + e.actual.empatados;
        int perdidosTotal = e.historico.perdidos + e.actual.perdidos;

        archivo << e.rankingFIFA << ";"
                << e.pais << ";"
                << e.tecnico << ";"
                << e.confederacion << ";"
                << golesFTotal << ";"
                << golesCTotal << ";"
                << ganadosTotal << ";"
                << empatadosTotal << ";"
                << perdidosTotal << "\n";
    }

    archivo.close();
    cout << "Archivo generado: " << nombreArchivo << endl;
}

void Torneo::guardarJugadoresCSV(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << "Equipo;Numero;Nombre;Apellido;Goles;Amarillas;Rojas;Minutos\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        const Equipo& e = equipos[i];

        for (int j = 0; j < 26; j++) {
            const Jugador& jug = e.jugadores[j];

            archivo << e.pais << ";"
                    << jug.numero << ";"
                    << jug.nombre << ";"
                    << jug.apellido << ";"
                    << jug.goles << ";"
                    << jug.amarillas << ";"
                    << jug.rojas << ";"
                    << jug.minutos << "\n";
        }
    }

    archivo.close();
    cout << "Archivo generado: " << nombreArchivo << endl;
}

Equipo* Torneo::getEquipos() {
    return equipos;
}

int Torneo::getCantidad() const {
    return cantidadEquipos;
}
