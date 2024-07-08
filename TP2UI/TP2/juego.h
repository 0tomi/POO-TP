#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglasnivel5.h"
#include "AtributosComunes/atributoscomunes.h"
#include "Generadores/colanpc.h"

// Falta completar
class Juego{
public:
    Juego();
    void setNivel(int nivel);
    void NextLevel();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();

private:
    int NivelActual;

    // Estadisticas del player
    int SocialCreditsEarnedInLevel;
    int TotalSocialCredits;
    int Multas;
    int CantidadNPCsRechazados;
    int CantidadNPCsAceptados;

    ColaNPC* Cola;

    // Niveles:
    void setUpNivel0();
    void setUpNivel1();
    void setUpNivel2();
    void setUpNivel3();
    void setUpNivel4();

    // Atributos
    AtributosComunes* atributos;

    // Reglas
    Reglas* rules[5];
};

#endif // JUEGO_H
