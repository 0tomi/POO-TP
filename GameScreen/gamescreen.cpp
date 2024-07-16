#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(Juego* newJuego, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Seteamos el juego, y obtenemos la cola de NPCs.
    juego = new Juego;
    ColaNPC* Cola = juego->getCola();

    temporizadorBotones.setSingleShot(true);
    tiempoPartida.setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    GestorNPC.setUp(ui->Escritorio, ui->FondoNPC, Cola);

    SpawnearBotones();
    RealizarConeccionesPrincipales();
    BloquearBotones(true);
}

GameScreen::~GameScreen()
{
    delete ui;
    delete BotonAprobar;
    delete BotonRechazar;
    delete BotonCentrar;
}

void GameScreen::RealizarConeccionesPrincipales()
{
    // Conecto los botones para que segun lo que haga el usuario, se evalue una cosa u otra.
    connect(BotonAprobar, &BotonesCustom::BotonApretado, this, &GameScreen::Acepto);
    connect(BotonRechazar, &BotonesCustom::BotonApretado, this, &GameScreen::Rechazo);
    connect(BotonRechazar, &BotonesCustom::BotonApretado, &GestorNPC, &GestorNPCsUI::Rechazado);

    // Conectamos boton de centrar para centrar el documento.
    connect(BotonCentrar, &BotonesCustom::BotonApretado, &GestorNPC, &GestorNPCsUI::CentrarDocumentos);
}

void GameScreen::EmpezarJuego()
{
    RealizarConecciones();
    // En caso de cortar la animacion de entrada antes de terminar, hay un temporizador que habilita los botones posados 0.8 segundos
    temporizadorBotones.start(800);

    tiempoPartida.start(8*60*1000); // 8 Minutos

    GestorNPC.Entrar();
}

void GameScreen::PausarJuego()
{
    GestorNPC.Pausar();
    tiempoRestante = tiempoPartida.remainingTime();
    tiempoPartida.stop();
}

void GameScreen::ReanudarJuego()
{
    GestorNPC.Reanudar();
    tiempoPartida.start(tiempoRestante);
}

void GameScreen::RealizarConecciones()
{
    // Desbloquear botones despues de pasado un tiempo
    connect(&temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

    // Conectamos el temporizador de partida para terminar la partida.
    connect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);
}

void GameScreen::FinalDePartida()
{
    // a desarrollar
    BloquearBotones(true);

    GestorNPC.TerminoNivel();

    // Conectamos el temporizador de partida para terminar la partida.
    disconnect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);
    tiempoPartida.stop();

    // Desconectamos las cosas que le dan progreso al juego
    disconnect(&temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

    emit NivelTerminado();
    qDebug() << "Termino el juego";
}

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

void GameScreen::Acepto()
{
    GestorNPC.DocAprobado();
    juego->addNPCaceptado();
    SelloDocumento(true);
}

void GameScreen::Rechazo()
{
    GestorNPC.DocRechazado();
    juego->addNPCrechazado();
    SelloDocumento(false);
}

void GameScreen::SelloDocumento(bool Boton)
{
    GestorNPC.DetenerAnimacionesDocumentos();
    GestorNPC.Salir();

    temporizadorBotones.start(2500);
    BloquearBotones(true);

    juego->EvaluarDecision(GestorNPC.getTipo(), GestorNPC.getValidez(), Boton);

    if (GestorNPC.NPCsRestantes() == 0)
        FinalDePartida();
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

void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange)
        if (GestorNPC.MostrandoElNPC())
            GestorNPC.Centrar();
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Centrar();
}



