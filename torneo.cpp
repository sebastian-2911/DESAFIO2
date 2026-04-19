#include "torneo.h"
#include <iostream>
#include <fstream>

using namespace std;

// convertir string a int sin stoi
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
    equipos = new Equipo[48];
}

// Destructor
Torneo::~Torneo() {
    delete[] equipos;
}

// Cargar equipos desde CSV
void Torneo::cargarEquipos(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    string linea;

    // Saltar encabezados
    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea) && cantidad < 48) {

        Equipo e;

        string pais, tecnico;
        string golesF_str, golesC_str, ganados_str, empatados_str, perdidos_str;

        int inicio = 0;
        int pos;

        // ranking (ignorar)
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        inicio = pos + 1;

        // pais
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        pais = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // tecnico
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        tecnico = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // federacion (ignorar)
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        inicio = pos + 1;

        // confederacion (ignorar)
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        inicio = pos + 1;

        // golesF
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        golesF_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // golesC
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        golesC_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // ganados
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        ganados_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // empatados
        pos = linea.find(";", inicio);
        if (pos == -1) continue;
        empatados_str = linea.substr(inicio, pos - inicio);
        inicio = pos + 1;

        // perdidos
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

        // guardar en arreglo
        equipos[cantidad] = e;
        cantidad++;
    }

    archivo.close();
}




Equipo* Torneo::getEquipos() {
    return equipos;
}

int Torneo::getCantidad() {
    return cantidad;
}
