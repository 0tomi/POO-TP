#ifndef PANTALLAPAUSA_H
#define PANTALLAPAUSA_H

#include <QWidget>
#include <QSoundEffect>

namespace Ui {
class PantallaPausa;
}

class PantallaPausa : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPausa(QWidget *parent = nullptr);
    void setInicio();
    void BlockVolverMenu(bool estado);
    ~PantallaPausa();

public slots:
    void setVolumen(float);
    void setFullScreenButton();
    void setWindowedButton();

signals:
    void setFullScreen();
    void setWindowedScreen();
    void quit();
    void return2lastWidget();
    void clickedTutorial();
    void musicVolume(float);
    void soundVolume(float);
    void EnviarLogs(QString log);
private:
    Ui::PantallaPausa *ui;
    QSoundEffect SonidosBotones;

private slots:
    void musicSliderChanged(int);
    void soundSliderChanged(int);
    void buttonFullScreenClicked();
    void buttonWindowedClicked();
    void buttonQuitClicked();
    void buttonReturnClicked();
    void ConfirmarSalir();
    void tutorialButton();
};

#endif // PANTALLAPAUSA_H
