#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H
#include<QString>
#include <QWidget>
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

private slots:
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

private:
    int dificultad=0;
    Ui::PantallaMenu *ui;
    PantallaTransicion * transicion;
    int indicePrevio;
    int indiceMainMenu;
};

#endif // PANTALLAMENU_H
