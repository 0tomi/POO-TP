#include "intropantalla.h"
#include "ui_intropantalla.h"

IntroPantalla::IntroPantalla(Juego *game, QWidget *parent):
    QWidget(parent)
    , ui(new Ui::IntroPantalla)
{
    ui->setupUi(this);
    this->juego = game;
    this->libro = new libroreglas(game, parent);
    this->libro->hide();
}

void IntroPantalla::Mostrar()
{
    this->show();
    this->libro->Entrar();
}

void IntroPantalla::setUp(int nivel)
{
    this->libro->setUpLevel(nivel);
}

IntroPantalla::~IntroPantalla()
{
    delete ui;
}
