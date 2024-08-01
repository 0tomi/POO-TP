#ifndef BOTONESCUSTOM_H
#define BOTONESCUSTOM_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QSoundEffect>

namespace Ui {
class BotonesCustom;
}

class BotonesCustom : public QWidget
{
    Q_OBJECT

public:
    explicit BotonesCustom(QWidget *parent = nullptr);
    explicit BotonesCustom(QString Estado1, QString Estado2, QWidget *parent = nullptr);
    void SetTiempoBloqueo(int milisegundos);
    void BloquearBoton(bool bloqueo);
    ~BotonesCustom();

    void Accion();

    void setSkinBotonBlock(QString newSkinBotonBlock);
    void setSkinBotonUnblock(QString newSkinBotonUnblock);

    bool getBotonBloqueado() const;

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

    QSoundEffect sonido2;

    void CrearSkinBoton(QString Estado1, QString &Direccion);
    bool BotonBloqueado;

    void PausarBoton();
    void DesbloquearBoton();

    int TiempoBloqueo;
};

#endif // BOTONESCUSTOM_H
