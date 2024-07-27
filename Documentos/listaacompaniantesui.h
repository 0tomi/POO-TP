#ifndef LISTAACOMPANIANTESUI_H
#define LISTAACOMPANIANTESUI_H

#include <QWidget>

namespace Ui {
class ListaAcompaniantesUI;
}

class ListaAcompaniantesUI : public QWidget
{
    Q_OBJECT

public:
    explicit ListaAcompaniantesUI(QWidget *parent = nullptr);
    ~ListaAcompaniantesUI();

private:
    Ui::ListaAcompaniantesUI *ui;
};

#endif // LISTAACOMPANIANTESUI_H
