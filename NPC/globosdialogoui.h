#ifndef GLOBOSDIALOGOUI_H
#define GLOBOSDIALOGOUI_H

#include <QWidget>

namespace Ui {
class GlobosDialogoUI;
}

class GlobosDialogoUI : public QWidget
{
    Q_OBJECT

public:
    explicit GlobosDialogoUI(QWidget *parent = nullptr);
    ~GlobosDialogoUI();

private:
    Ui::GlobosDialogoUI *ui;
};

#endif // GLOBOSDIALOGOUI_H
