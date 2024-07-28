#include "libroreglas.h"
#include "ui_libroreglas.h"
#include <QDebug>
libroreglas::libroreglas(Juego * datos, QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::libroreglas)
{
    ui->setupUi(this);

    setUpLevel(1);

    // Mostramos el indice y hacemos que el boton de anterior se oculte.
    PaginaActual = 0;   // Indice
    ui->Anterior->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
    for (int i = 0; i < 5; i++)
        reglas[i] = datos->getReglas(i);

    setBotones();
    setDatosPag1();
    hide();
}
void setDocumentacionInfo(Documentacion *documento){

}

void libroreglas::setBotones(){
    connect(ui->Anterior, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->Siguiente, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);
    connect(ui->BotonPasaporteyEstancia, &QPushButton::clicked,this, &libroreglas::IrPagSiguiente);
}

void libroreglas::IrPagSiguiente(){
    PaginaActual++;
    ui->Anterior->show();

    if (PaginaActual == CantidadPaginas-1)
        ui->Siguiente->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
}

void libroreglas::IrPagAnterior(){
    PaginaActual--;
    ui->Siguiente->show();

    if (PaginaActual == 0)
        ui->Anterior->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
}

void libroreglas::setDatosPag1(){
    // Reglas 1 esta en la posicion 0
    ReglasNivel1 * rules = dynamic_cast<ReglasNivel1*>(reglas[0]);

    setPaises(rules);
    setFechas(rules);
    setEstadoCivil(rules);
    setDuracionEstancia(rules);
    setTipoDeVisita(rules);
}

void libroreglas::setPaises(ReglasNivel1 * datos){
    int maxIndices;

    QString * Paises = datos->getPaises();
    int * IndicesValidos = datos->getPaisesPermitidos(maxIndices);

    QString Texto = "Paises Validos:\n";
    for(int i = 0; i < maxIndices; i++){
        Texto += Paises[IndicesValidos[i]] + "\n";
    }
    ui->PaisesPermitidos->setText(Texto);
}
void libroreglas::setFechas(ReglasNivel1 * datos){
    QString Texto = "Solo se permitirá la entrada a personas:\n";
    int fechaMin = datos->getFechaMinPermitida();
    int fechaMax = datos->getFechaMaxPermitida();
    Texto += "Mayores de:" + QString::number(fechaMin) + " (inclusivo)\n";
    Texto += "Menores de:" + QString::number(fechaMax) + " (inclusivo)\n";
    ui->EdadPermitida->setText(Texto);
}

void libroreglas::setEstadoCivil(ReglasNivel1 * datos){
    int max;
    QString * EstadosCivilesValidos = datos->getEstadoCivilPermitido(max);
    QString Texto = "Solo Podran ingresar los siguientes estados civiles:\n";
    for (int i = 0; i < max; ++i) {
        Texto += EstadosCivilesValidos[i] + "o/a/x" + "\n";
    }

    ui->EstadoCivilPermitido->setText(Texto);
}
void libroreglas::setDuracionEstancia(ReglasNivel1 * datos){
    QString Texto = "La duracion maxima de estancia es de:\n";
    int duracionMaxima = datos->getDuracionEstanciaPermitida();
    Texto += QString::number(duracionMaxima) + " Meses";
    ui->DuracionPermitida->setText(Texto);
}
void libroreglas::setTipoDeVisita(ReglasNivel1 * datos){
    QString Texto = "Solo se permitirá la entrada a los siguientes\n tipos de visita:\n";
    QString * tipoVisita = datos->getTipoDeVisitaValida();
    int Max = datos->getMaxVisitasPermitidas();
    for (int i = 0; i < Max ; ++i) {
        Texto += tipoVisita[i] + "\n";
    }

    ui->TipoDeVisitaValido->setText(Texto);
}
libroreglas::~libroreglas()
{
    delete ui;
}

void libroreglas::setUpLevel(int level)
{
    switch (level){
    case 1: CantidadPaginas = 2;
        break;
    case 2: CantidadPaginas = 2;
        break;
    case 3: CantidadPaginas = 2;
        break;
    case 4: CantidadPaginas = 2;
        break;
    default: CantidadPaginas = 2;
        break;
    }
}

void libroreglas::setDocumentacionInfo(Documentacion *documento)
{

}

