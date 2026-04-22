#include "Partido.h"
#include "Equipo.h"
#include "Jugador.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const float MU   = 1.35f;
const float ALFA = 0.4f;
const float BETA = 0.6f;

Partido::Partido() {
    equipoLocal = 0;
    equipoVisitante = 0;

    sede = "";
    arbitro1 = "";
    arbitro2 = "";
    arbitro3 = "";
    fecha = "";
    hora = "";

    golesLocal = 0;
    golesVisitante = 0;

    posesionLocal = 0;
    posesionVisitante = 0;

    tirosLocal = 0;
    tirosVisitante = 0;

    tirosArcoLocal = 0;
    tirosArcoVisitante = 0;

    faltasLocal = 0;
    faltasVisitante = 0;

    amarillasLocal = 0;
    amarillasVisitante = 0;

    rojasLocal = 0;
    rojasVisitante = 0;

    jugado = false;
}

Partido::Partido(Equipo* local, Equipo* visitante) {
    equipoLocal = local;
    equipoVisitante = visitante;

    sede = "";
    arbitro1 = "";
    arbitro2 = "";
    arbitro3 = "";
    fecha = "";
    hora = "";

    golesLocal = 0;
    golesVisitante = 0;

    posesionLocal = 0;
    posesionVisitante = 0;

    tirosLocal = 0;
    tirosVisitante = 0;

    tirosArcoLocal = 0;
    tirosArcoVisitante = 0;

    faltasLocal = 0;
    faltasVisitante = 0;

    amarillasLocal = 0;
    amarillasVisitante = 0;

    rojasLocal = 0;
    rojasVisitante = 0;

    jugado = false;
}

void Partido::configurar(string fechaPartido,
                         string horaPartido,
                         string nombreSede,
                         string arb1,
                         string arb2,
                         string arb3) {
    fecha = fechaPartido;
    hora = horaPartido;
    sede = nombreSede;
    arbitro1 = arb1;
    arbitro2 = arb2;
    arbitro3 = arb3;
}

int Partido::limitarEntero(int valor, int minimo, int maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

int Partido::poisson(float lambda) {
    if (lambda <= 0.0f) return 0;

    float L = exp(-lambda);
    int k = 0;
    float p = 1.0f;

    do {
        k++;
        p *= (float)rand() / (float)RAND_MAX;
    } while (p > L);

    return k - 1;
}

float Partido::calcularLambda(Equipo* ataque, Equipo* defensa) {
    int partidosAtaque = ataque->historico.ganados
                         + ataque->historico.empatados
                         + ataque->historico.perdidos;

    int partidosDefensa = defensa->historico.ganados
                          + defensa->historico.empatados
                          + defensa->historico.perdidos;

    float promedioGF = MU;
    float promedioGC = MU;

    if (partidosAtaque > 0) {
        promedioGF = (float)ataque->historico.golesF / (float)partidosAtaque;
    }

    if (partidosDefensa > 0) {
        promedioGC = (float)defensa->historico.golesC / (float)partidosDefensa;
    }

    if (promedioGF <= 0.0f) promedioGF = 0.1f;
    if (promedioGC <= 0.0f) promedioGC = 0.1f;

    // Formula del enunciado:
    // lambda = MU * (GFA / MU)^ALFA * (GCB / MU)^BETA
    float lambda = MU * pow(promedioGF / MU, ALFA) * pow(promedioGC / MU, BETA);

    // Limites para evitar resultados absurdos
    if (lambda < 0.15f) lambda = 0.15f;
    if (lambda > 4.50f) lambda = 4.50f;

    return lambda;
}

void Partido::jugar() {
    if (!equipoLocal || !equipoVisitante || jugado) return;

    Jugador** A = equipoLocal->obtenerAlineacion();
    Jugador** B = equipoVisitante->obtenerAlineacion();

    float lambdaL = calcularLambda(equipoLocal, equipoVisitante);
    float lambdaV = calcularLambda(equipoVisitante, equipoLocal);

    golesLocal = poisson(lambdaL);
    golesVisitante = poisson(lambdaV);

    // Posesion
    int basePosesion = 45 + rand() % 11;
    posesionLocal = limitarEntero(basePosesion, 35, 65);
    posesionVisitante = 100 - posesionLocal;

    // Tiros
    tirosLocal = golesLocal + 3 + rand() % 8;
    tirosVisitante = golesVisitante + 3 + rand() % 8;

    tirosArcoLocal = golesLocal + rand() % 4;
    tirosArcoVisitante = golesVisitante + rand() % 4;

    if (tirosArcoLocal > tirosLocal) tirosArcoLocal = tirosLocal;
    if (tirosArcoVisitante > tirosVisitante) tirosArcoVisitante = tirosVisitante;

    // Faltas y tarjetas
    faltasLocal = 5 + rand() % 11;
    faltasVisitante = 5 + rand() % 11;

    amarillasLocal = rand() % 5;
    amarillasVisitante = rand() % 5;

    rojasLocal = (rand() % 100 < 8) ? 1 : 0;
    rojasVisitante = (rand() % 100 < 8) ? 1 : 0;

    // Actualizar torneo actual
    equipoLocal->actual.golesF += golesLocal;
    equipoLocal->actual.golesC += golesVisitante;

    equipoVisitante->actual.golesF += golesVisitante;
    equipoVisitante->actual.golesC += golesLocal;

    if (golesLocal > golesVisitante) {
        equipoLocal->actual.ganados++;
        equipoVisitante->actual.perdidos++;
    }
    else if (golesVisitante > golesLocal) {
        equipoVisitante->actual.ganados++;
        equipoLocal->actual.perdidos++;
    }
    else {
        equipoLocal->actual.empatados++;
        equipoVisitante->actual.empatados++;
    }

    // Goles a jugadores
    for (int i = 0; i < golesLocal; i++) {
        A[rand() % 11]->goles++;
    }

    for (int i = 0; i < golesVisitante; i++) {
        B[rand() % 11]->goles++;
    }

    // Amarillas
    for (int i = 0; i < amarillasLocal; i++) {
        A[rand() % 11]->amarillas++;
    }

    for (int i = 0; i < amarillasVisitante; i++) {
        B[rand() % 11]->amarillas++;
    }

    // Rojas
    for (int i = 0; i < rojasLocal; i++) {
        A[rand() % 11]->rojas++;
    }

    for (int i = 0; i < rojasVisitante; i++) {
        B[rand() % 11]->rojas++;
    }

    // Minutos jugados
    for (int i = 0; i < 11; i++) {
        A[i]->minutos += 90;
        B[i]->minutos += 90;
    }

    jugado = true;

    delete[] A;
    delete[] B;
}

void Partido::mostrar() {
    cout << fecha << " " << hora << " | "
         << equipoLocal->pais << " "
         << golesLocal << " - "
         << golesVisitante << " "
         << equipoVisitante->pais << endl;
}

void Partido::mostrarDetalle() {
    cout << "----------------------------------------" << endl;
    cout << fecha << " " << hora << endl;
    cout << "Sede: " << sede << endl;
    cout << "Arbitros: " << arbitro1 << ", " << arbitro2 << ", " << arbitro3 << endl;
    cout << equipoLocal->pais << " " << golesLocal
         << " - " << golesVisitante << " " << equipoVisitante->pais << endl;
    cout << "Posesion: " << posesionLocal << "% - " << posesionVisitante << "%" << endl;
    cout << "Tiros: " << tirosLocal << " - " << tirosVisitante << endl;
    cout << "Tiros al arco: " << tirosArcoLocal << " - " << tirosArcoVisitante << endl;
    cout << "Faltas: " << faltasLocal << " - " << faltasVisitante << endl;
    cout << "Amarillas: " << amarillasLocal << " - " << amarillasVisitante << endl;
    cout << "Rojas: " << rojasLocal << " - " << rojasVisitante << endl;
    cout << "----------------------------------------" << endl;
}

string Partido::getFecha() {
    return fecha;
}

string Partido::getHora() {
    return hora;
}

Equipo* Partido::getEquipoLocal() {
    return equipoLocal;
}

Equipo* Partido::getEquipoVisitante() {
    return equipoVisitante;
}

int Partido::getGolesLocal() {
    return golesLocal;
}

int Partido::getGolesVisitante() {
    return golesVisitante;
}

int Partido::getPosesionLocal() {
    return posesionLocal;
}

int Partido::getPosesionVisitante() {
    return posesionVisitante;
}

bool Partido::yaSeJugo() {
    return jugado;
}
