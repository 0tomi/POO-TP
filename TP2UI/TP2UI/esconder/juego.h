#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglas.h"
#include "AtributosComun/atributoscomunes.h"

// Falta completar
class Juego{
public:
    Juego();
    void start();
    void set();

    // Esto despues lo eliminamos
    reglas* getReglas();

private:
    // Atributos
    AtributosComunes* atributos;

    // Reglas
    reglas* rules;
};

#endif // JUEGO_H
