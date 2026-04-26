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

    Clasificado(const Clasificado& otro)
        : equipo(otro.equipo),
        grupo(otro.grupo),
        posicion(otro.posicion),
        puntos(otro.puntos),
        diferencia(otro.diferencia),
        golesFavor(otro.golesFavor)
    {
    }
    //sobrecarga
    Clasificado& operator=(const Clasificado& otro) {
        if (this != &otro) {
            equipo = otro.equipo;
            grupo = otro.grupo;
            posicion = otro.posicion;
            puntos = otro.puntos;
            diferencia = otro.diferencia;
            golesFavor = otro.golesFavor;
        }
        return *this;
    }

    bool operator==(const Clasificado& otro) const {
        return equipo == otro.equipo &&
               grupo == otro.grupo &&
               posicion == otro.posicion;
    }

    bool operator>(const Clasificado& otro) const {
        if (puntos != otro.puntos) {
            return puntos > otro.puntos;
        }

        if (diferencia != otro.diferencia) {
            return diferencia > otro.diferencia;
        }

        return golesFavor > otro.golesFavor;
    }
};

#endif