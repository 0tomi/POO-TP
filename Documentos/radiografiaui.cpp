#include "radiografiaui.h"
#include "ui_radiografiaui.h"

radiografiaui::radiografiaui(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::radiografiaui), Mostrando(false)
{
    ui->setupUi(this);
    this->hide();
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

void radiografiaui::Entrar()
{
    ui->cuerpo->setCurrentIndex(0);
    DocumentosUI::Entrar();
    Mostrando = true;
}

void radiografiaui::Sacar()
{
    DocumentosUI::Sacar();
    Mostrando = false;
}

void radiografiaui::setmap(){
    for(const auto& objeto: objetos){
        QString ruta= ":/Niveles/Nivel5/Objetos/"+ objeto + ".png";//poner la ruta bien cuando tengamos la carpeta
        QPixmap pixmap(ruta);
        this->items.insert(objeto, pixmap);
    }
}

bool radiografiaui::getMostrando() const
{
    return Mostrando;
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
        for (const auto& objeto: *objetosAniadir){
            auto Item = objeto.Objeto;
            auto LabelActual = this->labelsCuerpo[objeto.ParteCuerpo];

            QPixmap* PixmapActual = &items[Item];
            auto PixmapReescalado = PixmapActual->scaled(LabelActual->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            LabelActual->setPixmap(PixmapReescalado);
        }
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
    this->Sacar();
}



