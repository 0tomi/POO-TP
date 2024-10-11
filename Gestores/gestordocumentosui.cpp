#include "gestordocumentosui.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GestorDocumentosUI::GestorDocumentosUI()
{
    Temporizador = new QTimer();
    Temporizador->setSingleShot(true);
    connect(Temporizador, &QTimer::timeout, this, &GestorDocumentosUI::Termino);

    // Seteamos los documentos en nulo
    for (int i = 0; i < MAX_Documentos; i++)
        documentos[i] = nullptr;
    for (int i = 0; i < MAX_Documentos; i++)
        documentosUI[i] = nullptr;

    pase = nullptr;
    nuevaEstancia = nullptr;
}

GestorDocumentosUI::~GestorDocumentosUI()
{
    for (int i = 0; i < MAX_Documentos; i++)
        delete documentosUI[i];
    delete Temporizador;
    delete pase;
}

bool GestorDocumentosUI::getMostrando() const
{
    return Mostrando;
}

void GestorDocumentosUI::TerminoNivel()
{
    if (Mostrando)
        this->Salir();
}

void GestorDocumentosUI::setVolume(float vol)
{
    if (nuevaEstancia)
        nuevaEstancia->setVolume(vol);
}

/// #################################### SETTERS ###################################################

void GestorDocumentosUI::setUp(int Level, QWidget *objeto)
{
    this->Escritorio = objeto;
    for (int i = 0; i < MAX_Documentos; i++)
        documentos[i] = nullptr;
    setUpNivel(Level);
}

void GestorDocumentosUI::setUpNivel(int nivel)
{
    this->nivelActual = nivel;
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

void GestorDocumentosUI::addRadiografia(radiografiaui *rad)
{
    documentosUI[5] = rad;
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
        nuevaEstancia = new NuevaEstanciaUI(Escritorio);
        documentosUI[Index] = nuevaEstancia;
        setUpDocumento(documentosUI[Index]);
    }
}

void GestorDocumentosUI::setUpLevel5()
{
    //this->topePerLevel = 5;
    //int Index = 5;
    //if (documentosUI[Index] == nullptr){
        // new Verificacion de antecedentes
   // }
}

void GestorDocumentosUI::deleteDocumentos()
{
    for (int i = 0; i < this->topePerLevel; i++)
        delete documentos[i];

    delete documentos[5];
}

void GestorDocumentosUI::setDocumento(NPC* npcInfo)
{
    Documentacion** info = npcInfo->getDocumentos();

    for (int i = 0; i < topePerLevel; i++)
        if (info[i] != nullptr)
            documentos[i] = info[i];

    if (documentos[4])
        documentos[1] = nullptr;

    int Tipo = npcInfo->getTipo();
    if (Tipo == 2)
        tienePase = true;
    else tienePase = false;

    if (this->nivelActual >= 5) {
        auto Radiografia = npcInfo->getDocumento(NPC::Radiografia);
        documentosUI[5]->setDocumentacionInfo(Radiografia);
    }

    // ### Seteamos el DNI o el Pasaporte segun corresponda
    if (documentos[0] != nullptr){
        auto identificacion = dynamic_cast<Pasaporte*> (documentos[0]);
        if (identificacion->getnacionalidad() == "Aztana")
            documentosUI[0] = dniUI;
        else
            documentosUI[0] = pasaporteUI;
    }

    // ### Seteamos el resto de documentos
    for (int i = 0; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->setDocumentacionInfo(documentos[i]);
}

void GestorDocumentosUI::Centrar()
{
    if (tienePase)
        pase->Centrar();

    for (int i = 0; i < topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Centrar();

    if (!documentosUI[5]->isHidden())
        documentosUI[5]->Centrar();
}

void GestorDocumentosUI::Entrar()
{
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Entrar();

    if (tienePase)
        pase->Entrar();
    Mostrando = true;
}

void GestorDocumentosUI::Salir()
{
    if (tienePase)
        pase->Sacar();
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            documentosUI[i]->Sacar();

    if (!documentosUI[5]->isHidden())
        documentosUI[5]->Centrar();

    Mostrando = false;
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
    DetenerAnimaciones();
    if (documentosUI[0] == pasaporteUI)
        pasaporteUI->setAprobado();
}

void GestorDocumentosUI::Rechazar()
{
    DetenerAnimaciones();
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
