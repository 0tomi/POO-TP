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

    pase = nullptr;
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
    setUpLevel1();
    if (nivel >= 2)
        setUpLevel2();
    if (nivel >= 3)
        setUpLevel3();
    if (nivel >= 4)
        setUpLevel4();
    if (nivel >= 5)
        setUpLevel5();
}

void GestorDocumentosUI::setUpLevel1()
{
    this->topePerLevel = 2;
    int Index = 0;
    if (pase == nullptr){
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
}

void GestorDocumentosUI::setUpLevel2()
{
    // A futuro vemos que va aca
    this->topePerLevel = 3;
    int Index = 2;
    if (documentosUI[Index] == nullptr){
        // Aca iria el setup para el pais de residencia
        documentosUI[Index] = new paisresidenciaui(Escritorio);
        setUpDocumento(documentosUI[Index]);
    }
}

void GestorDocumentosUI::setUpLevel3()
{
    this->topePerLevel = 4;
    int Index = 3;
    if (documentosUI[Index] == nullptr){
        documentosUI[Index] = new ListaAcompaniantesUI(Escritorio);
        setUpDocumento(documentosUI[Index]);
    }
}

void GestorDocumentosUI::setUpLevel4()
{
    this->topePerLevel = 5;
    int Index = 4;
    if (documentosUI[Index] == nullptr){

        // ######### Aca iria el NEW para el nuevo Doc Estancia ######

        setUpDocumento(documentosUI[Index]);
    }
}

void GestorDocumentosUI::setUpLevel5()
{
    this->topePerLevel = 7;
    int Index = 5;
    if (documentosUI[Index] == nullptr){
        // new Verificacion de antecedentes

        Index++;
        // new Busqueda elementos prohibidos

    }
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
