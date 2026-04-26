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

    Jugador();
    Jugador(const Jugador& otro);

    //sobrecarga
    Jugador& operator=(const Jugador& otro);
    bool operator==(const Jugador& otro) const;
    bool operator>(const Jugador& otro) const;
};

#endif
