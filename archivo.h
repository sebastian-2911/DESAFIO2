#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "equipo.h"
#include <string>

using namespace std;

int convertirEntero(const string& texto);

bool cargarEquiposDesdeCSV(const string& nombreArchivo,
                           Equipo equipos[],
                           int& cantidadEquipos,
                           int maxEquipos);
void guardarEquiposEnCSV(const string& nombreArchivo,
                         const Equipo equipos[],
                         int cantidadEquipos);

void guardarJugadoresEnCSV(const string& nombreArchivo,
                           const Equipo equipos[],
                           int cantidadEquipos);
#endif