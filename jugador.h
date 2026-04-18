#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador {
public:
    string nombre;
    string apellido;
    int numero;

    int goles;
    int amarillas;
    int rojas;
    int minutos;

    Jugador();
};

#endif
