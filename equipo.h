#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "jugador.h"

using namespace std;

class Equipo {
public:
    string pais;
    string tecnico;

    int golesF;
    int golesC;
    int ganados;
    int empatados;
    int perdidos;

    Jugador jugadores[26]; // 26 jugadores por equipo
    // cada objeto equipo ya tiene 26 jugadores
    // Constructor
    Equipo();

    // Inicializar jugadores
    void inicializarJugadores();
};

#endif
