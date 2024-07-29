#include "transcriptordialogos.h"
#include "ui_transcriptordialogos.h"

TranscriptorDialogos::TranscriptorDialogos(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::TranscriptorDialogos)
    , DialogoRecibido("")

{

    ui->setupUi(this);
}

TranscriptorDialogos::~TranscriptorDialogos()
{
    delete ui;
}

void TranscriptorDialogos::Entrar()
{
    ui->dialogo->setText(this->DialogoRecibido);
    DocumentosUI::Entrar();
}

void TranscriptorDialogos::Sacar()
{
    this->DialogoRecibido="";
    ui->dialogo->clear();
    DocumentosUI::Sacar();
}

void TranscriptorDialogos::CaptarMensaje(QString dialogo)
{
    this->DialogoRecibido=dialogo;

}

void TranscriptorDialogos::LimpiarDialogo()
{
    this->DialogoRecibido="";
}
void TranscriptorDialogos::setDocumentacionInfo(Documentacion *documento)
{

}
