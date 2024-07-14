#include "pasaporteui.h"
#include "ui_pasaporteui.h"

PasaporteUI::PasaporteUI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::PasaporteUI)
{
    ui->setupUi(this);
    setFixedSize(300,408);
    this->aux_npc = new NPCGenericoUI;
}
void PasaporteUI::setPasaporteInfo(Pasaporte * pasaporte, NPC * npc) {
    setStandby();
    ui->nombre->setText(pasaporte->getnombre());
    ui->fecha->setText(pasaporte->getfecha_nacimiento());
    ui->genero->setText(QString(pasaporte->getgenero()));
    ui->nacionalidad->setText(pasaporte->getnacionalidad());
    ui->estado_civil->setText(pasaporte->getestado_civil());
}

void PasaporteUI::setDocumentacionInfo(Documentacion *documento)
{

}

void PasaporteUI::setStandby()
{
    ui->stackedWidget->setCurrentWidget(ui->stand);
}

void PasaporteUI::setAprobado()
{
    ui->stackedWidget->setCurrentWidget(ui->Aprobado);
}

void PasaporteUI::setRechazado()
{
    ui->stackedWidget->setCurrentWidget(ui->Rechazado);
}

PasaporteUI::~PasaporteUI()
{
    delete ui;
}