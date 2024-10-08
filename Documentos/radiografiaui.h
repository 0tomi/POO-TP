#ifndef RADIOGRAFIAUI_H
#define RADIOGRAFIAUI_H

#include <QWidget>
#include <Qlabel>

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
    QLabel *labelsCuerpo[10];
};

#endif // RADIOGRAFIAUI_H
