#include "fase.h"
#include <iostream>
#include <fstream>
#include "metricas.h"

using namespace std;

Fase::Fase() {
    equiposTorneo = 0;
    cantidadEquipos = 0;
    diaActual = 0;
    dieciseisavosCreados = false;
    eliminatoriaJugada = false;
}

void Fase::iniciarFase(Equipo* equipos, int cantidad) {
    equiposTorneo = equipos;
    cantidadEquipos = cantidad;

    grupos.crearGrupos(equipos, cantidad);
    grupos.crearPartidos();

    diaActual = 0;
    dieciseisavosCreados = false;
    eliminatoriaJugada = false;
}

void Fase::iniciarCalendario() {
    diaActual = 0;
    dieciseisavosCreados = false;
    eliminatoriaJugada = false;
}

string Fase::construirFechaActual() const {
    int diaReal = 20 + diaActual;
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

void Fase::guardarCSVAutomatico() {
    ofstream equiposFile("equipos_actualizados.csv");
    ofstream jugadoresFile("jugadores_actualizados.csv");

    if (!equiposFile.is_open() || !jugadoresFile.is_open()) {
        cout << "Error al guardar CSV" << endl;
        return;
    }

    equiposFile << "Pais;GF;GC;Ganados;Empatados;Perdidos\n";
    jugadoresFile << "Equipo;Numero;Nombre;Apellido;Goles;Amarillas;Rojas;Minutos\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();
        Equipo& e = equiposTorneo[i];

        int gf = e.historico.golesF + e.actual.golesF;
        int gc = e.historico.golesC + e.actual.golesC;

        int g = e.historico.ganados + e.actual.ganados;
        int emp = e.historico.empatados + e.actual.empatados;
        int p = e.historico.perdidos + e.actual.perdidos;

        equiposFile << e.pais << ";" << gf << ";" << gc << ";"
                    << g << ";" << emp << ";" << p << "\n";

        for (int j = 0; j < 26; j++) {
            Metricas::sumarIteracion();
            Jugador& jug = e.jugadores[j];

            jugadoresFile << e.pais << ";"
                          << jug.numero << ";"
                          << jug.nombre << ";"
                          << jug.apellido << ";"
                          << jug.goles << ";"
                          << jug.amarillas << ";"
                          << jug.rojas << ";"
                          << jug.minutos << "\n";
        }
    }

    equiposFile.close();
    jugadoresFile.close();
}

bool Fase::crearDieciseisavos() {
    if (dieciseisavosCreados) {
        cout << "\nLos dieciseisavos ya fueron creados." << endl;
        return false;
    }

    if (!grupos.todosLosPartidosJugados()) {
        cout << "\nERROR: No se pueden crear los dieciseisavos." << endl;
        cout << "Debe jugar todos los partidos de la fase de grupos primero." << endl;
        return false;
    }

    Equipo* clasificados[48];
    grupos.obtenerGruposOrdenados(clasificados);
    eliminatoria.crearDesdeGrupos(clasificados);

    dieciseisavosCreados = true;

    cout << "\nDieciseisavos creados correctamente." << endl;
    return true;
}
void Fase::mostrarDieciseisavos() {
    if (!dieciseisavosCreados) {
        cout << "\nPrimero debe crearse la fase eliminatoria." << endl;
        return;
    }

    eliminatoria.mostrarClasificados();
    eliminatoria.mostrarLlaves();
}

void Fase::jugarDieciseisavos() {
    if (!dieciseisavosCreados) {
        cout << "\nPrimero debe crearse la fase eliminatoria." << endl;
        return;
    }

    eliminatoria.jugarDieciseisavos();
}

void Fase::jugarTodaEliminatoria() {
    if (!dieciseisavosCreados) {
        cout << "\nPrimero cree la eliminatoria." << endl;
        return;
    }

    if (eliminatoriaJugada) {
        mostrarInformeFinal();
        return;
    }

    eliminatoria.jugarDieciseisavos();
    eliminatoria.jugarOctavos();
    eliminatoria.jugarCuartos();
    eliminatoria.jugarSemifinales();
    eliminatoria.jugarTercerPuesto();
    eliminatoria.jugarFinal();

    eliminatoriaJugada = true;

    guardarCSVAutomatico();
    mostrarInformeFinal();
}

void Fase::mostrarGrupos() {
    cout << "\n===== TABLA DE GRUPOS =====" << endl;
    cout << "===========================" << endl << endl;

    grupos.mostrarGrupos();
}

void Fase::terminarFaseDeGrupos() {
    cout << "\n===== FASE DE GRUPOS TERMINADA =====" << endl;
    cout << "====================================" << endl;

    crearDieciseisavos();

    cout << "\nYa puede usar la opcion 6 para mostrar los dieciseisavos." << endl;
    cout << "Luego use la opcion 7 para jugar la eliminatoria." << endl;
}

void Fase::avanzarDia() {
    if (diaActual >= 19) {
        terminarFaseDeGrupos();
        return;
    }

    string fecha = construirFechaActual();

    cout << "\n=================================" << endl;
    cout << "DIA " << diaActual + 1 << endl;
    cout << "=================================" << endl;
    cout << "Fecha: " << fecha << endl << endl;

    grupos.jugarDia(fecha);

    guardarCSVAutomatico();

    diaActual++;
}

Jugador* Fase::maximoGoleadorDeEquipo(Equipo* equipo) {
    if (!equipo) {
        return 0;
    }

    Jugador* mejor = &equipo->jugadores[0];

    for (int i = 1; i < 26; i++) {
        Metricas::sumarIteracion();

        if (equipo->jugadores[i].goles > mejor->goles) {
            mejor = &equipo->jugadores[i];
        }
    }

    return mejor;
}
void Fase::insertarTopJugador(Jugador* candidato, Jugador* top[3]) {
    if (!candidato) {
        return;
    }

    for (int i = 0; i < 3; i++) {
        Metricas::sumarIteracion();
        if (top[i] == candidato) {
            return;
        }
    }

    for (int i = 0; i < 3; i++) {
        Metricas::sumarIteracion();
        if (top[i] == 0 || candidato->goles > top[i]->goles) {
            for (int j = 2; j > i; j--) {
                Metricas::sumarIteracion();
                top[j] = top[j - 1];
            }
            top[i] = candidato;
            return;
        }
    }
}

void Fase::contarConfederaciones(Partido* ronda, int cantidadPartidos,
                                 string& mejorConf, int& mejorCantidad) {
    string nombres[6] = {"UEFA", "CONMEBOL", "CAF", "AFC", "Concacaf", "OFC"};
    int conteo[6] = {0};

    for (int i = 0; i < cantidadPartidos; i++) {
        Metricas::sumarIteracion();
        Equipo* local = ronda[i].getEquipoLocal();
        Equipo* visitante = ronda[i].getEquipoVisitante();

        if (local) {
            for (int j = 0; j < 6; j++) {
                Metricas::sumarIteracion();
                if (local->confederacion == nombres[j]) {
                    conteo[j]++;
                    break;
                }
            }
        }

        if (visitante) {
            for (int j = 0; j < 6; j++) {
                Metricas::sumarIteracion();
                if (visitante->confederacion == nombres[j]) {
                    conteo[j]++;
                    break;
                }
            }
        }
    }

    mejorConf = nombres[0];
    mejorCantidad = conteo[0];

    for (int i = 1; i < 6; i++) {
        Metricas::sumarIteracion();
        if (conteo[i] > mejorCantidad) {
            mejorCantidad = conteo[i];
            mejorConf = nombres[i];
        }
    }
}

void Fase::mostrarTop4Mundial() {
    Partido* finalPtr = eliminatoria.getFinal();
    Partido* tercerPtr = eliminatoria.getTercerPuesto();

    if (!finalPtr || !tercerPtr) {
        return;
    }

    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercero;
    Equipo* cuarto;

    if (finalPtr[0].getGolesLocal() > finalPtr[0].getGolesVisitante()) {
        campeon = finalPtr[0].getEquipoLocal();
        subcampeon = finalPtr[0].getEquipoVisitante();
    } else {
        campeon = finalPtr[0].getEquipoVisitante();
        subcampeon = finalPtr[0].getEquipoLocal();
    }

    if (tercerPtr[0].getGolesLocal() > tercerPtr[0].getGolesVisitante()) {
        tercero = tercerPtr[0].getEquipoLocal();
        cuarto = tercerPtr[0].getEquipoVisitante();
    } else {
        tercero = tercerPtr[0].getEquipoVisitante();
        cuarto = tercerPtr[0].getEquipoLocal();
    }

    cout << "1. " << campeon->pais << endl;
    cout << "2. " << subcampeon->pais << endl;
    cout << "3. " << tercero->pais << endl;
    cout << "4. " << cuarto->pais << endl;
}

void Fase::mostrarGoleadorCampeon() {
    Partido* finalPtr = eliminatoria.getFinal();

    if (!finalPtr) {
        return;
    }

    Equipo* campeon;

    if (finalPtr[0].getGolesLocal() > finalPtr[0].getGolesVisitante()) {
        campeon = finalPtr[0].getEquipoLocal();
    } else {
        campeon = finalPtr[0].getEquipoVisitante();
    }

    Jugador* goleador = maximoGoleadorDeEquipo(campeon);

    cout << "Equipo campeon: " << campeon->pais << endl;

    if (goleador) {
        cout << "Maximo goleador del campeon: "
             << goleador->nombre << " " << goleador->apellido
             << " | #" << goleador->numero
             << " | Goles: " << goleador->goles << endl;
    }
}

void Fase::mostrarTop3Goleadores() {
    Jugador* top[3] = {0, 0, 0};
    Equipo* equipoTop[3] = {0, 0, 0};

    for (int i = 0; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();

        for (int j = 0; j < 26; j++) {
            Metricas::sumarIteracion();

            Jugador* candidato = &equiposTorneo[i].jugadores[j];

            for (int k = 0; k < 3; k++) {
                Metricas::sumarIteracion();

                if (top[k] == 0 || candidato->goles > top[k]->goles) {
                    for (int m = 2; m > k; m--) {
                        Metricas::sumarIteracion();
                        top[m] = top[m - 1];
                        equipoTop[m] = equipoTop[m - 1];
                    }

                    top[k] = candidato;
                    equipoTop[k] = &equiposTorneo[i];
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        Metricas::sumarIteracion();

        if (top[i]) {
            cout << (i + 1) << ". "
                 << top[i]->nombre << " " << top[i]->apellido
                 << " | #" << top[i]->numero
                 << " | " << equipoTop[i]->pais
                 << " | Goles: " << top[i]->goles
                 << endl;
        }
    }
}
void Fase::mostrarEquipoMasGoleadorHistorico() {
    if (!equiposTorneo || cantidadEquipos <= 0) {
        return;
    }

    Equipo* mejor = &equiposTorneo[0];
    int mejorTotal = mejor->historico.golesF + mejor->actual.golesF;

    for (int i = 1; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();
        int total = equiposTorneo[i].historico.golesF + equiposTorneo[i].actual.golesF;

        if (total > mejorTotal) {
            mejorTotal = total;
            mejor = &equiposTorneo[i];
        }
    }

    cout << mejor->pais << " | Total goles: " << mejorTotal << endl;
}

void Fase::mostrarConfederacionConMasPresencia() {
    string confR16, confR8, confR4;
    int cantR16 = 0;
    int cantR8 = 0;
    int cantR4 = 0;

    contarConfederaciones(eliminatoria.getDieciseisavos(),
                          eliminatoria.getTotalDieciseisavos(),
                          confR16, cantR16);

    contarConfederaciones(eliminatoria.getCuartos(),
                          eliminatoria.getTotalCuartos(),
                          confR8, cantR8);

    contarConfederaciones(eliminatoria.getSemifinales(),
                          eliminatoria.getTotalSemifinales(),
                          confR4, cantR4);

    cout << "R16: " << confR16 << " | Equipos: " << cantR16 << endl;
    cout << "R8: " << confR8 << " | Equipos: " << cantR8 << endl;
    cout << "R4: " << confR4 << " | Equipos: " << cantR4 << endl;
}

void Fase::mostrarInformeFinal() {
    if (!eliminatoriaJugada) {
        cout << "\nPrimero debe jugarse toda la eliminatoria." << endl;
        return;
    }

    cout << "\n==========================================" << endl;
    cout << "           INFORME FINAL DEL TORNEO       " << endl;
    cout << "==========================================" << endl;

    cout << "\n- El ranking de los 4 primeros puestos del mundial:" << endl;
    mostrarTop4Mundial();

    cout << "\n- El maximo goleador del equipo campeon del mundo:" << endl;
    mostrarGoleadorCampeon();

    cout << "\n- Los tres mayores goleadores de toda la copa mundial:" << endl;
    mostrarTop3Goleadores();

    cout << "\n- El equipo con mas cantidad de goles historicos:" << endl;
    mostrarEquipoMasGoleadorHistorico();

    cout << "\n- La confederacion con mayor presencia en R16, R8 y R4:" << endl;
    mostrarConfederacionConMasPresencia();

    cout << endl;
}
void Fase::mostrarCalendario() {
    grupos.mostrarCalendario();
}

bool Fase::hayDieciseisavosCreados() const {
    return dieciseisavosCreados;
}

bool Fase::hayEliminatoriaJugada() const {
    return eliminatoriaJugada;
}

int Fase::getDiaActual() const {
    return diaActual;
}

Fase::Fase(const Fase& otro)
{
    *this = otro;
}

//sobrecarga
Fase& Fase::operator=(const Fase& otro) {
    if (this != &otro) {
        grupos = otro.grupos;
        eliminatoria = otro.eliminatoria;

        equiposTorneo = otro.equiposTorneo;
        cantidadEquipos = otro.cantidadEquipos;

        diaActual = otro.diaActual;
        dieciseisavosCreados = otro.dieciseisavosCreados;
        eliminatoriaJugada = otro.eliminatoriaJugada;
    }

    return *this;
}

bool Fase::operator==(const Fase& otro) const {
    return equiposTorneo == otro.equiposTorneo &&
           cantidadEquipos == otro.cantidadEquipos &&
           diaActual == otro.diaActual;
}

bool Fase::operator>(const Fase& otro) const {
    return diaActual > otro.diaActual;
}