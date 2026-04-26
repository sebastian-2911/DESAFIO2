#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "equipo.h"
#include "partido.h"
#include "clasificado.h"
#include <string>

using namespace std;

class Eliminatoria {
private:
    Clasificado primeros[12];
    Clasificado segundos[12];
    Clasificado terceros[12];

    Clasificado mejoresPrimeros[8];
    Clasificado otrosPrimeros[4];
    Clasificado mejoresSegundos[8];
    Clasificado peoresSegundos[4];
    Clasificado mejoresTerceros[8];

    Partido dieciseisavos[16];
    Partido octavos[8];
    Partido cuartos[4];
    Partido semifinales[2];
    Partido tercerPuesto[1];
    Partido finalPartido[1];

    int totalDieciseisavos;
    int totalOctavos;
    int totalCuartos;
    int totalSemifinales;
    int totalTercerPuesto;
    int totalFinal;

    int cantidadPrimeros;
    int cantidadSegundos;
    int cantidadTerceros;

    int puntosEquipo(Equipo* e);
    int diferenciaEquipo(Equipo* e);
    bool mejorQue(const Clasificado& a, const Clasificado& b);
    void intercambiar(Clasificado& a, Clasificado& b);
    void ordenarClasificados(Clasificado* arreglo, int n);
    void copiarGrupoOrdenado(Equipo* grupo[4], Clasificado salida[4], char letraGrupo);
    void armarClasificados(Equipo* gruposOrdenados[48]);
    bool mismoGrupo(const Clasificado& a, const Clasificado& b);

    bool emparejarPrimerosVsTerceros(int idxPrimero,
                                     bool usadosTerceros[],
                                     Clasificado primeros8[],
                                     Clasificado terceros8[],
                                     Partido partidosTemp[],
                                     int inicioPartidos);

    bool emparejarPrimerosVsPeoresSegundos(int idxPrimero,
                                           bool usadosSegundos[],
                                           Clasificado primeros4[],
                                           Clasificado segundos4[],
                                           Partido partidosTemp[],
                                           int inicioPartidos);

    bool emparejarSegundosEntreSi(int idx,
                                  bool usados[],
                                  Clasificado segundos8[],
                                  Partido partidosTemp[],
                                  int inicioPartidos);

    string construirFechaEliminatoria(int dia, int mes) const;

    Equipo* ganadorDe(Partido& p);
    Equipo* perdedorDe(Partido& p);
    void asegurarGanador(Partido& p, const string& fecha);

    void configurarPartido(Partido& p, const string& fecha);
    void mostrarRonda(const string& titulo, Partido* ronda, int cantidad);
    void jugarRonda(const string& titulo,
                    Partido* ronda,
                    int cantidad,
                    int diaBase,
                    int mes,
                    int partidosPorDia);
    void crearRondaDesdeAnterior(Partido* rondaAnterior,
                                 int cantidadNuevaRonda,
                                 Partido* nuevaRonda,
                                 int diaBase,
                                 int mes,
                                 int partidosPorDia);

public:
    Eliminatoria();

    void crearDesdeGrupos(Equipo* gruposOrdenados[48]);

    void mostrarClasificados();
    void mostrarLlaves();

    void jugarDieciseisavos();
    void crearOctavos();
    void jugarOctavos();
    void crearCuartos();
    void jugarCuartos();
    void crearSemifinales();
    void jugarSemifinales();
    void crearTercerPuestoYFinal();
    void jugarTercerPuesto();
    void jugarFinal();

    Partido* getDieciseisavos();
    Partido* getOctavos();
    Partido* getCuartos();
    Partido* getSemifinales();
    Partido* getTercerPuesto();
    Partido* getFinal();

    int getTotalDieciseisavos();
    int getTotalOctavos();
    int getTotalCuartos();
    int getTotalSemifinales();

    Eliminatoria(const Eliminatoria& otro);

    //sobrecarga
    Eliminatoria& operator=(const Eliminatoria& otro);
    bool operator==(const Eliminatoria& otro) const;
    bool operator>(const Eliminatoria& otro) const;
};

#endif
