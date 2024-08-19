#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglasnivel5.h"
#include "AtributosComunes/atributoscomunes.h"
#include "Generadores/colanpc.h"

// Falta completar
class Juego{
public:
    Juego();
    void setDificultad(int dificultad);
    void PrepararJuego(int Nivel = 1, int Dificultad = 2); // Modo normal por default
    void setDefaultStats();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();
    AtributosComunes *getAtributos();

    // A futuro para cuando tengamos la funcion de guardar partida
    void SetPartida(string DireccionPartida);
    void GuardarPartida();

    // Evaluar acciones del jugador
    void EvaluarDecision(int TipoNPC, bool ValidezNPC, bool DecisionJugador);

    // Getters y setters de las estadisticas
    int getSocialCreditsEarnedInLevel() const;
    int getTotalSocialCredits() const;

    int getMultas() const;
    void addMulta();

    int getCantidadNPCsRechazados() const;
    void addNPCrechazado();

    int getCantidadNPCsAceptados() const;
    void addNPCaceptado();

    int getMaxMultas() const;

    int getNivelActual() const;

    int getDificultad() const;

private:
    int NivelActual;
    int Dificultad;

    // Partida guardada o a guardar
    string DireccionPartida;

    // Estadisticas del player
    int SocialCreditsEarnedInLevel;
    int TotalSocialCredits;
    int Multas;
    int CantidadNPCsRechazados;
    int CantidadNPCsAceptados;
    void SumarSocialCredits(int TipoNPC);
    void RestarSocialCredits(int TipoNPC);

    // Caracteristicas del nivel
    int MaxMultas;
    float BonificadorGanarCreditosDificultad;
    float BonificadorPerderCreditosDificultad;

    ColaNPC Cola;

    // Niveles:
    void ResetJuego();
    void setUpNivel1();
    void setUpNivel2();
    void setUpNivel3();
    void setUpNivel4();
    void setUpNivel5();

    // Atributos
    AtributosComunes atributos;

    // Reglas
    ReglasNivel1 reglasLVL1;
    ReglasNivel2 reglasLVL2;
    ReglasNivel3 reglasLVL3;
    ReglasNivel4 reglasLVL4;
    ReglasNivel5 reglasLVL5;
    Reglas * reglas[5] = {&reglasLVL1, &reglasLVL2, &reglasLVL3, &reglasLVL4, &reglasLVL5};
};

#endif // JUEGO_H
