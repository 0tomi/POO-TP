#include "documentacion.h"

Documentacion::Documentacion()
{
    datosFalsos = nullptr;
}

Documentacion::~Documentacion()
{
    if (datosFalsos)
        delete datosFalsos;
}

QString Documentacion::getDatosFalsos()
{
    if (datosFalsos)
        return *datosFalsos;
    else return "";
}

void Documentacion::addDatosFalsos(QString datos)
{
    if (!datosFalsos)
        datosFalsos = new QString;

    *datosFalsos += datos + "\n";
}
