#ifndef NPCGENERICOUI_H
#define NPCGENERICOUI_H

#include "npcui.h"
#include "npccomun.h"
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QRandomGenerator>
#include <QLabel>

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
    void Entrar() override;
    void Sacar() override;

protected:
    void ReescalarNPC();
    void ReescalarLabel(QLabel * Label, QPixmap &ImagenLabel, double factorW, double factorH);
    void reposicionarLabels(double factorW, double factorH);
    void reposLabel(QPoint pos, QLabel * label, double factorW, double factorH, int margen);

    QPoint ojosPos;
    QPoint bocaPos;
    QPoint cejasPos;
    QPoint narizPos;

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
