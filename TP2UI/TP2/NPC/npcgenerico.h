#ifndef NPCGENERICO_H
#define NPCGENERICO_H

#include "npcui.h"
#include <QWidget>


namespace Ui {
class NPCGenerico;
}

class NPCGenerico : public NPCUI
{
    Q_OBJECT

public:
    explicit NPCGenerico(QWidget *parent = nullptr);
    ~NPCGenerico();

private:
    Ui::NPCGenerico *ui;
};

#endif // NPCGENERICO_H
