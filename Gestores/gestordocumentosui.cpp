#include "gestordocumentosui.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
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

/// #################################### SETTERS ###################################################

void GestorDocumentosUI::setUp(int Level, QWidget *objeto)
{
    this->Escritorio = objeto;
    setUpNivel(Level);
}

void GestorDocumentosUI::setUpNivel(int nivel)
{
    int Index = 0;
    setUpLevel1(Index);
    if (nivel >= 2)
        setUpLevel2(Index);
    if (nivel >= 3)
        setUpLevel3(Index);
    if (nivel >= 4)
        setUpLevel4(Index);
    if (nivel >= 5)
        setUpLevel5(Index);
}
void GestorDocumentosUI::nextNivel(int nivel)
{
    int Index;
    switch(nivel){
    case 2: Index = 2;
        setUpLevel2(Index);
        break;
    case 3:
        Index = 4;
        setUpLevel2(Index);
        break;
    case 4:
        Index = 6;  // ############################# CAMBIAR A FUTURO ######################
        setUpLevel2(Index);
        break;
    case 5:
        Index = 8;
        setUpLevel2(Index);
        break;
    }
}

void GestorDocumentosUI::setUpLevel1(int &Index)
{
    this->topePerLevel = 2;
    // New del uader pass (pase diplomatico)
    pase = new UADERpass(Escritorio);
    setUpDocumento(pase);

    // New al pasaporte, dni
    pasaporteUI = new PasaporteUI(Escritorio);
    dniUI = new DNI(Escritorio);
    setUpDocumento(pasaporteUI);
    setUpDocumento(dniUI);
    Index++;

    // New de estancia
    documentosUI[Index] = new estanciaUI(Escritorio);
    setUpDocumento(documentosUI[Index]);
    Index++;
}

void GestorDocumentosUI::setUpLevel2(int &Index)
{
    // A futuro vemos que va aca
    this->topePerLevel = 3;
    Index++;
}

void GestorDocumentosUI::setUpLevel3(int &Index)
{
    this->topePerLevel = 4;
    // News del documento para saber si la persona viaja sola o con otros integrantes

    Index++;

    // Es probable que esto no sea un documento, sino que sea algo de dialogo
}

void GestorDocumentosUI::setUpLevel4(int &Index)
{
    this->topePerLevel = 4;
    // Aca iria rework de la estancia
}

void GestorDocumentosUI::setUpLevel5(int &Index)
{
    this->topePerLevel = 6;
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

    for (int i = 0; i < topePerLevel; i++)
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


    // ### Seteamos el DNI o el Pasaporte segun corresponda
    if (documentos[0] != nullptr){
        Pasaporte *identificacion = dynamic_cast<Pasaporte*> (documentos[0]);
        if (identificacion->getnacionalidad() == "Aztana"){
            documentosUI[0] = dniUI;
            dniUI->setDNIInfo(identificacion, npcInfo);
        } else {
            documentosUI[0] = pasaporteUI;
            pasaporteUI->setPasaporteInfo(identificacion, npcInfo);
        }
    }

    // ### Seteamos el resto de documentos
    for (int i = 1; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->setDocumentacionInfo(documentos[i]);
    // en desarrollo
}

void GestorDocumentosUI::Centrar()
{
    if (tienePase)
        pase->Centrar();

    for (int i = 0; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Centrar();
}

void GestorDocumentosUI::Entrar()
{
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Entrar();

    if (tienePase)
        pase->Entrar();
}

void GestorDocumentosUI::Salir()
{
    if (tienePase)
        pase->Sacar();
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Sacar();
}

void GestorDocumentosUI::DetenerAnimaciones()
{
    if (tienePase)
        pase->PausarAnimacionCentrar();
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->PausarAnimacionCentrar();
}

void GestorDocumentosUI::Aprobado()
{
    if (documentosUI[0] == pasaporteUI)
        pasaporteUI->setAprobado();
}

void GestorDocumentosUI::Rechazar()
{
    if (documentosUI[0] == pasaporteUI)
        pasaporteUI->setRechazado();
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
