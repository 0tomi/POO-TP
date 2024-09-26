#include "juego.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
Juego::Juego():
    reglasLVL1()
    , reglasLVL2(), reglasLVL3()
    , reglasLVL4(), reglasLVL5()
    , Cola()
{
    setDefaultStats();
}

/// #################################### PREPRARAR JUEGO ###################################################
void Juego::PrepararJuego(int Dificultad)
{
    NivelActual = 1;
    setDificultad(Dificultad);
    setDefaultStats();
    setUpNivel1();
}

void Juego::PrepararJuego(int Nivel, int Dificultad)
{
    NivelActual = Nivel;

    setDificultad(Dificultad);

    // Reseteamos la cantidad ganada en el nivel
    this->SocialCreditsEarnedInLevel = 0;
    // El else vendra cuando implementemos las partidas guardadas
    switch (Nivel) {
    case 1: setUpNivel1();
        break;
    case 2: setUpNivel2();
        break;
    case 3: setUpNivel3();
        break;
    case 4: setUpNivel4();
        break;
    default: setUpNivel5();
        break;
    }
}

void Juego::PrepararJuego(PlayerStats stats)
{
    PrepararJuego(stats.Nivel, stats.Dificultad);

    // Le damos al jugador las estadisticas que posee.
    SocialCreditsEarnedInLevel = 0;
    TotalSocialCredits = stats.TotalSocialCredits;
    Multas = stats.Multas;
    CantidadNPCsRechazados = stats.CantidadNPCsRechazados;
    CantidadNPCsAceptados = stats.CantidadNPCsAceptados;
}

void Juego::setDificultad(int dificultad)
{
    this->Dificultad = dificultad;
    switch (dificultad){
    // Modo facil
    case 1: MaxMultas = 6;
        BonificadorPerderCreditosDificultad = 0.5;
        BonificadorGanarCreditosDificultad = 1.5;
        break;
    // Modo DEMONIO
    case 3: MaxMultas = 2;
        BonificadorPerderCreditosDificultad = 1.5;
        BonificadorGanarCreditosDificultad = 0.5;
        break;
    // Modo Normal
    default:MaxMultas = 4;
        BonificadorPerderCreditosDificultad = 1;
        BonificadorGanarCreditosDificultad = 1;
        break;
    }
}

/// #################################### RESET JUEGO ###################################################
void Juego::setDefaultStats()
{
    // Seteamos las estadisticas del jugador.
    SocialCreditsEarnedInLevel = 0;
    TotalSocialCredits = 0;
    Multas = 0;
    CantidadNPCsRechazados = 0;
    CantidadNPCsAceptados = 0;
}

/// #################################### TOMA DE DECISIONES ###################################################
void Juego::EvaluarDecision(int TipoNPC, bool ValidezNPC, bool DecisionJugador)
{
    bool AprobarRefugiado = (TipoNPC == 3) && (DecisionJugador);
    if (AprobarRefugiado)
        RestarSocialCredits(TipoNPC);
    else
        if ((DecisionJugador != ValidezNPC) && TipoNPC != 3)
            RestarSocialCredits(TipoNPC);
        else
            SumarSocialCredits(TipoNPC);
}

void Juego::SumarSocialCredits(int Tipo)
{
    int SocialCredits;
    switch(Tipo){
    case 0: SocialCredits = 10;
        break;
    case 1: SocialCredits = 15;
        break;
    case 2: SocialCredits = 25;
        break;
    default: SocialCredits = 0;
        break;
    };

    SocialCreditsEarnedInLevel += (SocialCredits * BonificadorGanarCreditosDificultad);
    TotalSocialCredits += (SocialCredits * BonificadorGanarCreditosDificultad);
}

void Juego::RestarSocialCredits(int Tipo)
{
    int SocialCredits;
    switch(Tipo){
    case 0: SocialCredits = 15;
        break;
    case 1: SocialCredits = 25;
        break;
    case 2: SocialCredits = 25;
        addMulta();
        break;
    default: SocialCredits = 25;
        addMulta();
        break;
    };

    SocialCreditsEarnedInLevel -= (SocialCredits * BonificadorPerderCreditosDificultad);
    TotalSocialCredits -= (SocialCredits * BonificadorGanarCreditosDificultad);
}

/// #################################### SETUP DE NIVELES ###################################################
/// A futuro estaria bueno hacer que la cantidad de NPCs que pueda salir sea random,
/// pero por motivos de testeo lo vamos a dejar asi.
void Juego::setUpNivel1()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel
    Cola.Inicializar(NivelActual, Dificultad, reglas);

    // Aldeanos, Refugiados, Diplomaticos, Revolucionarios, Cantidad de NPCs falsos.
    Cola.addNPC(NivelActual, 5, 3, 4, 2, 4);
}

void Juego::setUpNivel2()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel
    reglasLVL2.generar_PaisesPermitidos(6);
    Cola.Inicializar(NivelActual, Dificultad, reglas);
    Cola.addNPC(NivelActual, 7, 4, 2, 5, 5);
}

void Juego::setUpNivel3()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel

    Cola.Inicializar(NivelActual, Dificultad, reglas);
    Cola.addNPC(NivelActual, 8, 2, 3, 8, 6);
}

void Juego::setUpNivel4()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel

    Cola.Inicializar(NivelActual, Dificultad, reglas);
    Cola.addNPC(NivelActual, 8, 2, 3, 8, 6);
}

void Juego::setUpNivel5()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel

    Cola.Inicializar(NivelActual, Dificultad, reglas);
    Cola.addNPC(NivelActual, 8, 2, 3, 8, 6);
}

/// #################################### GETTERS & SETTERS ###################################################
Reglas* Juego::getReglas(int numero){
    return reglas[numero];
}

ColaNPC *Juego::getCola()
{
    return &Cola;
}

int Juego::getSocialCreditsEarnedInLevel() const
{
    return SocialCreditsEarnedInLevel;
}

int Juego::getTotalSocialCredits() const
{
    return TotalSocialCredits;
}

int Juego::getMultas() const
{
    return Multas;
}

void Juego::addMulta()
{
    Multas++;
}

int Juego::getCantidadNPCsRechazados() const
{
    return CantidadNPCsRechazados;
}

void Juego::addNPCrechazado()
{
    CantidadNPCsRechazados++;
}

int Juego::getCantidadNPCsAceptados() const
{
    return CantidadNPCsAceptados;
}

void Juego::addNPCaceptado()
{
    CantidadNPCsAceptados++;
}

int Juego::getMaxMultas() const
{
    return MaxMultas;
}

int Juego::getNivelActual() const
{
    return NivelActual;
}

int Juego::getDificultad() const
{
    return Dificultad;
}
