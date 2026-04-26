#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "torneo.h"
#include "fase.h"
#include "util.h"
#include "metricas.h"

using namespace std;

void mostrarMenu() {
    cout << "\n======================================" << endl;
    cout << "              MENU TORNEO             " << endl;
    cout << "======================================" << endl;
    cout << "1. Avanzar un dia" << endl;
    cout << "2. Mostrar todos los equipos" << endl;
    cout << "3. Mostrar grupos" << endl;
    cout << "4. Mostrar estadisticas de equipos" << endl;
    cout << "5. Mostrar estadisticas de jugadores" << endl;
    cout << "6. Crear y mostrar fase eliminatoria" << endl;
    cout << "7. Jugar toda la eliminatoria" << endl;
    cout << "8. Mostrar calendario" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione: ";
}

int main() {
    srand((unsigned)time(NULL));

    Torneo torneo;
    torneo.cargarEquipos("fifa.csv");

    if (torneo.getCantidad() != 48) {
        cout << "Error: se necesitan exactamente 48 equipos." << endl;
        cout << "Equipos cargados: " << torneo.getCantidad() << endl;
        return 1;
    }

    Fase fase;
    fase.iniciarFase(torneo.getEquipos(), torneo.getCantidad());
    fase.iniciarCalendario();

    int opcion = -1;
    string linea;

    do {
        mostrarMenu();

        if (!getline(cin, linea)) {
            cout << "Error leyendo la opcion." << endl;
            break;
        }

        if (!esEnteroValido(linea)) {
            cout << "Opcion invalida." << endl;
            continue;
        }

        opcion = convertirEnteroSeguro(linea);

        switch (opcion) {

        case 1:
            Metricas::reiniciar();

            fase.avanzarDia();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(fase.hayDieciseisavosCreados())
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Avanzar un dia", memoria);
            }
            break;

        case 2:
            Metricas::reiniciar();

            torneo.mostrarTodo();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(fase.hayDieciseisavosCreados())
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Mostrar todos los equipos", memoria);
            }
            break;

        case 3:
            Metricas::reiniciar();

            fase.mostrarGrupos();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(fase.hayDieciseisavosCreados())
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Mostrar grupos", memoria);
            }
            break;

        case 4:
            Metricas::reiniciar();

            torneo.mostrarEstadisticasEquipos();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(fase.hayDieciseisavosCreados())
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Mostrar estadisticas de equipos", memoria);
            }
            break;

        case 5:
            Metricas::reiniciar();

            torneo.mostrarEstadisticasJugadores();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(fase.hayDieciseisavosCreados())
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Mostrar estadisticas de jugadores", memoria);
            }
            break;

        case 6:
            Metricas::reiniciar();

            fase.crearDieciseisavos();
            fase.mostrarDieciseisavos();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(true) // ya se crean aquí
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Crear y mostrar fase eliminatoria", memoria);
            }
            break;

        case 7:
            Metricas::reiniciar();

            fase.jugarTodaEliminatoria();

            {
                long long memoria =
                    calcularMemoriaTorneo(torneo.getCantidad())
                    + calcularMemoriaGrupos()
                    + calcularMemoriaEliminatoria(true)
                    + sizeof(opcion)
                    + sizeof(linea);

                Metricas::mostrar("Gasto total del sistema", memoria);
            }
            break;

        case 8:
            fase.mostrarCalendario();
            break;

        case 0:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}