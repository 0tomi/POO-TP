#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QTimer>
#include <QDebug>

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Seteamos el juego, y obtenemos la cola de NPCs.
    juego = new Juego();
    Cola = juego->getCola();

    // Setear temporizador para bloquear botones
    temporizadorBotones = new QTimer(this);
    temporizadorBotones->setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    SpawnearNPC();
    documentos.setUpDocumentos(1, ui->Escritorio);

    BloquearBotones(true);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::EmpezarJuego()
{
    RealizarConecciones();
    // En caso de cortar la animacion de entrada antes de terminar, hay un temporizador que habilita los botones posados 0.8 segundos
    temporizadorBotones->start(800);
    EntrarNPC();
}

void GameScreen::RealizarConecciones()
{
    // Conecto los botones para que segun lo que haga el usuario, se evalue una cosa u otra.
    connect(ui->aceptarBoton, &QPushButton::clicked, this, &GameScreen::Acepto);
    connect(ui->rechazarBoton, &QPushButton::clicked, this, &GameScreen::Rechazo);

    // Conectamos boton de centrar para centrar el documento.
    connect(ui->BotonCentrar, &QPushButton::clicked, this, &GameScreen::FuncionBotonCentral);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::EntrarNPC);

    // Desbloquear botones despues de pasado un tiempo
    connect(temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);
}

void GameScreen::FinalDePartida()
{
    // a desarrollar
    disconnect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::FinalDePartida);
}

void GameScreen::Acepto()
{
    SelloDocumento(true);
}

void GameScreen::Rechazo()
{
    SelloDocumento(false);
    npcUI->Rechazado();
}
void GameScreen::SelloDocumento(bool Boton)
{
    SacarNPC();
    temporizadorBotones->start(1000);
    BloquearBotones(true);
    if (!(Cola->getSize())){
        // Desconectamos las cosas que le dan progreso al juego
        disconnect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::EntrarNPC);
        connect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::FinalDePartida);
        disconnect(temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);

        qDebug() << "Termino el juego";
    }
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    ui->BotonCentrar->setDisabled(Bloqueo);
    ui->aceptarBoton->setDisabled(Bloqueo);
    ui->rechazarBoton->setDisabled(Bloqueo);
}

void GameScreen::FuncionBotonCentral()
{
    // Bloqueamos los botones para que no bugeen el juego
    BloquearBotones(true);
    temporizadorBotones->start(700);

    CentrarDocumentos();
}

void GameScreen::DesbloquearBotones()
{
    BloquearBotones(false);
    CentrarNPC();
}

void GameScreen::SpawnearNPC()
{
    // Esto quedara asi hasta implementar los NPCs especiales
    npcUI = new NPCGenericoUI(this);

    QVBoxLayout *layout = new QVBoxLayout(ui->FondoNPC);
    layout->addWidget(npcUI);
    layout->setContentsMargins(40,80,40,0);
    ui->FondoNPC->setLayout(layout);

    npcUI->hide();

    npcUI->move(-(npcUI->width()),0);
}

void GameScreen::EntrarNPC()
{
    delete NPCenEscena;
    if (Cola->getSize()){
        NPCenEscena = Cola->getNPC();

        qDebug() << NPCenEscena->getGenero();
        qDebug() << NPCenEscena->getTipo();

        npcUI->setNPC(NPCenEscena);

        int centerX = ((ui->FondoNPC->width()) / 2) - (npcUI->width() / 2);
        int centerY = ((ui->FondoNPC->height())) - (npcUI->height());

        npcUI->Entrar(centerX, centerY);

        EntrarDOC();
    }
}

void GameScreen::SacarNPC()
{
    int SalidaEscena = ui->FondoNPC->width() + npcUI->width();
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height()) + 50;
    npcUI->Sacar(SalidaEscena, centerY);

    SacarDOC();
}

void GameScreen::CentrarNPC()
{
    int centerX = (ui->FondoNPC->width() - npcUI->width()) /2;
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());
    npcUI->move(centerX,centerY);
}

void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange){
        CentrarNPC();
        CentrarDocumentos();
    }
}

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



