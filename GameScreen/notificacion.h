#ifndef NOTIFICACION_H
#define NOTIFICACION_H

#include "../Documentos/documentosui.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QSoundEffect>
#include <QTimer>

namespace Ui {
class Notificacion;
}

class Notificacion : public DocumentosUI
{
    Q_OBJECT

public:
    explicit Notificacion(int Numero, bool Multa, QString motivos, QWidget *parent = nullptr);
    void setDocumentacionInfo(Documentacion *documento){};
    ~Notificacion();
    void setVolume(float);
    void Entrar() override;

signals:
    void QuiereCerrarNotificacion(int);

private:
    Ui::Notificacion *ui;
    QTimer Temporizador;
    QPushButton * cerrar;
    QHBoxLayout * layout;
    int numeroNotificacion;

    // Sonido
    QSoundEffect sonidoEntrada;
    QSoundEffect sonidoSalida;
};

#endif // NOTIFICACION_H
