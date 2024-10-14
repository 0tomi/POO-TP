#ifndef NPCGENERICOUI_H
#define NPCGENERICOUI_H

#include "npcui.h"
#include "npccomun.h"
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QRandomGenerator>
#include <QLabel>
#include <QSoundEffect>

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
    void setSkinNPC(Skin skinNPC);
    void Rechazado();
    void Entrar() override;
    void Salir(bool Aceptado) override;
    void setSoundVolume(float vol);
    void Finalizar() override;

protected:
    void ReescalarNPC();
    void ReescalarLabel(QLabel * Label, QPixmap &ImagenLabel, double factorW, double factorH);
    void reposicionarLabels(double factorW, double factorH);
    void reposLabel(QPoint pos, QLabel * label, double factorW, double factorH, int margen);

    QPoint ojosPos;
    QPoint bocaPos;
    QPoint cejasPos;
    QPoint narizPos, peloPos, gorroPos;

private:
    Ui::NPCGenericoUI *ui;
    NPCcomun *NPCenEscena;

    // Funcion para eliminar la hoja CSS de la ui, para que no se superponga con los pixmaps
    // (porque sino cada vez que se quiera hacer una modificacion hay que estar colocando las imagenes)
    void LimpiarHojaCSS();

    // Facciones NPC
    QPixmap gorro, pelo, ojos, cuerpo, boca, nariz, cejas;

    // Parpadeo
    QRandomGenerator* tiempoParpadeo;
    QTimer parpadeo;
    QTimer quejarse;

    void emitQuejarse();
    void Parpadear();
    void setearParpadear(bool estado);
    bool parpadeando;

    QPixmap ojosCerrados;
    QPixmap bocaCerrada;
    QPixmap nada;

    // Sonido
    QSoundEffect Rechazo;
};

#endif // NPCGENERICOUI_H
