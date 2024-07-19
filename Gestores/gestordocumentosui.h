5#ifndef GESTORDOCUMENTOSUI_H
#define GESTORDOCUMENTOSUI_H
#include <QWidget>
#include <QTimer>

#include "../Documentos/uaderpass.h"
#include "../Documentos/documentacion.h"
#include "../Documentos/estanciaUI.h"
#include "../Documentos/pasaporteui.h"
#include "../Documentos/dni.h"
#include "../NPC/npccomun.h"

class GestorDocumentosUI: public QWidget
{
    Q_OBJECT

public:
    GestorDocumentosUI();

    void setUp(int Level, QWidget *objeto);
    void setUpNivel(int nivel);
    void deleteDocumentos();

    void setDocumento(NPC* infoNPC);

    void Centrar();
    void Entrar();
    void Salir();
    void DetenerAnimaciones();

    void Aprobado();
    void Rechazar();

    ~GestorDocumentosUI();

signals:
    void TerminoEntrada();

private:
    QTimer *Temporizador; // Hasta no tener los pasaportes y DNIs, usare esto.
    QWidget *Escritorio;
    DocumentosUI* documentosUI[10];
    Documentacion* documentos[10];
    UADERpass* pase;
    DNI* dniUI;
    PasaporteUI* pasaporteUI;

    bool tienePase;
    int DocumentosEnEscena[10];
    int topePerNPC;
    int topePerLevel;

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
