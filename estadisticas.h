#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

class Estadisticas {
public:
    int golesF;
    int golesC;
    int ganados;
    int empatados;
    int perdidos;

    Estadisticas()
        : golesF(0), golesC(0), ganados(0), empatados(0), perdidos(0) {}

    Estadisticas(const Estadisticas& otra)
        : golesF(otra.golesF),
        golesC(otra.golesC),
        ganados(otra.ganados),
        empatados(otra.empatados),
        perdidos(otra.perdidos)
    {
    }
    //sobrecarga
    Estadisticas& operator=(const Estadisticas& otra) {
        if (this != &otra) {
            golesF = otra.golesF;
            golesC = otra.golesC;
            ganados = otra.ganados;
            empatados = otra.empatados;
            perdidos = otra.perdidos;
        }
        return *this;
    }

    bool operator==(const Estadisticas& otra) const {
        return golesF == otra.golesF &&
               golesC == otra.golesC &&
               ganados == otra.ganados &&
               empatados == otra.empatados &&
               perdidos == otra.perdidos;
    }

    bool operator>(const Estadisticas& otra) const {
        int puntos = ganados * 3 + empatados;
        int puntosOtra = otra.ganados * 3 + otra.empatados;

        if (puntos != puntosOtra) {
            return puntos > puntosOtra;
        }

        return (golesF - golesC) > (otra.golesF - otra.golesC);
    }
};

#endif