#ifndef NPCUI_H
#define NPCUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include "../NPC/npc.h"

namespace Ui {
class NPCUI;
}

class NPCUI : public QWidget
{
    Q_OBJECT

public:
    explicit NPCUI(QWidget *parent = nullptr);
    virtual void setNPC(NPC* newNPCenEscena) = 0;
    void Entrar(int X, int Y);
    void Sacar(int X, int Y);
    virtual ~NPCUI();

signals:
    void animacionSalirTerminada();

protected:
    // Animaciones
    void PrepararAnimacionEntrada(int X, int Y);
    QPropertyAnimation *animacionEntrada;

    void PrepararAnimacionSalida(int X, int Y);
    QPropertyAnimation *animacionSalida;

    // Termino animacion
    void TerminoAnimacion();

private:
    Ui::NPCUI *ui;
};

#endif // NPCUI_H
