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
    void setNPC(NPC* newNPCenEscena);
    void Rechazado();

private:
    Ui::NPCGenericoUI *ui;
    NPCcomun *NPCenEscena;

    QRandomGenerator* tiempoParpadeo;
    void Parpadear();
    void setearParpadear();
    bool parpadeando;
    QTimer* parpadeo;
    QPixmap* ojos;
};

#endif // NPCGENERICOUI_H
