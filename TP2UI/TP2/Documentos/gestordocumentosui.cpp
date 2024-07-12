#include "gestordocumentosui.h"
#include <QDebug>

GestorDocumentosUI::GestorDocumentosUI()
{
    Temporizador = new QTimer();
    Temporizador->setSingleShot(true);
    connect(Temporizador, &QTimer::timeout, this, &GestorDocumentosUI::Termino);

    // Seteamos los documentos en nulo
    for (int i = 0; i < 10; i++)
        documentos[i] = nullptr;
    for (int i = 0; i < 10; i++)
        documentosUI[i] = nullptr;
}

void GestorDocumentosUI::setUpDocumentos(int Level, QWidget *objeto)
{
    this->Escritorio = objeto;
    setUpNivel(Level);
}

void GestorDocumentosUI::setUpNivel(int nivel)
{
    setUpLevel1();
    if (nivel >= 1)
        setUpLevel2();
    if (nivel >= 2)
        setUpLevel3();
    if (nivel >= 3)
        setUpLevel4();
    if (nivel >= 4)
        setUpLevel5();
}

void GestorDocumentosUI::setUpLevel1()
{
    this->topePerLevel = 2;
    // aca tocara inicializar todos los documentos del respectivo level.

    // New del uader pass (pase diplomatico)
    pase = new UADERpass(Escritorio);
    setUpDocumento(pase);

    // New al pasaporte, dni

    // New de estancia
    documentosUI[1] = new estanciaUI(Escritorio);
    setUpDocumento(documentosUI[1]);
}

void GestorDocumentosUI::setUpLevel2()
{
    // News del pais de residencia

    // News del proposito de viaje

}

void GestorDocumentosUI::setUpLevel3()
{
    // News del documento para saber si la persona viaja sola o con otros integrantes

    // Es probable que esto no sea un documento, sino que sea algo de dialogo

}

void GestorDocumentosUI::setUpLevel4()
{
    // New paises de paso anteriores

    // New Visas previas

    // New Ocupacion

    // New Bienes transportados

    // vemos si meter todas estas cosas, porque es mucho, o capaz las distribuimos en otros niveles.
}

void GestorDocumentosUI::setUpLevel5()
{
    // new Verificacion de antecedentes

    // new Busqueda elementos prohibidos

}

void GestorDocumentosUI::deleteDocumentos()
{
    for (int i = 0; i < this->topePerLevel; i++)
        delete documentos[i];
}

void GestorDocumentosUI::setDocumento(Documentacion **info, int Tipo)
{
    for (int i = 1; i < topePerLevel; i++)
        if (info[i] != nullptr)
            documentos[i] = info[i];

    if (Tipo == 2)
        tienePase = true;
    else tienePase = false;

    /*  ### PARTE QUE SE ENCARGA DE SETEAR EL PASAPORTE O EL DNI SEGUN CORRESPONDA

    if (documentos[0] != nullptr){
        DNIgenerico *identificacion = documentos[0];
        if (identifacion->getPais() == "Aztana"){
            documentosUI[0] = DNIUI;
            DNIUI->setDocumentacionInfo(documentos[0], NPCui)
        } else {
            documentosUI[0] = PasaporteUI;
            PasaporteUI->setDocumentacionInfo(documentos[0], NPCui)
    }
    */

    for (int i = 1; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->setDocumentacionInfo(documentos[i]);
    // en desarrollo
}

void GestorDocumentosUI::nextNivel(int nivel)
{
    if (nivel == 1)
        setUpLevel2();
    if (nivel == 2)
        setUpLevel3();
    if (nivel == 3)
        setUpLevel4();
    if (nivel == 4)
        setUpLevel5();
}

void GestorDocumentosUI::Centrar()
{
    if (tienePase)
        CentrarDocumento(pase);

    for (int i = 0; i < topePerLevel; i++)
        if (documentosUI[i] != nullptr)
            CentrarDocumento(documentosUI[i]);
}

void GestorDocumentosUI::Entrar()
{
    if (tienePase)
        EntrarDocumento(pase);
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentosUI[i] != nullptr)
            EntrarDocumento(documentosUI[i]);
}

void GestorDocumentosUI::EntrarDocumento(DocumentosUI *doc)
{
    int centerX = ((Escritorio->width()) - (doc->width())) /2;
    int centerY = (((Escritorio->height())) - (doc->height())) / 2;
    Temporizador->start(900);
    doc->Entrar(centerX,centerY);
}

void GestorDocumentosUI::Salir()
{
    if (tienePase)
        SalirDocumento(pase);
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentosUI[i] != nullptr)
            SalirDocumento(documentosUI[i]);
}

void GestorDocumentosUI::DetenerAnimaciones()
{
    if (tienePase)
        pase->PausarAnimacionCentrar();
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentosUI[i] != nullptr)
            documentosUI[i]->PausarAnimacionCentrar();
}

GestorDocumentosUI::~GestorDocumentosUI()
{
    for (int i = 0; i < 10; i++)
        delete documentosUI[i];
    for (int i = 0; i < 10; i++)
        delete documentos[i];
    delete Temporizador;
    delete pase;
}

void GestorDocumentosUI::SalirDocumento(DocumentosUI *doc)
{
    int centerX = ((Escritorio->width()) - (doc->width())) / 2;
    doc->Sacar(centerX);
}

void GestorDocumentosUI::CentrarDocumento(DocumentosUI *doc)
{
    int centerX = ((Escritorio->width()) - (doc->width())) /2;
    int centerY = (((Escritorio->height())) - (doc->height())) / 2;

    qDebug() << "Se movio doc";
    doc->Centrar(centerX,centerY);
}

void GestorDocumentosUI::Termino()
{
    qDebug() << "Termino el cronometro";
    emit TerminoEntrada();
}

void GestorDocumentosUI::setUpDocumento(DocumentosUI *doc)
{
    doc->hide();
    doc->move(0,-(doc->width()));
}
