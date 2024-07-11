#ifndef TOMIBOTONES_H
#define TOMIBOTONES_H

#include <QWidget>
#include <QTimer>
#include <QString>

namespace Ui {
class TomiBotones;
}

class TomiBotones : public QWidget
{
    Q_OBJECT

public:
    explicit TomiBotones(QString Estado1, QString Estado2, QWidget *parent = nullptr);
    void SetTiempoBloqueo(int milisegundos);
    void BloquearBoton(bool bloqueo);
    ~TomiBotones();

signals:
    void BotonApretado();
    void BottonLiberado();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::TomiBotones *ui;
    QTimer TemporizadorBotones;
    QString SkinBotonBlock;
    QString SkinBotonUnblock;

    void CrearSkinBoton(QString Estado1, QString &Direccion);
    bool BotonBloqueado;

    void PausarBoton();
    void DesbloquearBoton();

    int TiempoBloqueo;
    void Accion();
};

#endif // TOMIBOTONES_H
