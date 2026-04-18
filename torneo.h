#ifndef TORNEO_H
#define TORNEO_H

#include <string>
#include "equipo.h"
using namespace std;

class Torneo {
private:
    Equipo* equipos;
    int cantidad;

public:
    Torneo();
    ~Torneo();

    void cargarEquipos(string nombreArchivo);
    void mostrarEquipos();
};

#endif
