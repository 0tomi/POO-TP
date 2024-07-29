#include "transcriptordialogos.h"
#include "ui_transcriptordialogos.h"

TranscriptorDialogos::TranscriptorDialogos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TranscriptorDialogos)
{
    ui->setupUi(this);
}

TranscriptorDialogos::~TranscriptorDialogos()
{
    delete ui;
}

void TranscriptorDialogos::Entrar()
{

    DocumentosUI::Entrar();
}
