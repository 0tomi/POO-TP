#include "libroreglas.h"
#include "ui_libroreglas.h"
#include <QDebug>
libroreglas::libroreglas(QWidget *parent)//, ReglasNivel1 * rules)
    : QWidget(parent)
    , ui(new Ui::libroreglas)
{
    ui->setupUi(this);
    ui->LibroReglas->setCurrentIndex(0);
    //this->ruleslvl1 = rules;
    this->atributos = new AtributosComunes;
    this->archi = new LectorArchivos(":/Resources/ArchivosTexto/paises.txt");
    this->atributos->setAtributos(archi->getArray(), archi->getTopeArray());
    this->ruleslvl1 = new ReglasNivel1(this->atributos);
    setBotones();
    setDatosPag1();

}
/*void setDocumentacionInfo(Documentacion *documento){
    qDebug() << "hola";
}*/

void libroreglas::setBotones(){
    connect(ui->BotonAnterior, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->BotonSiguiente, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);
}

void libroreglas::IrPagSiguiente(){
    int currentIndex = ui->LibroReglas->currentIndex();
    if (currentIndex < ui->LibroReglas->count() - 1) {
        ui->LibroReglas->setCurrentIndex(currentIndex + 1);
    }
}

void libroreglas::IrPagAnterior(){
    int currentIndex = ui->LibroReglas->currentIndex();
    if (currentIndex > 0) {
        ui->LibroReglas->setCurrentIndex(currentIndex - 1);
    }
}

void libroreglas::setDatosPag1(){
    int maxPaises, maxIndices;
    QString * Paises = this->atributos->getPaises(maxPaises);
    int * IndicesValidos = this->ruleslvl1->getPaisesPermitidos(maxIndices);
    QString Texto = "Paises Validos:\n";
    for(int i = 0; i < maxIndices; i++){
        Texto += Paises[IndicesValidos[i]] + "\n";
    }
    ui->PaisesPermitidos->setText(Texto);
    delete[] Paises;
}
libroreglas::~libroreglas()
{
    delete ui;
}

