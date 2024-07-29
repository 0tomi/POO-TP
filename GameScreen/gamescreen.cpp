#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GameScreen::GameScreen(Juego* newJuego, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    juego = newJuego;
    Pausado = false;

    setUpLibroReglas();

    pantallaPerdiste = new PantallaPerdiste(this);
    pantallaPerdiste->setFixedSize(1920,1080);
    pantallaPerdiste->hide();

    // Seteamos el juego, y obtenemos la cola de NPCs.
    ColaNPC* Cola = juego->getCola();

    tiempoPartida.setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    GestorNPC.setUp(ui->Escritorio, ui->FondoNPC, Cola);
    GestorNPC.setUpDocsIcono(ui->MesaAzul);

    // Agregamos el libro de reglas
    // ACA ES DONDE SE DEBERIA PASAR POR CONSTRUCTOR EL PUNTERO DE JUEGO
    libroReglasUI = new libroreglas(juego, ui->Escritorio);

    SpawnearBotones();
    SetearConexionesDocumentos();
    RealizarConexionesPrincipales();
    BloquearBotones(true);
}

GameScreen::~GameScreen()
{
    delete ui;
    delete BotonAprobar;
    delete BotonRechazar;
    delete BotonCentrar;
    delete pantallaPerdiste;
}

void GameScreen::setUpLibroReglas()
{
    MostrandoReglas = false;
    bloquearBotonReglas.setSingleShot(true);
    connect(&bloquearBotonReglas, &QTimer::timeout, [this]() {
        ui->aparecerReglas->setEnabled(true);
    });
}
/// #################################### BOTONES ###################################################
void GameScreen::SpawnearBotones()
{
    // Añadimos los botones a la escena
    QString BotonAceptarDesbloqueado = ":/Resources/MaterialPantallas/BotonAprobarSinApretar.png";
    QString BotonAceptarBloqueado = ":/Resources/MaterialPantallas/BotonAprobarApretado.png";
    QString BotonRechazarDesbloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarNoApretado .png";
    QString BotonRechazarBloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarApretado.png";
    QString BotonCentrarBlock = ":/Resources/MaterialPantallas/BotonCentrarBloqueado.png";
    QString BotonCentrarDesblock = ":/Resources/MaterialPantallas/BotonCentrarDesbloqueado.png";

    BotonAprobar = new BotonesCustom(BotonAceptarDesbloqueado, BotonAceptarBloqueado, ui->ContenedorBotones);
    BotonRechazar = new BotonesCustom(BotonRechazarDesbloqueado, BotonRechazarBloqueado, ui->ContenedorBotones);
    BotonCentrar = new BotonesCustom(BotonCentrarDesblock, BotonCentrarBlock,ui->ContenedorBotones);
    EspaciadorBotones = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    BotonAprobar->resize(200,125);
    BotonRechazar->resize(200,125);

    BotonAprobar->SetTiempoBloqueo(2500);
    BotonRechazar->SetTiempoBloqueo(2500);
    BotonCentrar->SetTiempoBloqueo(1000);

    ui->ContenedorBotones->layout()->addWidget(BotonCentrar);
    ui->ContenedorBotones->layout()->addItem(EspaciadorBotones);
    ui->ContenedorBotones->layout()->addWidget(BotonAprobar);
    ui->ContenedorBotones->layout()->addWidget(BotonRechazar);
}

void GameScreen::SetearConexionesDocumentos()
{
    DocsIconUI * setup  =  GestorNPC.getDocsIcono();
    // Bloqueamos los botones al estar el documento cerrado o abierto.
    connect(setup, &DocsIconUI::Abierto, [this]() {
        this->DesbloquearBotones();
    });

    connect(setup, &DocsIconUI::Cerrado, [this]() {
        this->BloquearBotones(true);
    });
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    BotonCentrar->BloquearBoton(Bloqueo);
    BotonAprobar->BloquearBoton(Bloqueo);
    BotonRechazar->BloquearBoton(Bloqueo);
}

void GameScreen::DesbloquearBotones()
{
    BloquearBotones(false);
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Centrar();
}

/// #################################### CONEXIONES ###################################################

void GameScreen::RealizarConexionesPrincipales()
{
    // Conecto los botones para que segun lo que haga el usuario, se evalue una cosa u otra.
    connect(BotonAprobar, &BotonesCustom::BotonApretado, this, &GameScreen::Acepto);
    connect(BotonRechazar, &BotonesCustom::BotonApretado, this, &GameScreen::Rechazo);

    // Conectamos boton de centrar para centrar el documento.
    connect(BotonCentrar, &BotonesCustom::BotonApretado, &GestorNPC, &GestorNPCsUI::CentrarDocumentos);

    connect(pantallaPerdiste, &PantallaPerdiste::AnimacionTermino, this, &GameScreen::Decidir);

    // Conectamos nuestro cronometro rustico
    connect(&TiempoDia, &QTimer::timeout, this, &GameScreen::ActualizarTiempo);

    // Conectamos el temporizador de partida para terminar la partida.
    connect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);

    // Conectamos el quedarse sin npcs con el final de la partida
    connect(&GestorNPC, &GestorNPCsUI::ColaTerminada, this, &GameScreen::FinalDePartida);

    // Conectmaos el boton de reglas
    connect(ui->aparecerReglas, &QPushButton::clicked, this, &GameScreen::MostrarReglas);
}

/// #################################### PREPRARAR JUEGO ###################################################

void GameScreen::PrepararJuego(int Nivel, int Dificultad)
{
    qDebug() << "Nivel actual: " << Nivel;
    juego->PrepararJuego(Nivel, Dificultad);
    libroReglasUI->setUpLevel(Nivel);
    // more stuff to do
    if (Nivel > 1)
        GestorNPC.setUpNuevoNivel(Nivel);
}

void GameScreen::EmpezarJuego()
{
    tiempoPartida.start(8*60*1000); // 8 Minutos

    // Seteamos el pasaje de tiempo en el juego
    TiempoDia.start(52 * 1000); // Cada 52 segundos el tiempo cambia
    TiempoActual = 0;
    ActualizarTiempo();

    GestorNPC.EmpezarJuego();
    GestorNPC.Entrar();
}

/// #################################### REINICIAR ###################################################

void GameScreen::Restart()
{
    juego->setDefaultStats();
    /// A futuro un reset donde cambiamos las reglas
}

/// #################################### PAUSAR JUEGO ###################################################

void GameScreen::PausarJuego()
{
    GestorNPC.Pausar();
    tiempoRestante = tiempoPartida.remainingTime();
    tiempoPartida.stop();
    Pausado = true;
}

void GameScreen::ReanudarJuego()
{
    GestorNPC.Reanudar();
    tiempoPartida.start(tiempoRestante);
    GestorNPC.CentrarNPC();

    Pausado = false;
}

void GameScreen::Centrar()
{
    GestorNPC.CentrarNPC();
}

/// #################################### FINAL DE PARTIDA ###################################################

void GameScreen::FinalDePartida()
{
    // a desarrollar
    GestorNPC.TerminoNivel();

    if (MostrandoReglas)
        MostrarReglas();

    if (tiempoPartida.isActive())
        tiempoPartida.stop();
    TiempoDia.stop();


    if (!Pausado){
        if (juego->getTotalSocialCredits() < 0)
           pantallaPerdiste->Iniciar(true);
        else pantallaPerdiste->Iniciar(false);
    } else
        qDebug() << "Se detuvo forzosamente el juego";
}

void GameScreen::Decidir()
{
    if (juego->getTotalSocialCredits() < 0)
        emit NivelTerminado(true);
    else emit NivelTerminado(false);
}

void GameScreen::ActualizarTiempo()
{
    ui->Pasillo->setCurrentIndex(TiempoActual);
    TiempoActual++;
    if (TiempoActual > 9)
        TiempoActual = 0;
}

/// #################################### DECISIONES DEL JUGADOR ###################################################

void GameScreen::Acepto()
{
    juego->addNPCaceptado();
    SelloDocumento(true);
}

void GameScreen::Rechazo()
{
    juego->addNPCrechazado();
    SelloDocumento(false);
}

void GameScreen::SelloDocumento(bool Boton)
{
    GestorNPC.Salir(Boton);

    juego->EvaluarDecision(GestorNPC.getTipo(), GestorNPC.getValidez(), Boton);

    qDebug() << "Puntaje actual: " << juego->getSocialCreditsEarnedInLevel();
}

/// #################################### Libro de Reglas ###################################################
void GameScreen::MostrarReglas()
{
    ui->aparecerReglas->setEnabled(false);
    bloquearBotonReglas.start(500);

    if (MostrandoReglas){
        libroReglasUI->Sacar();
        MostrandoReglas = false;
    } else {
        libroReglasUI->Entrar();
        MostrandoReglas = true;
    }
}

/// #################################### EVENTOS DE VENTANA ###################################################

void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange){
        if (GestorNPC.MostrandoElNPC())
            GestorNPC.Centrar();
        if (pantallaPerdiste->getMostrandoPantalla())
            pantallaPerdiste->setFixedSize(width(), height());
    }
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Centrar();
    if (pantallaPerdiste->getMostrandoPantalla())
        pantallaPerdiste->setFixedSize(width(), height());
}



