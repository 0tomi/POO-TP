#ifndef PANTALLAMENU_H
#define PANTALLAMENU_H

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
    void clickedSettings();
    void clickedSalir();
    void clickedFacil();
    void clickedNormal();
    void clickedDemonio();
    void clickedStart();

private slots:
    void botonJugarClicked();
    void botonSettingsclicked();
    void botonSalirclicked();
    void botonFacilclicked();
    void botonNormalclicked();
    void botonDemonioclicked();

private:
    Ui::PantallaMenu *ui;
};

#endif // PANTALLAMENU_H
