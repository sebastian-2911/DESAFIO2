#include "Grupo.h"
#include "Equipo.h"
#include "Partido.h"

// CONSTRUCTOR
Grupo::Grupo() {
    totalPartidos = 0;
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
        int r = rand() % n;
        intercambiar(bombo[i], bombo[r]);
    }
}

// VALIDAR CONFEDERACIONES
bool Grupo::sePuedeAgregar(Equipo** grupoTemp, int usados, Equipo* candidato) {

    int uefa = 0;

    for (int i = 0; i < usados; i++) {

        if (grupoTemp[i]->confederacion == "UEFA") {
            uefa++;
        }

        if (grupoTemp[i]->confederacion == candidato->confederacion) {

            if (candidato->confederacion == "UEFA") {
                if (uefa >= 2) return false;
            } else {
                return false;
            }
        }
    }

    return true;
}

// CREAR BOMBOS (SIN DAÑAR EL ARREGLO ORIGINAL)
void Grupo::crearBombos(Equipo* equipos, int cantidad) {

    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    bool usaAgregado = false;

    // meter USA primero
    for (int i = 0; i < cantidad; i++) {
        if (equipos[i].pais == "United States") {
            bombo1[n1++] = &equipos[i];
            usaAgregado = true;
            break;
        }
    }

    for (int i = 0; i < cantidad; i++) {

        if (usaAgregado && equipos[i].pais == "United States")
            continue;

        if (n1 < 12)
            bombo1[n1++] = &equipos[i];
        else if (n2 < 12)
            bombo2[n2++] = &equipos[i];
        else if (n3 < 12)
            bombo3[n3++] = &equipos[i];
        else if (n4 < 12)
            bombo4[n4++] = &equipos[i];
    }
}

// BACKTRACKING PARA ARMAR GRUPOS
bool Grupo::armarGruposRecursivo(int grupoActual, int bomboActual,
                                 bool usados1[], bool usados2[],
                                 bool usados3[], bool usados4[]) {

    if (grupoActual == 12)
        return true;

    if (bomboActual == 4)
        return armarGruposRecursivo(grupoActual + 1, 0,
                                    usados1, usados2, usados3, usados4);

    Equipo** bombo = 0;
    bool* usados = 0;

    if (bomboActual == 0) { bombo = bombo1; usados = usados1; }
    else if (bomboActual == 1) { bombo = bombo2; usados = usados2; }
    else if (bomboActual == 2) { bombo = bombo3; usados = usados3; }
    else { bombo = bombo4; usados = usados4; }

    int base = grupoActual * 4;

    Equipo* grupoTemp[4];
    for (int i = 0; i < bomboActual; i++) {
        grupoTemp[i] = grupos[base + i];
    }

    for (int i = 0; i < 12; i++) {

        if (!usados[i]) {

            if (sePuedeAgregar(grupoTemp, bomboActual, bombo[i])) {

                grupos[base + bomboActual] = bombo[i];
                usados[i] = true;

                if (armarGruposRecursivo(grupoActual, bomboActual + 1,
                                         usados1, usados2, usados3, usados4))
                    return true;

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

    for (int i = 0; i < 48; i++)
        grupos[i] = 0;

    bool usados1[12] = {false};
    bool usados2[12] = {false};
    bool usados3[12] = {false};
    bool usados4[12] = {false};

    bool ok = armarGruposRecursivo(0, 0,
                                   usados1, usados2,
                                   usados3, usados4);

    if (!ok) {
        cout << "Error: no se pudieron generar grupos validos\n";
    }
}

// CREAR PARTIDOS
void Grupo::crearPartidos() {

    partidos = new Partido[72];
    totalPartidos = 0;

    int dia = 0;

    for (int g = 0; g < 12; g++) {

        int base = g * 4;

        Equipo* e1 = grupos[base + 0];
        Equipo* e2 = grupos[base + 1];
        Equipo* e3 = grupos[base + 2];
        Equipo* e4 = grupos[base + 3];

        Partido lista[6] = {
            Partido(e1, e2),
            Partido(e1, e3),
            Partido(e1, e4),
            Partido(e2, e3),
            Partido(e2, e4),
            Partido(e3, e4)
        };

        for (int i = 0; i < 6; i++) {

            string fecha = to_string(20 + dia) + "/06/2026";

            lista[i].configurar(
                fecha,
                "00:00",
                "anastasio",
                "jorge",
                "anibal",
                "pierluigi collina"
                );

            partidos[totalPartidos++] = lista[i];

            dia = (dia + 1) % 19;
        }
    }
}

// JUGAR DÍA
void Grupo::jugarDia(string fecha) {

    cout << "PARTIDOS DEL DIA" << endl;
    cout << "----------------" << endl;

    bool huboPartidos = false;

    for (int i = 0; i < totalPartidos; i++) {

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

// COMPARADOR TABLA
bool Grupo::vaAntes(Equipo* a, Equipo* b) {

    int ptsA = a->actual.ganados * 3 + a->actual.empatados;
    int ptsB = b->actual.ganados * 3 + b->actual.empatados;

    if (ptsA != ptsB) return ptsA > ptsB;

    int diffA = a->actual.golesF - a->actual.golesC;
    int diffB = b->actual.golesF - b->actual.golesC;

    if (diffA != diffB) return diffA > diffB;

    return a->actual.golesF > b->actual.golesF;
}

// ORDENAR GRUPO
void Grupo::ordenarGrupo(int inicio) {

    for (int i = inicio; i < inicio + 4; i++) {
        for (int j = i + 1; j < inicio + 4; j++) {

            if (!vaAntes(grupos[i], grupos[j])) {
                intercambiar(grupos[i], grupos[j]);
            }
        }
    }
}

// MOSTRAR GRUPOS
void Grupo::mostrarGrupos() {

    char letra = 'A';

    for (int i = 0; i < 12; i++) {

        int inicio = i * 4;

        ordenarGrupo(inicio);

        cout << "Grupo " << letra << endl;

        for (int j = 0; j < 4; j++) {

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
