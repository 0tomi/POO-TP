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
    void setDificultad(int dificultad);
    void NextLevel();
    void ResetJuego();
    void PrepararJuego(int Reset, int Dificultad = 2); // Modo normal por default

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();

    // A futuro para cuando tengamos la funcion de guardar partida
    void SetPartida(string DireccionPartida);
    void GuardarPartida();

    // Getters y setters de las estadisticas
    int getSocialCreditsEarnedInLevel() const;
    void EvaluarDecision(int TipoNPC, bool ValidezNPC, bool DecisionJugador);
    void SumarSocialCredits(int TipoNPC);
    void RestarSocialCredits(int TipoNPC);

    int getTotalSocialCredits() const;

    int getMultas() const;
    void addMulta();

    int getCantidadNPCsRechazados() const;
    void addNPCrechazado();

    int getCantidadNPCsAceptados() const;
    void addNPCaceptado();

    int getMaxMultas() const;

private:
    int NivelActual;

    // Partida guardada o a guardar
    string DireccionPartida;

    // Estadisticas del player
    int SocialCreditsEarnedInLevel;
    int TotalSocialCredits;
    int Multas;
    int CantidadNPCsRechazados;
    int CantidadNPCsAceptados;

    // Caracteristicas del nivel
    int MaxMultas;
    float BonificadorGanarCreditosDificultad;
    float BonificadorPerderCreditosDificultad;

    ColaNPC* Cola;

    // Niveles:
    void setUpNivel1();
    void setUpNivel2();
    void setUpNivel3();
    void setUpNivel4();
    void setUpNivel5();

    // Atributos
    AtributosComunes* atributos;

    // Reglas
    Reglas* rules[5];
};

#endif // JUEGO_H
