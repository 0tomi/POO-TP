#ifndef INTROPANTALLA_H
#define INTROPANTALLA_H

#include <QWidget>
#include "../juego.h"
#include "libroreglas.h"

namespace Ui {
class IntroPantalla;
}

class IntroPantalla : public QWidget
{
    Q_OBJECT

public:
    explicit IntroPantalla(Juego*, QWidget *parent = nullptr);
    void acomodarPantalla();
    void Mostrar();
    void setUp(int nivel);
    void forzarSalir();
    ~IntroPantalla();

    bool isActive() const;

public slots:
    void setVolumenes(float);

signals:
    void ClickeoEmpezar();

private:
    void Salir();
    QPropertyAnimation * animacionSalida;
    Ui::IntroPantalla *ui;
    QWidget * padre;
    Juego* juego;
    libroreglas * libro;
    bool activa;
};

#endif // INTROPANTALLA_H
