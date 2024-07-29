#include "paisresidenciaui.h"
#include "ui_paisresidenciaui.h"

paisresidenciaui::paisresidenciaui(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::paisresidenciaui)
{
    ui->setupUi(this);
    setFixedSize(250,250);
}

paisresidenciaui::~paisresidenciaui()
{
    delete ui;
}

void paisresidenciaui::setDocumentacionInfo(Documentacion *documento)
{
    this->PaisResidenciaUI = dynamic_cast<PaisResidencia*>(documento);
    ui->PaisResidencia->setText(this->PaisResidenciaUI->getPaisResidencia());
    ui->Nombre->setText(this->PaisResidenciaUI->getNombre());
    ui->FechaNacimiento->setText(this->PaisResidenciaUI->getFecha());
}


