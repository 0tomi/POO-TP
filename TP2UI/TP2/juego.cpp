#include "lectorArchivos.h"
#include "juego.h"

Juego::Juego(){
    this->atributos = new AtributosComunes();

    // Leemos los paises y los guardamos en el array de paises
    LectorArchivos LA("../TP2/ArchivosTexto/paises.txt");
    this->atributos->setAtributos(LA.getArray(), LA.getTopeArray());

    // Seteamos las reglas del juego, pasando el array de paises.
    rules[0] = new ReglasNivel1(atributos);
    rules[1] = new ReglasNivel2(rules[0]);
    rules[2] = new ReglasNivel3(rules[1]);
    rules[3] = new ReglasNivel4(rules[2]);
    rules[4] = new ReglasNivel5(rules[3]);
}

Reglas* Juego::getReglas(int numero){
    return (numero < 5)? rules[numero]: NULL;
}
