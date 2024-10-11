#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H
#include<QString>
#include <QWidget>
#include <QSoundEffect>
#include <QPushButton>
#include "../PantallaTransicion/pantallatransicion.h"
#include "../SaveSlots/guardarpartida.h"

namespace Ui {
class PantallaMenu;
}

class PantallaMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaMenu(GuardarPartidas *, QWidget *parent = nullptr);
    void setInicio();
    ~PantallaMenu();
    void stopMusic();
    void continueMusic();
    void checkSaveSlots();
public slots:
    void setVolumen(float);
    void setMusicVolume(float);

signals:
    void clickedJugar();
    void clickedCargar();
    void clickedSettings();
    void clickedSalir();
    void clickedFacil();
    void clickedNormal();
    void clickedDemonio();
    void slotSelected2Save(int);
    void slotSelected2Play(int);
    void clickedStartDefault(int dificultad);
    void clickedStart(int nivel, int dificultad);
    void clickedStartCheat(int lvl, int dif, quint32 seed);
    void clickedTutorial();
    void EnviarLogs(QString Log);

protected:
    void keyPressEvent(QKeyEvent *event) override; // Para detectar cuando se presiona una tecla
    void ActualizarCont(int &, bool &);
    void DesbloquearCheats();
    int SecuenciaMagica = 0;
    bool CheatsActivados = false;

private slots:
    void actualizarNivel(int);
    void actualizarDificultad(int);

    void switchCheatClicked();

    void botonJugarClicked();
    void switchSelectorDificultad();

    void botonSettingsclicked();
    void botonSalirclicked();

    void botonFacilclicked();
    void switchFacil();
    void botonNormalclicked();
    void switchNormal();
    void botonDemonioclicked();
    void switchDemonio();

    void botonCargarclicked();
    void switchCargar();

    void botonPartida1clicked();
    void botonPartida2clicked();
    void botonPartida3clicked();

    void botonVolver1clicked();
    void switchMenu();

    void botonStartclicked();
    void cheatStartClicked();
    void SlotGuardadoSeleccionado(int);

    void tutorialButton();
private:
    // Sistema de partidas guardadas:
    const QString COLOR_DESBLOQUEADO = "color: white; background-color: rgb(170, 0, 255);";
    const QString COLOR_BLOQUEADO = "color: white; background-color: #1e1532;";
    GuardarPartidas * guardarPartida;
    vector<bool> Partidas;

    void bloquearBotonGuardado(QPushButton * botonGuardado, QPushButton * botonRanura);
    void desbloquearBotonGuardado(QPushButton * botonGuardado, QPushButton * botonRanura);
    void setBotonesPartida(int num, bool);
    void ConfigurarSonidos();
    void ConfigurarBotonesDificultad();
    void ConfigurarBotonesElegirPartidaGuardada();
    void ConfigurarBotonesElegirRanura();

    QSoundEffect Musica;
    QSoundEffect GTALocura;
    QSoundEffect SonidosBotones;
    QSoundEffect SonidoModoDemonio;
    int dificultad = 1;
    int nivel = 1;
    quint32 seedPersonalizada;
    Ui::PantallaMenu *ui;
    PantallaTransicion * transicion;
    int indicePrevio;
    int indiceMainMenu;
};

#endif // PANTALLAMENU_H
