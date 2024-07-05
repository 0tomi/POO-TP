#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QResizeEvent>

#include "NPC/npcui.h"
#include "Documentos/uaderpass.h"

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

public slots:
    void EmpezarJuego();
    void SacarNPC();

private:
    Ui::GameScreen *ui;

    // Documentos
    DocumentosUI* doc;
    void SpawnearDocumento();
    void EntrarDOC();

    QPropertyAnimation *animacionEntradaDOC;
    void PrepararAnimacionEntradaDOC();

    QPropertyAnimation *animacionSalidaDOC;
    void PrepararAnimacionSalidaDOC();

    void FletearDOC();

    // NPCs
    void SpawnearNPC();

    NPCUI *npcUI;
    void EntrarNPC();

    QPropertyAnimation *animacionEntrada;
    void PrepararAnimacionEntradaNPC();

    QPropertyAnimation *animacionSalida;
    void PrepararAnimacionSalidaNPC();

    // Reubicar NPCs en la escena
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void FletearNPC();

};

#endif // GAMESCREEN_H
