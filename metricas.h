#ifndef METRICAS_H
#define METRICAS_H
#include "equipo.h"

#include <iostream>
using namespace std;

class Metricas {
private:
    static long long iteraciones;


public:
    static void reiniciar();
    static void sumarIteracion();
    static void sumarIteraciones(long long cantidad);
    static long long getIteraciones();

    static void mostrar(const string& nombreFuncionalidad, long long memoria);

};
long long calcularMemoriaTotal(Equipo* equipos, int cantidadEquipos);
#endif