#include "generadorlistaacompaniantes.h"

#include <ctime>

GeneradorListaAcompaniantes::GeneradorListaAcompaniantes() {
    LectorArchivos archivo(":/Resources/ArchivosTexto/mujeres.txt");
    this->nombresMujeres = archivo.getArray();
    this->maxMujeres = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/hombres.txt");
    this->nombresHombres = archivo.getArray();
    this->maxHombres = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/x.txt");
    this->nombresX = archivo.getArray();
    this->maxX = archivo.getTopeArray();

    archivo.LeerArchivoNuevo(":/Resources/ArchivosTexto/apellidos.txt");
    this->apellidos = archivo.getArray();
    this->maxApellidos = archivo.getTopeArray();

    quint32 semilla = static_cast<quint32>(time(NULL));
    numRandom.seed(semilla);
}

GeneradorListaAcompaniantes::~GeneradorListaAcompaniantes() {}


// <-------- METODOS PRIVADOS -------->
char GeneradorListaAcompaniantes::getGeneroRandom() {
    const char generos[] = {'H', 'M', 'X'};
    int randomIndex = numRandom.bounded(3);
    return generos[randomIndex];
}


QString GeneradorListaAcompaniantes::generarNombre(char genero) {
    QString nombreResult;
    int i;

    switch(genero) {
    case 'H':
        i = this->numRandom.bounded(this->maxHombres);
        nombreResult = this->nombresHombres[i];
        break;
    case 'M':
        i = this->numRandom.bounded(this->maxMujeres);
        nombreResult = this->nombresMujeres[i];
        break;
    case 'X':
        i = this->numRandom.bounded(this->maxX);
        nombreResult = this->nombresX[i];
        break;
    }
    nombreResult += " " + this->apellidos[this->numRandom.bounded(this->maxApellidos)];
    return nombreResult;
}


// <-------- METODOS PUBLICOS --------->
ListaAcompaniantes* GeneradorListaAcompaniantes::getListaAcompaniantes() {
    int indexRandom = numRandom.bounded(4); // cant acompañantes
    QString msjSinAcomp; // para almacenar mensaje si es que no tiene acompañante

    if (indexRandom == 0) {
        msjSinAcomp = "Viaja sin acompañante";
        return new ListaAcompaniantes(msjSinAcomp);
    }

    // tiene acompañantes...
    int topeNombres = indexRandom;
    QString* nombresAcomps = new QString[topeNombres];

    for (int i = 0; i < topeNombres; i++) {
        char generoRandom = getGeneroRandom();
        switch (generoRandom) {
            case 'H':
                nombresAcomps[i] = generarNombre('H');
                break;
            case 'M':
                nombresAcomps[i] = generarNombre('M');
                break;
            case 'X':
                nombresAcomps[i] = generarNombre('X');
                break;
        }
    }
    return new ListaAcompaniantes(nombresAcomps, topeNombres);
}
