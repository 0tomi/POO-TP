#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Agregamos el NPC y Documentos a la escena
    this->SpawnearNPC();
    this->SpawnearDocumento();

    // Preparamos animaciones de entrada del Doc
    animacionEntradaDOC = new QPropertyAnimation(doc, "pos");
    animacionSalidaDOC = new QPropertyAnimation(doc, "pos");
    connect(animacionSalidaDOC, &QPropertyAnimation::finished, this, &GameScreen::FletearDOC);

    // Preparamos animaciones de entrada del NPC
    animacionEntrada = new QPropertyAnimation(npcUI, "pos");
    this->animacionSalida = new QPropertyAnimation(npcUI, "pos");
    connect(animacionSalida, &QPropertyAnimation::finished, this, &GameScreen::FletearNPC);

    connect(ui->aceptarBoton, &QPushButton::clicked, this,&GameScreen::SacarNPC);
    connect(ui->rechazarBoton, &QPushButton::clicked, this,&GameScreen::EntrarNPC);

    //EmpezarJuego();

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
    EntrarDOC();
}

void GameScreen::EntrarNPC()
{
    PrepararAnimacionEntradaNPC();
    npcUI->show();
    animacionEntrada->start();
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    int centerX = (ui->FondoNPC->width() - npcUI->width()) /2;
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());
    npcUI->move(centerX,centerY);
}

void GameScreen::SacarNPC()
{
    PrepararAnimacionSalidaNPC();
    animacionSalida->start();
}

void GameScreen::SpawnearDocumento()
{
    doc = new UADERpass(this);
    doc->setFixedSize(300,300);

    QVBoxLayout *layout = new QVBoxLayout(ui->Escritorio);
    layout->addWidget(doc);
    ui->Escritorio->setLayout(layout);

    doc->move(0,-500);
}

void GameScreen::EntrarDOC()
{
    PrepararAnimacionEntradaDOC();
    doc->show();
    animacionEntradaDOC->start();
}

void GameScreen::PrepararAnimacionEntradaDOC()
{
    int centerX = ((ui->Escritorio->width()) - (doc->width())) /2;
    int centerY = (((ui->Escritorio->height())) - (doc->height())) / 2;

    animacionEntradaDOC->setDuration(1000);
    animacionEntradaDOC->setStartValue(QPoint(centerX,-500));
    animacionEntradaDOC->setEndValue(QPoint(centerX,centerY));
}

void GameScreen::PrepararAnimacionSalidaDOC()
{
    int centerX = ((ui->Escritorio->width())) - (doc->width()) / 2;

    animacionSalidaDOC->setDuration(1000);
    animacionSalidaDOC->setStartValue(doc->pos());
    animacionSalidaDOC->setEndValue(QPoint(centerX,-500));
}

void GameScreen::FletearDOC()
{
    qDebug() << "desapareci";
    doc->hide();
}

void GameScreen::SpawnearNPC()
{
    npcUI = new NPCUI(this);
    npcUI->setFixedSize(300,300);

    QVBoxLayout *layout = new QVBoxLayout(ui->FondoNPC);
    layout->addWidget(npcUI);
    ui->FondoNPC->setLayout(layout);
    npcUI->move(-500,0);
}

void GameScreen::PrepararAnimacionEntradaNPC()
{
    int centerX = ((ui->FondoNPC->width()) / 2) - (npcUI->width() / 2);
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());

    animacionEntrada->setDuration(1000);
    animacionEntrada->setStartValue(QPoint(-500,centerY));
    animacionEntrada->setEndValue(QPoint(centerX,centerY));
}

void GameScreen::PrepararAnimacionSalidaNPC()
{
    int centerY = ((ui->FondoNPC->height())) - (npcUI->height());

    animacionSalida->setDuration(1000);
    animacionSalida->setStartValue(npcUI->pos());
    animacionSalida->setEndValue(QPoint(1000,centerY));
}

void GameScreen::FletearNPC()
{
    npcUI->hide();
}
