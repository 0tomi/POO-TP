#include "libroreglas.h"
#include "ui_libroreglas.h"
#include <QDebug>
libroreglas::libroreglas(Juego * datos, QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::libroreglas)
{
    ui->setupUi(this);
    setFixedSize(708,688);

    setUpLevel(1);

    // Mostramos el indice y hacemos que el boton de anterior se oculte.
    PaginaActual = 0;   // Indice
    ui->Anterior->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);

    // Setup de reglas
    for (int i = 0; i < 5; i++)
        reglas[i] = datos->getReglas(i);

    setBotones();
    setDatosPag1();
    hide();
}

void libroreglas::setUpLevel(int level)
{
    CantidadPaginas = 3;
    ui->Nivel2Boton1->hide();
    ui->Nivel2Boton2->hide();
    ui->Nivel3Boton1->hide();

    if (level >= 2){
        CantidadPaginas = 4;
        ui->Nivel2Boton1->show();
        ui->Nivel2Boton2->show();
    }
    if (level >= 3){
        CantidadPaginas = 5;
        ui->Nivel3Boton1->show();
    }
    if (level >= 4){

    }
    if (level >= 5){

    }
}

void libroreglas::Entrar()
{
    raise();
    DocumentosUI::Entrar();
}

void setDocumentacionInfo(Documentacion *documento){

}

void libroreglas::setBotones(){
    connect(ui->Anterior, &QPushButton::clicked, this,&libroreglas::IrPagAnterior);
    connect(ui->Siguiente, &QPushButton::clicked, this,&libroreglas::IrPagSiguiente);

    // Botones del indice
    connect(ui->BotonPasaporteyEstancia, &QPushButton::clicked, [this]() {
        SaltarPagina(1);
    });

    // Ir a tipos de NPCs
    connect(ui->BotonTipos, &QPushButton::clicked, [this]() {
        SaltarPagina(2);
    });

    // Ir a requisitos de nivel 2
    connect(ui->Nivel2Boton1, &QPushButton::clicked, [this]() {
        SaltarPagina(3);
    });

    connect(ui->Nivel2Boton2, &QPushButton::clicked, [this]() {
        SaltarPagina(3);
    });

    // Ir a requisitos de nivel 3
    connect(ui->Nivel3Boton1, &QPushButton::clicked, [this]() {
        SaltarPagina(4);
    });
}

void libroreglas::IrPagSiguiente(){
    PaginaActual++;
    ui->Anterior->show();

    if (PaginaActual == CantidadPaginas-1)
        ui->Siguiente->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
}

void libroreglas::SaltarPagina(int pagina)
{
    if (pagina != 0)
        ui->Anterior->show();
    else
        ui->Anterior->hide();

    if (pagina == CantidadPaginas-1)
        ui->Siguiente->hide();

    ui->LibroReglas->setCurrentIndex(pagina);
    PaginaActual = pagina;
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
    int * IndicesInv = datos->getPaisesInvalidos(maxIndices);

    QString Texto = "Paises no permitidos:\n";
    for(int i = 0; i < maxIndices; i++){
        Texto += Paises[IndicesInv[i]] + "\n";
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

void libroreglas::setDocumentacionInfo(Documentacion *documento)
{

}

