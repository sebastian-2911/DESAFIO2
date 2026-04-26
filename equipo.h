#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "jugador.h"
#include "estadisticas.h"

using namespace std;

class Equipo {
public:
    string pais;
    string tecnico;
    string confederacion;
    int rankingFIFA;

    Estadisticas historico;
    Estadisticas actual;

    Jugador jugadores[26];

private:
    Jugador* alineacion[11];

public:
    Equipo();

    void reiniciarActual();
    void inicializarJugadores();
    Jugador** obtenerAlineacion();
    Jugador* getJugadorAlineado(int indice);

    bool operator==(const Equipo& otro) const;
    bool operator>(const Equipo& otro) const;
};

#endif