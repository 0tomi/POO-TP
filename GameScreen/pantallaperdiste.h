#ifndef PANTALLAPERDISTE_H
#define PANTALLAPERDISTE_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSoundEffect>

namespace Ui {
class PantallaPerdiste;
}

class PantallaPerdiste : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPerdiste(QWidget *parent = nullptr);
    void setSoundVolume(float vol);
    void Iniciar(bool Perdio);
    ~PantallaPerdiste();

    bool getMostrandoPantalla() const;

signals:
    void MidAnimacion();
    void AnimacionTermino();

private slots:
    void ArrancarFinal();
    void FinalizoAnimacion();

private:
    QSoundEffect sonidoGanar, sonidoPerder;
    bool MostrandoPantalla;
    Ui::PantallaPerdiste *ui;
    QWidget * padre;
    QTimer TiempoVisualizacion;
    QPropertyAnimation * inicio;
    QPropertyAnimation * final;
    QGraphicsOpacityEffect * opacityEffect;
};

#endif // PANTALLAPERDISTE_H
