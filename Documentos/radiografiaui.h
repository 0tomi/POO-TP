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
    ~radiografiaui();
    void Sacar();
    void Entrar();
private slots:
    void on_voltear1_clicked();

    void on_voltear2_clicked();

    void on_botonsalir_clicked();
    void entrarRadiografia();
    void setLabels(radiografia* datos);
private:
    Ui::radiografiaui *ui;
    QLabel *labelsCuerpo[10];
    QMap<QString, QPixmap>items;
    vector<QString>objetos;
    void setmap();
    bool Mostrando;
};

#endif // RADIOGRAFIAUI_H
