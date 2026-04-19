#include "fase.h"

// Constructor
Fase::Fase() {
}

// Iniciar fase de grupos
void Fase::iniciarFase(Equipo* equipos, int cantidad) {
    grupos.crearGrupos(equipos, cantidad);
}

// Mostrar grupos
void Fase::mostrar() {
    grupos.mostrarGrupos();
}
