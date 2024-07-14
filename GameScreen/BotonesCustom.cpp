#include "BotonesCustom.h"
#include "ui_BotonesCustom.h"

BotonesCustom::BotonesCustom(QString Estado1, QString Estado2, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BotonesCustom)
{
    // Sacamos el efecto azualdo del boton
    ui->setupUi(this);

    // Colocamos la imagen que va a tener el boton segun el estado.
    CrearSkinBoton(Estado1, SkinBotonUnblock);
    CrearSkinBoton(Estado2, SkinBotonBlock);

    // Le damos la apariencia de no estar apretado al boton.
    ui->Boton->setStyleSheet(SkinBotonUnblock);

    // Conectamos el temporizador al apretar los botones
    TemporizadorBotones.setSingleShot(true);
    TiempoBloqueo = 1000;
}

void BotonesCustom::SetTiempoBloqueo(int milisegundos)
{
    TiempoBloqueo = milisegundos;
}

void BotonesCustom::BloquearBoton(bool bloqueo)
{
    if (bloqueo){
        disconnect(&TemporizadorBotones, &QTimer::timeout, this, &BotonesCustom::DesbloquearBoton);
        PausarBoton();
    } else
        DesbloquearBoton();
}

void BotonesCustom::DesbloquearBoton()
{
    disconnect(&TemporizadorBotones, &QTimer::timeout, this, &BotonesCustom::DesbloquearBoton);
    ui->Boton->setStyleSheet(SkinBotonUnblock);
    BotonBloqueado = false;
    emit BottonLiberado();
}

BotonesCustom::~BotonesCustom()
{
    delete ui;
}

void BotonesCustom::mousePressEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if (!BotonBloqueado)
        Accion();
}

void BotonesCustom::CrearSkinBoton(QString Estado1, QString &Direccion)
{
    Direccion = "border-image: url(" + Estado1 + ");";
}

void BotonesCustom::PausarBoton()
{
    ui->Boton->setStyleSheet(SkinBotonBlock);
    BotonBloqueado = true;
}

void BotonesCustom::Accion()
{
    connect(&TemporizadorBotones, &QTimer::timeout, this, &BotonesCustom::DesbloquearBoton);
    TemporizadorBotones.start(TiempoBloqueo);
    emit BotonApretado();
    PausarBoton();
}
