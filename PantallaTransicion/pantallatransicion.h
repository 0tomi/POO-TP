#ifndef PANTALLATRANSICION_H
#define PANTALLATRANSICION_H

#include <QWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <functional>

namespace Ui {
class PantallaTransicion;
}

class PantallaTransicion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaTransicion(QWidget *parent = nullptr);
    ~PantallaTransicion();

    bool Mostrando() const;

    template <typename T>
    void ArrancarTransicion(int Duracion, T* objeto, void (T::*metodo)());
    void ArrancarTransicion(int duracion, std::function<void()> func);
    void ArrancarTransicionCargando(int duracion, std::function<void()> func);

signals:
    void midAnimacion();
    void terminoAnimacion();

private:
    Ui::PantallaTransicion *ui;
    QPropertyAnimation* iniciarTransicion;
    QPropertyAnimation* terminarTransicion;
    QGraphicsOpacityEffect* efecto;

    // metodo del objeto que se ejecutara
    std::function<void()> metodo2ejecutar;
    bool mostrando;

    void MidTransicion();
    void TerminarTransicion();
};

// Definición del método template
// Definimos el metodo aca por temas del compilador, para que no se le mame la burra al c++ como diria el profe
    template <typename T>
    void PantallaTransicion::ArrancarTransicion(int Duracion, T* objeto, void (T::*metodo)()) {
        // Configuramos el metodo que se ejecutará
        metodo2ejecutar = [objeto, metodo]() {
            (objeto->*metodo)();
        };

        iniciarTransicion->setDuration(Duracion); // duración en milisegundos
        terminarTransicion->setDuration(Duracion);

        // Colocamos la opacidad en 0 para arrancar la animacion
        efecto->setOpacity(0);

        show();
        mostrando = true;
        iniciarTransicion->start();
    }

#endif // PANTALLATRANSICION_H
