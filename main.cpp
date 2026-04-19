#include "torneo.h"
#include "fase.h"

int main() {

    Torneo t;
    t.cargarEquipos("fifa.csv");

    Fase f;

    f.iniciarFase(t.getEquipos(), t.getCantidad());
    f.mostrar();

    return 0;
}
