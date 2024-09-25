#ifndef PANTALLAPAUSA_H
#define PANTALLAPAUSA_H

#include <QWidget>

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
private:
    Ui::PantallaPausa *ui;

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
