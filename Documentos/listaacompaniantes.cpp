#include "listaacompaniantes.h"

ListaAcompaniantes::ListaAcompaniantes() {
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString _mensajeSinAcomp, bool _validez) {
    mensajeSinAcomp = _mensajeSinAcomp;
    validez = _validez;
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString* _nombresAcomps, int _topeNombresAcomps, bool _validez) {
    nombresAcomps = _nombresAcomps;
    topeNombresAcomps = _topeNombresAcomps;
    validez = _validez;
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
