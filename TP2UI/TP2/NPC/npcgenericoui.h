#ifndef NPCGENERICOUI_H
#define NPCGENERICOUI_H

#include "npcui.h"
#include "npccomun.h"
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QRandomGenerator>

namespace Ui {
class NPCGenericoUI;
}

class NPCGenericoUI : public NPCUI
{
    Q_OBJECT

public:
    explicit NPCGenericoUI(QWidget *parent = nullptr);
    ~NPCGenericoUI();
    void setNPC(NPC* newNPCenEscena) override;
    void Rechazado();
    void Entrar(int X, int Y) override;
    void Sacar(int X, int Y) override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::NPCGenericoUI *ui;
    NPCcomun *NPCenEscena;

    // Facciones NPC
    QPixmap ojos, cuerpo, boca, nariz, cejas;

    // Parpadeo
    QRandomGenerator* tiempoParpadeo;
    QTimer parpadeo;

    void Parpadear();
    void setearParpadear(bool estado);
    bool parpadeando;

    QPixmap ojosCerrados;
    QPixmap bocaCerrada;
};

#endif // NPCGENERICOUI_H
