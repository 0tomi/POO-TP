#include "paisresidencia.h"

PaisResidencia::PaisResidencia(QString nombre,QString fecha,QString PaisDeResidencia) {
    this->PaisDeResidencia = PaisDeResidencia;
    this->nombre = nombre;
    this->fecha_nacimiento = fecha;
}

QString PaisResidencia::getNombre() const
{
    return this->nombre;
}

QString PaisResidencia::getFecha() const
{
    return this->fecha_nacimiento;
}

QString PaisResidencia::getPaisResidencia() const
{
    return this->PaisDeResidencia;
}
