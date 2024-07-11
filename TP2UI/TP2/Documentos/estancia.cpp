#include "estancia.h"

Estancia::Estancia(int _duracion, QString _tipo) {
    duracionEst = _duracion;
    tipoEst = _tipo;
}

int Estancia::getDuracEstancia() {
    return duracionEst;
}

QString Estancia::getTipoEstancia() {
    return tipoEst;
}
