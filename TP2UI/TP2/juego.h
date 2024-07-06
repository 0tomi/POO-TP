#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglasnivel5.h"
#include "AtributosComunes/atributoscomunes.h"

// Falta completar
class Juego{
public:
    Juego();
    void start();
    void set();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);

private:
    // Atributos
    AtributosComunes* atributos;

    // Reglas
    Reglas* rules[5];
};

#endif // JUEGO_H
