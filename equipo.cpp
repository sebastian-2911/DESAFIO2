#include "equipo.h"
#include <cstdlib>
#include "metricas.h"

//  CONSTRUCTOR
Equipo::Equipo()
    : pais(""),
    tecnico(""),
    confederacion(""),
    rankingFIFA(0),
    historico(),
    actual() {
    inicializarJugadores();

    for (int i = 0; i < 11; i++) {
        Metricas::sumarIteracion();
        alineacion[i] = 0;
    }
}

//  RESET TORNEO
void Equipo::reiniciarActual() {
    actual = Estadisticas();
}

// JUGADORES
#include <sstream>

void Equipo::inicializarJugadores() {
    for (int i = 0; i < 26; i++) {
        Metricas::sumarIteracion();

        stringstream ss1;
        stringstream ss2;

        ss1 << "Jugador" << (i + 1);
        ss2 << "Apellido" << (i + 1);

        jugadores[i].nombre = ss1.str();
        jugadores[i].apellido = ss2.str();
        jugadores[i].numero = i + 1;

        jugadores[i].goles = 0;
        jugadores[i].amarillas = 0;
        jugadores[i].rojas = 0;
        jugadores[i].minutos = 0;
    }
}
//ALINEACION
Jugador** Equipo::obtenerAlineacion() {
    bool usados[26] = {false};

    for (int i = 0; i < 11; i++) {
        Metricas::sumarIteracion();
        int indice;

        do {
            Metricas::sumarIteracion();
            indice = rand() % 26;
        } while (usados[indice]);

        usados[indice] = true;
        alineacion[i] = &jugadores[indice];
    }

    return alineacion;
}
Jugador* Equipo::getJugadorAlineado(int indice) {
    if (indice < 0 || indice >= 11) {
        return 0;
    }
    return alineacion[indice];
}
Equipo::Equipo(const Equipo& otro)
    : pais(otro.pais),
    tecnico(otro.tecnico),
    confederacion(otro.confederacion),
    rankingFIFA(otro.rankingFIFA),
    historico(otro.historico),
    actual(otro.actual)
{
    for (int i = 0; i < 26; i++) {
        jugadores[i] = otro.jugadores[i];
    }

    for (int i = 0; i < 11; i++) {
        alineacion[i] = 0;
    }
}
//sobrecarga
Equipo& Equipo::operator=(const Equipo& otro) {
    if (this != &otro) {
        pais = otro.pais;
        tecnico = otro.tecnico;
        confederacion = otro.confederacion;
        rankingFIFA = otro.rankingFIFA;

        historico = otro.historico;
        actual = otro.actual;

        for (int i = 0; i < 26; i++) {
            jugadores[i] = otro.jugadores[i];
        }

        for (int i = 0; i < 11; i++) {
            alineacion[i] = 0;
        }
    }

    return *this;
}

bool Equipo::operator==(const Equipo& otro) const {
    return pais == otro.pais;
}

bool Equipo::operator>(const Equipo& otro) const {
    return rankingFIFA < otro.rankingFIFA;
}