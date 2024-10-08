#include "pantallatutorial.h"
#include "ui_pantallatutorial.h"

PantallaTutorial::PantallaTutorial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaTutorial), sonidoBotones(parent), musica(parent)
{
    ui->setupUi(this);

    sonidoBotones.setSource(QUrl("qrc:/Resources/Sonidos/BotonesMenu.WAV"));
    musica.setSource(QUrl(""));
    setMusicVolume(1.0);
    setSoundVolume(1.0);

    ui->PagTutorial->setCurrentIndex(PaginaActual);
    CantidadPaginas = ui->PagTutorial->count();
    this->PaginaActual = 0;

    if (CantidadPaginas > 0) {
        setBotones();
        actualizarBotones();
    } else {
        ui->Anterior_2->setEnabled(false);
        ui->Siguiente_2->setEnabled(false);
    }
}

void PantallaTutorial::setSoundVolume(float vol)
{
    sonidoBotones.setVolume(vol-0.2);
}

void PantallaTutorial::setMusicVolume(float vol)
{
    musica.setVolume(vol-0.2);
}

PantallaTutorial::~PantallaTutorial()
{
    delete ui;
}

void PantallaTutorial::setBotones()
{
    connect(ui->Anterior_2, &QPushButton::clicked, this, &PantallaTutorial::IrPagAnterior);
    connect(ui->Siguiente_2, &QPushButton::clicked, this, &PantallaTutorial::IrPagSiguiente);
    connect(ui->TerminarTutorial, &QPushButton::clicked, this, &PantallaTutorial::SalirTutorial);
}

void PantallaTutorial::IrPagAnterior()
{
    if (PaginaActual > 0) {
        sonidoBotones.play();
        PaginaActual--;
        ui->PagTutorial->setCurrentIndex(PaginaActual);
        actualizarBotones();
    }
}

void PantallaTutorial::IrPagSiguiente()
{
    if (PaginaActual < CantidadPaginas - 1) {
        sonidoBotones.play();
        PaginaActual++;
        ui->PagTutorial->setCurrentIndex(PaginaActual);
        actualizarBotones();
    }
}

void PantallaTutorial::SalirTutorial()
{
    sonidoBotones.play();
    emit TerminarTutorial();
}

void PantallaTutorial::actualizarBotones()
{
    ui->Anterior_2->setVisible(PaginaActual > 0);
    ui->Siguiente_2->setVisible(PaginaActual < CantidadPaginas - 1);
}
