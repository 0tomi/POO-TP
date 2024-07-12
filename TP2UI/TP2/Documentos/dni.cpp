#include "dni.h"
#include "ui_dni.h"

DNI::DNI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::DNI)
{
    ui->setupUi(this);
    setFixedSize(300,300);
}
void DNI::setDNIInfo(Pasaporte * dni, NPCUI * npc){
    ui->nombre->setText(dni->getnombre());
    ui->fecha->setText(dni->getfecha_nacimiento());
    ui->genero->setText(QString(dni->getgenero()));
    ui->nacionalidad->setText(dni->getnacionalidad());
    ui->estado_civil->setText(dni->getestado_civil());
}

void DNI::setDocumentacionInfo(Documentacion *documento)
{

}

DNI::~DNI()
{
    delete ui;
}
