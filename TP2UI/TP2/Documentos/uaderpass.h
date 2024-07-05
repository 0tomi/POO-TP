#ifndef UADERPASS_H
#define UADERPASS_H

#include <QWidget>
#include "documentosui.h"

namespace Ui {
class UADERpass;
}

class UADERpass : public DocumentosUI
{
    Q_OBJECT

public:
    explicit UADERpass(QWidget *parent = nullptr);
    ~UADERpass();

private:
    Ui::UADERpass *ui;
};

#endif // UADERPASS_H
