#include "partido.h"
#include "equipo.h"
#include "jugador.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "metricas.h"

using namespace std;

const float MU   = 1.35f;
const float ALFA = 0.4f;
const float BETA = 0.6f;

void Partido::reset() {
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
    prorrogaJugada = false;
}

Partido::Partido() {
    equipoLocal = 0;
    equipoVisitante = 0;
    reset();
}

Partido::Partido(Equipo* local, Equipo* visitante) {
    equipoLocal = local;
    equipoVisitante = visitante;
    reset();
}

void Partido::configurar(const string& fechaPartido,
                         const string& horaPartido,
                         const string& nombreSede,
                         const string& arb1,
                         const string& arb2,
                         const string& arb3) {
    fecha = fechaPartido;
    hora = horaPartido;
    sede = nombreSede;
    arbitro1 = arb1;
    arbitro2 = arb2;
    arbitro3 = arb3;
}

int Partido::limitarEntero(int valor, int minimo, int maximo) const {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

int Partido::poisson(float lambda) const {
    if (lambda <= 0.0f) return 0;

    float L = exp(-lambda);
    int k = 0;
    float p = 1.0f;

    do {
        Metricas::sumarIteracion();
        k++;
        p *= (float)rand() / (float)RAND_MAX;
    } while (p > L);

    return k - 1;
}
float Partido::calcularLambda(Equipo* ataque, Equipo* defensa) const {
    int partidosA = ataque->historico.ganados +
                    ataque->historico.empatados +
                    ataque->historico.perdidos;

    int partidosB = defensa->historico.ganados +
                    defensa->historico.empatados +
                    defensa->historico.perdidos;

    float gf = MU;
    float gc = MU;

    if (partidosA > 0) {
        gf = (float)ataque->historico.golesF / partidosA;
    }

    if (partidosB > 0) {
        gc = (float)defensa->historico.golesC / partidosB;
    }

    if (gf < 0.2f) gf = 0.2f;
    if (gc < 0.2f) gc = 0.2f;

    // ranking menor = mejor equipo
    float fuerzaAtaque = (210.0f - ataque->rankingFIFA) / 209.0f;
    float fuerzaDefensa = (210.0f - defensa->rankingFIFA) / 209.0f;

    if (fuerzaAtaque < 0.15f) fuerzaAtaque = 0.15f;
    if (fuerzaDefensa < 0.15f) fuerzaDefensa = 0.15f;

    float lambda = 0.35f
                   + gf * 0.45f
                   + gc * 0.15f
                   + fuerzaAtaque * 1.10f
                   - fuerzaDefensa * 0.55f;

    if (lambda < 0.25f) lambda = 0.25f;
    if (lambda > 2.80f) lambda = 2.80f;

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

    // ===== POSESION BASADA EN RANKING =====
    int rankingLocal = equipoLocal->rankingFIFA;
    int rankingVisitante = equipoVisitante->rankingFIFA;

    int diferencia = rankingVisitante - rankingLocal;

    posesionLocal = 50 + (diferencia / 3) + ((rand() % 11) - 5);

    posesionLocal = limitarEntero(posesionLocal, 30, 70);
    posesionVisitante = 100 - posesionLocal;

    // ===== OTRAS ESTADISTICAS =====
    tirosLocal = golesLocal + 3 + rand() % 8;
    tirosVisitante = golesVisitante + 3 + rand() % 8;

    tirosArcoLocal = golesLocal + rand() % 4;
    tirosArcoVisitante = golesVisitante + rand() % 4;

    if (tirosArcoLocal > tirosLocal) tirosArcoLocal = tirosLocal;
    if (tirosArcoVisitante > tirosVisitante) tirosArcoVisitante = tirosVisitante;

    faltasLocal = 5 + rand() % 11;
    faltasVisitante = 5 + rand() % 11;

    amarillasLocal = rand() % 5;
    amarillasVisitante = rand() % 5;

    rojasLocal = (rand() % 100 < 8) ? 1 : 0;
    rojasVisitante = (rand() % 100 < 8) ? 1 : 0;

    // ===== ACTUALIZAR EQUIPOS =====
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

    // ===== ESTADISTICAS DE JUGADORES =====
    for (int i = 0; i < golesLocal; i++) {
        Metricas::sumarIteracion();
        A[rand() % 11]->goles++;
    }

    for (int i = 0; i < golesVisitante; i++) {
        Metricas::sumarIteracion();
        B[rand() % 11]->goles++;
    }

    for (int i = 0; i < amarillasLocal; i++) {
        Metricas::sumarIteracion();
        A[rand() % 11]->amarillas++;
    }

    for (int i = 0; i < amarillasVisitante; i++) {
        Metricas::sumarIteracion();
        B[rand() % 11]->amarillas++;
    }

    for (int i = 0; i < rojasLocal; i++) {
        Metricas::sumarIteracion();
        A[rand() % 11]->rojas++;
    }

    for (int i = 0; i < rojasVisitante; i++) {
        Metricas::sumarIteracion();
        B[rand() % 11]->rojas++;
    }

    for (int i = 0; i < 11; i++) {
        Metricas::sumarIteracion();
        A[i]->minutos += 90;
        B[i]->minutos += 90;
    }

    jugado = true;
}
void Partido::prorroga() {
    if (!jugado) return;
    if (golesLocal != golesVisitante) return;

    prorrogaJugada = true;

    int fuerzaLocal = 211 - equipoLocal->rankingFIFA;
    int fuerzaVisitante = 211 - equipoVisitante->rankingFIFA;

    if (fuerzaLocal < 1) fuerzaLocal = 1;
    if (fuerzaVisitante < 1) fuerzaVisitante = 1;

    int total = fuerzaLocal + fuerzaVisitante;
    int r = rand() % total;

    if (r < fuerzaLocal) {
        golesLocal++;
        equipoLocal->actual.golesF++;
        equipoVisitante->actual.golesC++;

        equipoLocal->getJugadorAlineado(rand() % 11)->goles++;
    }
    else {
        golesVisitante++;
        equipoVisitante->actual.golesF++;
        equipoLocal->actual.golesC++;

        equipoVisitante->getJugadorAlineado(rand() % 11)->goles++;
    }

    for (int i = 0; i < 11; i++) {
        Metricas::sumarIteracion();
        equipoLocal->getJugadorAlineado(i)->minutos += 30;
        equipoVisitante->getJugadorAlineado(i)->minutos += 30;
    }
}
void Partido::mostrar() const {
    cout << fecha << " " << hora << " | "
         << equipoLocal->pais << " "
         << golesLocal << " - "
         << golesVisitante << " "
         << equipoVisitante->pais << endl;
}

void Partido::mostrarDetalle() const {
    cout << "----------------------------------------" << endl;
    cout << fecha << " " << hora << endl;
    cout << "Sede: " << sede << endl;
    cout << "Arbitros: " << arbitro1 << ", " << arbitro2 << ", " << arbitro3 << endl;
    cout << equipoLocal->pais << " " << golesLocal
         << " - " << golesVisitante << " " << equipoVisitante->pais << endl;
    if (prorrogaJugada) {
        cout << "Definido en prorroga" << endl;
    }
    cout << "Posesion: " << posesionLocal << "% - " << posesionVisitante << "%" << endl;
    cout << "Tiros: " << tirosLocal << " - " << tirosVisitante << endl;
    cout << "Tiros al arco: " << tirosArcoLocal << " - " << tirosArcoVisitante << endl;
    cout << "Faltas: " << faltasLocal << " - " << faltasVisitante << endl;
    cout << "Amarillas: " << amarillasLocal << " - " << amarillasVisitante << endl;
    cout << "Rojas: " << rojasLocal << " - " << rojasVisitante << endl;
    cout << "----------------------------------------" << endl;
}

string Partido::getFecha() const {
    return fecha;
}

string Partido::getHora() const {
    return hora;
}

Equipo* Partido::getEquipoLocal() const {
    return equipoLocal;
}

Equipo* Partido::getEquipoVisitante() const {
    return equipoVisitante;
}

int Partido::getGolesLocal() const {
    return golesLocal;
}

int Partido::getGolesVisitante() const {
    return golesVisitante;
}

int Partido::getPosesionLocal() const {
    return posesionLocal;
}

int Partido::getPosesionVisitante() const {
    return posesionVisitante;
}

bool Partido::yaSeJugo() const {
    return jugado;
}
bool Partido::huboProrroga() const {
    return prorrogaJugada;
}
