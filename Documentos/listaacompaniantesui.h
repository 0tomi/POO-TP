#ifndef LISTAACOMPANIANTESUI_H
#define LISTAACOMPANIANTESUI_H

#include "documentosui.h"
#include "listaacompaniantes.h"

namespace Ui {
class ListaAcompaniantesUI;
}

class ListaAcompaniantesUI : public DocumentosUI
{
    Q_OBJECT

public:
    explicit ListaAcompaniantesUI(QWidget *parent = nullptr);
    virtual void setDocumentacionInfo(Documentacion *documento);
    ~ListaAcompaniantesUI();

private:
    Ui::ListaAcompaniantesUI *ui;
};

#endif // LISTAACOMPANIANTESUI_H
