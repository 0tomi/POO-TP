#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
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

private:
    Ui::GameScreen *ui;
    QTimer *temporizadorBotones;

    void RealizarConecciones();

    // no se como hacer esto asi q lo voy a hacer asi nomas
    void Acepto();
    void Rechazo();
    void SelloDocumento(bool Boton);
    void BloquearBotones(bool Bloqueo);
    // Otro metodo que voy  a poner simplemente porque no se como se hace.
    void DesbloquearBotones();

    // Documentos
    DocumentosUI* doc;

    void CentrarDocumentos();

    void SpawnearDocumento();
    void EntrarDOC();
    void SacarDOC();

    // NPCs
    NPCUI *npcUI;

    void SpawnearNPC();
    void EntrarNPC();
    void SacarNPC();

    // Reubicar NPCs en la escena
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GAMESCREEN_H
