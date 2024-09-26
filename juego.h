#ifndef JUEGO_H
#define JUEGO_H

#include "Reglas/reglasnivel5.h"
#include "Generadores/colanpc.h"
#include "SaveSlots/PlayerStats.h"

// Falta completar
class Juego{
public:
    Juego();
    void setDificultad(int dificultad);

    // Preparar Juego
    void PrepararJuego(int Dificultad);
    void PrepararJuego(int Nivel, int Dificultad); // Modo normal por default
    void PrepararJuego(PlayerStats);
    void setDefaultStats();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();

    // A futuro para cuando tengamos la funcion de guardar partida
    void SetPartida(string DireccionPartida);
    void GuardarPartida();

    // Evaluar acciones del jugador
    bool EvaluarDecision(bool& Veredicto, int TipoNPC, bool ValidezNPC, bool DecisionJugador);

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
    bool RestarSocialCredits(int TipoNPC);

    // Caracteristicas del nivel
    int MaxMultas;
    float BonificadorGanarCreditosDificultad;
    float BonificadorPerderCreditosDificultad;

    ColaNPC Cola;

    // Niveles:
    void setUpNivel1();
    void setUpNivel2();
    void setUpNivel3();
    void setUpNivel4();
    void setUpNivel5();

    // Reglas
    ReglasNivel1 reglasLVL1;
    ReglasNivel2 reglasLVL2;
    ReglasNivel3 reglasLVL3;
    ReglasNivel4 reglasLVL4;
    ReglasNivel5 reglasLVL5;
    Reglas * reglas[5] = {&reglasLVL1, &reglasLVL2, &reglasLVL3, &reglasLVL4, &reglasLVL5};
};

#endif // JUEGO_H
