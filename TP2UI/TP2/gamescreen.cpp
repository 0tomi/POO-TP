#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QTimer>
#include <QDebug>

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Setear temporizador para bloquear botones
    temporizadorBotones = new QTimer(this);
    temporizadorBotones->setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    SpawnearNPC();
    SpawnearDocumento();

    BloquearBotones(true);

    RealizarConecciones();
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::EmpezarJuego()
{
    // Arranca la wea esta weon
    qDebug() << "Comenze el juego";
    EntrarNPC();
}

void GameScreen::RealizarConecciones()
{
    // Conecto los botones para que segun lo que haga el usuario, se evalue una cosa u otra.
    connect(ui->aceptarBoton, &QPushButton::clicked, this, &GameScreen::Acepto);
    connect(ui->rechazarBoton, &QPushButton::clicked, this, &GameScreen::Rechazo);

    // Conectamos boton de centrar para centrar el documento.
    connect(ui->BotonCentrar, &QPushButton::clicked, this, &GameScreen::CentrarDocumentos);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(npcUI, &NPCUI::animacionSalirTerminada, this, &GameScreen::EntrarNPC);

    // Desbloquear botones cuando el documento se arroja sobre la mesa
    connect(doc, &DocumentosUI::animacionEntrarTerminada, this, &GameScreen::DesbloquearBotones);

    // Desbloquear botones despues de pasado un tiempo
    connect(temporizadorBotones, &QTimer::timeout, this, &GameScreen::DesbloquearBotones);
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
    SacarNPC();
    BloquearBotones(true);
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    ui->BotonCentrar->setDisabled(Bloqueo);
    ui->aceptarBoton->setDisabled(Bloqueo);
    ui->rechazarBoton->setDisabled(Bloqueo);
}

void GameScreen::DesbloquearBotones()
{
    BloquearBotones(false);
}

void GameScreen::CentrarDocumentos()
{
    int centerX = ((ui->Escritorio->width()) - (doc->width())) /2;
    int centerY = (((ui->Escritorio->height())) - (doc->height())) / 2;

    // Bloqueamos los botones para que no bugeen el juego
    BloquearBotones(true);
    temporizadorBotones->start(700);

    // Esto dsps iria con un for por cada documento
    doc->Centrar(centerX, centerY);
}

void GameScreen::EntrarNPC()
{
    int centerX = ((ui->FondoNPC->width()) / 2) - (npcUI->width() / 2);
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());

    npcUI->Entrar(centerX, centerY);
    EntrarDOC();
}

void GameScreen::SacarNPC()
{
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());
    npcUI->Sacar(centerY);

    SacarDOC();
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    int centerX = (ui->FondoNPC->width() - npcUI->width()) /2;
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());
    npcUI->move(centerX,centerY);
}

void GameScreen::SpawnearDocumento()
{
    doc = new UADERpass(ui->Escritorio);
    doc->setFixedSize(300,300);

    doc->move(0,-500);
}

void GameScreen::EntrarDOC()
{
    int centerX = ((ui->Escritorio->width()) - (doc->width())) /2;
    int centerY = (((ui->Escritorio->height())) - (doc->height())) / 2;

    doc->Entrar(centerX,centerY);
}

void GameScreen::SacarDOC()
{
    int centerX = ((ui->Escritorio->width()) - (doc->width())) / 2;
    doc->Sacar(centerX);
}

void GameScreen::SpawnearNPC()
{
    npcUI = new NPCGenerico(this);

    QVBoxLayout *layout = new QVBoxLayout(ui->FondoNPC);
    layout->addWidget(npcUI);
    ui->FondoNPC->setLayout(layout);

    npcUI->setFixedSize(300,300);

    npcUI->move(-500,0);
}


