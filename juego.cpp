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
void Juego::PrepararJuego(int Nivel, int Dificultad)
{
    this->SemillaMadre = QTime::currentTime().msec();
    emit Log("Semilla de inicio de juego: " + QString::number(SemillaMadre));
    setReglasSeed();
    NivelActual = Nivel;
    setDificultad(Dificultad);

    // Reseteamos la cantidad ganada en el nivel
    setDefaultStats();
    this->setUpNivel(Nivel);
}

void Juego::PrepararJuego(int Nivel, int Dificultad, quint32 SeedPersonalizada)
{
    this->SemillaMadre = SeedPersonalizada;
    emit Log("Semilla de inicio de juego: " + QString::number(SemillaMadre));
    setReglasSeed();
    NivelActual = Nivel;
    setDificultad(Dificultad);

    // Reseteamos la cantidad ganada en el nivel
    this->SocialCreditsEarnedInLevel = 0;
    this->setUpNivel(Nivel);
}

void Juego::PrepararJuego(PlayerStats stats)
{
    PrepararJuego(stats.Nivel, stats.Dificultad, stats.seed);

    // Le damos al jugador las estadisticas que posee.
    TotalSocialCredits = stats.TotalSocialCredits;
    Multas = stats.Multas;
    CantidadNPCsRechazados = stats.CantidadNPCsRechazados;
    CantidadNPCsAceptados = stats.CantidadNPCsAceptados;
    CantidadERRORES = stats.CantidadErrores;

    if (stats.tiempoPartida > 0)
        SocialCreditsEarnedInLevel = stats.socialCreditsEarnedInLVL;
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
    CantidadERRORES = 0;
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

    if (!Veredicto)
        CantidadERRORES++;

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
void Juego::setUpNivel(int Nivel)
{
    if (Nivel > 5)
        Nivel = 5;

    const QString Niveles[] = {NIVEL1, NIVEL2, NIVEL3, NIVEL4, NIVEL5};
    auto Nivel2Cargar = &Niveles[Nivel - 1];

    lectorNiveles.leerDatos(*Nivel2Cargar);

    InicializarNivel1();
    if (Nivel > 1)
        InicializarNivel2();
    if (Nivel > 2)
        InicializarNivel3();
    if (Nivel > 3)
        InicializarNivel4();
    if (Nivel == 5)
        InicializarNivel5();
    if (Nivel > 5)
        RandomizarParametros();

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

void Juego::InicializarNivel2()
{
    int CantidadPaisesPermitidos = lectorNiveles.obtenerValor("Cantidad de paises de paso permitidos");
    reglasLVL2.generar_PaisesPermitidos(CantidadPaisesPermitidos);
}

void Juego::InicializarNivel3()
{
    int Cantidad = lectorNiveles.obtenerValor("Cantidad maxima de acompaniantes permitidos");
    reglasLVL3.set_MaxAcompaniantes(Cantidad);
}

void Juego::InicializarNivel4()
{
    int CantidadPaises = lectorNiveles.obtenerValor("Cantidad de paises de paso permitidos");
    reglasLVL4.generar_PaisesPaso(CantidadPaises);
    int CantidadOcupaciones = lectorNiveles.obtenerValor("Cantidad de ocupaciones permitidos");
    reglasLVL4.generar_Ocupacion(CantidadOcupaciones);
    int CantidadBienes = lectorNiveles.obtenerValor("Cantidad de bienes transportados permitidos");
    reglasLVL4.generar_BienesTransportados(CantidadBienes);
}

void Juego::InicializarNivel5()
{
    int Cantidad = lectorNiveles.obtenerValor("Cantidad de objetos permitidos");
    reglasLVL5.generar_ObjetosPermitidos(Cantidad);
}

void Juego::RandomizarParametros()
{
    QRandomGenerator rand;
    for (int i = 0; i < 4; i++)
        CantNPCS[i] = rand.bounded(20);
    reglasLVL3.generar_MaxAcompaniantes();
}


/// #################################### GETTERS & SETTERS ###################################################
Reglas* Juego::getReglas(int numero){
    return reglas[numero];
}

ColaNPC *Juego::getCola()
{
    return &Cola;
}

PlayerStats Juego::getDatosJugador()
{
    PlayerStats stats;
    stats.Nivel = this->NivelActual;
    stats.Dificultad = this->Dificultad;
    stats.CantidadNPCsAceptados = this->CantidadNPCsAceptados;
    stats.CantidadNPCsRechazados = this->CantidadNPCsRechazados;
    stats.CantidadErrores = this->CantidadERRORES;
    stats.Multas = this->Multas;
    stats.TotalSocialCredits = this->TotalSocialCredits;
    stats.socialCreditsEarnedInLVL = 0;
    stats.seed = this->SemillaMadre;
    stats.tiempoFondo = 0; stats.tiempoPartida = 0; stats.cantNPCsPasados = 0; stats.cantidadTiempoDia = 0;

    return stats;
}

PlayerStats Juego::getEmptyDatosJugador()
{
    return {0,0,0,0,0,0,0,0,0,0,0,0,this->SemillaMadre};
}

void Juego::updateDatosJugador(PlayerStats &stats)
{
    stats.CantidadNPCsAceptados = this->CantidadNPCsAceptados;
    stats.CantidadNPCsRechazados = this->CantidadNPCsRechazados;
    stats.CantidadErrores = this->CantidadERRORES;
    stats.Multas = this->Multas;
    stats.TotalSocialCredits = this->TotalSocialCredits;
    stats.socialCreditsEarnedInLVL = this->SocialCreditsEarnedInLevel;
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

quint32 Juego::getSemillaMadre() const
{
    return SemillaMadre;
}

void Juego::setReglasSeed()
{
    for (int i = 0; i < 5; ++i)
        reglas[i]->setSeed(this->SemillaMadre);
}

int Juego::getCantidadERRORES() const
{
    return CantidadERRORES;
}
