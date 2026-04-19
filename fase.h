#ifndef FASE_H
#define FASE_H

#include "grupo.h"
#include "equipo.h"

class Fase {
private:
    Grupo grupos;

public:
    Fase();

    void iniciarFase(Equipo* equipos, int cantidad);
    void mostrar();
};

#endif
