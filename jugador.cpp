#include "jugador.h"

Jugador::Jugador()
    : nombre(""),
    apellido(""),
    numero(0),
    goles(0),
    amarillas(0),
    rojas(0),
    minutos(0)
{
}
Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre),
    apellido(otro.apellido),
    numero(otro.numero),
    goles(otro.goles),
    amarillas(otro.amarillas),
    rojas(otro.rojas),
    minutos(otro.minutos)
{

}

//sobrecarga
Jugador& Jugador::operator=(const Jugador& otro) {
    if (this != &otro) {
        nombre = otro.nombre;
        apellido = otro.apellido;
        numero = otro.numero;
        goles = otro.goles;
        amarillas = otro.amarillas;
        rojas = otro.rojas;
        minutos = otro.minutos;
    }

    return *this;
}

bool Jugador::operator==(const Jugador& otro) const {
    return numero == otro.numero &&
           nombre == otro.nombre &&
           apellido == otro.apellido;
}

bool Jugador::operator>(const Jugador& otro) const {
    return goles > otro.goles;
}
