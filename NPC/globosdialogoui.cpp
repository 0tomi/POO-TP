#include "globosdialogoui.h"
#include "ui_globosdialogoui.h"

GlobosDialogoUI::GlobosDialogoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobosDialogoUI)
{
    ui->setupUi(this);
    setFixedSize(300,150);
    hide();
    TiempoVisualizacion.setSingleShot(true);
}

void GlobosDialogoUI::setMensaje(const QString &newMensaje)
{
    mensaje = newMensaje;
    ui->Texto->setText(mensaje);
    emit MensajePreparado();
    connect(&TiempoVisualizacion, &QTimer::timeout, this, &GlobosDialogoUI::TerminarMensaje);
    MostrarMensaje();
}

void GlobosDialogoUI::MostrarMensaje()
{
    // en desarrollo
    show();
    raise();
    emit Hablando(mensaje);
    TiempoVisualizacion.start(6000);
}

void GlobosDialogoUI::ForzarSalir()
{
    if (TiempoVisualizacion.isActive()){
        TiempoVisualizacion.stop();
        TerminarMensaje();
    }
}

// ########## A futuro #############
void GlobosDialogoUI::CorrerMensaje()
{

}

GlobosDialogoUI::~GlobosDialogoUI()
{
    delete ui;
}

void GlobosDialogoUI::DarFormatoPorqueQTesHorrible(QString &formato)
{
    QString textoActual = ui->Texto->text();
    // Mantiene las etiquetas HTML y solo actualiza el contenido del texto
    QString updatedText = textoActual.section(':', 0, 0) + ": <i>" + formato + "</i>";
    ui->Texto->setText(updatedText);
}

void GlobosDialogoUI::TerminarMensaje()
{
    hide();
    // Aca estaria la animacion de que se va el globo.
    emit MensajeTerminado();
}
