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
void setDocumentacionInfo(Documentacion *documento){

}

void libroreglas::setBotones(){
    connect(ui->BotonAnterior, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->BotonSiguiente, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);
    connect(ui->BotonPasaporteyEstancia, &QPushButton::clicked,this, &libroreglas::IrPagSiguiente);
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
    setPaises();
    setFechas();
    setEstadoCivil();
    setDuracionEstancia();
    setTipoDeVisita();
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
    delete[] Paises;
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
    delete[] EstadosCivilesValidos;
    ui->EstadoCivilPermitido->setText(Texto);
}
void libroreglas::setDuracionEstancia(){
    QString Texto = "La duracion maxima de estancia es de:\n";
    int duracionMaxima = this->ruleslvl1->getDuracionEstanciaPermitida();
    Texto += QString::number(duracionMaxima) + " Meses";
    ui->DuracionPermitida->setText(Texto);
}
void libroreglas::setTipoDeVisita(){
    QString Texto = "Solo se permitirá la entrada a los siguientes tipos de visita:\n";
    QString * tipoVisita = this->ruleslvl1->getTipoDeVisitaValida();
    int Max = this->ruleslvl1->getMaxVisitasPermitidas();
    for (int i = 0; i < Max ; ++i) {
        Texto += tipoVisita[i] + "\n";
    }
    delete[] tipoVisita;
    ui->TipoDeVisitaValido->setText(Texto);
}
libroreglas::~libroreglas()
{
    delete ui;
}

