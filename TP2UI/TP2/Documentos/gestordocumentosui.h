#ifndef GESTORDOCUMENTOSUI_H
#define GESTORDOCUMENTOSUI_H
#include <QWidget>
#include "uaderpass.h"
#include "documentacion.h"
#include "estanciaUI.h"
#include "pasaporteui.h"
#include "dni.h"
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
    void DetenerAnimaciones();

    ~GestorDocumentosUI();

signals:
    void TerminoEntrada();

private:
    QTimer *Temporizador; // Hasta no tener los pasaportes y DNIs, usare esto.
    QWidget *Escritorio;
    DocumentosUI* documentosUI[10];
    Documentacion* documentos[10];
    UADERpass* pase;
    Pasaporteui * Pasaporte;
    DNI * Dni;

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
    void setUpLevel1(int &Index);
    void setUpLevel2(int &Index);
    void setUpLevel3(int &Index);
    void setUpLevel4(int &Index);
    void setUpLevel5(int &Index);
};

#endif // GESTORDOCUMENTOSUI_H
