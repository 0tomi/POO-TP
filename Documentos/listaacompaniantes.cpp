#include "listaacompaniantes.h"

bool ListaAcompaniantes::getValidez() const
{
    return validez;
}

int ListaAcompaniantes::getCantAcompaniantes() const
{
    return CantAcompaniantes;
}

bool ListaAcompaniantes::getValidezDialogo() const
{
    return dialogo;
}

ListaAcompaniantes::ListaAcompaniantes() {
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString _mensajeSinAcomp, bool _validez,  bool _dialogo) {
    mensajeSinAcomp = _mensajeSinAcomp;
    validez = _validez;
    this->dialogo = _dialogo;
    nombresAcomps = nullptr;
    topeNombresAcomps = 0;
    CantAcompaniantes = 0;
}

ListaAcompaniantes::ListaAcompaniantes(QString* _nombresAcomps, int _topeNombresAcomps, bool _validez, bool _dialogo) {
    nombresAcomps = _nombresAcomps;
    topeNombresAcomps = _topeNombresAcomps;
    validez = _validez;
    this->dialogo = _dialogo;
    CantAcompaniantes = _topeNombresAcomps;
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
