#include "estancia.h"

Estancia::Estancia(int _durac, string _tipo) {
    duracionEst = _durac;
    tipoEst = _tipo;
}

int Estancia::getDuracEstancia() {
    return duracionEst;
}

string Estancia::getTipoEstancia() {
    return tipoEst;
}
