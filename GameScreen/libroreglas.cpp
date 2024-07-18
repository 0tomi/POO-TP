#include "libroreglas.h"
#include "ui_libroreglas.h"


LibroReglas::LibroReglas(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::LibroReglas)
{
    ui->setupUi(this);


    // hacer residencia
}

LibroReglas::~LibroReglas()
{
    delete ui;
}

void LibroReglas::setBotones() {
    // Conectar los botones a las funciones correspondientes
    connect(ui->boton_siguiente, &QPushButton::clicked, this, &LibroReglas::mostrarPaginaSiguiente);
    connect(ui->Boton_anterior, &QPushButton::clicked, this, &LibroReglas::mostrarPaginaAnterior);
    connect(ui->reglasnivel1,&QPushButton::clicked,this, &LibroReglas::IrAPagina1);

    // Actualizar la visibilidad de los botones al iniciar
    int index = ui->PaginasLibro->currentIndex();
    ui->Boton_anterior->setVisible(index != 0);
    ui->boton_siguiente->setVisible(index != ui->PaginasLibro->count() - 1);
}

void LibroReglas::mostrarPaginaSiguiente() {
    int currentIndex = ui->PaginasLibro->currentIndex();
    if (currentIndex < ui->PaginasLibro->count() - 1) {
        ui->PaginasLibro->setCurrentIndex(currentIndex + 1);
    }

    // Actualizar la visibilidad de los botones después de cambiar la página
    ui->Boton_anterior->setVisible(true);
    ui->boton_siguiente->setVisible(currentIndex + 1 != ui->PaginasLibro->count() - 1);
}


void LibroReglas::mostrarPaginaAnterior() {
    int currentIndex = ui->PaginasLibro->currentIndex();
    if (currentIndex > 0) {
        ui->PaginasLibro->setCurrentIndex(currentIndex - 1);
    }

    // Actualizar la visibilidad de los botones después de cambiar la página
    ui->boton_siguiente->setVisible(true);
    ui->Boton_anterior->setVisible(currentIndex - 1 != 0);
}

void LibroReglas::setUpPagina1(){
    int max, max_validos;
    QString * paises = this->atributos->getPaises(max);
    QString Texto_aniadir = " ";
    int * IndicesValidos = this->rules->getPaisesPermitidos(max_validos);
    for (int i = 0; i < max_validos; ++i) {
        Texto_aniadir += paises[IndicesValidos[i]] + "\n";
    }

    ui->Reglas_paises->setText(Texto_aniadir);
    QString * VisitasValidas = this->rules->getTipoDeVisitaValida();
    max_validos = rules->getMaxVisitasPermitidas();
    Texto_aniadir = " ";
    for (int i = 0; i < max_validos; ++i) {
        Texto_aniadir += VisitasValidas[i] + "\n";
    }
    ui->Reglas_estancia->setText(Texto_aniadir);

    delete[] paises;
    delete[] IndicesValidos;
    delete[] VisitasValidas;
    //para spawnear el npc vas al widfget img npc, traer la biblioteca npcgenerico,guardar puntero npcgenerico y en el constructor hacer new ncpcgenerico y hacer comoi padre
    // img npc y dsp 2 problemas, tamanio y show, en el momento que spawnee, tendria q hacer static cast y usar metodo setnpcinfo en setdocumentacion info y mandar eel puntero
    // dsp de setnpc uso metodo show
}

void LibroReglas::MoverIndice(int index){
    switch (index){
    case 1:
        ui->PaginasLibro->setCurrentIndex(index);
        setUpPagina1();
        break;
    }
}

void LibroReglas::IrAPagina1(){
    MoverIndice(1);
}
