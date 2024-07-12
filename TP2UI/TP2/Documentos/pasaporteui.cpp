#include "pasaporteui.h"
#include "ui_pasaporteui.h"

PasaporteUI::PasaporteUI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::PasaporteUI)
{
    ui->setupUi(this);
    setFixedSize(300,300);
    this->aux_npc = new NPCGenericoUI;
}
void PasaporteUI::setDocumentacionInfo(Pasaporte * pasaporte, NPC * npc) {
    ui->nombre->setText(pasaporte->getnombre());
    ui->fecha->setText(pasaporte->getfecha_nacimiento());
    ui->genero->setText(QString(pasaporte->getgenero()));
    ui->nacionalidad->setText(pasaporte->getnacionalidad());
    ui->estado_civil->setText(pasaporte->getestado_civil());
}
void setDocumentacionInfo(Documentacion *documento){

}
PasaporteUI::~PasaporteUI()
{
    delete ui;
}
