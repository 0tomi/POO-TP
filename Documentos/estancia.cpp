#include "estancia.h"

bool Estancia::getValidez() const
{
    return Validez;
}

Estancia::Estancia(int _duracion, QString _tipo, bool valido) {
    duracionEst = _duracion;
    tipoEst = _tipo;
    Validez = valido;
}

int Estancia::getDuracEstancia() {
    return duracionEst;
}

QString Estancia::getTipoEstancia() {
    return tipoEst;
}
