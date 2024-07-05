#ifndef NPCUI_H
#define NPCUI_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class NPCUI;
}

class NPCUI : public QWidget
{
    Q_OBJECT

public:
    explicit NPCUI(QWidget *parent = nullptr);
    ~NPCUI();

private:
    Ui::NPCUI *ui;
};

#endif // NPCUI_H
