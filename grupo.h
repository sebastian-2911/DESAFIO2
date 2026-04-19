#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"

class Grupo {
private:
    Equipo** grupos; // arreglo de punteros (48 equipos)

public:
    Grupo();
    ~Grupo();

    void crearGrupos(Equipo* equipos, int cantidad);
    void mostrarGrupos();
};

#endif


