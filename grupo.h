#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Equipo;
class Partido;

class Grupo {

private:
    Equipo* bombo1[12];
    Equipo* bombo2[12];
    Equipo* bombo3[12];
    Equipo* bombo4[12];

    Equipo* grupos[48]; // 12 grupos * 4 equipos

    Partido* partidos;
    int totalPartidos;

    // auxiliares
    bool sePuedeAgregar(Equipo** grupoTemp, int usados, Equipo* candidato);
    void intercambiar(Equipo*& a, Equipo*& b);
    void barajarBombo(Equipo** bombo, int n);
    bool armarGruposRecursivo(int grupoActual, int bomboActual,
                              bool usados1[], bool usados2[],
                              bool usados3[], bool usados4[]);

    bool vaAntes(Equipo* a, Equipo* b);
    void ordenarGrupo(int inicio);

public:
    Grupo();

    void crearBombos(Equipo* equipos, int cantidad);
    void crearGrupos(Equipo* equipos, int cantidad);
    void crearPartidos();

    void jugarDia(string fecha);
    void mostrarGrupos();
};

#endif



