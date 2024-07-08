#ifndef GESTORDOCUMENTOSUI_H
#define GESTORDOCUMENTOSUI_H
#include <QWidget>
#include "uaderpass.h"
#include "documentacion.h"
#include <QTimer>

class GestorDocumentosUI: public QWidget
{
    Q_OBJECT

public:
    GestorDocumentosUI();

    void setUpDocumentos(int Level, QWidget *objeto);
    void deleteDocumentos();

    void setDocumento(Documentacion **info, int Tipo);

    void Centrar();
    void Entrar();
    void Salir();

    ~GestorDocumentosUI();

signals:
    void TerminoEntrada();

private:
    QTimer *Temporizador; // Hasta no tener los pasaportes y DNIs, usare esto.
    QWidget *Escritorio;
    DocumentosUI* documentosUI[10];
    Documentacion* documentos[10];
    UADERpass* pase;

    bool tienePase;
    int DocumentosEnEscena[10];
    int topePerNPC;
    int topePerLevel;

    void EntrarDocumento(DocumentosUI *doc);
    void SalirDocumento(DocumentosUI *doc);
    void CentrarDocumento(DocumentosUI *doc);

    void Termino();

    void setUpLevel1();
    void setUpDocumento(DocumentosUI *doc);
};

#endif // GESTORDOCUMENTOSUI_H
