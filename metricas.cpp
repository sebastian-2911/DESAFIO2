#include "metricas.h"
#include "equipo.h"
#include "jugador.h"
#include "partido.h"

long long Metricas::iteraciones = 0;

void Metricas::reiniciar() {
    iteraciones = 0;
}

void Metricas::sumarIteracion() {
    iteraciones++;
}

void Metricas::sumarIteraciones(long long cantidad) {
    iteraciones += cantidad;
}

long long Metricas::getIteraciones() {
    return iteraciones;
}

void Metricas::mostrar(const string& nombreFuncionalidad, long long memoria) {
    cout << "\n===== MEDICION DE RECURSOS =====" << endl;
    cout << "Funcionalidad: " << nombreFuncionalidad << endl;
    cout << "Iteraciones: " << iteraciones << endl;
    cout << "Memoria estimada: " << memoria << " bytes" << endl;
    cout << "================================" << endl;
}
long long calcularMemoriaTotal(Equipo* equipos, int cantidadEquipos) {
    long long memoria = 0;

    // Equipos
    memoria += sizeof(Equipo) * cantidadEquipos;

    // Jugadores
    memoria += sizeof(Jugador) * 26 * cantidadEquipos;

    // Partidos (RECOMENDADO)
    memoria += sizeof(Partido) * 72;  // grupos
    memoria += sizeof(Partido) * 16;  // dieciseisavos
    memoria += sizeof(Partido) * 8;   // octavos
    memoria += sizeof(Partido) * 4;   // cuartos
    memoria += sizeof(Partido) * 2;   // semifinales
    memoria += sizeof(Partido) * 2;   // final + tercero

    return memoria;
}