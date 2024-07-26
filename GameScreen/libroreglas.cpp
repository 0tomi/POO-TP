#include "libroreglas.h"
#include "ui_libroreglas.h"
#include <QDebug>
libroreglas::libroreglas(ReglasNivel1 * rules, AtributosComunes * atributos,QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::libroreglas)
{
    ui->setupUi(this);
    ui->LibroReglas->setCurrentIndex(0);
    ui->StackedBotones->setCurrentIndex(2);
    this->ruleslvl1 = rules;
    this->atributos = atributos;
    setBotones();
    setDatosPag1();
    hide();

}
void setDocumentacionInfo(Documentacion *documento){

}

void libroreglas::setBotones(){
    connect(ui->Anterior, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->Anterior_2, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->Siguiente, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);
    connect(ui->Siguiente_2, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);
    connect(ui->BotonPasaporteyEstancia, &QPushButton::clicked,this, &libroreglas::IrPagSiguiente);
    connect(ui->BotonCerrar, &QPushButton::clicked, this, &libroreglas::cerrarLibro);
}

void libroreglas::IrPagSiguiente(){

    int currentIndex = ui->LibroReglas->currentIndex();
    int pageCount = ui->LibroReglas->count();

    // Avanzar al siguiente índice
    if (currentIndex < pageCount - 1) {
        currentIndex++;
        ui->LibroReglas->setCurrentIndex(currentIndex);
    }

    // Mostrar el widget adecuado basado en el índice actual
    if (currentIndex == pageCount - 1) {
        // Si estamos en la última página, solo mostrar el botón "Anterior_2"
        ui->StackedBotones->setCurrentIndex(1);
    } else if (currentIndex == 0) {
        // Si estamos en la primera página, solo mostrar el botón "Siguiente_2"
        ui->StackedBotones->setCurrentIndex(2);
    } else {
        // Si hay páginas anteriores y siguientes, mostrar ambos botones
        ui->StackedBotones->setCurrentIndex(0);
    }

}

void libroreglas::IrPagAnterior(){
    int currentIndex = ui->LibroReglas->currentIndex();

    // Avanzar al siguiente índice
    if (currentIndex > 0) {
        currentIndex--;
        ui->LibroReglas->setCurrentIndex(currentIndex);
    }

    // Mostrar el widget adecuado basado en el índice actual
    if (currentIndex == 0) {
        // Si estamos en la primera página, solo mostrar el boton siguiente
         ui->StackedBotones->setCurrentIndex(2);
    } else if (currentIndex == ui->LibroReglas->count() - 1) {
        // Si estamos en la última página, solo mostrar el boton anterior
         ui->StackedBotones->setCurrentIndex(1);
    } else {
        // Si hay paginas anteriores y siguientes, mostrar ambos botones
         ui->StackedBotones->setCurrentIndex(0);
    }

}


void libroreglas::setDatosPag1(){
    setPaises();
    setFechas();
    setEstadoCivil();
    setDuracionEstancia();
    setTipoDeVisita();
}

void libroreglas::cerrarLibro()
{
    DocumentosUI::Sacar();
}

void libroreglas::setPaises(){
    int maxPaises, maxIndices;
    QString * Paises = this->atributos->getPaises(maxPaises);
    int * IndicesValidos = this->ruleslvl1->getPaisesPermitidos(maxIndices);
    QString Texto = "Paises Validos:\n";
    for(int i = 0; i < maxIndices; i++){
        Texto += Paises[IndicesValidos[i]] + "\n";
    }
    ui->PaisesPermitidos->setText(Texto);
}
void libroreglas::setFechas(){
    QString Texto = "Solo se permitirá la entrada a personas:\n";
    int fechaMin = this->ruleslvl1->getFechaMinPermitida();
    int fechaMax = this->ruleslvl1->getFechaMaxPermitida();
    Texto += "Mayores de:" + QString::number(fechaMin) + " (inclusivo)\n";
    Texto += "Menores de:" + QString::number(fechaMax) + " (inclusivo)\n";
    ui->EdadPermitida->setText(Texto);
}

void libroreglas::setEstadoCivil(){
    int max;
    QString * EstadosCivilesValidos = this->ruleslvl1->getEstadoCivilPermitido(max);
    QString Texto = "Solo Podran ingresar los siguientes estados civiles:\n";
    for (int i = 0; i < max; ++i) {
        Texto += EstadosCivilesValidos[i] + "o/a/x" + "\n";
    }

    ui->EstadoCivilPermitido->setText(Texto);
}
void libroreglas::setDuracionEstancia(){
    QString Texto = "La duracion maxima de estancia es de:\n";
    int duracionMaxima = this->ruleslvl1->getDuracionEstanciaPermitida();
    Texto += QString::number(duracionMaxima) + " Meses";
    ui->DuracionPermitida->setText(Texto);
}
void libroreglas::setTipoDeVisita(){
    QString Texto = "Solo se permitirá la entrada a los siguientes\n tipos de visita:\n";
    QString * tipoVisita = this->ruleslvl1->getTipoDeVisitaValida();
    int Max = this->ruleslvl1->getMaxVisitasPermitidas();
    for (int i = 0; i < Max ; ++i) {
        Texto += tipoVisita[i] + "\n";
    }

    ui->TipoDeVisitaValido->setText(Texto);
}
libroreglas::~libroreglas()
{
    delete ui;
}

void libroreglas::setDocumentacionInfo(Documentacion *documento)
{

}

