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
    enum class TiposImagen {
        Normal,
        Border
    };

    explicit BotonesCustom(QWidget *parent = nullptr);
    explicit BotonesCustom(QString Estado1, QString Estado2, QWidget *parent = nullptr);
    explicit BotonesCustom(QString Estado1, QString Estado2, TiposImagen , QWidget *parent = nullptr);
    void copyFormat();
    void SetTiempoBloqueo(int milisegundos);
    void BloquearBoton(bool bloqueo);
    ~BotonesCustom();

    void Accion();

    void setSkinBotonBlock(QString newSkinBotonBlock);
    void setSkinBotonUnblock(QString newSkinBotonUnblock);

    bool getBotonBloqueado() const;
    void setVolumen(float);

signals:
    void BotonApretado();
    void BottonLiberado();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BotonesCustom *ui;
    QWidget * padre;
    QTimer TemporizadorBotones;
    QString SkinBotonBlock;
    QString SkinBotonUnblock;

    const QString ImagenNormal = "image";
    const QString ImagenStretch = "border-image";
    QSoundEffect sonido2;

    void CrearSkinBoton(QString Estado1, QString &Direccion);
    void CrearSkinBoton(QString Estado1, QString &Direccion, TiposImagen);
    bool BotonBloqueado;

    void PausarBoton();
    void DesbloquearBoton();

    int TiempoBloqueo;
};

#endif // BOTONESCUSTOM_H
