#include "pantallapausa.h"
#include "ui_pantallapausa.h"

PantallaPausa::PantallaPausa(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPausa)
{
    ui->setupUi(this);

    connect(ui->returnButton, &QPushButton::clicked, this, &PantallaPausa::buttonReturnClicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &PantallaPausa::buttonQuitClicked);
    connect(ui->fullscreenButton, &QPushButton::clicked, this, &PantallaPausa::buttonFullScreenClicked);
    connect(ui->windowedButton, &QPushButton::clicked, this, &PantallaPausa::buttonWindowedClicked);
}

PantallaPausa::~PantallaPausa()
{
    delete ui;
}

void PantallaPausa::setFullScreenButton()
{
    ui->stackedWidget->setCurrentWidget(ui->ActivarPantallaCompleta);
}

void PantallaPausa::setWindowedButton()
{
    ui->stackedWidget->setCurrentWidget(ui->ActivarModoVentana);
}

void PantallaPausa::buttonFullScreenClicked()
{
    emit setFullScreen();
    ui->stackedWidget->setCurrentWidget(ui->ActivarModoVentana);
    qDebug() << "se clickeo boton de fullscreen";
}

void PantallaPausa::buttonWindowedClicked()
{
    emit setWindowedScreen();
    ui->stackedWidget->setCurrentWidget(ui->ActivarPantallaCompleta);
    qDebug() << "se clickeo boton de ventana";
}

void PantallaPausa::buttonQuitClicked()
{
    emit quit();
}

void PantallaPausa::buttonReturnClicked()
{
    emit return2lastWidget();
}

