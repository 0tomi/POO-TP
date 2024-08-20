#include "reglas.h"
#include "../lectorarchivos.h"

Reglas::Reglas() {
    LectorArchivos lector(":/Resources/ArchivosTexto/paises.txt");
    this->paises = lector.getArray();
    this->maxPaises = lector.getTopeArray();
}

Reglas::~Reglas()
{

}

