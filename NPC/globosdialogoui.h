#ifndef GLOBOSDIALOGOUI_H
#define GLOBOSDIALOGOUI_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

namespace Ui {
class GlobosDialogoUI;
}

class GlobosDialogoUI : public QWidget
{
    Q_OBJECT

public:
    explicit GlobosDialogoUI(QWidget *parent = nullptr);
    void MostrarMensaje();
    void ForzarSalir();
    void CorrerMensaje(); // A futuro, para acumular mensajes.
    ~GlobosDialogoUI();
    void Centrar(int X, int Y);

public slots:
    void setMensaje(const QString &mensaje, const int X, const int Y); // Recibe el mensaje y lo setea.

signals:
    void Hablando(const QString &mensaje);
    void MensajePreparado();
    void MensajeTerminado();

private:
    void DarFormatoPorqueQTesHorrible(QString &formato);
    Ui::GlobosDialogoUI *ui;
    void MensajeEmitido();
    QString mensaje;
    QTimer TiempoVisualizacion;

    void SetearAnimacionEntrada();
    void PrepararAnimacionEntrada(int X, int Y);
    QPropertyAnimation * animacionEntrada;

    void SetearAnimacionSalida();
    QPropertyAnimation * animacionSalida;
    QGraphicsOpacityEffect * opacityEffect;
    void EsconderDialogo();

    void CalcularPosicionDelGlobo(int &X, int &Y);
    void setMostrandose();
    bool Mostrandose;
private slots:
    void TerminarMensaje();
};

#endif // GLOBOSDIALOGOUI_H
