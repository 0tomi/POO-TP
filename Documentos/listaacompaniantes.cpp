#include "listaacompaniantes.h"

ListaAcompaniantes::ListaAcompaniantes() {
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString _mensajeSinAcomp) {
    mensajeSinAcomp = _mensajeSinAcomp;
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString* _nombresAcomps, int _topeNombresAcomps) {
    nombresAcomps = _nombresAcomps;
    topeNombresAcomps = _topeNombresAcomps;
}

// getters:
QString ListaAcompaniantes::getMensajeSinAcomp() {
    return mensajeSinAcomp;
}
QString* ListaAcompaniantes::getNombresAcomps() {
    return nombresAcomps;
}

int ListaAcompaniantes::getTopeNombresAcomps() {
    return topeNombresAcomps;
}
