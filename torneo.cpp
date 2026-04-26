#include "torneo.h"
#include "equipo.h"
#include <iostream>
#include "archivo.h"
#include "metricas.h"

using namespace std;

Torneo::Torneo() {
    capacidadEquipos = 48;
    cantidadEquipos = 0;
    equipos = new Equipo[capacidadEquipos];
}

Torneo::~Torneo() {
    delete[] equipos;
    equipos = 0;
    cantidadEquipos = 0;
    capacidadEquipos = 0;
}

int Torneo::calcularPuntos(int ganados, int empatados) const {
    return ganados * 3 + empatados;
}

int Torneo::calcularPartidos(int ganados, int empatados, int perdidos) const {
    return ganados + empatados + perdidos;
}

void Torneo::cargarEquipos(const string& nombreArchivo) {
    cargarEquiposDesdeCSV(nombreArchivo, equipos, cantidadEquipos, capacidadEquipos);
}

void Torneo::guardarEquiposCSV(const string& nombreArchivo) const {
    guardarEquiposEnCSV(nombreArchivo, equipos, cantidadEquipos);
}

void Torneo::guardarJugadoresCSV(const string& nombreArchivo) const {
    guardarJugadoresEnCSV(nombreArchivo, equipos, cantidadEquipos);
}

void Torneo::mostrarTodo() const {
    cout << "\n====== EQUIPOS DEL TORNEO ======\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();
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
        Metricas::sumarIteracion();
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
        Metricas::sumarIteracion();
        const Equipo& e = equipos[i];

        cout << "\nEquipo: " << e.pais << endl;
        cout << "-------------------------" << endl;

        for (int j = 0; j < 26; j++) {
            Metricas::sumarIteracion();
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

int Torneo::getCantidad() const {
    return cantidadEquipos;
}
Torneo::Torneo(const Torneo& otro)
    : cantidadEquipos(otro.cantidadEquipos)
{
    for (int i = 0; i < cantidadEquipos; i++) {
        equipos[i] = otro.equipos[i];
    }
}
//sobrecarga
Torneo& Torneo::operator=(const Torneo& otro) {
    if (this != &otro) {
        cantidadEquipos = otro.cantidadEquipos;

        for (int i = 0; i < cantidadEquipos; i++) {
            equipos[i] = otro.equipos[i];
        }
    }

    return *this;
}

bool Torneo::operator==(const Torneo& otro) const {
    return cantidadEquipos == otro.cantidadEquipos;
}

bool Torneo::operator>(const Torneo& otro) const {
    return cantidadEquipos > otro.cantidadEquipos;
}