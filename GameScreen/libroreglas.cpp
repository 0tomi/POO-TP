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

    DocumentosUI::DesactivarEventosMouse();
}

void libroreglas::setUpLevel(int level)
{
    setDatosPag1();

    CantidadPaginas = 3;
    ui->Nivel2Boton1->hide();
    ui->Nivel2Boton2->hide();
    ui->Nivel3Boton1->hide();
    ui->Nivel4Boton1->hide();
    ui->Nivel5boton1->hide();

    if (level >= 2){
        setDatosNivel2();
        CantidadPaginas = 4;
        ui->Nivel2Boton1->show();
        ui->Nivel2Boton2->show();
    }
    if (level >= 3){
        setDatosNivel3();
        CantidadPaginas = 5;
        ui->Nivel3Boton1->show();
    }
    if (level >= 4){
        setDatosNivel4();
        CantidadPaginas = 6;
        ui->Nivel4Boton1->show();
    }
    if (level >= 5){
        setDatosNivel5();
        CantidadPaginas = 7;
        ui->Nivel5boton1->show();
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
    connect(ui->Anterior, &QPushButton::clicked, [this](){ this->PasarPagina(ui->LibroReglas->currentIndex()-1); });
    connect(ui->Siguiente, &QPushButton::clicked, [this](){ this->PasarPagina(ui->LibroReglas->currentIndex()+1); });

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

    connect(ui->Nivel4Boton1, &QPushButton::clicked, [this]() {
        SaltarPagina(5);
    });
    connect(ui->Nivel5boton1,&QPushButton::clicked, [this](){
        SaltarPagina(6);
    });
}

void libroreglas::PasarPagina(int pag)
{
    pasarPagina.play();
    // Caso primer pagina
    if (pag == 0)
        ui->Anterior->hide();
    else ui->Anterior->show();

    // Caso ultima pagina
    if (pag == CantidadPaginas-1)
        ui->Siguiente->hide();
    else ui->Siguiente->show();

    ui->LibroReglas->setCurrentIndex(pag);
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

void libroreglas::setDatosPag1(){
    // Reglas 1 esta en la posicion 0
    Reglas* test = juego->getReglas(0);
    ReglasNivel1 * rules = dynamic_cast<ReglasNivel1*>(test);
    if (!rules){
        qDebug() << "Fallo al castear reglas de nivel 1 en libro de reglas";
        return;
    }

    setPaises(rules);
    setFechas(rules);
    setEstadoCivil(rules);
    setDuracionEstancia(rules);
    setTipoDeVisita(rules);
}

void libroreglas::setDatosNivel2()
{
    ReglasNivel2* reglas = dynamic_cast<ReglasNivel2*>(juego->getReglas(1));
    if (!reglas){
        qDebug() << "Fallo al castear reglas de nivel 2 en libro de reglas";
        return;
    }

    setDatos(reglas->getPaisesValidos(), ui->PaisesResidenciaInvalidos);
}

void libroreglas::setDatosNivel3()
{
    ReglasNivel3* reglas = dynamic_cast<ReglasNivel3*>(juego->getReglas(2));
    if (!reglas){
        qDebug() << "Fallo al castear reglas de nivel 3 en libro de reglas";
        return;
    }

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

void libroreglas::setDatosNivel4()
{
    auto reglas = dynamic_cast<ReglasNivel4*>(juego->getReglas(3));
    if (!reglas){
        qDebug() << "Fallo al castear reglas de nivel 4 en el libro de reglas";
        return;
    }

    setDatos(reglas->getBienesTransportadosPermitidos(), ui->ListaBienesPermitidos);
    setDatos(reglas->getPaisesPermitidos(), ui->ListaPaisesPermitidos);
    setDatos(reglas->getOcupacionPermitidos(), ui->ListaOcupacionesPermitidas);
}

void libroreglas::setDatosNivel5()
{
    LectorArchivos archivo(":/Niveles/Nivel5/ObjetosInvalidos.txt");
    setDatos(archivo.getVector(),ui->ObjetosRadiografiaIlegales);
    archivo.LeerArchivoNuevo(":/Niveles/Nivel5/ObjetosValidos.txt");
    setDatos(archivo.getVector(),ui->ObjetosRadiografiaLegales);
}

void libroreglas::setDatos(const vector<QString> &lineas, QLabel* lugarDondeSeColocaElTexto)
{
    QString texto;
    for (const auto& linea: lineas)
        texto += "- " + linea + "\n";
    lugarDondeSeColocaElTexto->setText(texto);
}

void libroreglas::setPaises(ReglasNivel1 * datos){
    setDatos(datos->getPaisesPermitidos(), ui->PaisesPermitidos);
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
    vector<QString>  EstadosCivilesValidos = datos->getEstadoCivilPermitido();
    QString Texto = "Solo podran ingresar los \nsiguientes estados civiles:\n";
    for (int i = 0; i < EstadosCivilesValidos.size(); ++i) {
        Texto += EstadosCivilesValidos[i] + "o/a/x" + "\n";
    }

    ui->EstadoCivilPermitido->setText(Texto);
}
void libroreglas::setDuracionEstancia(ReglasNivel1 * datos){
    QString Texto;
    int duracionMaxima = datos->getDuracionEstanciaPermitida();
    Texto += QString::number(duracionMaxima) + " Meses";
    ui->DuracionPermitida->setText(Texto);
}
void libroreglas::setTipoDeVisita(ReglasNivel1 * datos){
    QString Texto;
    vector<QString> tipoVisita = datos->getTipoDeVisitaValida();
    for (int i = 0; i < tipoVisita.size() ; ++i) {
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

