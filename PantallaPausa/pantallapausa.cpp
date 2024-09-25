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
    connect(ui->tutorialButton, &QPushButton::clicked, this, &PantallaPausa::clickedTutorial);

    connect(ui->soundButton, &QPushButton::clicked, this, [this](){
        ui->Menus->setCurrentIndex(2);
    });
    connect(ui->volverApausa, &QPushButton::clicked, this, [this](){
        ui->Menus->setCurrentIndex(0);
    });

    ui->VolumenMusica->setRange(0, 100);
    ui->VolumenSonidos->setRange(0,100);
    ui->VolumenMusica->setTickPosition(QSlider::NoTicks);
    ui->VolumenSonidos->setTickPosition(QSlider::NoTicks);

    connect(ui->VolumenSonidos, &QSlider::valueChanged, this, &PantallaPausa::soundSliderChanged);
    connect(ui->VolumenMusica, &QSlider::valueChanged, this, &PantallaPausa::musicSliderChanged);
    ui->VolumenMusica->setValue(100);
    ui->VolumenSonidos->setValue(100);
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

void PantallaPausa::musicSliderChanged(int dato)
{
    float valor = dato/ 100.0;
    emit musicVolume(valor);
}

void PantallaPausa::soundSliderChanged(int dato)
{
    float valor = dato/ 100.0;
    emit soundVolume(valor);
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



void PantallaPausa::tutorialButton()
{
    emit clickedTutorial();
}

