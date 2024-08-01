#include "../Documentos/pasaporte.h"

Pasaporte::Pasaporte(QString nombre, QString fecha_nacimiento, char genero, QString nacionalidad, QString estado_civil) {
    this->nombre = nombre;
    this->estado_civil = estado_civil;
    this->genero = genero;
    this->fecha_nacimiento = fecha_nacimiento;
    this->nacionalidad = nacionalidad;
}

QString Pasaporte::getestado_civil() const{
    return this->estado_civil;
}

Skin Pasaporte::getSkinNPC() const
{
    return SkinNPC;
}

void Pasaporte::setSkinNPC(const Skin &newSkinNPC)
{
    SkinNPC = newSkinNPC;
}

QString Pasaporte::getnombre() const{
    return this->nombre;
}

char Pasaporte::getgenero() const{
    return this->genero;
}

QString Pasaporte::getfecha_nacimiento() const{
    return this->fecha_nacimiento;
}

QString Pasaporte::getnacionalidad() const {
    return this->nacionalidad;
}
