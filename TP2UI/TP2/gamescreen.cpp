#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(Juego* newJuego, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Seteamos el juego, y obtenemos la cola de NPCs.
    juego = newJuego;
    Cola = juego->getCola();

    temporizadorBotones.setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    SpawnearNPC();
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

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::RealizarConecciones()
{
    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(npcUI, &NPCUI::animacionEntrarTerminada, this, &GameScreen::CentrarNPC);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::EntrarNPC);

    // Desbloquear botones despues de pasado un tiempo
    connect(&temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

    // Conectamos el temporizador de partida para terminar la partida.
    connect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::FinalDePartida()
{
    // a desarrollar
    BloquearBotones(true);
    if (GestorNPC.MostrandoElNPC()){
        GestorNPC.SacarNPC();
    }
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

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::Rechazo()
{
    SelloDocumento(false);
    npcUI->Rechazado();
}

void GameScreen::SelloDocumento(bool Boton)
{
    documentos.DetenerAnimaciones();
    SacarNPC();
    temporizadorBotones.start(2500);
    BloquearBotones(true);

    if (Boton == NPCenEscena->getValidez())
        juego->SumarSocialCredits(NPCenEscena->getTipo());
    else
        juego->RestarSocialCredits(NPCenEscena->getTipo());

    qDebug() << "Cola: " << Cola->getSize();

    if (!Cola->getSize())
        FinalDePartida();
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
    CentrarNPC();
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::SpawnearNPC()
{
    // Esto quedara asi hasta implementar los NPCs especiales
    //npcUI = new NPCGenericoUI(ui->FondoNPC);

    // ## FORMATO VIEJO QUE NO SE PORQUE USE ##

    npcUI = new NPCGenericoUI(ui->FondoNPC);
    //QVBoxLayout *layout = new QVBoxLayout(ui->FondoNPC);
    //layout->addWidget(npcUI);
    //layout->setContentsMargins(40,80,40,0);
    //ui->FondoNPC->setLayout(layout);
    ui->FondoNPC->layout()->addWidget(npcUI);

    npcUI->hide();

    npcUI->move(-(npcUI->width()),0);
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::EntrarNPC()
{
    NPCenEscena = Cola->getNPC();

    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##
    qDebug() << NPCenEscena->getGenero();
    qDebug() << NPCenEscena->getTipo();
    qDebug() << NPCenEscena->getValidez();
    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##

    npcUI->setNPC(NPCenEscena);

    int centerX = (ui->FondoNPC->width() - npcUI->width()) / 2;
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());

    npcUI->Entrar(centerX, centerY);
    EntrarDOC();

}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::SacarNPC()
{
    int SalidaEscena = ui->FondoNPC->width() + npcUI->width();
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height()) + 50;
    npcUI->Sacar(SalidaEscena, centerY);

    SacarDOC();
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::CentrarNPC()
{
    int centerX = (ui->FondoNPC->width() - npcUI->width()) /2;
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());
    npcUI->move(centerX,centerY);
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange){
        CentrarNPC();
        CentrarDocumentos();
    }
}

// ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ## REEMPLAZAR ##
void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    CentrarNPC();
    CentrarDocumentos();
}

void GameScreen::EntrarDOC()
{
    documentos.setDocumento(NPCenEscena->getDocumentos(), NPCenEscena->getTipo());
    documentos.Entrar();
}

void GameScreen::SacarDOC()
{
    documentos.Salir();
}

void GameScreen::CentrarDocumentos()
{
    documentos.Centrar();
}



