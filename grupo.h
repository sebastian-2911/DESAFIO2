#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"
#include "partido.h"
#include <string>

using namespace std;

class Grupo {
private:
    Equipo* grupos[48];
    Equipo* bombo1[12];
    Equipo* bombo2[12];
    Equipo* bombo3[12];
    Equipo* bombo4[12];

    Partido partidos[72];
    int totalPartidos;

    void intercambiar(Equipo*& a, Equipo*& b);
    void barajarBombo(Equipo** bombo, int n);
    bool sePuedeAgregar(Equipo** grupoTemp, int usados, Equipo* candidato);
    void crearBombos(Equipo* equipos, int cantidad);

    bool armarGruposRecursivo(int grupoActual, int bomboActual,
                              bool usados1[], bool usados2[],
                              bool usados3[], bool usados4[]);

    bool vaAntes(Equipo* a, Equipo* b);
    void ordenarGrupo(int inicio);
    string construirFechaDesdeIndice(int dia) const;

public:
    Grupo();

    void crearGrupos(Equipo* equipos, int cantidad);
    void crearPartidos();
    void jugarDia(string fecha);

    void mostrarCalendario() const;

    void obtenerGruposOrdenados(Equipo* destino[48]);
    void mostrarGrupos();

    bool todosLosPartidosJugados() const;

};

#endif



