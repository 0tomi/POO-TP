#include "pantallapausa.h"
#include "ui_pantallapausa.h"

PantallaPausa::PantallaPausa(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPausa)
{
    ui->setupUi(this);

    connect(ui->returnButton, &QPushButton::clicked, this, &PantallaPausa::buttonReturnClicked);
    connect(ui->fullscreenButton, &QPushButton::clicked, this, &PantallaPausa::buttonFullScreenClicked);
    connect(ui->windowedButton, &QPushButton::clicked, this, &PantallaPausa::buttonWindowedClicked);

    connect(ui->quitButton, &QPushButton::clicked, this, &PantallaPausa::ConfirmarSalir);
    connect(ui->quitButtonConfirmed, &QPushButton::clicked, this, &PantallaPausa::buttonQuitClicked);
    connect(ui->noReturnButton, &QPushButton::clicked, this, &PantallaPausa::setInicio);
}

void PantallaPausa::setInicio()
{
    ui->Menus->setCurrentIndex(0);
}

void PantallaPausa::BlockVolverMenu(bool estado)
{
    if (estado)
        ui->quitButton->hide();
    else ui->quitButton->show();
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

void PantallaPausa::ConfirmarSalir()
{
    ui->Menus->setCurrentIndex(1);
}


