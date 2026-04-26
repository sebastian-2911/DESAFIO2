#include "archivo.h"
#include <iostream>
#include <fstream>
#include "metricas.h"

using namespace std;

int convertirEntero(const string& texto) {
    int num = 0;
    int i = 0;

    while (i < (int)texto.length() && texto[i] == ' ') {
        Metricas::sumarIteracion();
        i++;
    }

    for (; i < (int)texto.length(); i++) {
        Metricas::sumarIteracion();
        if (texto[i] >= '0' && texto[i] <= '9') {
            num = num * 10 + (texto[i] - '0');
        }
        else {
            break;
        }
    }

    return num;
}

bool cargarEquiposDesdeCSV(const string& nombreArchivo,
                           Equipo equipos[],
                           int& cantidadEquipos,
                           int maxEquipos) {
    ifstream archivo(nombreArchivo.c_str());
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        cantidadEquipos = 0;
        return false;
    }

    cantidadEquipos = 0;

    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea) && cantidadEquipos < maxEquipos) {
        Metricas::sumarIteracion();
        if (linea.empty()) {
            continue;
        }

        string columnas[10];
        int indiceColumna = 0;
        int inicio = 0;
        int pos = 0;

        while ((pos = (int)linea.find(';', inicio)) != (int)string::npos && indiceColumna < 9) {
            Metricas::sumarIteracion();
            columnas[indiceColumna] = linea.substr(inicio, pos - inicio);
            indiceColumna++;
            inicio = pos + 1;
        }

        columnas[indiceColumna] = linea.substr(inicio);

        if (indiceColumna < 9) {
            cout << "Linea invalida: " << linea << endl;
            continue;
        }

        Equipo& e = equipos[cantidadEquipos];

        e.rankingFIFA = convertirEntero(columnas[0]);
        e.pais = columnas[1];
        e.tecnico = columnas[2];
        e.confederacion = columnas[4];

        e.historico.golesF = convertirEntero(columnas[5]);
        e.historico.golesC = convertirEntero(columnas[6]);
        e.historico.ganados = convertirEntero(columnas[7]);
        e.historico.empatados = convertirEntero(columnas[8]);
        e.historico.perdidos = convertirEntero(columnas[9]);

        e.reiniciarActual();
        e.inicializarJugadores();

        cantidadEquipos++;
    }

    archivo.close();

    if (cantidadEquipos == 0) {
        cout << "Archivo vacio o sin equipos validos." << endl;
        return false;
    }

    cout << "Equipos cargados: " << cantidadEquipos << endl;
    return true;
}
void guardarEquiposEnCSV(const string& nombreArchivo,
                         const Equipo equipos[],
                         int cantidadEquipos) {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << "RankingFIFA;Pais;Tecnico;Confederacion;GF_Historico_Total;GC_Historico_Total;Ganados_Historico_Total;Empatados_Historico_Total;Perdidos_Historico_Total\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();
        const Equipo& e = equipos[i];

        int golesFTotal = e.historico.golesF + e.actual.golesF;
        int golesCTotal = e.historico.golesC + e.actual.golesC;
        int ganadosTotal = e.historico.ganados + e.actual.ganados;
        int empatadosTotal = e.historico.empatados + e.actual.empatados;
        int perdidosTotal = e.historico.perdidos + e.actual.perdidos;

        archivo << e.rankingFIFA << ";"
                << e.pais << ";"
                << e.tecnico << ";"
                << e.confederacion << ";"
                << golesFTotal << ";"
                << golesCTotal << ";"
                << ganadosTotal << ";"
                << empatadosTotal << ";"
                << perdidosTotal << "\n";
    }

    archivo.close();
    cout << "Archivo generado: " << nombreArchivo << endl;
}
void guardarJugadoresEnCSV(const string& nombreArchivo,
                           const Equipo equipos[],
                           int cantidadEquipos) {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << "Equipo;Numero;Nombre;Apellido;Goles;Amarillas;Rojas;Minutos\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        Metricas::sumarIteracion();
        const Equipo& e = equipos[i];

        for (int j = 0; j < 26; j++) {
            Metricas::sumarIteracion();
            const Jugador& jug = e.jugadores[j];

            archivo << e.pais << ";"
                    << jug.numero << ";"
                    << jug.nombre << ";"
                    << jug.apellido << ";"
                    << jug.goles << ";"
                    << jug.amarillas << ";"
                    << jug.rojas << ";"
                    << jug.minutos << "\n";
        }
    }

    archivo.close();
    cout << "Archivo generado: " << nombreArchivo << endl;
}