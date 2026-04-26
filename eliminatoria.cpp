#include "eliminatoria.h"
#include <iostream>
#include <cstdlib>
#include "metricas.h"

using namespace std;

Eliminatoria::Eliminatoria() {
    totalDieciseisavos = 0;
    totalOctavos = 0;
    totalCuartos = 0;
    totalSemifinales = 0;
    totalTercerPuesto = 0;
    totalFinal = 0;

    cantidadPrimeros = 0;
    cantidadSegundos = 0;
    cantidadTerceros = 0;
}

int Eliminatoria::puntosEquipo(Equipo* e) {
    return e->actual.ganados * 3 + e->actual.empatados;
}

int Eliminatoria::diferenciaEquipo(Equipo* e) {
    return e->actual.golesF - e->actual.golesC;
}

bool Eliminatoria::mejorQue(const Clasificado& a, const Clasificado& b) {
    if (a.puntos != b.puntos) return a.puntos > b.puntos;
    if (a.diferencia != b.diferencia) return a.diferencia > b.diferencia;
    if (a.golesFavor != b.golesFavor) return a.golesFavor > b.golesFavor;

    return (rand() % 2) == 0;
}

void Eliminatoria::intercambiar(Clasificado& a, Clasificado& b) {
    Clasificado temp = a;
    a = b;
    b = temp;
}

void Eliminatoria::ordenarClasificados(Clasificado* arreglo, int n) {
    for (int i = 0; i < n; i++) {
        Metricas::sumarIteracion();
        for (int j = i + 1; j < n; j++) {
            Metricas::sumarIteracion();
            if (!mejorQue(arreglo[i], arreglo[j])) {
                intercambiar(arreglo[i], arreglo[j]);
            }
        }
    }
}

void Eliminatoria::copiarGrupoOrdenado(Equipo* grupo[4], Clasificado salida[4], char letraGrupo) {
    for (int i = 0; i < 4; i++) {
        Metricas::sumarIteracion();
        salida[i].equipo = grupo[i];
        salida[i].grupo = letraGrupo;
        salida[i].posicion = i + 1;
        salida[i].puntos = puntosEquipo(grupo[i]);
        salida[i].diferencia = diferenciaEquipo(grupo[i]);
        salida[i].golesFavor = grupo[i]->actual.golesF;
    }

    for (int i = 0; i < 4; i++) {
        Metricas::sumarIteracion();
        for (int j = i + 1; j < 4; j++) {
            Metricas::sumarIteracion();
            if (!mejorQue(salida[i], salida[j])) {
                intercambiar(salida[i], salida[j]);
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        Metricas::sumarIteracion();
        salida[i].posicion = i + 1;
    }
}

void Eliminatoria::armarClasificados(Equipo* gruposOrdenados[48]) {
    cantidadPrimeros = 0;
    cantidadSegundos = 0;
    cantidadTerceros = 0;

    for (int g = 0; g < 12; g++) {
        Metricas::sumarIteracion();
        Equipo* grupoTemp[4];
        Clasificado ordenados[4];
        int base = g * 4;
        char letra = 'A' + g;

        for (int i = 0; i < 4; i++) {
            Metricas::sumarIteracion();
            grupoTemp[i] = gruposOrdenados[base + i];
        }

        copiarGrupoOrdenado(grupoTemp, ordenados, letra);

        primeros[cantidadPrimeros++] = ordenados[0];
        segundos[cantidadSegundos++] = ordenados[1];
        terceros[cantidadTerceros++] = ordenados[2];
    }

    ordenarClasificados(primeros, 12);
    ordenarClasificados(segundos, 12);
    ordenarClasificados(terceros, 12);

    for (int i = 0; i < 8; i++) {
        Metricas::sumarIteracion();
        mejoresPrimeros[i] = primeros[i];
        mejoresTerceros[i] = terceros[i];
        mejoresSegundos[i] = segundos[i];
    }

    for (int i = 0; i < 4; i++) {
        Metricas::sumarIteracion();
        otrosPrimeros[i] = primeros[8 + i];
        peoresSegundos[i] = segundos[8 + i];
    }
}

bool Eliminatoria::mismoGrupo(const Clasificado& a, const Clasificado& b) {
    return a.grupo == b.grupo;
}

bool Eliminatoria::emparejarPrimerosVsTerceros(int idxPrimero,
                                               bool usadosTerceros[],
                                               Clasificado primeros8[],
                                               Clasificado terceros8[],
                                               Partido partidosTemp[],
                                               int inicioPartidos) {
    if (idxPrimero == 8) return true;

    for (int i = 0; i < 8; i++) {
        Metricas::sumarIteracion();
        if (!usadosTerceros[i] && !mismoGrupo(primeros8[idxPrimero], terceros8[i])) {
            usadosTerceros[i] = true;
            partidosTemp[inicioPartidos + idxPrimero] =
                Partido(primeros8[idxPrimero].equipo, terceros8[i].equipo);

            if (emparejarPrimerosVsTerceros(idxPrimero + 1, usadosTerceros,
                                            primeros8, terceros8, partidosTemp, inicioPartidos)) {
                return true;
            }

            usadosTerceros[i] = false;
        }
    }

    return false;
}

bool Eliminatoria::emparejarPrimerosVsPeoresSegundos(int idxPrimero,
                                                     bool usadosSegundos[],
                                                     Clasificado primeros4[],
                                                     Clasificado segundos4[],
                                                     Partido partidosTemp[],
                                                     int inicioPartidos) {
    if (idxPrimero == 4) return true;

    for (int i = 0; i < 4; i++) {
        Metricas::sumarIteracion();
        if (!usadosSegundos[i] && !mismoGrupo(primeros4[idxPrimero], segundos4[i])) {
            usadosSegundos[i] = true;
            partidosTemp[inicioPartidos + idxPrimero] =
                Partido(primeros4[idxPrimero].equipo, segundos4[i].equipo);

            if (emparejarPrimerosVsPeoresSegundos(idxPrimero + 1, usadosSegundos,
                                                  primeros4, segundos4, partidosTemp, inicioPartidos)) {
                return true;
            }

            usadosSegundos[i] = false;
        }
    }

    return false;
}

bool Eliminatoria::emparejarSegundosEntreSi(int idx,
                                            bool usados[],
                                            Clasificado segundos8[],
                                            Partido partidosTemp[],
                                            int inicioPartidos) {
    if (idx == 8) return true;

    if (usados[idx]) {
        return emparejarSegundosEntreSi(idx + 1, usados, segundos8, partidosTemp, inicioPartidos);
    }

    usados[idx] = true;

    for (int j = idx + 1; j < 8; j++) {
        Metricas::sumarIteracion();
        if (!usados[j] && !mismoGrupo(segundos8[idx], segundos8[j])) {
            usados[j] = true;

            int realIdx = inicioPartidos;
            while (realIdx < inicioPartidos + 4 &&
                   partidosTemp[realIdx].getEquipoLocal() != 0) {
                Metricas::sumarIteracion();
                realIdx++;
            }

            partidosTemp[realIdx] = Partido(segundos8[idx].equipo, segundos8[j].equipo);

            if (emparejarSegundosEntreSi(idx + 1, usados, segundos8, partidosTemp, inicioPartidos)) {
                return true;
            }

            partidosTemp[realIdx] = Partido();
            usados[j] = false;
        }
    }

    usados[idx] = false;
    return false;
}

string Eliminatoria::construirFechaEliminatoria(int dia, int mes) const {
    string fecha = "";

    if (dia < 10) {
        fecha += "0";
    }
    fecha += to_string(dia);
    fecha += "/";

    if (mes < 10) {
        fecha += "0";
    }
    fecha += to_string(mes);
    fecha += "/2026";

    return fecha;
}

void Eliminatoria::configurarPartido(Partido& p, const string& fecha) {
    p.configurar(
        fecha,
        "00:00",
        "nombreSede",
        "codArbitro1",
        "codArbitro2",
        "codArbitro3"
        );
}

void Eliminatoria::mostrarRonda(const string& titulo, Partido* ronda, int cantidad) {
    cout << "\n===== " << titulo << " =====\n";

    if (titulo == "DIECISEISAVOS") {
        cout << "-------------------------\n";
    }
    else if (titulo == "OCTAVOS") {
        cout << "-------------------\n";
    }
    else if (titulo == "CUARTOS") {
        cout << "-------------------\n";
    }
    else if (titulo == "SEMIFINALES") {
        cout << "-----------------------\n";
    }
    else if (titulo == "TERCER PUESTO") {
        cout << "-------------------------\n";
    }
    else if (titulo == "FINAL") {
        cout << "-----------------\n";
    }
    else {
        cout << "-----------------------------\n";
    }

    for (int i = 0; i < cantidad; i++) {
        Metricas::sumarIteracion();
        if (cantidad > 1) {
            cout << "Partido " << i + 1 << ": ";
        }
        ronda[i].mostrar();
    }

    cout << endl;
}

void Eliminatoria::jugarRonda(const string& titulo,
                              Partido* ronda,
                              int cantidad,
                              int diaBase,
                              int mes,
                              int partidosPorDia) {
    cout << "\n===== " << titulo << " =====\n";
    cout << "------------------------------------\n";

    for (int i = 0; i < cantidad; i++) {
        Metricas::sumarIteracion();
        int dia = diaBase + (i / partidosPorDia);
        string fecha = construirFechaEliminatoria(dia, mes);

        asegurarGanador(ronda[i], fecha);
        ronda[i].mostrarDetalle();
    }

    cout << endl;
}

void Eliminatoria::crearRondaDesdeAnterior(Partido* rondaAnterior,
                                           int cantidadNuevaRonda,
                                           Partido* nuevaRonda,
                                           int diaBase,
                                           int mes,
                                           int partidosPorDia) {
    for (int i = 0; i < cantidadNuevaRonda; i++) {
        Metricas::sumarIteracion();
        Equipo* a = ganadorDe(rondaAnterior[i * 2]);
        Equipo* b = ganadorDe(rondaAnterior[i * 2 + 1]);

        nuevaRonda[i] = Partido(a, b);

        int dia = diaBase + (i / partidosPorDia);
        string fecha = construirFechaEliminatoria(dia, mes);

        configurarPartido(nuevaRonda[i], fecha);
    }
}

void Eliminatoria::crearDesdeGrupos(Equipo* gruposOrdenados[48]) {
    armarClasificados(gruposOrdenados);

    for (int i = 0; i < 16; i++) {
        Metricas::sumarIteracion();
        dieciseisavos[i] = Partido();
    }

    bool usadosTerceros[8] = {false};
    bool usadosPeoresSegundos[4] = {false};
    bool usadosMejoresSegundos[8] = {false};

    bool ok1 = emparejarPrimerosVsTerceros(0, usadosTerceros,
                                           mejoresPrimeros, mejoresTerceros,
                                           dieciseisavos, 0);

    bool ok2 = emparejarPrimerosVsPeoresSegundos(0, usadosPeoresSegundos,
                                                 otrosPrimeros, peoresSegundos,
                                                 dieciseisavos, 8);

    for (int i = 12; i < 16; i++) {
        Metricas::sumarIteracion();
        dieciseisavos[i] = Partido();
    }

    bool ok3 = emparejarSegundosEntreSi(0, usadosMejoresSegundos,
                                        mejoresSegundos, dieciseisavos, 12);

    if (!ok1 || !ok2 || !ok3) {
        cout << "No fue posible armar las llaves de dieciseisavos cumpliendo restricciones." << endl;
        totalDieciseisavos = 0;
        return;
    }

    for (int i = 0; i < 16; i++) {
        Metricas::sumarIteracion();
        string fecha = construirFechaEliminatoria(10 + (i / 4), 7);
        configurarPartido(dieciseisavos[i], fecha);
    }

    totalDieciseisavos = 16;
    totalOctavos = 0;
    totalCuartos = 0;
    totalSemifinales = 0;
    totalTercerPuesto = 0;
    totalFinal = 0;
}

void Eliminatoria::mostrarClasificados() {
    cout << "\n===== CLASIFICADOS A DIECISEISAVOS =====\n";

    cout << "\nPRIMEROS DE GRUPO\n";
    cout << "-----------------\n";
    for (int i = 0; i < 12; i++) {
        Metricas::sumarIteracion();
        cout << primeros[i].equipo->pais
             << " | Grupo " << primeros[i].grupo
             << " | Pts: " << primeros[i].puntos
             << " | DG: " << primeros[i].diferencia
             << " | GF: " << primeros[i].golesFavor << endl;
    }

    cout << "\nSEGUNDOS DE GRUPO\n";
    cout << "-----------------\n";
    for (int i = 0; i < 12; i++) {
        Metricas::sumarIteracion();
        cout << segundos[i].equipo->pais
             << " | Grupo " << segundos[i].grupo
             << " | Pts: " << segundos[i].puntos
             << " | DG: " << segundos[i].diferencia
             << " | GF: " << segundos[i].golesFavor << endl;
    }

    cout << "\nMEJORES 8 TERCEROS\n";
    cout << "------------------\n";
    for (int i = 0; i < 8; i++) {
        Metricas::sumarIteracion();
        cout << mejoresTerceros[i].equipo->pais
             << " | Grupo " << mejoresTerceros[i].grupo
             << " | Pts: " << mejoresTerceros[i].puntos
             << " | DG: " << mejoresTerceros[i].diferencia
             << " | GF: " << mejoresTerceros[i].golesFavor << endl;
    }

    cout << endl;
}

void Eliminatoria::mostrarLlaves() {
    mostrarRonda("DIECISEISAVOS", dieciseisavos, totalDieciseisavos);

    if (totalOctavos > 0) {
        mostrarRonda("OCTAVOS", octavos, totalOctavos);
    }

    if (totalCuartos > 0) {
        mostrarRonda("CUARTOS", cuartos, totalCuartos);
    }

    if (totalSemifinales > 0) {
        mostrarRonda("SEMIFINALES", semifinales, totalSemifinales);
    }

    if (totalTercerPuesto > 0) {
        mostrarRonda("TERCER PUESTO", tercerPuesto, totalTercerPuesto);
    }

    if (totalFinal > 0) {
        mostrarRonda("FINAL", finalPartido, totalFinal);
    }
}

Equipo* Eliminatoria::ganadorDe(Partido& p) {
    if (p.getGolesLocal() > p.getGolesVisitante()) {
        return p.getEquipoLocal();
    }
    return p.getEquipoVisitante();
}

Equipo* Eliminatoria::perdedorDe(Partido& p) {
    if (p.getGolesLocal() > p.getGolesVisitante()) {
        return p.getEquipoVisitante();
    }
    return p.getEquipoLocal();
}

void Eliminatoria::asegurarGanador(Partido& p, const string& fecha) {
    p.jugar();

    if (p.getGolesLocal() == p.getGolesVisitante()) {
        p.prorroga();
    }
}
void Eliminatoria::jugarDieciseisavos() {
    if (totalDieciseisavos == 0) {
        cout << "\nPrimero debe crearse la eliminatoria." << endl;
        return;
    }

    jugarRonda("RESULTADOS DIECISEISAVOS", dieciseisavos, totalDieciseisavos, 10, 7, 4);
    crearOctavos();
}

void Eliminatoria::crearOctavos() {
    crearRondaDesdeAnterior(dieciseisavos, 8, octavos, 14, 7, 4);
    totalOctavos = 8;
}

void Eliminatoria::jugarOctavos() {
    if (totalOctavos == 0) {
        cout << "\nPrimero debe jugarse dieciseisavos." << endl;
        return;
    }

    jugarRonda("RESULTADOS OCTAVOS", octavos, totalOctavos, 14, 7, 4);
    crearCuartos();
}

void Eliminatoria::crearCuartos() {
    crearRondaDesdeAnterior(octavos, 4, cuartos, 16, 7, 1);
    totalCuartos = 4;
}

void Eliminatoria::jugarCuartos() {
    if (totalCuartos == 0) {
        cout << "\nPrimero debe jugarse octavos." << endl;
        return;
    }

    jugarRonda("RESULTADOS CUARTOS", cuartos, totalCuartos, 16, 7, 1);
    crearSemifinales();
}

void Eliminatoria::crearSemifinales() {
    crearRondaDesdeAnterior(cuartos, 2, semifinales, 20, 7, 1);
    totalSemifinales = 2;
}

void Eliminatoria::jugarSemifinales() {
    if (totalSemifinales == 0) {
        cout << "\nPrimero debe jugarse cuartos." << endl;
        return;
    }

    jugarRonda("RESULTADOS SEMIFINALES", semifinales, totalSemifinales, 20, 7, 1);
    crearTercerPuestoYFinal();
}

void Eliminatoria::crearTercerPuestoYFinal() {
    Equipo* ganador1 = ganadorDe(semifinales[0]);
    Equipo* ganador2 = ganadorDe(semifinales[1]);
    Equipo* perdedor1 = perdedorDe(semifinales[0]);
    Equipo* perdedor2 = perdedorDe(semifinales[1]);

    finalPartido[0] = Partido(ganador1, ganador2);
    configurarPartido(finalPartido[0], construirFechaEliminatoria(24, 7));

    tercerPuesto[0] = Partido(perdedor1, perdedor2);
    configurarPartido(tercerPuesto[0], construirFechaEliminatoria(23, 7));

    totalTercerPuesto = 1;
    totalFinal = 1;
}

void Eliminatoria::jugarTercerPuesto() {
    if (totalTercerPuesto == 0) {
        cout << "\nPrimero deben jugarse semifinales." << endl;
        return;
    }

    jugarRonda("RESULTADO TERCER PUESTO", tercerPuesto, 1, 23, 7, 1);
}

void Eliminatoria::jugarFinal() {
    if (totalFinal == 0) {
        cout << "\nPrimero deben jugarse semifinales." << endl;
        return;
    }

    jugarRonda("RESULTADO FINAL", finalPartido, 1, 24, 7, 1);

    cout << "\n===== CAMPEON =====\n";
    cout << ganadorDe(finalPartido[0])->pais << endl << endl;
}

Partido* Eliminatoria::getDieciseisavos() {
    return dieciseisavos;
}

Partido* Eliminatoria::getOctavos() {
    return octavos;
}

Partido* Eliminatoria::getCuartos() {
    return cuartos;
}

Partido* Eliminatoria::getSemifinales() {
    return semifinales;
}

Partido* Eliminatoria::getTercerPuesto() {
    return tercerPuesto;
}

Partido* Eliminatoria::getFinal() {
    return finalPartido;
}

int Eliminatoria::getTotalDieciseisavos() {
    return totalDieciseisavos;
}

int Eliminatoria::getTotalOctavos() {
    return totalOctavos;
}

int Eliminatoria::getTotalCuartos() {
    return totalCuartos;
}

int Eliminatoria::getTotalSemifinales() {
    return totalSemifinales;
}

Eliminatoria::Eliminatoria(const Eliminatoria& otro)
{
    *this = otro;
}
//sobrecarga
Eliminatoria& Eliminatoria::operator=(const Eliminatoria& otro) {
    if (this != &otro) {
        for (int i = 0; i < 12; i++) {
            primeros[i] = otro.primeros[i];
            segundos[i] = otro.segundos[i];
            terceros[i] = otro.terceros[i];
        }

        for (int i = 0; i < 8; i++) {
            mejoresPrimeros[i] = otro.mejoresPrimeros[i];
            mejoresSegundos[i] = otro.mejoresSegundos[i];
            mejoresTerceros[i] = otro.mejoresTerceros[i];
        }

        for (int i = 0; i < 4; i++) {
            otrosPrimeros[i] = otro.otrosPrimeros[i];
            peoresSegundos[i] = otro.peoresSegundos[i];
        }

        for (int i = 0; i < 16; i++) {
            dieciseisavos[i] = otro.dieciseisavos[i];
        }

        for (int i = 0; i < 8; i++) {
            octavos[i] = otro.octavos[i];
        }

        for (int i = 0; i < 4; i++) {
            cuartos[i] = otro.cuartos[i];
        }

        for (int i = 0; i < 2; i++) {
            semifinales[i] = otro.semifinales[i];
        }

        tercerPuesto[0] = otro.tercerPuesto[0];
        finalPartido[0] = otro.finalPartido[0];

        totalDieciseisavos = otro.totalDieciseisavos;
        totalOctavos = otro.totalOctavos;
        totalCuartos = otro.totalCuartos;
        totalSemifinales = otro.totalSemifinales;
        totalTercerPuesto = otro.totalTercerPuesto;
        totalFinal = otro.totalFinal;

        cantidadPrimeros = otro.cantidadPrimeros;
        cantidadSegundos = otro.cantidadSegundos;
        cantidadTerceros = otro.cantidadTerceros;
    }

    return *this;
}

bool Eliminatoria::operator==(const Eliminatoria& otro) const {
    return totalDieciseisavos == otro.totalDieciseisavos &&
           totalOctavos == otro.totalOctavos &&
           totalCuartos == otro.totalCuartos &&
           totalSemifinales == otro.totalSemifinales &&
           totalTercerPuesto == otro.totalTercerPuesto &&
           totalFinal == otro.totalFinal;
}

bool Eliminatoria::operator>(const Eliminatoria& otro) const {
    int totalPartidos = totalDieciseisavos + totalOctavos + totalCuartos +
                        totalSemifinales + totalTercerPuesto + totalFinal;

    int totalPartidosOtro = otro.totalDieciseisavos + otro.totalOctavos +
                            otro.totalCuartos + otro.totalSemifinales +
                            otro.totalTercerPuesto + otro.totalFinal;

    return totalPartidos > totalPartidosOtro;
}