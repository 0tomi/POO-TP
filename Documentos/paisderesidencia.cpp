#include "paisderesidencia.h"

PaisDeResidencia::PaisDeResidencia(QString nombre, QString fecha, char genero, QString nacionalidad,QString PaisdeResidencia) {
    this->PaisdeResidencia = PaisdeResidencia;
    this->fecha_nacimiento = fecha;
    this->nacionalidad = nacionalidad;
    this->genero = genero;
    this->nombre = nombre;
}

QString PaisDeResidencia::getFecha() const{
    return this->fecha_nacimiento;
}

QString PaisDeResidencia::getNacionalidad() const{
    return this->fecha_nacimiento;
}

QString PaisDeResidencia::getNombre() const{
    return this->nombre;
}

char PaisDeResidencia::getGenero() const{
    return this->genero;
}

QString PaisDeResidencia::getPaisdeResidencia() const{
    return this->PaisdeResidencia;
}
