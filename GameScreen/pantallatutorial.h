#ifndef PANTALLATUTORIAL_H
#define PANTALLATUTORIAL_H

#include <QWidget>
#include <QSoundEffect>

namespace Ui {
class PantallaTutorial;
}

class PantallaTutorial : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaTutorial(QWidget *parent = nullptr);
    void setSoundVolume(float vol);
    void setMusicVolume(float vol);
    ~PantallaTutorial();

private:
    QSoundEffect sonidoBotones, musica;
    Ui::PantallaTutorial *ui;
    void setBotones();
    void IrPagAnterior();
    void IrPagSiguiente();
    void SaltarPagina(int pagina);
    void SalirTutorial();
    void actualizarBotones();

    int CantidadPaginas;
    int PaginaActual;
signals:
    void TerminarTutorial();
};

#endif // PANTALLATUTORIAL_H
