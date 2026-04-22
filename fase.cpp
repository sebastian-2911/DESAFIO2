#include "fase.h"
#include <iostream>

using namespace std;

Fase::Fase() {
    diaActual = 0;
}

void Fase::iniciarFase(Equipo* equipos, int cantidad) {
    grupos.crearGrupos(equipos, cantidad);
    grupos.crearPartidos();
}

void Fase::iniciarCalendario() {
    diaActual = 0;
}

void Fase::mostrarGrupos() {
    cout << "\n===== TABLA DE GRUPOS =====" << endl;
    cout << "===========================" << endl << endl;

    grupos.mostrarGrupos();
}

void Fase::avanzarDia() {
    string fecha = to_string(20 + diaActual) + "/06/2026";

    cout << "\n=================================" << endl;
    cout << "            DIA " << diaActual + 1 << endl;
    cout << "=================================" << endl;
    cout << "Fecha: " << fecha << endl << endl;

    grupos.jugarDia(fecha);

    mostrarGrupos();

    diaActual++;
}
