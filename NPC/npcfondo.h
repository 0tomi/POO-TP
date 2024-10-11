#ifndef NPCFONDO_H
#define NPCFONDO_H

#include <QWidget>

namespace Ui {
class NPCFondo;
}

class NPCFondo : public QWidget
{
    Q_OBJECT

public:
    explicit NPCFondo(QWidget *parent = nullptr);
    ~NPCFondo();

private:
    QWidget * padre;
    Ui::NPCFondo *ui;
};

#endif // NPCFONDO_H
