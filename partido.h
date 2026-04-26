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
    bool prorrogaJugada;

    void reset();
    int limitarEntero(int valor, int minimo, int maximo) const;
    int poisson(float lambda) const;
    float calcularLambda(Equipo* ataque, Equipo* defensa) const;

public:
    Partido();
    Partido(Equipo* local, Equipo* visitante);

    void configurar(const string& fechaPartido,
                    const string& horaPartido,
                    const string& nombreSede,
                    const string& arb1,
                    const string& arb2,
                    const string& arb3);

    void jugar();

    void mostrar() const;
    void mostrarDetalle() const;

    string getFecha() const;
    string getHora() const;

    Equipo* getEquipoLocal() const;
    Equipo* getEquipoVisitante() const;

    int getGolesLocal() const;
    int getGolesVisitante() const;

    int getPosesionLocal() const;
    int getPosesionVisitante() const;

    bool yaSeJugo() const;

    void prorroga();
    bool huboProrroga() const;
};

#endif


