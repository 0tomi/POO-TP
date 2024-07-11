#include "generarestancia.h"

#include <stdlib.h>
#include <ctime>
#include <QDebug>

GenerarEstancia::GenerarEstancia() {

}

GenerarEstancia::~GenerarEstancia()
{
    delete NumRandom;
}

GenerarEstancia::GenerarEstancia(QString* _tiposVisitas, int _topeTiposVisits, QString* _tiposVisitsVal, int _topeVisitsVal, int _duracMax) {
    tipoVisitas = _tiposVisitas;
    topeTipoVisitas = _topeTiposVisits;

    tipoVisitasValidas = _tiposVisitsVal;
    topeVisitasValidas = _topeVisitsVal;

    duracMaximaEstancia = _duracMax;

    NumRandom = new QRandomGenerator(time(NULL));
}

// getters:
Estancia* GenerarEstancia::getEstancia(bool valido) {
    int duracGenerar;
    int opcion = NumRandom->bounded(1, 4);
    QString* tiposInvalidos = nullptr;
    QString tipoEstGenerar;
    int cantInvalidos = 0;

    if (valido) { // data valida
        // genero duracion estancia random (valida)
        duracGenerar = NumRandom->bounded(3, duracMaximaEstancia);

        // genero tipo estancia random (valida)
        int sorteo;
        if (topeVisitasValidas == 1)
            sorteo = 0;
        else
            sorteo = NumRandom->bounded(topeVisitasValidas);
        tipoEstGenerar = tipoVisitasValidas[sorteo];
    } else { // data invalida
        switch (opcion) {
        case 1: // genera solo duracion estancia invalida
            if (duracMaximaEstancia > 0) {
                duracGenerar = NumRandom->bounded(10, duracMaximaEstancia);
            }
            if (topeVisitasValidas > 0) {
                tipoEstGenerar = tipoVisitasValidas[NumRandom->bounded(topeVisitasValidas)];
            }
            break;
        case 2: // genero solo tipo estancia invalido
            if (duracMaximaEstancia > 0) {
                duracGenerar = NumRandom->bounded(3, duracMaximaEstancia);
            }
            tiposInvalidos = getTiposInvalidos(tipoVisitas, tipoVisitasValidas, cantInvalidos);
            if (cantInvalidos > 0) {
                tipoEstGenerar = tiposInvalidos[NumRandom->bounded(cantInvalidos)];
            }
            delete[] tiposInvalidos;
            break;
        case 3: // ambos datos invalidos
            if (duracMaximaEstancia > 0) {
                duracGenerar = NumRandom->bounded(10, duracMaximaEstancia);
            }
            tiposInvalidos = getTiposInvalidos(tipoVisitas, tipoVisitasValidas, cantInvalidos);
            if (cantInvalidos > 0) {
                tipoEstGenerar = tiposInvalidos[NumRandom->bounded(cantInvalidos)];
            }
            delete[] tiposInvalidos;
            break;
        }
    }
    Estancia* estanciaAGenerar = new Estancia(duracGenerar, tipoEstGenerar);
    return estanciaAGenerar;
}

QString* GenerarEstancia::getTiposInvalidos(QString* tiposVisitas, QString* tiposVisitsVal, int &cantInvalidos) {
    bool band; int topeTiposInvalidos = 3; int index = 0;
    QString* tiposInvalidos = new QString[topeTiposInvalidos];

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
