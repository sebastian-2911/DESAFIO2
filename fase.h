#ifndef FASE_H
#define FASE_H

#include <string>
#include "grupo.h"
#include "Equipo.h"

using namespace std;

class Fase {
private:
    Grupo grupos;
    int diaActual;

public:
    Fase();

    void iniciarFase(Equipo* equipos, int cantidad);
    void iniciarCalendario();
    void avanzarDia();
    void mostrarGrupos();
};

#endif
