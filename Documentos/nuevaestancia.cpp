#include "nuevaestancia.h"

NuevaEstancia::NuevaEstancia() {}

NuevaEstancia::NuevaEstancia(Estancia* _estancia, vector<QString> _paisesPaso, vector<QString> _bienesTransp, QString _ocupacion) {
    estancia = _estancia;
    paisesPaso = _paisesPaso;
    bienesTransp = _bienesTransp;
    ocupacion = _ocupacion;
}

Estancia *NuevaEstancia::getEstancia() {
    return this->estancia;
}

vector<QString> NuevaEstancia::getPaisesPaso() {
    return this->paisesPaso;
}

vector<QString> NuevaEstancia::getBienesTransp() {
    return this->bienesTransp;
}

QString NuevaEstancia::getOcupacion() {
    return this->ocupacion;
}