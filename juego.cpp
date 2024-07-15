#include "lectorArchivos.h"
#include "juego.h"
#include <QDebug>

Juego::Juego(){
    this->atributos = new AtributosComunes();

    // Leemos los paises y los guardamos en el array de paises
    LectorArchivos LA(":/Resources/ArchivosTexto/paises.txt");
    this->atributos->setAtributos(LA.getArray(), LA.getTopeArray());

    PrepararJuego(0);
}

void Juego::PrepararJuego(int Reset)
{
    // Seteamos las reglas del juego, pasando el array de paises.
    rules[0] = new ReglasNivel1(atributos);
    rules[1] = new ReglasNivel2(rules[0]);
    rules[2] = new ReglasNivel3(rules[1]);
    rules[3] = new ReglasNivel4(rules[2]);
    rules[4] = new ReglasNivel5(rules[3]);

    if (!Reset)
        Cola = new ColaNPC(atributos, rules);
    else
        Cola->actualizarReglas(rules, 0);


    NivelActual = 1;
    // Test
    Cola->addNPC(NivelActual,2,2,2,2, 3);
    // setUpNivel1();

    // Seteamos las estadisticas del jugador.
    SocialCreditsEarnedInLevel = 0;
    TotalSocialCredits = 0;
    Multas = 0;
    CantidadNPCsRechazados = 0;
    CantidadNPCsAceptados = 0;

    setDificultad(1);
}

void Juego::setDificultad(int dificultad)
{
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

void Juego::setNivel(int nivel)
{
    if (nivel < 5){
        NivelActual = nivel;
        Cola->vaciarCola();
    }
}

void Juego::NextLevel()
{
    NivelActual++;
    this->SocialCreditsEarnedInLevel = 0;
    Cola->nextNivel(NivelActual);
    Cola->vaciarCola();

    switch (NivelActual){
    case 2: setUpNivel2();
        break;
    case 3: setUpNivel3();
        break;
    case 4: setUpNivel4();
        break;
    case 5: setUpNivel5();
        break;
    }
}

void Juego::ResetJuego()
{
    SocialCreditsEarnedInLevel = 0;
    TotalSocialCredits = 0;
    Multas = 0;
    CantidadNPCsRechazados = 0;
    CantidadNPCsAceptados = 0;

    for (int i = 0; i < 5; i++)
        delete rules[i];

    PrepararJuego(1);
}

Reglas* Juego::getReglas(int numero){
    return (numero < 5)? rules[numero]: NULL;
}

ColaNPC *Juego::getCola()
{
    return this->Cola;
}

int Juego::getSocialCreditsEarnedInLevel() const
{
    return SocialCreditsEarnedInLevel;
}

void Juego::EvaluarDecision(int TipoNPC, bool ValidezNPC, bool DecisionJugador)
{
    if (TipoNPC == 3 && DecisionJugador)
        RestarSocialCredits(TipoNPC);
    else
        if (DecisionJugador == ValidezNPC)
            SumarSocialCredits(TipoNPC);
        else
            RestarSocialCredits(TipoNPC);

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
    TotalSocialCredits += SocialCreditsEarnedInLevel;
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
    TotalSocialCredits -= SocialCreditsEarnedInLevel;
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

void Juego::setUpNivel1()
{
    // A desarrollar
    Cola->addNPC(1, 10,10,4,0,6);
}

void Juego::setUpNivel2()
{
    // A desarrollar
    Cola->addNPC(2, 10,10,4,0,6);
}

void Juego::setUpNivel3()
{
    // A desarrollar
    Cola->addNPC(3, 10,10,4,0,6);
}

void Juego::setUpNivel4()
{
    // A desarrollar
    Cola->addNPC(4, 10,10,4,0,6);
}

void Juego::setUpNivel5()
{
    // A desarrollar
    Cola->addNPC(5, 10,10,4,0,6);
}
