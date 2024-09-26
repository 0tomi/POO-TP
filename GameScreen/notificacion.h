#ifndef NOTIFICACION_H
#define NOTIFICACION_H

#include <QWidget>

namespace Ui {
class Notificacion;
}

class Notificacion : public QWidget
{
    Q_OBJECT

public:
    explicit Notificacion(QWidget *parent = nullptr);
    ~Notificacion();

private:
    Ui::Notificacion *ui;
};

#endif // NOTIFICACION_H
