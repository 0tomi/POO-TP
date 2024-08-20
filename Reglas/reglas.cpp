#include "reglas.h"
#include "../lectorarchivos.h"

Reglas::Reglas() {
    LectorArchivos lector(":/Resources/ArchivosTexto/paises.txt");
    this->paises = lector.getArray();
    this->maxPaises = lector.getTopeArray();
}

Reglas::~Reglas()
{
    //delete paises;
}

QString *Reglas::getPaises(int &max) const
{
    max = this->maxPaises;
    return paises;
}

QString *Reglas::getTipoVisitas(int &max)
{
    max = MaxTipoVisitas;
    return copiarVector(this->tipoVisitas, MaxTipoVisitas);
}

QString *Reglas::getEstadosCiviles(int &max)
{
    max = MaxEstadosCiviles;
    return copiarVector(estadosCiviles, MaxEstadosCiviles);
}

QString *Reglas::copiarVector(QString * viejoVec, int max)
{
    QString * nuevoVec = new QString[max];
    for (int i = 0; i < max; i++)
        nuevoVec[i] = viejoVec[i];
    return nuevoVec;
}

