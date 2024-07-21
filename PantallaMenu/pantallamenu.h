#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H
#include<QString>
#include <QWidget>

namespace Ui {
class PantallaMenu;
}

class PantallaMenu : public QWidget
{
    Q_OBJECT

public:

    explicit PantallaMenu(QWidget *parent = nullptr);
    ~PantallaMenu();
signals:
    void clickedJugar();
    void clickedCargar();
    void clickedSettings();
    void clickedSalir(QCloseEvent *event);
    void clickedFacil();
    void clickedNormal();
    void clickedDemonio();
    void clickedStart(int dificultad, QString modo);
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
    int dificultad=0;
    QString modo;
    Ui::PantallaMenu *ui;
};

#endif // PANTALLAMENU_H
