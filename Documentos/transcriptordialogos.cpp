#include "transcriptordialogos.h"
#include "ui_transcriptordialogos.h"

TranscriptorDialogos::TranscriptorDialogos(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::TranscriptorDialogos), sonidoEntrada(parent), sonidoSalida(parent)
{

    ui->setupUi(this);
    sonidoEntrada.setSource(QUrl("qrc:/Resources/Sonidos/NotificacionEntradaTranscriptor.wav"));
    sonidoSalida.setSource(QUrl("qrc:/Resources/Sonidos/NotificacionSalidaTranscriptor.wav"));
    setVolume(1.0);
    hide();
    DialogoRecibido = "";
    Mostrando = false;
    connect(this, &TranscriptorDialogos::animacionSalirTerminada, ui->Dialogos, &QLabel::clear);
}

TranscriptorDialogos::~TranscriptorDialogos()
{
    delete ui;
}

void TranscriptorDialogos::Entrar()
{
    ui->Dialogos->setText(this->DialogoRecibido);
    sonidoEntrada.play();
    raise();
    DocumentosUI::Entrar();
    Mostrando = true;
}

void TranscriptorDialogos::Sacar()
{
    sonidoSalida.play();
    DocumentosUI::Sacar();
    Mostrando = false;
}

void TranscriptorDialogos::setVolume(float vol)
{
    sonidoEntrada.setVolume(vol-0.2);
    sonidoSalida.setVolume(vol-0.2);
}

void TranscriptorDialogos::CaptarMensaje(QString dialogo)
{
    this->DialogoRecibido+=dialogo + "\n";

}

void TranscriptorDialogos::LimpiarDialogo()
{
    this->DialogoRecibido="";
}

void TranscriptorDialogos::MostrarOcultar()
{
    if (Mostrando)
        this->Sacar();
    else this->Entrar();
}

void TranscriptorDialogos::PrepararAnimacionEntrada()
{
    if (animacionEntrada->state() == QAbstractAnimation::Paused)
        animacionEntrada->stop();

    int centerX = ((padre->width()) - (width())) /2;
    int centerY = (((padre->height())) - (height())) / 2;

    animacionEntrada->setStartValue(QPoint(centerX, padre->height()));
    animacionEntrada->setEndValue(QPoint(centerX,centerY));
}

void TranscriptorDialogos::PrepararAnimacionSalida()
{
    int centerX = ((padre->width()) - (width())) /2;
    animacionSalida->setStartValue(this->pos());
    animacionSalida->setEndValue(QPoint(centerX,padre->height()));
}

bool TranscriptorDialogos::getMostrando() const
{
    return Mostrando;
}

void TranscriptorDialogos::setDocumentacionInfo(Documentacion *documento)
{

}
