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

void radiografiaui::setDocumentacionInfo(Documentacion *documento)
{
    auto Radiografia = dynamic_cast<radiografia*>(documento);
    if (Radiografia)
        setLabels(Radiografia);
    else qDebug() << "Fallo al castear puntero de radiografia";
}

void radiografiaui::setmap(){
    for(const auto& objeto: objetos){
        QString ruta= ":/Niveles/Nivel5/Objetos/"+ objeto + ".png";//poner la ruta bien cuando tengamos la carpeta
        QPixmap pixmap(ruta);
        this->items.insert(objeto, pixmap);
    }
}
void radiografiaui::setLabels(radiografia* datos){
    auto objetosAniadir = &datos->GetVector();
    for (auto& label : this->labelsCuerpo) {
        if (label) {
            label->clear();  // Libera el QPixmap actual
        }
    }
    if(objetosAniadir->empty()){
        return;
    }else {
        for (const auto& objeto: *objetosAniadir)
            this->labelsCuerpo[objeto.ParteCuerpo]->setPixmap(this->items[objeto.Objeto]); // Esto es peligroso por como funcionan los mapas
    }
}
radiografiaui::~radiografiaui()
{
    delete ui;
}

void radiografiaui::on_voltear1_clicked()
{
    int indiceActual = ui->cuerpo->currentIndex(); // Obtener el índice actual

    // Alternar entre las páginas 0 y 1
    int nuevoIndice = (indiceActual == 0) ? 1 : 0; // Si está en 0, cambiar a 1 y viceversa

    ui->cuerpo->setCurrentIndex(nuevoIndice); // Cambiar a la nueva página
}


void radiografiaui::on_voltear2_clicked()
{
    int indiceActual = ui->cuerpo->currentIndex();
    int nuevoIndice = (indiceActual == 0) ? 1 : 0;
    ui->cuerpo->setCurrentIndex(nuevoIndice);
}


void radiografiaui::on_botonsalir_clicked()
{
    DocumentosUI::Sacar();
}



