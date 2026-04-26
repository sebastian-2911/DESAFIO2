#include "util.h"
#include "metricas.h"

bool esEnteroValido(const string& texto) {
    if (texto.empty()) {
        return false;
    }

    int inicio = 0;

    if (texto[0] == '-') {
        if (texto.length() == 1) {
            return false;
        }

        inicio = 1;
    }

    for (int i = inicio; i < (int)texto.length(); i++) {
        Metricas::sumarIteracion();
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }

    return true;
}

int convertirEnteroSeguro(const string& texto) {
    int numero = 0;
    int signo = 1;
    int i = 0;

    if (texto[0] == '-') {
        signo = -1;
        i = 1;
    }

    for (; i < (int)texto.length(); i++) {
        Metricas::sumarIteracion();
        numero = numero * 10 + (texto[i] - '0');
    }

    return numero * signo;
}