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
private slots:
    void onSalirClicked();
    void onSigNivelClicked();
private:
    Ui::PantallaFinalNivel *ui;
};

#endif // PANTALLAFINALNIVEL_H
