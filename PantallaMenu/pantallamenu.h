#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H
#include<string>
#include <QWidget>

namespace Ui {
class PantallaMenu;
}

class PantallaMenu : public QWidget
{
    Q_OBJECT

public:
    int dificultad=0;
    std::string modo;
    explicit PantallaMenu(QWidget *parent = nullptr);
    ~PantallaMenu();
signals:
    void clickedJugar();
    void clickedCargar();
    void clickedSettings();
    void clickedSalir();
    void clickedFacil();
    void clickedNormal();
    void clickedDemonio();
    void clickedStart(int dificultad, std::string modo);
    void clickedPartida1();
    void clickedPartida2();
    void clickedPartida3();

private slots:
    void botonJugarClicked();
    void botonSettingsclicked();
    void botonSalirclicked();
    void botonFacilclicked();
    void botonNormalclicked();
    void botonDemonioclicked();
    void botonCargarclicked();
    void botonPartida1clicked();
    void botonPartida2clicked();
    void botonPartida3clicked();
    void botonVolver3clicked();
    void botonVolver2clicked();
    void botonVolver1clicked();
    void botonStartclicked();

private:

    Ui::PantallaMenu *ui;
};

#endif // PANTALLAMENU_H
