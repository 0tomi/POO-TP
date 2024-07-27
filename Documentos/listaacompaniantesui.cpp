#include "listaacompaniantesui.h"
#include "ui_listaacompaniantesui.h"
#include "listaacompaniantes.h"
#include "../Generadores/generadorlistaacompaniantes.h"

ListaAcompaniantesUI::ListaAcompaniantesUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaAcompaniantesUI)
{
    ui->setupUi(this);

    GeneradorListaAcompaniantes* generador = new GeneradorListaAcompaniantes();
    ListaAcompaniantes* listaAcomp = generador->getListaAcompaniantes();

    QString msjSinAcomp = listaAcomp->getMensajeSinAcomp();
    QString* arrAcomps = listaAcomp->getNombresAcomps();
    int topeArr = listaAcomp->getTopeNombresAcomps();

    if (topeArr == 0) { // No tiene acomp
        ui->stackedW->setCurrentIndex(0);
        ui->sinAcompText->setText(msjSinAcomp);
    } else {
        ui->stackedW->setCurrentIndex(1);
        switch(topeArr) {
            case 1: // tiene un acomp.
                ui->acomp1->setText(arrAcomps[0]);
                break;
            case 2: // tiene 2 acomps.
                ui->acomp1->setText(arrAcomps[0]);
                ui->acomp2->setText(arrAcomps[1]);
                break;
            case 3:
                ui->acomp1->setText(arrAcomps[0]);
                ui->acomp2->setText(arrAcomps[1]);
                ui->acomp3->setText(arrAcomps[2]);
                break;
        }
    }
}

ListaAcompaniantesUI::~ListaAcompaniantesUI()
{
    delete ui;
}
