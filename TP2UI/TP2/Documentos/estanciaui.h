#ifndef ESTANCIAUI_H
#define ESTANCIAUI_H

#include <QWidget>
#include <QLabel>

#include "documentosui.h"
#include "estancia.h"

namespace Ui {
class estanciaUI;
}

class estanciaUI : public DocumentosUI
{
    Q_OBJECT

public:
    explicit estanciaUI(QWidget *parent = nullptr);
    void setDocumentacionInfo(Documentacion *documento) override;
    ~estanciaUI();

private:
    Ui::estanciaUI *ui;
    Estancia* estanciaInfo;
};

#endif // ESTANCIAUI_H
