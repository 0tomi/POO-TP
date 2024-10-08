#ifndef RADIOGRAFIAUI_H
#define RADIOGRAFIAUI_H

#include <QWidget>

namespace Ui {
class radiografiaui;
}

class radiografiaui : public QWidget
{
    Q_OBJECT

public:
    explicit radiografiaui(QWidget *parent = nullptr);
    ~radiografiaui();

private:
    Ui::radiografiaui *ui;
};

#endif // RADIOGRAFIAUI_H
