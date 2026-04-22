#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using std::string;

class Jugador {
public:
    string nombre;
    string apellido;
    int numero;

    int goles;
    int amarillas;
    int rojas;
    int minutos;

    Jugador();  // constructor
};

#endif
