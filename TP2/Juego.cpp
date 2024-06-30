#include <fstream>
#include "LectorArchivos.cpp"
#include "Juego.h"

Juego::Juego(){
    this->atributos = new AtributosComunes();

    // Leemos los paises y los guardamos en el array de paises
    LectorArchivos LA("ArchivosTexto/paises.txt");
    this->atributos->setAtributos(LA.getArray(), LA.getTopeArray());

    // Seteamos las reglas del juego, pasando el array de paises.
    this->rules = new reglas(atributos);
}

void Juego::LeerPaises(){
    int maxPaises = 20;
    int contadorPaises = 0;
    // Abrir archivo
    string direccionPaises = "ArchivosTexto/paises.txt";
    ifstream ArchivoPaises(direccionPaises);

    // Si falla cerramos el programa
    if (ArchivoPaises.fail())
        exit(1);

    // Creamos el array que contendra los paises
    string* paises = new string[maxPaises];

    // Leer archivo
    while (getline(ArchivoPaises, paises[contadorPaises])){
        contadorPaises++;
        
        // Si el array se nos queda chico, lo incrementamos
        if (contadorPaises == maxPaises){
            maxPaises += 20;
            paises = rescaleVector(paises, maxPaises, contadorPaises);
        }
    }

    // Si el array quedo sobredimensionado, lo acortamos
    if (contadorPaises < maxPaises){
        maxPaises = contadorPaises;
        paises = rescaleVector(paises, maxPaises, contadorPaises);
    }

    atributos->setAtributos(paises, maxPaises);
    ArchivoPaises.close();
}

string* Juego::rescaleVector(string* oldVector, int max, int cont){
    string* newVector = new string[max];
    for (int i = 0; i < cont; i++)
        newVector[i] = oldVector[i];

    delete[] oldVector;
    return newVector;
}

reglas* Juego::getReglas(){
    return this->rules;
}