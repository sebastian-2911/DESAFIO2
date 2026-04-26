#ifndef TORNEO_H
#define TORNEO_H

#include "equipo.h"
#include <string>

using namespace std;

class Torneo {
private:
    Equipo* equipos;
    int cantidadEquipos;
    int capacidadEquipos;

    int calcularPuntos(int ganados, int empatados) const;
    int calcularPartidos(int ganados, int empatados, int perdidos) const;

public:
    Torneo();
    ~Torneo();

    void cargarEquipos(const string& nombreArchivo);

    void mostrarTodo() const;
    void mostrarEstadisticasEquipos() const;
    void mostrarEstadisticasJugadores() const;

    void guardarEquiposCSV(const string& nombreArchivo) const;
    void guardarJugadoresCSV(const string& nombreArchivo) const;

    Equipo* getEquipos();
    int getCantidad() const;

    Torneo(const Torneo& otro);

    //sobrecarga
    Torneo& operator=(const Torneo& otro);
    bool operator==(const Torneo& otro) const;
    bool operator>(const Torneo& otro) const;
};

#endif