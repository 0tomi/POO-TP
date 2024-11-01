#ifndef NPCFONDO_H
#define NPCFONDO_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class NPCFondo;
}

class NPCFondo : public QWidget
{
    Q_OBJECT

public:
    explicit NPCFondo(QWidget *parent = nullptr);
    void moverAdelante();
    void moverAdelante(int x, int y);
    void volverEntrar();
    void salir();
    void MoverAdelante(NPCFondo * anterior);
    ~NPCFondo();

signals:
    void Salio();
    void Entro();
    void Posicion(QPoint);

private:
    void PrepararAnimacionAdelantar(int x, int y);
    QPropertyAnimation * animacionAdelantar;
    QPropertyAnimation * animacionSalir;
    QPropertyAnimation * animacionEntrar;
    QWidget * padre;
    Ui::NPCFondo *ui;
};

#endif // NPCFONDO_H
