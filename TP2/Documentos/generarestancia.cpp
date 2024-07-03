#include "generarestancia.h"

#include <ctime>

GenerarEstancia::GenerarEstancia() {}

GenerarEstancia::GenerarEstancia(string* _tiposVisitas, int _topeTiposVisits, string* _tiposVisitsVal, int _topeVisitsVal, int _duracMax) {
    tipoVisitas = _tiposVisitas;
    topeTipoVisitas = _topeTiposVisits;
    tipoVisitasValidas = _tiposVisitsVal;
    topeVisitasValidas = _topeVisitsVal;
    duracMaximaEstancia = _duracMax;
}

// getters:
Juego* GenerarEstancia::getClaseJuego() {
    return juego;
}

int GenerarEstancia::getTopeTipoVisitas() {
    return topeTipoVisitas;
}

int GenerarEstancia::getTopeTipoVisitasVals() {
    return topeVisitasValidas;
}

bool GenerarEstancia::getValidacion() {
    return valido;
}

Estancia* GenerarEstancia::getEstancia(bool& valido) {
    srand(time(0));
    int duracGenerar = 0; int opcion = 1 + (rand() % 3);
    string* tiposInvalidos = nullptr;
    string tipoEstGenerar;
    int cantInvalidos = 0;

    if (valido) { // data valida
        // genero duracion estancia random (valida)
        if (duracMaximaEstancia > 0) {
            duracGenerar = 3 + (rand() % duracMaximaEstancia);
        }
        // genero tipo estancia random (valida)
        if (topeVisitasValidas > 0) {
            tipoEstGenerar = tipoVisitasValidas[rand() % topeVisitasValidas];
        }
        valido = true;
    } else { // data invalida

        switch (opcion) {
        case 1: // genera solo duracion estancia invalida
            if (duracMaximaEstancia > 0) {
                duracGenerar = 10 + (rand() % duracMaximaEstancia);
            }
            if (topeVisitasValidas > 0) {
                tipoEstGenerar = tipoVisitasValidas[rand() % topeVisitasValidas];
            }
            valido = false;
            break;
        case 2: // genero solo tipo estancia invalido
            if (duracMaximaEstancia > 0) {
                duracGenerar = 3 + (rand() % duracMaximaEstancia);
            }
            tiposInvalidos = getTiposInvalidos(tipoVisitas, tipoVisitasValidas, cantInvalidos);
            if (cantInvalidos > 0) {
                tipoEstGenerar = tiposInvalidos[rand() % cantInvalidos];
            }
            delete[] tiposInvalidos;
            valido = false;
            break;
        case 3: // ambos datos invalidos
            if (duracMaximaEstancia > 0) {
                duracGenerar = 10 + (rand() % duracMaximaEstancia);
            }
            tiposInvalidos = getTiposInvalidos(tipoVisitas, tipoVisitasValidas, cantInvalidos);
            if (cantInvalidos > 0) {
                tipoEstGenerar = tiposInvalidos[rand() % cantInvalidos];
            }
            delete[] tiposInvalidos;
            valido = false;
            break;
        default: // genera todos validos
            if (duracMaximaEstancia > 0) {
                duracGenerar = 3 + (rand() % duracMaximaEstancia);
            }
            if (topeVisitasValidas > 0) {
                tipoEstGenerar = tipoVisitasValidas[rand() % topeVisitasValidas];
            }
            valido = true;
            break;
        }
    }
    Estancia* estanciaAGenerar = new Estancia(duracGenerar, tipoEstGenerar);
    return estanciaAGenerar;
}

string* GenerarEstancia::getTiposInvalidos(string* tiposVisitas, string* tiposVisitsVal, int &cantInvalidos) {
    bool band; int topeTiposInvalidos = 3; int index = 0;
    string* tiposInvalidos = new string[topeTiposInvalidos];

    for (int i = 0; i < topeTipoVisitas; i++) {
        band = false;
        for (int j = 0; j < topeVisitasValidas; j++) {
            if (tiposVisitas[i] == tiposVisitsVal[j]) {
                band = true;
                break;
            }
        }
        if (!band && index < topeTiposInvalidos) {
            tiposInvalidos[index++] = tiposVisitas[i];
        }
    }
    cantInvalidos = index;
    return tiposInvalidos;
}
