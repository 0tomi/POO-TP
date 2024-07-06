#include "documentacion.h"

bool Documentacion::getValida() const
{
    return valida;
}

Documentacion::Documentacion(bool validez){
    this->valida = validez;
}

Pasaporte *Documentacion::getPasaport() const
{
    return pasaport;
}

void Documentacion::setPasaport(Pasaporte *newPasaport)
{
    pasaport = newPasaport;
}

Estancia *Documentacion::getEstancia() const
{
    return estancia;
}

void Documentacion::setEstancia(Estancia *newEstancia)
{
    estancia = newEstancia;
}

Documentacion::~Documentacion()
{
    delete estancia;
    delete pasaport;
}


