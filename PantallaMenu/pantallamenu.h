#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H
#include<QString>
#include <QWidget>
#include <QSoundEffect>
#include "../PantallaTransicion/pantallatransicion.h"

namespace Ui {
class PantallaMenu;
}

class PantallaMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaMenu(QWidget *parent = nullptr);
    void setInicio();
    ~PantallaMenu();
public slots:
    void setVolumen(float);

signals:
    void clickedJugar();
    void clickedCargar();
    void clickedSettings();
    void clickedSalir();
    void clickedFacil();
    void clickedNormal();
    void clickedDemonio();
    void clickedStart(int nivel, int dificultad);
    void clickedPartida1();
    void clickedPartida2();
    void clickedPartida3();
    void clickedTutorial();

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

    void tutorialButton();

private:
    QSoundEffect GTALocura;
    QSoundEffect SonidosBotones;
    QSoundEffect SonidoModoDemonio;
    int dificultad = 1;
    int nivel = 1;
    Ui::PantallaMenu *ui;
    PantallaTransicion * transicion;
    int indicePrevio;
    int indiceMainMenu;
};

#endif // PANTALLAMENU_H
