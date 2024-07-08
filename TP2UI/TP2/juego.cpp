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

    Cola = new ColaNPC(atributos, rules[0]);

    NivelActual = 0;
    // Test
    Cola->addNPC(2,1,1,0, 1);
    // setUpNivel0();
}

void Juego::setNivel(int nivel)
{
    if (nivel < 5){
        NivelActual = nivel;
        Cola->actualizarReglas(rules[nivel], nivel);
        Cola->vaciarCola();
    }
}

void Juego::NextLevel()
{
    NivelActual++;
    Cola->actualizarReglas(rules[NivelActual], NivelActual);
    Cola->vaciarCola();

    switch (NivelActual){
    case 1: setUpNivel1();
        break;
    case 2: setUpNivel2();
        break;
    case 3: setUpNivel3();
        break;
    case 4: setUpNivel4();
        break;
    }
}

Reglas* Juego::getReglas(int numero){
    return (numero < 5)? rules[numero]: NULL;
}

ColaNPC *Juego::getCola()
{
    return this->Cola;
}

void Juego::setUpNivel0()
{
    // A desarrollar
    Cola->addNPC(10,10,4,0,6);
}

void Juego::setUpNivel1()
{
    // A desarrollar
    Cola->addNPC(10,10,4,0,6);
}

void Juego::setUpNivel2()
{
    // A desarrollar
    Cola->addNPC(10,10,4,0,6);
}

void Juego::setUpNivel3()
{
    // A desarrollar
    Cola->addNPC(10,10,4,0,6);
}

void Juego::setUpNivel4()
{
    // A desarrollar
    Cola->addNPC(10,10,4,0,6);
}
