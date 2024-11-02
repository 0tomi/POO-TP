#ifndef NPCFONDO_H
#define NPCFONDO_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QRandomGenerator>

namespace Ui {
class NPCFondo;
}

class NPCFondo : public QWidget
{
    Q_OBJECT

public:
    explicit NPCFondo(QRandomGenerator *  generador, QWidget *parent = nullptr);
    void moverAdelante();
    void moverAdelanteSinSalir();
    void moverAdelante(int x, int y);
    void volverEntrar();
    void salir();
    void MoverAdelante(NPCFondo * anterior);
    void setPrimero(bool);
    bool isPrimero() const;
    ~NPCFondo();

public slots:
    void updateLocation(QPoint);

signals:
    void Salio();
    void Entro();
    void Posicion(QPoint);

private slots:
    void PrepararAnimacionStandBy();

private:
    void PrepararAnimacionAdelantar(int x, int y);
    bool primero;
    QPropertyAnimation * animacionAdelantar;
    QPropertyAnimation * animacionSalir;
    QPropertyAnimation * animacionEntrar;
    QPropertyAnimation * standBy;
    bool estadoStandBy;
    int yNormal;

    QRandomGenerator * rand;
    QWidget * padre;
    Ui::NPCFondo *ui;
};

#endif // NPCFONDO_H
