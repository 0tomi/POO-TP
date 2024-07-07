#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglasnivel5.h"
#include "AtributosComunes/atributoscomunes.h"
#include "Generadores/colanpc.h"

// Falta completar
class Juego{
public:
    Juego();
    void set();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();

private:
    int SocialCreditsEarnedInLevel;
    int TotalSocialCredits;

    ColaNPC* Cola;

    // Atributos
    AtributosComunes* atributos;

    // Reglas
    Reglas* rules[5];
};

#endif // JUEGO_H
