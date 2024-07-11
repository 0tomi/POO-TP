#include "estanciaui.h"
#include "ui_estanciaui.h"

estanciaUI::estanciaUI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::estanciaUI)
{
    ui->setupUi(this);
    setFixedSize(200, 200);
}

estanciaUI::setDocumentacionInfo(Documentacion *documento) {
    ui->tipoVisita->setText(estancia->getTipoEstancia());
    ui->duracionVisita->setText(QString("%1 MESES").arg(estancia->getDuracEstancia()));
}

estanciaUI::~estanciaUI()
{
    delete ui;
}
