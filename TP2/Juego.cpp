#include <fstream>
#include "Juego.h"

Juego::Juego(){
    this->maxPaises = 20;

    // Leemos los paises y los guardamos en el array de paises
    this->LeerPaises();

    // Seteamos las reglas del juego, pasando el array de paises.
    this->rules = new reglas(this->paises, this->maxPaises);
}

void Juego::LeerPaises(){
    int contadorPaises = 0;
    // Abrir archivo
    string direccionPaises = "./paises.txt";
    ifstream Paises(direccionPaises);

    // Si falla cerramos el programa
    if (Paises.fail())
        exit(1);

    // Creamos el array que contendra los paises
    this->paises = new string[this->maxPaises];
    
    // Leer archivo
    while (getline(Paises, this->paises[contadorPaises])){
        contadorPaises++;
        
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
}

void Juego::rescaleVector(int cont){
    string* newVector = new string[maxPaises];
    for (int i = 0; i < cont; i++)
        newVector[i] = paises[i];

    delete paises[];
    paises = newVector;
}
