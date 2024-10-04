#ifndef PANTALLAFINALNIVEL_H
#define PANTALLAFINALNIVEL_H

#include "../juego.h"
#include "../SaveSlots/guardarpartida.h"

#include <QWidget>
#include <QString>

namespace Ui {
class PantallaFinalNivel;
}

class PantallaFinalNivel : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaFinalNivel(GuardarPartidas* sg, QWidget *parent = nullptr);
    ~PantallaFinalNivel();
    void setPantallaFinalUI(Juego* juegoInfo, bool perdio);
signals:
    void salirClicked();
    void sigNivelClicked(int NextLevel, int Dificultad);
    void reintentarClicked(int NextLevel, int Dificultad);
    void EnviarLogs(QString Log);
private slots:
    void onSalirClicked();
    void onSigNivelClicked();
    void onReintentarClicked();

private:
    GuardarPartidas * saveGame;
    Ui::PantallaFinalNivel *ui;
    const QString COLOR_ROJO = "color: rgb(255, 0, 0);";
    const QString COLOR_BLANCO = "color: rgb(255, 255, 255);";
    int NivelActual;
    int Dificultad;
    bool Perdio;
};

#endif // PANTALLAFINALNIVEL_H
