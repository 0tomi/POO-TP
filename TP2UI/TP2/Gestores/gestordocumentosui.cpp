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

GestorDocumentosUI::~GestorDocumentosUI()
{
    for (int i = 0; i < 10; i++)
        delete documentosUI[i];
    delete Temporizador;
    delete pase;
}

void GestorDocumentosUI::setUp(int Level, QWidget *objeto)
{
    this->Escritorio = objeto;
    setUpNivel(Level);
}

void GestorDocumentosUI::setUpNivel(int nivel)
{
    int Index = 0;
    setUpLevel1(Index);
    if (nivel >= 1)
        setUpLevel2(Index);
    if (nivel >= 2)
        setUpLevel3(Index);
    if (nivel >= 3)
        setUpLevel4(Index);
    if (nivel >= 4)
        setUpLevel5(Index);
}

void GestorDocumentosUI::setUpLevel1(int &Index)
{
    this->topePerLevel = 2;
    // New del uader pass (pase diplomatico)
    pase = new UADERpass(Escritorio);
    setUpDocumento(pase);

    // New al pasaporte, dni

    Index++;

    // New de estancia
    documentosUI[Index] = new estanciaUI(Escritorio);
    setUpDocumento(documentosUI[Index]);
    Index++;
}

void GestorDocumentosUI::setUpLevel2(int &Index)
{
    // News del pais de residencia

    Index++;
    // News del proposito de viaje

    Index++;
}

void GestorDocumentosUI::setUpLevel3(int &Index)
{
    // News del documento para saber si la persona viaja sola o con otros integrantes

    Index++;

    // Es probable que esto no sea un documento, sino que sea algo de dialogo

    Index++;
}

void GestorDocumentosUI::setUpLevel4(int &Index)
{
    // New paises de paso anteriores

    Index++;
    // New Visas previas

    Index++;
    // New Ocupacion

    Index++;
    // New Bienes transportados

    Index++;
    // vemos si meter todas estas cosas, porque es mucho, o capaz las distribuimos en otros niveles.
}

void GestorDocumentosUI::setUpLevel5(int &Index)
{
    // new Verificacion de antecedentes

    Index++;
    // new Busqueda elementos prohibidos

    Index++;
}

void GestorDocumentosUI::deleteDocumentos()
{
    for (int i = 0; i < this->topePerLevel; i++)
        delete documentos[i];
}

void GestorDocumentosUI::setDocumento(NPC* npcInfo)
{
    Documentacion** info = npcInfo->getDocumentos();
    int Tipo = npcInfo->getTipo();

    for (int i = 1; i < topePerLevel; i++)
        if (info[i] != nullptr)
            documentos[i] = info[i];

    if (Tipo == 2)
        tienePase = true;
    else tienePase = false;

    NPCcomun* npcComunInfo;
    // Aca iria la declaracion del npc especial.

    npcComunInfo = dynamic_cast<NPCcomun*> (npcInfo);
    if (!npcComunInfo)
        qDebug() << "El npc es de tipo especial"; // y aca iria el casteo al npc especial

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
    int Index;
    switch(nivel){
    case 1: Index = 2;
        setUpLevel2(Index);
        break;
    case 2:
        Index = 4;
        setUpLevel2(Index);
        break;
    case 3:
        Index = 6;  // ############################# CAMBIAR A FUTURO ######################
        setUpLevel2(Index);
        break;
    case 4:
        Index = 8;
        setUpLevel2(Index);
        break;
    }
}

void GestorDocumentosUI::Centrar()
{
    if (tienePase)
        CentrarDocumento(pase);

    for (int i = 0; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            CentrarDocumento(documentosUI[i]);
}

void GestorDocumentosUI::Entrar()
{
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            EntrarDocumento(documentosUI[i]);

    if (tienePase)
        EntrarDocumento(pase);
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
        if (documentos[i] != nullptr)
            SalirDocumento(documentosUI[i]);
}

void GestorDocumentosUI::DetenerAnimaciones()
{
    if (tienePase)
        pase->PausarAnimacionCentrar();
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->PausarAnimacionCentrar();
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

    doc->Centrar(centerX,centerY);
}

void GestorDocumentosUI::Termino()
{
    emit TerminoEntrada();
}

void GestorDocumentosUI::setUpDocumento(DocumentosUI *doc)
{
    doc->hide();
    doc->move(0,-(doc->width()));
}
