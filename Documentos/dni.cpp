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
    NPCenDoc->show();
}
void DNI::setDNIInfo(Pasaporte * dni, NPC * npc){
    NPCenDoc->setNPC(npc);

    ui->nombre->setText(dni->getnombre());
    ui->fecha->setText(dni->getfecha_nacimiento());
    ui->genero->setText(QString(dni->getgenero()));
    ui->estado_civil->setText(dni->getestado_civil());
}

void DNI::setDocumentacionInfo(Documentacion *documento)
{

}

DNI::~DNI()
{
    delete ui;
}
