#include "gestordocumentosui.h"

GestorDocumentosUI::GestorDocumentosUI()
{
    Temporizador = new QTimer();
    Temporizador->setSingleShot(true);
    connect(Temporizador, &QTimer::timeout, this, &GestorDocumentosUI::Termino);
}

void GestorDocumentosUI::setUpDocumentos(char Level, QWidget *objeto)
{
    this->Escritorio = objeto;
    if (Level == 1)
        setUpLevel1();
}

void GestorDocumentosUI::setUpLevel1()
{
    this->topePerLevel = 4;
    // aca tocara inicializar todos los documentos del respectivo level.
    pase = new UADERpass(Escritorio);
    setUpDocumento(pase);

    // resto de documentos
}

void GestorDocumentosUI::deleteDocumentos()
{
    for (int i = 0; i < this->topePerLevel; i++)
        delete documentos[i];
}

void GestorDocumentosUI::setDocumento(Documentacion **info, char Tipo)
{
    documentos = info;
    if (Tipo == 2)
        tienePase = true;
    else tienePase = false;

    for (int i = 0; i < topePerLevel; i++)
        if (!(documentos[i] == nullptr))
            documentosUI[i]->setDocumentacionInfo(documentos[i]);
    // en desarrollo
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
    if (tienePase)
        EntrarDocumento(pase);
    for (int i = 0; i < this->topePerLevel; i++)
        if (documentos[i] != nullptr)
            EntrarDocumento(documentosUI[i]);
}

void GestorDocumentosUI::EntrarDocumento(DocumentosUI *doc)
{
    int centerX = ((Escritorio->width()) - (doc->width())) /2;
    int centerY = (((Escritorio->height())) - (doc->height())) / 2;
    Temporizador->start(1000);
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

GestorDocumentosUI::~GestorDocumentosUI()
{
    for (int i = 0; i < 10; i++)
        delete documentosUI[i];
    delete[] documentos;
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
    doc->setFixedSize(300,300);
    doc->hide();
    doc->move(0,-(doc->width()));
}
