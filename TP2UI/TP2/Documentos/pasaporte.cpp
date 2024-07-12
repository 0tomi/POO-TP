#include "../Documentos/pasaporte.h"

Pasaporte::Pasaporte(QString nombre, QString fecha_nacimiento, char genero, QString nacionalidad, QString estado_civil) {
    this->nombre = nombre;
    this->estado_civil = estado_civil;
    this->genero = genero;
    this->fecha_nacimiento = fecha_nacimiento;
    this->nacionalidad = nacionalidad;
}

QString Pasaporte::getestado_civil(){
    return this->estado_civil;
}

QString Pasaporte::getnombre(){
    return this->nombre;
}

char Pasaporte::getgenero(){
    return this->genero;
}

QString Pasaporte::getfecha_nacimiento(){
    return this->fecha_nacimiento;
}

QString Pasaporte::getnacionalidad(){
    return this->nacionalidad;
}
