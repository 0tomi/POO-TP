#ifndef NPCFONDO_H
#define NPCFONDO_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class NPCFondo;
}

class NPCFondo : public QWidget
{
    Q_OBJECT

public:
    explicit NPCFondo(QWidget *parent = nullptr);
    void MoverAdelante(NPCFondo * anterior);
    ~NPCFondo();

private:
    void PrepararAnimacionAdelantar(int x, int y);
    QPropertyAnimation * animacionAdelantar;
    QWidget * padre;
    Ui::NPCFondo *ui;
};

#endif // NPCFONDO_H
