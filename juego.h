#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include "Reglas/reglasnivel5.h"
#include "Generadores/colanpc.h"
#include "SaveSlots/PlayerStats.h"
#include "Niveles/lectorniveles.h"

// Falta completar
class Juego: public QObject{
    Q_OBJECT

signals:
    void Log(QString);

public:
    Juego();
    void setDificultad(int dificultad);

    // Preparar Juego
    void PrepararJuego(int Nivel, int Dificultad); // Modo normal por default
    void PrepararJuego(PlayerStats);
    void PrepararJuego(int Nivel, int Dificultad, quint32 SeedPersonalizada);
    void setDefaultStats();

    // Esto despues lo eliminamos
    Reglas* getReglas(int numero);
    ColaNPC *getCola();
    PlayerStats getDatosJugador();
    PlayerStats getEmptyDatosJugador();
    void updateDatosJugador(PlayerStats &stats);

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

    quint32 getSemillaMadre() const;

private:
    quint32 SemillaMadre;
    void setReglasSeed();
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
    LectorNiveles lectorNiveles;
    const QString NIVEL1 = ":/Niveles/Nivel1/Nivel1Settings.txt";
    const QString NIVEL2 = ":/Niveles/Nivel2/Nivel2Settings.txt";
    const QString NIVEL3 = ":/Niveles/Nivel3/Nivel3Settings.txt";
    const QString NIVEL4 = ":/Niveles/Nivel4/Nivel4Settings.txt";
    const QString NIVEL5 = ":/Niveles/Nivel5/Nivel5Settings.txt";
    int CantNPCS[5]; // 0: Aldeanos, 1: Refugiados, 2: Diplomaticos, 3: Revolucionarios, 4: NPCs falsos

    void InicializarNivel1();
    void InicializarNivel2();
    void InicializarNivel3();
    void InicializarNivel4();
    void InicializarNivel5();
    void RandomizarParametros();
    void setUpNivel(int Nivel);

    // Reglas
    ReglasNivel1 reglasLVL1;
    ReglasNivel2 reglasLVL2;
    ReglasNivel3 reglasLVL3;
    ReglasNivel4 reglasLVL4;
    ReglasNivel5 reglasLVL5;
    Reglas * reglas[5] = {&reglasLVL1, &reglasLVL2, &reglasLVL3, &reglasLVL4, &reglasLVL5};
};

#endif // JUEGO_H
