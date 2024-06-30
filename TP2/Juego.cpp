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

reglas* Juego::getReglas(){
    return this->rules;
}