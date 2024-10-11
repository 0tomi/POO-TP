#include "pantallatransicion.h"
#include "ui_pantallatransicion.h"

/// ################################# CONSTRUCTOR #########################################
PantallaTransicion::PantallaTransicion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaTransicion)
{
    ui->setupUi(this);
    ui->Cargando->hide();

    mostrando = false;

    // Armo pantalla para las transiciones
    this->resize(parent->size());
    hide();

    // Damos opacidad 0 para que aparezca la pantalla y no se vea
    this->efecto = new QGraphicsOpacityEffect(this);
    efecto->setOpacity(0);
    setGraphicsEffect(efecto);

    // Animacion para que aparezca el fondo
    this->iniciarTransicion = new QPropertyAnimation(efecto, "opacity");
    iniciarTransicion->setStartValue(0.0); // opacidad inicial (invisible)
    iniciarTransicion->setEndValue(1.0); // opacidad final (visible)

    // Animacion para que desaparezca el fondo
    this->terminarTransicion = new QPropertyAnimation(efecto, "opacity");
    terminarTransicion->setStartValue(1.0); // opacidad inicial (visible)
    terminarTransicion->setEndValue(0.0); // opacidad final (invisible)

    // Conectamos el final de la animacion de inicio, con la de la animacion de final.
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &PantallaTransicion::MidTransicion);
    connect(terminarTransicion, &QAbstractAnimation::finished, this, &PantallaTransicion::TerminarTransicion);
}

PantallaTransicion::~PantallaTransicion()
{
    delete ui;
    delete iniciarTransicion;
    delete terminarTransicion;
}

void PantallaTransicion::MidTransicion()
{
    emit midAnimacion();
    terminarTransicion->start();
    metodo2ejecutar();
}

void PantallaTransicion::TerminarTransicion()
{
    mostrando = false;
    emit terminoAnimacion();
    ui->Cargando->hide();
    hide();
}

bool PantallaTransicion::Mostrando() const
{
    return mostrando;
}

void PantallaTransicion::ArrancarTransicion(int duracion, std::function<void ()> func)
{
    ui->Cargando->hide();
    metodo2ejecutar = func;

    iniciarTransicion->setDuration(duracion); // duración en milisegundos
    terminarTransicion->setDuration(duracion);

    // Colocamos la opacidad en 0 para arrancar la animacion
    efecto->setOpacity(0);

    show();
    mostrando = true;
    iniciarTransicion->start();
}

void PantallaTransicion::ArrancarTransicionCargando(int duracion, std::function<void ()> func)
{
    ui->Cargando->show();
    metodo2ejecutar = func;

    iniciarTransicion->setDuration(duracion); // duración en milisegundos
    terminarTransicion->setDuration(duracion);

    // Colocamos la opacidad en 0 para arrancar la animacion
    efecto->setOpacity(0);

    show();
    mostrando = true;
    iniciarTransicion->start();
}
