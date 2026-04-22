#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
using namespace std;

class Equipo;
class Jugador;

class Partido {
private:
    Equipo* equipoLocal;
    Equipo* equipoVisitante;

    string sede;
    string arbitro1;
    string arbitro2;
    string arbitro3;
    string fecha;
    string hora;

    int golesLocal;
    int golesVisitante;

    int posesionLocal;
    int posesionVisitante;

    int tirosLocal;
    int tirosVisitante;

    int tirosArcoLocal;
    int tirosArcoVisitante;

    int faltasLocal;
    int faltasVisitante;

    int amarillasLocal;
    int amarillasVisitante;

    int rojasLocal;
    int rojasVisitante;

    bool jugado;

    int poisson(float lambda);
    float calcularLambda(Equipo* ataque, Equipo* defensa);
    int limitarEntero(int valor, int minimo, int maximo);

public:
    Partido();
    Partido(Equipo* local, Equipo* visitante);

    void configurar(string fechaPartido,
                    string horaPartido,
                    string nombreSede,
                    string arb1,
                    string arb2,
                    string arb3);

    void jugar();
    void mostrar();
    void mostrarDetalle();

    string getFecha();
    string getHora();

    Equipo* getEquipoLocal();
    Equipo* getEquipoVisitante();

    int getGolesLocal();
    int getGolesVisitante();

    int getPosesionLocal();
    int getPosesionVisitante();

    bool yaSeJugo();
};

#endif
