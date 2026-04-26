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
long long calcularMemoriaTorneo(int cantidadEquipos) {
    long long memoria = 0;

    memoria += sizeof(Equipo) * cantidadEquipos;
    memoria += sizeof(int); // cantidadEquipos

    return memoria;
}

long long calcularMemoriaGrupos() {
    long long memoria = 0;

    memoria += sizeof(Equipo*) * 48; // grupos
    memoria += sizeof(Equipo*) * 12; // bombo1
    memoria += sizeof(Equipo*) * 12; // bombo2
    memoria += sizeof(Equipo*) * 12; // bombo3
    memoria += sizeof(Equipo*) * 12; // bombo4

    memoria += sizeof(Partido) * 72; // partidos fase de grupos
    memoria += sizeof(int);          // totalPartidos

    return memoria;
}

long long calcularMemoriaEliminatoria(bool dieciseisavosCreados) {
    long long memoria = 0;

    if (!dieciseisavosCreados) {
        return 0;
    }

    memoria += sizeof(Partido) * 16; // dieciseisavos
    memoria += sizeof(Partido) * 8;  // octavos
    memoria += sizeof(Partido) * 4;  // cuartos
    memoria += sizeof(Partido) * 2;  // semifinales
    memoria += sizeof(Partido) * 1;  // tercer puesto
    memoria += sizeof(Partido) * 1;  // final

    memoria += sizeof(int) * 6;      // totales de rondas

    return memoria;
}