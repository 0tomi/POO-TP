#include "notificacion.h"
#include "ui_notificacion.h"

Notificacion::Notificacion(int Numero, bool Multa, QString texto, float vol, QWidget *parent):
    DocumentosUI(parent)
    , ui(new Ui::Notificacion), sonidoEntrada(parent), sonidoSalida(parent)
{
    this->numeroNotificacion = Numero;
    hide();
    ui->setupUi(this);
    Temporizador.setSingleShot(true);

    sonidoEntrada.setSource(QUrl("qrc:/Resources/Documentos/Notificaciones/NotificacionEntrada.WAV"));
    sonidoSalida.setSource(QUrl("qrc:/Resources/Documentos/Notificaciones/NotificacionSalida.WAV"));
    setVolume(vol);

    layout = new QHBoxLayout(ui->BotonCerrar);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    ui->BotonCerrar->setLayout(layout);

    cerrar = new QPushButton(ui->BotonCerrar);
    cerrar->setStyleSheet("background-color: rgba(255, 255, 255, 0); border: none;");  // Hacerlo invisible
    ui->BotonCerrar->layout()->addWidget(cerrar);

    ui->Motivos->setText(texto);
    if (Multa)
        ui->stackedWidget->setCurrentIndex(0);
    else ui->stackedWidget->setCurrentIndex(1);

    animacionEntrada->setDuration(2000);

    connect(cerrar, &QPushButton::clicked, [this](){
        sonidoSalida.play();
        this->hide();
        Temporizador.start(3000);
        });

    connect(&Temporizador, &QTimer::timeout, [this](){
        emit QuiereCerrarNotificacion(numeroNotificacion);
    });
}

Notificacion::~Notificacion()
{
    delete layout;
    delete ui;
    delete cerrar;
}

void Notificacion::setVolume(float vol)
{
    sonidoEntrada.setVolume(vol - 0.2);
    sonidoSalida.setVolume(vol - 0.2);
}

void Notificacion::Entrar()
{
    int CentroX = (padre->width() - this->width()) / 2;
    int CentroY = (padre->height() - this->height()) / 2;
    animacionEntrada->setStartValue(QPoint(CentroX, padre->height()));
    animacionEntrada->setEndValue(QPoint(CentroX, CentroY));
    animacionEntrada->start();
    this->show();
    sonidoEntrada.play();
}
