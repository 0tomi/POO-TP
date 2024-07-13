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

    // Agregamos el NPC y Documentos a la escena
    GestorNPC.setUp(ui->FondoNPC, Cola);
    documentos.setUpDocumentos(1, ui->Escritorio);

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
    connect(BotonAprobar, &TomiBotones::BotonApretado, this, &GameScreen::Acepto);
    connect(BotonRechazar, &TomiBotones::BotonApretado, this, &GameScreen::Rechazo);
    connect(BotonRechazar, &TomiBotones::BotonApretado, &GestorNPC, &GestorNPCsUI::Rechazado);

    // Conectamos boton de centrar para centrar el documento.
    connect(BotonCentrar, &TomiBotones::BotonApretado, this, &GameScreen::FuncionBotonCentral);
}

void GameScreen::EmpezarJuego()
{
    RealizarConecciones();
    // En caso de cortar la animacion de entrada antes de terminar, hay un temporizador que habilita los botones posados 0.8 segundos
    temporizadorBotones.start(800);

    tiempoPartida.start(8*60*1000); // 8 Minutos

    EntrarNPC();
}

void GameScreen::RealizarConecciones()
{
    // Desbloquear botones despues de pasado un tiempo
    connect(&temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

    // Conectamos el temporizador de partida para terminar la partida.
    connect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);

    // Conectamos la cola al final de la partida
    connect(&GestorNPC, &GestorNPCsUI::ColaTerminada, this, &GameScreen::FinalDePartida);

    // Conectamos los documentos con la salida de los npcs
    connect(&GestorNPC, &GestorNPCsUI::NPCTerminoSalir, this, &GameScreen::EntrarNPC);
}

void GameScreen::FinalDePartida()
{
    // a desarrollar
    BloquearBotones(true);
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Salir();
    GestorNPC.TerminoNivel();

    // Conectamos el temporizador de partida para terminar la partida.
    disconnect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);
    tiempoPartida.stop();

    // Desconectamos las cosas que le dan progreso al juego
    disconnect(&temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

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

    BotonAprobar = new TomiBotones(BotonAceptarDesbloqueado, BotonAceptarBloqueado, ui->ContenedorBotones);
    BotonRechazar = new TomiBotones(BotonRechazarDesbloqueado, BotonRechazarBloqueado, ui->ContenedorBotones);
    BotonCentrar = new TomiBotones(BotonCentrarDesblock, BotonCentrarBlock,ui->ContenedorBotones);
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
    SelloDocumento(true);
}

void GameScreen::Rechazo()
{
    SelloDocumento(false);
}

void GameScreen::SelloDocumento(bool Boton)
{
    documentos.DetenerAnimaciones();
    SacarNPC();
    temporizadorBotones.start(2500);
    BloquearBotones(true);

    if (Boton == GestorNPC.getValidez())
        juego->SumarSocialCredits(GestorNPC.getTipo());
    else
        juego->RestarSocialCredits(GestorNPC.getTipo());
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    BotonCentrar->BloquearBoton(Bloqueo);
    BotonAprobar->BloquearBoton(Bloqueo);
    BotonRechazar->BloquearBoton(Bloqueo);
}

void GameScreen::FuncionBotonCentral()
{
    // Bloqueamos los botones para que no bugeen el juego
    CentrarDocumentos();
}

void GameScreen::DesbloquearBotones()
{
    BloquearBotones(false);
    GestorNPC.Centrar();
}

void GameScreen::EntrarNPC()
{
    NPC* NPCinfo = GestorNPC.Entrar();
    documentos.setDocumento(NPCinfo);
    documentos.Entrar();
}

void GameScreen::SacarNPC()
{
    GestorNPC.Salir();
    SacarDOC();
}

void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange){
        GestorNPC.Centrar();
        CentrarDocumentos();
    }
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    GestorNPC.Centrar();
    CentrarDocumentos();
}

void GameScreen::SacarDOC()
{
    documentos.Salir();
}

void GameScreen::CentrarDocumentos()
{
    documentos.Centrar();
}



