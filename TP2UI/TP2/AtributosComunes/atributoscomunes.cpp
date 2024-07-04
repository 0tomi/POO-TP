#include "atributoscomunes.h"

AtributosComunes::AtributosComunes(){
    this->paises = NULL;
    this->maxPaises = 0;
}

void AtributosComunes::setAtributos(string* pais, int maxPais){
    this->paises = pais;
    this->maxPaises = maxPais;
}

string* AtributosComunes::getPaises(int &max){
    max = this->maxPaises;
    return this->paises;
}

string* AtributosComunes::getVisitas(int &max){
    max = 3;
    return this->tipoVisitas;
}

string* AtributosComunes::getEstadosCiviles(int &max){
    max = 4;
    return this->EstadosCiviles;
}

