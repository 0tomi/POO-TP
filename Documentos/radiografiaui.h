#ifndef RADIOGRAFIAUI_H
#define RADIOGRAFIAUI_H

#include <QWidget>
#include <Qlabel>
#include <QMap>
#include <QString>
#include <QPixmap>
#include"documentosui.h"
#include "radiografia.h"
#include "../lectorarchivos.h"

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
    QMap<QString, QPixmap>items;
    vector<QString>objetos;
    void setmap();

};

#endif // RADIOGRAFIAUI_H
