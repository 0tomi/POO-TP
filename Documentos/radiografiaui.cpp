#include "radiografiaui.h"
#include "ui_radiografiaui.h"

radiografiaui::radiografiaui(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::radiografiaui)
{
    ui->setupUi(this);
    this->labelsCuerpo[0]=ui->frente1;
    this->labelsCuerpo[1]=ui->frente2;
    this->labelsCuerpo[2]=ui->frente3;
    this->labelsCuerpo[3]=ui->frente4;
    this->labelsCuerpo[4]=ui->frente5;
    this->labelsCuerpo[5]=ui->espalda1;
    this->labelsCuerpo[6]=ui->espalda2;
    this->labelsCuerpo[7]=ui->espalda3;
    this->labelsCuerpo[8]=ui->espalda4;
    this->labelsCuerpo[9]=ui->espalda5;
    LectorArchivos lector(":/Niveles/Nivel5/Objetos.txt");
    this->objetos=lector.getVector();
    setmap();
}

void radiografiaui::setmap(){
    for(int i=0;i < this->objetos.size();i++){
        QString ruta= ":/Niveles/Nivel5/carpeta"+this->objetos[i]+".png";//poner la ruta bien cuando tengamos la carpeta
        QPixmap pixmap(ruta);
        this->items.insert(this->objetos[i], pixmap);

    }
}
void radiografiaui::setLabels(radiografia* datos){
    vector<ParDatos>objetosAniadir = datos->GetVector();
    for (auto& label : this->labelsCuerpo) {
        if (label) {
            label->clear();  // Libera el QPixmap actual
        }
    }
    if(objetosAniadir.empty()){
        return;
    }else {
        for(int i = 0; i < objetosAniadir.size(); i++){
            this->labelsCuerpo[objetosAniadir[i].ParteCuerpo]->setPixmap(this->items[objetosAniadir[i].Objeto]);
        }
    }
}
radiografiaui::~radiografiaui()
{
    delete ui;
}
