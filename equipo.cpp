#include "equipo.h"
#include <cstdlib>

// STADÍSTICAS
Estadisticas::Estadisticas() {
    golesF = 0;
    golesC = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;
}

// CONSTRUCTOR
Equipo::Equipo() {
    pais = "";
    tecnico = "";
    confederacion = "";
    rankingFIFA = 0;

    historico = Estadisticas();
    actual = Estadisticas();

    inicializarJugadores();
}

//  RESET TORNEO
void Equipo::reiniciarActual() {
    actual = Estadisticas();
}

// JUGADORES
void Equipo::inicializarJugadores() {

    for (int i = 0; i < 26; i++) {

        int num = i + 1;

        jugadores[i].nombre = "Jugador";
        jugadores[i].apellido = "Apellido";
        jugadores[i].numero = num;

        jugadores[i].goles = 0;
        jugadores[i].amarillas = 0;
        jugadores[i].rojas = 0;
        jugadores[i].minutos = 0;
    }
}

//ALINEACIÓN
Jugador** Equipo::obtenerAlineacion() {

    Jugador** alineacion = new Jugador*[11];

    bool usados[26] = { false };

    for (int i = 0; i < 11; i++) {

        int indice;

        do {
            indice = rand() % 26;
        } while (usados[indice]);

        usados[indice] = true;

        alineacion[i] = &jugadores[indice];
    }

    return alineacion;
}
