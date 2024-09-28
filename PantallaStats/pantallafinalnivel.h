#ifndef PANTALLAFINALNIVEL_H
#define PANTALLAFINALNIVEL_H

#include "../juego.h"

#include <QWidget>
#include <vector>
#include <QString>
#include <QRandomGenerator>

namespace Ui {
class PantallaFinalNivel;
}

class PantallaFinalNivel : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaFinalNivel(QWidget *parent = nullptr);
    ~PantallaFinalNivel();
    void setPantallaFinalUI(Juego* juegoInfo, bool perdio);
    void guardarPartida();

    vector<QString> getTips();
    void setTips(vector<QString> tipsNew);
signals:
    void salirClicked();
    void sigNivelClicked(int NextLevel, int Dificultad);
    void reintentarClicked(int NextLevel, int Dificultad);

private slots:
    void onSalirClicked();
    void onSigNivelClicked();
    void onReintentarClicked();

private:
    Ui::PantallaFinalNivel *ui;
    const QString COLOR_ROJO = "color: rgb(255, 0, 0);";
    const QString COLOR_BLANCO = "color: rgb(255, 255, 255);";
    int NivelActual;
    int Dificultad;
    bool Perdio;
    vector<QString> tips;

    QRandomGenerator Random;
};

#endif // PANTALLAFINALNIVEL_H
