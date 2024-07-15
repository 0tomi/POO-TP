#ifndef NPCUI_H
#define NPCUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
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
    virtual void Entrar(int X, int Y);
    virtual void Sacar(int X, int Y);
    virtual ~NPCUI();

signals:
    void animacionSalirTerminada();
    void animacionEntrarTerminada();
    void Saliendo();
    void Entrando();
    void QuiereHablar(const QString &dialogo);

protected:
    // Animaciones
    void PrepararAnimacionEntrada(int X, int Y);
    QPropertyAnimation *animacionEntrada;

    void PrepararAnimacionSalida(int X, int Y);
    QPropertyAnimation *animacionSalida;

    // Termino animacion
    void TerminoAnimacion();

    // Dialogos
    QTimer emitirDialogo;
    NPC* NPCrepresentado;

protected slots:
    void Hablar();  // Toca reworkear para futuros niveles

private:
    Ui::NPCUI *ui;
};

#endif // NPCUI_H
