#include "torneo.h"
#include <iostream>
#include <fstream>

using namespace std;

//  convierte string a int (sin stoi)
int convertirEntero(string texto) {
    int num = 0;

    for (int i = 0; i < texto.length(); i++) {
        if (texto[i] >= '0' && texto[i] <= '9') {
            num = num * 10 + (texto[i] - '0');
        } else {
            break;
        }
    }

    return num;
}

// Constructor
Torneo::Torneo() {
    cantidad = 0;
    equipos = new Equipo[48]; // memoria dinámica
}

//  Destructor
Torneo::~Torneo() {
    delete[] equipos;
}

//  Cargar equipos desde CSV
void Torneo::cargarEquipos(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;

    // Saltar encabezados
    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea)) {

        Equipo e;

        string ranking, pais, tecnico, federacion, confederacion;
        string golesF_str, golesC_str, ganados_str, empatados_str, perdidos_str;

        int inicio = 0;
        int pos;


        pos = linea.find(";", inicio);
        ranking = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        pais = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        tecnico = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        federacion = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        confederacion = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        golesF_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        golesC_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        ganados_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        pos = linea.find(";", inicio);
        empatados_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        perdidos_str = linea.substr(inicio);

        // convertir a int
        e.golesF = convertirEntero(golesF_str);
        e.golesC = convertirEntero(golesC_str);
        e.ganados = convertirEntero(ganados_str);
        e.empatados = convertirEntero(empatados_str);
        e.perdidos = convertirEntero(perdidos_str);

        // guardar datos
        e.pais = pais;
        e.tecnico = tecnico;

        //  guardar en arreglo
        if (cantidad < 48) {
            equipos[cantidad] = e;
            cantidad++;
        }
    }

    archivo.close();
}

//  Mostrar equipos
void Torneo::mostrarEquipos() {
    for (int i = 0; i < cantidad; i++) {
        cout << equipos[i].pais
             << " | GF: " << equipos[i].golesF
             << " GC: " << equipos[i].golesC
             << " G: " << equipos[i].ganados
             << " E: " << equipos[i].empatados
             << " P: " << equipos[i].perdidos << endl;
    }
}
