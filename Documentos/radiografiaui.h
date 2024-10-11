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

/*  Falta:
 *  - Meter sonidos al dar vuelta las hojas
 *  - Sonido al cerrar la radiografia
 *  - Resize al pixelmap, para que se ajuste al tamanio del label sobre el que se aplica (Reescalar el pixmap)
 *  - Asegurar mas el sistema de labels usando los mapas.
 */
namespace Ui {
class radiografiaui;
}

class radiografiaui : public DocumentosUI
{
    Q_OBJECT

public:
    explicit radiografiaui(QWidget *parent = nullptr);
    virtual void setDocumentacionInfo(Documentacion *documento) override;
    virtual void Entrar() override;
    virtual void Sacar() override;

    ~radiografiaui();
    //void Sacar(); Falta override y meterle sonidos al cerrarla
    //void Entrar();
    bool getMostrando() const;

private slots:
    void on_voltear1_clicked();
    void on_voltear2_clicked();
    void on_botonsalir_clicked();

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
