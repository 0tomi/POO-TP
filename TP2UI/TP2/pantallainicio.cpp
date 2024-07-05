#include "pantallainicio.h"
#include "ui_pantallainicio.h"

PantallaInicio::PantallaInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaInicio)
{
    ui->setupUi(this);
    connect(ui->comenzarJuego, &QPushButton::clicked, this, &PantallaInicio::empezarJuego);
}

void PantallaInicio::empezarJuego()
{
    emit ClickeoBotonEmpezar();
}

PantallaInicio::~PantallaInicio()
{
    delete ui;
}
