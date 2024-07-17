#ifndef PANTALLAFINALNIVEL_H
#define PANTALLAFINALNIVEL_H

#include "../juego.h"

#include <QWidget>
#include <QString>

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
signals:
    void salirClicked();
    void sigNivelClicked();
    void reintentarClicked();

private slots:
    void onSalirClicked();
    void onSigNivelClicked();
    void onReintentarClicked();

private:
    Ui::PantallaFinalNivel *ui;
    const QString COLOR_ROJO = "color: rgb(255, 0, 0);";
    const QString COLOR_BLANCO = "color: rgb(255, 255, 255);";
};

#endif // PANTALLAFINALNIVEL_H
