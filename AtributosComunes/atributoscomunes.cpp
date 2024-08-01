#include "atributoscomunes.h"
#include "../lectorarchivos.h"

AtributosComunes::AtributosComunes(){
    LectorArchivos lector(":/Resources/ArchivosTexto/paises.txt");
    this->paises = lector.getArray();
    this->maxPaises = lector.getTopeArray();
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

