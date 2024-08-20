#include "docsiconui.h"
#include "ui_docsiconui.h"

DocsIconUI::DocsIconUI(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::DocsIconUI)
{
    ui->setupUi(this);
    padre = parent;
    setCurrentIndex(0);
    LibroAbierto = false;

    // Creamos las animaciones de entrada
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(1000);
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);

    // Creamos las animaciones de salida
    animacionSalida = new QPropertyAnimation(this, "pos");
    animacionSalida->setDuration(1000);
    animacionSalida->setEasingCurve(QEasingCurve::InExpo);

    // Crear animacion de vibracion

    // Hacemos que cuando termine la animacion de salida, el documento desaparezca.
    connect(animacionEntrada, &QPropertyAnimation::finished, this, &DocsIconUI::emitAnimacionEntrarTerminada);
    connect(animacionSalida, &QPropertyAnimation::finished, this, &DocsIconUI::emitAnimacionSalirTerminada);
    hide();
    BlockDocumento = false;
    mostrando = false;
}


DocsIconUI::~DocsIconUI()
{
    delete ui;
    delete animacionEntrada;
    delete animacionSalida;
}

void DocsIconUI::BloquearDocumento()
{
    CerrarDocumento();
    BlockDocumento = true;
}

void DocsIconUI::accionar()
{
    if (BlockDocumento){
        Sacar();
    } else {
        if (LibroAbierto)
            CerrarDocumento();
        else
            AbrirDocumento();
    }
}

void DocsIconUI::Entrar()
{
    this->PrepararAnimacionEntrada();
    this->animacionEntrada->start();
    this->show();
    BlockDocumento = false;
    this->mostrando = true;
}

void DocsIconUI::Sacar()
{
    this->PrepararAnimacionSalida();
    CerrarDocumento();
    this->animacionSalida->start();
    this->mostrando = false;
}

void DocsIconUI::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        accionar();
}

void DocsIconUI::PrepararAnimacionEntrada()
{
    if (animacionEntrada->state() == QAbstractAnimation::Paused)
        animacionEntrada->stop();

    int centerX = ((padre->width()) - (width())) /2;
    int centerY = (((padre->height())) - (height())) / 2;

    animacionEntrada->setStartValue(QPoint(centerX,-500));
    animacionEntrada->setEndValue(QPoint(centerX,centerY));
}

void DocsIconUI::PrepararAnimacionSalida()
{
    int centerX = ((padre->width()) - (width())) / 2;
    animacionSalida->setStartValue(this->pos());
    animacionSalida->setEndValue(QPoint(centerX,-500));
}

void DocsIconUI::CerrarDocumento()
{
    setCurrentIndex(0);
    LibroAbierto = false;
    emitCerrado();
}

void DocsIconUI::AbrirDocumento()
{
    setCurrentIndex(1);
    LibroAbierto = true;
    emitAbierto();
}

bool DocsIconUI::Mostrando() const
{
    return mostrando;
}

bool DocsIconUI::getLibroAbierto() const
{
    return LibroAbierto;
}

void DocsIconUI::emitAbierto()
{
    emit Abierto();
}

void DocsIconUI::emitCerrado()
{
    emit Cerrado();
}

void DocsIconUI::emitAnimacionSalirTerminada()
{
    hide();
    emit animacionSalirTerminada();
}

void DocsIconUI::emitAnimacionEntrarTerminada()
{
    emit animacionEntrarTerminada();
}
