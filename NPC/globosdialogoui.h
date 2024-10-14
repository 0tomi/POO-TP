#ifndef GLOBOSDIALOGOUI_H
#define GLOBOSDIALOGOUI_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QRandomGenerator>
#include <QSoundEffect>

namespace Ui {
class GlobosDialogoUI;
}

class GlobosDialogoUI : public QWidget
{
    Q_OBJECT

public:
    explicit GlobosDialogoUI(QWidget *parent = nullptr);
    void MostrarMensaje();
    void PausarMensaje();
    void ReanudarMensaje();
    void InterrumpirMensaje(bool estado);
    void ForzarSalir();
    void Finalizar();
    void CorrerMensaje(); // A futuro, para acumular mensajes.
    ~GlobosDialogoUI();
    void Centrar();
    void setVolume(float);

public slots:
    void setMensaje(const QString &newMensaje); // Recibe el mensaje y lo setea.

signals:
    void Hablando(const QString &mensaje);
    void MensajePreparado();
    void MensajeTerminado();

private:
    QRandomGenerator Random;
    QWidget * padre;
    Ui::GlobosDialogoUI *ui;

    void MensajeEmitido();
    QString mensaje;
    QTimer TiempoVisualizacion;
    int tiempoRestante;

    void SetearAnimacionEntrada();
    void PrepararAnimacionEntrada();
    QPropertyAnimation * animacionEntrada;

    void SetearAnimacionSalida();
    QPropertyAnimation * animacionSalida;
    QGraphicsOpacityEffect * opacityEffect;
    void EsconderDialogo();

    void CalcularPosicionDelGlobo(int &X, int &Y);
    bool Mostrandose;
    bool interrumpirMensaje;

    int tamanioNormalGloboX, tamanioNormalGloboY;
    int tamanioAumentadoGloboX, tamanioAumentadoGloboY;

    QUrl URLSonidos[4];
    QSoundEffect Sonido;
    void ReproducirSonido();
private slots:
    void TerminarMensaje();
};

#endif // GLOBOSDIALOGOUI_H
