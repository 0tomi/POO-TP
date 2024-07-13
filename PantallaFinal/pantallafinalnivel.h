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
    void setPantallaFinalUI(Juego* juegoInfo);
    void guardarPartida();
signals:
    void salirClicked();
    void sigNivelClicked();
    void cerrarApp();
private slots:
    void on_salir_clicked();
    void on_sigNivel_clicked();
private:
    Ui::PantallaFinalNivel *ui;
};

#endif // PANTALLAFINALNIVEL_H
