#include "libroreglas.h"
#include "ui_libroreglas.h"
#include <QDebug>
libroreglas::libroreglas(Juego * datos, QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::libroreglas), pasarPagina(this), moverLibro(this)
{
    ui->setupUi(this);
    pasarPagina.setSource(QUrl("qrc:/Resources/Sonidos/Libro/PasarPagina.WAV"));
    moverLibro.setSource(QUrl("qrc:/Resources/Sonidos/Libro/LibroMovimiento.WAV"));
    setVolume(1.0);

    setFixedSize(708,688);
    juego = datos;

    setUpLevel(1);

    // Mostramos el indice y hacemos que el boton de anterior se oculte.
    PaginaActual = 0;   // Indice
    ui->Anterior->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);

    setBotones();
    hide();
}

void libroreglas::setUpLevel(int level)
{
    setDatosPag1();

    CantidadPaginas = 3;
    ui->Nivel2Boton1->hide();
    ui->Nivel2Boton2->hide();
    ui->Nivel3Boton1->hide();

    if (level >= 2){
        setDatosNivel2();
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
    moverLibro.play();
    DocumentosUI::Entrar();
}

void libroreglas::Sacar()
{
    moverLibro.play();
    DocumentosUI::Sacar();
}

void libroreglas::setVolume(float volumen)
{
    pasarPagina.setVolume(volumen);
    moverLibro.setVolume(volumen - 0.2);
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
    pasarPagina.play();
    PaginaActual++;
    ui->Anterior->show();

    if (PaginaActual == CantidadPaginas-1)
        ui->Siguiente->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
}

void libroreglas::SaltarPagina(int pagina)
{
    pasarPagina.play();
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
    pasarPagina.play();
    PaginaActual--;
    ui->Siguiente->show();

    if (PaginaActual == 0)
        ui->Anterior->hide();

    ui->LibroReglas->setCurrentIndex(PaginaActual);
}

void libroreglas::setDatosPag1(){
    // Reglas 1 esta en la posicion 0
    Reglas* test = juego->getReglas(0);
    ReglasNivel1 * rules = dynamic_cast<ReglasNivel1*>(test);

    setPaises(rules);
    setFechas(rules);
    setEstadoCivil(rules);
    setDuracionEstancia(rules);
    setTipoDeVisita(rules);
}

void libroreglas::setDatosNivel2()
{
    ReglasNivel2* reglas = dynamic_cast<ReglasNivel2*>(juego->getReglas(1));
    if (!reglas)
        qDebug() << "Fallo al castear reglas de nivel 2 en libro de reglas";
    QString texto;
    int max;

    QString* paises = reglas->getPaisesInvalidos(max);

    for (int i = 0; i < max; i++)
        texto += "- " + paises[i] + "\n";

    ui->PaisesResidenciaInvalidos->setText(texto);
    delete[] paises;
}

void libroreglas::setDatosNivel3()
{
    ReglasNivel3* reglas = dynamic_cast<ReglasNivel3*>(juego->getReglas(2));
    if (!reglas)
        qDebug() << "Fallo al castear reglas de nivel 3 en libro de reglas";

    int maxAcompaniantes = reglas->getMaxAcompaniantes();
    switch (maxAcompaniantes){
    case 0: ui->CantAcompsPermitida->setText("No se permiten acompaniantes.");
        break;
    case 1: ui->CantAcompsPermitida->setText("Se permite como máximo 1 acompaniante.");
        break;
    case 2: ui->CantAcompsPermitida->setText("Se permite como máximo 2 acompaniantes.");
        break;
    default: ui->CantAcompsPermitida->setText("Se permite como máximo 3 acompaniantes.");
    }
}

void libroreglas::setPaises(ReglasNivel1 * datos){
    int maxIndices;
    int maxPaises;
    QString * Paises = datos->getPaises(maxPaises);
    int * IndicesInv = datos->getPaisesInvalidos(maxIndices);

    QString Texto = "Paises no permitidos:\n";
    for(int i = 0; i < maxIndices; i++){
        Texto += Paises[IndicesInv[i]] + "\n";
    }
    ui->PaisesPermitidos->setText(Texto);
}
void libroreglas::setFechas(ReglasNivel1 * datos){
    QString Texto = "Solo se permiten personas:\n";
    int fechaMin = datos->getFechaMinPermitida();
    int fechaMax = datos->getFechaMaxPermitida();
    Texto += "Mayores de:" + QString::number(fechaMin) + " (inclusivo)\n";
    Texto += "Menores de:" + QString::number(fechaMax) + " (inclusivo)\n";
    ui->EdadPermitida->setText(Texto);
}

void libroreglas::setEstadoCivil(ReglasNivel1 * datos){
    int max;
    QString * EstadosCivilesValidos = datos->getEstadoCivilPermitido(max);
    QString Texto = "Solo podran ingresar los \nsiguientes estados civiles:\n";
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
    QString Texto = "Solo se permitirá la \nentrada a los siguientes\n tipos de visita:\n";
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

