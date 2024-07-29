#ifndef PAISRESIDENCIAUI_H
#define PAISRESIDENCIAUI_H
#include "documentosui.h"
#include "paisresidencia.h"
#include <QWidget>

namespace Ui {
class paisresidenciaui;
}

class paisresidenciaui : public DocumentosUI
{
    Q_OBJECT

public:
    explicit paisresidenciaui(QWidget *parent = nullptr);
    ~paisresidenciaui();
    virtual void setDocumentacionInfo(Documentacion *documento);

private:
    Ui::paisresidenciaui *ui;
    PaisResidencia * PaisResidenciaUI;
};

#endif // PAISRESIDENCIAUI_H
