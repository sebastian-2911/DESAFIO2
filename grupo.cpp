#include "grupo.h"
#include "equipo.h"
#include "partido.h"
#include <iostream>
#include <cstdlib>
#include "metricas.h"

using namespace std;

// CONSTRUCTOR
Grupo::Grupo() {
    totalPartidos = 0;

    for (int i = 0; i < 48; i++) {
        Metricas::sumarIteracion();
        grupos[i] = 0;
    }
}

// INTERCAMBIO MANUAL
void Grupo::intercambiar(Equipo*& a, Equipo*& b) {
    Equipo* temp = a;
    a = b;
    b = temp;
}

// BARAJAR BOMBO
void Grupo::barajarBombo(Equipo** bombo, int n) {
    for (int i = 0; i < n; i++) {
        Metricas::sumarIteracion();
        int r = rand() % n;
        intercambiar(bombo[i], bombo[r]);
    }
}

// VALIDAR CONFEDERACIONES
bool Grupo::sePuedeAgregar(Equipo** grupoTemp, int usados, Equipo* candidato) {
    int uefa = 0;

    for (int i = 0; i < usados; i++) {
        Metricas::sumarIteracion();
        if (grupoTemp[i]->confederacion == "UEFA") {
            uefa++;
        }

        if (grupoTemp[i]->confederacion == candidato->confederacion) {
            if (candidato->confederacion == "UEFA") {
                if (uefa >= 2) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }

    return true;
}

// CREAR BOMBOS
void Grupo::crearBombos(Equipo* equipos, int cantidad) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    bool usaAgregado = false;

    for (int i = 0; i < cantidad; i++) {
        Metricas::sumarIteracion();
        if (equipos[i].pais == "United States") {
            bombo1[n1++] = &equipos[i];
            usaAgregado = true;
            break;
        }
    }

    for (int i = 0; i < cantidad; i++) {
        Metricas::sumarIteracion();
        if (usaAgregado && equipos[i].pais == "United States") {
            continue;
        }

        if (n1 < 12) {
            bombo1[n1++] = &equipos[i];
        }
        else if (n2 < 12) {
            bombo2[n2++] = &equipos[i];
        }
        else if (n3 < 12) {
            bombo3[n3++] = &equipos[i];
        }
        else if (n4 < 12) {
            bombo4[n4++] = &equipos[i];
        }
    }
}

// BACKTRACKING PARA ARMAR GRUPOS
bool Grupo::armarGruposRecursivo(int grupoActual, int bomboActual,
                                 bool usados1[], bool usados2[],
                                 bool usados3[], bool usados4[]) {
    if (grupoActual == 12) {
        return true;
    }

    if (bomboActual == 4) {
        return armarGruposRecursivo(grupoActual + 1, 0,
                                    usados1, usados2, usados3, usados4);
    }

    Equipo** bombo = 0;
    bool* usados = 0;

    if (bomboActual == 0) {
        bombo = bombo1;
        usados = usados1;
    }
    else if (bomboActual == 1) {
        bombo = bombo2;
        usados = usados2;
    }
    else if (bomboActual == 2) {
        bombo = bombo3;
        usados = usados3;
    }
    else {
        bombo = bombo4;
        usados = usados4;
    }

    int base = grupoActual * 4;

    Equipo* grupoTemp[4];
    for (int i = 0; i < bomboActual; i++) {
        Metricas::sumarIteracion();
        grupoTemp[i] = grupos[base + i];
    }

    for (int i = 0; i < 12; i++) {
        Metricas::sumarIteracion();
        if (!usados[i]) {
            if (sePuedeAgregar(grupoTemp, bomboActual, bombo[i])) {
                grupos[base + bomboActual] = bombo[i];
                usados[i] = true;

                if (armarGruposRecursivo(grupoActual, bomboActual + 1,
                                         usados1, usados2, usados3, usados4)) {
                    return true;
                }

                usados[i] = false;
                grupos[base + bomboActual] = 0;
            }
        }
    }

    return false;
}

// CREAR GRUPOS
void Grupo::crearGrupos(Equipo* equipos, int cantidad) {
    crearBombos(equipos, cantidad);

    barajarBombo(bombo1, 12);
    barajarBombo(bombo2, 12);
    barajarBombo(bombo3, 12);
    barajarBombo(bombo4, 12);

    for (int i = 0; i < 48; i++) {
        Metricas::sumarIteracion();
        grupos[i] = 0;
    }

    bool usados1[12] = { false };
    bool usados2[12] = { false };
    bool usados3[12] = { false };
    bool usados4[12] = { false };

    bool ok = armarGruposRecursivo(0, 0, usados1, usados2, usados3, usados4);

    if (!ok) {
        cout << "Error: no se pudieron generar grupos validos" << endl;
    }
}

// CONSTRUIR FECHA DESDE ÍNDICE DE DÍA
string Grupo::construirFechaDesdeIndice(int dia) const {
    int diaReal = 20 + dia;
    int mes = 6;

    if (diaReal > 30) {
        diaReal -= 30;
        mes = 7;
    }

    string fecha = "";

    if (diaReal < 10) {
        fecha += "0";
    }
    fecha += to_string(diaReal);

    fecha += "/";

    if (mes < 10) {
        fecha += "0";
    }
    fecha += to_string(mes);

    fecha += "/2026";

    return fecha;
}

// CREAR PARTIDOS
void Grupo::crearPartidos() {
    totalPartidos = 0;

    for (int ronda = 0; ronda < 3; ronda++) {
        Metricas::sumarIteracion();
        for (int g = 0; g < 12; g++) {
            Metricas::sumarIteracion();
            int base = g * 4;

            Equipo* e1 = grupos[base];
            Equipo* e2 = grupos[base + 1];
            Equipo* e3 = grupos[base + 2];
            Equipo* e4 = grupos[base + 3];

            int dia = ronda * 6 + (g / 2);
            string fecha = construirFechaDesdeIndice(dia);

            Partido p1;
            Partido p2;

            if (ronda == 0) {
                p1 = Partido(e1, e2);
                p2 = Partido(e3, e4);
            }
            else if (ronda == 1) {
                p1 = Partido(e1, e3);
                p2 = Partido(e2, e4);
            }
            else {
                p1 = Partido(e1, e4);
                p2 = Partido(e2, e3);
            }

            p1.configurar(
                fecha,
                "00:00",
                "nombreSede",
                "codArbitro1",
                "codArbitro2",
                "codArbitro3"
                );

            p2.configurar(
                fecha,
                "00:00",
                "nombreSede",
                "codArbitro1",
                "codArbitro2",
                "codArbitro3"
                );

            partidos[totalPartidos] = p1;
            totalPartidos++;

            partidos[totalPartidos] = p2;
            totalPartidos++;
        }
    }
}
// JUGAR DÍA
void Grupo::jugarDia(string fecha) {
    cout << "\nPARTIDOS DEL DIA" << endl;
    cout << "----------------" << endl;

    bool huboPartidos = false;

    for (int i = 0; i < totalPartidos; i++) {
        Metricas::sumarIteracion();
        if (partidos[i].getFecha() == fecha) {
            partidos[i].jugar();
            partidos[i].mostrarDetalle();
            huboPartidos = true;
        }
    }

    if (!huboPartidos) {
        cout << "No hay partidos programados para esta fecha." << endl;
    }

    cout << endl;
}

// REVISAR SI YA SE JUGARON TODOS LOS PARTIDOS
bool Grupo::todosLosPartidosJugados() const {
    Metricas::sumarIteracion();
    for (int i = 0; i < totalPartidos; i++) {
        if (!partidos[i].yaSeJugo()) {
            return false;
        }
    }
    return true;
}
// COMPARADOR TABLA
bool Grupo::vaAntes(Equipo* a, Equipo* b) {
    int ptsA = a->actual.ganados * 3 + a->actual.empatados;
    int ptsB = b->actual.ganados * 3 + b->actual.empatados;

    if (ptsA != ptsB) {
        return ptsA > ptsB;
    }

    int diffA = a->actual.golesF - a->actual.golesC;
    int diffB = b->actual.golesF - b->actual.golesC;

    if (diffA != diffB) {
        return diffA > diffB;
    }

    return a->actual.golesF > b->actual.golesF;
}

// ORDENAR GRUPO
void Grupo::ordenarGrupo(int inicio) {
    for (int i = inicio; i < inicio + 4; i++) {
        Metricas::sumarIteracion();
        for (int j = i + 1; j < inicio + 4; j++) {
            Metricas::sumarIteracion();
            if (!vaAntes(grupos[i], grupos[j])) {
                intercambiar(grupos[i], grupos[j]);
            }
        }
    }
}

// OBTENER GRUPOS ORDENADOS
void Grupo::obtenerGruposOrdenados(Equipo* destino[48]) {
    for (int g = 0; g < 12; g++) {
        Metricas::sumarIteracion();
        int inicio = g * 4;
        ordenarGrupo(inicio);

        for (int i = 0; i < 4; i++) {
            Metricas::sumarIteracion();
            destino[inicio + i] = grupos[inicio + i];
        }
    }
}

// MOSTRAR GRUPOS
void Grupo::mostrarGrupos() {
    char letra = 'A';

    for (int i = 0; i < 12; i++) {
        Metricas::sumarIteracion();
        int inicio = i * 4;

        ordenarGrupo(inicio);

        cout << "Grupo " << letra << endl;

        for (int j = 0; j < 4; j++) {
            Metricas::sumarIteracion();
            Equipo* e = grupos[inicio + j];
            int puntos = e->actual.ganados * 3 + e->actual.empatados;

            cout << e->pais
                 << " | " << e->confederacion
                 << " | Pts: " << puntos
                 << " | GF: " << e->actual.golesF
                 << " | GC: " << e->actual.golesC
                 << endl;
        }

        cout << endl;
        letra++;
    }
}
void Grupo::mostrarCalendario() const {
    cout << "\n===== CALENDARIO FASE DE GRUPOS =====" << endl;
    cout << "=====================================" << endl;

    string fechaActual = "";

    for (int i = 0; i < totalPartidos; i++) {
        Metricas::sumarIteracion();
        if (partidos[i].getFecha() != fechaActual) {
            fechaActual = partidos[i].getFecha();

            cout << "\nFecha: " << fechaActual << endl;
            cout << "------------------------" << endl;
        }

        cout << partidos[i].getHora() << " | "
             << partidos[i].getEquipoLocal()->pais
             << " vs "
             << partidos[i].getEquipoVisitante()->pais
             << endl;
    }

    cout << endl;
}

Grupo::Grupo(const Grupo& otro)
    : totalPartidos(otro.totalPartidos)
{
    for (int i = 0; i < 48; i++) {
        grupos[i] = otro.grupos[i];
    }

    for (int i = 0; i < 12; i++) {
        bombo1[i] = otro.bombo1[i];
        bombo2[i] = otro.bombo2[i];
        bombo3[i] = otro.bombo3[i];
        bombo4[i] = otro.bombo4[i];
    }

    for (int i = 0; i < 72; i++) {
        partidos[i] = otro.partidos[i];
    }
}

//sobrecarga
Grupo& Grupo::operator=(const Grupo& otro) {
    if (this != &otro) {
        totalPartidos = otro.totalPartidos;

        for (int i = 0; i < 48; i++) {
            grupos[i] = otro.grupos[i];
        }

        for (int i = 0; i < 12; i++) {
            bombo1[i] = otro.bombo1[i];
            bombo2[i] = otro.bombo2[i];
            bombo3[i] = otro.bombo3[i];
            bombo4[i] = otro.bombo4[i];
        }

        for (int i = 0; i < 72; i++) {
            partidos[i] = otro.partidos[i];
        }
    }

    return *this;
}

bool Grupo::operator==(const Grupo& otro) const {
    return totalPartidos == otro.totalPartidos;
}

bool Grupo::operator>(const Grupo& otro) const {
    return totalPartidos > otro.totalPartidos;
}