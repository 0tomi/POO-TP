#include "tomibotones.h"
#include "ui_tomibotones.h"
#include <QDebug>
#include <QPalette>

TomiBotones::TomiBotones(QString Estado1, QString Estado2, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TomiBotones)
{
    // Sacamos el efecto azualdo del boton
    ui->setupUi(this);

    // Colocamos la imagen que va a tener el boton segun el estado.
    //SkinBotonDesbloqueado.load(Estado1);
    //SkinBotonBloqueado.load(Estado2);
    CrearSkinBoton(Estado1, SkinBotonUnblock);
    CrearSkinBoton(Estado2, SkinBotonBlock);

    // Le damos la apariencia de no estar apretado al boton.
    //ui->Boton->setPixmap(SkinBotonDesbloqueado);
    ui->Boton->setStyleSheet(SkinBotonUnblock);

    // Conectamos el temporizador al apretar los botones
    TemporizadorBotones.setSingleShot(true);
    TiempoBloqueo = 1000;
}

void TomiBotones::SetTiempoBloqueo(int milisegundos)
{
    TiempoBloqueo = milisegundos;
}

void TomiBotones::BloquearBoton(bool bloqueo)
{
    if (bloqueo){
        //ui->Boton->setPixmap(SkinBotonBloqueado);
        ui->Boton->setStyleSheet(SkinBotonBlock);
        BotonBloqueado = true;
    } else
        DesbloquearBoton();
}

void TomiBotones::DesbloquearBoton()
{
    disconnect(&TemporizadorBotones, &QTimer::timeout, this, &TomiBotones::DesbloquearBoton);
    qDebug() << "Boton desbloqueado";
    //ui->Boton->setPixmap(SkinBotonDesbloqueado);
    ui->Boton->setStyleSheet(SkinBotonUnblock);
    BotonBloqueado = false;
    emit BottonLiberado();
}

TomiBotones::~TomiBotones()
{
    delete ui;
}

void TomiBotones::mousePressEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if (!BotonBloqueado)
        Accion();
}

void TomiBotones::CrearSkinBoton(QString Estado1, QString &Direccion)
{
    Direccion = "border-image: url(" + Estado1 + ");";
}

void TomiBotones::Accion()
{
    connect(&TemporizadorBotones, &QTimer::timeout, this, &TomiBotones::DesbloquearBoton);
    TemporizadorBotones.start(TiempoBloqueo);
    emit BotonApretado();
    BloquearBoton(true);
}
