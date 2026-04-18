#include "torneo.h"

int main() {
    Torneo t;

    t.cargarEquipos("fifa.csv");
    t.mostrarEquipos();

    return 0;
}
