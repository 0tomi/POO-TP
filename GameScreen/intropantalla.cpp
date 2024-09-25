#include "intropantalla.h"
#include "ui_intropantalla.h"

IntroPantalla::IntroPantalla(Juego *game, QWidget *parent):
    QWidget(parent)
    , ui(new Ui::IntroPantalla)
{
    ui->setupUi(this);
    this->padre = parent;
    this->juego = game;
    this->libro = new libroreglas(game, parent);
    this->libro->hide();

    animacionSalida = new QPropertyAnimation(this, "pos");
    animacionSalida->setDuration(2000);
    animacionSalida->setEasingCurve(QEasingCurve::OutExpo);

    connect(ui->TerminarIntro, &QPushButton::clicked, this, &IntroPantalla::Salir);
    connect(animacionSalida, &QAbstractAnimation::finished, [this](){
        this->hide();
        emit ClickeoEmpezar();
    });
}

void IntroPantalla::Mostrar()
{
    this->libro->Entrar();
}

void IntroPantalla::Salir()
{
    this->libro->Sacar();
    int centerX = ((padre->width()) - (width())) / 2;
    animacionSalida->setStartValue(this->pos());
    animacionSalida->setEndValue(QPoint(centerX, padre->height()));
    animacionSalida->start();
}

void IntroPantalla::setUp(int nivel)
{
    this->libro->setUpLevel(nivel);
    this->show();
}

IntroPantalla::~IntroPantalla()
{
    delete ui;
}
