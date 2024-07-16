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

private:
    Ui::PantallaMenu *ui;
};

#endif // PANTALLAMENU_H
