#ifndef TORNEO_H
#define TORNEO_H

#include <string>
using namespace std;

class Equipo;

class Torneo {
private:
    Equipo* equipos;
    int cantidad;

public:
    Torneo();
    ~Torneo();

    void cargarEquipos(string nombreArchivo);
    void mostrarTodo();

    void mostrarEstadisticasEquipos();
    void mostrarEstadisticasJugadores();

    Equipo* getEquipos();
    int getCantidad();
};

#endif
