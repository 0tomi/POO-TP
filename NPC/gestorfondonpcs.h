#ifndef GESTORFONDONPCS_H
#define GESTORFONDONPCS_H

#include <QWidget>
#include

class GestorFondoNPCs: public QObject
{
    Q_OBJECT
public:
    GestorFondoNPCs(QWidget * Fondo);

public slots:
    void updateCantidadNPCs(int);
    void resizeNPCs();
    void pasarNPC();

private:
    QWidget * fondo;
    int cantidadNPCs;
    int cantidadNPCsFondo;
};

#endif // GESTORFONDONPCS_H
