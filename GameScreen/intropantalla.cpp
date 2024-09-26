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
    animacionSalida->setDuration(1500);
    animacionSalida->setEasingCurve(QEasingCurve::OutExpo);

    connect(ui->TerminarIntro, &QPushButton::clicked, this, &IntroPantalla::Salir);
    connect(animacionSalida, &QAbstractAnimation::finished, [this](){
        this->hide();
        int CentroX = (padre->width() - this->width()) / 2;
        int CentroY = (padre->height() - this->height()) / 2;
        this->move(QPoint(CentroX, CentroY));
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

void IntroPantalla::setVolumenes(float volumen)
{
    libro->setVolume(volumen);
}