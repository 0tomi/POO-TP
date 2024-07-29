#include "generadorlistaacompaniantes.h"

#include <QDebug>

GeneradorListaAcompaniantes::GeneradorListaAcompaniantes(QRandomGenerator * generador) {
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

    numRandom = generador;
}

GeneradorListaAcompaniantes::~GeneradorListaAcompaniantes() {}


// <-------- METODOS PRIVADOS -------->
char GeneradorListaAcompaniantes::getGeneroRandom() {
    const char generos[] = {'H', 'M', 'X'};
    int randomIndex = numRandom->bounded(3);
    return generos[randomIndex];
}


QString GeneradorListaAcompaniantes::generarNombre(char genero) {
    QString nombreResult;
    int i;

    switch(genero) {
    case 'H':
        i = this->numRandom->bounded(this->maxHombres);
        nombreResult = this->nombresHombres[i];
        break;
    case 'M':
        i = this->numRandom->bounded(this->maxMujeres);
        nombreResult = this->nombresMujeres[i];
        break;
    case 'X':
        i = this->numRandom->bounded(this->maxX);
        nombreResult = this->nombresX[i];
        break;
    }
    nombreResult += " " + this->apellidos[this->numRandom->bounded(this->maxApellidos)];
    return nombreResult;
}


// <-------- METODOS PUBLICOS --------->
ListaAcompaniantes* GeneradorListaAcompaniantes::getListaAcompaniantes(bool validez) {
    int indexRandom = numRandom->bounded(4); // cant acompañantes
    QString msjSinAcomp; // para almacenar mensaje si es que no tiene acompañante

    if (indexRandom == 0) {
        msjSinAcomp = "Viaja sin acompañante";
        return new ListaAcompaniantes(msjSinAcomp, validez);
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

QString GeneradorListaAcompaniantes::generarDialogosAcomps(bool validez, int cantAcomp) {
    int numRandomExcluded = 0;
    QString dialogo;
    
    if (validez) { // genero dialogos validos
        switch(cantAcomp) {
            case 0:
                dialogo = dialogosAcomps[0];
                numRandomExcluded = generarRandomExcluido(cantAcomp);
                break;
            case 1:
                dialogo = dialogosAcomps[1];
                numRandomExcluded = generarRandomExcluido(cantAcomp);
                break;
            case 2:
                dialogo = dialogosAcomps[2];
                numRandomExcluded = generarRandomExcluido(cantAcomp);
                break;
            case 3:
                dialogo = dialogosAcomps[3];
                numRandomExcluded = generarRandomExcluido(cantAcomp);
                break;
        }
    } else { // genero dialogos invalidos
        dialogo = dialogosAcomps[numRandomExcluded];
    }
    return dialogo;
}

int GeneradorListaAcompaniantes::generarRandomExcluido(int excluded) {
    int res;
    do { // genera un numero random, si este numero es igual al excluido repite el proceso.
        res = numRandom->bounded(4);
    } while (res == excluded);
    return res;
}
