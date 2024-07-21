#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

#include <QWidget>

namespace Ui {
class PantallaInicio;
}

class PantallaInicio : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaInicio(QWidget *parent = nullptr);

    ~PantallaInicio();

signals:
    void ClickeoBotonEmpezar(int Nivel, int Dificultad);

private slots:
     void empezarJuego();

private:
    Ui::PantallaInicio *ui;
};

#endif // PANTALLAINICIO_H
