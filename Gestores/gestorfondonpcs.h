#ifndef GESTORFONDONPCS_H
#define GESTORFONDONPCS_H

#include <QWidget>
#include <QVector>
#include "../NPC/npcfondo.h"

using namespace std;

class GestorFondoNPCs: public QObject
{
    Q_OBJECT
public:
    GestorFondoNPCs();
    void setUp(QWidget * Fondo);
    ~GestorFondoNPCs();
    void start(int CantNPCs);
    void clear();

public slots:
    void resizeNPCs();
    void pasarNPC();
    void updateCantidadNPCs(int);

private slots:
    void NPCterminoSalir();
    void NPCactualizoPosicion(QPoint);

private:
    QWidget * fondo;
    QVector<NPCFondo*> npcs;
    int ultimoNPCenSalir;

    int cantidadNPCs;
    int cantidadNPCsFondo;
};

#endif // GESTORFONDONPCS_H
