#ifndef GENERARUI_H
#define GENERARUI_H

#include "estancia.h"
#include "generarestancia.h"
#include "juego.h"
#include "atributoscomunes.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class GenerarUI;
}

class GenerarUI : public QWidget
{
    Q_OBJECT

public:
    explicit GenerarUI(QWidget *parent = nullptr);
    ~GenerarUI();

private:
    Ui::GenerarUI *ui;
};

#endif // GENERARUI_H
