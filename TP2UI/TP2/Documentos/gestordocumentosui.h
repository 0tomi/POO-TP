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
    void setUpNivel(int nivel);
    void deleteDocumentos();

    void setDocumento(Documentacion **info, int Tipo);
    void nextNivel(int nivel);

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
    void setUpDocumento(DocumentosUI *doc);

    // Setup de niveles
    void setUpLevel1();
    void setUpLevel2();
    void setUpLevel3();
    void setUpLevel4();
    void setUpLevel5();
};

#endif // GESTORDOCUMENTOSUI_H
