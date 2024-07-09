#include "atributoscomunes.h"

AtributosComunes::AtributosComunes(){
    this->paises = NULL;
    this->maxPaises = 0;
}

void AtributosComunes::setAtributos(QString* pais, int maxPais){
    this->paises = pais;
    this->maxPaises = maxPais;
}

QString* AtributosComunes::getPaises(int &max){
    max = this->maxPaises;
    return this->paises;
}

QString* AtributosComunes::getVisitas(int &max){
    max = 3;
    return this->tipoVisitas;
}

QString* AtributosComunes::getEstadosCiviles(int &max){
    max = 4;
    return this->EstadosCiviles;
}

AtributosComunes::~AtributosComunes()
{
    delete paises;
}

