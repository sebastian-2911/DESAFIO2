#ifndef FASE_H
#define FASE_H

#include "grupo.h"
#include "eliminatoria.h"
#include "equipo.h"
#include "jugador.h"
#include <string>

using namespace std;

class Fase {
private:
    Grupo grupos;
    Eliminatoria eliminatoria;

    Equipo* equiposTorneo;
    int cantidadEquipos;

    int diaActual;
    bool dieciseisavosCreados;
    bool eliminatoriaJugada;

    void terminarFaseDeGrupos();
    void guardarCSVAutomatico();

    Jugador* maximoGoleadorDeEquipo(Equipo* equipo);
    void insertarTopJugador(Jugador* candidato, Jugador* top[3]);
    void contarConfederaciones(Partido* ronda, int cantidadPartidos,
                               string& mejorConf, int& mejorCantidad);

    void mostrarTop4Mundial();
    void mostrarGoleadorCampeon();
    void mostrarTop3Goleadores();
    void mostrarEquipoMasGoleadorHistorico();
    void mostrarConfederacionConMasPresencia();

public:
    Fase();

    void iniciarFase(Equipo* equipos, int cantidad);
    void iniciarCalendario();

    string construirFechaActual() const;

    bool crearDieciseisavos();
    void mostrarDieciseisavos();
    void jugarDieciseisavos();
    void jugarTodaEliminatoria();

    void mostrarCalendario();

    void mostrarGrupos();
    void avanzarDia();

    void mostrarInformeFinal();

    Fase(const Fase& otro);

    //sobrecarga
    Fase& operator=(const Fase& otro);
    bool operator==(const Fase& otro) const;
    bool operator>(const Fase& otro) const;
};

#endif
