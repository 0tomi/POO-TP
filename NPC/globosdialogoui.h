#ifndef GLOBOSDIALOGOUI_H
#define GLOBOSDIALOGOUI_H

#include <QWidget>
#include <QTimer>

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

public slots:
    void setMensaje(const QString &mensaje); // Recibe el mensaje y lo setea.

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

private slots:
    void TerminarMensaje();
};

#endif // GLOBOSDIALOGOUI_H
