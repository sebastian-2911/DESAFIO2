#include "equipo.h"

// Constructor
Equipo::Equipo() {
    pais = "";
    tecnico = "";

    golesF = 0;
    golesC = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;

    inicializarJugadores(); // crear jugadores automáticamente
}

// Inicializar jugadores
void Equipo::inicializarJugadores() {
    for (int i = 0; i < 26; i++) {

        jugadores[i].nombre = "Jugador";
        jugadores[i].apellido = "Apellido";
        jugadores[i].numero = i + 1;

        jugadores[i].goles = 0;
        jugadores[i].amarillas = 0;
        jugadores[i].rojas = 0;
        jugadores[i].minutos = 0;
    }
}
