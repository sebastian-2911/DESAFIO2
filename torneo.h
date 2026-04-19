#ifndef TORNEO_H
#define TORNEO_H

#include "equipo.h"
#include <string>

using namespace std;

class Torneo {
private:
    Equipo* equipos;
    int cantidad;

public:
    Torneo();
    ~Torneo();

    void cargarEquipos(string nombreArchivo);


    Equipo* getEquipos();
    int getCantidad();
};

#endif
