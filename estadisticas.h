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
};

#endif