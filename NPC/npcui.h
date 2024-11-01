#ifndef NPCUI_H
#define NPCUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QRandomGenerator>
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
    virtual void Centrar();
    virtual void Entrar();
    virtual void Salir(bool Aceptado);
    virtual ~NPCUI();
    virtual void Pausar(bool Estado);
    virtual void Finalizar();

signals:
    void animacionSalirTerminada();
    void animacionEntrarTerminada();
    void Saliendo();
    void Entrando();
    void QuiereHablar(const QString &dialogo);

protected:
    // Animaciones
    QRandomGenerator random;
    void PrepararAnimacionStandBy();
    QPropertyAnimation * animacionStandBy;
    bool estadoAnimacionStandby;

    void PrepararAnimacionEntrada();
    QPropertyAnimation *animacionEntrada;

    void PrepararAnimacionSalida();
    void PrepararAnimacionSalida2();
    QPropertyAnimation *animacionSalida;

    // Termino animacion
    void TerminoAnimacion();

    bool Mostrandose;

    // Dialogos
    int remainingTime;
    QTimer emitirDialogo;
    NPC* NPCrepresentado;
    QWidget * padre;

protected slots:
    void Hablar();  // Toca reworkear para futuros niveles

private:
    Ui::NPCUI *ui;
};

#endif // NPCUI_H
