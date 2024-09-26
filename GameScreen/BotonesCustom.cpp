#include "BotonesCustom.h"
#include "ui_BotonesCustom.h"

BotonesCustom::BotonesCustom(QWidget *parent):
    QWidget(parent)
    , ui(new Ui::BotonesCustom)
{
    ui->setupUi(this);
    sonido2.setSource(QUrl("qrc:/Resources/Sonidos/SonidoBoton.wav"));
    sonido2.setVolume(0.5);

    // Colocamos la imagen que va a tener el boton segun el estado.
    SkinBotonUnblock = "";
    SkinBotonBlock = "";

    // Le damos la apariencia de no estar apretado al boton.
    ui->Boton->setStyleSheet(SkinBotonUnblock);

    // Conectamos el temporizador al apretar los botones
    TemporizadorBotones.setSingleShot(true);
    TiempoBloqueo = 1000;
}

BotonesCustom::BotonesCustom(QString Estado1, QString Estado2, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BotonesCustom), sonido2(this)
{
    ui->setupUi(this);

    sonido2.setSource(QUrl("qrc:/Resources/Sonidos/SonidoBoton.wav"));
    sonido2.setVolume(1.0);

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

void BotonesCustom::setSkinBotonUnblock(QString newSkinBotonUnblock)
{
    CrearSkinBoton(newSkinBotonUnblock, SkinBotonUnblock);
}

void BotonesCustom::setSkinBotonBlock(QString newSkinBotonBlock)
{
    CrearSkinBoton(newSkinBotonBlock, SkinBotonBlock);
}

void BotonesCustom::CrearSkinBoton(QString Estado1, QString &Direccion)
{
    Direccion = "border-image: url(" + Estado1 + ");";
}

bool BotonesCustom::getBotonBloqueado() const
{
    return BotonBloqueado;
}

void BotonesCustom::setVolumen(float volumen)
{
    sonido2.setVolume(volumen);
}

void BotonesCustom::PausarBoton()
{
    ui->Boton->setStyleSheet(SkinBotonBlock);
    BotonBloqueado = true;
}

void BotonesCustom::Accion()
{
    sonido2.play();
    connect(&TemporizadorBotones, &QTimer::timeout, this, &BotonesCustom::DesbloquearBoton);
    TemporizadorBotones.start(TiempoBloqueo);
    emit BotonApretado();
    PausarBoton();
}
