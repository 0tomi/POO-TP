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
    this->libro->Entrar();
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
