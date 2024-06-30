#include <fstream>
#include "Juego.h"

Juego::Juego(){
    this->atributos = new AtributosComunes();
    this->maxPaises = 20;

    // Leemos los paises y los guardamos en el array de paises
    this->LeerPaises();

    // Seteamos las reglas del juego, pasando el array de paises.
    this->rules = new reglas(atributos);
}

void Juego::LeerPaises(){
    int contadorPaises = 0;
    // Abrir archivo
    string direccionPaises = "ArchivosTexto/paises.txt";
    ifstream ArchivoPaises(direccionPaises);

    // Si falla cerramos el programa
    if (ArchivoPaises.fail())
        exit(1);

    // Creamos el array que contendra los paises
    this->paises = new string[this->maxPaises];

    // Leer archivo
    while (getline(ArchivoPaises, this->paises[contadorPaises])){
        contadorPaises++;
        
        // Si el array se nos queda chico, lo incrementamos
        if (contadorPaises == this->maxPaises){
            this->maxPaises += 20;
            this->rescaleVector(contadorPaises);
        }
    }

    // Si el array quedo sobredimensionado, lo acortamos
    if (contadorPaises < this->maxPaises){
        this->maxPaises = contadorPaises;
        this->rescaleVector(contadorPaises);
    }

    atributos.setAtributos(this->paises, this->maxPaises);
    ArchivoPaises.close();
}

void Juego::rescaleVector(int cont){
    string* newVector = new string[maxPaises];
    for (int i = 0; i < cont; i++)
        newVector[i] = paises[i];

    delete[] paises;
    paises = newVector;
}

string* Juego::getPaises(int &max){
    max = this->maxPaises;
    return this->paises;
}

reglas* Juego::getReglas(){
    return this->rules;
}