#include "dni.h"
#include "ui_dni.h"

DNI::DNI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::DNI)
{
    ui->setupUi(this);
    setFixedSize(300,300);

    this->NPCenDoc = new NPCGenericoUI(ui->NPC);
    NPCenDoc->setFixedSize(100,100);

    filtro = new QGraphicsOpacityEffect(ui->filtro);
    filtro->setOpacity(0.5);
    ui->filtro->setGraphicsEffect(filtro);
    ui->filtro->raise();
}

void DNI::setDocumentacionInfo(Documentacion *documento)
{
    Pasaporte * dni = dynamic_cast<Pasaporte*>(documento);

    if (!dni)
        qDebug() << "DNI NULO";

    NPCenDoc->setSkinNPC(dni->getSkinNPC());

    ui->nombre->setText(dni->getnombre());
    ui->fecha->setText(dni->getfecha_nacimiento());
    ui->genero->setText(QString(dni->getgenero()));
    ui->estado_civil->setText(dni->getestado_civil());
}

DNI::~DNI()
{
    delete ui;
}
