#include "estanciaui.h"
#include "ui_estanciaui.h"

estanciaUI::estanciaUI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::estanciaUI)
{
    ui->setupUi(this);
    setFixedSize(250, 250);
}

void estanciaUI::setDocumentacionInfo(Documentacion *documento) {
    estanciaInfo = dynamic_cast<Estancia*>(documento);

    ui->tipoVisita->setText(estanciaInfo->getTipoEstancia());
    ui->duracionVisita->setText(QString("%1 MESES").arg(estanciaInfo->getDuracEstancia()));
}

estanciaUI::~estanciaUI()
{
    delete ui;
}
