#include "juego.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
Juego::Juego():
    reglasLVL1()
    , reglasLVL2(), reglasLVL3()
    , reglasLVL4(), reglasLVL5()
    , Cola()
{
    this->SemillaMadre = QTime::currentTime().msec();
    NivelActual = 1;
    setDefaultStats();
}

/// #################################### PREPRARAR JUEGO ###################################################
void Juego::PrepararJuego(int Dificultad)
{
    this->SemillaMadre = QTime::currentTime().msec();
    emit Log("Semilla de inicio de juego: " + QString::number(SemillaMadre));
    setReglasSeed();
    NivelActual = 1;
    setDificultad(Dificultad);
    setDefaultStats();
    setUpNivel1();
}

void Juego::PrepararJuego(int Nivel, int Dificultad)
{
    this->SemillaMadre = QTime::currentTime().msec();
    emit Log("Semilla de inicio de juego: " + QString::number(SemillaMadre));
    setReglasSeed();
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
bool Juego::EvaluarDecision(bool& Veredicto, int TipoNPC, bool ValidezNPC, bool DecisionJugador)
{
    Veredicto = true;
    bool Multa = false;
    bool AprobarRefugiado = (TipoNPC == 3) && (DecisionJugador);
    if (AprobarRefugiado){
        Multa = RestarSocialCredits(TipoNPC);
        Veredicto = false;
    } else {
        if ((DecisionJugador != ValidezNPC) && TipoNPC != 3){
            Multa = RestarSocialCredits(TipoNPC);
            Veredicto = false;
        } else
            SumarSocialCredits(TipoNPC);
    }
    return Multa;
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

bool Juego::RestarSocialCredits(int Tipo)
{
    bool Multa = false;
    int SocialCredits;
    switch(Tipo){
    case 0: SocialCredits = 15;
        break;
    case 1: SocialCredits = 25;
        break;
    case 2: SocialCredits = 25;
        addMulta();
        Multa = true;
        break;
    default: SocialCredits = 25;
        addMulta();
        Multa = true;
        break;
    };

    SocialCreditsEarnedInLevel -= (SocialCredits * BonificadorPerderCreditosDificultad);
    TotalSocialCredits -= (SocialCredits * BonificadorGanarCreditosDificultad);
    return Multa;
}

/// #################################### SETUP DE NIVELES ###################################################
void Juego::setUpNivel1()
{
    lectorNiveles.leerDatos(":/Niveles/Nivel1/Nivel1Settings.txt");
    this->InicializarNivel1();

    Cola.Inicializar(NivelActual, Dificultad, reglas, this->SemillaMadre);

    // Aldeanos, Refugiados, Diplomaticos, Revolucionarios, Cantidad de NPCs falsos.
    Cola.addNPC(NivelActual, CantNPCS[0], CantNPCS[1], CantNPCS[2], CantNPCS[3], CantNPCS[4]);
}

void Juego::InicializarNivel1()
{
    QString Claves[] ={                                                                                                 // Indices:
        "Cantidad de aldeanos", "Cantidad de refugiados", "Cantidad de diplomaticos", "Cantidad de revolucionarios",    // 0,1,2,3
        "Cantidad de NPCs invalidos",                                                                                   // 4
        "Cantidad de paises validos", "Cantidad de estados civiles validos", "Rango de fechas de nacimiento validas",   // 5,6,7
        "Fecha minima valida de nacimiento", "Fecha maxima valida de nacimiento", "Duracion de estancia maxima permitida",  // 8,9,10
        "Cantidad de tipos de visitas permitidas" // 11
    };
    int Valores[12];

    for (int i = 0; i < 12; i++)
        Valores[i] = lectorNiveles.obtenerValor(Claves[i]);

    for (int i = 0; i < 5; i++)
        CantNPCS[i] = Valores[i];

    reglasLVL1.generar_Paises(Valores[5]);
    reglasLVL1.generar_EstadosCiviles(Valores[6]);
    if (!Valores[7])
        reglasLVL1.set_Fechas(Valores[8], Valores[9]);
    else reglasLVL1.generar_Fechas(Valores[7]);
    reglasLVL1.generar_DuracionEstancia(Valores[10]);
    reglasLVL1.generar_TiposVisita(Valores[11]);

}

void Juego::setUpNivel2()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel
    reglasLVL2.generar_PaisesPermitidos(6);
    Cola.Inicializar(NivelActual, Dificultad, reglas, this->SemillaMadre);
    Cola.addNPC(NivelActual, 7, 4, 2, 5, 5);
}

void Juego::setUpNivel3()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel
    reglasLVL2.generar_PaisesPermitidos(6);
    reglasLVL3.set_MaxAcompaniantes(2);
    Cola.Inicializar(NivelActual, Dificultad, reglas, this->SemillaMadre);
    Cola.addNPC(NivelActual, 8, 2, 3, 8, 6);
}

void Juego::setUpNivel4()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel

    Cola.Inicializar(NivelActual, Dificultad, reglas, this->SemillaMadre);
    Cola.addNPC(NivelActual, 8, 2, 3, 8, 6);
}

void Juego::setUpNivel5()
{
    // Aca previamente tocaria una lectura del nivel concreto a iniciar
    // donde obtengamos los datos que necesitamos para cada nivel

    Cola.Inicializar(NivelActual, Dificultad, reglas, this->SemillaMadre);
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

void Juego::setReglasSeed()
{
    for (int i = 0; i < 5; ++i)
        reglas[i]->setSeed(this->SemillaMadre);
}
