#include "pantallatutorial.h"
#include "ui_pantallatutorial.h"

PantallaTutorial::PantallaTutorial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaTutorial)
{
    ui->setupUi(this);
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
        PaginaActual--;
        ui->PagTutorial->setCurrentIndex(PaginaActual);
        actualizarBotones();
    }
}

void PantallaTutorial::IrPagSiguiente()
{
    if (PaginaActual < CantidadPaginas - 1) {
        PaginaActual++;
        ui->PagTutorial->setCurrentIndex(PaginaActual);
        actualizarBotones();
    }
}

void PantallaTutorial::SalirTutorial()
{
    emit TerminarTutorial();
}

void PantallaTutorial::actualizarBotones()
{
    ui->Anterior_2->setVisible(PaginaActual > 0);
    ui->Siguiente_2->setVisible(PaginaActual < CantidadPaginas - 1);
}
