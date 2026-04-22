#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "jugador.h"

using std::string;

// ESTADÍSTICAS
struct Estadisticas {
    int golesF;
    int golesC;
    int ganados;
    int empatados;
    int perdidos;

    Estadisticas();
};

// EQUIPO
class Equipo {

public:
    string pais;
    string tecnico;
    string confederacion;
    int rankingFIFA;

    Estadisticas historico;
    Estadisticas actual;

    Jugador jugadores[26];

    // Constructor
    Equipo();

    // Métodos
    void reiniciarActual();
    void inicializarJugadores();
    Jugador** obtenerAlineacion();

private:
    string intAString(int num);
};

#endif
