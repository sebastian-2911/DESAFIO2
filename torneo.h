#ifndef TORNEO_H
#define TORNEO_H

#include <string>
#include "equipo.h"

using namespace std;

class Torneo {
private:
    Equipo* equipos;   // arreglo dinámico
    int cantidad;      // cuántos equipos hay

public:
    Torneo();          // constructor
    ~Torneo();         // destructor

    void cargarEquipos(string nombreArchivo);
    void mostrarEquipos();
};

#endif
