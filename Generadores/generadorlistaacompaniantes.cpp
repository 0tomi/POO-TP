#include "generadorlistaacompaniantes.h"

#include <QDebug>

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
}

void GeneradorListaAcompaniantes::Inicializar(QRandomGenerator *generador, ReglasNivel3* reglas)
{
    this->numRandom = generador;
    this->maxAcompaniantesValidos = reglas->getMaxAcompaniantes();
}

GeneradorListaAcompaniantes::~GeneradorListaAcompaniantes() {}


// <-------- METODOS PRIVADOS -------->
char GeneradorListaAcompaniantes::getGeneroRandom() {
    const char generos[] = {'H', 'M', 'X'};
    int randomIndex = numRandom->bounded(3);
    return generos[randomIndex];
}


QString *GeneradorListaAcompaniantes::generarAcompaniantes(int max)
{
    QString* nombresAcomps = new QString[max];
    for (int i = 0; i < maxAcompaniantesValidos; i++) {
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

    return nombresAcomps;
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
    generarCamposValidos(validez);
    int topeNombres; QString * nombresAcomps;
    if (validez){
        if (this->maxAcompaniantesValidos == 0) {
            QString msjSinAcomp = "Viaja sin acompañante";
            return new ListaAcompaniantes(msjSinAcomp, validez, true);
        } else {
            topeNombres = numRandom->bounded(maxAcompaniantesValidos+1);
            if (topeNombres == 0)
                return new ListaAcompaniantes("Viaja sin acompañante", validez, true);

            nombresAcomps = generarAcompaniantes(topeNombres);
            return new ListaAcompaniantes(nombresAcomps, topeNombres, validez, true);
        }
    } else {
        if (this->maxAcompaniantesValidos == 3) {
            topeNombres = numRandom->bounded(maxAcompaniantesValidos+1);
            nombresAcomps = generarAcompaniantes(topeNombres);

            return new ListaAcompaniantes(nombresAcomps, topeNombres, validez, false);
        }
        if (Campos[0]){

        }

        return new ListaAcompaniantes(nombresAcomps, topeNombres, validez, Campos[1]);
    }
}

int GeneradorListaAcompaniantes::generarRandomExcluido(int excluded) {
    int res;
    do { // genera un numero random, si este numero es igual al excluido repite el proceso.
        res = numRandom->bounded(4);
    } while (res == excluded);
    return res;
}

void GeneradorListaAcompaniantes::generarCamposValidos(bool validez)
{
    if (validez){
        Campos[0] = Campos[1] = true;
    } else {
        int sorteo = numRandom->bounded(3);
        switch (sorteo){
        case 0: Campos[0] = true;
            Campos[1] = false;
            break;
        case 1: Campos[0] = false;
            Campos[1] = false;
            break;
        case 2: Campos[0] = false;
            Campos[1] = true;
            break;
        }
    }
}
