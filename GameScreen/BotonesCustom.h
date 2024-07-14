#ifndef BOTONESCUSTOM_H
#define BOTONESCUSTOM_H

#include <QWidget>
#include <QTimer>
#include <QString>

namespace Ui {
class BotonesCustom;
}

class BotonesCustom : public QWidget
{
    Q_OBJECT

public:
    explicit BotonesCustom(QString Estado1, QString Estado2, QWidget *parent = nullptr);
    void SetTiempoBloqueo(int milisegundos);
    void BloquearBoton(bool bloqueo);
    ~BotonesCustom();

signals:
    void BotonApretado();
    void BottonLiberado();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BotonesCustom *ui;
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

#endif // BOTONESCUSTOM_H
