#ifndef CLASIFICADO_H
#define CLASIFICADO_H

#include "equipo.h"

class Clasificado {
public:
    Equipo* equipo;
    char grupo;
    int posicion;
    int puntos;
    int diferencia;
    int golesFavor;

    Clasificado()
        : equipo(0), grupo(' '), posicion(0),
        puntos(0), diferencia(0), golesFavor(0) {}
};

#endif