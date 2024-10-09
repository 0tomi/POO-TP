#ifndef RADIOGRAFIAUI_H
#define RADIOGRAFIAUI_H

#include <QWidget>
#include <Qlabel>
#include <map>
#include <QString>
#include <QPixmap>
#include"documentosui.h"
#include "radiografia.h"


namespace Ui {
class radiografiaui;
}

class radiografiaui : public DocumentosUI
{
    Q_OBJECT

public:
    explicit radiografiaui(QWidget *parent = nullptr);
    void setLabels(radiografia* datos);
    ~radiografiaui();

private:
    Ui::radiografiaui *ui;
    QLabel *labelsCuerpo[10];
    std::map<QString, QPixmap>items;

};

#endif // RADIOGRAFIAUI_H
